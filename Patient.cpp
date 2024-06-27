// Muhammad Idrees Khan                      22i-1747                    CY-B                OOP-Final Project.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <string>
#include <memory>
#include "Patient.h"
using namespace std;

Patient::Patient()
{
    // First, get the size of the file for the creation of arrays.
    fin.open("/home/mik/OOP_FinalProject/Cloud/p.txt", ios::in);
    if (fin)
    {
        while (getline(fin, temp))
        {
            size++;
        }
        fin.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    size -= 1;
    name = new string[size];
    PID = new int[size];
    age = new int[size];
    gender = new char[size];
    setData();
}
void Patient::setData()
{
    int i = 0;
    //***********************************Taking input from .txt File for first input.**********************************************
    fin.open("/home/mik/OOP_FinalProject/Cloud/p.txt", ios::in);
    if (fin)
    {
        getline(fin, firstline);
        while (i < size && getline(fin, name[i], ',') && (fin >> PID[i]))
        {
            fin.ignore(1, ',');
            fin >> age[i];
            fin.ignore(1, ',');
            fin >> gender[i];
            fin.ignore();
            i++;
        }
        fin.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    //***********************************Now Writing to .dat File in binary mode**********************************************
    fin.open("/home/mik/OOP_FinalProject/Cloud/Patients.dat", ios::out | ios::binary);
    if (fin)
    {
        fin.write(reinterpret_cast<char *>(name), size * sizeof(string));
        fin.write(reinterpret_cast<char *>(PID), size * sizeof(int));
        fin.write(reinterpret_cast<char *>(age), size * sizeof(int));
        fin.write((gender), size * sizeof(char));
        fin.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    *name = {""};
    *PID = {0};
    *age = {0};
    *gender = {'\0'};
    //***********************************Now Reading from .dat File in binary mode**********************************************
    fin.open("/home/mik/OOP_FinalProject/Cloud/Patients.dat", ios::in | ios::binary);
    if (fin)
    {
        fin.read(reinterpret_cast<char *>(name), size * sizeof(string));
        fin.read(reinterpret_cast<char *>(PID), size * sizeof(int));
        fin.read(reinterpret_cast<char *>(age), size * sizeof(int));
        fin.read((gender), size * sizeof(char));
        fin.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    //**************************************Rewrite after data is being done used*********************************************
    fin.open("/home/mik/OOP_FinalProject/Cloud/p.txt", ios::out);
    if (fin)
    {
        fin << firstline << endl;
        for (int i = 0; i < size; i++)
        {
            fin << name[i] << "," << PID[i] << "," << age[i] << "," << gender[i] << endl;
        }
        fin.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
}
void Patient::AddPatient()
{
    // Increment size to accommodate new patient
    size++;

    // Allocate new arrays with updated size
    string *newNames = new string[size];
    int *newPID = new int[size];
    int *newAge = new int[size];
    char *newGender = new char[size];

    // Copy existing data to new arrays
    for (int i = 0; i < size - 1; i++)
    {
        newNames[i] = name[i];
        newPID[i] = PID[i];
        newAge[i] = age[i];
        newGender[i] = gender[i];
    }

    // Get data for new patient
    cout << "Enter patient name: ";
    cin >> newNames[size - 1];
    cout << "Enter patient ID: ";
    cin >> newPID[size - 1];
    cout << "Enter patient age: ";
    cin >> newAge[size - 1];
    cout << "Enter patient gender (M/F): ";
    cin >> newGender[size - 1];

    // Deallocate old arrays and point to new ones
    delete[] name;
    delete[] PID;
    delete[] age;
    delete[] gender;
    name = newNames;
    PID = newPID;
    age = newAge;
    gender = newGender;

    // Append new patients'IOT to file
    ofstream fout("/home/mik/OOP_FinalProject/Cloud/iot.txt", ios::app);
    if (fout)
    {
        fout << newNames[size - 1] << "," << newPID[size - 1] << "," << newAge[size - 1] << "," << newGender[size - 1] << endl;
        fout.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    cout << "\033[1;32mNew Patient has been Added.\033[0m\n";
}
bool Patient::login()
{
    cout << "Enter your Patient ID:";
    cin >> patientid;
    bool ret;
    for (int i = 0; i < size; i++)
    {
        if (PID[i] == patientid)
        {
            kh = i;
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
        cout << "\033[1;31mSorry No Record Found!\033[0m\n";
        return false;
    }
}
void Patient::Display()
{
    cout << "\033[1;32mThe Data is.\033[0m\n";
    cout << left << setw(30) << setfill('-') << ""
         << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    cout << setfill(' ') << left << setw(20) << "Name" << setw(15) << "Patient ID"
         << setw(10) << "Age" << setw(5) << "Sex"
         << "\n";
    cout << left << setw(30) << setfill('-') << ""
         << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";

    for (int i = 0; i < size; i++)
    {
        cout << left << setw(20) << setfill(' ') << name[i] << setw(15) << setfill(' ') << PID[i] << setw(10) << setfill(' ')
             << age[i] << gender[i] << "\n";
    }
    cout << left << setw(30) << setfill('-') << ""
         << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
}
void Patient::viewConsultationHistory(int i)
{
    cout << "\033[1;32mThe Data is.\033[0m\n";
    cout << left << setw(30) << setfill('-') << ""
         << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    cout << setfill(' ') << left << setw(20) << "Name" << setw(15) << "Patient ID"
         << setw(10) << "Age" << setw(5) << "Sex"
         << "\n";
    cout << left << setw(20) << setfill(' ') << name[i] << setw(15) << setfill(' ') << PID[1] << setw(10) << setfill(' ')
         << age[i] << gender[i] << "\n";
    cout << left << setw(30) << setfill('-') << ""
         << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
}
int Patient::getPID()
{
    return patientid;
}
string *Patient::getName()
{
    return this->name;
}
Patient *Patient::operator=(const Patient &obj)
{
    this->name = obj.name;
    this->age = obj.age;
    this->kh = obj.kh;
    this->gender = obj.gender;
    return this;
}
void Patient::P_Display()
{
    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    cout << "| " << setw(28) << setfill(' ') << left << "1-Patient Name: "
         << "| " << setw(24) << setfill(' ') << left << name[kh] << "|\n";
    cout << "| " << setw(28) << setfill(' ') << left << "Patient ID: "
         << "| " << setw(24) << setfill(' ') << left << PID[kh] << "|\n";
    cout << "| " << setw(28) << setfill(' ') << left << "Patient Age: "
         << "| " << setw(24) << setfill(' ') << left << age[kh] << "|\n";
    cout << "| " << setw(28) << setfill(' ') << left << "Patient Sex: "
         << "| " << setw(24) << setfill(' ') << left << gender[kh] << "|\n";
    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
}
void Patient::Delete()
{
    // delete[] PID;
    // PID = nullptr;
    // delete[] age;
    // age = nullptr;
    // delete[] gender;
    // gender = nullptr;
}
Patient::~Patient()
{
}

IOT::IOT()
{
    Patient();
    fin.open("/home/mik/OOP_FinalProject/Cloud/iot.txt", ios::in);
    if (fin)
    {
        while (!fin.eof())
        {
            getline(fin, temp1);
            size1++;
        }
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    fin.close();
    BMI = 0.0;
    BP = "";
    OS = 0;
    pulseRate = 0;
    TI = "";
    MS = "";
    srand(time(0));
}
IOT::IOT(int i)
{
    Patient();
    fin.open("/home/mik/OOP_FinalProject/Cloud/iot.txt", ios::in);
    if (fin)
    {
        while (!fin.eof())
        {
            getline(fin, temp1);
            size1++;
        }
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    fin.close();
    BMI = 0.0;
    BP = "";
    OS = 0;
    pulseRate = 0;
    TI = "";
    MS = "";
    srand(time(0));
    size1 -= 2;
    PBMI = new float[size1];
    PBP = new string[size1];
    POS = new int[size1];
    PPR = new int[size1];
    PTI = new string[size1];
    PMS = new string[size1];
}
int IOT::getPID(int i)
{
    this->Patient_ID = Patient::getPID();
    return this->Patient_ID;
}
void IOT::P_BMI()
{
    for (int i = 0; i < size1; i++)
    {
        this->BMI = 10 + (rand() % 28);
        if (this->BMI > 28)
        {
            this->BMI -= 10;
        }
        this->PBMI[i] = this->BMI;
    }
}
void IOT::P_BP()
{
    int temp1 = 0;
    int temp2 = 0;
    for (int i = 0; i < size1; i++)
    {
        temp1 = 90 + (20 + rand() % 180);
        if (temp1 > 180)
        {
            temp1 -= 90;
        }
        temp2 = (rand() % 80) + 30;
        if (temp2 < 80)
        {
            temp2 += 30;
        }
        this->BP = to_string(temp1) + "/" + to_string(temp2);
        this->PBP[i] = this->BP;
    }
}
void IOT::P_OS()
{
    for (int i = 0; i < size1; i++)
    {
        this->OS = 90 + rand() % 10;
        this->POS[i] = this->OS;
    }
}
void IOT::P_PR()
{
    for (int i = 0; i < size1; i++)
    {
        this->pulseRate = 74 + rand() % 10;
        this->PPR[i] = this->pulseRate;
    }
}
void IOT::P_TI()
{
    int temp;
    for (int i = 0; i < size1; i++)
    {
        temp = rand() % 2;
        if (temp == 1)
        {
            this->TI = "Yes";
        }
        else
            this->TI = "No";
        this->PTI[i] = this->TI;
    }
}
void IOT::P_MS()
{
    int temp;
    for (int i = 0; i < size1; i++)
    {
        temp = rand() % 2;
        if (temp == 1)
        {
            this->MS = "Yes";
        }
        else
            this->MS = "No";
        this->PMS[i] = this->MS;
    }
}
void IOT::Enter()
{
    string line = "";
    //***************************************Reading from text file for first use*************************************.
    fin.open("/home/mik/OOP_FinalProject/Cloud/iot.txt", ios::in);
    if (fin)
    {
        getline(fin, line, '\n');
        for (int i = 0; i < size1; i++)
        {
            PBMI[i] = {0.0};
            PBP[i] = {""};
            POS[i] = {0};
            PPR[i] = {0};
            PTI[i] = {""};
            PMS[i] = {""};
        }

        for (int i = 0; i < size1; i++)
        {
            fin >> PBMI[i];
            fin.ignore(1, ',');
            getline(fin, PBP[i], ',');
            fin >> POS[i];
            fin.ignore(1, ',');
            fin >> PPR[i];
            fin.ignore(1, ',');
            getline(fin, PTI[i], ',');
            getline(fin, PMS[i]);
        }
        fin.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    fin.close();
    //***********************************Now Writing to .dat File in binary mode**********************************************
    ofstream fout("/home/mik/OOP_FinalProject/Cloud/iot.dat", ios::out | ios::binary);
    if (fout)
    {
        fout << line << endl;
        for (int i = 0; i < size1; ++i)
        {
            fout.write(reinterpret_cast<const char *>(&PBMI[i]), sizeof(PBMI[i]));

            int len = PBP[i].size();
            fout.write(reinterpret_cast<const char *>(&len), sizeof(len));
            fout.write(PBP[i].c_str(), len);
            PBP[i][len] = '\0';

            fout.write(reinterpret_cast<const char *>(&POS[i]), sizeof(POS[i]));
            fout.write(reinterpret_cast<const char *>(&PPR[i]), sizeof(PPR[i]));

            len = PTI[i].size();
            fout.write(reinterpret_cast<const char *>(&len), sizeof(len));
            fout.write(PTI[i].c_str(), len);
            PTI[i][len] = '\0';

            len = PMS[i].size();
            fout.write(reinterpret_cast<const char *>(&len), sizeof(len));
            fout.write(PMS[i].c_str(), len);
            PMS[i][len] = '\0';
        }
        fout.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
}
int IOT::AddPatienIOT()
{
    // Increment size to accommodate new patient
    size1++;

    // Allocate new arrays with updated size
    float *newPBMI = new float[size1];
    string *newPBP = new string[size1];
    int *newPOS = new int[size1];
    int *newPPR = new int[size1];
    string *newPTI = new string[size1];
    string *newPMS = new string[size1];
    // Copy existing data to new arrays
    for (int i = 0; i < size1 - 1; i++)
    {
        newPBMI[i] = PBMI[i];
        newPBP[i] = PBP[i];
        newPOS[i] = POS[i];
        newPPR[i] = PPR[i];
        newPTI[i] = PTI[i];
        newPMS[i] = PMS[i];
    }

    // Get data for new patient
    cout << "Enter patient BMI: ";
    cin >> newPBMI[size1 - 1];
    cout << "Enter patient BP (180/90): ";
    cin >> newPBP[size1 - 1];
    cout << "Enter patient OS: ";
    cin >> newPOS[size1 - 1];
    cout << "Enter patient PR: ";
    cin >> newPPR[size1 - 1];
    cout << "Enter patient TI (Yes/No): ";
    cin >> newPTI[size1 - 1];
    cout << "Enter patient MS (Yes/No): ";
    cin >> newPMS[size1 - 1];

    // Deallocate old arrays and point to new ones
    delete[] PBMI;
    delete[] PBP;
    delete[] POS;
    delete[] PPR;
    delete[] PTI;
    delete[] PMS;
    PBMI = newPBMI;
    PBP = newPBP;
    POS = newPOS;
    PPR = newPPR;
    PTI = newPTI;
    PMS = newPMS;
    // Append new patient to file
    ofstream fout("/home/mik/OOP_FinalProject/Cloud/p.txt", ios::app);
    if (fout)
    {
        fout << newPBMI[size - 1] << "," << newPBP[size - 1] << "," << newPOS[size - 1] << "," << newPPR[size - 1]<< "," << newPTI[size - 1] << "," << newPMS[size - 1] << endl;
        fout.close();
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    cout << "\033[1;32mNew Patient has been Added.\033[0m\n";
    return 0;
}
void IOT::Display()
{
    string line = "";
    for (int i = 0; i < size1; i++)
    {
        PBMI[i] = {0.0};
        PBP[i] = {""};
        POS[i] = {0};
        PPR[i] = {0};
        PTI[i] = {""};
        PMS[i] = {""};
    }
    //***********************************Now Reading from .dat File in binary mode**********************************************
    fstream fin;
    fin.open("/home/mik/OOP_FinalProject/Cloud/iot.dat", ios::in | ios::binary); // Open the binary file.
    if (!fin)
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    else
    {

        getline(fin, line, '\n'); // Read the header line

        int count = 0;
        for (count = 0; count < size1; count++)
        {
            fin.read(reinterpret_cast<char *>(&PBMI[count]), sizeof(float));

            int s1;
            fin.read(reinterpret_cast<char *>(&s1), sizeof(int));
            char *bp_buffer = new char[s1 + 1];
            fin.read(bp_buffer, s1);
            bp_buffer[s1] = '\0';
            PBP[count] = string(bp_buffer);
            delete[] bp_buffer;

            fin.read(reinterpret_cast<char *>(&POS[count]), sizeof(int));
            fin.read(reinterpret_cast<char *>(&PPR[count]), sizeof(int));

            int s2;
            fin.read(reinterpret_cast<char *>(&s2), sizeof(int));
            char *ti_buffer = new char[s2 + 1];
            fin.read(ti_buffer, s2);
            ti_buffer[s2] = '\0';
            PTI[count] = string(ti_buffer);
            delete[] ti_buffer;

            int s3;
            fin.read(reinterpret_cast<char *>(&s3), sizeof(int));
            char *ms_buffer = new char[s3 + 1];
            fin.read(ms_buffer, s3);
            ms_buffer[s3] = '\0';
            PMS[count] = string(ms_buffer);
            delete[] ms_buffer;
        }
        fin.close();
    }
    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    cout << "| " << setw(28) << setfill(' ') << left << "PBMI"
         << "| " << setw(8) << setfill(' ') << left << "PBP"
         << "| " << setw(8) << setfill(' ') << left << "POS"
         << "| " << setw(8) << setfill(' ') << left << "PPR"
         << "| " << setw(8) << setfill(' ') << left << "PTI"
         << "| " << setw(8) << setfill(' ') << left << "PMS"
         << "|\n";
    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    for (int i = 0; i < size1; i++)
    {
        cout << "| " << setw(28) << setfill(' ') << left << this->PBMI[i] << "| " << setw(8) << setfill(' ') << left << this->PBP[i] << "| " << setw(8) << setfill(' ') << left << this->POS[i] << "| " << setw(8) << setfill(' ') << left << this->PPR[i] << "| " << setw(8) << setfill(' ') << left << this->PTI[i] << "| " << setw(8) << setfill(' ') << left << this->PMS[i] << "|\n";
    }
    cout << left << setw(30) << setfill('-') << "" << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";

    //******************************Writing again to .txt file in order to Read from it for next time**********************
    fin.open("/home/mik/OOP_FinalProject/Cloud/iot.txt", ios::out);
    if (fin)
    {
        fin << line << endl;
        for (int i = 0; i < size1; i++)
        {
            fin << PBMI[i] << "," << PBP[i] << "," << POS[i] << "," << PPR[i] << "," << PTI[i] << "," << PMS[i] << endl;
        }
    }
    else
    {
        cout << "\033[1;31mFile Not Opened!\033[0m\n";
    }
    fin.close();
}
void IOT::P_Display()
{
    int i = rand() % 8;
    cout << left << setw(10) << setfill(' ') << "BMI";
    cout << left << setw(18) << setfill(' ') << "Blood Pressure";
    cout << left << setw(20) << setfill(' ') << "Oxygen Saturation";
    cout << left << setw(12) << setfill(' ') << "Pulse Rate";
    cout << left << setw(18) << setfill(' ') << "Tremor Indicator";
    cout << left << setw(15) << setfill(' ') << "Movement Sensor"
         << "\n";
    cout << left << setw(10) << setfill(' ') << this->PBMI[i];
    cout << left << setw(18) << setfill(' ') << this->PBP[i];
    cout << left << setw(20) << setfill(' ') << this->POS[i];
    cout << left << setw(12) << setfill(' ') << this->PPR[i];
    cout << left << setw(18) << setfill(' ') << this->PTI[i];
    cout << left << setw(15) << setfill(' ') << this->PMS[i] << "\n";
}
void IOT::Delete()
{
    delete[] PBMI;
    PBMI = nullptr;
    delete[] PBP;
    PBP = nullptr;
    delete[] POS;
    POS = nullptr;
    delete[] PMS;
    PMS = nullptr;
    delete[] PTI;
    PTI = nullptr;
}
IOT::~IOT()
{
}
