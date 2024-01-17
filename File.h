#ifndef FILE_H
#define FILE_H

using namespace std;
#include "Person.h"
#include "Flight.h"
#include "Reservation.h"

void createTicket(const Reservation *reservation);

void writeCustomersToFile();
void writeReservationsToFile();
void writeFlightsToFile();

void deleteReservationFromFile(int deletedReservationId);
void deleteFlightFromFile(int deletedFlightId);

Flight* findFlightById(int selectedFlight);
Passenger* findPassengerById(int selectedPassenger);
Reservation* findReservationById(int selectedreservationId);
void readReservationsFromFile(const string &filename, void (*processReservation)(const Reservation *), const Customer *customerAccount);


#endif