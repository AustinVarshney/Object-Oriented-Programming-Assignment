#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Patient Class
class Patient {
private:
    int id;
    string name;
    int age;
    string disease;

public:
    Patient(int pId, string pName, int pAge, string pDisease) 
        : id(pId), name(pName), age(pAge), disease(pDisease) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getDisease() const { return disease; }

    void displayInfo() const {
        cout << "Patient ID: " << id << "\nName: " << name << "\nAge: " << age << "\nDisease: " << disease << endl;
    }
};

// Doctor Class
class Doctor {
private:
    int id;
    string name;
    string specialization;

public:
    Doctor(int dId, string dName, string dSpecialization)
        : id(dId), name(dName), specialization(dSpecialization) {}

    int getId() const { return id; }
    string getName() const { return name; }
    string getSpecialization() const { return specialization; }

    void displayInfo() const {
        cout << "Doctor ID: " << id << "\nName: " << name << "\nSpecialization: " << specialization << endl;
    }
};

// Appointment Class
class Appointment {
private:
    int appointmentId;
    Patient patient;
    Doctor doctor;
    string date;

public:
    Appointment(int appId, const Patient &p, const Doctor &d, string appDate)
        : appointmentId(appId), patient(p), doctor(d), date(appDate) {}

    void displayInfo() const {
        cout << "Appointment ID: " << appointmentId << "\nDate: " << date << endl;
        cout << "Patient Info:\n";
        patient.displayInfo();
        cout << "Doctor Info:\n";
        doctor.displayInfo();
    }
};

// Healthcare Management System Class
class HealthcareSystem {
private:
    vector<Patient> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;

public:
    void addPatient() {
        int id, age;
        string name, disease;
        cout << "Enter Patient ID: ";
        cin >> id;
        cout << "Enter Patient Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Age: ";
        cin >> age;
        cout << "Enter Disease: ";
        cin.ignore();
        getline(cin, disease);
        
        patients.emplace_back(id, name, age, disease);
        cout << "Patient added successfully.\n";
    }

    void addDoctor() {
        int id;
        string name, specialization;
        cout << "Enter Doctor ID: ";
        cin >> id;
        cout << "Enter Doctor Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Specialization: ";
        getline(cin, specialization);

        doctors.emplace_back(id, name, specialization);
        cout << "Doctor added successfully.\n";
    }

    void scheduleAppointment() {
        int appId, patientId, doctorId;
        string date;
        
        cout << "Enter Appointment ID: ";
        cin >> appId;
        cout << "Enter Patient ID: ";
        cin >> patientId;
        cout << "Enter Doctor ID: ";
        cin >> doctorId;
        cout << "Enter Appointment Date (DD-MM-YYYY): ";
        cin.ignore();
        getline(cin, date);

        Patient *patient = nullptr;
        Doctor *doctor = nullptr;

        // Find the patient and doctor based on IDs
        for (auto &p : patients) {
            if (p.getId() == patientId) {
                patient = &p;
                break;
            }
        }

        for (auto &d : doctors) {
            if (d.getId() == doctorId) {
                doctor = &d;
                break;
            }
        }

        if (patient && doctor) {
            appointments.emplace_back(appId, *patient, *doctor, date);
            cout << "Appointment scheduled successfully.\n";
        } else {
            cout << "Patient or Doctor ID not found.\n";
        }
    }

    void viewAppointments() const {
        if (appointments.empty()) {
            cout << "No appointments scheduled.\n";
            return;
        }
        
        for (const auto &app : appointments) {
            app.displayInfo();
            cout << "---------------------------\n";
        }
    }
};

// Main Function
int main() {
    HealthcareSystem system;
    int choice;

    do {
        cout << "\n---- Healthcare Management System ----\n";
        cout << "1. Add Patient\n";
        cout << "2. Add Doctor\n";
        cout << "3. Schedule Appointment\n";
        cout << "4. View Appointments\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                system.addPatient();
                break;
            case 2:
                system.addDoctor();
                break;
            case 3:
                system.scheduleAppointment();
                break;
            case 4:
                system.viewAppointments();
                break;
            case 5:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
