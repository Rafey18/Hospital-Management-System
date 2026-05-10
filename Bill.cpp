#include "Bill.h"
#include <iostream>

Bill::Bill() {
	billID = 0;
	patientID = 0;
	appointmentID = 0;
	amount = 0.0;
	date[0] = '\0';
	status[0] = '\0';
}

Bill::Bill(int billID, int patientID, int appointmentID, double amount, const char* status, const char* date) {
	this->billID = billID;
	this->patientID = patientID;
	this->appointmentID = appointmentID;
	this->amount = amount;
	copyString(this->date, date, 11);
	copyString(this->status, status, 200);
}

int Bill::getID() const{ 
	return billID;
}
int Bill::getBillID()const { 
	return billID; 
}
int Bill::getPatientID() const{
	return patientID;
}
int Bill::getAppointmentID() const{
	return appointmentID; 
}
double Bill::getAmount() const { 
	return amount;
}
const char* Bill::getDate() const {
	return date; 
}
const char* Bill::getStatus() const {
	return status;
}

void Bill::setStatus(const char* status) {
	copyString(this->status, status, 200);
}

bool Bill::operator==(const Bill& object) const {
	return billID == object.billID;
}

std::ostream& operator<<(std::ostream& COUT, const Bill& object) {
	COUT << "Bill ID: " << object.billID
		<< " | Patient ID: " << object.patientID
		<< " | Appointment ID: " << object.appointmentID
		<< " | Amount: PKR " << object.amount
		<< " | Status: " << object.status
		<< " | Date: " << object.date;
	return COUT;
}
