// Muhammad Idrees Khan                      22i-1747                    CY-B                OOP-Final Project.
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <memory>
#include <unistd.h>
#include <thread>
#include <chrono>
#include "Patient.h"
#include "Doctor.h"
#include "Patient.cpp"
#include "Doctor.cpp"
using namespace std;
// Functions For Driver Program.
void loadingBar();
int AddPatients();
int main()
{
    string temp = "", temp1 = "";
    bool t;
    int choice = 0, choose = 0, h = 0;
    int appoint = 0;
    Patient p2;
    Patient *Pptr;
    Doctor d1;
    d1.setData();
    Doctor *Dptr;
    Doctor dm;
    appoint = rand() % 10;
    IOT i1(appoint);
    shared_ptr<IOT> i1_ptr = make_shared<IOT>(appoint);
    ViewEdit v1(i1_ptr);
    MakeCall m1;
    srand(time(0));
    int which = 0;
    cout << setfill(' ') << setw(30) << setfill('-') << ""
         << setw(10) << "" << setw(10) << "" << setw(6) << ""
         << "\n";
    loadingBar();
    cout << "\033[1;32mDone!\033[0m" << endl;
    cout << "\t\t\t\t\033[1;32mHealth Providers App:\033[0m\n";
    do
    {
        cout << left << setw(30) << ""
             << setw(10) << "" << setw(10) << "" << setw(6) << ""
             << "\n";
        cout << "1. Log in as Patient.\n";
        cout << "2. Log in as Doctor.\n";
        cout << "3. Log in as Admin.\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
            // For Login as Doctor
        case 1:
            if (p2.login())
            {
                Patient p1;
                p1 = p2;
                p1.setData();
                cout << "Processing";
                for (int i = 0; i < 10; ++i)
                {
                    cout << ".";
                    cout.flush();
                    usleep(500000); // Sleep for 0.5 seconds
                }
                cout << "\033[1;32mSuccess!\033[0m\n";
                cout << "Welcome-Your Data has been setup.\n";
                //************************Patient-IOT Turn.
                int ii = p1.getPID();
                i1.P_BMI();
                i1.P_BP();
                i1.P_OS();
                i1.P_PR();
                i1.P_TI();
                i1.P_MS();
                i1.Enter();
                Pptr = &p1;
                do
                {
                    cout << left << setw(30) << setfill('-') << ""
                         << setw(10) << "" << setw(10) << "" << setw(6) << ""
                         << "\n";
                    cout << "1. See Available Doctors.\n";
                    cout << "2. View your own Data.\n";
                    cout << "0. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        dm = d1;
                        dm.Display();
                        do
                        {
                            cout << "\nChoose a Doctor:\n";
                            cin >> which;
                        } while (which > 5 || which < 1);
                        h = p1.getPID();
                        which -= 1; // In c++ it starts from 0 to any num so choice-1 is actual num.
                        m1.pn(which);
                        if (m1.viewAppointmentRequests(which))
                        {
                            // m1.viewConsultationHistory(which);
                            if (m1.requestAccess())
                            {
                                m1.addData();
                                m1.editEHR();
                            }
                            cout << left << setw(30) << setfill('-') << ""
                                 << setw(10) << "" << setw(10) << "" << setw(6) << ""
                                 << "\n";
                            cout << "\033[1;32mResponse of Doctor!\033[0m\n";
                            v1.prescription();
                            v1.prescri();
                            cout << "\nOperation for Patient-Doctor Relation Ended.\n";
                        }
                        break;
                    case 2:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        p1.P_Display();
                        i1.P_Display();
                        break;
                    case 0:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        cout << "\033[1;32mExiting...Thank You For Using Patients App-Health Care System.\033[0m\n";
                        break;
                    default:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        cout << "\033[1;31mInvalid Choice!\033[0m\n";

                        break;
                    }
                    p2 = p1;
                } while (choice != 0);
            }
            else
            {
                cout << "\033[1;31mSorry No Record Found!-Exiting...\033[0m\n";
            }
            break;
        // For Login as Doctor
        case 2:
            cout << left << setw(30) << setfill('-') << ""
                 << setw(10) << "" << setw(10) << "" << setw(6) << ""
                 << "\n";
            if (d1.login())
            {
                Doctor d2;
                d2 = d1;
                d2.setData();
                Dptr = &d2;
                cout << left << setw(30) << setfill('-') << ""
                     << setw(10) << "" << setw(10) << "" << setw(6) << ""
                     << "\n";
                cout << "Processing";
                for (int i = 0; i < 10; ++i)
                {
                    cout << ".";
                    cout.flush();
                    usleep(500000); // Sleep for 0.5 seconds
                }
                cout << "\033[1;32mSuccess!\033[0m\n";
                cout << "Welcome-Your Data has been setup.\n";
                do
                {
                    cout << "1. View Appointment Requests.\n";
                    cout << "2. View your own Data.\n";
                    cout << "0. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        which = rand() % 5;
                        t = m1.viewAppointmentRequests(which);
                        if (t)
                        {
                            if (m1.requestAccess())
                            {
                                m1.addData();
                                m1.editEHR();
                            }
                            cout << "Done And Dusted\n";
                        }
                        else
                            cout << "The Patient Refused Or No Patient In the Appointment List.\n";
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        cout << "Thank You So Much for your Precious Time\n";
                        cout << "\nOperation for Patient-Doctor Relation Ended.\n";
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        break;
                    case 2:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        d1.D_Display();
                        break;
                    case 0:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        cout << "\033[1;32mExiting...Thank You For Using Doctor's App-Health Care System.\033[0m\n";
                        break;
                    default:
                        cout << "\033[1;31mInvalid Choice!\033[0m\n";
                        break;
                        d1 = d2;
                    }
                } while (choice != 0);
            }
            else
            {
                cout << "\033[1;31mSorry No Record Found!-Exiting...\033[0m\n";
            }
            break;
        // For Login as an admin.
        case 3:
            cout << left << setw(30) << setfill('-') << ""
                 << setw(10) << "" << setw(10) << "" << setw(6) << ""
                 << "\n";
            cin.ignore();
            cout << "Please Enter Your Username:";
            getline(cin, temp);
            cout << "Please enter Your Password:";
            getline(cin, temp1);
            if ((temp == "Idrees" || temp == "idrees") && (temp1 == "22i1747"))
            {
                cout << "Processing";
                for (int i = 0; i < 10; ++i)
                {
                    cout << ".";
                    cout.flush();
                    usleep(500000); // Sleep for 0.5 seconds
                }
                cout << "\033[1;32mSuccess!\033[0m\n";
                cout << "Welcome-Your Data has been setup.\n";
                do
                {
                    cout << "1. View Overall Data Stored In Our DataBase.\n";
                    cout << "2. Add New Patient.\n";
                    cout << "0. Exit\n";
                    cout << "Enter your choice: ";
                    cin >> choice;
                    switch (choice)
                    {
                    case 1:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        cout << "\t\t\tPatients\n";
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        p2.Display();
                        cout << "\t\t\tPatient-IOT\n";
                        i1.Enter();
                        i1.Display();
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        cout << "\t\t\tDoctors\n";
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        d1.Display();
                        break;
                    case 2:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        p2.AddPatient();
                        i1.AddPatienIOT();
                        break;
                    case 0:
                        cout << left << setw(30) << setfill('-') << ""
                             << setw(10) << "" << setw(10) << "" << setw(6) << ""
                             << "\n";
                        cout << "\033[1;32mExiting...Thank You For Using Health Care System.\033[0m\n";
                        break;
                    default:
                        break;
                    }
                } while (choice != 0);
            }
            break;
        case 0:
            cout << left << setw(30) << setfill('-') << ""
                 << setw(10) << "" << setw(10) << "" << setw(6) << ""
                 << "\n";
            cout << "\033[1;32mExiting...Thank You For Using Health Care System.\033[0m\n";
            break;
        default:
            cout << left << setw(30) << setfill('-') << ""
                 << setw(10) << "" << setw(10) << "" << setw(6) << ""
                 << "\n";
            cout << "\033[1;31mInvalid Choice!\033[0m\n";
            break;
        }
    } while (choice != 0);
    Pptr->Delete();
    Dptr->Delete();
    dm.Delete();
    p2.Delete();
    d1.Delete();
    i1.Delete();
    return 0;
}
void loadingBar()
{
    int total = 80;

    cout << endl;

    for (int i = 0; i < total; i++)
    {

        cout << "[";

        int progress = (i * 100) / total;
        cout << "\t\t\033[1;32mLoading\033[0m\n";
        for (int j = 0; j < progress / 2; j++)
        {
            cout << "\033[1;31m=\033[0m";
        }
        for (int j = progress / 2; j < 50; j++)
        {
            cout << " ";
        }

        cout << "] " << progress << "%\r";

        cout.flush();

        // Sleep for 100 milliseconds
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    cout << endl;
}