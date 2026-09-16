# Poly morphism in C++

1. Similar to Polymorphism in Life
   EG: RAHUL can be a boy, brother of a sister/brother, Sibling to sister or brother, Husband to wife, son to a parent, parent ot a child
   So Rahul is polymorphic in LIFE

2. Plymorphism = Many Forms

3. Thew Ability of a single Function / Operator to work uin different based on object it is acting or actual need

4. A phenomenon that allows an Object to have secveral different forms and behaviours

5. Types:
   --- Compile Time Polymorphism => STATIC
   --- Runtime Polymorphism => DYNAMIC

# Static Poly

- Compile time poly (STATIC) allowed by compiler
- TYPES:
  --- Function Overloading
  --- Operator Overloading

## Function Overloading

When a class contains multiple methods sharing a name but differing in argument count or argument type

If we use same function with same params gives error we cant redeclare, to redeclare must have diff type / number of arguments

```c++
class Add{
    public:
    int sum(int x, int y){return x + y;}
    int sum(int x, int y, int z){return x + y + z;}
    double sum(double x, double y){return x + y;}
}
```

# Operator Overloading

Wwhen operatro are overloaded they execvute user defined functions whenever used allowing for customised behaviour

```c++

```

liek if we write 4 + 5 + knows how to add them
if we write (3 + 5i) + (5  + 6i) + does not know how to add them ... hence we override + operator here, here it uses user feined function to perfoerm the task to execute addition of 2 complex numbers as we say how to add them
thats the meaning of user defined fucntion is executed in opeartor overload

- A + B whenever we write a + between complx num we want a function to get called to handle complex number addition written inside the Complex class itself
- When we write  A + B the + special function we wrote is called by A, bcoz A says mujhmei B plus kardo aur mai C ko return kardunga
- Something like a calles fucntion as A.func() and sends B as argument in tehre A.func(B)

Syntax to write this:

Return_Type Operator_To_Overload <op> (Args){
    ... Logic ...
}

- ermember the function name is operator Followed by operator we are overloading ... tell if its mandatory or not if yes how if no then how


## All operators whta can we overlocaded list
arithmetic
relational
logical
assignment
incerment decrement
fucntion call opeartor
subscript operator
member saccess opeartors
allocation deallocatrion
bitwise
otehr

# Runtime Polymorphism

COmpilation already done executable file is already made, comes in action when process is running

1. FUnction Ocverrirding : makes function polymorphic
2. Early VS Late Binding
3. Virtual Keyword : Way to achieve polymorphism by deferring binding decision to eruntime
4. Override Keyword : Helps to amke the intention clear and allows the compuiler to enforce overriding rules making your code sage and easirter to understand
5. Upcasting / Down casrting


see the code where we ioverride shape with circle and rectange


also upcasting :
- Base calss pointer var = address of Child class -> Shape *s = &c;
- this is upcasting : Upcasting means assigning the address of the derived class object to the base class pointer
 Parennt class ka pointer child class ke object ka address hold krke baitha hai


but doing ti still gave generic draiwng when we did shapeDrawing (&c) or &r wher esha[eDrawing has pointer ar to hold the address of child class object, still we couldnt call relevent draw method


# Early Binding

By fklow diageram explain

Shape box ahvig draw
       |
Circle Class having draw


on right of flow chart write : Circel c;
Shpe *s + &c;
s->draw();

now when we call s->draw() the compiler cant solve this confusion not that smart its dumb so when ever it sees s-> it binds it witht eh parent class only .. show with arrows in flow diagram


- Looks whihc type of obejt is created and binds with that object -> early binding
- hence even after shapeDrawing(&c) we get Generic draing


# Virtual Keyword

To solve this early binding thing we use virtual keyword
