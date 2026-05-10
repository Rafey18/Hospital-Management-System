#pragma once
#include<iostream>


class Bill {
private:
	int billID, patientID, appointmentID;
	double amount; char status[200];
	char date[11];


	void copyString(char* copyInto, const char* tobeCopied, int maxLength) {
		int i = 0;
		for (int index = 0; index < maxLength && tobeCopied[index] != '\0'; index++) {
			copyInto[index] = tobeCopied[index];
			i++;
		}
		copyInto[i] = '\0';
	}
public:
	Bill();
	Bill(int billID, int patientID, int appointmentID, double amount, const char* status, const char* date);

	int getID()const;
	int getBillID()const;
	int getPatientID()const;
	int getAppointmentID()const;
	double getAmount()const;
	const char* getDate() const;
	const char* getStatus() const;

	bool operator==(const Bill& object) const;
	friend std::ostream& operator<<(std::ostream& COUT, const Bill& object);

	void setStatus(const char* status);

	
};