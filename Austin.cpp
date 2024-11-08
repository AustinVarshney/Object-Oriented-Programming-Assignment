#include<iostream>
#include<vector>
#include <string>
#include<iomanip>
using namespace std;

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

// class Doctor{
//     int dId;
//     string name, specialization;
// public:
//     vector<int> pIds;

//     Doctor(int dId, string name, string specialization) : dId(dId), name(name), specialization(specialization){};

//     Doctor(int dId, string name, string specialization, int pId) : dId(dId), name(name), specialization(specialization){
//         pIds.emplace_back(pId);
//     };

//     int getId(){ return dId;}
//     string getName(){return name;}
//     string getSpecialization(){return specialization;}
//     vector<int> getPatientsId(){return pIds;}
// };

class Management{
public:
    void viewPatients(vector<Patient>& patients){
        cout<<"Patients Lists:\n";
        cout<<setw(5)<<"pID"<<setw(15)<<"Name"<<setw(5)<<"Age"<<"  "<<"Symptoms"<<endl;
        for(auto &patient : patients){
            cout<<setw(5)<<patient.getId()<<setw(15)<<patient.getName()<<setw(5)<<patient.getAge()<<"  "<<patient.getSymp()<<endl;
        }
    }

    // void viewDoctors(vector<Doctor>& doctors){
    //     cout<<"Doctors List:\n";
    //     cout<<setw(5)<<"dID"<<"   "<<"Name"<<"   "<<"Specialization"<<"   "<<"PatientIds"<<endl;
    //     for(auto &doctor : doctors){
    //         cout<<setw(5)<<doctor.getId()<<"   "<<doctor.getName()<<"   "<<doctor.getSpecialization()<<"   ";
    //         for(auto &pId : doctor.pIds){
    //             cout<<pId<<",";
    //         }
    //         cout<<endl;
    //     }
    // }

    int addPatient(vector<Patient>& patients){
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
                return 0;
            }
        }

        patients.emplace_back(pId, name, age, symptoms);
        cout<<"Patient is added successfully!\n";
        return 0;
    }
};

int main(){
    vector<Patient> patients = {
        Patient(1, "Rahul", 20, "Fewer"),
        Patient(2, "Ramesh", 56, "Diabetes"),
        Patient(3, "Ajay", 70, "Apetite")
    };

    // vector<Doctor> doctors = {
    //     Doctor(1,"Mukesh Gupta", "Pharmacy",1),
    //     Doctor(1,"Mahesh Sharma", "Biomecs",2),
    //     Doctor(1,"Sidhart", "Surgery",2),
    //     Doctor(1,"Ajay raj", "Liver",3)
    // };


    Management system;

    int choice;
    do{
        cout<<"1. View Patients\n";
        cout<<"2. Add Patients\n";
        // cout<<"3. View Doctors\n";
        cout<<"3. Exit\n";
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
            // case 3:
            //     system.viewDoctors(doctors);
            //     cout<<"===============================================================\n";
            //     break;
            case 3:
                cout<<"-------------- Thank You for the visit --------------";
                break;
            default:
                cout<<"Invalid Number\n";
                cout<<"---------TRY AGAIN---------\n";
                cout<<"===============================================================\n";
        }
    }while(choice!=3);
    return 0;
}