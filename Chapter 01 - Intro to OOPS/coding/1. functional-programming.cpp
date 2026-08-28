#include <bits/stdc++.h>
using namespace std;

// =========================================================================
// Functional Programming Paradigm (Before OOP)
// =========================================================================
// Demonstrates how procedural/functional programming organizes data and
// functions separately, and the scaling/security bottlenecks that arise.
// =========================================================================

// ---------------- Global Data (Shared State) ----------------
// Problem: Global data has no privacy or access restrictions;
// any function across the codebase can read and mutate it.
string schoolName = "DPS";

// ---------------- Student Behaviour Functions ----------------
// Functions must take every piece of student data as separate parameters.

void study(int id, int age, string name)
{
    cout << name << " (id: " << id << ", age: " << age << ") is Studying at " << schoolName << endl;
}

void eat(int id, int age, string name)
{
    cout << name << " is Eating" << endl;
}

void sleep(int id, int age, string name)
{
    cout << name << " is Sleeping" << endl;
}

// ---------------- Scaling Attempt 1: Duplicate Variables ----------------
// Problem: Variables multiply exponentially; mixing up arguments is silently valid.
void duplicateVariables()
{
    int id1 = 1, id2 = 2, id3 = 3;
    int age1 = 20, age2 = 21, age3 = 19;
    string name1 = "Rahul", name2 = "Aman", name3 = "Simran";

    study(id1, age1, name1);
    study(id2, age2, name2);
    study(id3, age3, name3);

    // Compiles fine, but silently wrong - data mismatch bug
    study(id1, age2, name3);
}

// ---------------- Scaling Attempt 2: Parallel Arrays ----------------
// Problem: Arrays are uncoordinated; no single entity bounds id[i] to name[i].
void parallelArrays()
{
    int ids[3] = {1, 2, 3};
    int ages[3] = {20, 21, 19};
    string names[3] = {"Rahul", "Aman", "Simran"};

    for (int i = 0; i < 3; i++)
    {
        study(ids[i], ages[i], names[i]);
    }
}

// ---------------- Global State Pollution ----------------
// An unrelated function can silently corrupt global state without ownership.
void teach()
{
    cout << "Teaching a class at " << schoolName << endl;
    schoolName = "Hacked High";
}

// =========================================================================
// Main Execution Function
// =========================================================================
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // ---------------- 1. Single Student Representation ----------------
    int id = 1;
    int age = 20;
    string name = "Rahul";

    study(id, age, name);
    eat(id, age, name);
    sleep(id, age, name);

    // ---------------- 2. Scaling to Multiple Students ----------------
    duplicateVariables();

    // ---------------- 3. Parallel Arrays Approach ----------------
    parallelArrays();

    // ---------------- 4. Uncontrolled State Mutation ----------------
    teach();

    // Global data was silently mutated by an external function
    cout << "School is now: " << schoolName << endl;

    return 0;
}
