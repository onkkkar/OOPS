# Workspace Master Rules

This is the primary rules file loaded into the agent's memory for this workspace. It defines the absolute standards for writing C++ code, Markdown teaching notes, and visual web notes.

---

## 1. Repository Structure

```text
OOPS/
├── .agents/
│   └── rules/
│       └── workspace-rules.md     # Primary memory rules (this file)
├── README.md                      # Root index: chapter table, layout, how to run
├── Chapter NN - <Topic>/
│   ├── coding/                    # Runnable, clean, compiling .cpp source files
│   └── notes/
│       ├── Notes.md                # Chapter teaching notes telling one continuous narrative
│       └── visual notes/           # Interactive, beautifully styled web notes (HTML/CSS/JS)
```

- **Chapter Folder Naming**:
  - Always **zero-pad** the chapter number to two digits: `Chapter 04 - Inheritance`, never `Chapter 4 - Inheritance`. Unpadded numbers sort incorrectly once the course passes Chapter 09.
  - Spell the topic correctly and in full. Rename with `git mv` so history is preserved.
- **Root README Maintenance**:
  - Every new chapter **must** be added to the `README.md` chapter table (notes link, visual notes link, coding link, and a one-line "Covers" summary) and ticked off in the Roadmap section.

---

## 2. Writing C++ Code (`.cpp` files in `coding/`)

- **Strict Compilation Requirement**:
  - Every single example file must compile cleanly without errors (`g++ -std=c++17 -fsyntax-only <file>`).
  - Even when creating deliberately flawed, anti-pattern, or "bad design" examples (e.g. showcasing loose variables, global state pollution, parallel arrays), the code must remain **syntactically valid C++**. Bad design means poor architecture, not broken syntax.
- **Short, Meaningful Comments**:
  - Keep comments short, single-line, and placed only where a conceptual detail is non-obvious.
  - Avoid redundant comments, boilerplate filler, or comment blocks for self-evident code lines.
- **Consolidated, Topic-Focused Files**:
  - Consolidate related code variations into structured, well-named files (e.g., `1. functional-programming.cpp`, `2. class-and-object.cpp`) rather than scattering dozens of 5-line files.
- **Scoped Data by Default**:
  - Keep instance data strictly scoped to where it is used (e.g., local variables inside `main()` or member variables inside a `class`/`struct`).
  - Use global variables **only** when specifically demonstrating the dangers of global state leakage.
- **Numbered Ordering**:
  - Prefix ordered example files with sequential numbers (e.g., `1. functional-programming.cpp`, `2. student-class.cpp`) to preserve the learning narrative.
  - Filenames must be **descriptive of the concept taught**, never generic (`coding2.cpp`, `test.cpp` are forbidden).

### 2.1 Standard Comment Decoration

Every `.cpp` file follows the same three-tier comment skeleton so all chapters read identically:

```cpp
// =========================================================================
// <Concept Title>: <one-line framing of what this file demonstrates>
// =========================================================================
// <2-4 lines explaining the idea, the rule being shown, or the trap being
// avoided. This is the only prose block in the file.>
// =========================================================================
class Student
{
    // ---------------- <Member Group> ----------------
    // <optional single-line note on why this group is grouped this way>
    int id;

public:
    // ---------------- Constructor (ctor) ----------------
    Student() { }

    // ---------------- Destructor (dtor) ----------------
    ~Student() { }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- <Numbered Step> ----------------
    return 0;
}
```

- **Banner comments** (`// ====`) mark file-level and class-level boundaries.
- **Divider comments** (`// ---- X ----`) mark member groups and `main()` steps.
- **Indentation is 4 spaces**, uniformly, in every chapter.
- **Illustrating a compiler error**: comment out the offending line and state the exact error inline, e.g. `// cout << A.name;   // COMPILATION ERROR: 'name' is protected`.
- **Preserve the user's voice**: output strings written by the user (including Hinglish, e.g. `"Wheelie karri hai "`) are kept **verbatim**. Only comments are polished.

---

## 3. Writing Teaching Notes (`Notes.md`)

- **Strict Zero-Omission Rule**:
  - When cleaning up, formatting, or enhancing user-written notes, **NEVER exclude, remove, or skip** anything written by the user.
  - All user thoughts, concepts, analogies (e.g. Sparrow/Bird, Rahul/Aman/Simran, Fortuner/WagonR, Car/Bike/Vehicle), definitions, and points **MUST remain intact**.
  - Polish clarity, improve grammar, expand explanations, and format cleanly, but **never delete original points or examples**.
- **Visual ASCII Architecture Diagrams**:
  - Use structured ASCII box diagrams and clear visual flowcharts to illustrate:
    - Class vs. Object relationships, blueprints, and container memory layouts.
    - Architectural comparisons (e.g. flat procedural file layout vs. encapsulated OOP boundaries; duplicated sibling classes vs. a shared base class).
    - Failure modes and antipatterns (e.g. global data contamination, parameter ripple effects, copy-paste duplication across sibling classes).
    - Lifecycle and ordering (e.g. constructor chaining down, destructor chaining up).
