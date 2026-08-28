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

  // ---- Interactive Inheritance Hierarchy ----
  // Hovering a derived card lights up the base class and the exact members
  // that child inherits, making the reuse relationship visible.
  var baseCard = document.querySelector('.base-card');
  var inheritLinks = document.querySelectorAll('.inherit-link');
  var derivedCards = document.querySelectorAll('.derived-card');
  var basePills = baseCard ? baseCard.querySelectorAll('.pill') : [];

  function setHierarchyLit(on){
    if (baseCard) baseCard.classList.toggle('lit', on);
    inheritLinks.forEach(function(l){ l.classList.toggle('lit', on); });
    basePills.forEach(function(pl){ pl.classList.toggle('flash', on); });
  }

  derivedCards.forEach(function(card){
    card.addEventListener('mouseenter', function(){ setHierarchyLit(true); });
    card.addEventListener('mouseleave', function(){ setHierarchyLit(false); });
  });

  if (baseCard){
    baseCard.addEventListener('mouseenter', function(){
      inheritLinks.forEach(function(l){ l.classList.add('lit'); });
      derivedCards.forEach(function(c){ c.classList.add('lit'); });
    });
    baseCard.addEventListener('mouseleave', function(){
      inheritLinks.forEach(function(l){ l.classList.remove('lit'); });
      derivedCards.forEach(function(c){ c.classList.remove('lit'); });
    });
  }

  // ---- Access Matrix Row Highlight ----
  // Hovering a specifier pill highlights its row in the access matrix table.
  document.querySelectorAll('[data-specifier]').forEach(function(trigger){
    var key = trigger.getAttribute('data-specifier');
    var row = document.querySelector('tr[data-row="' + key + '"]');
    if (!row) return;
    trigger.addEventListener('mouseenter', function(){ row.classList.add('row-lit'); });
    trigger.addEventListener('mouseleave', function(){ row.classList.remove('row-lit'); });
  });


  // ---- Constructor / Destructor Chaining Player ----
  // Steps through the real construction and destruction order of a Car object,
  // printing the exact lines the compiled program emits.
  var chainSteps  = Array.prototype.slice.call(document.querySelectorAll('.lifecycle-step[data-step]'));
  var chainStepBtn  = document.getElementById('chain-step');
  var chainPlayBtn  = document.getElementById('chain-play');
  var chainResetBtn = document.getElementById('chain-reset');
  var chainStatus   = document.getElementById('chain-status');
  var chainConsole  = document.getElementById('chain-console');

  if (chainSteps.length && chainStepBtn && chainConsole){
    var SCRIPT = [
      { out: 'Inside Vehicle ctor',            cls: 'base',    note: 'Base ctor runs FIRST - the foundation must exist before Car adds to it' },
      { out: 'Inside Car ctor',                cls: 'derived', note: 'Derived ctor body runs, and can already use name / model / numberOfTyres' },
      { out: null,                             cls: 'alive',   note: 'Object fully constructed - both halves initialised' },
      { out: 'Default Dtor Called for Car !!', cls: 'derived', note: 'Derived dtor runs FIRST - it may still need the parent data' },
      { out: 'dtor of Vehicle called !!',      cls: 'base',    note: 'Base dtor runs LAST - the foundation outlives the floors above it' },
      { out: null,                             cls: 'alive',   note: 'Memory released - construction order reversed exactly' }
    ];
    var chainAt = 0;
    var chainTimer = null;

    function chainRender(){
      chainSteps.forEach(function(el, i){
        el.classList.toggle('step-active', i === chainAt - 1);
        el.classList.toggle('step-done',   i < chainAt - 1);
      });
      var html = '<span class="console-label">Program output</span>';
      for (var i = 0; i < chainAt; i++){
        if (SCRIPT[i].out) html += '<span class="cline ' + SCRIPT[i].cls + '">' + SCRIPT[i].out + '</span>';
      }
      if (chainAt === 0){
        html += '<span class="cline" style="color:#64748B">(nothing yet - the object has not been created)</span>';
      } else if (SCRIPT[chainAt - 1].out === null){
        html += '<span class="cline ' + SCRIPT[chainAt - 1].cls + '">[ ' + (chainAt === 3 ? 'object alive' : 'memory released') + ' ]</span>';
      }
      chainConsole.innerHTML = html;
      if (chainStatus){
        chainStatus.textContent = chainAt === 0
          ? 'Not started - press Step to construct the object'
          : 'Step ' + chainAt + ' of ' + SCRIPT.length + ' - ' + SCRIPT[chainAt - 1].note;
      }
      chainStepBtn.disabled = chainAt >= SCRIPT.length;
      if (chainPlayBtn) chainPlayBtn.disabled = chainAt >= SCRIPT.length;
    }

    function chainAdvance(){
      if (chainAt < SCRIPT.length){ chainAt++; chainRender(); }
      return chainAt < SCRIPT.length;
    }

    function chainStop(){
      if (chainTimer){ clearInterval(chainTimer); chainTimer = null; }
    }

    chainStepBtn.addEventListener('click', function(){ chainStop(); chainAdvance(); });

    if (chainPlayBtn){
      chainPlayBtn.addEventListener('click', function(){
        chainStop();
        if (chainAt >= SCRIPT.length) return;
        if (reduceMotion){ while (chainAdvance()){} chainRender(); return; }
        chainTimer = setInterval(function(){ if (!chainAdvance()) chainStop(); }, 900);
      });
    }

    if (chainResetBtn){
      chainResetBtn.addEventListener('click', function(){ chainStop(); chainAt = 0; chainRender(); });
    }

    chainRender();
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
