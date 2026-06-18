## Copyright (c) Microsoft Corporation. All rights reserved.
## Licensed under the MIT License.

[CmdletBinding()]
param(
    [Parameter(Mandatory = $true)]
    [ValidateSet('repository', 'psresource', 'repositorylist', 'psresourcelist')]
    [string]$ResourceType,
    [Parameter(Mandatory = $true)]
    [ValidateSet('get', 'set', 'test', 'delete', 'export')]
    [string]$Operation,
    [Parameter(ValueFromPipeline)]
    $stdinput
)

enum Scope {
    CurrentUser
    AllUsers
}

enum ExitCode {
    Success = 0
    Error = 1
    RepositoryNotFound = 2
    RepositoryNotTrusted = 3
    InstallationFailed = 4
    UnknownResourceType = 5
    ResourceNotImplemented = 6
    TestNotImplemented = 7
    ExportNotImplemented = 8
    GetNotImplemented = 9
    SetNotImplemented = 10
    DeleteNotImplemented = 11
    UnknownOperation = 12
}

class PSResource {
    [string]$name
    [string]$version
    [Scope]$scope
    [string]$repositoryName
    [bool]$preRelease
    [bool]$_exist
    [bool]$_inDesiredState

    PSResource([string]$name, [string]$version, [Scope]$scope, [string]$repositoryName, [bool]$preRelease) {
        $this.name = $name
        $this.version = $version
        $this.scope = $scope
        $this.repositoryName = $repositoryName
        $this.preRelease = $preRelease
        $this._exist = $true
    }

    PSResource([string]$name) {
        $this.name = $name
        $this._exist = $false
    }

    [bool] IsInDesiredState([PSResource] $other) {
        $retValue = $true

        $psResourceSplat = @{
            Name           = $this.name
            Version        = if ($this.version) { $this.version } else { '*' }
        }

        Get-PSResource @psResourceSplat | Where-Object {
            ($null -eq $this.scope -or $_.Scope -eq $this.scope) -and
            ($null -eq $this.repositoryName -or $_.Repository -eq $this.repositoryName)
        } | Select-Object -First 1 | ForEach-Object {
            Write-Trace -message "Matching resource found: Name=$($_.Name), Version=$($_.Version), Scope=$($_.Scope), Repository=$($_.Repository), PreRelease=$($_.PreRelease)" -level debug
            $this._exist = $true
        }

        if ($this.name -ne $other.name) {
            Write-Trace -message "Name mismatch: $($this.name) vs $($other.name)" -level debug
            $retValue = $false
        }
        elseif ($null -ne $this.version -and $null -ne $other.version -and -not (SatisfiesVersion -version $this.version -versionRange $other.version)) {
            Write-Trace -message "Version mismatch: $($this.version) vs $($other.version)" -level debug
            $retValue = $false
        }
        elseif ($null -ne $this.scope -and $this.scope -ne $other.scope) {
            Write-Trace -message "Scope mismatch: $($this.scope) vs $($other.scope)" -level debug
            $retValue = $false
        }
        elseif ($null -ne $this.repositoryName -and $this.repositoryName -ne $other.repositoryName) {
            Write-Trace -message "Repository mismatch: $($this.repositoryName) vs $($other.repositoryName)" -level debug
            $retValue = $false
        }
        elseif ($this._exist -ne $other._exist) {
            Write-Trace -message "_exist mismatch: $($this._exist) vs $($other._exist)" -level debug
            $retValue = $false
        }

        return $retValue
    }

    [string] ToJson() {
        $retVal = ($this | Select-Object -ExcludeProperty _inDesiredState | ConvertTo-Json -Compress -EnumsAsStrings)
        Write-Trace -message "Serializing PSResource to JSON. Name: $($this.name), Version: $($this.version), Scope: $($this.scope), RepositoryName: $($this.repositoryName), PreRelease: $($this.preRelease), _exist: $($this._exist)" -level debug
        Write-Trace -message "Serialized JSON: $retVal" -level trace
        return $retVal
    }

    [string] ToJsonForTest() {
        return ($this | ConvertTo-Json -Compress -Depth 5 -EnumsAsStrings)
    }
}

class PSResourceList {
    [string]$repositoryName
    [PSResource[]]$resources
    [bool]$trustedRepository
    [bool]$_inDesiredState

    PSResourceList([string]$repositoryName, [PSResource[]]$resources, [bool]$trustedRepository) {
        $this.repositoryName = $repositoryName
        $this.resources = $resources
        $this.trustedRepository = $trustedRepository
    }

    [bool] IsInDesiredState([PSResourceList] $other) {
        if ($this.repositoryName -ne $other.repositoryName) {
            Write-Trace -message "RepositoryName mismatch: $($this.repositoryName) vs $($other.repositoryName)" -level debug
            return $false
        }

        if ($null -ne $this.resources -and $this.resources.Count -ne $other.resources.Count) {
            Write-Trace -message "Resources count mismatch: $($this.resources.Count) vs $($other.resources.Count)" -level debug
            return $false
        }

        foreach ($otherResource in $other.resources) {
            $found = $false
            foreach ($resource in $this.resources) {
                if ($resource.IsInDesiredState($otherResource)) {
                    $found = $true
                    break
                }
            }

            if ($found) {
                Write-Trace -message "Resource match found for: $($otherResource.name)" -level debug
                break
            }
            else {
                Write-Trace -message "Resource mismatch for: $($otherResource.name)" -level debug
                return $false
            }
        }

        return $true
    }

    [string] ToJson() {
        $resourceJson = if ($this.resources) { ($this.resources | ForEach-Object { $_.ToJson() }) -join ',' } else { '' }
        $resourceJson = "[$resourceJson]"
        $jsonString = "{'repositoryName': '$($this.repositoryName)','resources': $resourceJson}"
        $jsonString = $jsonString -replace "'", '"'
        $retVal =  $jsonString | ConvertFrom-Json | ConvertTo-Json -Compress -EnumsAsStrings

        Write-Trace -message "Serializing PSResourceList to JSON. RepositoryName: $($this.repositoryName), TrustedRepository: $($this.trustedRepository), Resources count: $($this.resources.Count)" -level debug
        Write-Trace -message "Serialized JSON: $retVal" -level trace

        return $retVal
    }

    [string] ToJsonForTest() {
        Write-Trace -message "Serializing PSResourceList to JSON for test output. RepositoryName: $($this.repositoryName), TrustedRepository: $($this.trustedRepository), Resources count: $($this.resources.Count)" -level debug
        $jsonForTest = $this | ConvertTo-Json -Compress -Depth 5 -EnumsAsStrings
        Write-Trace -message "Serialized JSON: $jsonForTest" -level trace
        return $jsonForTest
    }
}

class Repository {
    [string]$name
    [string]$uri
    [bool]$trusted
    [int]$priority
    [string]$repositoryType
    [bool]$_exist

    Repository([string]$name) {
        $this.name = $name
        $this._exist = $false
        $this.repositoryType = 'Unknown'
    }

    Repository([string]$name, [string]$uri, [bool]$trusted, [int]$priority, [string]$repositoryType) {
        $this.name = $name
        $this.uri = $uri
        $this.trusted = $trusted
        $this.priority = $priority
        $this.repositoryType = $repositoryType
        $this._exist = $true
    }

    Repository([PSCustomObject]$repositoryInfo) {
        $this.name = $repositoryInfo.Name
        $this.uri = $repositoryInfo.Uri
        $this.trusted = $repositoryInfo.Trusted
        $this.priority = $repositoryInfo.Priority
        $this.repositoryType = $repositoryInfo.ApiVersion
        $this._exist = $true
    }

