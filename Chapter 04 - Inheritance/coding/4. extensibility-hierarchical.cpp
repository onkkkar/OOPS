#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Extensibility & Hierarchical Inheritance
// =========================================================================
// One base class, many children. Vehicle is written once; Car and Bike both
// reuse it and extend it with their own specialised state and behaviour.
// Adding a Truck or a Bus tomorrow costs one new class - Vehicle stays untouched.
// =========================================================================

// =========================================================================
// Base Class (Parent): Vehicle
// =========================================================================
class Vehicle
{
    // ---------------- Protected Attributes (Shared with every Child) ----------------
protected:
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

    // ---------------- Behaviours Common to All Vehicles ----------------
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
// Derived Class 1 (Child): Car : public Vehicle
// =========================================================================
// 'public' mode means: private stays private, protected stays protected,
// and public stays public inside the child.
// =========================================================================
class Car : public Vehicle
{
    // Car already owns Vehicle's name, model, numberOfTyres
    // and Vehicle's startEngine() / stopEngine()

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
        // 'name' is Vehicle's, but inherited as protected, so Car can use it
        cout << "AC has Started of " << name << endl;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Car()
    {
        cout << "Default Dtor Called for Car !!" << endl;
    }
};

// =========================================================================
// Derived Class 2 (Child): Bike : public Vehicle
// =========================================================================
// The same Vehicle base, extended in a completely different direction.
// =========================================================================
class Bike : public Vehicle
{
    // ---------------- Bike-Specific Attributes ----------------
protected:
    string handleBarStyle;
    string suspensionType;

public:
    // ---------------- Constructor (ctor) ----------------
    Bike(string _name, string _model, int _tyres, int _doors, string _handleBarStyle, string _suspensionType) : Vehicle(_name, _model, _tyres)
    {
        cout << "Bike ctor called !!" << endl;
        this->handleBarStyle = _handleBarStyle;
        this->suspensionType = _suspensionType;
    }

    // ---------------- Bike-Specific Behaviour ----------------
    void wheelie()
    {
        cout << "Wheelie karri hai " << name << endl;
    }

    // ---------------- Destructor (dtor) ----------------
    ~Bike()
    {
        cout << "Bike dtor called !!" << endl;
    }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- Child 1: Car ----------------
    Car A("Maruti", "LXI", 4, 4, "Manual");
    A.startEngine(); // reused from Vehicle
    A.StartAC();     // Car's own extension
    A.stopEngine();  // reused from Vehicle

    // cout << A.name << endl; // COMPILATION ERROR: 'name' is protected

    // ---------------- Child 2: Bike ----------------
    Bike B("Hero", "vxi", 2, 0, "U", "hard");
    B.startEngine(); // same reused behaviour, zero duplicated code
    B.wheelie();     // Bike's own extension
    B.stopEngine();

    return 0;
}
