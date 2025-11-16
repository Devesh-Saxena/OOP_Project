#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Patient {
public:
    string id, name, age, disease;

    void input() {
        cout << "Enter Patient ID: ";
        cin >> id;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Disease: ";
        cin >> disease;
    }

    void display() {
        cout << "ID: " << id << " | Name: " << name 
             << " | Age: " << age << " | Disease: " << disease << endl;
    }
};

void addPatient() {
    Patient p;
    p.input();

    ofstream fout("patients.txt", ios::app);
    fout << p.id << " " << p.name << " " << p.age << " " << p.disease << "\n";
    fout.close();

    cout << "\nPatient added successfully!\n";
}

void viewPatients() {
    ifstream fin("patients.txt");
    Patient p;

    cout << "\n---- Patient Records ----\n";

    if (!fin) {
        cout << "No record found!\n";
        return;
    }

    bool empty = true;
    while (fin >> p.id >> p.name >> p.age >> p.disease) {
        empty = false;
        p.display();
    }

    if (empty) cout << "No records available!\n";

    fin.close();
}

void removePatient() {
    string removeID;
    cout << "Enter Patient ID to remove: ";
    cin >> removeID;

    ifstream fin("patients.txt");
    ofstream temp("temp.txt");

    Patient p;
    bool found = false;

    while (fin >> p.id >> p.name >> p.age >> p.disease) {
        if (p.id != removeID) {
            temp << p.id << " " << p.name << " " << p.age << " " << p.disease << "\n";
        } else {
            found = true;
        }
    }

    fin.close();
    temp.close();

    remove("patients.txt");
    rename("temp.txt", "patients.txt");

    if (found) {
        cout << "\nPatient record removed successfully!\n";
    } else {
        cout << "\nRecord not found!\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n===== Hospital Management System =====\n";
        cout << "1. Add Patient\n";
        cout << "2. View Patients\n";
        cout << "3. Remove Patient\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addPatient();
            break;
        case 2:
            viewPatients();
            break;
        case 3:
            removePatient();
            break;
        case 4:
            cout << "Exiting Program...\n";
            return 0;
        default:
            cout << "Invalid Choice! Try again.\n";
        }
    }
}
