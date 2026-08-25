# Chapter 03 - Encapsulation

Encapsulation is one of the foundational pillars of Object-Oriented Programming. While Chapter 01 introduced the concept of grouping data and behaviour together into a single blueprint, and Chapter 02 explored the lifecycle mechanics of constructing and destroying objects, Chapter 03 focuses on the **security boundaries and access controls** that govern an object.

$$\text{Encapsulation} = \text{Data (Attributes)} + \text{Methods (Behaviours)} + \text{Access Boundary (Security Layer)}$$

---

## 📌 Table of Contents

- [What is Encapsulation?](#what-is-encapsulation)
  - [The Capsule Analogy](#the-capsule-analogy)
  - [Why a Class is an Example of Encapsulation](#why-a-class-is-an-example-of-encapsulation)
- [Core Functions and Purposes of Encapsulation](#core-functions-and-purposes-of-encapsulation)
  - [1. Providing a Secure Layer (Controlled Exposure)](#1-providing-a-secure-layer-controlled-exposure)
  - [2. Hiding Internal Implementation (Algorithmic Privacy)](#2-hiding-internal-implementation-algorithmic-privacy)
  - [3. Exposing Only Necessary Information (Minimal Interface)](#3-exposing-only-necessary-information-minimal-interface)
- [Case Study: The Student and Teacher Interaction](#case-study-the-student-and-teacher-interaction)
  - [Attributes and Access Rules](#attributes-and-access-rules)
  - [Why the Teacher Does Not Need Implementation Details](#why-the-teacher-does-not-need-implementation-details)
  - [Visual Architecture: The Encapsulated Security Boundary](#visual-architecture-the-encapsulated-security-boundary)
- [Encapsulation as Data Hiding](#encapsulation-as-data-hiding)
  - [Preventing Unauthorized Access and Modification](#preventing-unauthorized-access-and-modification)
  - [Cross-Class Communication Without Structural Exposure](#cross-class-communication-without-structural-exposure)
- [Access Modifiers in C++](#access-modifiers-in-c)
  - [1. Public](#1-public)
  - [2. Private](#2-private)
  - [3. Protected](#3-protected)
  - [Access Modifiers Comparison Matrix](#access-modifiers-comparison-matrix)
- [Perfect Encapsulation](#perfect-encapsulation)
  - [What Perfect Encapsulation Means (and What It Doesn't)](#what-perfect-encapsulation-means-and-what-it-doesnt)
  - [Handling External Interaction: Getters and Setters](#handling-external-interaction-getters-and-setters)
  - [Visual Architecture: Controlled Flow Through Getters & Setters](#visual-architecture-controlled-flow-through-getters--setters)
- [Key Implementation Rules & Gotchas](#key-implementation-rules--gotchas)
  - [Default Access Specifier in C++ Classes](#default-access-specifier-in-c-classes)
  - [Why Constructors and Destructors Must Be Public](#why-constructors-and-destructors-must-be-public)
  - [A Philosophical Note: The 4 Pillars vs. 1 Pillar](#a-philosophical-note-the-4-pillars-vs-1-pillar)
- [Source Code Walkthrough](#source-code-walkthrough)
  - [1. encapsulation.cpp](#1-encapsulationcpp)
  - [2. perfect-encapsulation.cpp](#2-perfect-encapsulationcpp)
- [Summary](#summary)

---

> 📄 **Source Code Reference**: All executable C++ source files for this chapter are available in the `coding/` directory:
>
> 1. [`1. encapsulation.cpp`](../coding/1.%20encapsulation.cpp) - Demonstrates public vs. private attributes and methods, security boundaries, and compilation errors on unauthorized access.
> 2. [`2. perfect-encapsulation.cpp`](../coding/2.%20perfect-encapsulation.cpp) - Demonstrates perfect encapsulation with 100% private state and controlled read/write access via Getters and Setters.

---

## What is Encapsulation?

**Encapsulation** is the mechanism that binds together data (attributes/state) and the functions (behaviours/methods) that manipulate that data into a single, cohesive unit, while wrapping a protective barrier around it.

```
+-------------------------------------------------------------------+
|                        CLASS BOUNDARY                             |
|                                                                   |
|   +--------------------------+     +--------------------------+   |
|   |   DATA (Attributes)      | <-> |  METHODS (Behaviours)   |   |
|   |   id, name, age, gfName  |     |  study(), sleep(), ...   |   |
|   +--------------------------+     +--------------------------+   |
|                                                                   |
+-------------------------------------------------------------------+
```

### The Capsule Analogy

The term *Encapsulation* is directly derived from a medical capsule:

> "Like a medical capsule that encloses several medicinal ingredients within a single gelatin shell, a class encloses variables and functions together into a single contained unit."

In a medical capsule, the outer shell protects the inner compounds from contamination and ensures that the medicine is released only through the proper physiological channel. Similarly, in software engineering, encapsulation protects the inner variables of a class from arbitrary external meddling and ensures data is modified only through valid member functions.

### Why a Class is an Example of Encapsulation

A `class` is the primary programming construct used to achieve encapsulation:

1. It acts as the physical container that groups related variables (`id`, `name`, `age`) with their associated functions (`study()`, `sleep()`).
2. It establishes an access boundary through access specifiers (`public`, `private`, `protected`).

Therefore:
$$\text{Class} = \text{The Concrete Implementation of Encapsulation in C++}$$

---

## Core Functions and Purposes of Encapsulation

Encapsulation serves three critical architectural functions:

```
                      CORE FUNCTIONS OF ENCAPSULATION
                                     │
         ┌───────────────────────────┼───────────────────────────┐
         ▼                           ▼                           ▼
 1. Security Layer           2. Implementation Hiding    3. Minimal Interface
 (Expose only what is        (Hide internal algorithms   (Provide clean public
  safe to reveal)             and storage details)        methods to external world)
```

### 1. Providing a Secure Layer (Controlled Exposure)

Without encapsulation, all data members are exposed directly to the entire program. Any rogue function or external caller can silently read or overwrite sensitive fields without validation.

Encapsulation creates a **security layer**:
- We expose only the specific information and behaviours that we intend for the outer world to see.
- Sensitive or internal variables are locked inside the class.

### 2. Hiding Internal Implementation (Algorithmic Privacy)

External callers need to know **what** an object can do, not **how** it does it.
- When an external entity triggers a behaviour (such as `student.sleep()` or `student.study()`), the caller does not need to know the inner algorithms, memory layout, or step-by-step logic executing inside that method.
- The internal implementation can be refactored, optimized, or completely rewritten without breaking any external code that depends on it.

### 3. Exposing Only Necessary Information (Minimal Interface)

By exposing only a clean, well-defined public interface, we reduce cognitive load and prevent external code from forming tight coupling with internal details.

---

## Case Study: The Student and Teacher Interaction

Let us explore a concrete real-world scenario to see encapsulation in action: modelling a `Student` class and observing how an external entity (a `Teacher` or `main()`) interacts with it.

### Attributes and Access Rules

Consider a `Student` class with the following characteristics:

| Member Name | Member Type | Intended Access | Rationale |
| :--- | :--- | :--- | :--- |
| `id` | Attribute | `public` | Public identifier used across school systems |
| `name` | Attribute | `public` | Name is openly shared with everyone |
| `age` | Attribute | `private` | Personal, sensitive data; student does not want to expose it |
| `gfName` | Attribute | `private` | Highly confidential private information |
| `study()` | Behaviour | `public` | Standard student activity that teachers can instruct |
| `sleep()` | Behaviour | `public` | Standard life activity |
| `bunk()` | Behaviour | `public` | Student behaviour observable in school context |
| `gfChatting()`| Behaviour | `private` | Private personal behaviour hidden from external world |

```cpp
class Student
{
public:
    int id;
    string name;

private:
    int age;
    string gfName;

public:
    Student(string name, int age, int id, string gfName)
    {
        this->name = name;
        this->age = age;
        this->id = id;
        this->gfName = gfName; // Private attribute accessible INSIDE the class
    }

    void study() { cout << this->name << " is Studying" << endl; }
    void sleep() { cout << this->name << " is Sleeping" << endl; }
    void bunk()  { cout << this->name << " is Bunking" << endl; }

private:
    void gfChatting()
    {
        cout << this->name << " is Chatting with his Girlfriend " << this->gfName << endl;
    }
};
```

When an object `s1` is created:
```cpp
Student s1("yash", 25, 6, "priya");

// Allowed (Public):
cout << s1.name;      // Works: 'name' is public
s1.study();           // Works: 'study()' is public
s1.sleep();           // Works: 'sleep()' is public

// Blocked by Compiler (Private Security Layer):
// cout << s1.age;    // COMPILER ERROR: 'age' is private
// cout << s1.gfName; // COMPILER ERROR: 'gfName' is private
// s1.gfChatting();   // COMPILER ERROR: 'gfChatting' is private
```

### Why the Teacher Does Not Need Implementation Details

Now consider a `Teacher` interacting with the `Student`:

```
+---------------+                              +---------------+
|    TEACHER    |   ---- 1. s1.sleep() ---->   |    STUDENT    |
| (External)    |   <--- 2. executes -------   |   (Instance)  |
+---------------+                              +---------------+
        │                                              │
        │ DOES NOT KNOW:                               │ ENCAPSULATES:
        ├── How student falls asleep                   ├── Internal state (age, gfName)
        ├── What dreams occur                          ├── Internal logic inside sleep()
        └── What code runs inside sleep()              └── Private method gfChatting()
```

1. The teacher tells the student to go to sleep: `s1.sleep()`.
2. **Does the teacher need to know *how* the student is sleeping, or inspect the code lines written inside `sleep()`?**
   - **NO.** The teacher only requests the action. The student object internally handles the execution.
3. The same applies when the teacher tells the student to study: `s1.study()`.
   - The teacher does not need to know the internal study techniques, memory retention mechanisms, or personal notes used by the student.
   - We hide the internal implementation from the teacher and expose only the callable interface.

### Visual Architecture: The Encapsulated Security Boundary

```
=============================================================================
                      ENCAPSULATED OBJECT BOUNDARY
=============================================================================

                   EXTERNAL CALLERS (Teacher / main())
                                    │
                                    │ Interacts via Public Surface
                                    ▼
       ┌──────────────────────────────────────────────────────────┐
       │                   PUBLIC INTERFACE (Exposed)             │
       │                                                          │
       │   Attributes:                                            │
       │   ├── id                                                 │
       │   └── name                                               │
       │                                                          │
       │   Methods:                                               │
       │   ├── study()                                            │
       │   ├── sleep()                                            │
       │   └── bunk()                                             │
       └────────────────────────────┬─────────────────────────────┘
                                    │
                       PROTECTIVE SECURITY SHIELD
                                    │
       ┌────────────────────────────▼─────────────────────────────┐
       │                   PRIVATE INTERIOR (Hidden)              │
       │                                                          │
       │   Private Data:               Private Behaviours:        │
       │   ├── age                     └── gfChatting()           │
       │   └── gfName                                             │
       │                                                          │
       │   [ Blocked from direct external access or mutation ]    │
       └──────────────────────────────────────────────────────────┘
=============================================================================
```

---

## Encapsulation as Data Hiding

Because encapsulation hides internal variables and implementation details from outside classes and external callers, encapsulation is widely referred to as **Data Hiding**.

### Preventing Unauthorized Access and Modification

The primary objective of data hiding is:

> "To implement classes in a way that prevents unauthorized access to, or accidental modification of, the internal state of a class by external code or foreign instances."

- If a `Teacher` or external user could directly access `s1.age`, `s1.gfName`, or invoke `s1.gfChatting()`, it would constitute **unauthorized access of private data**.
- By declaring sensitive members `private`, the C++ compiler guarantees that unauthorized code cannot read or corrupt those values.

### Cross-Class Communication Without Structural Exposure

The underlying data structures and algorithms of one class do not need to be exposed to another class:

- Class `Teacher` and Class `Student` can communicate seamlessly through public methods.
- Neither class needs to expose its internal algorithms or private fields to collaborate effectively.
- This creates **loose coupling**: you can change the internal data structures of `Student` without breaking `Teacher`.

---

## Access Modifiers in C++

Access modifiers (or access specifiers) define the accessibility and scope of class members. C++ provides three access modifiers:

```
                              ACCESS MODIFIERS
                                     │
         ┌───────────────────────────┼───────────────────────────┐
         ▼                           ▼                           ▼
    1. public                   2. private                  3. protected
 (Accessible Everywhere)   (Accessible Only in Class)  (Class + Derived Classes)
```

### 1. Public

- Members declared as `public` are accessible from **any part of the program**.
- They can be accessed directly by object instances (`s1.name`) and external functions.
- Used for constructors, destructors, and methods intended to form the object's public API.

### 2. Private

- Members declared as `private` are accessible **only within the member functions of the same class**.
- They **cannot** be accessed from outside the class, nor can they be accessed by derived (child) classes.
- Used to protect state, sensitive attributes, and internal helper functions.

### 3. Protected

- Members declared as `protected` are accessible **within the same class and by derived (child) classes**.
- They are **not directly accessible** from external code or plain object instances.
- Used in inheritance hierarchies where derived classes need access to base class internals while keeping them hidden from the outside world. *(Detailed extensively in Inheritance).*

### Access Modifiers Comparison Matrix

| Access Specifier | Inside Same Class | Inside Derived Class | Outside Class / `main()` |
| :--- | :---: | :---: | :---: |
| `public` | ✅ Yes | ✅ Yes | ✅ Yes |
| `protected`| ✅ Yes | ✅ Yes | ❌ No |
| `private` | ✅ Yes | ❌ No | ❌ No |

---

## Perfect Encapsulation

### What Perfect Encapsulation Means (and What It Doesn't)

> **Definition of Perfect Encapsulation**:
> A class achieves **Perfect Encapsulation** when **ALL data attributes are private (100% hidden)**.

> [!IMPORTANT]
> **Common Misconception**:
> Perfect encapsulation does **NOT** mean that all members, including methods, must be private!
> If all methods were also private, no external code could ever create, command, or communicate with the object, rendering the class completely unusable.

```
       POOR DESIGN                       PERFECT ENCAPSULATION
+-----------------------+              +-----------------------+
| class Student {       |              | class Student {       |
| public:               |              | private:              |
|   int id;             |  ───────►    |   int id;             |
|   int age;            |              |   int age;            |
|   string name;        |              |   string name;        |
|   string gfName;      |              |   string gfName;      |
| };                    |              | public:               |
+-----------------------+              |   // Getters/Setters  |
(State fully exposed)                  | };                    |
                                       +-----------------------+
                                       (State 100% encapsulated)
```

### Handling External Interaction: Getters and Setters

Despite hiding all attributes, objects still need to interact with the outside world. We provide controlled, validated access using **Getters** and **Setters**:

1. **Getters (Accessors)**:
   - Public methods designed to **READ** private attribute values.
   - Example: `int getAge() const { return this->age; }`
2. **Setters (Mutators)**:
   - Public methods designed to **MODIFY** private attribute values.
   - Provide a checkpoint where validation logic, range checks, and security gates can be enforced.
   - Example:
     ```cpp
     void setAge(int age)
     {
         if (age > 0 && age < 120) {
             this->age = age;
         }
     }
     ```

### Visual Architecture: Controlled Flow Through Getters & Setters

```
=============================================================================
                  PERFECT ENCAPSULATION: CONTROLLED DATA FLOW
=============================================================================

                           EXTERNAL WORLD (main())
                                │             ▲
                   1. setAge(26)│             │ 2. getAge() -> returns 26
                                ▼             │
    ┌─────────────────────────────────────────────────────────────────────┐
    │                      PUBLIC INTERFACE LAYER                         │
    │                                                                     │
    │   [ Setter: setAge(int age) ]         [ Getter: getAge() const ]    │
    │   ├── Performs validation             └── Safely returns value      │
    │   └── Writes to private field             without direct reference  │
    └───────────────────────┬─────────────────────────▲───────────────────┘
                            │                         │
                            │ Writes                  │ Reads
                            ▼                         │
    ┌─────────────────────────────────────────────────┴───────────────────┐
    │                      PRIVATE DATA VAULT                             │
    │                                                                     │
    │   private:                                                          │
    │     int id;                                                         │
    │     int age;          <── Protected inside the memory vault         │
    │     string name;                                                    │
    │     string gfName;                                                  │
    └─────────────────────────────────────────────────────────────────────┘
=============================================================================
```

---

## Key Implementation Rules & Gotchas

### Default Access Specifier in C++ Classes

In C++, if you omit the access specifier in a `class`, all members defined before the first explicit specifier are **`private` by default**:

```cpp
class Student
{
    int id;       // PRIVATE by default!
    int age;      // PRIVATE by default!
    void secret() // PRIVATE by default!
    {
        // ...
    }

public:
    Student() { /* ... */ }
};
```

> [!NOTE]
> In a C++ `struct`, members are `public` by default. In a C++ `class`, members are `private` by default. This is the primary distinction between `struct` and `class` in C++.

### Why Constructors and Destructors Must Be Public

Constructors (`ctor`) and destructors (`dtor`) must almost always be placed in the `public:` section:

1. When code in `main()` writes `Student s1("yash", 25, 6, "priya");`, `main()` is calling the constructor from outside the class.
2. If the constructor were `private`, external code would not have permission to invoke it, causing a compilation failure (`error: 'Student::Student(...)' is private within this context`).
3. Similarly, when the object leaves scope, the destructor is invoked automatically. If the destructor were `private`, stack cleanup would fail.

*(Private constructors are reserved for advanced design patterns such as the Singleton Pattern).*

### A Philosophical Note: The 4 Pillars vs. 1 Pillar

In classical object-oriented literature, four core pillars are taught:

1. **Encapsulation** (Data packaging and access shielding)
2. **Abstraction** (Interface representation and complexity hiding)
3. **Inheritance** (Hierarchical code reuse)
4. **Polymorphism** (Dynamic behaviour dispatch)

> "While we study the 4 classical pillars in OOP, at the deepest architectural level, there is truly only **1 fundamental pillar: Abstraction**. 
> 
> Encapsulation is simply abstraction applied to state and access boundaries. Polymorphism is abstraction applied to behaviours and types. Inheritance is abstraction applied to classifications. As we advance through these chapters and reach Abstraction, we will see how every concept naturally flows from this single unifying truth."

For our structured learning roadmap, we study the 4 classical pillars step by step, starting with Encapsulation.

---

## Source Code Walkthrough

### 1. encapsulation.cpp

From [`coding/1. encapsulation.cpp`](../coding/1.%20encapsulation.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Class: Student (Demonstrating Encapsulation & Data Hiding)
// =========================================================================
// Encapsulation binds attributes (data) and methods (behaviours) together
// into a single unit (class), while providing a secure access boundary.
// =========================================================================
class Student
{
    // ---------------- Public Attributes ----------------
    // Accessible from anywhere in the program
public:
    int id;
    string name;

    // ---------------- Private Attributes ----------------
    // Accessible ONLY within this class - hidden from external world
private:
    int age;
    string gfName;

public:
    // ---------------- Constructor (ctor) ----------------
    // Constructors must always be public so objects can be created
    Student(string name, int age, int id, string gfName)
    {
        cout << "Parameterized Constructor Called" << endl;

        this->name = name;
        this->age = age;
        this->id = id;
        this->gfName = gfName; // Private attribute accessed within class member
    }

    // ---------------- Public Behaviours / Methods ----------------
    // External entities (e.g. Teacher, Main) can invoke these methods
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

    // ---------------- Private Method ----------------
    // Internal behaviour hidden from external world
private:
    void gfChatting()
    {
        cout << this->name << " is Chatting with his Girlfriend " << this->gfName << endl;
    }

public:
    // ---------------- Destructor (dtor) ----------------
    // Destructors must always be public so objects can be cleaned up
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

    // ---------------- Creating Object ----------------
    Student s1("yash", 25, 6, "priya");

    // Calling public behaviour
    s1.sleep();

    // Accessing public attributes
    cout << s1.id << ", " << s1.name << endl;

    // ---------------- Encapsulation & Security Layer in Action ----------------
    // Trying to access private attributes or methods from outside the class:
    //
    // cout << s1.age << endl;      // COMPILATION ERROR: 'age' is private
    // cout << s1.gfName << endl;   // COMPILATION ERROR: 'gfName' is private
    // s1.gfChatting();             // COMPILATION ERROR: 'gfChatting' is private
    //
    // Encapsulation prevents unauthorized external access and modification.

    return 0;
}
```

---

### 2. perfect-encapsulation.cpp

From [`coding/2. perfect-encapsulation.cpp`](../coding/2.%20perfect-encapsulation.cpp):

```cpp
#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Class: Student (Demonstrating Perfect Encapsulation)
// =========================================================================
// Perfect Encapsulation:
// 1. ALL data attributes are strictly private (hidden from outside).
// 2. Controlled access is provided using public Getters (Read) and Setters (Write).
// Note: Perfect encapsulation means ALL attributes are private;
//       it does NOT mean public methods are forbidden.
// =========================================================================
class Student
{
    // ---------------- Private Attributes (All Hidden) ----------------
    // By default in a C++ class, members without an access specifier are private
    int id;
    int age;
    string name;
    string gfName;

public:
    // ---------------- Constructor (ctor) ----------------
    Student(string name, int age, int id, string gfName)
    {
        cout << "Parameterized Constructor Called" << endl;

        this->name = name;
        this->age = age;
        this->id = id;
        this->gfName = gfName;
    }

    // ---------------- Getters (Read Access) ----------------
    // Public methods to securely read private data members

    int getId() const
    {
        return this->id;
    }

    int getAge() const
    {
        return this->age;
    }

    string getName() const
    {
        return this->name;
    }

    string getGfName() const
    {
        return this->gfName;
    }

    // ---------------- Setters (Controlled Write Access) ----------------
    // Public methods to securely validate and modify private data members

    void setId(int id)
    {
        this->id = id;
    }

    void setAge(int age)
    {
        this->age = age;
    }

    void setName(string name)
    {
        this->name = name;
    }

    void setGfName(string gfName)
    {
        this->gfName = gfName;
    }

    // ---------------- Public Behaviours ----------------
    void study()
    {
        cout << this->name << " is Studying" << endl;
    }

    // ---------------- Destructor (dtor) ----------------
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

    // ---------------- 1. Creating Object ----------------
    Student s1("yash", 25, 6, "priya");

    // ---------------- 2. GET (Reading Private Data) ----------------
    cout << "\n--- Initial Details (via Getters) ---" << endl;
    cout << "Name: " << s1.getName() << endl;
    cout << "Age: " << s1.getAge() << endl;
    cout << "ID: " << s1.getId() << endl;
    cout << "Girlfriend: " << s1.getGfName() << endl;

    // ---------------- 3. SET (Modifying Private Data) ----------------
    s1.setName("Onkar");
    s1.setAge(26);
    s1.setId(10);
    s1.setGfName("Shradha");

    // ---------------- 4. GET AGAIN (Reading Updated Data) ----------------
    cout << "\n--- Updated Details (via Getters) ---" << endl;
    cout << "Name: " << s1.getName() << endl;
    cout << "Age: " << s1.getAge() << endl;
    cout << "ID: " << s1.getId() << endl;
    cout << "Girlfriend: " << s1.getGfName() << endl;

    // ---------------- 5. Invoking Behaviour ----------------
    cout << "\n--- Behaviours ---" << endl;
    s1.study();

    return 0;
}
```

---

## Summary

```
=================================================================================
                                CHAPTER 03 SUMMARY
=================================================================================

1. Definition of Encapsulation:
   - Binding data (attributes) and behaviours (methods) into a single unit (class).
   - Establishing a security boundary to protect internal state.

2. Three Primary Functions:
   - Security layer: Exposes only safe information to the external world.
   - Implementation hiding: Conceals inner algorithmic complexity.
   - Minimal interface: Clean, decoupled communication between classes.

3. Access Modifiers:
   - public: Accessible from any part of the program.
   - private: Accessible ONLY within the class (default in C++ classes).
   - protected: Accessible within the class and derived classes.

4. Perfect Encapsulation:
   - 100% of data attributes are declared private.
   - Controlled external access is granted via public Getters and Setters.
   - Public methods remain available for communication.

5. Key Rules:
   - Class members are private by default if unspecified.
   - Constructors and Destructors must always be public for standard usage.
   - All 4 OOP pillars converge towards the overarching principle of Abstraction.
=================================================================================
```
