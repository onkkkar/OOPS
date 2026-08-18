# CLAUDE.md

This repo is a personal, chapter-by-chapter C++ / OOP learning course. These
are the working rules learned from how this repo's owner likes code and
notes written — follow them whenever writing or editing here.

## Repo Structure

- `Chapter NN - <Topic>/`
  - `Notes.md` — the chapter's teaching notes, telling one continuous story
  - `coding/` — runnable example `.cpp` files backing that story

## Writing Code (`.cpp` files)

- **Short Comments**: Comments stay short and single-line, only where something is genuinely non-obvious. No large comment blocks or per-line explanations.
- **Compilation Requirement**: Every example file must actually compile (`g++ -std=c++17 -fsyntax-only <file>`) — even code that's deliberately a *bad design example* should still be syntactically valid C++. "Messy" means poor structure, not broken syntax.
- **Consolidated Files**: Default to one well-named, consolidated file per topic (e.g. `functional-programming.cpp`) instead of splitting into many tiny files, unless explicitly asked to split by case.
- **Scoped Data**: Keep data scoped to where it's conceptually used — e.g. a single instance's fields as locals inside `main()`. Only reach for a global when the example is specifically demonstrating a problem caused by global state.
- **Numbered Ordering**: Prefix ordered example files with a number when a chapter's `coding/` folder builds up a sequence (e.g. `1. functional-programming.cpp`).

## Writing Notes (`Notes.md`)

- **Strict Zero-Omission Rule**: When cleaning up or enhancing user-written notes, **NEVER exclude, remove, or skip** anything written by the user. All user thoughts, concepts, analogies (e.g., sparrow/bird, student rahul/kunal/ram, car fortuner/wagonr), definitions, and points **MUST remain intact**. You may polish, fix typos/grammar, expand, and format, but **never delete original points or examples**.
- **Visual ASCII Architecture Diagrams**: Use clean ASCII box diagrams and visual flowcharts to illustrate:
  - Class vs. Object relationships and memory/container concepts.
  - Architectural comparisons (e.g., flat procedural file layout vs. bounded OOP concepts).
  - Limitations of bad design (e.g., data privacy leaks, parameter change ripple effects).
- **Navigation & Structure**:
  - Include a **📌 Table of Contents** at the top with clickable anchor links matching exact headers.
  - Maintain a clean hierarchy with Markdown headings (`#`, `##`, `###`, `####`) telling one continuous narrative.
- **Code & Notes Synchronization**:
  - Code snippets embedded in `Notes.md` must strictly match the actual `.cpp` source files in `coding/` (matching function names, parameter names, and logic).
  - Always back up a point or limitation with concrete code snippets pulled verbatim from the `.cpp` file whenever possible.
- **Rich Formatting**: Use bold key terms, blockquotes (`>`) for core takeaways/quotes (e.g., *"OOP is like Life!"*), and mathematical expressions where appropriate (e.g., $\text{Object} = \text{An Instance of a Class}$).

## Verifying Changes

- After editing `Notes.md`, re-read it to confirm headings render correctly, TOC anchor links work, and every embedded snippet matches its source `.cpp` file.
- Verify C++ code syntax by compiling with `g++ -std=c++17 -fsyntax-only`.

