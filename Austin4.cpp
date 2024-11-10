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

class Appointment{
  int aId, pId, dId, date, time;
  vector<Patient> &patients;
  vector<Doctor> &doctors;

public:
  Appointment(int aId, int dId, int pId, int date, int time, vector<Patient> &patients, vector<Doctor> &doctors) : aId(aId), dId(dId), pId(pId), date(date), time(time), patients(patients), doctors(doctors) {};
  int getId() { return aId; }
  int getpId() { return pId; }
  int getdId() { return dId; }
  int getDate() { return date; }
  int getTime() { return time; }
  
  string getPatientName(){
    for (auto &itr : patients){
      if (pId == itr.getId()){
        return itr.getName();
      }
    }
    return "unknown";
  }

  string getDoctorName(){

    for (auto &itr : doctors){
      if (dId == itr.getId()){
        return itr.getName();
      }
    }
    return "unknown";
  }
};

class Bill{
  int bId, amount, pId;
  string status;
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

class Prescription{
  int dId, pId, prId;
  string prescription;

public:
  Prescription(int prId, int dId, int pId, std::string prescription) : prId(prId), dId(dId), pId(pId), prescription(prescription) {};

  int getId() { return prId; }
  int getDoctorId() { return dId; }
  int getPatientId() { return pId; }
  string getPrescription() { return prescription; }
};

bool checkDoctorId(vector<Doctor> &doctors, int id){
  bool check = false;
  for (auto &doctor : doctors){
    if (id == doctor.getId()){
      check = true;
      break;
    }
  }
  return check;
};
bool checkPatientId(vector<Patient> &patients, int id){
  bool check = false;
  for (auto &patient : patients){
    if (id == patient.getId()){
      check = true;
      break;
    }
  }
  return check;
};

class Management{
public:
  void viewPatients(vector<Patient> &patients){
    cout<<"Patients Lists:\n";
    cout<<setw(5)<<"pID"<<setw(15)<<"Name"<<setw(5)<<"Age"<<"  "<<"Symptoms"<<endl;
    for (auto &patient : patients){
      cout<<setw(5)<<patient.getId()<<setw(15)<<patient.getName()<<setw(5)<<patient.getAge()<<"  "<<patient.getSymp()<<endl;
    }
  }

  void viewDoctors(vector<Doctor> &doctors)
  {
    cout<<"Doctors List:\n";
    cout<<setw(5)<<"dID"<<"   "<<"Name"<<"   "<<"Specialization"<<"   "<<"PatientIds"<<endl;
    for (auto &doctor : doctors){
      cout<<setw(5)<<doctor.getId()<<"   "<<doctor.getName()<<"   "<<doctor.getSpecialization()<<"   ";
      for (auto &pId : doctor.pIds){
        cout<<pId<<",";}
      cout<<endl;
    }
  }
  void viewBill(vector<Bill> &bills){
    cout<<"Bill List:\n";
    cout<<setw(5)<<"bID"<<"   "<<"pID"<<"   "<<"Name"<<"   "<<"Amount"<<"   "<<"Status"<<endl;
    for (auto &itr : bills)
    {
      cout<<setw(5)<<itr.getId()<<"   "<<itr.getpId()<<"   "<<itr.getName()<<"   "<<itr.getAmount()<<"   "<<itr.getStatus()<<"   "<<endl;
    }
  }
  void viewAppointment(vector<Appointment> &appointment){
    cout<<"Appointment List:\n";
    cout<<setw(5)<<"aID"<<"   "<<"pID"<<"   "<<"Patient Name"<<"   "<<"dID"<<"   "<<"DoctorName"<<"   "<<"Date"<<"    "<<"Time "<<endl;
    for (auto &itr : appointment)
    {
      cout<<setw(5)<<itr.getId()<<"   "<<itr.getpId()<<"   "<<itr.getPatientName()<<"   "<<itr.getdId()<<"   "<<itr.getDoctorName()<<"   "<<itr.getDate()<<"   "<<itr.getTime()<<endl;
    };
  };

