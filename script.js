/* ===========================================================
   XTetris · GitHub Pages script
   ===========================================================
   - Fetches the raw README.md from the repo and renders it as
     sanitized HTML, preserving badges, code blocks and headings.
   - Fetches the CHANGELOG.md for the changelog section.
   - Handles the "copy" buttons on code snippets.
   =========================================================== */

(function () {
  'use strict';

  const REPO   = 'PiBOH/XTetris';
  const BRANCH = 'main';
  const README_URL    = `https://raw.githubusercontent.com/${REPO}/${BRANCH}/README.md`;
  const CHANGELOG_URL = `https://raw.githubusercontent.com/${REPO}/${BRANCH}/CHANGELOG.md`;

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
        return `<img src="${escapeHtml(src)}" alt="${escapeHtml(alt)}" loading="lazy"${t}>`;
      });
    // links
    text = text.replace(/\[([^\]]+)\]\(([^)\s]+)(?:\s+"([^"]*)")?\)/g,
      (_, label, href, title) => {
        const t = title ? ` title="${escapeHtml(title)}"` : '';
        const ext = /^https?:\/\//i.test(href) ? ' target="_blank" rel="noopener"' : '';
        return `<a href="${escapeHtml(href)}"${t}${ext}>${escapeHtml(label)}</a>`;
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
  async function loadMarkdown(url) {
    const res = await fetch(url, { cache: 'no-store' });
    if (!res.ok) throw new Error(`HTTP ${res.status}`);
    return await res.text();
  }

  async function fillReadme() {
    const target = document.getElementById('readme-content');
    if (!target) return;
    try {
      const md  = await loadMarkdown(README_URL);
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
      const md  = await loadMarkdown(CHANGELOG_URL);
      // Show only first ~30 entries (roughly) to keep page light
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
    fillReadme();
    fillChangelog();
  });
})();
