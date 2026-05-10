#pragma once
#include<iostream>


class Person {
protected:
	int id;
	char* name;
	char* password;
	bool isLoggedIn;


	//As both name and password are like dynamic -->sooooo we use dynamic one rather than static
	char* copyString(const char* input) {
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

public:
	Person(int id, const char* name, const char* password, bool isLoggedIn);
	Person(const Person& object);
	Person& operator=(const Person& object);

	virtual void display() const= 0;
	virtual void showMenu() = 0;

	virtual void logOut();

	int getID() const;
	const char* getName()const;
	const char* getPassword()const;
	bool getIsLoggedIn()const;
	void setIsLoggedIn(bool input);

	virtual~Person();

};