    Repository([string]$name, [bool]$exist) {
        $this.name = $name
        $this._exist = $exist
        $this.repositoryType = 'Unknown'
    }

    [string] ToJson() {
        return ($this | ConvertTo-Json -Compress -EnumsAsStrings)
    }
}

function Write-Trace {
    param(
        [string]$message,

        [ValidateSet('error', 'warn', 'info', 'debug', 'trace')]
        [string]$level = 'trace'
    )

    $trace = [pscustomobject]@{
        $level.ToLower() = $message
    } | ConvertTo-Json -Compress

    $host.ui.WriteErrorLine($trace)
}

function SatisfiesVersion {
    param(
        [string]$version,
        [string]$versionRange
    )

    $typeName = 'NuGet.Versioning.VersionRange'

    Write-Trace -message "Checking if version '$version' satisfies version range '$versionRange'." -level debug

    if ($typeName -as [type]) {
        Write-Trace -message "NuGet.Versioning assembly is already loaded. Using existing assembly." -level debug
    }
    else {
        Write-Trace -message "Loading NuGet.Versioning assembly from $PSScriptRoot/dependencies/NuGet.Versioning.dll" -level debug
        Add-Type -Path "$PSScriptRoot/dependencies/NuGet.Versioning.dll" -ErrorAction Stop | Out-Null
    }

    try {
        $versionRangeObj = [NuGet.Versioning.VersionRange]::Parse($versionRange)
        $resourceVersion = [NuGet.Versioning.NuGetVersion]::Parse($version)
        return $versionRangeObj.Satisfies($resourceVersion)
    }
    catch {
        Write-Trace -message "Error parsing version or version range: $($_.Exception.Message)" -level error
        return $false
    }
}

function ConvertInputToPSResource(
    [PSCustomObject]$inputObj,
    [string]$repositoryName = $null
) {
    $scope = if ($inputObj.Scope) { [Scope]$inputObj.Scope } else { [Scope]"CurrentUser" }

    $psResource = [PSResource]::new(
        $inputObj.Name,
        $inputObj.Version,
        $scope,
        $inputObj.repositoryName ? $inputObj.repositoryName : $repositoryName,
        $inputObj.PreRelease
    )

    if ($null -ne $inputObj._exist) {
        $psResource._exist = $inputObj._exist
    }

    return $psResource
}

# catch any un-caught exception and write it to the error stream
trap {
    Write-Trace -message "Exiting with error code 1 due to unhandled exception: $($_.Exception.Message)" -level debug
    exit [ExitCode]::Error
}

function GetPSResourceList {
    param(
        [PSCustomObject]$inputObj
    )

    $inputResources = @()
    $inputResources += if ($inputObj.resources) {
        $inputObj.resources | ForEach-Object {
            ConvertInputToPSResource -inputObj $_ -repositoryName $inputObj.repositoryName
        }
    }

    $repositoryState = Get-PSResourceRepository -Name $inputObj.repositoryName -ErrorAction SilentlyContinue

    if (-not $repositoryState) {
        Write-Trace -message "Repository not found: $($inputObj.repositoryName)" -level info
        $emptyResources = @()
        $emptyResources += $inputResources | ForEach-Object {
            [PSResource]::new($_.Name)
        }

        return [PSResourceList]::new($inputObj.repositoryName, $emptyResources, $false)
    }

    $inputPSResourceList = [PSResourceList]::new($inputObj.repositoryName, $inputResources, $repositoryState.Trusted)

    $allPSResources = @()

    if ($inputPSResourceList.repositoryName) {
        $currentUserPSResources = Get-PSResource -Scope CurrentUser -ErrorAction SilentlyContinue | Where-Object { $_.Repository -eq $inputPSResourceList.RepositoryName }
        $allUsersPSResources = Get-PSResource -Scope AllUsers -ErrorAction SilentlyContinue | Where-Object { $_.Repository -eq $inputPSResourceList.RepositoryName }
    }

    $allPSResources += $currentUserPSResources | ForEach-Object {
        [PSResource]::new(
            $_.Name,
            $_.Prerelease ? $_.Version.ToString() + "-" + $_.Prerelease : $_.Version.ToString(),
            [Scope]"CurrentUser",
            $_.Repository,
            $_.PreRelease
        )
    }

    $allPSResources += $allUsersPSResources | ForEach-Object {
        [PSResource]::new(
            $_.Name,
            $_.Prerelease ? $_.Version.ToString() + "-" + $_.Prerelease : $_.Version.ToString(),
            [Scope]"AllUsers",
            $_.Repository,
            $_.PreRelease ? $true : $false
        )
    }

    $resourcesExist = @()

    foreach ($resource in $allPSResources) {
        foreach ($inputResource in $inputResources) {
            if ($resource.Name -eq $inputResource.Name) {
                Write-Trace -message "Found matching resource for input: $($inputResource.Name). Checking version constraints. Input version: $($inputResource.Version), Resource version: $($resource.Version)" -level debug
                if ($inputResource.Version) {
                    # Use the NuGet.Versioning package if available, otherwise do a simple comparison
                    try {
                        if (SatisfiesVersion -version $resource.Version -versionRange $inputResource.Version) {
                            $resourcesExist += $resource
                        }
                    }
                    catch {
                        Write-Trace -message "Error checking version constraints for resource: $($inputResource.Name). Error details: $($_.Exception.Message)" -level debug
                        # Fallback: simple string comparison (not full NuGet range support)
                        if ($resource.Version.ToString() -eq $inputResource.Version) {
                            $resourcesExist += $resource
                        }
                    }
                }
            }
        }
    }

    ## For get operation we only need the first resource that exists, which is always the latest for currentUser
    PopulatePSResourceListObjectByRepository -resourcesExist $resourcesExist -inputResources $inputResources -repositoryName $inputPSResourceList.RepositoryName -trustedRepository $inputPSResourceList.trustedRepository
}

function GetOperation {
    param(
        [string]$ResourceType
    )

    $inputObj = $stdinput | ConvertFrom-Json -ErrorAction Stop

    Write-Trace -message "Starting Get operation for ResourceType: $ResourceType" -level trace

    switch ($ResourceType) {
        'repository' {
            $inputRepository = [Repository]::new($inputObj)
            $rep = Get-PSResourceRepository -Name $inputRepository.Name -ErrorVariable err -ErrorAction SilentlyContinue
            Write-Trace -message "Get-PSResourceRepository returned: $($rep | ConvertTo-Json -Compress)" -level trace

            $ret = if ($err.FullyQualifiedErrorId -eq 'ErrorGettingSpecifiedRepo,Microsoft.PowerShell.PSResourceGet.Cmdlets.GetPSResourceRepository') {
                Write-Trace -message "Repository not found: $($inputRepository.Name). Returning _exist = false" -level debug
                [Repository]::new(
                    $InputRepository.Name,
                    $false
                )
            }
            else {
                [Repository]::new(
                    $rep.Name,
                    $rep.Uri,
                    $rep.Trusted,
                    $rep.Priority,
                    $rep.ApiVersion
                )

                Write-Trace -message "Returning repository object for: $($ret.Name)" -level trace
            }

            Write-Trace -message "Serialized JSON output for Get operation: $($ret.ToJson())" -level trace

            return ( $ret.ToJson() )
        }

        'repositorylist' {
            Write-Trace -level error -message "Get operation is not implemented for RepositoryList resource."
            exit [ExitCode]::ResourceNotImplemented
        }
        'psresource' {
            Write-Trace -level error -message "Get operation is not implemented for PSResource resource."
            exit [ExitCode]::ResourceNotImplemented
        }
        'psresourcelist' {
            (GetPSResourceList -inputObj $inputObj).ToJson()
        }
        default {
            Write-Trace -level error -message "Unknown ResourceType: $ResourceType"
            exit [ExitCode]::ResourceNotImplemented
        }
    }
}

