#include "FileHandler.h"
#include "FileNotFoundException.h"


const char* FileHandler::PatientFile = "patients.txt";
const char* FileHandler::DoctorFile = "doctors.txt";
const char* FileHandler::AdminFile = "admin.txt";
const char* FileHandler::AppointmentFile = "appointments.txt";
const char* FileHandler::BillFile = "bills.txt";
const char* FileHandler::PrescriptionFile = "prescriptions.txt";
const char* FileHandler::SecurityLogFile = "security_log.txt";
const char* FileHandler::DischargeFile = "discharged.txt";


// Since comma sai seperated --> splitAttribute takes comma to seperate
// Returns the number of fields found
int FileHandler::splitAttributes(const char* fileLine, char attributes[][200], int maxAttributes) {
	int columnIndex = 0;
	int charIndex = 0;

	for (int i = 0; fileLine[i] != '\0' && fileLine[i] != '\n' ; i++) {
		if (fileLine[i] == ',' && columnIndex < maxAttributes - 1) {
			attributes[columnIndex][charIndex] = '\0';
			columnIndex++;
			charIndex = 0;
		}
		else {
			if (charIndex < 199) {
				attributes[columnIndex][charIndex] = fileLine[i];
				charIndex++;
			}
		}
	}
	attributes[columnIndex][charIndex] = '\0';
	return columnIndex + 1;
}

int FileHandler::charToInt(const char* numberString) {
	int result = 0;
	int index = 0;
	while (numberString[index] == ' ') {
		index++;
	}
	while (numberString[index] >= '0' && numberString[index] <= '9') {
		result = result * 10 + charToDigit(numberString[index]);
		index++;
	}
	return result;
}

double FileHandler::charToDouble(const char* numberString) {
	double result = 0.0;
	double decimalMultiplier = 0.1;
	bool afterDecimalPoint = false;
	int index = 0;

	while (numberString[index] == ' ') {
		index++;
	}
	while (numberString[index] != '\0' && numberString[index] != '\n' && numberString[index] != '\r') {
		if (numberString[index] == '.') {
			afterDecimalPoint = true;
		}
		else if (numberString[index] >= '0' && numberString[index] <= '9') {
			if (!afterDecimalPoint) {
				result = result * 10 + charToDigit(numberString[index]);
			}
			else {
				result += charToDigit(numberString[index]) * decimalMultiplier;
				decimalMultiplier *= 0.1;
			}
		}
		index++;
	}
	return result;
}

void FileHandler::intToChar(int number, char* outputArray) {
	if (number == 0) {
		outputArray[0] = '0';
		outputArray[1] = '\0';
		return;
	}
	char reversedDigits[20];
	int digitCount = 0;
	while (number > 0) {
		reversedDigits[digitCount++] = '0' + number % 10;
		number /= 10;
	}
	for (int i = 0; i < digitCount; i++) {
		outputArray[i] = reversedDigits[digitCount - 1 - i];
	}
	outputArray[digitCount] = '\0';
}

void FileHandler::doubleToChar(double number, char* outputArray, int decimalPlaces) {
	int integerPart = (int)number;
	intToChar(integerPart, outputArray);

	int index = 0;
	while (outputArray[index] != '\0') {
		index++;
	}
	outputArray[index++] = '.';

	double fractionalPart = number - integerPart;
	for (int i = 0; i < decimalPlaces; i++) {
		fractionalPart *= 10;
		int digit = (int)fractionalPart;
		outputArray[index++] = '0' + digit;
		fractionalPart -= digit;
	}
	outputArray[index] = '\0';
}

bool FileHandler::isStringEqual(const char* firstString, const char* secondString) {
	int index = 0;
	while (firstString[index] != '\0' && secondString[index] != '\0') {
		if (firstString[index] != secondString[index]) {
			return false;
		}
		index++;
	}
	return firstString[index] == '\0' && secondString[index] == '\0';
}


