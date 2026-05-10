#pragma once
#include <SFML/Graphics.hpp>
#include "Storage.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"
#include "FileHandler.h"
#include "Validator.h"
#include "InsufficientFundsException.h"
#include "InvalidInputException.h"
#include "SlotUnavailableException.h"

// Screen state constants
namespace Screen {
    const int MAIN_MENU = 0;
    const int PATIENT_LOGIN = 1;
    const int DOCTOR_LOGIN = 2;
    const int ADMIN_LOGIN = 3;
    const int PATIENT_MENU = 4;
    const int DOCTOR_MENU = 5;
    const int ADMIN_MENU = 6;
    const int BOOK_APPOINTMENT = 7;
    const int CANCEL_APPOINTMENT = 8;
    const int VIEW_APPOINTMENTS = 9;
    const int VIEW_MEDICAL_RECORDS = 10;
    const int VIEW_BILLS = 11;
    const int PAY_BILL = 12;
    const int TOPUP_BALANCE = 13;
    const int VIEW_TODAY_APPTS = 14;
    const int MARK_COMPLETE = 15;
    const int MARK_NOSHOW = 16;
    const int WRITE_PRESCRIPTION = 17;
    const int VIEW_PATIENT_HISTORY = 18;
    const int ADD_DOCTOR = 19;
    const int REMOVE_DOCTOR = 20;
    const int VIEW_ALL_PATIENTS = 21;
    const int VIEW_ALL_DOCTORS = 22;
    const int VIEW_ALL_APPOINTMENTS = 23;
    const int VIEW_UNPAID_BILLS = 24;
    const int DISCHARGE_PATIENT = 25;
    const int VIEW_SECURITY_LOG = 26;
    const int DAILY_REPORT = 27;
    const int REGISTER_PATIENT = 28;
    const int ADD_PATIENT = 29;
    const int REMOVE_PATIENT = 30;
}

class SFMLApp {
private:
    sf::RenderWindow window;
    sf::Font font;

    // Data stores
    Storage<Patient> patients;
    Storage<Doctor> doctors;
    Storage<Admin>  admins;
    Storage<Appointment> appointments;
    Storage<Bill> bills;
    Storage<Prescription> prescriptions;

    // Session
    int currentScreen;
    Patient* loggedPatient;
    Doctor* loggedDoctor;
    Admin* loggedAdmin;
    int loginFailCount;

    // UI state
    char inputString[1000];       
    char statusMessage[500];      
    char displayBuffer[20000];   
    int menuSelection;           
    bool inputActive;
    int inputStep;                

    // Booking 
    char bookSpec[51];
    char bookDocID[10];
    char bookDate[11];
    char bookSlot[6];
    int  bookDoctorIndex;              

    //Temporary Stores
    char tempID[10];
    char tempMed[500];
    char tempNotes[300];
    char tempName[51];
    char tempSpec[51];
    char tempContact[12];
    char tempPass[51];
    char tempFee[20];
    char tempAge[5];
    char tempGender[3];
    char tempAmount[20];

    // Input field for password 
    bool isPasswordField;
    char enteredIDDisplay[50];    // stores the ID entered during login

    // helpers
    void loadAllData();
    void reloadAllData();

    // DRAW FUNCTIONS 
    void drawText(const char* text, float x, float y, unsigned int size, sf::Color color = sf::Color::White);
    void drawWrappedText(const char* text, float x, float y, float maxWidth, unsigned int size, sf::Color color = sf::Color::White);
    void drawButton(const char* label, float x, float y, float w, float h, bool highlighted = false);
    void drawInputBox(const char* label, float x, float y, float w, bool active = true);
    void drawPanel(float x, float y, float w, float h, sf::Color color = sf::Color(30, 30, 60));

    void handleMainMenu(sf::Event& event);
    void handlePatientLogin(sf::Event& event);
    void handleDoctorLogin(sf::Event& event);
    void handleAdminLogin(sf::Event& event);
    void handlePatientMenu(sf::Event& event);
    void handleDoctorMenu(sf::Event& event);
    void handleAdminMenu(sf::Event& event);

    // Patient 
    void handleBookAppointment(sf::Event& event);
    void handleCancelAppointment(sf::Event& event);
    void handleViewAppointments(sf::Event& event);
    void handleViewMedicalRecords(sf::Event& event);
    void handleViewBills(sf::Event& event);
    void handlePayBill(sf::Event& event);
    void handleTopUp(sf::Event& event);
    void handleRegisterPatient(sf::Event& event);
    void handleAddPatient(sf::Event& event);
    void handleRemovePatient(sf::Event& event);

    // Doctor 
    void handleViewTodayAppts(sf::Event& event);
    void handleMarkComplete(sf::Event& event);
    void handleMarkNoShow(sf::Event& event);
    void handleWritePrescription(sf::Event& event);
    void handleViewPatientHistory(sf::Event& event);

    // Admin 
    void handleAddDoctor(sf::Event& event);
    void handleRemoveDoctor(sf::Event& event);
    void handleViewAllPatients(sf::Event& event);
    void handleViewAllDoctors(sf::Event& event);
    void handleViewAllAppointments(sf::Event& event);
    void handleViewUnpaidBills(sf::Event& event);
    void handleDischargePatient(sf::Event& event);
    void handleViewSecurityLog(sf::Event& event);
    void handleDailyReport(sf::Event& event);


    // Draw screens 
    void drawMainMenu();
    void drawLoginScreen(const char* title);
    void drawPatientMenu();
    void drawDoctorMenu();
    void drawAdminMenu();
    void drawOutputScreen(const char* title);
    void drawInputScreen(const char* title, const char* prompt);
    void drawRegisterPatient();

    //Helping functions to check etc
    void copyToStore(char* placeToStore, const char* toStore, int maxLen);
    bool stringEqual(const char* string1, const char* string2) const;
    bool stringEqualCase(const char* string1, const char* string2) const;
    void getTodayDate(char* date);
    int  buildAvailableSlots(int doctorID, const char* date, char available[][6]);
    void sortAppointmentsByDate(Appointment* array, int size, bool ascending);
    void sortPrescriptionsByDate(Prescription* array, int size, bool descending);
    int  countUnpaidBills(int patientID);
    bool dateIsOverdue(const char* date);

    // Login helpers
    Patient* findPatientByCredentials(int id, const char* pass);
    Doctor* findDoctorByCredentials(int id, const char* pass);
    Admin* findAdminByCredentials(int id, const char* pass);

public:
    SFMLApp();
    void run();
};