  int addPatient(vector<Patient> &patients){
    static int pId = 1;
    int age;
    string name, symptoms;

    cout<<"Enter the Patient Name : ";
    cin.ignore();
    getline(cin, name);
    cout<<"Enter the age : ";
    cin >> age;
    cout<<"What are your symptoms ?\n";
    cin.ignore();
    getline(cin, symptoms);

    for (auto &patient : patients){
      if (pId == patient.getId()){
        pId += 1;
        patients.emplace_back(pId, name, age, symptoms);
        cout<<"Patient is added successfully!\n";

        return 0;
      }
    }

    patients.emplace_back(pId, name, age, symptoms);
    cout<<"Patient is added successfully!\n";
    return 0;
  }

  int addDoctors(vector<Doctor> &doctors){
    static int dId = 1;
    string name, specialization;

    cout<<"Enter the Doctor Name : ";
    cin.ignore();
    getline(cin, name);
    cout<<"What are your Specialization ?\n";
    cin.ignore();
    getline(cin, specialization);

    for (auto &doctor : doctors){
      if (dId == doctor.getId()){
        dId += 1;
        doctors.emplace_back(dId, name, specialization);
        cout<<"Doctor is added successfully!\n";

        return 0;
      }
    }

    doctors.emplace_back(dId, name, specialization);
    cout<<"Doctor is added successfully!\n";
    return 0;
  }

  int addBill(vector<Bill> &bills, vector<Patient> &patients){
    static int bId = 0;
    int amount;
    string status;
    int pId;
    cout<<"Enter the patient's id : ";
    cin >> pId;
    cout<<"enter the amount value : \n";
    cin >> amount;
    cout<<"Enter the status : \n";
    cin.ignore();
    getline(cin, status);
    bool patientFound = false;

    for (auto &itr : patients){
      if (pId == itr.getId()){

        patientFound = true;
        break;
      }
    }

    if (patientFound){
      bId += 1;
      bills.emplace_back(bId, pId, amount, status, patients);
      cout<<"Bill is added successfully!\n";
    }
    else{
      cout<<"No patient found with this ID!\n";
    }

    return 0;
  }

  void addAppointment(vector<Appointment> &appointments, vector<Patient> &patients, vector<Doctor> &doctors){
    static int aId = 0;
    int pId, dId, date, time;
    cout<<"Enter Patient ID : ";
    cin >> pId;
    cout<<"Enter Doctor ID : ";
    cin >> dId;
    cout<<"Enter Date : ";
    cin >> date;
    cout<<"Enter Time : ";
    cin >> time;

    bool patientFound = false;
    bool doctorFound = false;

    for (auto &itr : patients){
      if (pId == itr.getId()){
        patientFound = true;
        break;
      }
    }

    for (auto &itr : doctors){
      if (dId == itr.getId()){
        doctorFound = true;

        itr.pIds.push_back(pId);
        break;
      }
    }

    if (patientFound && doctorFound){
      aId += 1;
      appointments.emplace_back(aId, dId, pId, date, time, patients, doctors);
      cout<<"Appointment has been added!\n";
    }
    else{
      cout<<"Appointment creation failed. Please check patient and doctor IDs.\n";
    }
  }
  void viewPrescriptions(vector<Patient> &patients, vector<Doctor> &doctors, vector<Prescription> &prescriptions){
    if (prescriptions.size() == 0){
      cout<<"No prescriptions are available!"<<endl;
      return;
    }

    cout<<"Prescriptions List : \n";
    cout<<setw(4)<<"prescriptionId"<<setw(15)<<"Doctor Name"<<setw(15)<<"Patient Name\n";
    for (auto &prescription : prescriptions){
      // For finding the Doctor and Patient Name
      string docName = "null", patName = "null";
      for (auto &doctor : doctors){
        int docId = doctor.getId();
        if (prescription.getDoctorId() == docId){
          docName = doctor.getName();
        }
      }
      for (auto &patient : patients){
        int patId = patient.getId();
        if (prescription.getPatientId() == patId){
          patName = patient.getName();
        }
      }

      // Printing each prescriptions
      cout<<setw(14)<<prescription.getId()<<setw(15)<<docName<<setw(15)<<patName<<" - Prescription --> "<<prescription.getPrescription()<<endl;
    }
  }

