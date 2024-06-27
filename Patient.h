// Muhammad Idrees Khan                      22i-1747                    CY-B                OOP-Final Project.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <memory>
using namespace std;
#ifndef Patient_H_
#define Patient_H_
//*****************************Patientss Heirarchy******************************
class Patient
{
protected:
    string *name;
    int *age;
    char *gender;
    int *PID;

public:
    int patientid = 0;                      // For bool Login().
    string temp = "";                       // For size of fist File.
    int size = 0;                           // For loop Condition.
    int kh = 0;                             // For indez Storing.
    string firstline = "";                  // For reading Header lines.
    fstream fin;                            // Fstream Object For File Handling.
    Patient();                              // Patients Constructor.
    void setData();                         // To Set Data From File to Memory or Memory to File.
    void AddPatient();
    bool login();                           // Login to detect Right Login Info.
    void virtual Display();                 // To Display Processed Data.,//Overrided Function
    void viewConsultationHistory(int i);    // View Consultationn history of Patient.
    int getPID();                           // Getter For getting Patient ID.
    string *getName();                      // Getter For getting Patient Name.
    Patient *operator=(const Patient &obj); // Operator Overloading to Copy Data from one object to another object.
    void P_Display();                       // View A certain patient's Data,//Overrided Function
    void Delete();                          // To Delete Dynamic Memories that were Allocated.,//Overrided Function
    ~Patient();                             // Patient Destructor.
};

class IOT : public Patient
{
    float *PBMI;
    string *PBP;
    int *POS;
    int *PPR;
    string *PTI;
    string *PMS;

protected:
    float BMI;
    string BP;
    int OS;
    int pulseRate;
    string TI;
    string MS;
    int size1;
    string temp1 = "";

public:
    int Patient_ID;
    IOT();
    IOT(int i);
    int getPID(int i);
    void P_BMI();
    void P_BP();
    void P_OS();
    void P_PR();
    void P_TI();
    void P_MS();
    void Enter();
    int AddPatienIOT();
    void Display();   // Overrided Function
    void P_Display(); // Overrided Function
    void Delete();    // Overrided Function
    ~IOT();
};

#endif