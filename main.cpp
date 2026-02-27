#include <iostream>
#include <fstream>
#include <cstdio>

using namespace std;

// Function declarations
void addStudent();
void displayStudents();
void searchStudent();
void deleteStudent();
void updateStudent();
bool rollExists(int roll);

struct Student {
    int rollNo;
    string name;
    float marks;
};

int main() {
    int choice;

    do {
        cout << "\n========= Student Management System =========\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Update Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 5: updateStudent(); break;
            case 6: cout << "Exiting program...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}

// Check duplicate roll number
bool rollExists(int roll) {
    ifstream file("students.txt");
    Student s;

    while (file >> s.rollNo >> s.name >> s.marks) {
        if (s.rollNo == roll) {
            file.close();
            return true;
        }
    }

    file.close();
    return false;
}

// Add Student
void addStudent() {
    Student s;

    cout << "Enter Roll No: ";
    cin >> s.rollNo;

    if (rollExists(s.rollNo)) {
        cout << "Error: Roll number already exists!\n";
        return;
    }

    cout << "Enter Name: ";
    cin >> s.name;

    cout << "Enter Marks: ";
    cin >> s.marks;

    if (s.marks < 0 || s.marks > 100) {
        cout << "Invalid marks! Must be between 0 and 100.\n";
        return;
    }

    ofstream file("students.txt", ios::app);

    if (!file) {
        cout << "Error opening file!\n";
        return;
    }

    file << s.rollNo << " " << s.name << " " << s.marks << endl;
    file.close();

    cout << "Student added successfully!\n";
}

// Display Students
void displayStudents() {
    ifstream file("students.txt");

    if (!file) {
        cout << "No records found.\n";
        return;
    }

    Student s;

    cout << "\n---------------------------------\n";
    cout << "Roll No\tName\tMarks\n";
    cout << "---------------------------------\n";

    while (file >> s.rollNo >> s.name >> s.marks) {
        cout << s.rollNo << "\t"
             << s.name << "\t"
             << s.marks << endl;
    }

    file.close();
}

// Search Student
void searchStudent() {
    int roll;
    cout << "Enter Roll No to search: ";
    cin >> roll;

    ifstream file("students.txt");

    if (!file) {
        cout << "No records found.\n";
        return;
    }

    Student s;
    bool found = false;

    while (file >> s.rollNo >> s.name >> s.marks) {
        if (s.rollNo == roll) {
            cout << "\nStudent Found:\n";
            cout << "Roll No: " << s.rollNo << endl;
            cout << "Name: " << s.name << endl;
            cout << "Marks: " << s.marks << endl;
            found = true;
            break;
        }
    }

    if (!found)
        cout << "Student not found.\n";

    file.close();
}

// Delete Student
void deleteStudent() {
    int roll;
    cout << "Enter Roll No to delete: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file) {
        cout << "No records found.\n";
        return;
    }

    Student s;
    bool found = false;

    while (file >> s.rollNo >> s.name >> s.marks) {
        if (s.rollNo == roll) {
            found = true;
        } else {
            temp << s.rollNo << " "
                 << s.name << " "
                 << s.marks << endl;
        }
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student deleted successfully.\n";
    else
        cout << "Student not found.\n";
}

// Update Student
void updateStudent() {
    int roll;
    cout << "Enter Roll No to update: ";
    cin >> roll;

    ifstream file("students.txt");
    ofstream temp("temp.txt");

    if (!file) {
        cout << "No records found.\n";
        return;
    }

    Student s;
    bool found = false;

    while (file >> s.rollNo >> s.name >> s.marks) {
        if (s.rollNo == roll) {
            found = true;

            cout << "Enter new name: ";
            cin >> s.name;

            cout << "Enter new marks: ";
            cin >> s.marks;

            if (s.marks < 0 || s.marks > 100) {
                cout << "Invalid marks! Update cancelled.\n";
                temp << s.rollNo << " "
                     << s.name << " "
                     << s.marks << endl;
                continue;
            }
        }

        temp << s.rollNo << " "
             << s.name << " "
             << s.marks << endl;
    }

    file.close();
    temp.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (found)
        cout << "Student updated successfully.\n";
    else
        cout << "Student not found.\n";
}
