#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

class Employee {
private:
    int id;
    string name;
    string department;
    double salary;

public:
    Employee() : id(0), salary(0.0) {}

    void input() {
        cout << "\nEnter Employee ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, department);
        cout << "Enter Salary: ";
        cin >> salary;
    }

    void display() const {
        cout << left << setw(10) << id
             << setw(20) << name
             << setw(15) << department
             << setw(10) << salary << endl;
    }

    int getId() const { return id; }

    // Serialization (write)
    void writeToFile(ofstream &out) const {
        out.write(reinterpret_cast<const char*>(this), sizeof(Employee));
    }

    // Deserialization (read)
    bool readFromFile(ifstream &in) {
        return in.read(reinterpret_cast<char*>(this), sizeof(Employee));
    }

    void update() {
        cout << "\nEditing Employee ID: " << id << endl;
        cin.ignore();
        cout << "Enter New Name: ";
        getline(cin, name);
        cout << "Enter New Department: ";
        getline(cin, department);
        cout << "Enter New Salary: ";
        cin >> salary;
    }
};

#endif
