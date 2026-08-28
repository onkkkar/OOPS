(function(){
  var reduceMotion = window.matchMedia('(prefers-reduced-motion: reduce)').matches;

  // ---- Table of contents scrollspy ----
  var links = Array.prototype.slice.call(document.querySelectorAll('.toc a'));
  var map = links.map(function(a){
    var id = a.getAttribute('href').slice(1);
    var el = document.getElementById(id);
    return { a: a, el: el };
  }).filter(function(m){ return m.el; });

  if ('IntersectionObserver' in window && map.length){
    var tocObs = new IntersectionObserver(function(entries){
      entries.forEach(function(entry){
        var match = map.find(function(m){ return m.el === entry.target; });
        if (!match) return;
        if (entry.isIntersecting){
          links.forEach(function(l){ l.classList.remove('active'); });
          match.a.classList.add('active');
        }
      });
    }, { rootMargin: '-15% 0px -70% 0px', threshold: 0 });
    map.forEach(function(m){ tocObs.observe(m.el); });
  }

  // ---- Reading progress bar ----
  var bar = document.getElementById('progress-bar');
  function updateProgress(){
    if (!bar) return;
    var docHeight = document.documentElement.scrollHeight - window.innerHeight;
    var pct = docHeight > 0 ? (window.scrollY / docHeight) * 100 : 0;
    bar.style.width = pct + '%';
  }
  window.addEventListener('scroll', updateProgress, { passive: true });
  window.addEventListener('resize', updateProgress);
  updateProgress();

  // ---- Section permalinks (# appears on hover) ----
  document.querySelectorAll('.sec-head').forEach(function(sh){
    var section = sh.closest('section[id]');
    var h2 = sh.querySelector('h2');
    if (!section || !h2) return;
    var a = document.createElement('a');
    a.className = 'anchor-link';
    a.href = '#' + section.id;
    a.textContent = '#';
    a.setAttribute('aria-label', 'Link to this section');
    h2.appendChild(a);
  });
  document.querySelectorAll('section.sub[id] > h3').forEach(function(h3){
    var section = h3.closest('section.sub[id]');
    if (!section) return;
    var a = document.createElement('a');
    a.className = 'anchor-link';
    a.href = '#' + section.id;
    a.textContent = '#';
    a.setAttribute('aria-label', 'Link to this section');
    h3.appendChild(a);
  });

  // ---- Copy buttons on code blocks ----
  document.querySelectorAll('pre.code').forEach(function(pre){
    var btn = document.createElement('button');
    btn.type = 'button';
    btn.className = 'copy-btn';
    btn.textContent = 'Copy';
    btn.setAttribute('aria-label', 'Copy code');
    btn.addEventListener('click', function(){
      var text = pre.innerText.replace(/Copy$|Copied$/, '');
      var announce = function(){
        btn.textContent = 'Copied';
        btn.classList.add('copied');
        setTimeout(function(){ btn.textContent = 'Copy'; btn.classList.remove('copied'); }, 1500);
      };
      if (navigator.clipboard && navigator.clipboard.writeText){
        navigator.clipboard.writeText(text).then(announce).catch(function(){ fallbackCopy(text, announce); });
      } else {
        fallbackCopy(text, announce);
      }
    });
    pre.appendChild(btn);
  });

  function fallbackCopy(text, done){
    var ta = document.createElement('textarea');
    ta.value = text;
    ta.style.position = 'fixed';
    ta.style.opacity = '0';
    document.body.appendChild(ta);
    ta.select();
    try { document.execCommand('copy'); done(); } catch (e) { /* clipboard unavailable */ }
    document.body.removeChild(ta);
  }

  // ---- Estimated read time ----
  var rt = document.getElementById('read-time');
  if (rt){
    var main = document.querySelector('main');
    var words = main ? main.innerText.trim().split(/\s+/).length : 0;
    rt.textContent = '~' + Math.max(1, Math.round(words / 200)) + ' min';
  }

  // ---- Theme toggle (persists across visits) ----
  var root = document.documentElement;
  var stored = localStorage.getItem('oop-notes-theme');
  if (stored === 'light' || stored === 'dark') root.setAttribute('data-theme', stored);

  function currentTheme(){
    var attr = root.getAttribute('data-theme');
    if (attr) return attr;
    return window.matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light';
  }
  var themeBtn = document.getElementById('theme-toggle');
  if (themeBtn){
    var syncIcon = function(){ themeBtn.textContent = currentTheme() === 'dark' ? '☀' : '☾'; };
    syncIcon();
    themeBtn.addEventListener('click', function(){
      var next = currentTheme() === 'dark' ? 'light' : 'dark';
      root.setAttribute('data-theme', next);
      localStorage.setItem('oop-notes-theme', next);
      syncIcon();
    });
  }

  // ---- Width Mode toggle (Standard / Full Ultra-Wide) ----
  var widthBtn = document.getElementById('width-toggle');
  var isFullWidth = localStorage.getItem('oop-notes-width') === 'full';
  if (isFullWidth) document.body.classList.add('full-width');

  if (widthBtn){
    var syncWidthIcon = function(){
      var full = document.body.classList.contains('full-width');
      widthBtn.textContent = full ? '⊡' : '⊞';
      widthBtn.title = full ? 'Switch to standard reading width' : 'Expand to full screen width';
    };
    syncWidthIcon();
    widthBtn.addEventListener('click', function(){
      document.body.classList.toggle('full-width');
      var nowFull = document.body.classList.contains('full-width');
      localStorage.setItem('oop-notes-width', nowFull ? 'full' : 'standard');
      syncWidthIcon();
    });
  }

  // ---- Interactive Security Shield Highlight ----
  var publicPills = document.querySelectorAll('.interactive-public');
  var privateVaults = document.querySelectorAll('.interactive-private');
  var shieldBoundary = document.querySelector('.shield-boundary');

  if (publicPills && shieldBoundary) {
    publicPills.forEach(function(pill){
      pill.addEventListener('mouseenter', function(){
        shieldBoundary.classList.add('glow-public');
      });
      pill.addEventListener('mouseleave', function(){
        shieldBoundary.classList.remove('glow-public');
      });
    });
  }

  if (privateVaults && shieldBoundary) {
    privateVaults.forEach(function(vault){
      vault.addEventListener('mouseenter', function(){
        shieldBoundary.classList.add('glow-private');
      });
      vault.addEventListener('mouseleave', function(){
        shieldBoundary.classList.remove('glow-private');
      });
    });
  }


  // ---- Access Modifier Probe ----
  // Pick a specifier + a caller; render the verdict the compiler would give,
  // and light the matching row/cell in the access matrix.
  var probeWidget = document.getElementById('access-probe-widget');
  var probeVerdict = document.getElementById('probe-verdict');

  if (probeWidget && probeVerdict){
    var RULES = {
      'public|same':      [true,  'A class can always reach its own members, whatever their specifier.', 'cout << this->name;   // OK'],
      'public|derived':   [true,  'Public members are inherited as public, so the child reaches them directly.', 'cout << name;   // OK inside Car'],
      'public|outside':   [true,  'Public is the object\'s advertised interface - anyone holding the object can use it.', 'cout << s1.name;   // OK'],
      'protected|same':   [true,  'The declaring class always has full access to its own members.', 'cout << this->name;   // OK'],
      'protected|derived':[true,  'This is exactly what protected exists for: open to the family, closed to everyone else.', 'cout << name;   // OK inside Car'],
      'protected|outside':[false, 'Protected is private as far as the outside world is concerned. Expose it through a public getter instead.', 'cout << s1.name;   // ERROR: \'name\' is protected'],
      'private|same':     [true,  'Private means private to THIS class - inside it, access is unrestricted.', 'cout << this->gfName;   // OK'],
      'private|derived':  [false, 'Private members ARE inherited into the child object\'s memory, but the child has no permission to touch them. Only a public or protected method of the parent can hand the value over.', 'cout << gfName;   // ERROR: \'gfName\' is private'],
      'private|outside':  [false, 'The strongest seal: unreachable outside the declaring class. This is the core of data hiding.', 'cout << s1.gfName;   // ERROR: \'gfName\' is private']
    };
    var COL = { same: 1, derived: 2, outside: 3 };

    var curSpec = 'public', curWho = 'same';

    function probeRender(){
      var r = RULES[curSpec + '|' + curWho];
      probeVerdict.classList.toggle('allow', r[0]);
      probeVerdict.classList.toggle('deny', !r[0]);
      probeVerdict.querySelector('.pv-head').textContent = r[0] ? 'Allowed' : 'Blocked by the compiler';
      probeVerdict.querySelector('.pv-why').textContent = r[1];
      probeVerdict.querySelector('.pv-code').textContent = r[2];

      document.querySelectorAll('table.spec-table tr[data-row]').forEach(function(tr){
        var on = tr.getAttribute('data-row') === curSpec;
        tr.classList.toggle('row-lit', on);
        Array.prototype.slice.call(tr.children).forEach(function(td, i){
          td.classList.toggle('cell-lit', on && i === COL[curWho]);
        });
      });
    }

    probeWidget.querySelectorAll('[data-spec]').forEach(function(b){
      b.addEventListener('click', function(){
        curSpec = b.getAttribute('data-spec');
        probeWidget.querySelectorAll('[data-spec]').forEach(function(x){ x.classList.toggle('sel', x === b); });
        probeRender();
      });
    });
    probeWidget.querySelectorAll('[data-who]').forEach(function(b){
      b.addEventListener('click', function(){
        curWho = b.getAttribute('data-who');
        probeWidget.querySelectorAll('[data-who]').forEach(function(x){ x.classList.toggle('sel', x === b); });
        probeRender();
      });
    });

    probeRender();
  }

  // ---- Back to top ----
  var topBtn = document.getElementById('back-to-top');
  if (topBtn){
    window.addEventListener('scroll', function(){
      topBtn.classList.toggle('show', window.scrollY > 600);
    }, { passive: true });
    topBtn.addEventListener('click', function(){
      window.scrollTo({ top: 0, behavior: reduceMotion ? 'auto' : 'smooth' });
    });
  }
})();
