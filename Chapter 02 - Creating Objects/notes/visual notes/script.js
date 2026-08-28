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

  // ---- Interactive Blueprint & Instance Highlight ----
  var bpCards = document.querySelectorAll('.blueprint-card');
  var instCards = document.querySelectorAll('.instance-card');
  bpCards.forEach(function(bp){
    bp.addEventListener('mouseenter', function(){
      instCards.forEach(function(ic){ ic.classList.add('highlighted'); });
    });
    bp.addEventListener('mouseleave', function(){
      instCards.forEach(function(ic){ ic.classList.remove('highlighted'); });
    });
  });


  // ---- Shallow vs Deep Copy Simulator ----
  // Copy s3 into s4 under either strategy, then run both destructors and see
  // whether the heap float is freed once (deep) or twice (shallow).
  var simRoot = document.getElementById('copy-sim');
  if (simRoot){
    var simMode    = 'shallow';
    var simCopied  = false;
    var simDone    = false;
    var s4      = document.getElementById('sim-s4');
    var heap1   = document.getElementById('sim-heap1');
    var heap1sub= document.getElementById('sim-heap1-sub');
    var heap2   = document.getElementById('sim-heap2');
    var verdict = document.getElementById('sim-verdict');
    var log     = document.getElementById('sim-log');
    var btnCopy = document.getElementById('sim-copy');
    var btnDest = document.getElementById('sim-destroy');
    var btnReset= document.getElementById('sim-reset');

    function simLog(lines){
      log.innerHTML = lines.length
        ? lines.map(function(l){ return '<span class="sl ' + l[1] + '">' + l[0] + '</span>'; }).join('')
        : '<span class="sl dim">(no output yet)</span>';
    }

    function simReset(){
      simCopied = false; simDone = false;
      s4.style.visibility = 'hidden';
      heap2.style.visibility = 'hidden';
      heap1.classList.remove('freed','double-freed');
      heap2.classList.remove('freed','double-freed');
      heap1sub.textContent = 'owned by s3';
      verdict.className = 'sim-verdict';
      verdict.textContent = 'Two objects, one pointer attribute. Pick a copy strategy above, then copy and destroy - and watch what happens to the heap.';
      btnCopy.disabled = false; btnDest.disabled = true;
      simLog([]);
    }

    function simCopy(){
      simCopied = true;
      s4.style.visibility = 'visible';
      btnCopy.disabled = true; btnDest.disabled = false;
      if (simMode === 'shallow'){
        heap1sub.textContent = 'owned by s3 AND s4';
        verdict.className = 'sim-verdict bad';
        verdict.innerHTML = '<strong>Shallow copy done.</strong> Only the <em>address</em> was copied, so <code>s3.gpa</code> and <code>s4.gpa</code> now point at the same float. Two owners, one allocation.';
        simLog([['Student s4(s3);   // copy ctor runs','dim'],
                ['s4.gpa = s3.gpa   -> both hold the SAME address','warn']]);
      } else {
        heap2.style.visibility = 'visible';
        heap1sub.textContent = 'owned by s3';
        verdict.className = 'sim-verdict ok';
        verdict.innerHTML = '<strong>Deep copy done.</strong> A fresh float was allocated and the <em>value</em> copied into it. Each object owns its own memory.';
        simLog([['Student s4(s3);   // copy ctor runs','dim'],
                ['s4.gpa = new float(*s3.gpa)   -> separate allocation','good']]);
      }
    }

    function simDestroy(){
      simDone = true; btnDest.disabled = true;
      if (simMode === 'shallow'){
        heap1.classList.add('double-freed');
        verdict.className = 'sim-verdict bad';
        verdict.innerHTML = '<strong>Double free - undefined behaviour.</strong> s4’s destructor deleted the float, then s3’s destructor deleted the very same address again. This is the crash the deep copy exists to prevent.';
        simLog([['~Student()   // s4 destroyed first (created last)','dim'],
                ['delete s4.gpa;   -> float freed','good'],
                ['~Student()   // s3 destroyed','dim'],
                ['delete s3.gpa;   -> SAME address freed AGAIN','warn'],
                ['*** undefined behaviour: double free ***','warn']]);
      } else {
        heap1.classList.add('freed');
        heap2.classList.add('freed');
        verdict.className = 'sim-verdict ok';
        verdict.innerHTML = '<strong>Clean teardown.</strong> Each destructor freed exactly the allocation its own object owned. No leak, no double free.';
        simLog([['~Student()   // s4 destroyed first (created last)','dim'],
                ['delete s4.gpa;   -> float #2 freed','good'],
                ['~Student()   // s3 destroyed','dim'],
                ['delete s3.gpa;   -> float #1 freed','good'],
                ['*** both objects released cleanly ***','good']]);
      }
    }

    simRoot.querySelectorAll('[data-mode]').forEach(function(b){
      b.addEventListener('click', function(){
        simMode = b.getAttribute('data-mode');
        simRoot.querySelectorAll('[data-mode]').forEach(function(x){ x.classList.toggle('sel', x === b); });
        simReset();
      });
    });
    btnCopy.addEventListener('click', simCopy);
    btnDest.addEventListener('click', simDestroy);
    btnReset.addEventListener('click', simReset);
    simReset();
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
