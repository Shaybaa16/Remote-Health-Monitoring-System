// Muhammad Idrees Khan                      22i-1747                    CY-B                OOP-Final Project.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <memory>
#include "Patient.h"
using namespace std;
#ifndef Doctor_H_
#define Doctor_H_
//*****************************Doctors Heirarchy******************************
using namespace std;

class Doctor
{
private:
    string temp;
    int size = 0;

protected:
    string *specialization;
    int *DID;

public:
    int doctorid = 0; // For Bool Login
    string *name;
    int kh = 0;
    fstream file;
    Doctor();
    Doctor *operator=(const Doctor &obj);
    void setData();
    bool login();
    void D_Display();
    void virtual Display(); // Overrided Function
    int getSize();
    string *getName();
    void Delete(); // Overrided Function
    ~Doctor();
};

class ViewEdit : public Doctor
{
private: // Association Between Patients-IOT and Doctors Class as the "ViewEdit" class is not responsible for creating or managing the "IOT" object,
         // but it does have a reference to it through the "p2" member variable.
    shared_ptr<IOT> p2;
    int random = 0;
    int s = getSize();

protected:
    string *presc;
    int pno;

public:
    ViewEdit();
    ViewEdit(shared_ptr<IOT> pat);
    void View();
    void Edit();
    void prescription(); // Setting Prescription For Doctors.
    void Display();      // Overrided Function
    void prescri();
    int getsi();
    void Delete(); // Overrided Function
    ~ViewEdit();
};
class MakeCall : public ViewEdit
{
private:
    int patient_no;
    int ra;
    string advice;
    shared_ptr<Patient> p;
    int apponitmentreq;
    string *pName;
    string *dName;
    int j;
    int si;

public:
    MakeCall();                          // Constructor
    MakeCall(shared_ptr<Patient> pat);   // Composition as MakeCall is assigning and Also the removing the assigned memory in Destructor,Shared Memory by the Doctor and Patient Class.
    void pn(int j);                      // Assign the patient No.
    bool viewAppointmentRequests(int j); // Functionality to view Appointment Requests by the Doctor.
    void viewConsultationHistory(int w); // Functionality to view past consultation history of a patient.

    void addData(); // Functionality to add data into a patient's medical record.

    void editEHR();       // Functionality to edit a patient's EHR.
    bool requestAccess(); // Functionality to request access of Data from a patient.
    ~MakeCall();          // Destructor
};
#endif
