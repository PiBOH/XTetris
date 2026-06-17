/* ===========================================================
   XTetris · GitHub Pages script
   ===========================================================
   - Fetches the raw README.md from the repo and renders it as
     sanitized HTML, preserving badges, code blocks and headings.
   - Fetches the latest release tag from the GitHub API and
     updates every [data-version] / [data-download-filename] /
     [data-download-url] placeholder on the page.
   - Fetches the CHANGELOG.md for the changelog section.
   - Handles the "copy" buttons on code snippets.
   =========================================================== */

(function () {
  'use strict';

  const REPO           = 'PiBOH/XTetris';
  const BRANCH         = 'main';
  const README_URL     = `https://raw.githubusercontent.com/${REPO}/${BRANCH}/README.md`;
  const CHANGELOG_URL  = `https://raw.githubusercontent.com/${REPO}/${BRANCH}/CHANGELOG.md`;
  const RELEASE_API    = `https://api.github.com/repos/${REPO}/releases/latest`;
  const RELEASE_DL_TPL = `https://github.com/${REPO}/releases/latest/download/XTetris.zip`;

  // -------- tiny markdown renderer (intentionally minimal) -----
  function escapeHtml(s) {
    return s
      .replace(/&/g, '&amp;')
      .replace(/</g, '&lt;')
      .replace(/>/g, '&gt;')
      .replace(/"/g, '&quot;')
      .replace(/'/g, '&#39;');
  }

  function inlineFormat(text) {
    // images
    text = text.replace(/!\[([^\]]*)\]\(([^)\s]+)(?:\s+"([^"]*)")?\)/g,
      (_, alt, src, title) => {
        const t = title ? ` title="${escapeHtml(title)}"` : '';
        return `<img src="${escapeHtml(src)}" alt="${escapeHtml(alt)}" loading="lazy" decoding="async"${t}>`;
      });
    // links
    text = text.replace(/\[([^\]]+)\]\(([^)\s]+)(?:\s+"([^"]*)")?\)/g,
      (_, label, href, title) => {
        const t = title ? ` title="${escapeHtml(title)}"` : '';
        const ext = /^https?:\/\//i.test(href) ? ' target="_blank" rel="noopener"' : '';
        return `<a href="${escapeHtml(href)}"${t}${ext}>${inlineFormat(label)}</a>`;
      });
    // bold
    text = text.replace(/\*\*([^*]+)\*\*/g, '<strong>$1</strong>');
    // italic
    text = text.replace(/\*([^*]+)\*/g, '<em>$1</em>');
    // inline code
    text = text.replace(/`([^`]+)`/g, '<code>$1</code>');
    return text;
  }

  function renderMarkdown(md) {
    const lines = md.replace(/\r\n?/g, '\n').split('\n');
    const out = [];
    let i = 0;

    const flushParagraph = (buf) => {
      if (!buf.length) return;
      out.push('<p>' + inlineFormat(buf.join(' ')) + '</p>');
      buf.length = 0;
    };

    const paragraphBuf = [];

    while (i < lines.length) {
      const line = lines[i];

      // fenced code block
      if (/^```/.test(line)) {
        flushParagraph(paragraphBuf);
        const lang = line.slice(3).trim();
        const code = [];
        i++;
        while (i < lines.length && !/^```/.test(lines[i])) {
          code.push(lines[i]);
          i++;
        }
        i++; // skip closing fence
        const cls = lang ? ` class="language-${escapeHtml(lang)}"` : '';
        out.push(`<pre><code${cls}>${escapeHtml(code.join('\n'))}</code></pre>`);
        continue;
      }

      // heading
      const h = /^(#{1,6})\s+(.*)$/.exec(line);
      if (h) {
        flushParagraph(paragraphBuf);
        const level = h[1].length;
        const text  = inlineFormat(h[2].trim());
        out.push(`<h${level}>${text}</h${level}>`);
        i++;
        continue;
      }

      // horizontal rule
      if (/^-{3,}\s*$/.test(line) || /^\*{3,}\s*$/.test(line)) {
        flushParagraph(paragraphBuf);
        out.push('<hr/>');
        i++;
        continue;
      }

      // blockquote
      if (/^>\s?/.test(line)) {
        flushParagraph(paragraphBuf);
        const bq = [];
        while (i < lines.length && /^>\s?/.test(lines[i])) {
          bq.push(lines[i].replace(/^>\s?/, ''));
          i++;
        }
        out.push('<blockquote>' + inlineFormat(bq.join(' ')) + '</blockquote>');
        continue;
      }

      // unordered list
      if (/^[-*]\s+/.test(line)) {
        flushParagraph(paragraphBuf);
        const items = [];
        while (i < lines.length && /^[-*]\s+/.test(lines[i])) {
          items.push(lines[i].replace(/^[-*]\s+/, ''));
          i++;
        }
        out.push('<ul>' + items.map(t => '<li>' + inlineFormat(t) + '</li>').join('') + '</ul>');
        continue;
      }

      // ordered list
      if (/^\d+\.\s+/.test(line)) {
        flushParagraph(paragraphBuf);
        const items = [];
        while (i < lines.length && /^\d+\.\s+/.test(lines[i])) {
          items.push(lines[i].replace(/^\d+\.\s+/, ''));
          i++;
        }
        out.push('<ol>' + items.map(t => '<li>' + inlineFormat(t) + '</li>').join('') + '</ol>');
        continue;
      }

      // table (very basic GFM)
      if (/^\|/.test(line) && i + 1 < lines.length && /^\|[\s:-]+\|/.test(lines[i + 1])) {
        flushParagraph(paragraphBuf);
        const header = lines[i].split('|').slice(1, -1).map(s => s.trim());
        i += 2; // skip header + separator
        const rows = [];
        while (i < lines.length && /^\|/.test(lines[i])) {
          rows.push(lines[i].split('|').slice(1, -1).map(s => s.trim()));
          i++;
        }
        let html = '<table><thead><tr>';
        header.forEach(h => { html += `<th>${inlineFormat(h)}</th>`; });
        html += '</tr></thead><tbody>';
        rows.forEach(r => {
          html += '<tr>';
          r.forEach(c => { html += `<td>${inlineFormat(c)}</td>`; });
          html += '</tr>';
        });
        html += '</tbody></table>';
        out.push(html);
        continue;
      }

      // blank line
      if (!line.trim()) {
        flushParagraph(paragraphBuf);
        i++;
        continue;
      }

      // paragraph
      paragraphBuf.push(line.trim());
      i++;
    }
    flushParagraph(paragraphBuf);
    return out.join('\n');
  }

  // ---------- fetch & render helpers ----------
  async function loadText(url, accept) {
    const opts = accept ? { headers: { 'Accept': accept } } : {};
    const res = await fetch(url, { cache: 'no-store', ...opts });
    if (!res.ok) throw new Error(`HTTP ${res.status} su ${url}`);
    return await res.text();
  }

  async function loadJson(url) {
    const res = await fetch(url, {
      cache: 'no-store',
      headers: { 'Accept': 'application/vnd.github+json' }
    });
    if (!res.ok) throw new Error(`HTTP ${res.status} su ${url}`);
    return await res.json();
  }

  // ---------- latest release / version ----------
  async function fetchLatestRelease() {
    try {
      const data = await loadJson(RELEASE_API);
      let tag = (data.tag_name || '').toString();
      // Strip a leading "v" / "V" so "v3.0.45" -> "3.0.45"
      tag = tag.replace(/^v/i, '');
      return {
        tag: tag,
        name: data.name || tag,
        url: data.html_url,
        assets: (data.assets || []).map(a => ({
          name: a.name,
          url: a.browser_download_url
        }))
      };
    } catch (err) {
      console.warn('[XTetris] impossibile recuperare la versione:', err.message);
      return null;
    }
  }

  function applyVersionToPage(info) {
    const tag = info ? info.tag : 'latest';

    // 1) Replace every [data-version] with the tag
    document.querySelectorAll('[data-version]').forEach(el => {
      el.textContent = tag;
      el.removeAttribute('data-version'); // avoid double-update
    });

    // 2) Replace every [data-download-url] with the canonical
    //    "always-latest" download URL on GitHub Releases
    document.querySelectorAll('[data-download-url]').forEach(el => {
      const href = RELEASE_DL_TPL;
      if (el.tagName === 'A') el.setAttribute('href', href);
      else el.textContent = href;
      el.removeAttribute('data-download-url');
    });

    // 3) Replace every [data-download-filename] with the suggested filename
    document.querySelectorAll('[data-download-filename]').forEach(el => {
      el.textContent = `XTetris_${tag}.zip`;
      el.removeAttribute('data-download-filename');
    });

    // 4) Update the page <title> with the tag, if a [data-title-version] marker exists
    const titleSlot = document.querySelector('[data-title-version]');
    if (titleSlot) {
      document.title = document.title.replace(/\[VERSION\]|\{VERSION\}/, tag);
      titleSlot.removeAttribute('data-title-version');
    }

    // 5) Show a hidden status banner only when we couldn't fetch
    const banner = document.getElementById('version-banner');
    if (banner) {
      banner.hidden = !!info;
    }
  }

  async function fillReadme() {
    const target = document.getElementById('readme-content');
    if (!target) return;
    try {
      const md  = await loadText(README_URL);
      const html = renderMarkdown(md);
      target.innerHTML = html;
    } catch (err) {
      target.innerHTML =
        `<p style="color:#f0a000">⚠ Impossibile caricare il README dal repository GitHub.</p>
         <p>Controlla la connessione oppure apri direttamente
         <a href="https://github.com/${REPO}#readme" target="_blank" rel="noopener">github.com/${REPO}</a>.</p>
         <p style="color:#9da7b3;font-size:.85em">Dettagli: ${escapeHtml(err.message)}</p>`;
    }
  }

  async function fillChangelog() {
    const target = document.getElementById('changelog-content');
    if (!target) return;
    try {
      const md  = await loadText(CHANGELOG_URL);
      // Show only first ~400 lines to keep the page light
      const trimmed = md.split('\n').slice(0, 400).join('\n');
      target.innerHTML = renderMarkdown(trimmed);
    } catch (err) {
      target.innerHTML =
        `<p style="color:#f0a000">⚠ Impossibile caricare il changelog.</p>
         <p style="color:#9da7b3;font-size:.85em">${escapeHtml(err.message)}</p>`;
    }
  }

  // ---------- copy buttons ----------
  function bindCopyButtons() {
    document.querySelectorAll('.copy-btn').forEach(btn => {
      btn.addEventListener('click', async () => {
        const text = btn.dataset.copy || '';
        try {
          await navigator.clipboard.writeText(text);
          const original = btn.textContent;
          btn.textContent = '✓ Copiato';
          btn.classList.add('copied');
          setTimeout(() => {
            btn.textContent = original;
            btn.classList.remove('copied');
          }, 1500);
        } catch {
          btn.textContent = 'Errore';
          setTimeout(() => (btn.textContent = 'Copia'), 1500);
        }
      });
    });
  }

  // ---------- boot ----------
  document.addEventListener('DOMContentLoaded', () => {
    bindCopyButtons();

    // Version + download URLs come from the GitHub API
    fetchLatestRelease().then(applyVersionToPage);

    // README + changelog come from raw.githubusercontent.com
    fillReadme();
    fillChangelog();
  });
})();
