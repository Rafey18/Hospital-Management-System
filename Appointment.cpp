#include "Appointment.h"
#include<iostream>

Appointment::Appointment() {
	appointmentID = 0;
	patientID = 0;
	doctorID = 0;
	date[0] = '\0';
	timeSlot[0] = '\0';
	copyString(status, "pending", 10);
	isBooked = false;


}

Appointment::Appointment(int appointmentID, int patientID, int doctorID, const char* date, const char* timeSlot, const char* status, bool isBooked) {
	this->appointmentID = appointmentID;
	this->patientID = patientID;
	this->doctorID = doctorID;
	copyString(this->date, date, 10);
	copyString(this -> timeSlot, timeSlot, 10);
	copyString(this->status, status, 10);
	this->isBooked = isBooked;
}

bool Appointment::operator==(const Appointment& object) {

	if (this->doctorID != object.doctorID) {
		return false;
	}
	if (!isStringEqual(this->date, object.date)) {
		return false;
	}
	if (!isStringEqual(this->timeSlot, object.timeSlot)) {
		return false;
	}
	if (isStringEqual(this->status, "cancelled") || isStringEqual(object.status, "cancelled")) {
		return false;
	}
	return true;
}

std::ostream& operator<<(std::ostream& COUT, const Appointment& object) {
	COUT << "ID: " << object.appointmentID << " | Patient: " << object.patientID << " | Doctor: " << object.doctorID
		<< " | Date: " << object.date << " | Slot: " << object.timeSlot
		<< " | Status: " << object.status;
	return COUT;
}

int Appointment::getID() const {
	return appointmentID;

}

int Appointment::getAppointmentID()const {
	return appointmentID;
}

int Appointment::getPatientID()const {
	return patientID;
}

int Appointment::getDoctorID()const {
	return doctorID;
}

const char* Appointment::getDate()const {
	return date;
}

const char* Appointment::getStatus()const {
	return status;
}

const char* Appointment::getTimeSlot()const {
	return timeSlot;
}

bool Appointment::getIsBooked()const {
	return isBooked;
}

void Appointment::setStatus(const char* newStatus) {
	copyString(this->status, newStatus, 10);
}

void Appointment::setDate(const char* newDate) {
	copyString(this->date, newDate, 11);
}

void Appointment::setTimeSlot(const char* newTime) {
	copyString(this->timeSlot, newTime, 6);
}

void Appointment::setBooking(bool booking) {
	this->isBooked = booking;
}