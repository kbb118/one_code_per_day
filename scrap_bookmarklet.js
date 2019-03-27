// コピペしてブックマークのURL欄に入れれば使えます。
javascript: (function() {
    var title = window.prompt('Scrap "Scrapbox" to kbbkbb524&#39;s project.', document.title);
    if (!title) return;
    var lines = ['', '[' + window.location.href + ' ' + document.title + ']'];
    var quote = window.getSelection().toString();
    if (quote.trim()) lines = lines.concat(quote.split(/\n/g).map(function(line) {
        return ' > ' + line
    }));
    lines.push('');
    lines.push('[hr.icon]')
    lines.push('[scrapped by bookmarklet]');
    var body = encodeURIComponent(lines.join('\n'));
    window.open('https://scrapbox.io/kbbkbb524/' + encodeURIComponent(title.trim()) + '?body=' + body)
})();