#pragma once
#include "HospitalException.h"

class InsufficientFundsException : public HospitalException {
public:
    InsufficientFundsException() : HospitalException("Insufficient funds , please check your balance again") {

    }
   
};