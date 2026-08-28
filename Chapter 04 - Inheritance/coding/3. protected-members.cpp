#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Protected Members: The Middle Ground Built for Inheritance
// =========================================================================
// protected = private to the outside world, but public to the child class.
// The child can read/write it directly, yet main() still cannot.
// If the outside world needs the value, the child exposes its own getter.
// =========================================================================

// =========================================================================
// Base Class (Parent): Vehicle
// =========================================================================
class Vehicle
{
    // ---------------- Protected Attribute (Child-Accessible, Outsider-Blocked) ----------------
protected:
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
        this->name = _name;
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

    // ---------------- Getter of the Base Class ----------------
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
        // Direct access is legal now - 'name' is protected, not private
        cout << "AC has Started of " << name << endl;
    }

    // ---------------- Child's Own Getter ----------------
    // Re-exposes the protected base attribute to code outside the hierarchy
    string getName()
    {
        return this->name;
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

    // cout << A.name;   // COMPILATION ERROR: 'name' is protected, blocked outside
    cout << A.model << A.getName() << A.numberOfDoors << A.numberOfTyres << A.transmissionType << endl;

    return 0;
}
