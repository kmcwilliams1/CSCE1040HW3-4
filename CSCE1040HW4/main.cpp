#include <iostream>
#include <fstream>
#include "Driver/Driver.h"
#include "Passenger/Passenger.h"
#include "Ride/Ride.h"
#include "Driver/DriverCollection.h"
#include "Passenger/PassengerCollection.h"
#include "Ride/RideCollection.h"
#include "DriverMenu.cpp"
#include "PassengerMenu.cpp"

using namespace std;


int main() {
    Driver *driver;
    Passenger *passenger;

    DriverCollection driverCollection;
    PassengerCollection passengerCollection;
    RideCollection rideCollection;

    ifstream fin("RideShareData.dat");

    bool driverLoggedIn = false;
    char option;
    string enteredPassword;
    string readingLine;
    string role;
    string driverSearchWord = "Driver";
    string passengerSearchWord = "Passenger";
    string rideSearchWord = "Ride";

    while (fin >> readingLine) {
        role = readingLine.substr(0, readingLine.find(','));

        if (role == driverSearchWord) {

            driverCollection.readDriverProperties(readingLine);

        } else if (role == rideSearchWord) {

            rideCollection.readRideProperties(readingLine);

        } else if (role == passengerSearchWord) {

            passengerCollection.readPassengerProperties(readingLine);

        }
    }


    fin.clear();
    fin.seekg(0, ios::beg);

/*populates the passengers and drivers with ride objects*/
    for (auto &currentRidePtr: rideCollection.rides) {
        Ride &currentRide = *currentRidePtr;

        for (auto &currentPassengerPtr: passengerCollection.passengers) {
            Passenger &currentPassenger = *currentPassengerPtr;

            if (currentRide.assignedPassengerId == currentPassenger.id) {
                currentPassenger.rides.push_back(&currentRide);
            }

        }
    }


    for (auto &currentRidePtr: rideCollection.rides) {
        Ride &currentRide = *currentRidePtr;

        for (auto &currentDriverPtr: driverCollection.drivers) {
            Driver &currentDriver = *currentDriverPtr;

            if (currentRide.assignedDriverId == currentDriver.id) {
                currentDriver.rides.push_back(&currentRide);
            }
        }
    }


    fin.close();


    while (true) {


        cout << "  ______            _        _            __ _   \n"
                " |  ____|          | |      | |          / _| |  \n"
                " | |__   __ _  __ _| | ___  | |    _   _| |_| |_ \n"
                " |  __| / _` |/ _` | |/ _ \\ | |   | | | |  _| __|\n"
                " | |___| (_| | (_| | |  __/ | |___| |_| | | | |_ \n"
                " |______\\__,_|\\__, |_|\\___| |______\\__, |_|  \\__|\n"
                "               __/ |                __/ |        \n"
                "              |___/                |___/         \n" << endl;

        cout << "*****************************" << endl;
        cout << "| ******* Main Menu ******* |" << endl;
        cout << "| ************************* |" << endl;
        cout << "| ** A. Login            ** |" << endl;
        cout << "| ** B. Add Driver       ** |" << endl;
        cout << "| ** C. Add Passenger    ** |" << endl;
        cout << "| ** D. Exit             ** |" << endl;
        cout << "| ************************* |" << endl;
        cout << "*****************************" << endl;


        cin >> option;

        switch (option) {
            case 'A':
            case 'a': // Login
                cout << "Enter password: ";
                cin >> enteredPassword;
                cin.ignore();


                for (auto &currentDriver: driverCollection.drivers) {
                    if (currentDriver->password == enteredPassword) {
                        DriverMenu(currentDriver, &rideCollection, driverCollection);
                        driverLoggedIn = true;
                        break;
                    }
                }

                if (!driverLoggedIn) {
                    bool passengerLoggedIn = false;
                    for (auto &currentPassenger: passengerCollection.passengers) {
                        if (currentPassenger->password == enteredPassword) {
                            PassengerMenu(currentPassenger, &rideCollection, passengerCollection);
                            passengerLoggedIn = true;
                            break;
                        }
                    }

                    if (!passengerLoggedIn) {
                        cout << "Incorrect password, try again." << endl;
                    }
                }
                break;


            case 'B':
            case 'b': // Add Driver

                driver = driverCollection.addDriver();
                DriverMenu(driver, &rideCollection, driverCollection);
                break;


            case 'c':
            case 'C'://Add Passenger

                passenger = passengerCollection.addPassenger();
                PassengerMenu(passenger, &rideCollection, passengerCollection);
                break;

            default:
                cout << "Not a valid input, please try again." << endl;
                break;


            case 'd':
            case 'D': // Exit
            {
                ofstream fout("RideShareData.dat");

                // Check if the file is successfully opened
                if (!fout) {
                    cerr << "Failed to open output file" << endl;
                    return 1;
                }

                for (Ride *currentRide : rideCollection.rides) {
                    cout << currentRide->pickupLocation << endl;
                    currentRide->writeRideProperties(fout);
                }
                rideCollection.rides.clear();

                fout << endl;

                for (Passenger *currentPassenger : passengerCollection.passengers) {
                    currentPassenger->writePassengerProperties(fout);
                }
                passengerCollection.passengers.clear();

                fout << endl << endl;

                for (Driver *currentDriverPtr : driverCollection.drivers) {
                    currentDriverPtr->writeDriverProperties(fout);
                }

                driverCollection.drivers.clear();


                fout << endl;

                fout.close();
                cout << "Goodbye" << endl;
                return 0;
            }



        }

    }
}
