#include <bits/stdc++.h>
using namespace std;

class Vehicle
{
  // Private Attributes (Data Members) by default
public:
  string name;
  string model;
  int numberOfTyres;

  // Public Methods
public:
  // ctor
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

  // dtor
  ~Vehicle()
  {
    cout << "dtor of Vehicle called !!" << endl;
  }
};

// Derived Class (Child) inheriting from Base Class (Parent)
// Car : accessSpecifier(mode) Vehicle
// public mode means private inehrited as private, protected inherited as protected and public ones inherited as Public
class Car : public Vehicle
{
  // Has all Attributes and Mehtods of Vehicle
  // here we have all name, model and tyres of Vehicle accessible
  // Also we have startEngine() and stroEngine() accessible as well

  // Extra Property of Car Specific
public:
  int numberOfDoors;
  string transmissionType;

  // ctor
  Car(string _name, string _model, int _tyres, int _doors, string _transmission) : Vehicle(_name, _model, _tyres)
  {
    cout << "Inside Car ctor" << endl;
    this->numberOfDoors = _doors;
    this->transmissionType = _transmission;
  }

  // Car Specific Method
  void StartAC()
  {
    cout << "AC has Started of " << name << endl;
    // name is of Vehicle but inherited so we cna use it here
  }

  // dtor
  ~Car()
  {
    cout << "Default Dtor Called for Car !!" << endl;
  }
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // Car Object
  Car A("Maruti", "LXI", 4, 4, "Manual");
  A.startEngine();
  A.StartAC();
  A.stopEngine();
  cout << A.model << A.name << A.numberOfDoors << A.numberOfTyres << A.transmissionType << endl;

  return 0;
}
