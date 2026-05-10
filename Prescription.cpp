#include "Prescription.h"
#include <iostream>

// Default constructor
Prescription::Prescription() {
	prescriptionID = 0;
	appointmentID = 0;
	patientID = 0;
	DoctorID = 0;
	date[0] = '\0';
	medicine[0] = '\0';
	notes[0] = '\0';
}

// Parameterized constructor
Prescription::Prescription(int prescriptionID, int appointmentID,
	int patientID, int doctorID, const char* date,
	const char* medicine, const char* notes) {
	this->prescriptionID = prescriptionID;
	this->appointmentID = appointmentID;
	this->patientID = patientID;
	this->DoctorID = doctorID;
	copyString(this->date, date, 11);
	copyString(this->medicine, medicine, 500);
	copyString(this->notes, notes, 300);
}

int Prescription::getID() const {
	return prescriptionID;
}
int Prescription::getPrescriptionID()const {
	return prescriptionID;
}

int Prescription::getappointmentID()const {
	return appointmentID;
}

int Prescription::getpatientID() const {
	return patientID;
}

int Prescription::getdoctorID()const {
	return DoctorID;
}

const char* Prescription::getDate()const {
	return date;
}

const char* Prescription::getMedicine() const {
	return medicine;
}

const char* Prescription::getNotes()const {
	return notes;
}

bool Prescription::operator==(const Prescription& object) {
	if (prescriptionID == object.prescriptionID) {
		return true;
	}
	else {
		return false;
	}
}

std::ostream& operator<<(std::ostream& COUT, const Prescription& object) {
	COUT << "Prescription ID: " << object.prescriptionID
		<< " | Appointment ID: " << object.appointmentID
		<< " | Patient ID: " << object.patientID
		<< " | Doctor ID: " << object.DoctorID
		<< " | Date: " << object.date
		<< " | Medicines: " << object.medicine
		<< " | Notes: " << object.notes;
	return COUT;
}