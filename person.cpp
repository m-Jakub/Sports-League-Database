#include "declarations.h"
#include <iostream>

using namespace std;

Person::Person(string name, int ID)
    : full_name(name), salary(0), ID(ID)
{
}

Person::~Person() = default;

int Person::getID() const
{
    return ID;
}

string Person::getFullName() const
{
    return full_name;
}

int Person::getSalary() const
{
    return salary;
}

// to do: wrong input management
bool Person::changeSalary(int newSalary)
{
    if (newSalary >= 0)
    {
        salary = newSalary;
        return true;
    }
    cerr << "Warning: Salary can't be lower than 0, salary change unsuccesful" << endl;
    return false;
}

void Person::print()
{
    cout << "Full name: " << full_name << endl;
    cout << "ID: " << ID << endl;
    cout << "Salary: " << salary << endl;
}

void Person::printNameAndID()
{
    cout << getFullName() << "(ID: " << getID() << ")" << endl;
}