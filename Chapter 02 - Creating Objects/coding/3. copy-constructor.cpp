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
