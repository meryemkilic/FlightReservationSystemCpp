#ifndef DATABASE_H
#define DATABASE_H

#include "Person.h"
#include "Flight.h"
#include "Reservation.h"

Customer createCustomer(const string &username, const string &password, const string &name, const string &mail, const string &phone);
Passenger createPassenger(const string passengerId, const string name, Customer *customer, PassengerType passengerType, const int flightId);
Flight createFlight(const string &date, const string &time, const int capacity, float baseFare, const string &departureCity, const string &arrivalCity,
                    AirlineCompany airlineCompany, bool isDelayed);
void createReservation(Flight *flight, Passenger *passenger, TicketType ticketType);

bool isFlightCapacityFull(const Flight *flight);
void deleteCustomer(int deletedCustomerId);
void deletePassenger(int deletedPassengerId);
void deleteFlight(int deletedFlightId);
void deleteReservation(int deletedReservationId);
bool updateFlight(Flight **flight, string *newDate, string *newTime);
float calculateReservationPrice(const Flight *flight, const Passenger *passenger, TicketType ticketType);

#endif