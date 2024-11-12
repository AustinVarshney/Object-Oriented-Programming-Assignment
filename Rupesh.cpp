#include <iostream>
#include <ctime>
using namespace std;

class Doctor
{
protected:
    int doctor_id;
    string doctor_name;
    string Specialization;

public:
    Doctor()
    {
        doctor_id = 0;
        doctor_name = "ABC";
        Specialization = "Heart";
    }
    Doctor(int d_id)
    {
        doctor_id = d_id;
    }
    Doctor(int d_id, string d_name, string spec)
    {
        doctor_id = d_id;
        doctor_name = d_name;
        Specialization = spec;
    }

    void displayDoctor()
    {
        cout << "Doctor Id : " << doctor_id << endl;
        cout << "Doctor Name : " << doctor_name << endl;
        cout << "Specialization : " << Specialization << endl;
        cout << "NAme length : " << doctor_name.length();
    }
};

class Patient
{
protected:
    int patient_id;
    int age;
    string patient_name;
    string symptoms;

public:
    Patient()
    {
        patient_id = 0;
        patient_name = "XYZ";
        age = 16;
        symptoms = "Fever";
    }
    Patient(int p_id)
    {
        patient_id = p_id;
    }
    Patient(int p_id, string p_name, int p_age, string p_symptoms)
    {
        patient_id = p_id;
        patient_name = p_name;
        age = p_age;
        symptoms = p_symptoms;
    }
    void displayPatient()
    {
        cout << "Patient Id : " << patient_id << endl;
        cout << "Patient Name : " << patient_name << endl;
        cout << "Age : " << age << endl;
        cout << "Symptoms : " << symptoms << endl;
    }
};

class Appointment : public Doctor, public Patient
{
    int appointment_id;
    time_t appointmentDate;

public:
    Appointment(int appt_id, int d_id, int p_id, time_t date) : appointment_id(appt_id), Doctor(d_id), Patient(p_id), appointmentDate(date)
    {
    }

    // void addAppointment(int doctor_id, int patient_id, int appointment_id)
    // {
    //     doctor_id = this->doctor_id;
    //     patient_id = this->patient_id;
    //     appointment_id = this->appointment_id;
    // }

    void displayAppointment()
    {
        cout << "Doctor Id =" << doctor_id << endl;
        cout << "Patient Id =" << patient_id << endl;
        cout << "Appointment Id =" << appointment_id << endl;
        cout << "Date =" << ctime(&appointmentDate) << endl;
    }
};

int main()
{
    cout << "------------Doctor's Details-------------" << endl;
    Doctor d1(101, "Dr.Ramlal", "Heart Surgeon");
    d1.displayDoctor();

    cout << endl;
    cout << "----------Patient's Details------------" << endl;
    Patient p1(1000, "Ram", 20, "Fever");
    p1.displayPatient();

    cout << endl;
    cout << "------------Appointment Details------------" << endl;
    // // Create a tm structure and set it to a specific date and time
    tm customTime = {};
    customTime.tm_year = 2024 - 1900; // Year since 1900 (e.g., 2024 - 1900 = 124)
    customTime.tm_mon = 10;           // Month (0-11, so 10 is November)
    customTime.tm_mday = 15;          // Day of the month (1-31)
    customTime.tm_hour = 14;          // Hour (0-23)
    customTime.tm_min = 30;           // Minute (0-59)
    customTime.tm_sec = 0;            // Second (0-59)

    // Convert tm structure to time_t
    time_t timeObject = mktime(&customTime);

    // Print the custom date and time using ctime
    cout << "Custom date and time: " << ctime(&timeObject);
    Appointment a1(101, 21, 22, timeObject);
    a1.displayAppointment();
    return 0;
}

/* This is the Code for Custom Time and Date Display*/

// my name is rupesh