- **Navigation & Structure**:
  - Include a **📌 Table of Contents** at the top with clickable anchor links matching exact heading IDs.
  - Maintain a clean hierarchy with Markdown headings (`#`, `##`, `###`, `####`) telling one continuous story.
  - Distinguish narrative statements from sub-headings (e.g. *Real-World Modeling* as an introductory statement, and *Core Characteristics of OOP* as the sub-heading).
  - **Open by connecting to prior chapters** in one paragraph ("Chapter 01 introduced X, Chapter 02 explored Y, this chapter asks Z"), so the course reads as one narrative rather than four disconnected documents.
- **Rich Formatting & Math**:
  - Use bold key terms, blockquotes (`>`) for core quotes/analogies (e.g. *"OOP is like Life!"*), and LaTeX math for formal relationships (e.g. $\text{Object} = \text{An Instance of a Class}$).
  - Inside `$$...$$`, never use raw `&` or other LaTeX metacharacters; rewrite the phrase in words instead.
- **Punctuation Standard**:
  - Use standard hyphens `-` instead of em-dashes `—` across headings, captions, and text.
  - This applies to **every file type**: `Notes.md`, `.cpp` comments, and visual-notes `index.html`. Em-dashes have historically leaked into code comments and HTML prose - check all three.

### 3.1 Mandatory Notes.md Sections

Every chapter's `Notes.md` carries these, in this order:

1. `# Chapter NN - <Topic>` plus an opening paragraph linking back to prior chapters, and the chapter's defining LaTeX equation.
2. **📌 Table of Contents** with working anchors.
3. A **📄 Source Code Reference** blockquote listing every `.cpp` file in `coding/` as a relative link with a one-line description of what it teaches.
4. The teaching narrative.
5. **Key Implementation Rules & Gotchas** - a numbered list of the traps.
6. **Source Code Walkthrough** - one `### N. <filename>` subsection per `.cpp` file.
7. **Summary** - a single ASCII box recapping the chapter's numbered takeaways.
8. The prev/next chapter navigation footer (see 3.4).

### 3.2 Code & Notes Synchronization

- Code embedded in the **Source Code Walkthrough** must be the **complete file, byte-for-byte identical** to the `.cpp` in `coding/` - comments, blank lines, and indentation included.
- Code embedded **in the teaching narrative** may be an abridged fragment or a hypothetical variation (e.g. a `setAge` with validation that the source file omits), because the narrative is teaching an idea rather than documenting a file. Fragments that *do* claim to quote a source file must match its signatures, variable names, and logic exactly.
- **Program Output blocks**: when showing what a file prints, run it first and paste the real output. Never hand-write expected output - constructor/destructor chaining order is exactly the kind of thing that is easy to get wrong on paper.

### 3.3 Anchor Slug Rules

TOC anchors follow GitHub's slug algorithm: lowercase, strip punctuation, spaces become hyphens. Critically, `&` is **removed but its surrounding spaces are not collapsed**, producing a double hyphen:

```
"## Key Implementation Rules & Gotchas"  ->  #key-implementation-rules--gotchas
"## Access Modifiers in C++"             ->  #access-modifiers-in-c
```

### 3.4 Links Must Be Relative and Portable

- **Never** write absolute or machine-local links (`file:///Users/...`). They break for every other reader and on GitHub.
- Always use repo-relative paths with URL-encoded spaces: `[\`1. single-inheritance.cpp\`](../coding/1.%20single-inheritance.cpp)`.
- Every `Notes.md` ends with a prev/next navigation table linking the adjacent chapters' `Notes.md`.

---

## 4. Visual Web Notes (`notes/visual notes/`)

### 4.0 Shared Design Core (Mandatory in Every Chapter)

These are non-negotiable and identical across all chapters. **Never redefine tokens, fonts, or JS behaviour per chapter.**

- **Strict 3-File Separation**:
  - `index.html`: Pure semantic structure with no inline `<style>` or `<script>` tags.
  - `style.css`: Clean CSS custom properties (`:root`, `[data-theme="dark"]`), responsive grid, and components.
  - `script.js`: Interactive logic (TOC scrollspy, reading progress bar, code copy buttons, theme toggle, full-width toggle, back-to-top).
