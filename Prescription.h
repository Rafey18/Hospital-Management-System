#pragma once
#include <iostream>

class Prescription {
private:
    int prescriptionID;
    int appointmentID;
    int patientID;
    int DoctorID;
    char date[11];       
    char medicine[500]; 
    char notes[300];     

    void copyString(char* copyInto, const char* tobeCopied, int maxLength) {
        int i = 0;
        for (int index = 0; index < maxLength && tobeCopied[index] != '\0'; index++) {
            copyInto[index] = tobeCopied[index];
            i++;
        }
        copyInto[i] = '\0';
    }

public:
    Prescription();
    Prescription(int prescriptionID, int appointmentID, int patientID, int doctorID, const char* date, const char* medicine, const char* notes);

    int getID() const;
    int getPrescriptionID()const;
    int getappointmentID()const;
    int getpatientID()const;
    int getdoctorID()const;
    const char* getDate()const;
    const char* getMedicine() const;
    const char* getNotes()const;

    bool operator==(const Prescription& object);
    friend std::ostream& operator<<(std::ostream& COUT, const Prescription& object);
};