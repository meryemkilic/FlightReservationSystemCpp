#ifndef FILE_H
#define FILE_H

using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "Person.h.cpp"
#include "Flight.h.cpp"
#include "Reservation.h.cpp"

void createTicket(const Reservation *reservation);
void writeCustomerToFile();
void deleteCustomerFromFile();

void writeReservationsToFile();
void readReservationsFromFile(const char *RESERVATION_FILE, void (*processReservation)(const Reservation *), Customer *account);

void deleteReservationFromFile(int deletedReservationId);
void createTicket(const Reservation *reservation);

void writeFlightsToFile();
void deleteFlightFromFile(int deletedFlightId);


#endif