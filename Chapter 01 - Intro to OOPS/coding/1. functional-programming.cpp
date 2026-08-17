#include <bits/stdc++.h>
using namespace std;

// Global Data
string schoolName = "DPS";

// Functions for Student Behaviours
void study(int id, int age, string name)
{
    cout << name << " (id: " << id << ", age: " << age << ") is Studying" << endl;
}

void eat(int id, int age, string name)
{
    cout << name << " is Eating" << endl;
}

void sleep(int id, int age, string name)
{
    cout << name << " is Sleeping" << endl;
}

// ---- scaling to just 3 students ----
void duplicateVariables()
{
    int id1 = 1, id2 = 2, id3 = 3;
    int age1 = 20, age2 = 21, age3 = 19;
    string name1 = "Rahul", name2 = "Aman", name3 = "Simran";

    study(id1, age1, name1);
    study(id2, age2, name2);
    study(id3, age3, name3);

    // compiles fine, but silently wrong — mixed up students
    study(id1, age2, name3);
}

// --- scaling to just 3 students, but with parallel arrays ---
void parallelArrays()
{
    int ids[3] = {1, 2, 3};
    int ages[3] = {20, 21, 19};
    string names[3] = {"Rahul", "Aman", "Simran"};

    for (int i = 0; i < 3; i++){
        study(ids[i], ages[i], names[i]);
    }
}

// --- unrelated to students, but can still read schoolName — global data has no privacy ---
void teach()
{
    cout << "Teaching a class at " << schoolName << endl;
}

int main()
{
    // Just 1 Student
    int id = 1;
    int age = 20;
    string name = "Rahul";

    study(id, age, name);
    eat(id, age, name);
    sleep(id, age, name);

    // Scaling to just 3 Students
    duplicateVariables();

    // Scaling to just 3 Students, but with parallel arrays
    parallelArrays();

    teach();

    return 0;
}
