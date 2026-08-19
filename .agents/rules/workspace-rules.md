# Workspace Master Rules

This is the primary rules file loaded into the agent's memory for this workspace. It defines the absolute standards for writing C++ code, Markdown teaching notes, and visual web notes.

---

## 1. Repository Structure

```text
OOPS/
├── .agents/
│   └── rules/
│       └── workspace-rules.md     # Primary memory rules (this file)
├── Chapter NN - <Topic>/
│   ├── Notes.md                   # Chapter teaching notes telling one continuous narrative
│   ├── coding/                    # Runnable, clean, compiling .cpp source files
│   └── visual-notes/              # Interactive, beautifully styled web notes (HTML/CSS/JS)
```

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

---

## 3. Writing Teaching Notes (`Notes.md`)

- **Strict Zero-Omission Rule**:
  - When cleaning up, formatting, or enhancing user-written notes, **NEVER exclude, remove, or skip** anything written by the user.
  - All user thoughts, concepts, analogies (e.g., Sparrow/Bird, Rahul/Aman/Simran, Fortuner/WagonR), definitions, and points **MUST remain intact**.
  - Polish clarity, improve grammar, expand explanations, and format cleanly, but **never delete original points or examples**.
- **Visual ASCII Architecture Diagrams**:
  - Use structured ASCII box diagrams and clear visual flowcharts to illustrate:
    - Class vs. Object relationships, blueprints, and container memory layouts.
    - Architectural comparisons (e.g. flat procedural file layout vs. encapsulated OOP boundaries).
    - Failure modes and antipatterns (e.g. global data contamination, parameter ripple effects).
- **Navigation & Structure**:
  - Include a **📌 Table of Contents** at the top with clickable anchor links matching exact heading IDs.
  - Maintain a clean hierarchy with Markdown headings (`#`, `##`, `###`, `####`) telling one continuous story.
  - Distinguish narrative statements from sub-headings (e.g. *Real-World Modeling* as an introductory statement, and *Core Characteristics of OOP* as the sub-heading).
- **Code & Notes Synchronization**:
  - Code snippets embedded in `Notes.md` must strictly match the actual `.cpp` source files in `coding/` (matching function signatures, variable names, and logic verbatim).
- **Rich Formatting & Math**:
  - Use bold key terms, blockquotes (`>`) for core quotes/analogies (e.g. *"OOP is like Life!"*), and LaTeX math for formal relationships (e.g. $\text{Object} = \text{An Instance of a Class}$).
- **Punctuation Standard**:
  - Use standard hyphens `-` instead of em-dashes `—` across headings, captions, and text.

---

## 4. Visual Web Notes (`visual-notes/`)

When generating or updating the visual HTML notes for any chapter, adhere to the **Swiss Technical / Curated Harmonic Design System** implemented in Chapter 01.

### 4.1 Architecture & File Structure
- **Strict 3-File Separation**:
  - `index.html`: Pure semantic structure with no inline `<style>` or `<script>` tags.
  - `style.css`: Clean CSS custom properties (`:root`, `[data-theme="dark"]`), responsive grid, and components.
  - `script.js`: Interactive logic (TOC scrollspy, reading progress bar, code copy buttons, theme toggle, full-width toggle).
- **Zero Build Step**: The files must open immediately by double-clicking `index.html` locally in any browser.

### 4.2 Typography & Fonts
- **Headings (`h1`, `h2`, `h3`, `h4`)**: `Big Shoulders Display`, sans-serif (weights: 700, 800).
- **Body Prose**: `Source Serif 4`, Georgia, serif (size: `18.5px`, line-height: `1.75`).
- **Code, Data, Labels, & Badges**: `IBM Plex Mono`, monospace (weights: 400, 600, 700).

### 4.3 Curated Semantic Color System

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
| **Code Syntax Theme** | `#0F172A` Slate Carbon | `#07090E` Midnight Carbon | Keywords (`#38BDF8`), Types (`#34D399`), Strings (`#FDE047`), Functions (`#60A5FA`), Comments (`#94A3B8`) |

### 4.4 Layout, Width & Interactivity
- **Screen Width Flexibility**:
  - Maximum content width defaults to `1720px`.
  - Includes a floating **Full-Width Toggle (`⊞` / `⊡`)** persisting state in `localStorage` for wide monitors (`98vw`).
  - Prose paragraphs cap at `86ch` for optimal reading line length.
- **Interactive UI Features**:
  - **TOC Scrollspy**: Highlights active section in real-time.
  - **Reading Progress Bar**: Fixed top progress bar reflecting document scroll percentage.
  - **Code Block Copy Button**: One-click clipboard copy with visual "Copied!" feedback.
  - **Theme Toggle**: Floating button switching between light and dark themes, saved in `localStorage`.
  - **Interactive Blueprint Linking**: Hovering over a `.blueprint-card` highlights all its related `.instance-card` elements on the diagram.

---

## 5. Verification Checklist

Before finalizing any changes in any chapter:
1. Run `g++ -std=c++17 -fsyntax-only` on all `.cpp` files in `coding/` to guarantee zero compiler errors.
2. Confirm that all embedded code snippets in `Notes.md` and `visual-notes/index.html` match the `.cpp` files verbatim.
3. Validate that no user notes, examples, or analogies were deleted (Zero-Omission Rule).
4. Verify that in `visual-notes/style.css`:
   - All `strong` elements use Dark Yellow/Amber (`#D97706` / `#FBBF24`) for both text and underline.
   - Only leading numbered list pointer titles (`ol > li > strong:first-child`) use Vivid Pink (`#DB2777` / `#F472B6`).
   - No stray brackets or syntax errors exist in CSS or JS.
