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
