#pragma once


class HospitalException {
protected:
	char message[200];

	void copyString(char* copyInto, const char* tobeCopied, int maxLength) {
		int i = 0;
		for (int index = 0; index < maxLength && tobeCopied[index] != '\0'; index++) {
			copyInto[index] = tobeCopied[index];
			i++;
		}
		copyInto[i] = '\0';
	}
public:
	HospitalException(const char* messageP) {
		copyString(this->message, messageP, 200);
	}

	virtual const char* what() {
		return message;
	};
	virtual ~HospitalException() {}
};