- **Zero Build Step**: The files must open immediately by double-clicking `index.html` locally in any browser.
- **Shared `localStorage` keys**: `oop-notes-theme` and `oop-notes-width`, so a reader's theme and width choice persist as they move from chapter to chapter. Never namespace these per chapter.
- **Required Interactive Features** (all six, in every chapter):
  1. TOC scrollspy highlighting the active section (`IntersectionObserver`)
  2. Fixed reading progress bar reflecting scroll percentage
  3. One-click code copy buttons with "Copied" feedback
  4. Theme toggle (`☾` / `☀`) persisted in `localStorage`
  5. Full-width toggle (`⊞` / `⊡`) expanding to `98vw`, persisted in `localStorage`
  6. Back-to-top button appearing past 600px of scroll
- **Prev/Next Chapter Navigation**: a `.chapter-nav` block immediately before `</main>` linking the adjacent chapters' `index.html`.

### 4.1 Typography & Fonts
- **Headings (`h1`, `h2`, `h3`, `h4`)**: `Big Shoulders Display`, sans-serif (weights: 700, 800).
- **Body Prose**: `Source Serif 4`, Georgia, serif (size: `18.5px`, line-height: `1.75`).
- **Code, Data, Labels, & Badges**: `IBM Plex Mono`, monospace (weights: 400, 600, 700).

### 4.2 Curated Semantic Color System

All colors must be defined as CSS variables and adapted across Light and Dark themes:

| Element | Light Mode (`:root`) | Dark Mode (`[data-theme="dark"]`) | Purpose & Behavior |
| :--- | :--- | :--- | :--- |
| **Canvas (`--paper`)** | `#FAF9F6` (Archival Cream) | `#0B0E14` (Deep Charcoal Slate) | Base reading background with subtle dot-grid |
| **Cards (`--paper-raised`)**| `#FFFFFF` | `#141A24` | Elevated content boxes and diagram containers |
| **Body Ink (`--ink`)** | `#0F172A` (Slate 900) | `#F1F5F9` (Slate 100) | High-contrast, easy-reading prose text |
| **Body Bold (`strong`)** | **`#D97706` (Dark Yellow)** | **`#FBBF24` (Cyber Gold)** | **Both text and underline are Dark Yellow/Amber** |
| **Pointer Titles (`ol > li > strong:first-child`)** | **`#DB2777` (Vivid Pink)** | **`#F472B6` (Neon Pink)** | **Leading titles of numbered points (1., 2., 3.) are Pink with Pink underline** |
| **Pointer Markers (`ol > li::marker`)** | **`#DB2777` (Pink)** | **`#F472B6` (Neon Pink)** | Number markers `1.`, `2.` in monospace bold |
| **Italics (`em`)** | `#B45309` (Warm Amber Gold) | `#FDE68A` (Pale Gold) | Secondary emphasis across body prose |
| **Inline Code (`code`)** | `#0369A1` on `#E0F2FE` | `#7DD3FC` on `rgba(56, 189, 248, 0.15)` | Technical Ice-Blue pill chip with border |
| **Structural Blue (`--blue`)**| `#0284C7` | `#38BDF8` | Indices (`01`, `02`), blueprint headers, active TOC items, progress bar |
| **Attempt Tags (`.tag`)** | `#D97706` / `#B45309` | `#FBBF24` / `#FDE68A` | Concept & phase badges (`ATTEMPT 1`, `ATTEMPT 2`) |
| **Callout Panels (`.callout`)**| `#C2410C` (Terracotta) | `#FB923C` (Warm Rust) | Highlighting core philosophical quotes |
| **Semantic Emerald (`--emerald`)** | `#059669` | `#34D399` | Allowed / accessible / success states |
| **Semantic Rose (`--rose`)** | `#E11D48` | `#FB7185` | Blocked / private / failure states |
| **Code Syntax Theme** | `#0F172A` Slate Carbon | `#07090E` Midnight Carbon | Keywords (`#38BDF8`), Types (`#34D399`), Strings (`#FDE047`), Functions (`#60A5FA`), Comments (`#94A3B8`) |

### 4.3 Layout & Width
- Maximum content width defaults to `1720px`; the full-width toggle expands to `98vw`.
- Prose paragraphs cap at `86ch` for optimal reading line length.
- Sidebar TOC collapses below `1024px`; the chapter-nav grid collapses to one column below `640px`.

### 4.4 Component Lane (Chosen Per Chapter)

The shared core above is fixed, but the **component vocabulary** is a deliberate per-chapter choice. Two lanes exist. Pick one for a chapter and use it consistently throughout that chapter - never mix them within a single page.

| Lane | Used By | Signature Components |
| :--- | :--- | :--- |
| **A - Technical Drawing Sheet** | Chapter 01, Chapter 02 | `.titleblock` / `.tb-cell` header, numbered `.figure` + `.fig-no` plates, `.marginnote`, corner `.tick` marks, `.prose` columns |
| **B - Swiss Editorial** | Chapter 03, Chapter 04 | `.hero` + `.meta-badges` header, numbered `section.sec` + `.sec-num`, `.card-grid` / `.card`, `.callout`, `.alert-box`, `.diagram-box` + `.diagram-pre`, `.spec-table`, `.pill` groups |

