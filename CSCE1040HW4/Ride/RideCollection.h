

#ifndef CSCE1040HW4_RIDECOLLECTION_H
#define CSCE1040HW4_RIDECOLLECTION_H


#include "../Driver/Driver.h"

class RideCollection {

public:
    Ride *addRide(Ride* newRide);
    vector<Ride* > rides;

    void assignSchedule(Driver& driver);

    void readRideProperties(const string& basicString);
};


#endif //CSCE1040HW4_RIDECOLLECTION_H
