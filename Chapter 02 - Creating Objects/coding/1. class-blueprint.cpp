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