function TestPSResourceList {
    param(
        [PSCustomObject]$inputObj
    )

    $inputResources = @()
    $inputResources += $inputObj.resources | ForEach-Object { ConvertInputToPSResource -inputObj $_ -repositoryName $inputObj.repositoryName }

    $repositoryState = Get-PSResourceRepository -Name $inputObj.repositoryName -ErrorAction SilentlyContinue

    if (-not $repositoryState) {
        Write-Trace -message "Repository not found: $($inputObj.repositoryName). Returning PSResourceList with _inDesiredState = false." -level debug
        $retValue = [PSResourceList]::new($inputObj.repositoryName, $inputResources, $false)
        $retValue._inDesiredState = $false
        $retValue.ToJsonForTest()
        '["repositoryName", "resources"]'
    }

    $inputPSResourceList = [PSResourceList]::new($inputObj.repositoryName, $inputResources, $repositoryState.Trusted)

    $currentState = GetPSResourceList -inputObj $inputObj
    $inDesiredState = $currentState.IsInDesiredState($inputPSResourceList)

    $currentState._inDesiredState = $inDesiredState

    if ($inDesiredState) {
        Write-Trace -message "PSResourceList is in desired state." -level debug
        $currentState.ToJsonForTest()
        ## Return empty array as we are in desired state and there are no differing properties
        '[]'
    }
    else {
        Write-Trace -message "PSResourceList is NOT in desired state." -level debug
        $inputPSResourceList.ToJsonForTest()
        '["resources"]'
    }
}

function TestOperation {
    param(
        [string]$ResourceType
    )

    $inputObj = $stdinput | ConvertFrom-Json -ErrorAction Stop

    switch ($ResourceType) {
        'repository' {
            Write-Trace -level error -message "Test operation is not implemented for Repository resource."
            exit [ExitCode]::TestNotImplemented
        }
        'repositorylist' {
            Write-Trace -level error -message "Test operation is not implemented for RepositoryList resource."
            exit [ExitCode]::TestNotImplemented
        }
        'psresource' {
            Write-Trace -level error -message "Test operation is not implemented for PSResource resource."
            exit [ExitCode]::TestNotImplemented
        }
        'psresourcelist' {
            TestPSResourceList -inputObj $inputObj
        }

        default {
            Write-Trace -level error -message "Unknown ResourceType: $ResourceType"
            exit [ExitCode]::UnknownResourceType
        }
    }
}

function ExportOperation {
    switch ($ResourceType) {
        'repository' {
            $rep = Get-PSResourceRepository -ErrorAction SilentlyContinue

            if (-not $rep) {
                Write-Trace -message "No repositories found. Returning empty array." -level debug
                return @()
            }

            $rep | ForEach-Object {
                [Repository]::new(
                    $_.Name,
                    $_.Uri,
                    $_.Trusted,
                    $_.Priority,
                    $_.ApiVersion
                ).ToJson()
            }
        }

        'repositorylist' {
            Write-Trace -level error -message "Export operation is not implemented for RepositoryList resource."
            exit [ExitCode]::ExportNotImplemented
        }
        'psresource' {
            Write-Trace -level error -message "Export operation is not implemented for PSResource resource."
            exit [ExitCode]::ExportNotImplemented
        }
        'psresourcelist' {
            $currentUserPSResources = Get-PSResource
            $allUsersPSResources = Get-PSResource -Scope AllUsers
            PopulatePSResourceListObject -allUsersPSResources $allUsersPSResources -currentUserPSResources $currentUserPSResources
        }
        default {
            Write-Trace -level error -message "Unknown ResourceType: $ResourceType"
            exit [ExitCode]::UnknownResourceType
        }
    }
}

function SetPSResourceList {
    param(
        $inputObj
    )

    $repositoryName = $inputObj.repositoryName
    $resourcesToUninstall = @()
    $resourcesToInstall = [System.Collections.Generic.Dictionary[string, psobject]]::new()

    $resourcesChanged = $false

    $currentState = GetPSResourceList -inputObj $inputObj

    $inputObj.resources | ForEach-Object {
        $resourceDesiredState = ConvertInputToPSResource -inputObj $_ -repositoryName $repositoryName
        $name = $resourceDesiredState.name
        $version = $resourceDesiredState.version
        $scope = if ($resourceDesiredState.scope) { $resourceDesiredState.scope } else { "CurrentUser" }

        # Resource should not exist - uninstall if it does
        $currentState.resources | ForEach-Object {

            $isInDesiredState = $_.IsInDesiredState($resourceDesiredState)

            # Uninstall if resource should not exist but does
            if (-not $resourceDesiredState._exist -and $_._exist) {
                Write-Trace -message "Resource $($resourceDesiredState.name) exists but _exist is false. Adding to uninstall list." -level debug
                $resourcesToUninstall += $_
            }
            # Install if resource should exist but doesn't, or exists but not in desired state
            elseif ($resourceDesiredState._exist -and (-not $_._exist -or -not $isInDesiredState)) {
                Write-Trace -message "Resource $($resourceDesiredState.name) needs to be installed." -level debug
                $versionStr = if ($version) { $resourceDesiredState.version } else { 'latest' }
                $key = $name.ToLowerInvariant() + '-' + $versionStr.ToLowerInvariant()
                if (-not $resourcesToInstall.ContainsKey($key)) {
                    $resourcesToInstall[$key] = $resourceDesiredState
                }
            }
            # Otherwise resource is in desired state, no action needed
            else {
                Write-Trace -message "Resource $($resourceDesiredState.name) is in desired state." -level debug
            }
        }
    }

    if ($resourcesToUninstall.Count -gt 0) {
        Write-Trace -message "Uninstalling resources: $($resourcesToUninstall | ForEach-Object { "$($_.Name) - $($_.Version)" })" -level debug
        $resourcesToUninstall | ForEach-Object {
            Uninstall-PSResource -Name $_.Name -Scope $scope -ErrorAction Stop
        }
        $resourcesChanged = $true
    }

    if ($resourcesToInstall.Count -gt 0) {
        $psRepository = Get-PSResourceRepository -Name $repositoryName -ErrorAction SilentlyContinue

        if (-not $psRepository) {
            Write-Trace -level error -message "Repository '$repositoryName' not found. Cannot install resources."
            exit [ExitCode]::RepositoryNotFound
        }

        if (-not $psRepository.Trusted -and -not $inputObj.trustedRepository) {
            Write-Trace -level error -message "Repository '$repositoryName' is not trusted. Cannot install resources."
            exit [ExitCode]::RepositoryNotTrusted
        }

        Write-Trace -message "Installing resources: $($resourcesToInstall.Values | ForEach-Object { " $($_.Name) -- $($_.Version) " })" -level debug
        $resourcesToInstall.Values | ForEach-Object {
            $usePrerelease = if ($_.preRelease) { $true } else { $false }

            $installErrors = @()

            $name = $_.Name
            $version = $_.Version

            try {
                Install-PSResource -Name $_.Name -Version $_.Version -Scope $scope -Repository $repositoryName -ErrorAction Stop -TrustRepository:$inputObj.trustedRepository -Prerelease:$usePrerelease -Reinstall
            }
            catch {
                Write-Trace -level error -message "Failed to install resource '$name' with version '$version'. Error: $($_.Exception.Message)"
                $installErrors += $_.Exception.Message
            }

            if ($installErrors.Count -gt 0) {
                Write-Trace -level error -message "One or more errors occurred while installing resource '$name' with version '$version': $($installErrors -join '; ')"
                Write-Trace -level trace -message "Exiting with error code 4 due to installation failure."
                exit [ExitCode]::InstallationFailed
            }
        }

        $resourcesChanged = $true
    }

    (GetPSResourceList -inputObj $inputObj).ToJson()
    if ($resourcesChanged) {
        '["resources"]'
    }
    else {
        '[]'
    }
}