// File format: patient_id,name,age,gender,contact,password,balance
void FileHandler::loadPatients(Storage<Patient>& storage) {
	std::ifstream file(PatientFile);
	if (!file.is_open()) {
		throw FileNotFoundException(PatientFile);
	}

	char line[500];
	while (file.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}

		char attributes[7][200];
		int fieldCount = splitAttributes(line, attributes, 7);
		if (fieldCount < 7 || attributes[0][0] == '\0' || attributes[1][0] == '\0' || attributes[2][0] == '\0' || attributes[3][0] == '\0' || attributes[4][0] == '\0' ||
			attributes[5][0] == '\0' || attributes[6][0] == '\0') {
			continue;
		}

		int patientID  = charToInt(attributes[0]);
		int age        = charToInt(attributes[2]);
		char gender    = attributes[3][0];
		double balance = charToDouble(attributes[6]);

		Patient patientObject(patientID, attributes[1], attributes[5], false, balance, gender, age, attributes[4], 0);
		storage.add(patientObject);
	}
	file.close();
}

// File format: doctor_id,name,specialization,contact,password,fee
void FileHandler::loadDoctors(Storage<Doctor>& storage) {
	std::ifstream file(DoctorFile);
	if (!file.is_open()) {
		throw FileNotFoundException(DoctorFile);
	}

	char line[500];
	while (file.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}

		char attributes[6][200];
		int fieldCount = splitAttributes(line, attributes, 6);
		if (fieldCount < 6 || attributes[0][0] == '\0' || attributes[1][0] == '\0' || attributes[2][0] == '\0' || attributes[3][0] == '\0' || attributes[4][0] == '\0' ||
			attributes[5][0] == '\0') {
			continue;
		}

		int doctorID = charToInt(attributes[0]);
		double fee   = charToDouble(attributes[5]);

		Doctor doctorObject(doctorID, attributes[1], attributes[4], attributes[2], attributes[3], fee, false);
		storage.add(doctorObject);
	}
	file.close();
}

// File format: admin_id,name,password
void FileHandler::loadAdmins(Storage<Admin>& storage) {
	std::ifstream file(AdminFile);
	if (!file.is_open()) {
		throw FileNotFoundException(AdminFile);
	}

	char line[300];
	while (file.getline(line, 300)) {
		if (line[0] == '\0') {
			continue;
		}

		char attributes[3][200];
		int fieldCount = splitAttributes(line, attributes, 3);
		if (fieldCount < 3 || attributes[0][0] == '\0' || attributes[1][0] == '\0' || attributes[2][0] == '\0') {
			continue;
		}
		int adminID = charToInt(attributes[0]);

		Admin adminObject(adminID, attributes[1], attributes[2], false);
		storage.add(adminObject);
	}
	file.close();
}

// File format: appointment_id,patient_id,doctor_id,date,time_slot,status
void FileHandler::loadAppointments(Storage<Appointment>& storage) {
	std::ifstream file(AppointmentFile);
	if (!file.is_open()) {
		throw FileNotFoundException(AppointmentFile);
	}

	char line[500];
	while (file.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}

		char attributes[6][200];
		int fieldCount = splitAttributes(line, attributes, 6);
		if (fieldCount < 6 || attributes[0][0] == '\0' || attributes[1][0] == '\0' || attributes[2][0] == '\0' || attributes[3][0] == '\0' || attributes[4][0] == '\0' ||
			attributes[5][0] == '\0') {
			continue;
		}

		int appointmentID = charToInt(attributes[0]);
		int patientID     = charToInt(attributes[1]);
		int doctorID      = charToInt(attributes[2]);

		Appointment appointmentObject(appointmentID, patientID, doctorID, attributes[3], attributes[4], attributes[5], true);
		storage.add(appointmentObject);
	}
	file.close();
}