**New chapters default to Lane B** (Swiss Editorial), which is the newer and lighter-weight vocabulary.

### 4.5 One Chapter-Specific Interactive Diagram

Beyond the six shared features, every chapter's visual notes carry **at least one bespoke interactive diagram** that makes that chapter's central idea tangible - something the reader *operates*, not just reads. A static ASCII plate explains a structure; an interactive one lets the reader test a rule and be surprised. Where a chapter's hardest idea is a **consequence** (a bug, an ordering, a cost), prefer a simulator with a Reset over a hover highlight.

Current inventory - keep this table updated when adding a chapter:

| Chapter | Bespoke Interaction | What It Makes Tangible |
| :--- | :--- | :--- |
| **01** | `#ripple-fan` **Parameter Ripple Simulator** - add a property, then fix call sites one at a time while a counter drains | One new field costs 5 hand edits, and nothing in the language points them out |
| **01** | `.blueprint-card` &rarr; `.instance-card` hover highlight | One blueprint, many independent objects |
| **02** | `#copy-sim` **Shallow vs Deep Copy Simulator** - pick a copy strategy, copy, then run both destructors | Shallow copy double-frees one heap float; deep copy tears down cleanly |
| **03** | `#access-probe-widget` **Access Probe** - pick a specifier x a caller, get the compiler's verdict and light the matrix row/cell | Why `private` blocks even a child, and what `protected` exists for |
| **03** | `.pill` hover glows `.shield-boundary` blue/rose | The public surface vs the private interior |
| **04** | `#chain-console` **Ctor/Dtor Chaining Player** - Step/Play/Reset through all six lifecycle stages with live program output | Base constructs first and destructs last |
| **04** | `.derived-card` hover lights `.base-card` + inherited member pills | What a child actually inherits, member by member |

Guard every listener with a null check so a page that lacks the component never throws.

### 4.6 Code Blocks in Visual Notes

- Visual-notes code blocks are **abridged by design** - they carry the teaching essence, not the full file. The verbatim source lives in `Notes.md`'s Source Code Walkthrough.
- Syntax highlighting is hand-authored with `<span>` classes: `.kw` keywords, `.ty` types, `.str` strings, `.cm` comments, `.fn` functions, `.num` numerals.
- HTML-escape `<`, `>`, and `&` inside `<pre>` blocks (`&lt;`, `&gt;`, `&amp;`), including inside ASCII diagrams that use `<--` arrows.

---

## 5. Verification Checklist

Before finalizing any changes in any chapter, run all of these:

1. **Compile every `.cpp`**: `g++ -std=c++17 -fsyntax-only <file>` must pass with zero errors.
   > **macOS caveat**: the sources use `#include <bits/stdc++.h>`, a GCC/libstdc++ extension that Apple clang does not ship. A bare `g++` invocation therefore fails with `fatal error: 'bits/stdc++.h' file not found` - this is an environment issue, **not** a code error. Verify by writing a shim `bits/stdc++.h` (pulling in `<iostream>`, `<string>`, `<vector>`, `<algorithm>`, ...) into a scratch directory and compiling with `-I<scratch>`, or by installing real GCC via `brew install gcc`.
2. **Run the programs** whose output is quoted in `Notes.md`, and paste the actual output.
3. **Verify verbatim sync**: every Source Code Walkthrough block must be byte-identical to its `.cpp`. Diff them programmatically rather than by eye.
4. **Validate no user notes, examples, or analogies were deleted** (Zero-Omission Rule).
5. **Check `visual notes/style.css`**:
   - All `strong` elements use Dark Yellow/Amber (`#D97706` / `#FBBF24`) for both text and underline.
   - Only leading numbered list pointer titles (`ol > li > strong:first-child`) use Vivid Pink (`#DB2777` / `#F472B6`).
   - Braces balance (`{` count equals `}` count); no stray syntax errors.
6. **Check `visual notes/script.js`** parses: `node --check script.js`.
7. **Check `index.html`** tag balance for `div`, `section`, `main`, `nav`, `a`, `table`, `pre`, and confirm no inline `<style>` or `<script>` tags exist.
8. **Resolve every anchor**: each `href="#id"` in `index.html` and each `](#slug)` in `Notes.md` must point at an element/heading that exists (see 3.3 for slug rules).
9. **Resolve every relative link**: all `../` and `../../` paths must exist on disk; no `file:///` or `/Users/` absolute paths anywhere.
10. **Grep for em-dashes** (`—`) across `Notes.md`, `coding/*.cpp`, and `visual notes/index.html` - all must be hyphens.
11. **Update `README.md`**: chapter table row added, Roadmap checkbox ticked.
12. **Wire prev/next navigation** in both the new chapter and the previously-final chapter (whose "next" link did not exist before).
