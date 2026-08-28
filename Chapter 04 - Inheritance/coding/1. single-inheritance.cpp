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