// File format: bill_id,patient_id,appointment_id,amount,status,date
void FileHandler::loadBills(Storage<Bill>& storage) {
	std::ifstream file(BillFile);
	if (!file.is_open()) {
		throw FileNotFoundException(BillFile);
	}

	char line[500];
	while (file.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}

		char attributes[6][200];
		int fieldCount = splitAttributes(line, attributes, 6);
		if (fieldCount < 7 || attributes[0][0] == '\0' || attributes[1][0] == '\0' || attributes[2][0] == '\0' || attributes[3][0] == '\0' || attributes[4][0] == '\0' ||
			attributes[5][0] == '\0') {
			continue;
		}

		int billID        = charToInt(attributes[0]);
		int patientID     = charToInt(attributes[1]);
		int appointmentID = charToInt(attributes[2]);
		double amount     = charToDouble(attributes[3]);

		Bill billObject(billID, patientID, appointmentID, amount, attributes[4], attributes[5]);
		storage.add(billObject);
	}
	file.close();
}

// File format: prescription_id,appointment_id,patient_id,doctor_id,date,medicines,notes
void FileHandler::loadPrescriptions(Storage<Prescription>& storage) {
	std::ifstream file(PrescriptionFile);
	if (!file.is_open()) {
		throw FileNotFoundException(PrescriptionFile);
	}

	char line[200];
	while (file.getline(line, 200)) {
		if (line[0] == '\0') {
			continue;
		}

		char attributes[7][200];
		int fieldCount = splitAttributes(line, attributes, 7);
		if (fieldCount < 7) {
			continue;
		}

		int prescriptionID = charToInt(attributes[0]);
		int appointmentID  = charToInt(attributes[1]);
		int patientID      = charToInt(attributes[2]);
		int doctorID       = charToInt(attributes[3]);

		Prescription prescriptionObject(prescriptionID, appointmentID, patientID, doctorID, attributes[4], attributes[5], attributes[6]);
		storage.add(prescriptionObject);
	}
	file.close();
}


void FileHandler::appendPatient(const Patient& patient) {
	std::ofstream file(PatientFile, std::ios::app);
	if (!file.is_open()) {
		return;
	}

	char patientIDCharArray[10];
	char ageCharArray[10];
	char balanceCharArray[20];

	intToChar(patient.getPatientID(), patientIDCharArray);
	intToChar(patient.getAge(), ageCharArray);
	doubleToChar(patient.getBalance(), balanceCharArray, 2);

	file << patientIDCharArray << ","
		<< patient.getName() << ","
		<< ageCharArray << ","
		<< patient.getGender() << ","
		<< patient.getPhoneNumber() << ","
		<< patient.getPassword() << ","
		<< balanceCharArray << std::endl;

	file.close();
}

void FileHandler::appendDoctor(const Doctor& doctor) {
	std::ofstream file(DoctorFile, std::ios::app);
	if (!file.is_open()) {
		return;
	}

	char doctorIDCharArray[10];
	char feeCharArray[20];

	intToChar(doctor.getDoctorID(), doctorIDCharArray);
	doubleToChar(doctor.getFee(), feeCharArray, 2);

	file << doctorIDCharArray << ","
		<< doctor.getName() << ","
		<< doctor.getSpecialization() << ","
		<< doctor.getContactNumber() << ","
		<< doctor.getPassword() << ","
		<< feeCharArray << std::endl;

	file.close();
}

void FileHandler::appendAppointment(const Appointment& appointment) {
	std::ofstream file(AppointmentFile, std::ios::app);
	if (!file.is_open()) {
		return;
	}

	char appointmentIDCharArray[10];
	char patientIDCharArray[10];
	char doctorIDCharArray[10];

	intToChar(appointment.getAppointmentID(), appointmentIDCharArray);
	intToChar(appointment.getPatientID(), patientIDCharArray);
	intToChar(appointment.getDoctorID(), doctorIDCharArray);

	file << appointmentIDCharArray << ","
		<< patientIDCharArray << ","
		<< doctorIDCharArray << ","
		<< appointment.getDate() << ","
		<< appointment.getTimeSlot() << ","
		<< appointment.getStatus() << std::endl;

	file.close();
}

