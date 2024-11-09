#include <iostream>
#include <vector>
#include <map>
using namespace std;

class ViewDoctors
{
private:
  map<int, pair<string, string>> map1;

public:
  void addDoctor(int doctor_id, string name, string specialization)
  {
    map1[doctor_id] = {name, specialization};
  }

  void show_doctors() const
  {
    if (map1.empty())
    {
      cout << "No doctors available.\n";
      return;
    }
    for (auto itr : map1)
    {
      cout << "Doctor ID: " << itr.first << ", Name: " << itr.second.first
           << ", Specialization: " << itr.second.second << endl;
    }
  }
};

class Doctor
{
  int doctor_id;
  string name;
  string specialization;
  vector<int> patient_id;

public:
  Doctor(int doctor_id, string name, string specialization, ViewDoctors &view)

  {
    this->doctor_id = doctor_id;
    this->name = name;
    this->specialization = specialization;

    view.addDoctor(doctor_id, name, specialization);
  }

  void addPatient(int patientId)
  {
    patient_id.push_back(patientId);
  }

  void displayInfo() const
  {
    cout << "Name: " << name << "\nSpecialization: " << specialization
         << "\nPatient IDs: ";
    for (auto itr : patient_id)
    {
      cout << itr << ", ";
    }
    cout << endl;
  }
};

int main()
{
  int choice;
  ViewDoctors view;       // Shared instance of ViewDoctors
  vector<Doctor> doctors; // Store created doctors

  while (true)
  {
    cout << "\n--- Healthcare System ---\n";
    cout << "1. View Doctors\n2. Add Doctor\n";
    cout << "Choose an option: ";
    cin >> choice;

    if (choice == 2)
    {
      int doctor_id;
      string name;
      string specialization;
      cout << "Enter doctor ID: ";
      cin >> doctor_id;
      cout << "Enter name: ";
      cin >> name;
      cout << "Enter specialization: ";
      cin >> specialization;

      // Create a new doctor and add it to the vector
      Doctor d1(doctor_id, name, specialization, view);
      doctors.push_back(d1);
    }
    else if (choice == 1)
    {
      view.show_doctors();
    }
    else
    {
      cout << "Invalid option. Exiting.\n";
      break;
    }
  }
  return 0;
}

// #include <iostream>
// #include <vector>
// #include <map>
// using namespace std;

// class ViewDoctors
// {
// private:
//   map<int, pair<string, string>> map1;

// public:
//   ViewDoctors(int doctor_id, string name, string specialization)
//   {
//     map1[doctor_id] = {name, specialization};
//   }
//   void show_doctors()
//   {
//     for (auto itr : map1)
//     {
//       cout << itr.first << " : " << itr.second.first << " : " << itr.second.second << endl;
//     }
//   }
// };
// class Doctor
// {
//   int doctor_id;
//   string name;
//   string specialization;
//   vector<int> patient_id;

// public:
//   Doctor(int doctor_id, string name, string specialization)
//   {
//     this->doctor_id = doctor_id;
//     this->name = name;
//     this->specialization = specialization;
//     ViewDoctors doc(doctor_id, name, specialization);
//   }
//   void addPatient(int patientId)
//   {
//     patient_id.push_back(patientId);
//   }
//   void displayInfo()
//   {
//     cout << "name : " << name << endl;
//     cout << "Specialization: " << specialization << endl;
//     cout << "patient ids : ";
//     for (auto itr : patient_id)
//     {
//       cout << itr << " , ";
//     }
//   }
// };

// int main()
// {

//   int choice;
//   vector<Doctor> doctors;
//   while (true)
//   {
//     cout << "\n--- Healthcare System ---\n";
//     cout << "1. View Doctor\n2. Add Doctor\n";
//     cout << "Choose an option: ";
//     cin >> choice;
//     if (choice == 2)
//     {
//       int doctor_id;
//       string name;
//       string specialization;
//       cout << "make a doctor id : ";
//       cin >> doctor_id;
//       cout << endl;
//       cout << "enter name : ";
//       cin >> name;
//       cout << endl;
//       cout << "specialization : ";
//       cin >> specialization;
//       Doctor d1(doctor_id, name, specialization);
//       doctors.push_back(d1);
//     }
//     if (choice == 1)
//     {
//       for(auto val:doctors){}
//     }
//   }
// }
