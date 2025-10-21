#include "employee.h"

void addEmployee();
void viewEmployees();
void searchEmployee();
void editEmployee();
void deleteEmployee();

int main() {
    int choice;
    do {
        cout << "\n-----------------------------------------\n";
        cout << "     EMPLOYEE MANAGEMENT SYSTEM\n";
        cout << "-----------------------------------------\n";
        cout << "1. Add Employee\n";
        cout << "2. View Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Edit Employee\n";
        cout << "5. Delete Employee\n";
        cout << "6. Exit\n";
        cout << "-----------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addEmployee(); break;
            case 2: viewEmployees(); break;
            case 3: searchEmployee(); break;
            case 4: editEmployee(); break;
            case 5: deleteEmployee(); break;
            case 6: cout << "\nDeveloped by Bihar Gourav\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 6);

    return 0;
}

void addEmployee() {
    ofstream out("employees.dat", ios::binary | ios::app);
    Employee emp;
    emp.input();
    emp.writeToFile(out);
    out.close();
    cout << "Employee added successfully!\n";
}

void viewEmployees() {
    ifstream in("employees.dat", ios::binary);
    Employee emp;
    cout << "\n" << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(15) << "Department"
         << setw(10) << "Salary" << endl;
    cout << "-------------------------------------------------------------\n";
    while (emp.readFromFile(in)) {
        emp.display();
    }
    in.close();
}

void searchEmployee() {
    ifstream in("employees.dat", ios::binary);
    Employee emp;
    int id, found = 0;
    cout << "Enter Employee ID to search: ";
    cin >> id;

    while (emp.readFromFile(in)) {
        if (emp.getId() == id) {
            cout << "\nEmployee Found:\n";
            emp.display();
            found = 1;
            break;
        }
    }
    if (!found)
        cout << "Employee not found!\n";
    in.close();
}

void editEmployee() {
    fstream file("employees.dat", ios::binary | ios::in | ios::out);
    Employee emp;
    int id;
    cout << "Enter Employee ID to edit: ";
    cin >> id;

    while (file.read(reinterpret_cast<char*>(&emp), sizeof(Employee))) {
        if (emp.getId() == id) {
            emp.update();
            file.seekp(-sizeof(Employee), ios::cur);
            file.write(reinterpret_cast<char*>(&emp), sizeof(Employee));
            cout << "Record updated successfully!\n";
            file.close();
            return;
        }
    }
    cout << "Employee not found!\n";
    file.close();
}

void deleteEmployee() {
    ifstream in("employees.dat", ios::binary);
    ofstream out("temp.dat", ios::binary);
    Employee emp;
    int id;
    cout << "Enter Employee ID to delete: ";
    cin >> id;

    while (emp.readFromFile(in)) {
        if (emp.getId() != id)
            emp.writeToFile(out);
    }
    in.close();
    out.close();
    remove("employees.dat");
    rename("temp.dat", "employees.dat");
    cout << "Employee deleted successfully!\n";
}
