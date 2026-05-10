#pragma once
#include"Person.h"
#include<iostream>


class Admin : public Person {
private:
	int adminID;
public:

	Admin();
	Admin(int adminID, const char* name, const char* password, bool isLoggedIn);

	Admin(const Admin& object);
	Admin& operator=(const Admin& object);

	bool operator==(const Admin& object);
	friend std::ostream& operator<<(std::ostream& COUT, const Admin& object);

	void display() const;
	void showMenu();

	int getID() const;
	int getAdminID() const;

	~Admin();
};

