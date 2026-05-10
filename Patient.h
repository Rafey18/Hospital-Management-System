#pragma once
#include "Person.h"
#include<iostream>

class Patient : public Person{
private:
	int patientID;
	double balance;
	char gender;
	char phoneNumber[12];
	int unpaidBills;
	int age;


	void copyString(char* copyInto, const char* tobeCopied, int maxLength) {
		int i = 0;
		for (int index = 0; index < maxLength && tobeCopied[index] != '\0'; index++) {
			copyInto[index] = tobeCopied[index];
			i++;
		}
		copyInto[i] = '\0';
	}

public:

	Patient();
	Patient(int patientID, const char* name, const char* password, bool isLoggedIn, double balance, char gender, int age, const char* phoneNumber, int unpaidBills);
	Patient(const Patient& object);
	Patient& operator=(const Patient& object);

	Patient& operator +=(double number);
	Patient& operator -= (double number);
	bool operator==(const Patient& object);
	friend std::ostream& operator<<(std::ostream& COUT, const Patient& object);

	void showMenu();
	int getID() const;
	int getPatientID()const;
	double getBalance()const;
	char getGender()const;
	const char* getPhoneNumber()const;
	int getUnpaidBills()const;
	int getAge()const;

	void display() const;
	void setBalance(double newBalance);
	void setBillsUnpaid(int counter);

	~Patient();

};