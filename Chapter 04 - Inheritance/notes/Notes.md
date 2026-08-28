# Chapter 04 - Inheritance

Inheritance is the third classical pillar of Object-Oriented Programming. Chapter 01 introduced the idea of bundling data and behaviour into a single blueprint, Chapter 02 explored the lifecycle mechanics of constructing and destroying objects, and Chapter 03 established the **security boundaries** (`public`, `private`, `protected`) that govern an object. Chapter 04 now asks a different question: *what happens when two classes share most of their state and behaviour?*

The answer is **Inheritance** - the mechanism that lets one class acquire the attributes and behaviours of another class, and then extend them.

$$\text{Inheritance} = \text{Reuse of Parent State and Behaviour} + \text{Child-Specific Extension}$$

---

## 📌 Table of Contents

- [What is Inheritance?](#what-is-inheritance)
  - [The Real-World Analogy](#the-real-world-analogy)
  - [Base Class and Derived Class Terminology](#base-class-and-derived-class-terminology)
  - [The IS-A Relationship](#the-is-a-relationship)
- [Why Inheritance Exists: The Duplication Problem](#why-inheritance-exists-the-duplication-problem)
  - [Life Without Inheritance](#life-without-inheritance)
  - [Life With Inheritance](#life-with-inheritance)
- [Syntax of Inheritance in C++](#syntax-of-inheritance-in-c)
  - [The Inheritance Mode (Access Specifier)](#the-inheritance-mode-access-specifier)
  - [Visual Architecture: What the Child Actually Owns](#visual-architecture-what-the-child-actually-owns)
- [Constructor and Destructor Chaining](#constructor-and-destructor-chaining)
  - [Why the Parent Constructor Runs First](#why-the-parent-constructor-runs-first)
  - [The Member Initializer List](#the-member-initializer-list)
  - [Destruction Happens in Exact Reverse Order](#destruction-happens-in-exact-reverse-order)
  - [Visual Architecture: The Construction and Destruction Stack](#visual-architecture-the-construction-and-destruction-stack)
- [Access Specifiers Under Inheritance](#access-specifiers-under-inheritance)
  - [Private Members Are Inherited but Not Accessible](#private-members-are-inherited-but-not-accessible)
  - [The Getter Workaround](#the-getter-workaround)
  - [Protected: The Specifier Built for Inheritance](#protected-the-specifier-built-for-inheritance)
  - [Access Matrix Under Inheritance](#access-matrix-under-inheritance)
- [Extensibility and Hierarchical Inheritance](#extensibility-and-hierarchical-inheritance)
  - [One Parent, Many Children](#one-parent-many-children)
  - [Visual Architecture: The Vehicle Hierarchy](#visual-architecture-the-vehicle-hierarchy)
  - [Why This Is the Real Payoff](#why-this-is-the-real-payoff)
- [Key Implementation Rules & Gotchas](#key-implementation-rules--gotchas)
- [Source Code Walkthrough](#source-code-walkthrough)
  - [1. single-inheritance.cpp](#1-single-inheritancecpp)
  - [2. private-members-in-inheritance.cpp](#2-private-members-in-inheritancecpp)
  - [3. protected-members.cpp](#3-protected-memberscpp)
  - [4. extensibility-hierarchical.cpp](#4-extensibility-hierarchicalcpp)
- [Summary](#summary)

---

> 📄 **Source Code Reference**: All executable C++ source files for this chapter are available in the `coding/` directory:
>
> 1. [`1. single-inheritance.cpp`](../coding/1.%20single-inheritance.cpp) - Basic single inheritance: `Car : public Vehicle`, inherited attributes and methods, constructor and destructor chaining.
> 2. [`2. private-members-in-inheritance.cpp`](../coding/2.%20private-members-in-inheritance.cpp) - A `private` base attribute is inherited but blocked inside the child; the public getter is the legal route.
> 3. [`3. protected-members.cpp`](../coding/3.%20protected-members.cpp) - `protected` unlocks direct access for the child while still blocking the outside world.
> 4. [`4. extensibility-hierarchical.cpp`](../coding/4.%20extensibility-hierarchical.cpp) - One `Vehicle` base extended by two independent children, `Car` and `Bike`.

---

## What is Inheritance?

**Inheritance** is the mechanism by which one class (the **child**) acquires all the attributes and behaviours of another class (the **parent**), and is then free to add its own.

The child does not copy the parent's code. The child *contains* the parent. Every `Car` object physically carries a complete `Vehicle` sub-object inside it.

### The Real-World Analogy

> "A Car **is a** Vehicle. A Bike **is a** Vehicle. Both of them start an engine, both of them have a name, a model and a number of tyres. Only the extras differ - a Car has doors and a transmission, a Bike has a handlebar style and a suspension type."

Everything that is true of *every* vehicle belongs in `Vehicle`. Everything that is true of *only cars* belongs in `Car`. That single sentence is the entire design rule of inheritance.

### Base Class and Derived Class Terminology

The same two roles go by several interchangeable names:

| Role | Also Called | In Our Example |
| :--- | :--- | :--- |
| **Base Class** | Parent Class, Super Class | `Vehicle` |
| **Derived Class** | Child Class, Sub Class | `Car`, `Bike` |

### The IS-A Relationship

Inheritance models an **IS-A** relationship, and this is the test you apply before writing `:` in a class header:

```
    Car  IS-A  Vehicle    ✅  -> inheritance is correct
    Bike IS-A  Vehicle    ✅  -> inheritance is correct
    Car  IS-A  Engine     ❌  -> a Car HAS-A Engine, not IS-A (use composition)
```

If the sentence "Child IS-A Parent" does not read as plain English truth, inheritance is the wrong tool.

---

## Why Inheritance Exists: The Duplication Problem

### Life Without Inheritance

Suppose we model `Car` and `Bike` as two unrelated classes. Both need a name, a model, a tyre count, and both need to start and stop an engine:

```
        WITHOUT INHERITANCE (Duplicated Code)
+---------------------------+   +---------------------------+
|        class Car          |   |        class Bike         |
|---------------------------|   |---------------------------|
|  name                     |   |  name                     |   <-- duplicated
|  model                    |   |  model                    |   <-- duplicated
|  numberOfTyres            |   |  numberOfTyres            |   <-- duplicated
|  startEngine()            |   |  startEngine()            |   <-- duplicated
|  stopEngine()             |   |  stopEngine()             |   <-- duplicated
|---------------------------|   |---------------------------|
|  numberOfDoors            |   |  handleBarStyle           |
|  transmissionType         |   |  suspensionType           |
|  StartAC()                |   |  wheelie()                |
+---------------------------+   +---------------------------+

Problem: fix a bug in startEngine() and you must fix it in EVERY class.
```

Add a `Truck`, a `Bus`, and a `Tractor`, and the same five members get copy-pasted five more times. A single change to engine logic now means five edits, and the day you forget one of them, the classes silently disagree.

### Life With Inheritance

```
              WITH INHERITANCE (Written Once, Reused Everywhere)

                    +---------------------------+
                    |      class Vehicle        |   <-- written ONCE
                    |---------------------------|
                    |  name                     |
                    |  model                    |
                    |  numberOfTyres            |
                    |  startEngine()            |
                    |  stopEngine()             |
                    +---------------------------+
                                 ▲
                 ┌───────────────┴───────────────┐
                 │ : public Vehicle              │ : public Vehicle
    +---------------------------+   +---------------------------+
    |        class Car          |   |        class Bike         |
    |---------------------------|   |---------------------------|
    |  numberOfDoors            |   |  handleBarStyle           |
    |  transmissionType         |   |  suspensionType           |
    |  StartAC()                |   |  wheelie()                |
    +---------------------------+   +---------------------------+
       (only the EXTRAS remain)        (only the EXTRAS remain)
```

The two headline benefits:

1. **Code Reusability:** The shared members are written once in `Vehicle` and reused by every child, with zero duplication.
2. **Extensibility:** A new vehicle type costs one new small class. `Vehicle` itself is never touched, so nothing that already works can break.

---

## Syntax of Inheritance in C++

```cpp
class Car : public Vehicle
{
    // Car's own extra members
};
```

Read the header as three parts:

```
    class   Car    :    public    Vehicle
            ▲           ▲         ▲
            │           │         └── Base Class (Parent)
            │           └──────────── Inheritance Mode (access specifier)
            └──────────────────────── Derived Class (Child)
```

### The Inheritance Mode (Access Specifier)

The mode written between the `:` and the parent name controls how the parent's members are re-labelled inside the child. We use **`public` mode** throughout this chapter, and its rule is the simplest one:

> **`public` mode**: private members are inherited as private, protected members are inherited as protected, and public members are inherited as public.

In other words, `public` inheritance changes nothing - every member keeps the visibility the parent gave it. This is why `public` is the mode used in almost all real-world IS-A modelling.

| Inheritance Mode | Parent `public` becomes | Parent `protected` becomes | Parent `private` becomes |
| :--- | :---: | :---: | :---: |
| `public` | `public` | `protected` | Not accessible |
| `protected` | `protected` | `protected` | Not accessible |
| `private` | `private` | `private` | Not accessible |

> [!NOTE]
> In every mode, the parent's `private` members are **inherited** (they occupy memory inside the child object) but are **never directly accessible** to the child.

### Visual Architecture: What the Child Actually Owns

```
=============================================================================
                     MEMORY LAYOUT OF A SINGLE Car OBJECT
=============================================================================

        Car A("Maruti", "LXI", 4, 4, "Manual");

    ┌─────────────────────────────────────────────────────────────────────┐
    │                          Car OBJECT  'A'                            │
    │                                                                     │
    │   ┌─────────────────────────────────────────────────────────────┐   │
    │   │        INHERITED Vehicle SUB-OBJECT (built first)           │   │
    │   │                                                             │   │
    │   │   Attributes:              Methods:                         │   │
    │   │   ├── name  = "Maruti"     ├── startEngine()                │   │
    │   │   ├── model = "LXI"        └── stopEngine()                 │   │
    │   │   └── numberOfTyres = 4                                     │   │
    │   └─────────────────────────────────────────────────────────────┘   │
    │                                                                     │
    │   ┌─────────────────────────────────────────────────────────────┐   │
    │   │        Car'S OWN EXTENSION (built second)                   │   │
    │   │                                                             │   │
    │   │   Attributes:                    Methods:                   │   │
    │   │   ├── numberOfDoors = 4          └── StartAC()              │   │
    │   │   └── transmissionType = "Manual"                           │   │
    │   └─────────────────────────────────────────────────────────────┘   │
    └─────────────────────────────────────────────────────────────────────┘

    A.startEngine();  ──► reaches into the inherited Vehicle sub-object
    A.StartAC();      ──► Car's own method, and it can read 'name' from above
=============================================================================
```

---

## Constructor and Destructor Chaining

Creating one `Car` object runs **two** constructors, in a fixed order:

```cpp
Car A("Maruti", "LXI", 4, 4, "Manual");
```

produces:

```
Inside Vehicle ctor        <-- parent first
Inside Car ctor            <-- child second
```

### Why the Parent Constructor Runs First

The `Car` constructor body is free to use `name`, `model`, and `numberOfTyres` - members that belong to `Vehicle`. Those members must already exist and already be initialised before the `Car` body starts running. Therefore C++ guarantees the parent is fully constructed first, then the child layers itself on top.

**Rule:** Build the foundation before the floors above it.

### The Member Initializer List

Because `Vehicle` has no default (zero-argument) constructor - it only has a parameterised one - the child must explicitly say *which* parent constructor to call and *what* to pass it. That is the job of the **member initializer list**, the part after the colon in the child's constructor:

```cpp
Car(string _name, string _model, int _tyres, int _doors, string _transmission) : Vehicle(_name, _model, _tyres)
{
    cout << "Inside Car ctor" << endl;
    this->numberOfDoors = _doors;
    this->transmissionType = _transmission;
}
```

Read it as:
1. The child ctor accepts **all five** values - three belonging to `Vehicle`, two belonging to `Car`.
2. `: Vehicle(_name, _model, _tyres)` forwards the parent's three values upward and runs the parent ctor.
3. Only after the parent finishes does the `Car` body execute and assign its own two attributes.

> [!IMPORTANT]
> If you omit the `: Vehicle(...)` call, the compiler tries to invoke `Vehicle`'s *default* constructor. Since `Vehicle` does not define one, compilation fails with `no matching function for call to 'Vehicle::Vehicle()'`.

### Destruction Happens in Exact Reverse Order

When the object goes out of scope, destructors fire in the mirror image of construction:

```
Default Dtor Called for Car !!     <-- child first
dtor of Vehicle called !!          <-- parent last
```

This is the only order that is safe: the child's destructor may still need the parent's data while cleaning up, so the parent must survive until the child is completely finished.

### Visual Architecture: The Construction and Destruction Stack

```
=============================================================================
             LIFECYCLE OF   Car A("Maruti", "LXI", 4, 4, "Manual");
=============================================================================

   CONSTRUCTION (top-down)                DESTRUCTION (bottom-up)
   ───────────────────────                ───────────────────────

   1. Vehicle ctor  ──┐                          ┌──  4. Vehicle dtor
      "Inside          │                         │      "dtor of Vehicle
       Vehicle ctor"   │                         │       called !!"
                       ▼                         │
   2. Car ctor      ──►│  [ OBJECT ALIVE ]  ─────┘
      "Inside Car      │        │
       ctor"           │        └──►  3. Car dtor
                       ▼                 "Default Dtor Called for Car !!"

   Parent is born FIRST and dies LAST - it is the foundation of the object.
=============================================================================
```

---

## Access Specifiers Under Inheritance

Chapter 03 introduced `public`, `private`, and `protected`. Inheritance is where the third one finally earns its existence.

### Private Members Are Inherited but Not Accessible

Suppose `name` is `private` inside `Vehicle`:

```cpp
class Vehicle
{
    string name;   // PRIVATE by default in a class
public:
    string model;
    int numberOfTyres;
    // ...
};
```

Now inside `Car`:

```cpp
void StartAC()
{
    // cout << name;   // COMPILATION ERROR: 'name' is private in Vehicle
}
```

The attribute genuinely exists inside every `Car` object - it was allocated, and the `Vehicle` constructor filled it in. But the compiler refuses to let `Car` read it. **Private means private to the class that declared it, and nobody else - not even a child.**

```
+---------------------------------------------------------------+
|                     class Vehicle                             |
|                                                               |
|    private:  name    🔒  <-- sealed vault, child has no key   |
|    public:   model, numberOfTyres, startEngine(), getName()   |
+---------------------------------------------------------------+
                              ▲
                              │ : public Vehicle
+---------------------------------------------------------------+
|                       class Car                               |
|                                                               |
|    ❌ name          - inherited, but ACCESS DENIED            |
|    ✅ model         - readable                                |
|    ✅ getName()     - readable, and it returns 'name' legally  |
+---------------------------------------------------------------+
```

### The Getter Workaround

The parent already solved this problem in Chapter 03: expose a **public getter**. The getter is a member of `Vehicle`, so *it* is allowed to touch `name`, and the child inherits the getter as public:

```cpp
// Inside Vehicle
string getName()
{
    return this->name;
}

// Inside Car - the legal route in
void StartAC()
{
    cout << "AC has Started of " << getName() << endl;
}
```

This works, and it is perfectly correct design - but notice the cost. Every private attribute the child needs demands another accessor method on the parent. When the child is a genuine family member that legitimately needs the parent's internals, there is a better specifier.

### Protected: The Specifier Built for Inheritance

Change `name` from `private` to `protected`:

```cpp
class Vehicle
{
protected:
    string name;      // child can touch it, the outside world cannot
public:
    string model;
    // ...
};
```

Now `Car` may use `name` directly, with no getter in between:

```cpp
void StartAC()
{
    cout << "AC has Started of " << name << endl;   // legal now
}
```

But `main()` still cannot:

```cpp
Car A("Maruti", "LXI", 4, 4, "Manual");
// cout << A.name;   // COMPILATION ERROR: 'name' is protected
```

> **`protected` is the exact middle ground: private to the outside world, public to the family.**

If code *outside* the hierarchy needs the value, the child exposes its own getter - `Car` is allowed to read `name`, so `Car` is allowed to return it:

```cpp
// Inside Car - re-exposing the protected base attribute
string getName()
{
    return this->name;
}
```

```
=============================================================================
                  THE THREE SPECIFIERS SEEN FROM INHERITANCE
=============================================================================

                          class Vehicle (Parent)
    ┌─────────────────────────────────────────────────────────────────────┐
    │  public:     model         ── visible to Child ✅  and World ✅     │
    │  protected:  name          ── visible to Child ✅  and World ❌     │
    │  private:    engineNumber  ── visible to Child ❌  and World ❌     │
    └─────────────────────────────────────────────────────────────────────┘
             │                                       │
             │ inherited                             │ blocked at the
             ▼                                       ▼ class boundary
    ┌──────────────────────────┐          ┌──────────────────────────┐
    │      class Car (Child)   │          │   main() / Outside World │
    │   ✅ model               │          │   ✅ A.model             │
    │   ✅ name                │          │   ❌ A.name              │
    │   ❌ engineNumber        │          │   ❌ A.engineNumber      │
    └──────────────────────────┘          └──────────────────────────┘
=============================================================================
```

### Access Matrix Under Inheritance

| Access Specifier in Parent | Inside Parent | Inside Child (Derived) | Outside / `main()` |
| :--- | :---: | :---: | :---: |
| `public` | ✅ Yes | ✅ Yes | ✅ Yes |
| `protected` | ✅ Yes | ✅ Yes | ❌ No |
| `private` | ✅ Yes | ❌ No | ❌ No |

---

## Extensibility and Hierarchical Inheritance

### One Parent, Many Children

**Hierarchical inheritance** is the pattern where a single base class is extended by two or more independent derived classes. `Vehicle` is written once; `Car` and `Bike` each inherit it and pull in completely different directions:

```cpp
class Car : public Vehicle
{
public:
    int numberOfDoors;
    string transmissionType;
    void StartAC() { cout << "AC has Started of " << name << endl; }
};

class Bike : public Vehicle
{
protected:
    string handleBarStyle;
    string suspensionType;
public:
    void wheelie() { cout << "Wheelie karri hai " << name << endl; }
};
```

`Car` gets doors, a transmission, and an air conditioner. `Bike` gets a handlebar style, a suspension type, and a wheelie. Neither knows the other exists. Both start and stop an engine using the exact same code, written exactly once.

### Visual Architecture: The Vehicle Hierarchy

```
=============================================================================
                    HIERARCHICAL INHERITANCE: ONE BASE, MANY CHILDREN
=============================================================================

                        ┌─────────────────────────────┐
                        │      BASE: Vehicle          │
                        │─────────────────────────────│
                        │  protected:                 │
                        │    name, model,             │
                        │    numberOfTyres            │
                        │  public:                    │
                        │    startEngine()            │
                        │    stopEngine()             │
                        └──────────────┬──────────────┘
                                       │
                   ┌───────────────────┴───────────────────┐
                   │ : public Vehicle                      │ : public Vehicle
                   ▼                                       ▼
    ┌─────────────────────────────┐         ┌─────────────────────────────┐
    │       DERIVED: Car          │         │       DERIVED: Bike         │
    │─────────────────────────────│         │─────────────────────────────│
    │  public:                    │         │  protected:                 │
    │    numberOfDoors            │         │    handleBarStyle           │
    │    transmissionType         │         │    suspensionType           │
    │    StartAC()                │         │  public:                    │
    │                             │         │    wheelie()                │
    │  + everything from Vehicle  │         │  + everything from Vehicle  │
    └─────────────────────────────┘         └─────────────────────────────┘

              ┌ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┐
              │  FUTURE: Truck, Bus, Tractor ...          │
              │  each costs ONE new class.                │
              │  Vehicle is never edited, so nothing      │
              │  that already works can break.            │
              └ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ─ ┘
=============================================================================
```

### Why This Is the Real Payoff

Running the hierarchical example makes the reuse visible in the output. Creating a `Car` and then a `Bike` produces:

```
Inside Vehicle ctor          <-- Vehicle ctor runs for the Car
Inside Car ctor
Engine Started               <-- Vehicle's code
AC has Started of Maruti     <-- Car's own code
Engine Stopped               <-- Vehicle's code

Inside Vehicle ctor          <-- the SAME Vehicle ctor runs for the Bike
Bike ctor called !!
Engine Started               <-- the SAME Vehicle code, zero duplication
Wheelie karri hai Hero       <-- Bike's own code
Engine Stopped

Bike dtor called !!          <-- Bike destroyed first (declared last)
dtor of Vehicle called !!
Default Dtor Called for Car !!
dtor of Vehicle called !!
```

Two objects, two very different vehicles, one shared engine implementation. That is **extensibility**: the system grows outward at the leaves while the trunk stays untouched.

---

## Key Implementation Rules & Gotchas

1. **Apply the IS-A Test First:** Write `class Child : public Parent` only when "Child IS-A Parent" is literally true. If the relationship is really "has a", use composition (a member object) instead.
2. **Public Mode Preserves Visibility:** With `: public Parent`, every inherited member keeps the exact access level the parent gave it. Public stays public, protected stays protected.
3. **Private Is Inherited but Sealed:** A private base member occupies memory in the child object but is unreachable from the child's code. Only a public/protected member function of the parent can hand it over.
4. **Use `protected` for Family Data:** When the child legitimately needs a parent attribute, `protected` avoids a getter chain while still blocking the outside world.
5. **Parent Constructs First, Destructs Last:** Construction runs base → derived; destruction runs derived → base. The parent is the foundation, so it must exist before and outlive the child's own members.
6. **Forward Parent Arguments Explicitly:** If the parent has no default constructor, the child *must* call a parent constructor in its member initializer list, or compilation fails.
7. **Constructors Are Not Inherited (by default):** The child does not automatically get the parent's constructors as its own; it defines its own and forwards to the parent.
8. **Destructors Are Not Inherited Either:** Each class writes its own destructor, and C++ chains the calls automatically - you never call the parent destructor by hand.

---

## Source Code Walkthrough

### 1. single-inheritance.cpp

From [`coding/1. single-inheritance.cpp`](../coding/1.%20single-inheritance.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Single Inheritance: Vehicle (Base / Parent) -> Car (Derived / Child)
// =========================================================================
// Inheritance lets a child class reuse the attributes and behaviours of a
// parent class instead of re-writing them, and then extend the parent with
// its own child-specific members.
// =========================================================================

// =========================================================================
// Base Class (Parent): Vehicle
// =========================================================================
class Vehicle
{
    // ---------------- Attributes ----------------
    // Kept public here purely to demonstrate the simplest inheritance case
public:
    string name;
    string model;
    int numberOfTyres;

    // ---------------- Public Methods ----------------
public:
    // ---------------- Constructor (ctor) ----------------
    Vehicle(string _name, string _model, int _tyres)
    {
        cout << "Inside Vehicle ctor" << endl;
        this->name = _name;
        this->model = _model;
        this->numberOfTyres = _tyres;
    }

    // ---------------- Common Behaviours (inherited by every vehicle) ----------------
    void startEngine()
    {
        cout << "Engine Started" << endl;
    }

    void stopEngine()
    {
        cout << "Engine Stopped" << endl;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Vehicle()
    {
        cout << "dtor of Vehicle called !!" << endl;
    }
};

// =========================================================================
// Derived Class (Child): Car inherits from Vehicle
// =========================================================================
// Syntax: class Car : accessSpecifier(mode) Vehicle
// 'public' mode means: private members stay private, protected members stay
// protected, and public members stay public inside the child.
// =========================================================================
class Car : public Vehicle
{
    // Car already owns everything Vehicle exposed:
    // Attributes -> name, model, numberOfTyres
    // Methods    -> startEngine(), stopEngine()

    // ---------------- Car-Specific Attributes (the "extension") ----------------
public:
    int numberOfDoors;
    string transmissionType;

    // ---------------- Constructor (ctor) ----------------
    // The base ctor must run first, so Vehicle(...) is invoked through the
    // member initializer list before the Car body executes.
    Car(string _name, string _model, int _tyres, int _doors, string _transmission) : Vehicle(_name, _model, _tyres)
    {
        cout << "Inside Car ctor" << endl;
        this->numberOfDoors = _doors;
        this->transmissionType = _transmission;
    }

    // ---------------- Car-Specific Behaviour ----------------
    void StartAC()
    {
        // 'name' belongs to Vehicle, but it is inherited, so Car can use it
        cout << "AC has Started of " << name << endl;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Car()
    {
        cout << "Default Dtor Called for Car !!" << endl;
    }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- Creating a Child Object ----------------
    // Construction order : Vehicle ctor -> Car ctor
    // Destruction order  : Car dtor    -> Vehicle dtor (exact reverse)
    Car A("Maruti", "LXI", 4, 4, "Manual");

    // ---------------- Inherited + Own Behaviours ----------------
    A.startEngine(); // inherited from Vehicle
    A.StartAC();     // Car's own method
    A.stopEngine();  // inherited from Vehicle

    // ---------------- Inherited + Own Attributes ----------------
    cout << A.model << A.name << A.numberOfDoors << A.numberOfTyres << A.transmissionType << endl;

    return 0;
}
```

**Program Output:**

```
Inside Vehicle ctor
Inside Car ctor
Engine Started
AC has Started of Maruti
Engine Stopped
LXIMaruti44Manual
Default Dtor Called for Car !!
dtor of Vehicle called !!
```

---

### 2. private-members-in-inheritance.cpp

From [`coding/2. private-members-in-inheritance.cpp`](../coding/2.%20private-members-in-inheritance.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Private Members Are NOT Accessible Inside the Child Class
// =========================================================================
// A private member of the base class IS inherited (it exists in the child
// object's memory), but the child is NOT allowed to touch it directly.
// The only legal route is a public getter/setter exposed by the base class.
// =========================================================================

// =========================================================================
// Base Class (Parent): Vehicle
// =========================================================================
class Vehicle
{
    // ---------------- Private Attribute (Hidden even from the Child) ----------------
    // Members before the first access specifier are private by default
    string name;

    // ---------------- Public Attributes ----------------
public:
    string model;
    int numberOfTyres;

    // ---------------- Public Methods ----------------
public:
    // ---------------- Constructor (ctor) ----------------
    Vehicle(string _name, string _model, int _tyres)
    {
        cout << "Inside Vehicle ctor" << endl;
        this->name = _name; // legal: we are inside Vehicle itself
        this->model = _model;
        this->numberOfTyres = _tyres;
    }

    void startEngine()
    {
        cout << "Engine Started" << endl;
    }

    void stopEngine()
    {
        cout << "Engine Stopped" << endl;
    }

    // ---------------- Getter (the only door to the private attribute) ----------------
    string getName()
    {
        return this->name;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Vehicle()
    {
        cout << "dtor of Vehicle called !!" << endl;
    }
};

// =========================================================================
// Derived Class (Child): Car
// =========================================================================
class Car : public Vehicle
{
    // ---------------- Car-Specific Attributes ----------------
public:
    int numberOfDoors;
    string transmissionType;

    // ---------------- Constructor (ctor) ----------------
    Car(string _name, string _model, int _tyres, int _doors, string _transmission) : Vehicle(_name, _model, _tyres)
    {
        cout << "Inside Car ctor" << endl;
        this->numberOfDoors = _doors;
        this->transmissionType = _transmission;
    }

    // ---------------- Car-Specific Behaviour ----------------
    void StartAC()
    {
        // cout << name;      // COMPILATION ERROR: 'name' is private in Vehicle
        // The inherited public getter is the legal way in
        cout << "AC has Started of " << getName() << endl;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Car()
    {
        cout << "Default Dtor Called for Car !!" << endl;
    }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- Creating a Child Object ----------------
    Car A("Maruti", "LXI", 4, 4, "Manual");

    A.startEngine();
    A.StartAC();
    A.stopEngine();

    // 'name' is reachable from outside only through the inherited getter
    cout << A.model << A.getName() << A.numberOfDoors << A.numberOfTyres << A.transmissionType << endl;

    return 0;
}
```

**Key Takeaway:** `name` still exists inside every `Car` object and the `Vehicle` constructor still fills it in. The child simply lacks permission to name it directly - `getName()` is the door.

---

### 3. protected-members.cpp

From [`coding/3. protected-members.cpp`](../coding/3.%20protected-members.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Protected Members: The Middle Ground Built for Inheritance
// =========================================================================
// protected = private to the outside world, but public to the child class.
// The child can read/write it directly, yet main() still cannot.
// If the outside world needs the value, the child exposes its own getter.
// =========================================================================

// =========================================================================
// Base Class (Parent): Vehicle
// =========================================================================
class Vehicle
{
    // ---------------- Protected Attribute (Child-Accessible, Outsider-Blocked) ----------------
protected:
    string name;

    // ---------------- Public Attributes ----------------
public:
    string model;
    int numberOfTyres;

    // ---------------- Public Methods ----------------
public:
    // ---------------- Constructor (ctor) ----------------
    Vehicle(string _name, string _model, int _tyres)
    {
        cout << "Inside Vehicle ctor" << endl;
        this->name = _name;
        this->model = _model;
        this->numberOfTyres = _tyres;
    }

    void startEngine()
    {
        cout << "Engine Started" << endl;
    }

    void stopEngine()
    {
        cout << "Engine Stopped" << endl;
    }

    // ---------------- Getter of the Base Class ----------------
    string getName()
    {
        return this->name;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Vehicle()
    {
        cout << "dtor of Vehicle called !!" << endl;
    }
};

// =========================================================================
// Derived Class (Child): Car
// =========================================================================
class Car : public Vehicle
{
    // ---------------- Car-Specific Attributes ----------------
public:
    int numberOfDoors;
    string transmissionType;

    // ---------------- Constructor (ctor) ----------------
    Car(string _name, string _model, int _tyres, int _doors, string _transmission) : Vehicle(_name, _model, _tyres)
    {
        cout << "Inside Car ctor" << endl;
        this->numberOfDoors = _doors;
        this->transmissionType = _transmission;
    }

    // ---------------- Car-Specific Behaviour ----------------
    void StartAC()
    {
        // Direct access is legal now - 'name' is protected, not private
        cout << "AC has Started of " << name << endl;
    }

    // ---------------- Child's Own Getter ----------------
    // Re-exposes the protected base attribute to code outside the hierarchy
    string getName()
    {
        return this->name;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Car()
    {
        cout << "Default Dtor Called for Car !!" << endl;
    }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- Creating a Child Object ----------------
    Car A("Maruti", "LXI", 4, 4, "Manual");

    A.startEngine();
    A.StartAC();
    A.stopEngine();

    // cout << A.name;   // COMPILATION ERROR: 'name' is protected, blocked outside
    cout << A.model << A.getName() << A.numberOfDoors << A.numberOfTyres << A.transmissionType << endl;

    return 0;
}
```

**Key Takeaway:** `Car::getName()` **hides** `Vehicle::getName()` because both have the same name and signature. Calling `A.getName()` resolves to the child's version - a first glimpse of the name-resolution rules that Polymorphism will formalise.

---

### 4. extensibility-hierarchical.cpp

From [`coding/4. extensibility-hierarchical.cpp`](../coding/4.%20extensibility-hierarchical.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Extensibility & Hierarchical Inheritance
// =========================================================================
// One base class, many children. Vehicle is written once; Car and Bike both
// reuse it and extend it with their own specialised state and behaviour.
// Adding a Truck or a Bus tomorrow costs one new class - Vehicle stays untouched.
// =========================================================================

// =========================================================================
// Base Class (Parent): Vehicle
// =========================================================================
class Vehicle
{
    // ---------------- Protected Attributes (Shared with every Child) ----------------
protected:
    string name;
    string model;
    int numberOfTyres;

    // ---------------- Public Methods ----------------
public:
    // ---------------- Constructor (ctor) ----------------
    Vehicle(string _name, string _model, int _tyres)
    {
        cout << "Inside Vehicle ctor" << endl;
        this->name = _name;
        this->model = _model;
        this->numberOfTyres = _tyres;
    }

    // ---------------- Behaviours Common to All Vehicles ----------------
    void startEngine()
    {
        cout << "Engine Started" << endl;
    }

    void stopEngine()
    {
        cout << "Engine Stopped" << endl;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Vehicle()
    {
        cout << "dtor of Vehicle called !!" << endl;
    }
};

// =========================================================================
// Derived Class 1 (Child): Car : public Vehicle
// =========================================================================
// 'public' mode means: private stays private, protected stays protected,
// and public stays public inside the child.
// =========================================================================
class Car : public Vehicle
{
    // Car already owns Vehicle's name, model, numberOfTyres
    // and Vehicle's startEngine() / stopEngine()

    // ---------------- Car-Specific Attributes ----------------
public:
    int numberOfDoors;
    string transmissionType;

    // ---------------- Constructor (ctor) ----------------
    Car(string _name, string _model, int _tyres, int _doors, string _transmission) : Vehicle(_name, _model, _tyres)
    {
        cout << "Inside Car ctor" << endl;
        this->numberOfDoors = _doors;
        this->transmissionType = _transmission;
    }

    // ---------------- Car-Specific Behaviour ----------------
    void StartAC()
    {
        // 'name' is Vehicle's, but inherited as protected, so Car can use it
        cout << "AC has Started of " << name << endl;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Car()
    {
        cout << "Default Dtor Called for Car !!" << endl;
    }
};

// =========================================================================
// Derived Class 2 (Child): Bike : public Vehicle
// =========================================================================
// The same Vehicle base, extended in a completely different direction.
// =========================================================================
class Bike : public Vehicle
{
    // ---------------- Bike-Specific Attributes ----------------
protected:
    string handleBarStyle;
    string suspensionType;

public:
    // ---------------- Constructor (ctor) ----------------
    Bike(string _name, string _model, int _tyres, int _doors, string _handleBarStyle, string _suspensionType) : Vehicle(_name, _model, _tyres)
    {
        cout << "Bike ctor called !!" << endl;
        this->handleBarStyle = _handleBarStyle;
        this->suspensionType = _suspensionType;
    }

    // ---------------- Bike-Specific Behaviour ----------------
    void wheelie()
    {
        cout << "Wheelie karri hai " << name << endl;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Bike()
    {
        cout << "Bike dtor called !!" << endl;
    }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- Child 1: Car ----------------
    Car A("Maruti", "LXI", 4, 4, "Manual");
    A.startEngine(); // reused from Vehicle
    A.StartAC();     // Car's own extension
    A.stopEngine();  // reused from Vehicle

    // cout << A.name << endl; // COMPILATION ERROR: 'name' is protected

    // ---------------- Child 2: Bike ----------------
    Bike B("Hero", "vxi", 2, 0, "U", "hard");
    B.startEngine(); // same reused behaviour, zero duplicated code
    B.wheelie();     // Bike's own extension
    B.stopEngine();

    return 0;
}
```

**Program Output:**

```
Inside Vehicle ctor
Inside Car ctor
Engine Started
AC has Started of Maruti
Engine Stopped
Inside Vehicle ctor
Bike ctor called !!
Engine Started
Wheelie karri hai Hero
Engine Stopped
Bike dtor called !!
dtor of Vehicle called !!
Default Dtor Called for Car !!
dtor of Vehicle called !!
```

Note the destruction order at the end: `B` was declared last, so `B` is destroyed first (`Bike` dtor, then its `Vehicle` part), and only then is `A` destroyed (`Car` dtor, then its `Vehicle` part). Stack objects always die in the reverse order of their creation.

---

## Summary

```
=================================================================================
                                CHAPTER 04 SUMMARY
=================================================================================

1. Definition of Inheritance:
   - A child class acquires the attributes and behaviours of a parent class,
     then extends them with its own members.
   - Models the IS-A relationship (Car IS-A Vehicle, Bike IS-A Vehicle).

2. Terminology:
   - Base Class    = Parent Class = Super Class  (Vehicle)
   - Derived Class = Child Class  = Sub Class    (Car, Bike)

3. Syntax and Mode:
   - class Car : public Vehicle
   - 'public' mode preserves every member's original access level:
     public -> public, protected -> protected, private -> not accessible.

4. Constructor & Destructor Chaining:
   - Construction runs base FIRST, then derived.
   - Destruction runs derived FIRST, then base (exact reverse).
   - The member initializer list ( : Vehicle(...) ) forwards arguments upward,
     and is mandatory when the parent has no default constructor.

5. Access Specifiers Under Inheritance:
   - public    : reachable by the child AND the outside world.
   - protected : reachable by the child ONLY - the specifier built for inheritance.
   - private   : inherited into memory, but unreachable by the child;
                 a public getter on the parent is the only legal route.

6. Extensibility (Hierarchical Inheritance):
   - One base class, many independent children (Vehicle -> Car, Bike, ...).
   - Shared code is written ONCE and reused, eliminating duplication.
   - New vehicle types cost one new class; the base is never edited,
     so existing working code cannot break.
=================================================================================
```

---

<!-- chapter-nav -->

| Previous | Next |
| :--- | ---: |
| [&larr; Chapter 03 - Encapsulation](../../Chapter%2003%20-%20Encapsulation/notes/Notes.md) |  |
