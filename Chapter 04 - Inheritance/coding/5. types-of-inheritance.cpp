#include <iostream>
#include <string>
using namespace std;

// =========================================================================
// THE FIVE TYPES OF INHERITANCE
// =========================================================================
//   1. Single        : one base  -> one derived
//   2. Multiple       : many bases -> one derived
//   3. Multilevel     : A -> B -> C  (a chain)
//   4. Hierarchical   : one base  -> many derived (siblings)
//   5. Hybrid         : any mix of the above (here: hierarchical + multiple)
//
// Note on __FUNCTION__ :
//   __FUNCTION__ is a predefined identifier (a GCC/MSVC spelling of the
//   standard __func__). It holds the name of the function currently
//   executing, as a C-string. Inside a constructor, GCC fills it with the
//   class name - handy for tracing exactly which ctor in a hierarchy ran.
// =========================================================================

// =========================================================================
// Shared root base class
// =========================================================================
class Employee
{
protected:
  string name;
  int employeeId;

public:
  Employee(const string &empName, int empId) : name(empName), employeeId(empId)
  {
    cout << __FUNCTION__ << " ctor  -> " << name << " (#" << employeeId << ")" << endl;
  }

  void display() const
  {
    cout << "Employee: " << name << ", ID: " << employeeId << endl;
  }
};

// =========================================================================
// 1. SINGLE INHERITANCE :  Employee  ->  Developer
// =========================================================================
class Developer : public Employee
{
private:
  string programmingLanguage;

public:
  Developer(const string &empName, int empId, const string &lang)
      : Employee(empName, empId) // base part built first
  {
    this->programmingLanguage = lang;
  }

  void show() const
  {
    display(); // inherited
    cout << "Specialization: Developer, Language: " << programmingLanguage << endl;
  }
};

// =========================================================================
// 2. MULTIPLE INHERITANCE :  (Employee + ProjectManager + TeamLead) -> TechLead
// =========================================================================
class ProjectManager
{
protected:
  string projectManaged;

public:
  ProjectManager(const string &project) : projectManaged(project) {}

  void manageProject() const
  {
    cout << "Manages project: " << projectManaged << endl;
  }
};

class TeamLead
{
protected:
  int teamSize;

public:
  TeamLead(int size) : teamSize(size) {}

  void leadTeam() const
  {
    cout << "Leads a team of " << teamSize << " members" << endl;
  }
};

class TechLead : public Employee, public ProjectManager, public TeamLead
{
public:
  // Each base ctor is initialised explicitly, in the SAME left-to-right
  // order the bases are listed above: Employee, then ProjectManager, then TeamLead.
  TechLead(const string &empName, int empId, const string &project, int size)
      : Employee(empName, empId), ProjectManager(project), TeamLead(size) {}

  void displayInfo() const
  {
    display();       // from Employee
    manageProject(); // from ProjectManager
    leadTeam();      // from TeamLead
  }
};

// =========================================================================
// 3. MULTILEVEL INHERITANCE :  Employee -> HRManager -> HRDirector
// =========================================================================
class HRManager : public Employee
{
public:
  HRManager(const string &empName, int empId) : Employee(empName, empId)
  {
    cout << __FUNCTION__ << " ctor" << endl;
  }

  void handleHRDuties() const
  {
    cout << "HR Manager handling human-resources duties" << endl;
  }
};

class HRDirector : public HRManager
{
public:
  HRDirector(const string &empName, int empId) : HRManager(empName, empId)
  {
    cout << __FUNCTION__ << " ctor" << endl;
  }

  void manageHRDepartment() const
  {
    cout << "HR Director managing the whole HR department" << endl;
  }
};

// =========================================================================
// 4. HIERARCHICAL INHERITANCE :  Employee -> { Manager, Analyst }
// =========================================================================
class Manager : public Employee
{
public:
  Manager(const string &empName, int empId) : Employee(empName, empId) {}

  void approveLeaves() const
  {
    cout << name << " approves leave requests" << endl; // protected 'name'
  }
};

class Analyst : public Employee
{
public:
  Analyst(const string &empName, int empId) : Employee(empName, empId) {}

  void buildReport() const
  {
    cout << name << " builds the quarterly report" << endl;
  }
};

