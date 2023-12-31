

#include "DriverCollection.h"
#include "Driver.h"
#include "LuxuryDriver/LuxuryDriver.h"
#include "BasicDriver/BasicDriver.h"
#include "EconomyDriver/EconomyDriver.h"
#include "GroupDriver/GroupDriver.h"
#include <iostream>
#include <limits>
#include <random>
#include <sstream>

using namespace std;


Driver *DriverCollection::addDriver() {

    auto *newDriver = new Driver;
    int vehicleType;
    string firstName;
    string lastName;
    vector<Ride> rides;
    string password;


    cout << "\n\n\n\n\n\n\n\n\n";
    cout << "********************************" << endl;
    cout << "********************************" << endl;
    cout << "      ___          __   __          ___  __  \n"
            "|\\ | |__  |  |    |  \\ |__) | \\  / |__  |__) \n"
            "| \\| |___ |/\\|    |__/ |  \\ |  \\/  |___ |  \\ \n"
            "                                             " << endl;

    cout << "********************************" << endl;
    cout << "********************************" << endl << endl << endl;


    cout << "********************************" << endl;
    cout << "*     Personal Information:    *" << endl;
    cout << "********************************" << endl;
    cout << "*  First Name: ";
    cin >> firstName;
    newDriver->firstName = firstName;
    cout << "*  Last Name: ";
    cin >> lastName;
    newDriver->lastName = lastName;
    cout << "*  Password: ";
    cin >> password;
    newDriver->password = password;
    cout << "********************************" << endl;
    cout << "\n";


    while (true) {
        cout << "********************************" << endl;
        cout << "*      Vehicle Information:    *" << endl;
        cout << "********************************" << endl;
        cout << "*      Enter Vehicle Type:     *" << endl;
        cout << "*1. Economy - (2 or less seats)*" << endl;
        cout << "*     2. Basic - (2-4 seats)   *" << endl;
        cout << "*    3. Group - (5-7 seats)    *" << endl;
        cout << "*   4. Luxury - (Limo-style)   *" << endl;
        cout << "********************************" << endl;
        cout << "* Type: ";

        // Check if input is an integer
        if (!(cin >> vehicleType) || (vehicleType < 1 || vehicleType > 4)) {
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    switch (vehicleType) {
        case 1:  // Economy Driver
        {
            auto *economyDriver = new EconomyDriver;
            economyDriver->addEconomyParameters();
            economyDriver->copyPropertiesFrom(newDriver);
            newDriver = economyDriver;
            break;
        }
        case 2:  // Basic Driver
        {
            auto *basicDriver = new BasicDriver;
            basicDriver->addBasicParameters();
            basicDriver->copyPropertiesFrom(newDriver);
            newDriver = basicDriver;
            break;
        }
        case 3:  // Group Driver
        {
            auto *groupDriver = new GroupDriver;
            groupDriver->addGroupParameters();
            groupDriver->copyPropertiesFrom(newDriver);
            newDriver = groupDriver;
            break;
        }
        case 4:  // Luxury Driver
        {
            auto *luxuryDriver = new LuxuryDriver;
            luxuryDriver->addLuxuryParameters();
            luxuryDriver->copyPropertiesFrom(newDriver);
            newDriver = luxuryDriver;
            break;
        }
        default:
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
    }

    newDriver->setVehicleType(static_cast<Driver::VehicleType>(vehicleType));


    char option;

    while (true) {
        cout << "Is Vehicle Handicapable? (Y/N): ";
        cin >> option;

        if (option == 'Y' || option == 'y') {
            newDriver->setHandicappedCapable(true);
            break;
        } else if (option == 'N' || option == 'n') {
            newDriver->setHandicappedCapable(false);
            break;
        } else {
            cout << "Not a valid input, please try again: " << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    cout << "*************************************" << endl;

    while (true) {
        cout << "Are Pets Allowed? (Y/N): ";
        cin >> option;

        if (option == 'Y' || option == 'y') {
            newDriver->setPetsAllowed(true);
            break;
        } else if (option == 'N' || option == 'n') {
            newDriver->setPetsAllowed(false);
            break;
        } else {
            cout << "Not a valid input, please try again: " << endl;
            cin.clear();
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }

    cout << "************************************* \n\n\n\n\n\n";


    /*true random number*/
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(1, 20000);
    int random_number = distribution(generator);
    newDriver->id = random_number;

    newDriver->setAvailable(true);
    newDriver->setDriverRating(0);


    this->drivers.push_back(newDriver);
    return newDriver;


}



void DriverCollection::removeDriver(Driver &driver) {
    for (auto it = this->drivers.begin(); it != this->drivers.end();) {
        if ((*it)->getId() == driver.getId()) {
            delete *it;
            it = this->drivers.erase(it);
        } else {
            ++it;
        }
    }
}

void DriverCollection::readDriverProperties(const string &basicString) {
    istringstream dataStream(basicString);
    string temp;


    getline(dataStream, temp, ',');
    {/*the string that says "Driver" goes here */}

    getline(dataStream, temp, ',');
    {
        int subClass = stoi(temp);
        switch (subClass) {
            case 1: {
                auto *economyDriver = new EconomyDriver;
                economyDriver->readEconomyProperties(basicString);
                this->drivers.push_back(economyDriver);
                break;
            }
            case 2: {
                auto *basicDriver = new BasicDriver;
                basicDriver->readBasicProperties(basicString);
                this->drivers.push_back(basicDriver);
                break;
            }
            case 3: {
                auto *groupDriver = new GroupDriver;
                groupDriver->readGroupProperties(basicString);
                this->drivers.push_back(groupDriver);
                break;
            }
            case 4: {
                auto *luxuryDriver = new LuxuryDriver;
                luxuryDriver->readLuxuryProperties(basicString);
                this->drivers.push_back(luxuryDriver);
                break;
            }
            default:
                break;
        }
    }
}




