# Chapter 01 - Introduction to OOPS

## What is OOPS?

OOPS stands for **Object Oriented Programming System(s)** - a programming
paradigm (a way of structuring and thinking about code).

To actually understand *what* it is and *why* it matters, it helps more to see
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
- a property they'd like to keep **private**: `gfName` (girlfriend's name)
- their own **behaviours**: `study()`, `eat()`, `sleep()`
- a behaviour that depends on the private property: `hasGF()`

Let's solve this the only way functional programming lets us: with plain
variables and plain functions.

### Attempt 1 - One Student

For a single student, this reads naturally enough
(from `coding/messy-code.cpp`):

```cpp
int id;
int age;
string name;

void study(int id, int age, string name)
{
    cout << name << " (id: " << id << ", age: " << age << ") is Studying" << endl;
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

This looks fine - for **one** student. The trouble starts when we try to
scale it to 100.

### Scaling to 100 Students

#### Option A: Duplicate Variables

We give every student their own numbered set of variables - `id1`, `id2`,
`id3`, ... `age1`, `age2`, ... and so on:

```cpp
int id1 = 1, id2 = 2, id3 = 3;
int age1 = 20, age2 = 21, age3 = 19;
string name1 = "Rahul", name2 = "Aman", name3 = "Simran";
string gfName1 = "Priya", gfName2 = "", gfName3 = "Karan";

study(id1, age1, name1);
study(id2, age2, name2);
study(id3, age3, name3);

// The compiler happily accepts this too - id1 with age2 with
// name3 - three DIFFERENT students' data mixed into one call.
study(id1, age2, name3);
```

For **100** students, that's `id1..id100`, `age1..age100`, `name1..name100`,
`gfName1..gfName100` - roughly 400 separate variables for what is
conceptually a single kind of thing, "a student." Worse, nothing stops us
from calling `study(id1, age2, name3)` - mixing up three different students'
data in one call. It compiles fine and runs; it's just silently wrong,
because nothing in the language says `id1`, `age1`, and `name1` belong
together.

#### Option B: Parallel Arrays

Instead of numbered variables, we use one array per property:

```cpp
int ids[3] = {1, 2, 3};
int ages[3] = {20, 21, 19};
string names[3] = {"Rahul", "Aman", "Simran"};
string gfNames[3] = {"Priya", "", "Karan"};

for (int i = 0; i < 3; i++)
{
    // We MUST remember that index i means the same student in
    // every single array. Nothing enforces that correspondence
    // except our own discipline while writing the loop.
    study(ids[i], ages[i], names[i]);
}
```

This is slightly less repetitive, but the underlying problem hasn't gone
away: `ids[i]`, `ages[i]`, and `names[i]` are only "the same student" because
*we* keep every array in sync by hand. If any one array gets sorted, filtered,
or updated independently of the others, the correspondence silently breaks.

**Note:** even at just 3 students, this code already feels messy and fragile.
At 100 students - with more properties and behaviours added over time - it
becomes genuinely unmanageable.

## Limitations of Functional Programming

Looking back at `messy-code.cpp`, we can now name exactly what's going wrong.

### 1. Doesn't Model Real-World Entities Well

A student is one real-world "thing." In our code, it's scattered across four
or more unrelated variables (`id`, `age`, `name`, `gfName`) and four or more
unrelated functions (`study`, `eat`, `sleep`, `hasGF`) with nothing in the
language tying them together as a single concept. The relationship between a
student and *their own* `study()` call has to be modeled entirely in the
programmer's head. This gets worse once we add related real-world entities
too - teachers, subjects, classrooms - each pulling in their own scattered
variables and functions with the same problem.

### 2. Adding New Data Requires Every Function to Be Modified

Right now every behaviour function already takes the full trio just to print
a message that mostly ignores it:

```cpp
void study(int id, int age, string name)
{
    cout << name << " (id: " << id << ", age: " << age << ") is Studying" << endl;
}

void eat(int id, int age, string name)
{
    cout << name << " is Eating" << endl;
}
```

Suppose we now add a new property, `numberOfSubjects`, to each student. Every
one of these functions - including `eat()`, which never uses it - must grow a
new parameter just to keep compiling:

```cpp
void study(int id, int age, string name, int numberOfSubjects)
{
    cout << name << " (id: " << id << ", age: " << age << ") is Studying" << endl;
}

void eat(int id, int age, string name, int numberOfSubjects) // unused here, but must still be threaded through
{
    cout << name << " is Eating" << endl;
}
```

And every call site - `study(id, age, name)`, `study(ids[i], ages[i],
names[i])`, and so on throughout `duplicateVariables()` and
`parallelArrays()` - must also be updated to pass it. One new piece of data
means touching every function in the file, whether that function needed the
data or not.

### 3. Global Data Has No Privacy

Look at `hasGF()` again - it takes **zero parameters** and just reads the
global `gfName` directly. And in the full file, there's also a `schoolName`
global and a `teach()` function:

```cpp
string schoolName = "DPS"; // meant only for students...

// This function has NOTHING to do with a student's personal life.
// Yet because schoolName is global,
// teach() can read and misuse ANY of it if it wanted to.
void teach()
{
    cout << "A teacher is taking a class at " << schoolName << endl;
    cout << "...and could just as easily print " << gfName << " if it wanted to." << endl;
}
```

`teach()` is meant to be a teacher-only function - it has no business knowing
a student's girlfriend's name. But because `gfName` is a global variable,
nothing in the language stops `teach()` (or any other function) from reading
or printing it anyway. There is no way to say "this data is private to the
student."

### 4. No Clear Boundaries Between Data and Behaviour

The student's properties (`id`, `age`, `name`, `gfName`) live at the top of
the file as loose globals. The student's behaviours (`study`, `eat`, `sleep`,
`hasGF`) live below as loose functions. Nothing marks any of them as
belonging to "Student" except naming convention and the programmer
remembering the connection. There's no boundary around the concept at all.

### 5. No Modularity - Code Becomes Monolithic

As we add more students, more teachers, more subjects - all handled the same
way, as more flat variables and more flat functions - everything piles into
one undifferentiated set of globals and functions with no sub-grouping. There
is no unit smaller than "the whole file" to reason about, test, or reuse.
Functional programming code like this can become monolithic and increasingly
difficult to maintain as it grows.

## Towards a Solution: The "Container" Idea

Imagine, instead, a single container - a box - that holds `id`, `name`, `age`,
and `gfName` together, *and* holds the behaviours `study()`, `eat()`,
`sleep()`, and `hasGF()` that act on them, all as one unit.

Filling in that container with real values is what makes something "a
student" - whoever holds a fully filled-in container has all the information
and behaviour tags that define a student.

This also fixes the privacy problem: if `gfName` is sealed *inside* the box,
only the box's own behaviours (like `hasGF()`) can reach it - unlike the
global `gfName` in `messy-code.cpp`, which `teach()` could read even though it
has no business doing so.

This "container" is exactly what the next chapter formally introduces as a
**class**, and a container filled in with real values is what we'll call an
**object**. Along the way, we'll also see how OOPS brings back the
**modularity** that functional programming lost - grouping related data and
behaviour into self-contained, reusable units instead of one flat pile of
globals and functions.
