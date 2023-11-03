

#ifndef CSCE1040HW4_DRIVERCOLLECTION_H
#define CSCE1040HW4_DRIVERCOLLECTION_H


#include "Driver.h"

class DriverCollection {

public:
    Driver addDriver(Driver driver);
    vector<Driver> drivers;

    void removeDriver(const Driver& driver);
};


#endif //CSCE1040HW4_DRIVERCOLLECTION_H
