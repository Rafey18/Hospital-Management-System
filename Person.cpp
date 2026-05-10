#include"Person.h"
#include<iostream>

Person::Person(int id, const char* name, const char* password, bool isLoggedIn) {
	this->id = id;
	this->isLoggedIn = isLoggedIn;
	this->name = copyString(name);
	this->password = copyString(password);
}

Person::Person(const Person& object) {
	this->id = object.id;
	this->isLoggedIn = object.isLoggedIn;
	this->name = copyString(object.name);
	this->password = copyString(object.password);
}

Person& Person::operator=(const Person& object) {
	if (&object == this) {
		return *this;
	}
	this->id = object.id;
	this->isLoggedIn = object.isLoggedIn;

	delete[] name;
	delete[] password;

	this->name = copyString(object.name);
	this->password = copyString(object.password);

	return *this;

}

void Person::logOut() {
	isLoggedIn = false;
}

int Person::getID() const {
	return id;
}

const char* Person::getPassword()const {
	return password;
}

const char* Person::getName() const {
	return name;
}

bool Person::getIsLoggedIn()const {
	return isLoggedIn;
}

void Person::setIsLoggedIn(bool input) {
	isLoggedIn = input;
}

Person::~Person() {
	delete[] name;
	delete[] password;
}