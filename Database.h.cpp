#ifndef DATABASE_H_CPP
#define DATABASE_H_CPP

#include "Person.h.cpp"
#include "Flight.h.cpp"
#include "Reservation.h.cpp"

Customer createCustomer(const string &username, const string &password, const string &name, const string &mail, const string &phone);
Passenger createPassenger(const string passengerId, const string name, Customer *customer, PassengerType passengerType);
Flight createFlight(const string &date, const string &time, const vector<int> &capacity, float baseFare, const string &departureCity, const string &arrivalCity,
                    AirlineCompany airlineCompany, bool isDelayed);

void deleteCustomer(int deletedCustomerId);
void deletePassenger(int deletedPassengerId);
void deleteFlight(int deletedFlightId);
bool updateFlight(Flight **flight, string *newDate, string *newTime);

int generateCustomerId();
int generatePassengerId();
int generateFlightId();

#endif