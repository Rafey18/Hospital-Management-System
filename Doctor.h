#pragma once
#include"Person.h"
#include<iostream>


class Doctor:public Person {
private:
	int doctorID;
	char contactNumber[12];
	double fee;
	//Yai dynamic hai as specialization depends on users input
	char* specialization;

	//For dynamic
	char* copyStringDynamic(const char* input) {
		if (input == nullptr) {
			char* empty = new char[1];
			empty[0] = '\0';
			return empty;
		}

		int index = 0;
		for (int i = 0; input[i] != '\0'; i++) {
			index++;
		}

		char* newArray = new char[index + 1];
		for (int i = 0; i < index; i++) {
			newArray[i] = input[i];
		}
		newArray[index] = '\0';
		return newArray;
	}

	//For static
	void copyString(char* copyInto, const char* tobeCopied, int maxLength) {
		int i = 0;
		for (int index = 0; index < maxLength && tobeCopied[index] != '\0'; index++) {
			copyInto[index] = tobeCopied[index];
			i++;
		}
		copyInto[i] = '\0';
	}

public:
	Doctor();
	Doctor(int doctorID, const char* name, const char* password, const char* specialization, const char* contactNumber, double fee, bool isLoggedIn);
	Doctor(const Doctor& object);
	Doctor& operator=(const Doctor& object);

	bool operator==(const Doctor& object);
	friend std::ostream& operator<<(std::ostream& COUT, const Doctor& object);

	void display() const;
	void showMenu();

	int getID()const;
	int getDoctorID()const;
	const char* getContactNumber()const;
	const char* getSpecialization() const;
	double getFee() const;

	void setFee(double newFee);

	~Doctor();

};