  void addPrescription(vector<Patient> &patients, vector<Doctor> &doctors, vector<Prescription> &prescriptions){
    static int prId = 1;
    int dId, pId;
    // int prId, dId, pId;
    string prescription;
    cout<<"Enter the Doctor Id : ";
    cin >> dId;
    cout<<"Enter the Patient Id : ";
    cin >> pId;
    cout<<"Enter the Prescription : ";
    cin.ignore();
    getline(cin, prescription);

    // If any Id out of dId and pId not exists, then we write the statement of being Id invalid.
    if (!checkDoctorId(doctors, dId)){
      cout<<"Doctor Id is invalid. Please check again!";
      return;
    }
    else if (!checkPatientId(patients, pId)){
      cout<<"Patient Id is invalid. Please check again!";
      return;
    }

    prescriptions.emplace_back(prId++, dId, pId, prescription);
    cout<<"Prescription is added successfully!\n";
    return;
  }
};

int main(){
  vector<Patient> patients;
  vector<Doctor> doctors;
  vector<Bill> bills;
  vector<Appointment> appointment;
  vector<Prescription> prescriptions;

  Management system;

  int choice;
  do{
    cout<<"--------------------"<<endl;
    cout<<"1. View Patients\n";
    cout<<"2. Add Patients\n";
    cout<<"--------------------"<<endl;
    cout<<"3. View Doctors\n";
    cout<<"4. Add Doctors\n";
    cout<<"--------------------"<<endl;
    cout<<"5. View Bill\n";
    cout<<"6. Add Bill\n";
    cout<<"--------------------"<<endl;
    cout<<"7. View Appointment\n";
    cout<<"8. Add Appointment\n";
    cout<<"--------------------"<<endl;
    cout<<"9. View Prescription\n";
    cout<<"10. Add Prescription\n";
    cout<<"--------------------"<<endl;
    cout<<"11. Exit\n";
    cout<<"--------------------"<<endl;
    cout<<"Enter your choice : ";
    cin >> choice;

    switch (choice){
    case 1:
      system.viewPatients(patients);
      cout<<"===============================================================\n";
      break;
    case 2:
      system.addPatient(patients);
      cout<<"===============================================================\n";
      break;
    case 3:
      system.viewDoctors(doctors);
      cout<<"===============================================================\n";
      break;
    case 4:
      system.addDoctors(doctors);
      cout<<"===============================================================\n";
      break;
    case 5:
      system.viewBill(bills);
      cout<<"===============================================================\n";
      break;
    case 6:
      system.addBill(bills, patients);
      cout<<"===============================================================\n";
      break;
    case 7:
      system.viewAppointment(appointment);
      cout<<"===============================================================\n";
      break;
    case 8:
      system.addAppointment(appointment, patients, doctors);
      cout<<"===============================================================\n";
      break;
    case 9:
      system.viewPrescriptions(patients, doctors, prescriptions);
      cout<<"===============================================================\n";
      break;
    case 10:
      system.addPrescription(patients, doctors, prescriptions);
      cout<<"===============================================================\n";
      break;
    case 11:
      cout<<"-------------- Thank You for the visit --------------";
      break;
    default:
      cout<<"Invalid Number\n";
      cout<<"---------TRY AGAIN---------\n";
      cout<<"===============================================================\n";
    }
  } while (choice != 11);
  return 0;
}