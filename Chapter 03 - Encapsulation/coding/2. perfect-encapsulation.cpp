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
