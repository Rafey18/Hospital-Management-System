#include"Doctor.h"
#include<iostream>


Doctor::Doctor() :Person(0, "", "", false) {
	doctorID = 0;
	specialization = copyStringDynamic("");
	contactNumber[0] = '\0';
	fee = 0.0;
}

Doctor::Doctor(int doctorID, const char* name, const char* password, const char* specialization, const char* contactNumber, double fee, bool isLoggedIn) :Person(doctorID, name, password, isLoggedIn) {
	this->doctorID = doctorID;
	this->specialization = copyStringDynamic(specialization);
	copyString(this->contactNumber, contactNumber, 12);
	this->fee = fee;
}

Doctor::Doctor(const Doctor& object):Person(object) {
	this->doctorID = object.doctorID;
	this->fee = object.fee;
	this->specialization = copyStringDynamic(object.specialization);
	copyString(this->contactNumber, object.contactNumber, 12);
}

Doctor& Doctor::operator=(const Doctor& object) {
	if (&object == this) {
		return *this;
	}

	Person::operator=(object);
	delete[] specialization;

	this->doctorID = object.doctorID;
	this->fee = object.fee;
	this->specialization = copyStringDynamic(object.specialization);
	copyString(this->contactNumber, object.contactNumber, 12);

	return *this;
}


bool Doctor:: operator==(const Doctor& object) {
	if (this->doctorID == object.doctorID) {
		return true;
	}
	else {
		return false;
	}
}

std::ostream& operator<<(std::ostream& COUT, const Doctor& object) {
	COUT << "ID: " << object.doctorID << " | " << "Name: " << object.name
		<< " | PhoneNumber: "
		<< object.contactNumber << " | Specialization: " << object.specialization <<
		" | Fee: " << object.fee << std::endl;
	return COUT;
}


void Doctor::display() const{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Doctor ID: " << doctorID << std::endl;
	std::cout << "Phone: " << contactNumber << std::endl;
	std::cout << "Specialization: " << specialization << std::endl;
	std::cout << "Fee: " << fee << std::endl;
}

void Doctor::showMenu() {
	std::cout << std::endl;
	std::cout << "Welcome, Dr. " << name << " | Specialization: " << specialization << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << "1. View Today's Appointments" << std::endl;
	std::cout << "2. Mark Appointment Complete" << std::endl;
	std::cout << "3. Mark Appointment No-Show" << std::endl;
	std::cout << "4. Write Prescription" <<std:: endl;
	std::cout << "5. View Patient Medical History" << std::endl;
	std::cout << "6. Logout" << std::endl;
}

int Doctor::getID() const {
	return doctorID;
}

int Doctor::getDoctorID() const {
	return doctorID;
}

const char* Doctor::getContactNumber()const {
	return contactNumber;
}

const char* Doctor::getSpecialization()const {
	return specialization;
}

double Doctor::getFee()const {
	return fee;
}

void Doctor::setFee(double newFee) {
	fee = newFee;
}

Doctor::~Doctor() {
	delete[] specialization;
}