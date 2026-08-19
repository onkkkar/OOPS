#include <bits/stdc++.h>
using namespace std;

// Class
class Student
{
public:
    // Attributes / Data
    int id;
    int age;
    string name;

    // Constructor
    Student()
    {
        cout << "Default Constructor Called" << endl;

        this->name = name;
        this->age = age;
        this->id = id;
    }

    // Behaviour / Methods
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

    // Destructor
    ~Student()
    {
        cout << "Default Destructor Called" << endl;
    }
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Creating Objects
    // Number of Objects created === number of times Constructor and Destructor are called
    Student s1;

    // s1 object
    s1.name = "yash";
    s1.age = 25;
    s1.id = 6;
    s1.sleep();

    cout << s1.id << ", " << s1.age << ", " << s1.name << endl;

    return 0;
}