void FileHandler::appendBill(const Bill& bill) {
	std::ofstream file(BillFile, std::ios::app);
	if (!file.is_open()) {
		return;
	}

	char billIDCharArray[10];
	char patientIDCharArray[10];
	char appointmentIDCharArray[10];
	char amountCharArray[20];

	intToChar(bill.getBillID(), billIDCharArray);
	intToChar(bill.getPatientID(), patientIDCharArray);
	intToChar(bill.getAppointmentID(), appointmentIDCharArray);
	doubleToChar(bill.getAmount(), amountCharArray, 2);

	file << billIDCharArray << ","
		<< patientIDCharArray << ","
		<< appointmentIDCharArray << ","
		<< amountCharArray << ","
		<< bill.getStatus() << ","
		<< bill.getDate() << std::endl;

	file.close();
}

void FileHandler::appendPrescription(const Prescription& prescription) {
	std::ofstream file(PrescriptionFile, std::ios::app);
	if (!file.is_open()) {
		return;
	}

	char prescriptionIDCharArray[10];
	char appointmentIDCharArray[10];
	char patientIDCharArray[10];
	char doctorIDCharArray[10];

	intToChar(prescription.getPrescriptionID(), prescriptionIDCharArray);
	intToChar(prescription.getappointmentID(), appointmentIDCharArray);
	intToChar(prescription.getpatientID(), patientIDCharArray);
	intToChar(prescription.getdoctorID(), doctorIDCharArray);

	file << prescriptionIDCharArray << ","
		<< appointmentIDCharArray << ","
		<< patientIDCharArray << ","
		<< doctorIDCharArray << ","
		<< prescription.getDate() << ","
		<< prescription.getMedicine() << ","
		<< prescription.getNotes() << std::endl;

	file.close();
}


void FileHandler::updatePatient(const Patient& patient) {
	std::ifstream inFile(PatientFile);
	if (!inFile.is_open()) {
		throw FileNotFoundException(PatientFile);
	}
	std::ofstream outFile("temp_patient.txt");

	char patientIDCharArray[10];
	intToChar(patient.getPatientID(), patientIDCharArray);

	char line[500];
	while (inFile.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}

		char attributes[7][200];
		splitAttributes(line, attributes, 7);

		if (isStringEqual(attributes[0], patientIDCharArray)) {
			char ageCharArray[10];
			char balanceCharArray[20];
			intToChar(patient.getAge(), ageCharArray);
			doubleToChar(patient.getBalance(), balanceCharArray, 2);

			outFile << patientIDCharArray << ","
				<< patient.getName() << ","
				<< ageCharArray << ","
				<< patient.getGender() << ","
				<< patient.getPhoneNumber() << ","
				<< patient.getPassword() << ","
				<< balanceCharArray << std::endl;
		}
		else {
			outFile << line << std::endl;
		}
	}

	inFile.close();
	outFile.close();
	remove(PatientFile);
	rename("temp_patient.txt", PatientFile);
}

void FileHandler::updateAppointment(const Appointment& appointment) {
	std::ifstream inFile(AppointmentFile);
	if (!inFile.is_open()) {
		throw FileNotFoundException(AppointmentFile);
	}
	std::ofstream outFile("temp_appointment.txt");

	char appointmentIDCharArray[10];
	intToChar(appointment.getAppointmentID(), appointmentIDCharArray);

	char line[500];
	while (inFile.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}

		char attributes[6][200];
		splitAttributes(line, attributes, 6);

		if (isStringEqual(attributes[0], appointmentIDCharArray)) {
			char patientIDCharArray[10];
			char doctorIDCharArray[10];
			intToChar(appointment.getPatientID(), patientIDCharArray);
			intToChar(appointment.getDoctorID(), doctorIDCharArray);

			outFile << appointmentIDCharArray << ","
				<< patientIDCharArray << ","
				<< doctorIDCharArray << ","
				<< appointment.getDate() << ","
				<< appointment.getTimeSlot() << ","
				<< appointment.getStatus() << std::endl;
		}
		else {
			outFile << line << std::endl;
		}
	}

	inFile.close();
	outFile.close();
	remove(AppointmentFile);
	rename("temp_appointment.txt", AppointmentFile);
}

