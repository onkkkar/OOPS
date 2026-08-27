#include <bits/stdc++.h>
using namespace std;

class Vehicle
{
  // Private Attributes (Data Members) by default
  string name;

public:
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

  // Getter Method to acess private things
  string getName()
  {
    return this->name;
  }

  // dtor
  ~Vehicle()
  {
    cout << "dtor of Vehicle called !!" << endl;
  }
};

class Car : public Vehicle
{
public:
  int numberOfDoors;
  string transmissionType;

  Car(string _name, string _model, int _tyres, int _doors, string _transmission) : Vehicle(_name, _model, _tyres)
  {
    cout << "Inside Car ctor" << endl;
    this->numberOfDoors = _doors;
    this->transmissionType = _transmission;
  }

  void StartAC()
  {
    cout << "AC has Started of " << getName() << endl;
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
  cout << A.model << A.getName() << A.numberOfDoors << A.numberOfTyres << A.transmissionType << endl;

  return 0;
}
