#include"Patient.h"
#include<iostream>


Patient::Patient() :Person(0, "", "", false) {
	patientID = 0;
	balance = 0.0;
	age = 0;
	gender = 'U';//UNANSWERED
	phoneNumber[0] = '\0';
	unpaidBills = 0;
}

Patient::Patient(int patientID, const char* name, const char* password, bool isLoggedIn, double balance, char gender, int age, const char* phoneNumber, int unpaidBills) : Person(patientID, name, password, isLoggedIn) {
	this->patientID = patientID;
	this->balance = balance;
	this->age = age;
	this->gender = gender;
	this->unpaidBills = unpaidBills;
	copyString(this->phoneNumber, phoneNumber, 12);
}

Patient::Patient(const Patient& object):Person(object) {
	this->patientID = object.patientID;
	this->balance = object.balance;
	this->age = object.age;
	this->gender = object.gender;
	this->unpaidBills = object.unpaidBills;

	copyString(this->phoneNumber, object.phoneNumber, 12);
}

Patient& Patient::operator=(const Patient& object) {
	if (&object == this) {
		return* this;
	}

	Person::operator=(object);
	this->patientID = object.patientID;
	this->age = object.age;
	this->balance = object.balance;
	this->gender = object.gender;
	this->unpaidBills = object.unpaidBills;
	copyString(this->phoneNumber, object.phoneNumber, 12);
	return *this;
}

Patient& Patient::operator+=(double number) {
	balance += number;
	return *this;
}

Patient& Patient::operator-=(double number) {
	balance -= number;
	return *this;
}

bool Patient::operator==(const Patient& object){
	return patientID == object.patientID;
}

std::ostream& operator<<(std::ostream& COUT, const Patient& object) {
	COUT << "ID: " << object.patientID << " | " << "Name: " << object.name
		<< " | Age: " << object.age << " | Gender: " << object.gender << " | PhoneNumber: "
		<< object.phoneNumber << " | Balance: " << object.balance << " | UnpaidBills" <<
		object.unpaidBills << std::endl;
	return COUT;
}


void Patient::display()const {
	std::cout << "Name: " << name << std::endl;
	std::cout << "Patient ID: " << patientID << std::endl;
	std::cout << "Age: " << age << std::endl;
	std::cout << "Gender: " << gender << std::endl;
	std::cout << "Phone: " << phoneNumber << std::endl;
	std::cout << "Balance pkr: " << balance << std::endl;
	std::cout << "Unpaid Bills " << unpaidBills << std::endl;
}

void Patient::showMenu() {
	std::cout << std::endl;
	std::cout << "Welcome, " << name << std::endl;
	std::cout << "Balance pkr: " << balance << std::endl;
	std::cout << "===================" << std::endl;
	std::cout << "1. Book Appointment" << std::endl;
	std::cout << "2. Cancel Appointment" << std::endl;
	std::cout << "3. View My Appointment" << std::endl;
	std::cout << "4. View My Medical Records" << std::endl;
	std::cout << "5. View My Bills" << std::endl;
	std::cout << "6. Pay Bills" << std::endl;
	std::cout << "7. Top Up Balance" << std::endl;
	std::cout << "8. LogOut" << std::endl;

}

int Patient::getPatientID() const {
	return patientID;
}

double Patient::getBalance() const {
	return balance;
}

int Patient::getAge()const {
	return age;
}
int Patient::getID()const {
	return id;
}

char Patient::getGender() const {
	return gender;
}

const char* Patient::getPhoneNumber()const {
	return phoneNumber;
}

int Patient::getUnpaidBills()const {
	return unpaidBills;
}

void Patient::setBalance(double newBalance) {
	this->balance = newBalance;
}

void Patient::setBillsUnpaid(int counter) {
	unpaidBills = counter;
}

Patient::~Patient(){}