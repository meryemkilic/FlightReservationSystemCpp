#include "Reservation.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<Reservation> reservations;
int reservationCount = 0;

Reservation::Reservation(int reservationId, float constantPrice, Flight *flight, Passenger *passenger, TicketType ticketType,
                         bool isCheckIn, bool isFlightFull)
    : reservationId(reservationId), constantPrice(constantPrice), flight(flight), passenger(passenger),
      ticketType(ticketType), isCheckIn(isCheckIn), isFlightFull(isFlightFull)
{
}

Reservation::Reservation() : reservationId(0), constantPrice(0), flight(nullptr), passenger(nullptr), ticketType(), isCheckIn(false), isFlightFull(false) {}

int Reservation::getReservationId() const
{
    return reservationId;
}

float Reservation::getConstantPrice() const
{
    return constantPrice;
}

Flight *Reservation::getFlight() const
{
    return flight;
}

Passenger *Reservation::getPassenger() const
{
    return passenger;
}

TicketType Reservation::getTicketType() const
{
    return ticketType;
}

bool Reservation::getIsCheckIn() const
{
    return isCheckIn;
}

bool Reservation::getIsFlightFull() const
{
    return isFlightFull;
}

void Reservation::setReservationId(int newReservationId)
{
    reservationId = newReservationId;
}

void Reservation::setConstantPrice(float newConstantPrice)
{
    constantPrice = newConstantPrice;
}

void Reservation::setFlight(Flight *newFlight)
{
    flight = newFlight;
}

void Reservation::setPassenger(Passenger *newPassenger)
{
    passenger = newPassenger;
}

void Reservation::setTicketType(TicketType newTicketType)
{
    ticketType = newTicketType;
}

void Reservation::setIsCheckIn(bool newIsCheckIn)
{
    isCheckIn = newIsCheckIn;
}

void Reservation::setIsFlightFull(bool newIsFlightFull)
{
    isFlightFull = newIsFlightFull;
}
