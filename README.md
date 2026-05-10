# MediCore Hospital Management System

A C++ desktop application for managing hospital operations, built using SFML for the graphical interface. The system supports three user roles: Patient, Doctor, and Admin — each with their own login and dedicated features.

---

## Features

### Patient
- Register a new account or log in with existing credentials
- Book appointments by specialization, doctor, date, and time slot
- Cancel pending appointments (with automatic refund)
- View all personal appointments sorted by date
- View medical records and prescriptions
- View and pay bills
- Top up account balance

### Doctor
- View today's scheduled appointments
- Mark appointments as completed or no-show
- Write prescriptions for completed appointments
- View medical history of own patients

### Admin
- Add and remove doctors
- Add and remove patients
- View all patients, doctors, and appointments
- View and manage unpaid bills (with overdue flagging)
- Discharge patients (clears pending records)
- View security log (failed login attempts)
- Generate daily reports (appointments, revenue, doctor summaries)

---

## Project Structure

```
├── main.cpp
├── SFMLApp.h / SFMLApp.cpp       # Main app loop, all screen drawing and event handling
├── Patient.h                      # Patient class (inherits Person)
├── Doctor.h                       # Doctor class (inherits Person, dynamic specialization)
├── Admin.h                        # Admin class (inherits Person)
├── Appointment.h                  # Appointment class
├── Bill.h                         # Bill class
├── Prescription.h                 # Prescription class
├── Person.h                       # Base class
├── Storage.h                      # Generic templated storage class
├── FileHandler.h                  # All file read/write/update/delete operations
├── Validator.h                    # Input validation (contact, password, date, time)
├── HospitalException.h            # Base exception class
├── FileNotFoundException.h
├── InsufficientFundsException.h
├── InvalidInputException.h
└── SlotUnavailableException.h
```

---

## How to Build (Visual Studio)

1. Install SFML and link it to your project (include dirs, lib dirs, DLLs)
2. Add all `.h` and `.cpp` files to the project
3. Build and run

---

## Navigation

The app is keyboard-driven:

| Key | Action |
|-----|--------|
| Arrow Up / Down | Navigate menu |
| Enter | Select / Confirm |
| ESC | Go back / Cancel |
| R | Register (on Patient Login screen) |
| Backspace | Delete last character in input |

---

## Security

- Failed login attempts are logged to `security_log.txt` with role, ID, and timestamp
- After 3 consecutive failed attempts, the account is locked for that session
- Passwords are masked with `*` during input

---

## Constraints & Notes

- No STL `string` used anywhere — all string operations are custom (`customStrLen`, `StrCpyFunction`, `strcatFunction`, etc.)
- Patients cannot be removed or discharged if they have unpaid bills or pending appointments
- Doctors cannot be removed if they have pending appointments
- Appointment booking deducts the doctor's fee immediately; cancellation refunds it
- Bills marked as overdue if unpaid for more than 7 days
