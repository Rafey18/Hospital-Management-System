#pragma once
#include "HospitalException.h"


class SlotUnavailableException : public HospitalException {
public:
    SlotUnavailableException() : HospitalException("This time slot is already booked. Please choose another."){}

};