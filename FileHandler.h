#pragma once
#include <fstream>
#include <iostream>
#include <ctime>
#include "Storage.h"
#include "Patient.h"
#include "Doctor.h"
#include "Admin.h"
#include "Appointment.h"
#include "Bill.h"
#include "Prescription.h"


class FileHandler {
private:
	static const char* PatientFile;
	static const char* DoctorFile;
	static const char* AdminFile;
	static const char* BillFile;
	static const char* AppointmentFile;
	static const char* SecurityLogFile;
	static const char* PrescriptionFile;
	static const char* DischargeFile;


	//Since commas to seperate-> function to seperate them
	
	//Added in ordert to check no. of fields 
	//like agar no. of fields not exact ya phir any missing or comma 1 less--> data corrupted
	//no of column = no . of fields
	static int splitAttributes(const char* fileLine, char attributes[][200], int maxAttributes); 
	 
	//Copying arrays
	void copyString(char* copyInto, const char* tobeCopied, int maxLength) {
		int i = 0;
		for (int index = 0; index < maxLength && tobeCopied[index] != '\0'; index++) {
			copyInto[index] = tobeCopied[index];
			i++;
		}
		copyInto[i] = '\0';
	}

	static int charToDigit(char character) {
		int number;
		number = character - 48;
		return number;
	}

	static int charToInt(const char* characterNumber);

	static double charToDouble(const char* characterNumber);
	static void intToChar(int number, char* array);
	static void doubleToChar(double number, char* array , int decimal);

	static bool isStringEqual(const char* string1, const char* string2);

public:

	static void loadPatients(Storage<Patient>& storage);
	static void loadDoctors(Storage<Doctor>& storage);
	static void loadAdmins(Storage<Admin>& storage);
	static void loadAppointments(Storage<Appointment>& storage);
	static void loadPrescriptions(Storage<Prescription>& storage);
	static void loadBills(Storage<Bill>& storage);


	static void appendPatient(const Patient& patientToAppend);
	static void appendDoctor(const Doctor& patientToAppend);
	static void appendAppointment(const Appointment& patientToAppend);
	static void appendBill(const Bill& patientToAppend);
	static void appendPrescription(const Prescription& patientToAppend);


	static void updatePatient(const Patient& patientToUpdate);
	static void updateAppointment(const Appointment& appointmentToUpdate);
	static void updateBill(const Bill& billToUpdate);


	static void deletePatient(int patientID);
	static void deleteDoctor(int doctorID);




	//for getting ids taakai we can generate new id 
	static int getFilePatientID();
	static int getFileDoctorID();
	static int getFileAppointmentID();
	static int geFileBillID();
	static int getFilePrescriptionID();


	static void readSecurityLog();

	static void dischargePatient(const Patient& patientToBeDischarged);
	static void logSecurityEvent(const char* role, int enteredID, const char* result);
};