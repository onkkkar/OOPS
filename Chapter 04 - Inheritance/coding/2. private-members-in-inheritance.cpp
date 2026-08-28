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
