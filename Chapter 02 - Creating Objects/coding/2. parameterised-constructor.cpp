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