function SetOperation {
    param(
        [string]$ResourceType
    )

    $inputObj = $stdinput | ConvertFrom-Json -ErrorAction Stop

    switch ($ResourceType) {
        'repository' {
            $rep = Get-PSResourceRepository -Name $inputObj.Name -ErrorAction SilentlyContinue

            $properties = @('name', 'uri', 'trusted', 'priority', 'repositoryType')

            $splatt = @{}

            foreach ($property in $properties) {
                if ($null -ne $inputObj.PSObject.Properties[$property]) {
                    if ($property -eq 'repositoryType') {
                        $splatt['ApiVersion'] = $inputObj.$property
                    }
                    else {
                        $splatt[$property] = $inputObj.$property
                    }
                }
            }

            if ($null -eq $rep -and $inputObj._exist -ne $false) {
                Register-PSResourceRepository @splatt
            }
            else {
                if ($inputObj._exist -eq $false) {
                    Write-Trace -message "Repository $($inputObj.Name) exists and _exist is false. Deleting it." -level debug
                    Unregister-PSResourceRepository -Name $inputObj.Name
                }
                else {
                    Set-PSResourceRepository @splatt
                }
            }

            return GetOperation -ResourceType $ResourceType
        }

        'repositorylist' {
            Write-Trace -level error -message "Set operation is not implemented for RepositoryList resource."
            exit [ExitCode]::SetNotImplemented
        }
        'psresource' {
            Write-Trace -level error -message "Set operation is not implemented for PSResource resource."
            exit [ExitCode]::SetNotImplemented
        }
        'psresourcelist' { return SetPSResourceList -inputObj $inputObj }
        default {
            Write-Trace -level error -message "Unknown ResourceType: $ResourceType"
            exit [ExitCode]::UnknownResourceType
        }
    }
}

function DeleteOperation {
    param(
        [string]$ResourceType
    )

    $inputObj = $stdinput | ConvertFrom-Json -ErrorAction Stop
    switch ($ResourceType) {
        'repository' {
            if ($inputObj._exist -ne $false) {
                throw "_exist property is not set to false for the repository. Cannot delete."
            }

            $rep = Get-PSResourceRepository -Name $inputObj.Name -ErrorAction SilentlyContinue

            if ($null -ne $rep) {
                Unregister-PSResourceRepository -Name $inputObj.Name
            }
            else {
                Write-Trace -message "Repository not found: $($inputObj.Name). Nothing to delete." -level debug
            }

            return GetOperation -ResourceType $ResourceType
        }
        'repositorylist' {
            Write-Trace -level error -message "Delete operation is not implemented for RepositoryList resource."
            exit [ExitCode]::DeleteNotImplemented
        }
        'psresource' {
            Write-Trace -level error -message "Delete operation is not implemented for PSResource resource."
            exit [ExitCode]::DeleteNotImplemented
        }
        'psresourcelist' {
            Write-Trace -level error -message "Delete operation is not implemented for PSResourceList resource."
            exit [ExitCode]::DeleteNotImplemented
        }
        default {
            Write-Trace -level error -message "Unknown ResourceType: $ResourceType"
            exit [ExitCode]::UnknownResourceType
        }
    }
}

function PopulatePSResourceListObjectByRepository {
    param (
        $resourcesExist,
        $inputResources,
        $repositoryName,
        $trustedRepository
    )

    $resources = @()

    if (-not $resourcesExist) {
        $resources = $inputResources | ForEach-Object {
            [PSResource]::new(
                $_.Name
            )
        }
    }
    else {
        $resources += $resourcesExist | ForEach-Object {
            [PSResource]::new(
                $_.Name,
                $_.Version.PreRelease ? $_.Version.ToString() + "-" + $_.PreRelease : $_.Version.ToString(),
                $_.Scope,
                $_.RepositoryName,
                $_.PreRelease ? $true : $false
            )
        }
    }

    $psresourceListObj =
    [PSResourceList]::new(
        $repositoryName,
        $resources,
        $trustedRepository
    )

    return $psresourceListObj
}

function PopulatePSResourceListObject {
    param (
        $allUsersPSResources,
        $currentUserPSResources
    )

    $allPSResources = @()

    $allPSResources += $allUsersPSResources | ForEach-Object {
        return [PSResource]::new(
            $_.Name,
            $_.Version,
            [Scope]"AllUsers",
            $_.Repository,
            $_.PreRelease ? $true : $false
        )
    }

    $allPSResources += $currentUserPSResources | ForEach-Object {
        return [PSResource]::new(
            $_.Name,
            $_.Version,
            [Scope]"CurrentUser",
            $_.Repository,
            $_.PreRelease ? $true : $false
        )
    }

    $repoGrps = $allPSResources | Group-Object -Property repositoryName

    $repoGrps | ForEach-Object {
        $repositoryTrust = if ($_.Name) { (Get-PSResourceRepository -Name $_.Name -ErrorAction SilentlyContinue).Trusted } else { $false }
        $repoName = $_.Name
        $resources = $_.Group
        [PSResourceList]::new($repoName, $resources, $repositoryTrust).ToJson()
    }
}

## This is mostly needed for CI tests as the PSModulePath has a different version PSResourceGet
## If the module is loaded from a different path, then we get an error "Assembly with same name is already loaded"
if ($null -eq (Get-Module -Name Microsoft.PowerShell.PSResourceGet)) {
    $path = Join-Path -Path $PSScriptRoot -ChildPath "Microsoft.PowerShell.PSResourceGet.psd1"
    Write-Trace -level trace -message "Importing Microsoft.PowerShell.PSResourceGet module from path: $path"
    Import-Module -Name $path -Force -ErrorAction Stop
}

switch ($Operation.ToLower()) {
    'get' { return (GetOperation -ResourceType $ResourceType) }
    'set' { return (SetOperation -ResourceType $ResourceType) }
    'test' { return (TestOperation -ResourceType $ResourceType) }
    'export' { return (ExportOperation -ResourceType $ResourceType) }
    'delete' { return (DeleteOperation -ResourceType $ResourceType) }
    default {
        Write-Trace -level error -message "Unknown Operation: $Operation"
        exit [ExitCode]::UnknownOperation
    }
}

