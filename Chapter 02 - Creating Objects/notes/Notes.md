# Chapter 02 - Creating Objects

Chapter 01 established the vocabulary: a **class** is a blueprint, and an
**object** is that blueprint filled in with real values.

$$\text{Object} = \text{An Instance of a Class}$$

This chapter is about the mechanics of actually creating those objects in
C++.

## Roadmap: What Creating an Object Involves

Everything below happens in a fixed sequence of ideas, each building on the
last:

1. **Define the blueprint** - write the `class` itself (attributes + behaviours).
2. **Instantiate it** - create an **object**: an instance of that class.
3. **Constructor** - the special function that runs automatically the moment an object is created.
4. **Parameterised Constructor** - a better way to hand the constructor its initial values in one call.
5. **Copy Constructor** - build a new object by copying an existing one.
6. **Destructor** - the special function that runs automatically the moment an object is destroyed.
7. **Stack vs. Dynamic (Heap) Allocation** - and why a heap-allocated attribute needs extra care in both the destructor and the copy constructor.
8. **Object Life Cycle** - the full sequence, start to finish, tying every stage above together.

---

## 📌 Table of Contents

- [Chapter 02 - Creating Objects](#chapter-02---creating-objects)
  - [Roadmap: What Creating an Object Involves](#roadmap-what-creating-an-object-involves)
  - [📌 Table of Contents](#-table-of-contents)
  - [The Class: Writing the Blueprint](#the-class-writing-the-blueprint)
  - [Constructors](#constructors)
    - [The Default Constructor](#the-default-constructor)
    - [What a Constructor Actually Does](#what-a-constructor-actually-does)
  - [Destructors](#destructors)
    - [What a Destructor Actually Does](#what-a-destructor-actually-does)
    - [Destruction Order Is the Reverse of Creation Order](#destruction-order-is-the-reverse-of-creation-order)
  - [A Better Way to Build Objects: Parameterised Constructors](#a-better-way-to-build-objects-parameterised-constructors)
    - [The `this` Keyword](#the-this-keyword)
  - [Copy Constructors](#copy-constructors)
  - [Stack vs. Dynamic (Heap) Allocation](#stack-vs-dynamic-heap-allocation)
    - [Accessing Members: `.` vs `->`](#accessing-members--vs--)
    - [Manual Cleanup: You Must `delete` What You `new`](#manual-cleanup-you-must-delete-what-you-new)
  - [Why the Destructor Must Clean Up Dynamic Attributes](#why-the-destructor-must-clean-up-dynamic-attributes)
    - [Deep Copy: Why the Copy Constructor Also Needs to Care](#deep-copy-why-the-copy-constructor-also-needs-to-care)
  - [Object Life Cycle](#object-life-cycle)
  - [Key Implementation Rules & Gotchas](#key-implementation-rules--gotchas)
- [Source Code Walkthrough](#source-code-walkthrough)
  - [1. class-blueprint.cpp](#1-class-blueprintcpp)
  - [2. parameterised-constructor.cpp](#2-parameterised-constructorcpp)
  - [3. copy-constructor.cpp](#3-copy-constructorcpp)
  - [4. dynamic-allocation.cpp](#4-dynamic-allocationcpp)
- [Summary](#summary)

---

> 📄 **Source code for this chapter** lives in `coding/`, split one concept
> per file so each one only contains what's needed to demonstrate that idea:
>
> 1. [`1. class-blueprint.cpp`](../coding/1.%20class-blueprint.cpp)
> 2. [`2. parameterised-constructor.cpp`](../coding/2.%20parameterised-constructor.cpp)
> 3. [`3. copy-constructor.cpp`](../coding/3.%20copy-constructor.cpp)
> 4. [`4. dynamic-allocation.cpp`](../coding/4.%20dynamic-allocation.cpp)

---

## The Class: Writing the Blueprint

A class is just a `struct`-like container that tells C++ what an object of
that kind will look like - what data it carries and what it can do. It has
no values yet; it's a template, not a thing - `Student`, `Person`, `Car`,
whatever real-world entity we're modelling.

```cpp
class Student
{
public:
    // Attribute / Property / Data / State
    int id;
    int age;
    string name;

    // Behaviour / Method / Function
    void study() { /* ... */ }
};
```

- **Attributes / Properties / Data / State** - the variables that belong to
  the class (`id`, `age`, `name`).
- **Behaviours / Methods / Functions** - the functions that belong to the
  class (`study()`).
- **`public:`** - marks these members as reachable from outside the class
  (e.g. from `main()`). Chapter 03 (Encapsulation) covers what happens when
  members are hidden instead - for now, just know that `public` is what lets
  code like `s1.name = "yash";` compile.

```
+-------------------------------------------------------+
|                    CLASS: Student                     |
|-------------------------------------------------------|
|  [ Data / State ]                                     |
|  - id: int                                            |
|  - age: int                                           |
|  - name: string                                       |
|-------------------------------------------------------|
|  [ Behaviours ]                                       |
|  - study()                                            |
+-------------------------------------------------------+
```

---

## Constructors

A **constructor (ctor)** is a special function that runs **automatically the
instant an object is created**. It's how the Class blueprint actually turns
into a usable Object.

- Its name is always **identical to the class name** - `Student()` for
  class `Student`.
- It never has a return type, not even `void`.

### The Default Constructor

If we write a class and never declare *any* constructor ourselves, C++
silently inserts an empty one for us - the **default constructor**. Writing
it out explicitly just lets us see, in the output, exactly when it fires:

```cpp
Student()
{
    cout << "Default Constructor Called" << endl;
}
```

> 📄 See [`1. class-blueprint.cpp`](../coding/1.%20class-blueprint.cpp)

### What a Constructor Actually Does

Say we need `s1`, `s2`, `s3`, … - many Student objects, each with its own
`id`, `age`, and `name`. The constructor is what makes that possible: it
runs **once per object**, independently, so every object gets its own set of
attributes rather than sharing one.

```cpp
Student s1;   // Constructor runs -> prints "Default Constructor Called"
s1.name = "yash";
s1.age = 25;
s1.id = 6;

Student s2;   // Constructor runs AGAIN, completely independently of s1
s2.name = "john";
s2.age = 20;
s2.id = 7;
```

```
Default Constructor Called      <- from `Student s1;`
yash is Sleeping
Default Constructor Called      <- from `Student s2;`
john is Bunking
```

Every `Student` declaration triggers exactly one constructor call. That's
the rule to hold onto: **number of objects created === number of times the
constructor runs.**

---

## Destructors

A **destructor (dtor)** is the mirror image of a constructor: a special
function that runs **automatically the instant an object is destroyed** -
for a stack object, that means the moment it goes out of scope (e.g. when
`main()` reaches its closing brace).

- Same naming rule as constructors: identical to the class name.
- Prefixed with a tilde, `~` - so for `Student`, it's `~Student()`.
- Just like the constructor, if we don't write one, the compiler silently
  inserts a default (empty) one.

```cpp
~Student()
{
    cout << this->name << " - Default Destructor Called" << endl;
}
```

### What a Destructor Actually Does

When the program reaches `return 0;` in `main()`, every stack object created
inside it is torn down, and each one's destructor fires as that happens.
This is where any cleanup work for that object belongs.

### Destruction Order Is the Reverse of Creation Order

This is easy to get backwards, so it's worth stating precisely: stack
objects are destroyed in the **reverse** of the order they were created -
last created, first destroyed (LIFO).

```cpp
Student s1;   // created 1st
Student s2;   // created 2nd
// ... end of main() ...
```

```
Default Constructor Called   <- s1 created (1st)
Default Constructor Called   <- s2 created (2nd)
...
john - Default Destructor Called   <- s2 destroyed FIRST
yash - Default Destructor Called   <- s1 destroyed SECOND
```

```
CREATION ORDER:      s1  ->  s2
                       |       |
DESTRUCTION ORDER:    s2  <-  s1
                 (last-created is first-destroyed)
```

> 📄 Run [`1. class-blueprint.cpp`](../coding/1.%20class-blueprint.cpp)
> yourself and watch the destructor lines print in reverse of the constructor
> lines.

---

## A Better Way to Build Objects: Parameterised Constructors

Building `s1` in the examples above took four separate statements: one to
create it, three more to assign its attributes one at a time. That's fragile
- it's easy to forget an attribute and end up with a half-initialized
object. A **parameterised constructor** fixes this by accepting all the
values an object needs *as arguments to the constructor call itself*.

```cpp
Student(string name, int age, int id, float gpa)
{
    this->name = name;
    this->age = age;
    this->id = id;
    this->gpa = gpa;

    cout << this->name << " - Parameterised Constructor Called" << endl;
}
```

```cpp
// Old way - object exists momentarily with no valid data, then gets filled in by hand
Student s1;
s1.name = "yash";
s1.age = 25;
s1.id = 6;

// Better way - object is born already fully formed
Student s2("aman", 21, 7, 8.4f);
```

Both constructors can coexist on the same class - C++ picks whichever one
matches how you called it (an empty `Student s1;` calls the default one, a
`Student s2(...)` with arguments calls the parameterised one).

> 📄 See [`2. parameterised-constructor.cpp`](../coding/2.%20parameterised-constructor.cpp)

### The `this` Keyword

> **IMPORTANT:** `this` refers to the exact object a method is currently
> running on.

Inside the parameterised constructor above, the parameter is named `name`
and the attribute is also named `name` - deliberately, since they represent
the same idea. `this->name` disambiguates them: it means "the `name`
attribute that belongs to the object under construction," as opposed to the
plain `name`, which refers to the parameter.

```
Student s2("aman", 21, 7, 8.4f);
                |
                v
 inside the constructor, `this` == s2
 this->name = name;
   ^            ^
   |            +-- the incoming parameter "aman"
   +-- s2's own `name` attribute, now set to "aman"
```

`this` isn't unique to constructors - it works the same way inside any
method of a class, always pointing back to the object the method was called
on (`s1.study()` -> inside `study()`, `this` is `s1`).

---

## Copy Constructors

Suppose we want a new Student, `s4`, that starts out with exactly the same
data as an existing one, `s3`. Instead of retyping every value, we can copy
it directly from `s3` using a **copy constructor** - a constructor that
builds a new object out of an already-existing object of the same class.

```cpp
Student(const Student &source)
{
    this->name = source.name;
    this->age = source.age;
    this->id = source.id;
    this->gpa = source.gpa;

    cout << this->name << " - Copy Constructor Called" << endl;
}
```

- `this` refers to the **new** object being created (`s4` or `s5` below).
- `source` refers to the **existing** object being copied from (`s3`).
- `source` is a **reference** (`&`) - without it, C++ would need to copy
  `source` into the parameter first, which means calling the copy
  constructor again just to *enter* the copy constructor: infinite
  recursion. Passing by reference hands over the original object directly.
- `source` is **`const`** - this constructor only ever reads from the
  object it's copying; it has no business modifying it.

There are two equivalent ways to invoke it:

```cpp
Student s4(s3);   // direct-initialization form
Student s5 = s3;  // copy-initialization form - looks like assignment, isn't
```

Both lines call the copy constructor and pass `s3` as `source`; `s5 = s3` is
not an assignment here because `s5` doesn't exist yet - it's being defined.

```
     s3 (existing object)
       |
       |  field-by-field copy
       v
+--------------+     +--------------+
|  s4 (new)    |     |  s5 (new)    |
|  name = ...  |     |  name = ...  |
|  age  = ...  |     |  age  = ...  |
|  id   = ...  |     |  id   = ...  |
+--------------+     +--------------+
 independent objects - changing s4 later does not affect s3 or s5
```

> 📄 See [`3. copy-constructor.cpp`](../coding/3.%20copy-constructor.cpp)

---

## Stack vs. Dynamic (Heap) Allocation

Every object we've made so far -

```cpp
Student s3("yash", 25, 6, 9.0f);
```

- is allocated **on the stack**. Its lifetime is automatic: it's created
where it's declared, and destroyed automatically when that scope ends.

There's a second way: **dynamic (heap) allocation**, using `new`. Instead of
handing back the object itself, `new` hands back a **pointer** to an object
living on the heap:

```cpp
Student *s6 = new Student("kunal", 22, 8, 7.5f);
```

The parameterised constructor runs exactly as normal - `new` just changes
*where* the object lives and *how* we refer to it (through a pointer, `s6`,
rather than a plain variable).

### Accessing Members: `.` vs `->`

| Object kind | Declared as | Access attributes/methods with |
|---|---|---|
| Stack object | `Student s3(...)` | `s3.name`, `s3.study()` |
| Heap object (via pointer) | `Student *s6 = new Student(...)` | `s6->name`, `s6->study()` |

`->` is shorthand for "dereference the pointer, then access the member" -
`s6->name` means the same thing as `(*s6).name`.

### Manual Cleanup: You Must `delete` What You `new`

A stack object is destroyed for us automatically. A heap object is not -
there's no "end of scope" moment for something `new` created, so its
destructor never runs on its own. We have to trigger it ourselves:

```cpp
delete s6;
```

`delete` is what actually calls `s6`'s destructor and frees the memory `new`
allocated. Forget this line, and the object is **leaked**: its memory stays
reserved for the rest of the program's life, and its destructor never runs
at all.

> 📄 See [`4. dynamic-allocation.cpp`](../coding/4.%20dynamic-allocation.cpp)

---

## Why the Destructor Must Clean Up Dynamic Attributes

So far every attribute (`int`, `string`, `float`) has been a plain value
that C++ knows how to destroy on its own. But what if an *attribute itself*
is a pointer to memory the object allocated dynamically?

```cpp
class Student
{
public:
    float *gpa; // the object OWNS this heap memory
    // ...

    Student(string name, int age, int id, float gpa)
    {
        // ...
        this->gpa = new float(gpa); // dynamic memory allocation for this attribute
    }
};
```

Here, `new float(gpa)` allocates a single `float` on the heap and stores its
address in the `gpa` pointer. The object's other attributes (`id`, `age`,
`name`) are destroyed automatically when the object is destroyed - but the
`float` that `gpa` points to is **not**. The default destructor only knows
how to clean up the pointer variable itself (a few bytes holding an
address); it has no idea it's also responsible for the memory that address
points to.

So we have to say so explicitly, in our own destructor:

```cpp
~Student()
{
    cout << this->name << " - Default Destructor Called" << endl;
    delete this->gpa; // without this, the float leaks
}
```

**This is exactly why we get in the habit of always writing a destructor
once a class owns any dynamic memory**: it's the one guaranteed place to
release what the constructor allocated.

### Deep Copy: Why the Copy Constructor Also Needs to Care

The moment a class holds a pointer like `gpa`, the copy constructor from
earlier is no longer safe as written. If it just copied the pointer's
*address*:

```cpp
this->gpa = source.gpa; // WRONG once gpa is a pointer - copies the address, not the value
```

then the new object and `source` would both point at the **same** heap
`float`. Two objects, one shared piece of memory - and both of their
destructors will eventually call `delete` on it:

```
 s3.gpa ---+
           +---> [ float on heap ]   <-- deleted TWICE when both s3 and its
 s4.gpa ---+                              copy are destroyed: undefined behaviour
```

The fix is a **deep copy**: allocate a brand-new `float` for the new object,
and copy the *value* `source.gpa` points to, not the pointer itself:

```cpp
Student(const Student &source)
{
    // ...
    this->gpa = new float(*source.gpa); // new heap float, value copied from source
}
```

```
 s3.gpa ---> [ float #1 on heap ]
 s4.gpa ---> [ float #2 on heap ]   <-- independent copy, safe to delete separately
```

Now each object owns its own `float`, and each destructor can safely
`delete` its own copy without touching the other's.

> 📄 See [`4. dynamic-allocation.cpp`](../coding/4.%20dynamic-allocation.cpp) for the
> full working version, including the corrected copy constructor.

---

## Object Life Cycle

Pulling every section above together, every object goes through the same
sequence of stages:

```
 1. Object declared          Student s1;  /  Student *s6 = new Student(...);
             |
             v
 2. Constructor runs         attributes are set (by hand, or via parameters)
             |
             v
 3. Object is used           attributes accessed, methods called
             |
             v
 4. Destructor runs          stack: automatic, at end of scope, reverse order
                              heap:  only when `delete` is called explicitly
             |
             v
 5. Memory reclaimed         including any dynamically allocated attributes,
                              IF the destructor explicitly deletes them
```

---

## Key Implementation Rules & Gotchas

1. **The Free Default Constructor Disappears:** C++ auto-generates a default constructor only while you write none. The moment you define a parameterised constructor, the free `Student()` is gone, and `Student s1;` stops compiling unless you declare it back explicitly.
2. **Destruction Is the Reverse of Creation:** Stack objects are destroyed in the exact reverse of the order they were created. The object declared last is destroyed first.
3. **`this` Exists to Break Ties:** When a parameter shares a name with an attribute, the parameter wins inside the function body. `this->name = name;` is what tells C++ which of the two you mean.
4. **The Copy Constructor Must Take a Reference:** `ClassName(const ClassName &source)` takes its argument by reference deliberately. Passing by value would itself require a copy, which would call the copy constructor, forever - infinite recursion. The `const` additionally guarantees the source is never modified while being copied.
5. **What You `new`, You Must `delete`:** Heap objects are never cleaned up automatically. Forget the `delete` and the memory leaks *and* the destructor never runs at all.
6. **A Pointer Attribute Costs You Twice:** An attribute allocated with `new` must be released in the destructor *and* deep-copied in the copy constructor. The default field-by-field copy duplicates the **address**, not the value, leaving two objects owning the same memory and eventually double-freeing it.
7. **Use `->` on Pointers, `.` on Objects:** `s3.study()` for a stack object; `s6->study()` for a pointer to a heap object. `->` is shorthand for dereference-then-access.

---

## Source Code Walkthrough

### 1. class-blueprint.cpp

From [`coding/1. class-blueprint.cpp`](../coding/1.%20class-blueprint.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Class: Student (Writing the Blueprint)
// =========================================================================
// A class is a blueprint/template describing what data and behaviours
// every Student object will possess.
// =========================================================================
class Student
{
public:
    // ---------------- Attributes / State / Properties ----------------
    int id;
    int age;
    string name;

    // ---------------- Default Constructor (ctor) ----------------
    // Runs automatically the instant an object is created on stack or heap.
    // If omitted, C++ generates a default constructor implicitly.
    Student()
    {
        cout << "Default Constructor Called" << endl;
    }

    // ---------------- Behaviours / Methods / Functions ----------------
    void study()
    {
        cout << this->name << " is Studying" << endl;
    }

    void sleep()
    {
        cout << this->name << " is Sleeping" << endl;
    }

    void bunk()
    {
        cout << this->name << " is Bunking" << endl;
    }

    // ---------------- Destructor (dtor) ----------------
    // Runs automatically when an object goes out of scope and is destroyed.
    ~Student()
    {
        cout << this->name << " - Default Destructor Called" << endl;
    }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- 1. Creating First Object (s1) ----------------
    // Default ctor runs, then attributes are assigned manually.
    Student s1;
    s1.name = "yash";
    s1.age = 25;
    s1.id = 6;
    s1.sleep();

    // ---------------- 2. Creating Second Object (s2) ----------------
    // An independent instance in memory with its own state.
    Student s2;
    s2.name = "john";
    s2.age = 20;
    s2.id = 7;
    s2.bunk();

    // ---------------- 3. Displaying Object States ----------------
    cout << s1.id << ", " << s1.age << ", " << s1.name << endl;
    cout << s2.id << ", " << s2.age << ", " << s2.name << endl;

    // ---------------- 4. Object Destruction ----------------
    // Stack objects are destroyed in REVERSE order of creation (s2, then s1).
    return 0;
}
```

---

### 2. parameterised-constructor.cpp

From [`coding/2. parameterised-constructor.cpp`](../coding/2.%20parameterised-constructor.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Class: Student (Parameterised Constructor & 'this' Pointer)
// =========================================================================
// Initializes object attributes at the instant of creation.
// =========================================================================
class Student
{
public:
    // ---------------- Attributes ----------------
    int id;
    int age;
    string name;
    float gpa;

    // ---------------- Default Constructor ----------------
    Student()
    {
        cout << "Default Constructor Called" << endl;
    }

    // ---------------- Parameterised Constructor ----------------
    // Takes initial values directly during object instantiation.
    // 'this' resolves ambiguity between member attributes and parameter names.
    Student(string name, int age, int id, float gpa)
    {
        this->name = name;
        this->age = age;
        this->id = id;
        this->gpa = gpa;

        cout << this->name << " - Parameterised Constructor Called" << endl;
    }

    // ---------------- Behaviours / Methods ----------------
    void study()
    {
        cout << this->name << " is Studying" << endl;
    }

    // ---------------- Destructor ----------------
    ~Student()
    {
        cout << this->name << " - Default Destructor Called" << endl;
    }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- 1. Default Initialization ----------------
    Student s1;
    s1.name = "yash";
    s1.age = 25;
    s1.id = 6;

    // ---------------- 2. Parameterised Initialization ----------------
    // All attributes initialized atomically in one step.
    Student s2("aman", 21, 7, 8.4f);

    // ---------------- 3. Method Invocations ----------------
    s1.study();
    s2.study();

    // ---------------- 4. Attribute Output ----------------
    cout << s1.id << ", " << s1.age << ", " << s1.name << endl;
    cout << s2.id << ", " << s2.age << ", " << s2.name << ", " << s2.gpa << endl;

    return 0;
}
```

---

### 3. copy-constructor.cpp

From [`coding/3. copy-constructor.cpp`](../coding/3.%20copy-constructor.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Class: Student (Copy Constructor & Pass-By-Const-Reference)
// =========================================================================
// Creates a new independent object by copying an existing object's state.
// =========================================================================
class Student
{
public:
    // ---------------- Attributes ----------------
    int id;
    int age;
    string name;
    float gpa;

    // ---------------- Parameterised Constructor ----------------
    Student(string name, int age, int id, float gpa)
    {
        this->name = name;
        this->age = age;
        this->id = id;
        this->gpa = gpa;

        cout << this->name << " - Parameterised Constructor Called" << endl;
    }

    // ---------------- Copy Constructor ----------------
    // Builds a NEW object by copying fields from an existing object (`source`).
    // Passed by const reference (&) to avoid infinite recursion and prevent mutation.
    Student(const Student &source)
    {
        this->name = source.name;
        this->age = source.age;
        this->id = source.id;
        this->gpa = source.gpa;

        cout << this->name << " - Copy Constructor Called" << endl;
    }

    // ---------------- Behaviours / Methods ----------------
    void study()
    {
        cout << this->name << " is Studying" << endl;
    }

    // ---------------- Destructor ----------------
    ~Student()
    {
        cout << this->name << " - Default Destructor Called" << endl;
    }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- 1. Original Object (s3) ----------------
    Student s3("yash", 25, 6, 9.0f);

    // ---------------- 2. Copy Constructor Invocations ----------------
    Student s4(s3);  // Direct initialization form
    Student s5 = s3; // Copy initialization form

    // ---------------- 3. Mutation Independence ----------------
    // s4 is an independent object; mutating s4 does not affect s3 or s5.
    s4.name = "yash-copy";
    cout << s3.name << ", " << s4.name << ", " << s5.name << endl;

    return 0;
}
```

---

### 4. dynamic-allocation.cpp

From [`coding/4. dynamic-allocation.cpp`](../coding/4.%20dynamic-allocation.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Class: Student (Dynamic Allocation, Deep Copy & Destructor Cleanup)
// =========================================================================
// Demonstrates heap allocation of attributes and dynamic objects using new/delete.
// =========================================================================
class Student
{
public:
    // ---------------- Attributes ----------------
    int id;
    int age;
    string name;
    float *gpa; // Dynamically allocated attribute on Heap

    // ---------------- Parameterised Constructor ----------------
    Student(string name, int age, int id, float gpa)
    {
        this->name = name;
        this->age = age;
        this->id = id;
        this->gpa = new float(gpa); // Allocate heap memory for float

        cout << this->name << " - Parameterised Constructor Called" << endl;
    }

    // ---------------- Copy Constructor (Deep Copy) ----------------
    // Allocates separate heap memory for the new object and copies the value.
    // Avoids shallow copy dangling pointers and double-free crashes.
    Student(const Student &source)
    {
        this->name = source.name;
        this->age = source.age;
        this->id = source.id;
        this->gpa = new float(*source.gpa); // Deep copy: fresh heap allocation

        cout << this->name << " - Copy Constructor Called" << endl;
    }

    // ---------------- Behaviours / Methods ----------------
    void study()
    {
        cout << this->name << " is Studying" << endl;
    }

    // ---------------- Destructor (Explicit Resource Cleanup) ----------------
    // Must delete dynamically allocated attributes to prevent memory leaks.
    ~Student()
    {
        cout << this->name << " - Default Destructor Called" << endl;
        delete this->gpa; // Free allocated heap memory
    }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- 1. Stack Allocation (Automatic Lifetime) ----------------
    // Lifetime managed by stack scope; accessed using '.' operator.
    Student s3("yash", 25, 6, 9.0f);
    cout << s3.id << ", " << s3.age << ", " << s3.name << ", " << *s3.gpa << endl;

    // ---------------- 2. Heap / Dynamic Allocation (Manual Lifetime) ----------------
    // 'new' allocates Student on Heap and returns a pointer; accessed with '->'.
    Student *s6 = new Student("kunal", 22, 8, 7.5f);

    cout << s6->id << ", " << s6->age << ", " << s6->name << ", " << *s6->gpa << endl;
    s6->study();

    // ---------------- 3. Manual Cleanup for Dynamic Object ----------------
    // Dynamic objects are not destroyed automatically; 'delete' triggers destructor.
    delete s6;

    return 0;
}
```

---

## Summary

1. **Constructor** - runs automatically once per object, at creation; same
   name as the class; a default one is auto-generated if we write none.
2. **Destructor** - runs automatically once per object, at destruction; same
   name prefixed with `~`; also auto-generated if omitted. Stack objects are
   destroyed in **reverse** of creation order.
3. **Parameterised Constructor** - lets an object be built fully-formed in
   one call, using `this` to distinguish parameters from attributes of the
   same name.
4. **Copy Constructor** - `ClassName(const ClassName &source)` - builds a
   new object from an existing one, field by field. Reference avoids
   infinite recursion; `const` prevents modifying the source.
5. **Stack vs. Heap** - stack objects (`Student s3(...)`) are cleaned up
   automatically; heap objects (`Student *s6 = new Student(...)`) must be
   manually `delete`d, or they leak, and their destructor never runs.
6. **Dynamic Attributes Need Manual Cleanup, Twice Over** - a pointer
   attribute allocated with `new` must be `delete`d in the destructor, and
   **deep-copied** (not pointer-copied) in the copy constructor - otherwise
   two objects end up owning, and eventually double-freeing, the same
   memory.

---

<!-- chapter-nav -->

| Previous | Next |
| :--- | ---: |
| [&larr; Chapter 01 - Intro to OOPS](../../Chapter%2001%20-%20Intro%20to%20OOPS/notes/Notes.md) | [Chapter 03 - Encapsulation &rarr;](../../Chapter%2003%20-%20Encapsulation/notes/Notes.md) |