// =========================================================================
// 5. HYBRID INHERITANCE :  hierarchical (both from Employee) + multiple
//    Employee -> MarketingManager
//    Employee -> SalesManager
//    (MarketingManager + SalesManager) -> BusinessDevelopmentManager
// =========================================================================
class MarketingManager : public Employee
{
public:
  MarketingManager(const string &empName, int empId) : Employee(empName, empId) {}

  void createMarketingStrategy() const
  {
    cout << "Marketing Manager creating a marketing strategy" << endl;
  }
};

class SalesManager : public Employee
{
public:
  SalesManager(const string &empName, int empId) : Employee(empName, empId) {}

  void boostSales() const
  {
    cout << "Sales Manager boosting sales" << endl;
  }
};

class BusinessDevelopmentManager : public MarketingManager, public SalesManager
{
public:
  // Because BOTH bases carry their own Employee sub-object, we pass the
  // employee details twice - once down each branch.
  BusinessDevelopmentManager(const string &empName, int empId)
      : MarketingManager(empName, empId), SalesManager(empName, empId) {}

  void coordinate() const
  {
    createMarketingStrategy(); // unambiguous: only MarketingManager has it
    boostSales();              // unambiguous: only SalesManager has it
    cout << "BDM coordinating business development" << endl;
    // display();  // would be AMBIGUOUS: two Employee sub-objects exist
  }
};

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << "--- 1. Single ---" << endl;
  Developer dev("Ramu Kaka", 101, "C++");
  dev.show();

  cout << "\n--- 2. Multiple ---" << endl;
  TechLead techLead("Anna Dev", 202, "Project X", 5);
  techLead.displayInfo();

  cout << "\n--- 3. Multilevel ---" << endl;
  HRDirector hrDirector("Lucy Madam", 303);
  hrDirector.handleHRDuties();
  hrDirector.manageHRDepartment();

  cout << "\n--- 4. Hierarchical ---" << endl;
  Manager mgr("Devi Lal", 404);
  Analyst ana("Sam Uncle", 505);
  mgr.approveLeaves();
  ana.buildReport();

  cout << "\n--- 5. Hybrid ---" << endl;
  BusinessDevelopmentManager bdManager("Neha Ma'am", 606);
  bdManager.coordinate();

  return 0;
}

/*
  ---------------------- OUTPUT ----------------------

  --- 1. Single ---
  Employee ctor  -> Ramu Kaka (#101)
  Employee: Ramu Kaka, ID: 101
  Specialization: Developer, Language: C++

  --- 2. Multiple ---
  Employee ctor  -> Anna Dev (#202)
  Employee: Anna Dev, ID: 202
  Manages project: Project X
  Leads a team of 5 members

  --- 3. Multilevel ---
  Employee ctor  -> Lucy Madam (#303)
  HRManager ctor
  HRDirector ctor
  HR Manager handling human-resources duties
  HR Director managing the whole HR department

  --- 4. Hierarchical ---
  Employee ctor  -> Devi Lal (#404)
  Employee ctor  -> Sam Uncle (#505)
  Devi Lal approves leave requests
  Sam Uncle builds the quarterly report

  --- 5. Hybrid ---
  Employee ctor  -> Neha Ma'am (#606)
  Employee ctor  -> Neha Ma'am (#606)
  Marketing Manager creating a marketing strategy
  Sales Manager boosting sales
  BDM coordinating business development

  ---------------------- WHY (key points) ----------------------

  * __FUNCTION__ prints "Employee", "HRManager", "HRDirector" from inside
    each ctor - it resolves to the enclosing function's / class ctor's name.

  * Multilevel (case 3): the chain constructs top-down
    Employee -> HRManager -> HRDirector, so you see all three ctor lines
    in that order for a single HRDirector object.

  * Hierarchical (case 4): Manager and Analyst are independent siblings.
    Each object gets its OWN Employee sub-object, hence two "Employee ctor"
    lines, one per object.

  * Hybrid (case 5): BusinessDevelopmentManager reaches Employee through
    BOTH MarketingManager and SalesManager, so it contains TWO separate
    Employee sub-objects - that is why "Employee ctor -> Neha Ma'am (#606)"
    prints twice, and why calling display() directly would be ambiguous.
    (The classic "diamond"; virtual inheritance is the fix, covered later.)
*/