# SIG # Begin signature block
# MIInSQYJKoZIhvcNAQcCoIInOjCCJzYCAQExDzANBglghkgBZQMEAgEFADB5Bgor
# BgEEAYI3AgEEoGswaTA0BgorBgEEAYI3AgEeMCYCAwEAAAQQH8w7YFlLCE63JNLG
# KX7zUQIBAAIBAAIBAAIBAAIBADAxMA0GCWCGSAFlAwQCAQUABCAVk2uYnRfzQAcj
# oH4AMP5T734ZaSNhzm8aav6EXMRGL6CCDLowggX1MIID3aADAgECAhMzAAACHU0Z
# yE7XD1dIAAAAAAIdMA0GCSqGSIb3DQEBCwUAMFcxCzAJBgNVBAYTAlVTMR4wHAYD
# VQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKDAmBgNVBAMTH01pY3Jvc29mdCBD
# b2RlIFNpZ25pbmcgUENBIDIwMjQwHhcNMjYwNDE2MTg1OTQzWhcNMjcwNDE1MTg1
# OTQzWjB0MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQMA4GA1UE
# BxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMR4wHAYD
# VQQDExVNaWNyb3NvZnQgQ29ycG9yYXRpb24wggEiMA0GCSqGSIb3DQEBAQUAA4IB
# DwAwggEKAoIBAQDQvewXxx9gZZFC6Ys1WBay8BJ8kGA4JQnH5CMafqOASlTpK9H8
# o5ZXTXt0caVQTNMUPt445wXYD+dFtaKWTwDn1I52oUSrC9vJin1Gsqt+zyKJL5Dg
# 3eQXbQNR61DmMy20GLTIO3SFed9Rfi/ophgCLGFLDR3r0KvHjwMb/jYWS0celV/4
# Lz27LfAekm8v9E5IXaeiXbAUYZKK090n4CVl3JBtbN+9DtI9SNu/yjvozW52/u7R
# X/Ttpa/KDlpuokZ+Zcbvmtd9ur9gFLvZzh41o9MsE/clQtdaFWGvuo6Jua/ntpgk
# ey3E5/vBFe+MJPG6phdnuo6r57ZudCudiI1bAgMBAAGjggGbMIIBlzAOBgNVHQ8B
# Af8EBAMCB4AwHwYDVR0lBBgwFgYKKwYBBAGCN0wIAQYIKwYBBQUHAwMwHQYDVR0O
# BBYEFH6QuMwqcPG0hQlQ6c5jCtTTLrVeMEUGA1UdEQQ+MDykOjA4MR4wHAYDVQQL
# ExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xFjAUBgNVBAUTDTIzMDAxMis1MDc1NTkw
# HwYDVR0jBBgwFoAUf1k/VCHarU/vBeXmo9ctBpQSCDEwYAYDVR0fBFkwVzBVoFOg
# UYZPaHR0cDovL3d3dy5taWNyb3NvZnQuY29tL3BraW9wcy9jcmwvTWljcm9zb2Z0
# JTIwQ29kZSUyMFNpZ25pbmclMjBQQ0ElMjAyMDI0LmNybDBtBggrBgEFBQcBAQRh
# MF8wXQYIKwYBBQUHMAKGUWh0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMv
# Y2VydHMvTWljcm9zb2Z0JTIwQ29kZSUyMFNpZ25pbmclMjBQQ0ElMjAyMDI0LmNy
# dDAMBgNVHRMBAf8EAjAAMA0GCSqGSIb3DQEBCwUAA4ICAQBKTbYOjzwTG/DXGaz9
# s6+fQeaTtDcFmMY+5UyVFCyj7Pv+5i37qfX8lSL/tBIfYQfWsMuBQlfZurJD6r4H
# VJ2CeH+1fgiq8dcHdVKoZ3Sa2qXoX3cq9iS8cVb06B7+5/XJ7I0OxHH9fDsvJ3T3
# w5V/ZtAIFmLrl+P0CtG+92uzRsn0nTbdFjOkLMLWPLAU3THohKRlSEMgFJpPkm5n
# 5UAZ35xX6FWCrDLsSKb555bTifwa8mJBwdlof0bmfYidH+dxZ1FdDxvLnNl9zeKs
# A4kejaaIqqIPguhwAti5Ql7BlTNoJNwxCvBmqW2MQLnCkYN/VVUsR3V2x/rcTNzo
# Bf/Z/SpROvdaA2ZOOd1uioXJt3tdLQ7vHpqpib0KfWr/FWXW10q38VxfCnRQBqzb
# SuztR7nEMuzX7Ck+B/XaPDXd1qh72+QYyB0Z2VzWmO9zsnb9Uq/dwu8LGeQqnyu6
# 7SDGACvnXii2fb9+US492VTnXSnFKyqwgzUyFMtZK1/sHYTv6bG4TtQUygQxTN+Z
# V+aJIlKO2MqZ7bKrAnOzS9m6NgoTdWOq11bTOZwKlIEV/EhV9SWkDmdpR/hPPT2v
# 6TEj4F8PT/zHjRezIU5c/DGlt/VhY/pK0XkJtEyMmmS1BMtjU/rqBZVMIm3dnxQs
# /TBByr+Cf8Z1r7aifQVQ+WSqzjCCBr0wggSloAMCAQICEzMAAAA5O7Y3Gb8GHWcA
# AAAAADkwDQYJKoZIhvcNAQEMBQAwgYgxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpX
# YXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNyb3NvZnQg
# Q29ycG9yYXRpb24xMjAwBgNVBAMTKU1pY3Jvc29mdCBSb290IENlcnRpZmljYXRl
# IEF1dGhvcml0eSAyMDExMB4XDTI0MDgwODIwNTQxOFoXDTM2MDMyMjIyMTMwNFow
# VzELMAkGA1UEBhMCVVMxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEo
# MCYGA1UEAxMfTWljcm9zb2Z0IENvZGUgU2lnbmluZyBQQ0EgMjAyNDCCAiIwDQYJ
# KoZIhvcNAQEBBQADggIPADCCAgoCggIBANgBnB7jOMeqlRYHNa265v4IY9fH8TKh
# emHfPINe1gpLaV3dhg324WwH06LcHbpnsBukCDNitryo0dtS/EW6I/yEL/bLSY8h
# KpbfQuWusBPr9qazYcDxCW/qnjb5JsI1s8bNOg3bVATvQVL4tcf03aTycsz8QeCd
# M0l/yHRObJ9QqazM1r6VPEOJ7LL+uEEb73w6QCuhs89a1uv1zerOYMnsneRRwCbp
# yW11IcggU0cRKDDq1pjVJzIbIF6+oiXXbReOsgeI8zu1FyQfK0fVkaya8SmVHQ/t
# Of23mZ4W9k0Ri22QW9p3UgSC5OUDktKxxcCmGL6tXLfOGSWHIIV4YrTJTT6PNty5
# REojHJuZHArkF9VnHTERWoTjAzfI3kP+5b4alUdhgAZ7ttOu1bVnXfHaqPYl2rPs
# 20ji03LOVWsh/radgE17es5hL+t6lV0eVHrVhsssROWJuz2MXMCt7iw7lFPG9LXK
# Gjsmonn2gotGdHIuEg5JnJMJVmixd5LRlkmgYRZKzhxSCwyoGIq0PhaA7Y+VPct5
# pCHkijcIIDm0nlkK+0KyepolcqGm0T/GYQRMhHJlGOOmVQop36wUVUYklUy++vDW
# eEgEo4s7hxN6mIbf2MSIQ/iIfMZgJxC69oukMUXCrOC3SkE/xIkgpfl22MM1itkZ
# 35nNXkMolU1lAgMBAAGjggFOMIIBSjAOBgNVHQ8BAf8EBAMCAYYwEAYJKwYBBAGC
# NxUBBAMCAQAwHQYDVR0OBBYEFH9ZP1Qh2q1P7wXl5qPXLQaUEggxMBkGCSsGAQQB
# gjcUAgQMHgoAUwB1AGIAQwBBMA8GA1UdEwEB/wQFMAMBAf8wHwYDVR0jBBgwFoAU
# ci06AjGQQ7kUBU7h6qfHMdEjiTQwWgYDVR0fBFMwUTBPoE2gS4ZJaHR0cDovL2Ny
# bC5taWNyb3NvZnQuY29tL3BraS9jcmwvcHJvZHVjdHMvTWljUm9vQ2VyQXV0MjAx
# MV8yMDExXzAzXzIyLmNybDBeBggrBgEFBQcBAQRSMFAwTgYIKwYBBQUHMAKGQmh0
# dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2kvY2VydHMvTWljUm9vQ2VyQXV0MjAx
# MV8yMDExXzAzXzIyLmNydDANBgkqhkiG9w0BAQwFAAOCAgEAFJQfOChP7onn6fLI
# MKrSlN1WYKwDFgAddymOUO3FrM8d7B/W/iQ6DxXsDn7D5W4wMwYeLystcEqfkjz4
# NURRgazyMu5yRzQh4LqjA4tStTcJh1opExo7nn5PuPBYnbu0+THSuVHTe0VTTPVh
# ily/piFrDo3axQ9P4C+Ol5yet+2gTfekICS5xS+cYfSIvgn0JksVBVMYVI5QFu/q
# hnLhsEFEUzG8fvv0hjgkO+lkpV9ty6GkN4vdnd7ya6Q6aR9y34aiM1qmxaxBi6OU
# nyNl6fkuun/diTFnYDLTppOkr/mg5WSfCiDVMNCxtj4wPKC5OmHm1DQIt/MNokbb
# H3UGsFP1QbzsLocuSqLCvH09Io3fDPTmscR9Y75G4qX7RTX8AdBPo0I6OEojf39z
# uFZt0qOHm65YWQE69cZM2ueE1MB05dNNgHK9gTE7zKvK/fg8B2qjW88MT/WF5V5u
# vZGtqa9FSL2RazArA+rDPuf6JGYz4HpgMZHB4S6szWSKYBv0VisCzfxgeU+dquXW
# 9bd0auYlOB58DPcOYKdc3Se94g+xL4pcEhbB54JOgAkwYTu/9dLeH2pDqeJZAABV
# DWRQCaXfO5LgyKwKCLYXpigrZYCjUSBcr+Ve8PFWMhVTQl0v4q8J/AUmQN5W4n10
# 1cY2L4A7GTQG1h32HHAvfQESWP0xghnlMIIZ4QIBATBuMFcxCzAJBgNVBAYTAlVT
# MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKDAmBgNVBAMTH01pY3Jv
# c29mdCBDb2RlIFNpZ25pbmcgUENBIDIwMjQCEzMAAAIdTRnITtcPV0gAAAAAAh0w
# DQYJYIZIAWUDBAIBBQCgga4wGQYJKoZIhvcNAQkDMQwGCisGAQQBgjcCAQQwHAYK
# KwYBBAGCNwIBCzEOMAwGCisGAQQBgjcCARUwLwYJKoZIhvcNAQkEMSIEIEuPRvq2
# S2K0QFBjUSXm8gOg7WsD76o5Ju5oz4xDlHJDMEIGCisGAQQBgjcCAQwxNDAyoBSA
# EgBNAGkAYwByAG8AcwBvAGYAdKEagBhodHRwOi8vd3d3Lm1pY3Jvc29mdC5jb20w
# DQYJKoZIhvcNAQEBBQAEggEArFMcD6/WAnyOf2z7KVTnLaaWWz4im/F7AAf2pbr8
# bYRRzlV7nBwX0PJAi0mLY/gtiid2uXQJs5NdHTLSsGq1AI79GarGWB04zwfMGJHX
# jGPgkqsiPwpO05JhY+2RSeXP2wvXODJnjE9WzryvhqOj5iqM3b8URgRISohOnU1O
# D4Qh0LJUE2Rd/zr9fhOjkvuePsQsjGPNDXIsS4v8dj5j7johgIRHidBjdEU/WFXI
# gLTXiM1nRJUm8Djdh8fT0a32eA4WM8hNLMWvCquudNqbxyYkQfY991OuSpfptRk1
# Os6l12uW8gKLmF4Ml6ktWiKB5SKuxXA8GvpqN3OQIQbkDKGCF5cwgheTBgorBgEE
# AYI3AwMBMYIXgzCCF38GCSqGSIb3DQEHAqCCF3AwghdsAgEDMQ8wDQYJYIZIAWUD
# BAIBBQAwggFSBgsqhkiG9w0BCRABBKCCAUEEggE9MIIBOQIBAQYKKwYBBAGEWQoD
# ATAxMA0GCWCGSAFlAwQCAQUABCB9u8SOX6mLTzbqfhuHElmPuNmMKeZc7lSfzzdU
# yD23sQIGagz/kIj/GBMyMDI2MDUyMDE1MjEzNC43ODZaMASAAgH0oIHRpIHOMIHL
# MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQMA4GA1UEBxMHUmVk
# bW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMSUwIwYDVQQLExxN
# aWNyb3NvZnQgQW1lcmljYSBPcGVyYXRpb25zMScwJQYDVQQLEx5uU2hpZWxkIFRT
# UyBFU046RTAwMi0wNUUwLUQ5NDcxJTAjBgNVBAMTHE1pY3Jvc29mdCBUaW1lLVN0
# YW1wIFNlcnZpY2WgghHtMIIHIDCCBQigAwIBAgITMwAAAikO1WQqtJfyGgABAAAC
# KTANBgkqhkiG9w0BAQsFADB8MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGlu
# Z3RvbjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBv
# cmF0aW9uMSYwJAYDVQQDEx1NaWNyb3NvZnQgVGltZS1TdGFtcCBQQ0EgMjAxMDAe
# Fw0yNjAyMTkxOTQwMDdaFw0yNzA1MTcxOTQwMDdaMIHLMQswCQYDVQQGEwJVUzET
# MBEGA1UECBMKV2FzaGluZ3RvbjEQMA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMV
# TWljcm9zb2Z0IENvcnBvcmF0aW9uMSUwIwYDVQQLExxNaWNyb3NvZnQgQW1lcmlj
# YSBPcGVyYXRpb25zMScwJQYDVQQLEx5uU2hpZWxkIFRTUyBFU046RTAwMi0wNUUw
# LUQ5NDcxJTAjBgNVBAMTHE1pY3Jvc29mdCBUaW1lLVN0YW1wIFNlcnZpY2UwggIi
# MA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCeItFq4z1oCYSmUZmpYDsbJWEu
# ++1bbc/Mz7Pa3I0ZX5EON+WirB0FvnGlyFRUylzO5TJXZfU8QFPOU95P1Y1OZ8J+
# quA5G+AWSBOr/48scl0s9RBpqgTMq/lbyqBz4CMmvVR2QevAgVp4a1hbmOm9G7YW
# ey68N5F5rSDYV0wMlg4Iy8YRuFgRN2eBpVXt9IvFaFmBnQLZfo22KZ3L8PWEHUhX
# U5dLOSZoTfqqQ/B+deW56ACMnnHjPxZu+szHhZMLUrMWTgs9J7Cn8DtelcKj9aM+
# 0Zq7tkSDHCrwo6eCSfw3clktXRRrdmsccal8RCDiNFFgZsypwF2aGAF6kg41+Ql+
# thXpnOMUH4mPCAJZWp0zDWowsK/Yo5jHL1pT/AgbL3FoAy4cbhOI4Pb1eQFG+jT7
# skS2F/b+ZACUA1EDZ830K+Bu0yw+FpSGy8tpd1szk3cUYjIpzIG4z3oFNmiSJN8Y
# dNd4SHsER5Dks5bxiKbpvmfrOA39jTb7EW2TT7ySWgJISfvTezuLmQsTVSzNsvap
# VlHhE2zBqDw409nvOtitCFbnhhXNfatzb2+Gf2tX2s6YBa151CC/8+emJvvegXbW
# NudzYt8cFRom0PZ+fJRhhBfdSqCqr8QeOGJ8VYlmxFXqx1SdDSkTCSgpsskGqZwh
# /6umA1g4L7zeGBNngQIDAQABo4IBSTCCAUUwHQYDVR0OBBYEFCdNRaSL9AW8QvaQ
# 21WjRAXKN4M7MB8GA1UdIwQYMBaAFJ+nFV0AXmJdg/Tl0mWnG1M1GelyMF8GA1Ud
# HwRYMFYwVKBSoFCGTmh0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMvY3Js
# L01pY3Jvc29mdCUyMFRpbWUtU3RhbXAlMjBQQ0ElMjAyMDEwKDEpLmNybDBsBggr
# BgEFBQcBAQRgMF4wXAYIKwYBBQUHMAKGUGh0dHA6Ly93d3cubWljcm9zb2Z0LmNv
# bS9wa2lvcHMvY2VydHMvTWljcm9zb2Z0JTIwVGltZS1TdGFtcCUyMFBDQSUyMDIw
# MTAoMSkuY3J0MAwGA1UdEwEB/wQCMAAwFgYDVR0lAQH/BAwwCgYIKwYBBQUHAwgw
# DgYDVR0PAQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4ICAQA9wc72lf/czDhp09T3
# PGAMOQhxl/x04jpE7t39FeqQSn2Up6DVzhgwnzCqY3NIhLtUaWrd7NxvrhZDca+J
# 4xzvrRQNPHeRQpnJVeHsyTu53gTBlUB1TRI6OnZt/AVmR9oMJ/NBOqB+d+SOb8Px
# 6zRgRwk62sFkOkB5lig/DMnYEeR/amW9Hdo8vXcKmaa/DbSOAHSdfZFt+iqMZfNl
# kEOn71/RAKTNv4Qpq/2FhcjMMmSkIhshBdBVB0VjmkwFfhVUf5TTuLJ9sDR4EyCv
# OZJ3B6g7Iw6WjQxycjwkfzsVMTpfusJ5SwdOHL8yGPWZOePjwa8ISXWs6kiVK/6S
# 0/JVb1LpxpyYKREQjnU/5OecKt2OXlHdwFWZrwAi98RPZa6EExcb/LGLf10tNHju
# 1eTlohY0jzNZQ0BDgSuMZgMU+8EEjtMQMIDnlPGEUON7LHXHH0KL0FA01PEWVZKr
# r/LUOuuDTNFzw543FPMp4gkCIFlKdRuciR1IXOk+Xse6rj9tJFYgVn+44BHou2XQ
# e5RX30ef3AQWa0mxyGDqJzGsV3X5+bNQeMV88iWulJPq5sgnGG9O/H1/HH4HsO9Z
# KGX/WrJpQmFuQrTOR49XjveaC0xaFmGsNg+RhbtD5qTkn+ISDvw0IJ/E/VXNdz/y
# Wgol6r507hT8sAMupnhkF2uw1DCCB3EwggVZoAMCAQICEzMAAAAVxedrngKbSZkA
# AAAAABUwDQYJKoZIhvcNAQELBQAwgYgxCzAJBgNVBAYTAlVTMRMwEQYDVQQIEwpX
# YXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4wHAYDVQQKExVNaWNyb3NvZnQg
# Q29ycG9yYXRpb24xMjAwBgNVBAMTKU1pY3Jvc29mdCBSb290IENlcnRpZmljYXRl
# IEF1dGhvcml0eSAyMDEwMB4XDTIxMDkzMDE4MjIyNVoXDTMwMDkzMDE4MzIyNVow
# fDELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1Jl
# ZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEmMCQGA1UEAxMd
# TWljcm9zb2Z0IFRpbWUtU3RhbXAgUENBIDIwMTAwggIiMA0GCSqGSIb3DQEBAQUA
# A4ICDwAwggIKAoICAQDk4aZM57RyIQt5osvXJHm9DtWC0/3unAcH0qlsTnXIyjVX
# 9gF/bErg4r25PhdgM/9cT8dm95VTcVrifkpa/rg2Z4VGIwy1jRPPdzLAEBjoYH1q
# UoNEt6aORmsHFPPFdvWGUNzBRMhxXFExN6AKOG6N7dcP2CZTfDlhAnrEqv1yaa8d
# q6z2Nr41JmTamDu6GnszrYBbfowQHJ1S/rboYiXcag/PXfT+jlPP1uyFVk3v3byN
# pOORj7I5LFGc6XBpDco2LXCOMcg1KL3jtIckw+DJj361VI/c+gVVmG1oO5pGve2k
# rnopN6zL64NF50ZuyjLVwIYwXE8s4mKyzbnijYjklqwBSru+cakXW2dg3viSkR4d
# Pf0gz3N9QZpGdc3EXzTdEonW/aUgfX782Z5F37ZyL9t9X4C626p+Nuw2TPYrbqgS
# Uei/BQOj0XOmTTd0lBw0gg/wEPK3Rxjtp+iZfD9M269ewvPV2HM9Q07BMzlMjgK8
# QmguEOqEUUbi0b1qGFphAXPKZ6Je1yh2AuIzGHLXpyDwwvoSCtdjbwzJNmSLW6Cm
# gyFdXzB0kZSU2LlQ+QuJYfM2BjUYhEfb3BvR/bLUHMVr9lxSUV0S2yW6r1AFemzF
# ER1y7435UsSFF5PAPBXbGjfHCBUYP3irRbb1Hode2o+eFnJpxq57t7c+auIurQID
# AQABo4IB3TCCAdkwEgYJKwYBBAGCNxUBBAUCAwEAATAjBgkrBgEEAYI3FQIEFgQU
# KqdS/mTEmr6CkTxGNSnPEP8vBO4wHQYDVR0OBBYEFJ+nFV0AXmJdg/Tl0mWnG1M1
# GelyMFwGA1UdIARVMFMwUQYMKwYBBAGCN0yDfQEBMEEwPwYIKwYBBQUHAgEWM2h0
# dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMvRG9jcy9SZXBvc2l0b3J5Lmh0
# bTATBgNVHSUEDDAKBggrBgEFBQcDCDAZBgkrBgEEAYI3FAIEDB4KAFMAdQBiAEMA
# QTALBgNVHQ8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zAfBgNVHSMEGDAWgBTV9lbL
# j+iiXGJo0T2UkFvXzpoYxDBWBgNVHR8ETzBNMEugSaBHhkVodHRwOi8vY3JsLm1p
# Y3Jvc29mdC5jb20vcGtpL2NybC9wcm9kdWN0cy9NaWNSb29DZXJBdXRfMjAxMC0w
# Ni0yMy5jcmwwWgYIKwYBBQUHAQEETjBMMEoGCCsGAQUFBzAChj5odHRwOi8vd3d3
# Lm1pY3Jvc29mdC5jb20vcGtpL2NlcnRzL01pY1Jvb0NlckF1dF8yMDEwLTA2LTIz
# LmNydDANBgkqhkiG9w0BAQsFAAOCAgEAnVV9/Cqt4SwfZwExJFvhnnJL/Klv6lwU
# tj5OR2R4sQaTlz0xM7U518JxNj/aZGx80HU5bbsPMeTCj/ts0aGUGCLu6WZnOlNN
# 3Zi6th542DYunKmCVgADsAW+iehp4LoJ7nvfam++Kctu2D9IdQHZGN5tggz1bSNU
# 5HhTdSRXud2f8449xvNo32X2pFaq95W2KFUn0CS9QKC/GbYSEhFdPSfgQJY4rPf5
# KYnDvBewVIVCs/wMnosZiefwC2qBwoEZQhlSdYo2wh3DYXMuLGt7bj8sCXgU6ZGy
# qVvfSaN0DLzskYDSPeZKPmY7T7uG+jIa2Zb0j/aRAfbOxnT99kxybxCrdTDFNLB6
# 2FD+CljdQDzHVG2dY3RILLFORy3BFARxv2T5JL5zbcqOCb2zAVdJVGTZc9d/HltE
# AY5aGZFrDZ+kKNxnGSgkujhLmm77IVRrakURR6nxt67I6IleT53S0Ex2tVdUCbFp
# AUR+fKFhbHP+CrvsQWY9af3LwUFJfn6Tvsv4O+S3Fb+0zj6lMVGEvL8CwYKiexcd
# FYmNcP7ntdAoGokLjzbaukz5m/8K6TT4JDVnK+ANuOaMmdbhIurwJ0I9JZTmdHRb
# atGePu1+oDEzfbzL6Xu/OHBE0ZDxyKs6ijoIYn/ZcGNTTY3ugm2lBRDBcQZqELQd
# VTNYs6FwZvKhggNQMIICOAIBATCB+aGB0aSBzjCByzELMAkGA1UEBhMCVVMxEzAR
# BgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNVBAoTFU1p
# Y3Jvc29mdCBDb3Jwb3JhdGlvbjElMCMGA1UECxMcTWljcm9zb2Z0IEFtZXJpY2Eg
# T3BlcmF0aW9uczEnMCUGA1UECxMeblNoaWVsZCBUU1MgRVNOOkUwMDItMDVFMC1E
# OTQ3MSUwIwYDVQQDExxNaWNyb3NvZnQgVGltZS1TdGFtcCBTZXJ2aWNloiMKAQEw
# BwYFKw4DAhoDFQC3v9iSO22xob7ZxN5dXCEq+9Iv/6CBgzCBgKR+MHwxCzAJBgNV
# BAYTAlVTMRMwEQYDVQQIEwpXYXNoaW5ndG9uMRAwDgYDVQQHEwdSZWRtb25kMR4w
# HAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xJjAkBgNVBAMTHU1pY3Jvc29m
# dCBUaW1lLVN0YW1wIFBDQSAyMDEwMA0GCSqGSIb3DQEBCwUAAgUA7bgmsjAiGA8y
# MDI2MDUyMDEyMjUyMloYDzIwMjYwNTIxMTIyNTIyWjB3MD0GCisGAQQBhFkKBAEx
# LzAtMAoCBQDtuCayAgEAMAoCAQACAh6mAgH/MAcCAQACAhN0MAoCBQDtuXgyAgEA
# MDYGCisGAQQBhFkKBAIxKDAmMAwGCisGAQQBhFkKAwKgCjAIAgEAAgMHoSChCjAI
# AgEAAgMBhqAwDQYJKoZIhvcNAQELBQADggEBAJxHL1MALUHoRN+VBcARhX3mv0ZD
# JYPsV8a9RPkkSDLcvAeqdw/p6RSZyP+a7w2p3hP4/dPaWSoy1xMluxhiOPqntc8N
# jG506fkO90/d0JJ9laTwTw9UpaG9tDX42+NcGkWj6Ht14wcm84BpzA6jvBBlJJ0V
# fjLFWo/hrlXlrgH5dSAMzt90e4UMhbmS1yDjbsdMG+jS0M3OnJsVQ7oMc7A+nmb4
# wxjszb+/ia9H75a0VzNAx1MVPRMagz89cbTCNFgJgeJmaJfxEdXyfmnsAWfCJZpE
# agfqIK+/EaMaan+Cfr2XegcGMRa02yJ3R0VJMlN3UrX43+hNpOwKcGmtSUAxggQN
# MIIECQIBATCBkzB8MQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQ
# MA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9u
# MSYwJAYDVQQDEx1NaWNyb3NvZnQgVGltZS1TdGFtcCBQQ0EgMjAxMAITMwAAAikO
# 1WQqtJfyGgABAAACKTANBglghkgBZQMEAgEFAKCCAUowGgYJKoZIhvcNAQkDMQ0G
# CyqGSIb3DQEJEAEEMC8GCSqGSIb3DQEJBDEiBCBDuvw9y2wjJicwWSqKLzaNVuz+
# 0fqRPBqW7a69r2h7BjCB+gYLKoZIhvcNAQkQAi8xgeowgecwgeQwgb0EILfKPfEi
# tvD/lSvEumxqPkkeOEtgkmKFEVMuel9oOrqSMIGYMIGApH4wfDELMAkGA1UEBhMC
# VVMxEzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNV
# BAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEmMCQGA1UEAxMdTWljcm9zb2Z0IFRp
# bWUtU3RhbXAgUENBIDIwMTACEzMAAAIpDtVkKrSX8hoAAQAAAikwIgQgzmlhogvt
# fNK9ho0y1g7Ae7nShmKqn8Ax28XWFQcjHH8wDQYJKoZIhvcNAQELBQAEggIAZ6bl
# MMLcfRMpn24LShcBGT2VunUAmbkHvhelKaDMhXGFv+QFK4gf9+ChDcLpQ1j0l665
# gdRrmQHkMKRYkrM42H7yGxh/YGuM/0YF3NBSVOqHjnS56cxbGvPRGmJZ+30w+0em
# l9lIQiqim/W4S2DS8hic0Lu920g2jygD+cIP5bLUjUvTh5STIh+v6OA02zVmy53G
# hm4Kwc8u6dmp7G43zZkRKxvf1aPmNVbXEXavE2PXUKE9XtQT20dNw3vTVthEybfO
# /X7sjImWUjm2qED82AtLrr1B5KVKqHdKCf9tp+10JtLbrT9JJh4bDUNtsTmkdUyL
# WQ5KF8seqQfwPA5n8NhHXLisdxFUlgZPjs+Q+Xrp9mcIPIYKvE8XNy6eBzoIpjBz
# yhsY69+Z8JPBLd4pgJhls0NuA/So/MG0J3TZI0zVw/bKpyy4qJfdTN7j+D/7LJ2/
# Jg33jEWhCZ1ILfecWj7uFY6muIlp5SUpdodzql5aNm1nt+OByJzQR0wBUIfwx7xT
# OhL77Pwd7QKSyIBZ4Fv/vAertzX1ZXV69Qo7qLw+jNpQb1O1omWfpnXZxQbFT4sq
# 94iXaciyD0RrFtbeGg5W2X+OM3b4/7T8uaH+yXVwF1HCAq7Q+KKVHS5/0Ivnhs+i
# 1Yc++7kVi1bQtjHpImYIqQQKWDxJCTCuscKsugs=
# SIG # End signature block
