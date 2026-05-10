#include<iostream>
#include"Validator.h"

bool Validator::isValidID(int id) {
	if (id > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool Validator::isValidPassword(const char* Password) {
	int length = 0;
	for (int i = 0; Password[i] != '\0'; i++) {
		length++;
	}
	if (length >= 6) {
		return true;
	}
	else {
		return false;
	}
}

bool Validator::isValidContact(const char* Contact) {
	int length = 0;

	for (int i = 0; Contact[i] != '\0'; i++) {
		if (!isDigit(Contact[i])) {
			return false;
		}
		else {
			length++;
		}
	}
	if (length == 11) {
		return true;
	}
	else {
		return false;
	}
}

bool Validator::isValidPositiveAmount(double amount) {
	if (amount > 0.0) {
		return true;
	}
	else {
		return false;
	}
}

bool Validator::isValidMenuChoice(int choice , int minimum , int maximum) {
	if (choice >= minimum && choice <= maximum) {
		return true;
	}
	else {
		return false;
	}
}
bool Validator::isValidTime(const char* time) {

	const char* validTime[8] = { "09:00", "10:00", "11:00", "12:00" , "13:00", "14:00", "15:00", "16:00" };
	for (int i = 0; i < 8; i++) {
		int j = 0;
		for ( j = 0; time[j] != '\0' && validTime[i][j] != '\0'; j++) {
			if (time[j] != validTime[i][j]) {
				break;
			}
		}
		if (time[j] == '\0' && validTime[i][j] == '\0') {
			return true;
		}
	}
	return false;
}

bool Validator::isValidDate(const char* date) {
	int length = 0;
	while (date[length] != '\0') {
		length++;
	}

	if (length != 10) {
		return false;
	}
	
	for (int x = 0; x < 10; x++) {
		if (x == 2 || x == 5) {
			continue; // position index for dashes
		}
		else {
			if (date[x] < '0' || date[x] >'9') {
				return false;
			}
		}
	}

	//Day;
	int dayDigit1 = charToDigit(date[0]);
	int dayDigit2 = charToDigit(date[1]);

	int day =  dayDigit1 * 10 + dayDigit2;
	if (day <= 0 || day > 31) {
		return false;
	}

	// month
	int monthDigit1 = charToDigit(date[3]);
	int monthDigit2 = charToDigit(date[4]);

	int month = monthDigit1 * 10 + monthDigit2;
	if (month <= 0 || month > 12) {
		return false;
	}


	//Year
	int yearDigit1 = charToDigit(date[6]);
	int yearDigit2 = charToDigit(date[7]);
	int yearDigit3 = charToDigit(date[8]);
	int yearDigit4 = charToDigit(date[9]);


	int year = yearDigit1 * 1000 + yearDigit2 * 100 + yearDigit3 * 10 + yearDigit4;
	
	if (year < 2026) {
		return false;
	}

	return true;
}