void FileHandler::updateBill(const Bill& bill) {
	std::ifstream inFile(BillFile);
	if (!inFile.is_open()) {
		throw FileNotFoundException(BillFile);
	}
	std::ofstream outFile("temp_bill.txt");

	char billIDCharArray[10];
	intToChar(bill.getBillID(), billIDCharArray);

	char line[500];
	while (inFile.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}

		char attributes[6][200];
		splitAttributes(line, attributes, 6);

		if (isStringEqual(attributes[0], billIDCharArray)) {
			char patientIDCharArray[10];
			char appointmentIDCharArray[10];
			char amountCharArray[20];
			intToChar(bill.getPatientID(), patientIDCharArray);
			intToChar(bill.getAppointmentID(), appointmentIDCharArray);
			doubleToChar(bill.getAmount(), amountCharArray, 2);

			outFile << billIDCharArray << ","
				<< patientIDCharArray << ","
				<< appointmentIDCharArray << ","
				<< amountCharArray << ","
				<< bill.getStatus() << ","
				<< bill.getDate() << std::endl;
		}
		else {
			outFile << line << std::endl;
		}
	}

	inFile.close();
	outFile.close();
	remove(BillFile);
	rename("temp_bill.txt", BillFile);
}


void FileHandler::deletePatient(int patientID) {
	std::ifstream inFile(PatientFile);
	if (!inFile.is_open()) {
		return;
	}
	std::ofstream outFile("temp_delete_patient.txt");

	char patientIDCharArray[10];
	intToChar(patientID, patientIDCharArray);

	char line[500];
	while (inFile.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}
		char attributes[7][200];
		splitAttributes(line, attributes, 7);

		if (!isStringEqual(attributes[0], patientIDCharArray)) {
			outFile << line << std::endl;
		}
	}

	inFile.close();
	outFile.close();
	remove(PatientFile);
	rename("temp_delete_patient.txt", PatientFile);
}

void FileHandler::deleteDoctor(int doctorID) {
	std::ifstream inFile(DoctorFile);
	if (!inFile.is_open()) {
		return;
	}
	std::ofstream outFile("temp_delete_doctor.txt");

	char doctorIDCharArray[10];
	intToChar(doctorID, doctorIDCharArray);

	char line[500];
	while (inFile.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}
		char attributes[6][200];
		splitAttributes(line, attributes, 6);

		if (!isStringEqual(attributes[0], doctorIDCharArray)) {
			outFile << line << "\n";
		}
	}

	inFile.close();
	outFile.close();
	remove(DoctorFile);
	rename("temp_delete_doctor.txt", DoctorFile);
}


// Reads a file and returns the highest ID found (first field on each line) + 1
static int getMaxIDFromFile(const char* filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		return 0;
	}

	int maxID = 0;
	char line[500];
	while (file.getline(line, 500)) {
		if (line[0] == '\0') {
			continue;
		}
		int currentID = 0;
		int index = 0;
		while (line[index] >= '0' && line[index] <= '9') {
			currentID = currentID * 10 + (line[index] - '0');
			index++;
		}
		if (currentID > maxID) {
			maxID = currentID;
		}
	}
	file.close();
	return maxID;
}

int FileHandler::getFilePatientID(){
	return getMaxIDFromFile(PatientFile) + 1;
}
int FileHandler::getFileDoctorID() {
	return getMaxIDFromFile(DoctorFile) + 1;
}
int FileHandler::getFileAppointmentID(){
	return getMaxIDFromFile(AppointmentFile) + 1;
}
int FileHandler::geFileBillID(){
	return getMaxIDFromFile(BillFile) + 1; 
}
int FileHandler::getFilePrescriptionID(){
	return getMaxIDFromFile(PrescriptionFile) + 1;
}


