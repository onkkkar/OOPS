# Object-Oriented Programming in C++

Course notes, runnable code, and interactive visual notes - one folder per chapter, building one continuous narrative from "why OOP exists" through the classical pillars.

---

## 📚 Chapters

| # | Chapter | Covers | Notes | Visual | Code |
| :--- | :--- | :--- | :---: | :---: | :---: |
| 01 | **Intro to OOPS** | Functional programming and where it breaks down, real-world modelling, the container idea, classes and objects, attributes and behaviour | [Notes.md](Chapter%2001%20-%20Intro%20to%20OOPS/notes/Notes.md) | [Open](Chapter%2001%20-%20Intro%20to%20OOPS/notes/visual%20notes/index.html) | [1 file](Chapter%2001%20-%20Intro%20to%20OOPS/coding) |
| 02 | **Creating Objects** | Class blueprints, default and parameterised constructors, the `this` keyword, copy constructors, destructors, stack vs heap allocation, deep copy | [Notes.md](Chapter%2002%20-%20Creating%20Objects/notes/Notes.md) | [Open](Chapter%2002%20-%20Creating%20Objects/notes/visual%20notes/index.html) | [4 files](Chapter%2002%20-%20Creating%20Objects/coding) |
| 03 | **Encapsulation** | Data plus behaviour plus a security boundary, data hiding, the three access modifiers, perfect encapsulation, getters and setters | [Notes.md](Chapter%2003%20-%20Encapsulation/notes/Notes.md) | [Open](Chapter%2003%20-%20Encapsulation/notes/visual%20notes/index.html) | [2 files](Chapter%2003%20-%20Encapsulation/coding) |
| 04 | **Inheritance** | The IS-A relationship, base and derived classes, `public` inheritance mode, constructor and destructor chaining, `protected`, hierarchical extensibility | [Notes.md](Chapter%2004%20-%20Inheritance/notes/Notes.md) | [Open](Chapter%2004%20-%20Inheritance/notes/visual%20notes/index.html) | [4 files](Chapter%2004%20-%20Inheritance/coding) |

---

## 🗂 Repository Layout

```text
OOPS/
├── .agents/
│   └── rules/
│       └── workspace-rules.md      # Authoring standards for code, notes, and visual notes
├── README.md                       # This index
└── Chapter NN - <Topic>/
    ├── coding/                     # Numbered, runnable, compiling .cpp files
    └── notes/
        ├── Notes.md                # Chapter teaching notes (one continuous narrative)
        └── visual notes/           # Interactive web notes - open index.html directly
            ├── index.html
            ├── style.css
            └── script.js
```

---

## ▶️ Running the Code

Every `.cpp` file is standalone and compiles under C++17:

```bash
g++ -std=c++17 "Chapter 04 - Inheritance/coding/1. single-inheritance.cpp" -o run && ./run
```

> [!NOTE]
> The sources use `#include <bits/stdc++.h>`, which is a GCC/libstdc++ extension. On macOS the default `g++` is Apple clang and does **not** ship that header. Install real GCC (`brew install gcc`, then use `g++-14`), or place a shim `bits/stdc++.h` on the include path that pulls in `<iostream>`, `<string>`, and friends.

---

## 📖 Reading the Visual Notes

The visual notes have **zero build step** - double-click any `index.html` and it opens in the browser. Each page carries:

- **Theme toggle** (`☾` / `☀`) - light and dark, saved across visits and shared between chapters
- **Full-width toggle** (`⊞` / `⊡`) - expands to `98vw` on wide monitors
- **Reading progress bar** and **TOC scrollspy** that tracks the active section
- **Copy buttons** on every code block
- **Prev/next chapter navigation** at the foot of each page
- **Chapter-specific interactive diagrams** you operate rather than just read:
  - **Ch 01 - Parameter Ripple Simulator**: add one property, then fix each call site while the pending-edit counter drains
  - **Ch 02 - Shallow vs Deep Copy Simulator**: pick a copy strategy, copy, run both destructors, and watch the double free happen
  - **Ch 03 - Access Probe**: pick a specifier and a caller, get the compiler's actual verdict with the matrix row lit
  - **Ch 04 - Ctor/Dtor Chaining Player**: Step or Play through all six lifecycle stages with live program output

---

## 🧭 Roadmap

- [x] Chapter 01 - Intro to OOPS
- [x] Chapter 02 - Creating Objects
- [x] Chapter 03 - Encapsulation
- [x] Chapter 04 - Inheritance
- [ ] Chapter 05 - Polymorphism
- [ ] Chapter 06 - Abstraction
