#include<iostream>
#include<vector>
#include <string>
#include<iomanip>
using namespace std;

//Patient Class
class Patient{
    int pId, age;
    string name, symptoms;
public:
    Patient(int pId, string name, int age, string symptoms) : pId(pId), age(age), name(name), symptoms(symptoms){};

    int getId(){ return pId;}
    string getName(){return name;}
    int getAge(){return age;}
    string getSymp(){return symptoms;}
};

//Doctor Class
class Doctor{
protected:
    int dId;
    string name, specialization;

public:
    vector<int> pIds;
    Doctor(int dId, string name, string specialization) : dId(dId), name(name), specialization(specialization){};

    int getId(){ return dId;}
    string getName(){return name;}
    string getSpecialization(){return specialization;}
    vector<int> getPatientsId(){return pIds;}
};

//Patient Class
class Prescription{
    int dId, pId, prId;
    string prescription;
public:
    Prescription(int prId, int dId, int pId, string prescription) : prId(prId), dId(dId), pId(pId), prescription(prescription){};

    int getId(){return prId;}
    int getDoctorId(){return dId;}
    int getPatientId(){return pId;}
    string getPrescription(){return prescription;}
};

//Functions to check whether Doctors, Patients Ids exists or not
bool checkDoctorId(vector<Doctor>& doctors, int id){
    bool check = false;
    for(auto &doctor : doctors){
        if(id == doctor.getId()){
            check = true;
            break;
        }
    }
    return check;
};
bool checkPatientId(vector<Patient>& patients, int id){
    bool check = false;
    for(auto &patient : patients){
        if(id == patient.getId()){
            check = true;
            break;
        }
    }
    return check;
};

//Management Class - It includes all the functions that we need to do
class Management{
public:
    void viewPatients(vector<Patient>& patients){
        if(patients.size() == 0){
            cout<<"No patient registered!"<<endl;
            return;
        }
        cout<<"Patients Lists:\n";
        cout<<setw(5)<<"pID"<<setw(15)<<"Name"<<setw(5)<<"Age"<<"  "<<"Symptoms"<<endl;
        for(auto &patient : patients){
            cout<<setw(5)<<patient.getId()<<setw(15)<<patient.getName()<<setw(5)<<patient.getAge()<<"  "<<patient.getSymp()<<endl;
        }
    }

    void addPatient(vector<Patient>& patients){
        int pId, age;
        string name, symptoms;

        cout<<"Enter the Patient Id : ";
        cin>>pId;
        cout<<"Enter the Patient Name : ";
        cin.ignore();
        getline(cin, name);
        cout<<"Enter the age : ";
        cin>>age;
        cout<<"What are your symptoms ?\n";
        cin.ignore();
        getline(cin, symptoms);

        for(auto &patient : patients){
            if(pId == patient.getId()){
                cout<<"Patient Id is already created! Please Enter a different Patient Id.\n";
                return;
            }
        }

        patients.emplace_back(pId, name, age, symptoms);
        cout<<"Patient is added successfully!\n";
        return;
    }

    void viewDoctors(vector<Doctor>& doctors){
        if(doctors.size() == 0){
            cout<<"No Doctor is available!"<<endl;
            return;
        }
        cout<<"Doctors List:\n";
        cout<<setw(5)<<"dID"<<"   "<<"Name"<<"   "<<"Specialization"<<"   "<<"PatientIds"<<endl;
        for(auto &doctor : doctors){
            cout<<setw(5)<<doctor.getId()<<"   "<<doctor.getName()<<"   "<<doctor.getSpecialization()<<"   ";
            for(auto &pId : doctor.pIds){
                cout<<pId<<",";
            }
            cout<<endl;
        }
    }

    void addDoctors(vector<Doctor>& doctors){
        int dId;
        string name, specialization;

        cout<<"Enter the Doctor Id : ";
        cin>>dId;
        cout<<"Enter the Doctor Name : ";
        cin.ignore();
        getline(cin, name);
        cout<<"What are your Specialization ?\n";
        cin.ignore();
        getline(cin, specialization);

        for(auto &doctor : doctors){
            if(dId == doctor.getId()){
                cout<<"Doctor Id is already created! Please Enter a different Doctor Id.\n";
                return;
            }
        }

        doctors.emplace_back(dId, name, specialization);
        cout<<"Doctor is added successfully!\n";
        return;
    }

    void viewPrescriptions(vector<Patient>& patients, vector<Doctor>& doctors, vector<Prescription>& prescriptions){
        if(prescriptions.size() == 0){
            cout<<"No prescriptions are available!"<<endl;
            return;
        }

        cout<<"Prescriptions List : \n";
        cout<<setw(4)<<"prescriptionId"<<setw(15)<<"Doctor Name"<<setw(15)<<"Patient Name\n";
        for(auto &prescription : prescriptions){
            //For finding the Doctor and Patient Name
            string docName = "null", patName = "null";
            for(auto &doctor : doctors){
                int docId = doctor.getId();
                if(prescription.getDoctorId() == docId){
                    docName = doctor.getName();
                }
            }
            for(auto &patient : patients){
                int patId = patient.getId();
                if(prescription.getPatientId() == patId){
                    patName = patient.getName();
                }
            }

            //Printing each prescriptions
            cout<<setw(14)<<prescription.getId()<<setw(15)<<docName<<setw(15)<<patName<<" - Prescription --> "<<prescription.getPrescription()<<endl;
        }
    }

    void addPrescription(vector<Patient>& patients, vector<Doctor>& doctors, vector<Prescription>& prescriptions){
        int prId, dId, pId;
        string prescription;
        cout<<"Enter the Prescription Id : ";
        cin>>prId;
        cout<<"Enter the Doctor Id : ";
        cin>>dId;
        cout<<"Enter the Patient Id : ";
        cin>>pId;
        cout<<"Enter the Prescription : ";
        cin.ignore();
        getline(cin, prescription);

        //If any Id out of dId and pId not exists, then we write the statement of being Id invalid.
        if(checkDoctorId(doctors, dId) || checkPatientId(patients, pId)){
            cout<<"Doctor Id or Patient Id is invalid. Please check again!";
            return; 
        }

        prescriptions.emplace_back(prId, dId, pId, prescription);
        cout<<"Prescription is added successfully!\n";
        return;
    }
};

int main(){
    vector<Patient> patients = {
        Patient(1, "Rahul", 20, "Fewer"),
    };

    vector<Doctor> doctors = {
        Doctor(1,"Mukesh Gupta", "Pharmacy"),
    };

    vector<Prescription> prescriptions = {
        // Prescription(1,1,1,"Take tablet two times a day"),
    };


    Management system;

    int choice;
    do{
        cout<<"1. View Patients\n";
        cout<<"2. Add Patients\n";
        cout<<"3. View Doctors\n";
        cout<<"4. Add Doctors\n";
        cout<<"5. View Prescriptions\n";
        cout<<"6. Add Prescriptions\n";
        cout<<"7. Exit\n";
        cout<<"Enter a Number : ";
        cin>>choice;

        switch(choice){
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
                system.viewPrescriptions(patients, doctors, prescriptions);
                cout<<"===============================================================\n";
                break;
            case 6:
                system.addPrescription(patients, doctors, prescriptions);
                cout<<"===============================================================\n";
                break;
            case 7:
                cout<<"-------------- Thank You for the visit --------------";
                break;
            default:
                cout<<"Invalid Number\n";
                cout<<"---------TRY AGAIN---------\n";
                cout<<"===============================================================\n";
        }
    }while(choice!=7);
    return 0;
}