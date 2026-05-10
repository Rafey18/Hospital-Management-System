#pragma once


class Validator {

private:
	static bool isDigit(char character) {
		if (character >= 48 && character <= 57) {
			return true;
		}
		return false;
	}
	static int charToDigit(char character) {
		int number;
		number = character - 48;
		return number;
	}


public:
	static bool isValidDate(const char* date);
	static bool isValidTime(const char* Time);
	static bool isValidPassword(const char* Password);
	static bool isValidID(int id);
	static bool isValidContact(const char* contact);
	static bool isValidMenuChoice(int choice, int minimum , int maximum)  ;
	static bool isValidPositiveAmount(double amount);
};
