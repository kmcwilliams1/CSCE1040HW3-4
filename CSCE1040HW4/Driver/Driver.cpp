
#include <sstream>
#include "Driver.h"


Driver::~Driver() = default;

Driver::Driver() = default;


bool Driver::isHandicappedCapable() const {
    return handicappedCapable;
}

void Driver::setHandicappedCapable(bool isHandicappedCapable) {
    handicappedCapable = isHandicappedCapable;
}

Driver::VehicleType Driver::getVehicleType() const {
    return vehicleType;
}

void Driver::setVehicleType(VehicleType type) {
    vehicleType = type;
}

float Driver::getDriverRating() const {
    return driverRating;
}

void Driver::setDriverRating(float rating) {
    driverRating = rating;
}

bool Driver::isPetsAllowed() const {
    return petsAllowed;
}

void Driver::setPetsAllowed(bool isPetsAllowed) {
    petsAllowed = isPetsAllowed;
}

bool Driver::isAvailable() const {
    return available;
}

void Driver::setAvailable() {
    available = !available;
}

int Driver::getId() const {
    return id;
}

void Driver::setId(int newId) {
    id = newId;
}

const string &Driver::getFirstName() const {
    return firstName;
}

void Driver::setFirstName(const string &first) {
    firstName = first;
}

const string &Driver::getLastName() const {
    return lastName;
}

void Driver::setLastName(const string &last) {
    lastName = last;
}


void Driver::setCompletedRides() {
    int i;
    for (Ride &ride: rides) {
        if (ride.getStatus() == Ride::RideStatus::Active) {
            cout << ride.pickupLocation << " -> " << ride.dropOffLocation << endl;
            cout << ride.id << endl;
        }
    }
    cout << "Which ride ID do you want to complete?" << endl;
    cin >> i;

    for (Ride &ride: rides) {
        if (ride.id == i) {
            ride.setStatus(Ride::RideStatus::Completed);
        }
    }

}


void Driver::setCancelledRides() {
    int i;
    for (Ride &ride: rides) {
        if (ride.getStatus() == Ride::RideStatus::Active) {
            cout << ride.pickupLocation << " -> " << ride.dropOffLocation << endl;
            cout << ride.id << endl;
        }
    }
    cout << "Which ride ID do you want to cancel?" << endl;
    cin >> i;

    for (Ride &ride: rides) {
        if (ride.id == i) {
            ride.setStatus(Ride::RideStatus::Cancelled);
        }
    }
}

const vector<Ride> &Driver::getRides() const {
    return rides;
}

const string &Driver::getPassword() const {
    return password;
}

void Driver::setPassword(const string &pass) {
    password = pass;
}

void Driver::getSchedule() {
    if (!rides.empty()) {
        cout << "Rides:" << endl;
        cout << "---------------------------------------" << endl;
        for (const Ride &ride: rides) {
            cout << "Pickup Location: " << ride.getPickupLocation() << endl;
            cout << "Drop-Off Location: " << ride.getDropOffLocation() << endl;
            cout << "Pickup Time: " << ride.getPickupTime() << endl;
            cout << "---------------------------------------" << endl;
        }
    } else {
        cout << "No rides available for this passenger." << endl;
    }

}

void Driver::getInfo() const {
    cout << "--------------------------------" << endl;
    cout << this->firstName << " " << this->lastName << endl;

}

void Driver::deleteCancelledAndCompletedRides() {
    for (auto it = rides.begin(); it != rides.end();) {
        if (it->rideStatus == Ride::RideStatus::Completed || it->rideStatus == Ride::RideStatus::Cancelled) {
            this->rides.erase(it);
        }
    }
}

void Driver::readDriverProperties(const string &basicString) {
    istringstream dataStream(basicString);
    string temp;

    getline(dataStream, temp, ',');
    {};

    getline(dataStream, temp, ',');
    {
        this->firstName = temp;
    };
    getline(dataStream, temp, ',');
    {
        this->lastName = temp;
    };
    getline(dataStream, temp, ',');
    {
        this->id = stoi(temp);
    };
    getline(dataStream, temp, ',');
    {
        this->available = true;
    };
    getline(dataStream, temp, ',');
    {
        this->vehicleType = static_cast<Driver::VehicleType>(stoi(temp));
    };
    getline(dataStream, temp, ',');
    {
        temp = std::to_string(1 ? this->petsAllowed = true : this->petsAllowed = false);
    };
    getline(dataStream, temp, ',');
    {
        this->driverRating = stof(temp);
    };
    getline(dataStream, temp, ',');
    {
        this->password = temp;
    };
    getline(dataStream, temp, '\n');
    {
        for (int i = 0; i < temp.length(); i++) {}
    };
    while (getline(dataStream, temp, ',')) {
        int tripID = stoi(temp);
        if (!rides.empty()) {
            rides.back().setId(tripID);
        }
    }
}

void Driver::writeDriverProperties(ostream &dataFile) {
    dataFile << "Driver,";
    dataFile << firstName << ",";
    dataFile << lastName << ",";
    dataFile << id << ",";
    dataFile << available << ","; // isAvailable
    dataFile << handicappedCapable << ",";
    dataFile << static_cast<int>(vehicleType) << ",";
    dataFile << petsAllowed << ",";
    dataFile << driverRating << ","; // driverRating
    dataFile << password << ",";
    for (const Ride &ride: rides) {
        dataFile << ride.getId() << ",";
    }
    dataFile << "\n";
}

void Driver::getCompletedRides() const {
    for (const Ride &ride: rides) {
        if (ride.rideStatus == Ride::RideStatus::Completed) {
            cout << ride.pickupLocation << " -> " << ride.dropOffLocation << endl;
            cout << ride.pickupTime << endl;
        }
    }
}

void Driver::getCancelledRides() const {
    for (const Ride &ride: rides) {
        if (ride.rideStatus == Ride::RideStatus::Cancelled) {
            cout << ride.pickupLocation << " -> " << ride.dropOffLocation << endl;
            cout << ride.pickupTime << endl;
        }
    }
}

void Driver::editInfo() {

}

void Driver::copyPropertiesFrom(const Driver *otherDriver) {

    if (otherDriver) {
        this->setHandicappedCapable(otherDriver->isHandicappedCapable());
        this->setPetsAllowed(otherDriver->isPetsAllowed());
        this->setDriverRating(otherDriver->getDriverRating());
        this->setId(otherDriver->getId());
        this->setFirstName(otherDriver->getFirstName());
        this->setLastName(otherDriver->getLastName());
        this->setPassword(otherDriver->password);

    };
    this->rides.clear();
    for (auto &&ride: otherDriver->getRides()) {
        this->rides.push_back(ride);
    }


}

