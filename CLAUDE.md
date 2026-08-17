# CLAUDE.md

This repo is a personal, chapter-by-chapter C++ / OOP learning course. These
are the working rules learned from how this repo's owner likes code and
notes written — follow them whenever writing or editing here.

## Repo structure

- `Chapter NN - <Topic>/`
  - `Notes.md` — the chapter's teaching notes, telling one continuous story
  - `coding/` — runnable example `.cpp` files backing that story

## Writing code (`.cpp` files)

- Comments stay short and single-line, only where something is genuinely
  non-obvious. No large comment blocks or per-line explanations.
- Every example file must actually compile
  (`g++ -std=c++17 -fsyntax-only <file>`) — even code that's deliberately a
  *bad design example* should still be syntactically valid C++. "Messy" means
  poor structure, not broken syntax.
- Default to one well-named, consolidated file per topic (e.g.
  `functional-programming.cpp`) instead of splitting into many tiny files,
  unless explicitly asked to split by case.
- Keep data scoped to where it's conceptually used — e.g. a single instance's
  fields as locals inside `main()`. Only reach for a global when the example
  is specifically demonstrating a problem caused by global state.
- Prefix ordered example files with a number when a chapter's `coding/`
  folder builds up a sequence (e.g. `1. functional-programming.cpp`).

## Writing notes (`Notes.md`)

- Use proper Markdown headings/subheadings (`#`, `##`, `###`) that carry a
  clear top-to-bottom narrative — never leave notes as an unstructured dump.
- Fix grammar/spelling when cleaning up notes, but preserve the original
  intended meaning and teaching story.
- Always back a point or limitation with a concrete example from the code we
  write, whenever one is possible — never leave something as prose-only if a
  snippet can explain it more clearly. Pull the snippet verbatim from the
  real `.cpp` file when possible, or use a clearly-scoped illustrative
  extension when the point needs something not literally in the file (e.g. a
  hypothetical new parameter).
- Keep every code excerpt embedded in notes in sync with the actual `.cpp`
  file. When the code changes, update the notes' file names, function names,
  and snippets to match — no drift between what's read and what's run.
- Keep examples minimal and easy to read — no unnecessary bulk, no restating
  the same block twice.

## Verifying changes

- After editing `Notes.md`, re-read it to confirm headings render correctly
  and every embedded snippet still matches its source file.
