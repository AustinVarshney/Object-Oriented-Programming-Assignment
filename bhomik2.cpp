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
  Patient(int pId, string name, int age, string symptoms) : pId(pId), age(age), name(name), symptoms(symptoms) {};

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

  Doctor(int dId, string name, string specialization) : dId(dId), name(name), specialization(specialization) {};

  int getId() { return dId; }
  string getName() { return name; }
  string getSpecialization() { return specialization; }
  vector<int> getPatientsId() { return pIds; }
};

class Bill
{
  int bId;
  int amount;
  string status;
  int pId;
  vector<Patient> &patients;

public:
  Bill(int bId, int pId, int amount, string status, vector<Patient> &patients) : bId(bId), pId(pId), amount(amount), status(status), patients(patients) {};
  int getId() { return bId; }
  int getpId() { return pId; }
  int getAmount() { return amount; }
  string getStatus() { return status; }
  string getName()
  {

    for (auto &itr : patients)
    {
      if (pId == itr.getId())
      {
        return itr.getName();
      }
    }
    return "unknown";
  }
};

class Management
{
public:
  void viewPatients(vector<Patient> &patients)
  {
    cout << "Patients Lists:\n";
    cout << setw(5) << "pID" << setw(15) << "Name" << setw(5) << "Age" << "  " << "Symptoms" << endl;
    for (auto &patient : patients)
    {
      cout << setw(5) << patient.getId() << setw(15) << patient.getName() << setw(5) << patient.getAge() << "  " << patient.getSymp() << endl;
    }
  }

  void viewDoctors(vector<Doctor> &doctors)
  {
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
  void viewBill(vector<Bill> &bills)
  {
    cout << "Bill List:\n";
    cout << setw(5) << "bID" << "   " << "pID" << "   " << "Name" << "   " << "Amount" << "   " << "Status" << endl;
    for (auto &itr : bills)
    {
      cout << setw(5) << itr.getId() << "   " << itr.getpId() << "   " << itr.getName() << "   " << itr.getAmount() << "   " << itr.getStatus() << "   " << endl;
    }
  }

  int addPatient(vector<Patient> &patients)
  {
    static int pId = 1;
    int age;
    string name, symptoms;

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
        pId += 1;
        patients.emplace_back(pId, name, age, symptoms);
        cout << "Patient is added successfully!\n";

        return 0;
      }
    }

    patients.emplace_back(pId, name, age, symptoms);
    cout << "Patient is added successfully!\n";
    return 0;
  }

  int addDoctors(vector<Doctor> &doctors)
  {
    static int dId = 1;
    string name, specialization;

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
        dId += 1;
        doctors.emplace_back(dId, name, specialization);
        cout << "Doctor is added successfully!\n";

        return 0;
      }
    }

    doctors.emplace_back(dId, name, specialization);
    cout << "Doctor is added successfully!\n";
    return 0;
  }

  int addBill(vector<Bill> &bills, vector<Patient> &patients)
  {
    static int bId = 0;
    int amount;
    string status;
    int pId;
    cout << "Enter the patient's id : ";
    cin >> pId;
    cout << "enter the amount value : \n";
    cin >> amount;
    cout << "Enter the status : \n";
    cin.ignore();
    getline(cin, status);
    bool patientFound = false;

    for (auto &itr : patients)
    {
      if (pId == itr.getId())
      {

        patientFound = true;
        break;
      }
    }

    if (patientFound)
    {

      bId += 1;
      bills.emplace_back(bId, pId, amount, status, patients);
      cout << "Bill is added successfully!\n";
    }
    else
    {
      cout << "No patient found with this ID!\n";
    }

    return 0;
  };
};

int main()
{
  vector<Patient> patients;
  vector<Doctor> doctors;
  vector<Bill> bills;

  Management system;

  int choice;
  do
  {
    cout << "1. View Patients\n";
    cout << "2. Add Patients\n";
    cout << "3. View Doctors\n";
    cout << "4. Add Doctors\n";
    cout << "5. View Bill\n";
    cout << "6. Add Bill\n";
    cout << "7. Exit\n";
    cout << "Enter a Number : ";
    cin >> choice;

    switch (choice)
    {
    case 1:
      system.viewPatients(patients);
      cout << "===============================================================\n";
      break;
    case 2:
      system.addPatient(patients);
      cout << "===============================================================\n";
      break;
    case 3:
      system.viewDoctors(doctors);
      cout << "===============================================================\n";
      break;
    case 4:
      system.addDoctors(doctors);
      cout << "===============================================================\n";
      break;
    case 5:
      system.viewBill(bills);
      cout << "===============================================================\n";
      break;
    case 6:
      system.addBill(bills, patients);
      cout << "===============================================================\n";
      break;
    case 7:
      cout << "-------------- Thank You for the visit --------------";
      break;

    default:
      cout << "Invalid Number\n";
      cout << "---------TRY AGAIN---------\n";
      cout << "===============================================================\n";
    }
  } while (choice != 7);
  return 0;
}