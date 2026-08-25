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
