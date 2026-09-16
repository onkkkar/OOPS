#include <bits/stdc++.h>
using namespace std;

class Shape
{
public:
  void draw()
  {
    cout << "Generic Drawing !!" << endl;
  }
};

class Circle : public Shape
{
  // We did inherit all methods and properties of Shape inside Circle in public mode which means:
  // public -> comes as public
  // private -> comes as private
  // protected -> comes as protected

public:
  // Overriding the draw method of the base class Shape
  void draw()
  {
    cout << "Circle Drawing !!" << endl;
  }
};

class Rectangle : public Shape
{
  // We did inherit all methods and properties of Shape inside Rectangle in public mode which means:
  // public -> comes as public
  // private -> comes as private
  // protected -> comes as protected

public:
  // Overriding the draw method of the base class Shape
  void draw()
  {
    cout << "Rectangle Drawing !!" << endl;
  }
};

void shapeDrawing(Shape *s)
{
  s->draw(); // This will call the draw method of the base class Shape
}

int main()
{
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  Circle c;
  c.draw(); // Circle Drawing !!

  Rectangle r;
  r.draw(); // Rectangle Drawing !!

  // Upcasting
  Shape *v = &c; //
  v->draw();     // Circle Drawing !!

  // Smae hapening here as we defined a pointer holder to take the &c or &c in shapeDrawing function params
  shapeDrawing(&c); // Generic Drawing !!
  shapeDrawing(&r); // Generic Drawing !!

  // THis didnt let us acheieve the relevent calls of circle or reactangel we want !! yet

  return 0;
}
