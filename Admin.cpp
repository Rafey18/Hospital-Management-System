#include"Admin.h"

Admin::Admin() :Person(0, "", "", false) {
	adminID = 0;
}


Admin::Admin(int adminID, const char* name, const char* password, bool isLoggedIn) :Person(adminID, name, password, isLoggedIn) {
	this->adminID = adminID;
}

Admin::Admin(const Admin& object) :Person(object) {
	this->adminID = object.adminID;
}

Admin& Admin::operator=(const Admin& object) {
	if (this == &object) {
		return *this;
	}
	Person::operator=(object);
	this->adminID = object.adminID;
	return *this;
}

bool Admin::operator==(const Admin& object) {
	if (this->adminID == object.adminID) {
		return true;
	}
	else {
		return false;
	}
}


std::ostream& operator<<(std::ostream& COUT, const Admin& object) {
	COUT << "Admin ID: " << object.adminID << " | Name: " << object.name;
	return COUT;
}

void Admin::display() const{
	std::cout << "Admin Name: " << name << " | Admin ID: " << adminID <<
		" | ";
	if (isLoggedIn) {
		std::cout << "Logged In" << std::endl;
	}
	else {
		std::cout << "logged Out" << std::endl;
	}
}

void Admin::showMenu() {
	std::cout << std::endl;
	std::cout << "Admin Panel -- MediCore" << std::endl;
	std::cout << "==========================" << std::endl;
	std::cout << "1. Add Doctor" << std::endl;
	std::cout << "2. Remove Doctor" << std::endl;
	std::cout << "3. Add Patient" << std::endl;
	std::cout << "4. Delete Doctor" << std::endl;
	std::cout << "5. View All Patients" << std::endl;
	std::cout << "6. View All Doctors" << std::endl;
	std::cout << "7. View All Appointments" << std::endl;
	std::cout << "8. View Unpaid Bills" << std::endl;
	std::cout << "9. Discharge Patient" << std::endl;
	std::cout << "10. View Security Log" << std::endl;
	std::cout << "11. Generate Daily Report" << std::endl;
	std::cout << "12. Logout" << std::endl;
}


int Admin::getID() const{
	return id;
}

int Admin::getAdminID()const {
	return adminID;
}

Admin::~Admin() {

}