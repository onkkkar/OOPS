# Chapter 01 - Introduction to OOPS

This is where the course begins. Before we can build classes, constructors, or security boundaries, we have to understand **why** object-oriented programming exists at all. This chapter traces the problem backwards: it starts inside the paradigm that came before OOP, pushes that paradigm until it visibly breaks, and only then introduces the container idea that fixes it. Chapter 02 will take that container and actually build one.

$$\text{Object} = \text{An Instance of a Class}$$

---

## 📌 Table of Contents

- [What is OOPS?](#what-is-oops)
- [Why Do We Need OOPS?](#why-do-we-need-oops)
- [The Paradigm Before OOPS: Functional Programming](#the-paradigm-before-oops-functional-programming)
- [Case Study: Modelling a Student](#case-study-modelling-a-student)
- [Limitations of Functional Programming](#limitations-of-functional-programming)
  - [1. Doesn't Model Real-World Entities Well](#1-doesnt-model-real-world-entities-well)
  - [2. Adding New Data Requires Modifying Every Function That Needs It](#2-adding-new-data-requires-modifying-every-function-that-needs-it)
  - [3. Global Data Has No Privacy](#3-global-data-has-no-privacy)
  - [4. No Clear Boundaries Between Data and Behaviour](#4-no-clear-boundaries-between-data-and-behaviour)
  - [5. No Modularity - Code Becomes Monolithic](#5-no-modularity---code-becomes-monolithic)
- [Towards a Solution: The "Container" Idea](#towards-a-solution-the-container-idea)
- [What is OOP? (Object-Oriented Programming System)](#what-is-oop-object-oriented-programming-system)
- [Objects and Classes](#objects-and-classes)
- [Attributes & Behaviour](#attributes--behaviour)
- [Key Implementation Rules & Gotchas](#key-implementation-rules--gotchas)
- [Source Code Walkthrough](#source-code-walkthrough)
  - [1. functional-programming.cpp](#1-functional-programmingcpp)
- [Summary](#summary)

---

## What is OOPS?

OOPS stands for **Object Oriented Programming System(s)** - a programming
paradigm (a way of structuring and thinking about code).

To actually understand _what_ it is and _why_ it matters, it helps more to see
the problem it solves than to memorize the definition. So before defining OOPS
any further, let's look at the paradigm that came before it, and where that
paradigm starts to struggle.

## Why Do We Need OOPS?

OOPS came into existence because the programming paradigm being used before it -
**Functional Programming** - ran into real difficulties as programs grew
larger and modeled more real-world things. To see why OOPS was needed, we
first need to understand functional programming and then watch it break down
on a concrete example.

## The Paradigm Before OOPS: Functional Programming

### How Functional Programming Works

Inside `main()`, we call a function. That function may call another function,
which may call another, and so on. Each function does its own work and, when
it finishes, optionally returns a value back to whoever called it. Once
everything unwinds back to `main()`, `main()` itself returns, and the program
exits.

When we call a function, we pass it **arguments** - the data it needs to do
its job - and it may give us back an **output** via a return value.

## Case Study: Modelling a Student

### The Requirement

Say we need to write a program for **100 students**, where each student has:

- their own **properties**: `id`, `age`, `name`
- their own **behaviours**: `study()`, `eat()`, `sleep()`

On top of that, the program has one piece of data shared by everyone - the
school's name, `schoolName` - which functional programming can only express as
a **global variable**.

Let's solve this the only way functional programming lets us: with plain
variables and plain functions.

> 📄 **Source Code Reference**: See the executable C++ code in [`coding/1. functional-programming.cpp`](../coding/1.%20functional-programming.cpp).

### Attempt 1 - One Student

For a single student, this reads naturally enough
(from `coding/1. functional-programming.cpp`):

```cpp
void study(int id, int age, string name)
{
    cout << name << " (id: " << id << ", age: " << age << ") is Studying at " << schoolName << endl;
}

void eat(int id, int age, string name)
{
    cout << name << " is Eating" << endl;
}

void sleep(int id, int age, string name)
{
    cout << name << " is Sleeping" << endl;
}
```

and inside `main()` we keep that one student's data as plain variables and
hand it to each behaviour:

```cpp
int id = 1;
int age = 20;
string name = "Rahul";

study(id, age, name);
eat(id, age, name);
sleep(id, age, name);
```

This looks fine - for **one** student. The trouble starts when we try to
scale it to 100.

### Scaling to 100 Students

#### Option A: Duplicate Variables

We give every student their own numbered set of variables - `id1`, `id2`,
`id3`, ... `age1`, `age2`, ... and so on:

```cpp
void duplicateVariables()
{
    int id1 = 1, id2 = 2, id3 = 3;
    int age1 = 20, age2 = 21, age3 = 19;
    string name1 = "Rahul", name2 = "Aman", name3 = "Simran";

    study(id1, age1, name1);
    study(id2, age2, name2);
    study(id3, age3, name3);

    // compiles fine, but silently wrong - mixed up students' data
    study(id1, age2, name3);
}
```

For **100** students, that's `id1..id100`, `age1..age100`, and
`name1..name100` - 300 separate variables for what is conceptually a single
kind of thing, "a student." Worse, nothing stops us from calling
`study(id1, age2, name3)` - mixing up three different students' data in one
call. It compiles fine and runs; it's just silently wrong,
because nothing in the language says `id1`, `age1`, and `name1` belong
together.

#### Option B: Parallel Arrays

Instead of numbered variables, we use one array per property:

```cpp
void parallelArrays()
{
    int ids[3] = {1, 2, 3};
    int ages[3] = {20, 21, 19};
    string names[3] = {"Rahul", "Aman", "Simran"};

    for (int i = 0; i < 3; i++)
    {
        // We MUST remember that index i means the same student in
        // every single array. Nothing enforces that correspondence
        // except our own discipline while writing the loop.
        study(ids[i], ages[i], names[i]);
    }
}
```

This is slightly less repetitive, but the underlying problem hasn't gone
away: `ids[i]`, `ages[i]`, and `names[i]` are only "the same student" because
_we_ keep every array in sync by hand. If any one array gets sorted, filtered,
or updated independently of the others, the correspondence silently breaks.

**Note:** even at just 3 students, this code already feels messy and fragile.
At 100 students - with more properties and behaviours added over time - it
becomes genuinely unmanageable.

## Limitations of Functional Programming

Looking back at `1. functional-programming.cpp`, we can now name exactly
what's going wrong.

### 1. Doesn't Model Real-World Entities Well

In the real world, a student is **one thing**. You point at Rahul and that
single person carries his id, his age, his name, and the fact that he studies,
eats, and sleeps. It's all one package.

In our code, that one thing has been chopped into six unrelated pieces:

```
REAL WORLD ENTITY (Student)            FUNCTIONAL PROGRAMMING (Scattered Pieces)
+---------------------------+          +--------------------------------------+
| Rahul                     |   ===>   | int id = 1;          (loose var)     |
| - id: 1                   |          | int age = 20;        (loose var)     |
| - age: 20                 |          | string name="Rahul"; (loose var)     |
| - name: "Rahul"           |          +--------------------------------------+
|                           |          | void study(...)      (loose func)    |
| Behaviours:               |          | void eat(...)        (loose func)    |
| - study(), eat(), sleep() |          | void sleep(...)      (loose func)    |
+---------------------------+          +--------------------------------------+
                                       | void teach(...)      (mixed in file!)|
                                       +--------------------------------------+
```

Nothing in the language says these six belong together. They're just three
loose variables and three loose functions sitting in a file. "Rahul" only
exists in _our head_ - we have to remember that `id`, `age`, and `name` are
one person, and remember to hand them to `study()` on every call so that
`study()` knows whom it is talking about.

And this is the small version of the problem. A real student has far more than
three properties - roll number, marks, attendance, fees, address, class,
section - and far more than three behaviours. Each one added is one more loose
piece to track by hand. Modelling **one** student is already a chore.

#### Now Add Teachers

Now the school wants teachers too. A teacher has their own properties -
`teacherId`, `teacherName`, `subject`, `salary` - and their own behaviours -
`teach()`, `grade()`, `takeAttendance()`. So we do the exact same thing again:
more loose variables, more loose functions, dumped into the same flat file
next to the student ones.

So the code never actually contains a "Student" or a "Teacher." It only
contains a growing pile of variables and functions that we, the programmers,
have privately agreed to think of as students and teachers. That agreement is
not written down anywhere the compiler can see - which is precisely why
functional programming models real-world entities so poorly.

### 2. Adding New Data Requires Modifying Every Function That Needs It

Suppose we now add a new property, `numberOfSubjects`, and only `study()`
actually needs it - to print how many subjects a student is taking. `eat()`
and `sleep()` never touch it, so their signatures stay exactly as they are;
that part isn't as bad as it might sound.

But `study()`'s signature did change, from three parameters to four:

```cpp
void study(int id, int age, string name, int numberOfSubjects)
{
    cout << name << " is Studying " << numberOfSubjects << " subjects" << endl;
}
```

and that ripples outward. Every place `study()` gets called anywhere in the
file now has one argument too few, and won't compile until it's fixed by
hand:

```cpp
study(id, age, name, numberOfSubjects);                    // main()
study(id1, age1, name1, subjects1);                         // duplicateVariables()
study(id2, age2, name2, subjects2);
study(id3, age3, name3, subjects3);
study(ids[i], ages[i], names[i], subjectsCount[i]);          // parallelArrays()
```

Five call sites, scattered across the file, all needing to be found and fixed
by hand - for one new property on one function.

```
THE RIPPLE EFFECT OF PARAMETER CHANGES:

       CHANGE: Add `numberOfSubjects` to student properties
                                 |
                                 v
        [ void study(id, age, name, numberOfSubjects) ]  <-- Signature Changed!
                                 |
           +---------------------+---------------------+
           |                     |                     |
           v                     v                     v
     main() call site    duplicateVariables()    parallelArrays() loop
     (Needs update)       (3 calls to update)       (Needs array update)
                                 |
                                 v
                   Pass-through functions like dailyRoutine()
                   (Must accept & forward unused param)
```

And this is the small version. The moment some _other_, unrelated function
calls `study()` on a student's behalf - say a `dailyRoutine()` that just runs
`study(); eat(); sleep();` in sequence - that function has to start accepting
`numberOfSubjects` too, purely to forward it along, even though it never uses
the value itself. Nothing marks `numberOfSubjects` as "belongs to the
student, available wherever the student's data already is." It has to be
re-declared, one parameter at a time, in every function that even indirectly
touches it.

### 3. Global Data Has No Privacy

#### The Story

All 100 of our students go to the same school, and their behaviours need to
know its name - `study()` should be able to say "Rahul ... is Studying at
DPS". The name is identical for every one of them, so making it a fourth
per-student property and copying `"DPS"` into all 100 students would be
pointless. What we want is **one** shared piece of data that every _student_
function can reach.

Functional programming gives us exactly one tool for that: a **global
variable**.

```cpp
// Global Data
string schoolName = "DPS";
```

And it works. `study()` reads it without being passed it:

```cpp
void study(int id, int age, string name)
{
    cout << name << " (id: " << id << ", age: " << age << ") is Studying at " << schoolName << endl;
}
```

```
Rahul (id: 1, age: 20) is Studying at DPS
```

So far, so good - this is exactly what we asked for.

#### The Problem

Now our program grows and we add `teach()`. It is a **teacher-side** function;
it has nothing to do with student data at all. But `schoolName` is global, so
`teach()` can freely read it _and silently overwrite it_:

```cpp
// --- unrelated to students, but can still read AND overwrite schoolName - global data has no privacy ---
void teach()
{
    cout << "Teaching a class at " << schoolName << endl;
    schoolName = "Hacked High";
}
```

Back in `main()`, nobody asked for that change, but everyone gets it:

```cpp
teach();

// schoolName was silently changed by a function that doesn't own it
cout << "School is now: " << schoolName << endl;
```

```
Teaching a class at DPS
School is now: Hacked High
```

```
UNINTENDED GLOBAL DATA LEAKAGE:

+--------------------------------------------------------+
|                     GLOBAL SCOPE                       |
|   string schoolName = "DPS";                           |
+--------------------------------------------------------+
         |                                      ^
         | Allowed Read Access                  | Unintended Write Access!
         v                                      |
+--------------------+                +--------------------+
| Student Functions  |                | Teacher Functions  |
|   study()          |                |   teach()          |
| (Intended Reader)  |                | (Overwrites global |
+--------------------+                |  schoolName data)  |
                                      +--------------------+
```

Ask the real question here: **did we ever want `teach()` to have that access?**
No. We wanted `schoolName` shared among the _students_, not exposed to every
function in the program. But that choice was never ours to make. The moment we
declare a global in functional programming, **everyone** can read it and
**everyone** can write to it. There is no way to say "this data belongs to the
students, and only student behaviours may touch it."

So one unrelated function can quietly corrupt data the rest of the program
depends on, and the compiler never warns us - because as far as the language is
concerned, nothing was violated. There was no rule to violate in the first
place.

### 4. No Clear Boundaries Between Data and Behaviour

That last point is really a symptom of something bigger: in functional
programming there is **no boundary** we can draw around a concept.

Look at how the file is laid out. `schoolName` sits at the top as a loose
global. A student's `id`, `age`, and `name` are loose variables inside
`main()`. `study()`, `eat()`, and `sleep()` are loose functions further down,
sitting at exactly the same level as `teach()` - which belongs to a completely
different concept. The file is one flat surface, and everything on it can see
everything else.

The only thing that makes `study()` "a student behaviour" and `teach()` "a
teacher behaviour" is that _we named them that way_. The language sees four
equally-anonymous functions. So:

- Nothing says `id`, `age`, and `name` belong together as one student - which
  is exactly why `study(id1, age2, name3)` compiles.
- Nothing says `study()` belongs _with_ that data - which is why the data has
  to be passed in by hand on every single call.
- Nothing says `teach()` is on the outside of the student concept - which is
  why it can reach straight into `schoolName`.

Every one of those boundaries exists only in the programmer's head. What we
actually need is a way to draw the boundary **in the code itself**: a line
where we can say "this data and these behaviours are one thing - inside is
theirs, outside stays out."

```
FLAT FILE LAYOUT (Functional) vs. BOUNDED CONCEPT (OOP Target):

Functional Programming (Flat & Unbounded):
+-------------------------------------------------------------------------+
| [schoolName global]   [id, age, name]   [study()]   [eat()]   [teach()] |
| (Everything is exposed on one flat surface; zero isolation boundaries)   |
+-------------------------------------------------------------------------+

Object-Oriented Goal (Encapsulated & Bounded):
+-----------------------------------+     +-----------------------------------+
|         STUDENT BOUNDARY          |     |         TEACHER BOUNDARY          |
|-----------------------------------|     |-----------------------------------|
|  Data: id, age, name, schoolName  |     |  Data: teacherId, subject         |
|  Behaviours: study(), eat()       |     |  Behaviours: teach(), grade()     |
+-----------------------------------+     +-----------------------------------+
```

### 5. No Modularity - Code Becomes Monolithic

As we add more students, more teachers, more subjects - all handled the same
way, as more flat variables and more flat functions - everything piles into
one undifferentiated set of globals and functions with no sub-grouping. There
is no unit smaller than "the whole file" to reason about, test, or reuse.
Functional programming code like this can become monolithic and increasingly
difficult to maintain as it grows.

## Towards a Solution: The "Container" Idea

Imagine, instead, a single container - a **box** - that holds data (`id`, `name`, `age`) together, _and_ holds the behaviours (`study()`, `eat()`, `sleep()`) that act on them, all bound together as **one unified unit**.

```
+-------------------------------------------------------+
|                   STUDENT CONTAINER                   |
|-------------------------------------------------------|
|  [ Data / State ]                                     |
|  - id: 101                                            |
|  - name: "Rahul"                                      |
|  - age: 20                                            |
|-------------------------------------------------------|
|  [ Behaviours / Methods ]                             |
|  - study()                                            |
|  - eat()                                              |
|  - sleep()                                            |
+-------------------------------------------------------+
```

### Key Breakthroughs of the Container Model

1. **Self-Contained Representation**: Filling in that container with real values is what makes something "a student". Whoever holds a fully filled-in container has all the information and behaviour tags that define a student.
2. **Data Privacy & Protection**: This fixes the privacy problem inherent in functional/procedural programming. Data sealed _inside_ the box can be reached **only** by the box's own behaviours.
   - _Contrast with Functional Code_: Unlike the global `schoolName` in `1. functional-programming.cpp` (which `teach()` could read and overwrite even though it had no business doing so), encapsulation in OOP ensures strict boundary access.
3. **Formalizing Class and Object**:
   - **Class**: This "container" or blueprint is formally introduced as a **Class**.
   - **Object**: A container filled in with real values is what we call an **Object**.
4. **Restoring Modularity**: OOPS brings back the **modularity** that functional programming lost - grouping related data and behaviour into self-contained, reusable units instead of one flat pile of globals and functions.

---

## What is OOP? (Object-Oriented Programming System)

> **"OOP is like Life! As things exist in Life, the same concepts exist in OOPS."**

In life, we deal with various physical and abstract entities. For example:

- **Bird / Sparrow**: "Sparrow" is an abstract term or concept, but in reality, there can be multiple individual sparrows (Sparrow 1, Sparrow 2, Sparrow 3, ...), each possessing its own specific attributes and behaviours.
- **Person**: "Person" is a concept, while individual people (Person 1, Person 2, Person 3, ...) have their own attributes (name, age, height) and behaviours (speak, eat).

If we want to solve real-world problems and depict real-world systems through code, **OOP is the paradigm of choice**. Just like a Student is a real-world entity with attributes and behaviours, we can model and construct exact software representations of a Student using OOP.

### Core Characteristics of OOP

1. **Real-World Problem Solving**: A programming technology/paradigm designed to solve real-world problems by modeling real-world systems directly within programming languages.
2. **Object Communication**: A programming style that involves dividing a program into distinct object components that communicate with one another.
3. **Entity-Based Coding Style**: Software is structured around real-world entities/objects (e.g., Student, Teacher, Car, Bus, etc.), where every object maintains its own private state/attributes and associated behaviours.
4. **Data and Behaviour Unification**: The fundamental idea is to combine both data and behaviour into a single unit to promote modularity.
   - _The Blueprint Analogy_: Imagine creating a box labeled **Student**. Inside it are all data fields (`id`, `name`, `age`) and behaviours (`study()`, `eat()`, `sleep()`). This box is a **blueprint**.
   - Anyone following this exact blueprint is termed a **Student**. Student `s1` has all these data fields and behaviours, as do `s2`, `s3`, and so on.
   - This mirrors the real world: the blueprint/container is a **Template (Class)**, whereas the actual entities `s1`, `s2`, `s3` created from it are **Objects**.
   - The template is the abstract idea (e.g., _"A student must have these attributes and behaviours"_ or _"A car must have these properties"_), while objects are the concrete instances that possess those properties (students, cars, birds, etc.).
5. **Enhanced Modularity, Reusability, and Maintainability**: OOP promotes modularity by encapsulating data and behaviour into a container/class. This modular approach greatly enhances code reusability and maintainability, allowing objects to be seamlessly reused across different parts of a program.
6. **"OOP is Life"**: OOP mirrors real-world structures, making complex software architectures intuitive to design, reason about, and maintain.

---

## Objects and Classes

1. **Real-World Entities Have State & Behaviour**: Entities like cars, persons, and students have state (data) and behaviour (actions).
2. **From Real World to Programming**: A student named **Rahul** is a real-world entity. In programming, Rahul is represented as an **Object**.
3. **The Blueprint (Class)**: What defines how an object will look and act? There must be a blueprint or template, which is the **Class**.
4. **Fundamental Definition**:
   $$\text{Object} = \text{An Instance of a Class}$$

### Concrete Example: Car Class vs. Car Objects

- **Car Template (Class)**: Defines properties: `bodyShape`, `color`, `tyres`, `seats`.
- **Fortuner (Object)**: `bodyShape` = SUV, `color` = White, `tyres` = 4, `seats` = 7.
- **WagonR (Object)**: `bodyShape` = Hatchback, `color` = White, `tyres` = 4, `seats` = 4.

```
+-------------------------------------------------------+
|                     CLASS: Car                        |
|-------------------------------------------------------|
|  - bodyShape: string                                  |
|  - color: string                                      |
|  - tyres: int                                         |
|  - seats: int                                         |
+-------------------------------------------------------+
                           |
       +-------------------+-------------------+
       |                                       |
       v                                       v
+-----------------------+               +-----------------------+
|  OBJECT: Fortuner     |               |   OBJECT: WagonR      |
|-----------------------|               |-----------------------|
|  bodyShape = "SUV"    |               |  bodyShape="Hatchback"|
|  color     = "White"  |               |  color     = "White"  |
|  tyres     = 4        |               |  tyres     = 4        |
|  seats     = 7        |               |  seats     = 4        |
+-----------------------+               +-----------------------+
```

_Summary_: The actual cars on the road (**Fortuner**, **WagonR**) are real **Objects**. The abstract idea/blueprint of what a car is constitutes the **Class / Blueprint / Template**. An object is the variable/entity that actually possesses that blueprint's structure.

---

## Attributes & Behaviour

1. **Attributes (State / Properties)**: The data elements, properties, or variables belonging to an object (e.g., `name`, `age`, `height`).
2. **Behaviour (Methods / Functions)**: The functions or actions that an object can execute (e.g., `speak()`, `eat()`).

### Visual Representation: Person Class & Instances

```
+-------------------------------------------------------+
|                    CLASS: Person                      |
|-------------------------------------------------------|
|  [ Data / State / Attributes ]                        |
|  - name: string                                       |
|  - age: int                                           |
|  - height: double                                     |
|-------------------------------------------------------|
|  [ Behaviours / Methods ]                             |
|  - speak()                                            |
|  - eat()                                              |
+-------------------------------------------------------+
                           |
        +------------------+------------------+
        |                  |                  |
        v                  v                  v
+----------------+  +----------------+  +----------------+
| OBJECT: Rahul  |  | OBJECT: Kunal  |  |  OBJECT: Ram   |
|----------------|  |----------------|  |----------------|
| name = "Rahul" |  | name = "Kunal" |  | name = "Ram"   |
| age  = 20      |  | age  = 22      |  | age  = 21      |
| height = 5.9   |  | height = 6.0   |  | height = 5.8   |
|----------------|  |----------------|  |----------------|
| speak()        |  | speak()        |  | speak()        |
| eat()          |  | eat()          |  | eat()          |
+----------------+  +----------------+  +----------------+
```

All of them - **Rahul**, **Ram**, and **Kunal** - are individual instances of the `Person` class. Every one of them is an **Object** possessing its own unique attribute values while sharing the common set of behaviours defined by the `Person` blueprint.

---

## Key Implementation Rules & Gotchas

1. **Parameter Order Is Silent and Unchecked:** Passing `study(age, id, name)` instead of `study(id, age, name)` compiles cleanly and runs, because both `id` and `age` are `int`. The bug surfaces only as wrong output. Grouping the data into one unit removes the whole class of mistake.
2. **Grouping Only Exists in Your Head:** In functional programming, nothing in the language records that `id`, `age`, and `name` belong to the same student. That relationship lives in naming discipline and memory, not in the code.
3. **Adding One Attribute Ripples Everywhere:** A new property means editing every function signature that needs it, plus every call site of those functions, plus every function that merely forwards the values along. One new field, many edits, and any one of them can be forgotten.
4. **Global Data Has No Owner and No Privacy:** A global like `schoolName` can be read and overwritten by any function anywhere in the program, including functions with nothing to do with students. The compiler never warns, because as far as the language is concerned nothing is wrong.
5. **Parallel Arrays Keep Correctness in the Index:** Storing students as `ids[]`, `ages[]`, and `names[]` means correctness depends entirely on every array staying the same length and every loop using the same index. Nothing enforces it.
6. **Bad Design Still Has to Compile:** The example file deliberately demonstrates poor architecture - global state, loose variables, parallel arrays. It is still valid, compiling C++. Bad design means poor structure, never broken syntax.

---

## Source Code Walkthrough

### 1. functional-programming.cpp

From [`coding/1. functional-programming.cpp`](../coding/1.%20functional-programming.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Functional Programming Paradigm (Before OOP)
// =========================================================================
// Demonstrates how procedural/functional programming organizes data and
// functions separately, and the scaling/security bottlenecks that arise.
// =========================================================================

// ---------------- Global Data (Shared State) ----------------
// Problem: Global data has no privacy or access restrictions;
// any function across the codebase can read and mutate it.
string schoolName = "DPS";

// ---------------- Student Behaviour Functions ----------------
// Functions must take every piece of student data as separate parameters.

void study(int id, int age, string name)
{
    cout << name << " (id: " << id << ", age: " << age << ") is Studying at " << schoolName << endl;
}

void eat(int id, int age, string name)
{
    cout << name << " is Eating" << endl;
}

void sleep(int id, int age, string name)
{
    cout << name << " is Sleeping" << endl;
}

// ---------------- Scaling Attempt 1: Duplicate Variables ----------------
// Problem: Variables multiply exponentially; mixing up arguments is silently valid.
void duplicateVariables()
{
    int id1 = 1, id2 = 2, id3 = 3;
    int age1 = 20, age2 = 21, age3 = 19;
    string name1 = "Rahul", name2 = "Aman", name3 = "Simran";

    study(id1, age1, name1);
    study(id2, age2, name2);
    study(id3, age3, name3);

    // Compiles fine, but silently wrong - data mismatch bug
    study(id1, age2, name3);
}

// ---------------- Scaling Attempt 2: Parallel Arrays ----------------
// Problem: Arrays are uncoordinated; no single entity bounds id[i] to name[i].
void parallelArrays()
{
    int ids[3] = {1, 2, 3};
    int ages[3] = {20, 21, 19};
    string names[3] = {"Rahul", "Aman", "Simran"};

    for (int i = 0; i < 3; i++)
    {
        study(ids[i], ages[i], names[i]);
    }
}

// ---------------- Global State Pollution ----------------
// An unrelated function can silently corrupt global state without ownership.
void teach()
{
    cout << "Teaching a class at " << schoolName << endl;
    schoolName = "Hacked High";
}

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- 1. Single Student Representation ----------------
    int id = 1;
    int age = 20;
    string name = "Rahul";

    study(id, age, name);
    eat(id, age, name);
    sleep(id, age, name);

    // ---------------- 2. Scaling to Multiple Students ----------------
    duplicateVariables();

    // ---------------- 3. Parallel Arrays Approach ----------------
    parallelArrays();

    // ---------------- 4. Uncontrolled State Mutation ----------------
    teach();

    // Global data was silently mutated by an external function
    cout << "School is now: " << schoolName << endl;

    return 0;
}
```

---

## Summary

1. **OOP Paradigm**: Object-Oriented Programming is a paradigm used to model and implement real-world objects in software.
2. **Real-World Alignment**: Identifying code structures that map directly to real-life entities and structuring code using classes and objects signifies the application of core OOP principles.
3. **Core Building Blocks**: **Classes** and **Objects** serve as the foundational building blocks of the entire Object-Oriented Programming paradigm.
4. **Major OOP Languages**: Prominent Object-Oriented programming languages include **C++**, **Java**, and **JavaScript** (JS).

---

<!-- chapter-nav -->

| Previous | Next |
| :--- | ---: |
|  | [Chapter 02 - Creating Objects &rarr;](../../Chapter%2002%20-%20Creating%20Objects/notes/Notes.md) |
