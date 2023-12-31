

#ifndef CSCE1040HW4_RIDE_H
#define CSCE1040HW4_RIDE_H


#include <ctime>
#include <iostream>
using namespace std;



class Ride {
public:
    Ride();
    ~Ride();
    //variables
    enum class RideStatus {
        Active = 12,
        Completed,
        Cancelled
    };
    int sizeOfParty{};
    bool includesPets{};
    RideStatus rideStatus{};
    float rating{};
    int id{};
    string pickupLocation;
    string dropOffLocation;
    time_t pickupTime{};
    time_t dropOffTime{};
    string note;
    bool handicapable{};
    int assignedDriverId{};
    int assignedPassengerId{};


    //methods
    void writeRideProperties(ostream &dataFile) const;

    //setters and getters
    int getSizeOfParty() const;
    void setSizeOfParty(int partySize);

    bool getIncludesPets() const;
    void setIncludesPets();

    RideStatus getStatus() const;
    void setStatus(RideStatus status);

    float getRating() const;
    void setRating(float rideRating);

    int getId() const;
    void setId();

    string getPickupLocation() const;
    void setPickupLocation(const string& location);

    string getDropOffLocation() const;
    void setDropOffLocation(const string& location);

    string getPickupTime() const;
    void setPickupTime();

    string getDropOffTime() const;
    void setDropOffTime();

    const string& getNote() const;
    void setNote(const string &note);

    bool getHandicapped() const;
    void setHandicapped();

    int getAssignedDriverId() const;
    void setAssignedDriverId(int driverId);

    int getAssignedPassengerId()const;
    void setAssignedPassengerId(int passengerId);


};


#endif //CSCE1040HW4_RIDE_H
