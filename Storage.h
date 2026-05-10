#pragma once

template <typename T>
class Storage {
private:
	T StorageData[100];
	int count;

public:
	Storage() {
		count = 0;
	}

	bool add(const T& dataToBeAdded) {
		if (count >= 100) {
			return false;
		}
		else {
			StorageData[count] = dataToBeAdded;
			count++;
			return true;
		}
	}

	bool removeByID(int id) {
		for (int i = 0; i < count; i++) {
			if (StorageData[i].getID() == id) {
				for (int x = i; x < count - 1; x++) {
					StorageData[x] = StorageData[x + 1];
				}
				count--;
				return true;
			}
		}
		return false;
	}


	T* findID(int id) {
		for (int i = 0; i < count; i++) {
			if (id == StorageData[i].getID()) {
				return &StorageData[i];
			}
		}
		return nullptr;
	}

	void clearAllData() {
		count = 0;
	}

	bool isFull() {
		if (count >= 100) {
			return true;
		}
		else {
			return false;
		}
	}

	int arraySize() {
		return count;
	}

	T* getAll() {
		return StorageData;
	}
};
