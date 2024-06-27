// Muhammad Idrees Khan                      22i-1747                    CY-B                OOP-Final Project.
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <string>
#include <memory>
#include "Doctor.h"
#include "Patient.h"
using namespace std;

Doctor::Doctor()
{
    // First, get the size of the file for the creation of arrays.
    file.open("/home/mik/OOP_FinalProject/Cloud/d.txt", ios::in);
    if (file)
    {
        while (getline(file, temp))
        {
            size++;
        }
        file.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }

    // Add a check to make sure that the size of the arrays is not 0
    if (size > 0)
    {
        name = new string[size];
        specialization = new string[size];
        DID = new int[size];
        for (int i = 0; i < size; i++)
        {
            name[i] = "";
            DID[i] = 0;
            specialization[i] = "";
        }

        setData();
    }
}

Doctor *Doctor::operator=(const Doctor &obj)
{
    this->name = obj.name;
    return this;
}
void Doctor::setData()
{
    int i = 0;
    //***********************************Taking input from .txt File for first input.**********************************************
    file.open("/home/mik/OOP_FinalProject/Cloud/d.txt", ios::in);

    if (file)
    {
        while (i < size && getline(file, name[i], ',') && (file >> DID[i]) && getline(file.ignore(1, '.'), specialization[i]))
        {
            i++;
        }
        file.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }

    //***********************************Now Writing to .dat File in binary mode**********************************************
    file.open("/home/mik/OOP_FinalProject/Cloud/Doctors.dat", ios::out | ios::binary);
    if (file)
    {
        for (int j = 0; j < size; j++)
        {
            int nameLength = name[j].length();
            int specializationLength = specialization[j].length();
            file.write(reinterpret_cast<char *>(&nameLength), sizeof(int));
            file.write(name[j].c_str(), nameLength);
            file.write(reinterpret_cast<char *>(&DID[j]), sizeof(int));
            file.write(reinterpret_cast<char *>(&specializationLength), sizeof(int));
            file.write(specialization[j].c_str(), specializationLength);
        }
        file.close();
    }

    for (int i = 0; i < size; i++)
    {
        name[i] = "";
        DID[i] = 0;
        specialization[i] = "";
    }

    //***********************************Now Reading from .dat File in binary mode**********************************************
    file.open("/home/mik/OOP_FinalProject/Cloud/Doctors.dat", ios::in | ios::binary);
    if (file)
    {
        for (int j = 0; j < size; j++)
        {
            int nameLength, specializationLength;
            file.read(reinterpret_cast<char *>(&nameLength), sizeof(int));
            char *nameBuffer = new char[nameLength + 1];
            file.read(nameBuffer, nameLength);
            nameBuffer[nameLength] = '\0';
            name[j] = nameBuffer;

            file.read(reinterpret_cast<char *>(&DID[j]), sizeof(int));

            file.read(reinterpret_cast<char *>(&specializationLength), sizeof(int));
            char *specializationBuffer = new char[specializationLength + 1];
            file.read(specializationBuffer, specializationLength);
            specializationBuffer[specializationLength] = '\0';
            specialization[j] = specializationBuffer;

            delete[] nameBuffer;
            delete[] specializationBuffer;
        }
        file.close();
    }
    //**************************************Rewrite after data is being done used*********************************************
    file.open("/home/mik/OOP_FinalProject/Cloud/d.txt", ios::out);
    if (file)
    {
        for (int i = 0; i < size; i++)
        {
            file << name[i] << "," << DID[i] << "," << specialization[i] << endl;
        }
        file.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
}

bool Doctor::login()
{
    cout << "Enter your Doctor ID:";
    cin >> doctorid;
    bool ret;
    for (int i = 0; i < size; i++)
    {
        if (DID[i] == doctorid)
        {
            kh = i; // To store the index in order to display later.
            ret = true;
            break;
        }
        else
            ret = false;
    }
    if (ret == true)
    {
        return true;
    }
    else
    {
        cout << "\t\033[1;31mFSorry-No Record Found!\033[0m\n\n";
        return false;
    }
}
void Doctor::D_Display()
{

    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    cout << "| " << setw(28) << setfill(' ') << left << "1-Doctor Name: "
         << "| " << setw(24) << setfill(' ') << left << name[kh] << "|\n";
    cout << "| " << setw(28) << setfill(' ') << left << "1-Doctor ID: "
         << "| " << setw(24) << setfill(' ') << left << DID[kh] << "|\n";
    cout << "| " << setw(28) << setfill(' ') << left << "1-Specialization: "
         << "| " << setw(24) << setfill(' ') << left << specialization[kh] << "|\n";
    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
}
void Doctor::Display()
{
    // Print the data
    cout << left << setw(50) << setfill('-') << ""
         << "\n";
    cout << "| " << setw(28) << setfill(' ') << left << "Doctor Name"
         << "| " << setw(10) << setfill(' ') << left << "Doctor ID"
         << "| " << setw(16) << setfill(' ') << left << "Specialization"
         << "|\n";
    cout << left << setw(50) << setfill('-') << ""
         << "\n";
    for (int j = 0; j < size; j++)
    {
        cout << "| " << setw(15) << setfill(' ') << left << name[j] << "| " << setw(16) << setfill(' ') << left << DID[j] << "|\n";
        cout << "| " << setw(28) << setfill(' ') << left << " "
             << "| " << setw(10) << setfill(' ') << left << " "
             << "| " << setw(16) << setfill(' ') << left << specialization[j] << "|\n";
        cout << left << setw(50) << setfill('-') << ""
             << "\n";
    }
}
int Doctor::getSize()
{
    return this->size;
}
string *Doctor::getName()
{
    return this->name;
}
void Doctor::Delete()
{
    // delete[] name;
    // name = nullptr;
    // delete[] specialization;
    // specialization = nullptr;
}
Doctor::~Doctor()
{
}
ViewEdit::ViewEdit()
{
    Doctor();
    p2 = make_shared<IOT>();
}
ViewEdit::ViewEdit(shared_ptr<IOT> pat)
{
    p2 = pat;
    presc = new string[s];
    pno = p2->Patient_ID;
}
void ViewEdit::View()
{
    p2->Display();
}
void ViewEdit::Edit()
{
    random = rand() % 6;
    switch (random)
    {
    case 1:
        p2->P_BMI();
        break;
    case 2:
        p2->P_BP();
        break;
    case 3:
        p2->P_MS();
        break;
    case 4:
        p2->P_OS();
        break;
    case 5:
        p2->P_PR();
        break;
    default:
        p2->P_TI();
        break;
    }
    int r = rand() % 6;
    switch (r)
    {
    case 1:
        p2->P_BMI();
        break;
    case 2:
        p2->P_BP();
        break;
    case 3:
        p2->P_MS();
        break;
    case 4:
        p2->P_OS();
        break;
    case 5:
        p2->P_PR();
        break;
    default:
        p2->P_TI();
        break;
    }
    cout << "**********************The Editing has been Done!***************************\n";
    p2->Enter();
    p2->Display();
}
void ViewEdit::prescription()
{
    //***********************************Taking input from .txt File for first input.**********************************************
    fstream file("/home/mik/OOP_FinalProject/Cloud/pd.txt", ios::in);
    if (file)
    {
        for (int i = 0; i < s; i++)

            getline(file, presc[i], ';');

        file.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    //***********************************Now Writing to .dat File in binary mode**********************************************
    file.open("/home/mik/OOP_FinalProject/Cloud/PandD.dat", ios::out | ios::binary);
    if (file)
    {
        for (int i = 0; i < s; i++)
        {
            int presclength = presc[i].length();
            file.write(reinterpret_cast<char *>(&presclength), sizeof(int));
            file.write(presc[i].c_str(), presclength);
        }
        file.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
}
void ViewEdit::Display()
{
    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    cout << "| " << setw(28) << setfill(' ') << left << "Prescription"
         << "|\n";
    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    for (int i = 0; i < s; i++)
    {
        cout << "| " << setw(28) << setfill(' ') << left << i + 1 << "- " << presc[i] << "|\n";
    }
    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
}
void ViewEdit::prescri()
{
    cout << left << setw(30) << setfill('-') << ""
         << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    int i = rand() % 5;
    cout << presc[i] << endl;
}
int ViewEdit::getsi()
{
    return s;
}
void ViewEdit::Delete()
{
    delete[] presc;
    presc = nullptr;
}
ViewEdit::~ViewEdit()
{
}

MakeCall::MakeCall()
{
    ra = 0;
    advice = "";
    p = make_shared<Patient>();
    apponitmentreq = 0;
    j = 0;
    pName = p->getName();
    dName = Doctor::getName();
    si = getsi();
}
MakeCall::MakeCall(shared_ptr<Patient> pat)
{
    p = pat;
}

void MakeCall::pn(int j)
{
    this->patient_no = j;
}
bool MakeCall::viewAppointmentRequests(int j)
{
    srand(time(0));               // Seed the random number generator with the current time
    apponitmentreq = rand() % 10; // Generate a random number between 0 and 10.
    if (apponitmentreq >= si)
    {
        cout << "\033[1;31mCannot find any slot for appointment!\033[0m\n";

        return false;
    }
    else
    {
        cout << "The total appointment requests for " << dName[j] << " are:" << endl;

        for (int i = 0; i < apponitmentreq; i++)
        {
            cout << i + 1 << "-" << pName[i] << endl;
        }
        int which = 0;
        do
        {
            cout << "\nChoose a Patient:\n";
            cin >> which;
        } while (which > 5 || which < 1);
        which -= 1;
        viewConsultationHistory(which);
        return true;
    }
}

void MakeCall::viewConsultationHistory(int w) // Functionality to view past consultation history of a patient.
{
    p->viewConsultationHistory(w);
}
void MakeCall::addData() // Functionality to add data into a patient's medical record.
{
    p->setData();
    cout << "\t\t\033[1;32mThe Data is Set successfully.\033[0m\n";
}
void MakeCall::editEHR() // Functionality to edit a patient's EHR.
{
    Edit();
}
bool MakeCall::requestAccess() // Functionality to request access of Data from a patient.
{
    ra = rand() % 5;
    if (ra == 1 && (patient_no == 2 || patient_no == 7 || patient_no == 9))
    {
        cout << "\033[1;32mAccess Granted!!\033[0m\n";
        advice = presc[rand() % 3];
        return true;
    }
    else if (ra == 2 && (patient_no == 1 || patient_no == 4))
    {
        cout << "\033[1;32mAccess Granted!!\033[0m\n";
        advice = presc[rand() % 4];
        return true;
    }
    else if (ra == 3 && (patient_no == 3 || patient_no == 5))
    {
        cout << "\033[1;32mAccess Granted!!\033[0m\n";
        advice = presc[rand() % 5];
        return true;
    }
    else if (ra == 4 && (patient_no == 6 || patient_no == 8))
    {
        cout << "\033[1;32mAccess Granted!!\033[0m\n";
        advice = presc[rand() % 2];
        return true;
    }
    else
    {
        cout << "\033[1;31mAccess Not Granted.\033[0m\n";
        return false;
    }
}
MakeCall::~MakeCall()
{
    p = nullptr;
}
