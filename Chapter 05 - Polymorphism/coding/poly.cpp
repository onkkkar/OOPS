#include <bits/stdc++.h>
using namespace std;

class Add
{
public:
  // Function Overloading: Same function name with different parameters (number or type)

  //  1
  int add(int a, int b)
  {
    return a + b;
  }

  // 2
  int sum(int a, int b, int c)
  {
    return a + b + c;
  }

  // 3
  double add(double a, double b)
  {
    return a + b;
  }
};

// Operator Overloading: Same operator with different parameters (number or type)
class Complex
{
public:
  // A Complex number has two parts: real and imaginary
  // Written as a + bi, where a is the real part and b is the imaginary part and i is Iota (√-1)

  int real, imaginary;

  // default ctor
  // When no values are passed, the default constructor initializes the real and imaginary parts to -1
  Complex()
  {
    real = imaginary = -1;
  }

  // parameterized ctor
  Complex(int r, int i)
  {
    real = r;
    imaginary = i;
  }

  // Print Complex number in the form of a + bi
  void print()
  {
    cout << this->real << " + " << this->imaginary << "i" << endl;
  }

  // Overload the + operator : To add two Complex numbers
  // Rule to add Complex numbers: (a + bi) + (c + di) = (a + c) + (b + d)i

  // Return type: Complex
  // Function name: operator+, where operator is function name and + is the operator to be overloaded
  // Complex &B : B argument, taken by ref a s&B so taht no copy is created
  Complex operator+(const Complex &B)
  {
    // this points to -> A instance
    Complex temp;                                   // a temperary complex number to store the result of addition
    temp.real = this->real + B.real;                // Real : a + c
    temp.imaginary = this->imaginary + B.imaginary; // Imaginary : (b + d)i
    return temp;
  }

  // Overload the - operator : To add two Complex numbers
  // Rule to add Complex numbers: (a + bi) + (c + di) = (a + c) + (b + d)i

  // Return type: Complex
  // Function name: operator-, where operator is function name and - is the operator to be overloaded
  // Complex &B : B argument, taken by ref a s&B so taht no copy is created
  Complex operator-(const Complex &B)
  {
    // this points to -> A instance
    Complex temp;                                   // a temperary complex number to store the result of addition
    temp.real = this->real - B.real;                // Real : a - c
    temp.imaginary = this->imaginary - B.imaginary; // Imaginary : (b - d)i
    return temp;
  }

  // Overload the = operator : To add two Complex numbers
  // Rule to add Complex numbers: (a + bi) + (c + di) = (a + c) + (b + d)i

  // Return type: Complex
  // Function name: operator==, where operator is function name and == is the operator to be overloaded
  // Complex &B : B argument, taken by ref a s&B so taht no copy is created
  bool operator==(const Complex &B)
  {
    // this -> A instance
    return (this->real == B.real && this->imaginary == B.imaginary);
  }
};

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  // Create an object of the Add class
  Add obj;
  cout << "O/P of 2 integers: " << obj.add(5, 10) << endl;     // Calls the first add method
  cout << "O/P of 2 doubles: " << obj.add(5.5, 10.5) << endl;  // Calls the second add method
  cout << "O/P of 3 integers: " << obj.sum(5, 10, 15) << endl; // Calls the sum method

  // Complex number addition using operator overloading
  Complex c1(5, 10);
  c1.print();

  Complex c2(15, 20);
  c2.print();

  Complex c3 = c1 + c2; // Using the overloaded + operator
  c3.print();

  Complex c4 = c1 - c2; // Using the overloaded - operator
  c4.print();

  bool c5 = c1 == c2; // Using the overloaded == operator
  if (c5)
  {
    cout << "Both Complex Numbers are equal" << endl;
  }
  else
  {
    cout << "Both Complex Numbers are not equal" << endl;
  }

  return 0;
}
