#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Patient
{
protected:
    int pId, age;
    string name, symptoms;

public:
    Patient()
    {
    }
    Patient(int pId, string name, int age, string symptoms) : pId(pId), age(age), name(name), symptoms(symptoms) {};

    void patientInfo()
    {
        cout << "Patient Name : " << name << endl;
        cout << "Age : " << age << endl;
        cout << "Symptoms : " << symptoms << endl;
    }

    int getId() { return pId; }
    string getName() { return name; }
    int getAge() { return age; }
    string getSymp() { return symptoms; }
};

class Doctor
{
protected:
    int dId;
    string name, specialization;

public:
    vector<int> pIds;
    Doctor()
    {
        // this->dId = dId;
    }
    Doctor(int dId, string name, string specialization) : dId(dId), name(name), specialization(specialization) {};

    void doctorInfo()
    {
        cout << "Doctor Name : " << name << endl;
        cout << "Specialization : " << specialization << endl;
    }

    int getId() { return dId; }
    string getName() { return name; }
    string getSpecialization() { return specialization; }
    vector<int> getPatientsId() { return pIds; }
};

class Appointment
{
protected:
    int appointmentId, pId, dId;

public:
    Appointment() {}
    Appointment(int apptId, int pId, int dId) : appointmentId(apptId), pId(pId), dId(dId)
    {
    }

    void bookAppointment()
    {
        cout << "Enter Appointment ID : ";
        cin >> appointmentId;

        cout << "Enter Patient Id : ";
        cin >> pId;

        cout << "Enter Doctor ID : ";
        cin >> dId;
    }

    void displayAppointment(vector<Doctor> &doctors, vector<Patient> &patients)
    {
        cout << "Appointment Id : " << appointmentId << endl;
        cout << "------x--------Doctor Details ------x------" << endl;

        for (auto &doctor : doctors)
        {
            if (doctor.getId() == dId)
            {
                doctor.doctorInfo();
            }
        }

        cout << "------x--------Patient Details ------x------" << endl;
        for (auto &patient : patients)
        {
            if (patient.getId() == pId)
            {
                patient.patientInfo();
            }
        }
    }

    int getDoctorId()
    {
        return dId;
    }

    int getPatientId()
    {
        return pId;
    }
};

class Management
{
    vector<Doctor> doctors;
    vector<Patient> patients;
    vector<Appointment> appointment;

public:
    void viewPatients()
    {
        if (patients.size() == 0)
        {
            cout << "No patient registered!" << endl;
            return;
        }
        cout << "Patients Lists:\n";
        cout << setw(5) << "pID" << setw(15) << "Name" << setw(5) << "Age" << "  " << "Symptoms" << endl;
        for (auto &patient : patients)
        {
            cout << setw(5) << patient.getId() << setw(15) << patient.getName() << setw(5) << patient.getAge() << "  " << patient.getSymp() << endl;
        }
    }

    void viewDoctors()
    {
        if (doctors.size() == 0)
        {
            cout << "No Doctor is available!" << endl;
            return;
        }
        cout << "Doctors List:\n";
        cout << setw(5) << "dID" << "   " << "Name" << "   " << "Specialization" << "   " << "PatientIds" << endl;
        for (auto &doctor : doctors)
        {
            cout << setw(5) << doctor.getId() << "   " << doctor.getName() << "   " << doctor.getSpecialization() << "   ";
            for (auto &pId : doctor.pIds)
            {
                cout << pId << ",";
            }
            cout << endl;
        }
    }

    int addPatient()
    {
        int pId, age;
        string name, symptoms;

        cout << "Enter the Patient Id : ";
        cin >> pId;
        cout << "Enter the Patient Name : ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter the age : ";
        cin >> age;
        cout << "What are your symptoms ?\n";
        cin.ignore();
        getline(cin, symptoms);

        for (auto &patient : patients)
        {
            if (pId == patient.getId())
            {
                cout << "Patient Id is already created! Please Enter a different Patient Id.\n";
                return 0;
            }
        }

        patients.emplace_back(pId, name, age, symptoms);
        cout << "Patient is added successfully!\n";
        return 0;
    }

    int addDoctors()
    {
        int dId;
        string name, specialization;

        cout << "Enter the Doctor Id : ";
        cin >> dId;
        cout << "Enter the Doctor Name : ";
        cin.ignore();
        getline(cin, name);
        cout << "What are your Specialization ?\n";
        cin.ignore();
        getline(cin, specialization);

        for (auto &doctor : doctors)
        {
            if (dId == doctor.getId())
            {
                cout << "Doctor Id is already created! Please Enter a different Doctor Id.\n";
                return 0;
            }
        }

        doctors.emplace_back(dId, name, specialization);
        cout << "Doctor is added successfully!\n";
        return 0;
    }

    void addAppointment()
    {
        Appointment appt;

        // Take All Values to book the appointment
        appt.bookAppointment();

        Patient *patient = nullptr;
        Doctor *doctor = nullptr;

        // check for Particular doctor,  He/She is available in the Hospital.
        for (auto &d : doctors)
        {
            if (appt.getDoctorId() == d.getId())
            {
                doctor = &d;
                break;
            }
        }

        // check for Particular Patient,  He/She books an appointment in the Hospital.
        for (auto &p : patients)
        {
            if (appt.getPatientId() == p.getId())
            {
                patient = &p;
                break;
            }
        }

        // check for Both Patient and Doctor there
        if (patient && doctor)
        {
            appointment.push_back(appt);
            cout << "Appointment Scheduled Successfully" << endl;
        }
        else
        {
            if (!doctor)
                cout << "Appointment Failed! Doctor not registered in Hospital." << endl;
            if (!patient)
                cout << "Appointment Failed! Patient does not exist." << endl;
        }
    }

    void viewAppointments()
    {
        if (appointment.empty())
        {
            cout << "No appointments scheduled!" << endl;
            return;
        }
        for (auto &appt : appointment)
        {
            appt.displayAppointment(doctors, patients);
            cout << "===================================================" << endl;
        }
    }
};

int main()
{
    Management system;
    int choice;
    do
    {
        cout << "1. View Patients\n2. Add Patients\n3. View Doctors\n4. Add Doctors\n5. Add Appointment\n6. View Appointments\n7. Exit\n";
        cout << "Enter a Number : ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.viewPatients();
            cout << "===============================================================\n";
            break;
        case 2:
            system.addPatient();
            cout << "===============================================================\n";
            break;
        case 3:
            system.viewDoctors();
            cout << "===============================================================\n";
            break;
        case 4:
            system.addDoctors();
            cout << "===============================================================\n";
            break;
        case 5:
            system.addAppointment();
            cout << "===============================================================\n";
            break;
        case 6:
            system.viewAppointments();
            cout << "===============================================================\n";
            break;
        case 7:
            cout << "-------------- Thank You for the visit --------------\n";
            break;
        default:
            cout << "Invalid Number\n";
            cout << "---------TRY AGAIN---------\n";
            cout << "===============================================================\n";
        }
    } while (choice != 7);
    return 0;
}
