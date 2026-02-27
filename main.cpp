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
void searchStudent() {
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;

    ifstream file("students.txt");
    Student s;
    bool found = false;

    while (file >> s.rollNo >> s.name >> s.marks) {
        if (s.rollNo == roll) {
            cout << "\nStudent Found:\n";
            s.display();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student not found.\n";
    }

    file.close();
}


int main() {
    int choice;

    do {
        cout << "\n===== Student Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display Students\n";
        cout << "3. Search Student\n";
        cout << "4. Exit\n";
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
                searchStudent();
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 4);

    return 0;
}
