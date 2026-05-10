#pragma once
#include<iostream>


class Appointment {
private:
	int appointmentID;
	int patientID;
	int doctorID;
	char date[11];
	char timeSlot[6];
	char status[10];
	bool isBooked;

	void copyString(char* copyInto, const char* tobeCopied, int maxLength) {
		int i = 0;
		for (int index = 0; index < maxLength && tobeCopied[index] != '\0'; index++) {
			copyInto[index] = tobeCopied[index];
			i++;
		}
		copyInto[i] = '\0';
	}

	bool isStringEqual(const char* string1, const char* string2) {
		for (int i = 0; string1[i] != '\0' && string2[i] != '\0'; i++) {
			if (string1[i] != string2[i]) {
				return false;
			}
		}
		return true;
	}
public:

	Appointment();
	Appointment(int appointmentID, int patientID, int doctorID, const char* date, const char* timeSlot, const char* status, bool isBooked);

	bool operator==(const Appointment& object);
	friend std::ostream& operator<<(std::ostream& COUT, const Appointment& object);

	int getID() const;
	int getAppointmentID()const;
	int getPatientID() const;
	int getDoctorID() const;
	const char* getDate()const;
	const char* getTimeSlot() const;
	const char* getStatus() const;
	bool getIsBooked()const;


	void setDate(const char* newDate);
	void setTimeSlot(const char* newTime);
	void setStatus(const char* newStatus);
	void setBooking(bool booked);
};