void FileHandler::logSecurityEvent(const char* role, int enteredID, const char* result) {
	std::ofstream file(SecurityLogFile, std::ios::app);
	if (!file.is_open()) {
		return;
	}

	time_t now = time(nullptr);
	tm timeInfo;
	localtime_s(&timeInfo, &now);

	char timeStampBuffer[30];
	strftime(timeStampBuffer, sizeof(timeStampBuffer), "%d-%m-%Y %H:%M:%S", &timeInfo);

	char enteredIDCharArray[10];
	intToChar(enteredID, enteredIDCharArray);

	file << timeStampBuffer << "," << role << "," << enteredIDCharArray << "," << result << std::endl;
	file.close();
}

void FileHandler::readSecurityLog() {
	std::ifstream file(SecurityLogFile);
	if (!file.is_open()) {
		std::cout << "No security events logged.\n";
		return;
	}

	char line[300];
	bool hasEvents = false;
	while (file.getline(line, 300)) {
		if (line[0] != '\0') {
			std::cout << line << std::endl;
			hasEvents = true;
		}
	}
	if (!hasEvents) {
		std::cout << "No security events logged." << std::endl;
	}
	file.close();
}


void FileHandler::dischargePatient(const Patient& patient) {
	char patientIDCharArray[10];
	intToChar(patient.getPatientID(), patientIDCharArray);

	//Basically discharge patient meaning we remove patient from patient itself ,and data from appointment, prescription and bill
	{
		std::ofstream outFile(DischargeFile, std::ios::app);
		char ageCharArray[10];
		char balanceCharArray[20];
		intToChar(patient.getAge(), ageCharArray);
		doubleToChar(patient.getBalance(), balanceCharArray, 2);

		outFile << patientIDCharArray << ","
			<< patient.getName() << ","
			<< ageCharArray << ","
			<< patient.getGender() << ","
			<< patient.getPhoneNumber() << ","
			<< patient.getPassword() << ","
			<< balanceCharArray << "\n";
	}

	// Removing patient
	deletePatient(patient.getPatientID());

	//Then Removing patient's appointments from file
	{
		std::ifstream inFile(AppointmentFile);
		std::ofstream outFile("temp_discharge_appointments.txt");
		char line[500];
		while (inFile.getline(line, 500)) {
			if (line[0] == '\0') {
				continue;
			}
			char attributes[6][200];
			splitAttributes(line, attributes, 6);
			if (!isStringEqual(attributes[1], patientIDCharArray)) {
				outFile << line << std::endl;
			}
		}
		inFile.close();
		outFile.close();
		remove(AppointmentFile);
		rename("temp_discharge_appointments.txt", AppointmentFile);
	}

	//Thenn Removing patient's bills file
	{
		std::ifstream inFile(BillFile);
		std::ofstream outFile("temp_discharge_bills.txt");
		char line[500];
		while (inFile.getline(line, 500)) {
			if (line[0] == '\0') {
				continue;
			}
			char attributes[6][200];
			splitAttributes(line, attributes, 6);
			if (!isStringEqual(attributes[1], patientIDCharArray)) {
				outFile << line << std::endl;
			}
		}
		inFile.close();
		outFile.close();
		remove(BillFile);
		rename("temp_discharge_bills.txt", BillFile);
	}

	//Thennn Removing patient's prescriptions file
	{
		std::ifstream inFile(PrescriptionFile);
		std::ofstream outFile("temp_discharge_prescriptions.txt");
		char line[1200];
		while (inFile.getline(line, 1200)) {
			if (line[0] == '\0') {
				continue;
			}
			char attributes[7][200];
			splitAttributes(line, attributes, 7);
			if (!isStringEqual(attributes[2], patientIDCharArray)) {
				outFile << line << std::endl;
			}
		}
		inFile.close();
		outFile.close();
		remove(PrescriptionFile);
		rename("temp_discharge_prescriptions.txt", PrescriptionFile);
	}
}
