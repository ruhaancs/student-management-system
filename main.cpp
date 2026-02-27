#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Student {
public:
    int rollNo;
    string name;
    float marks;

    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "Roll No: " << rollNo
             << " | Name: " << name
             << " | Marks: " << marks << endl;
    }
};

void addStudent() {
    Student s;
    s.input();

    ofstream file("students.txt", ios::app);
    file << s.rollNo << " " << s.name << " " << s.marks << endl;
    file.close();

    cout << "Student added successfully!\n";
}

void displayStudents() {
    ifstream file("students.txt");
    Student s;

    cout << "\n--- Student Records ---\n";
    while (file >> s.rollNo >> s.name >> s.marks) {
        s.display();
    }
    file.close();
}

int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 3);

    return 0;
}
