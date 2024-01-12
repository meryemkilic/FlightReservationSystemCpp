#ifndef RESERVATION_H
#define RESERVATION_H

using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Flight.h"
#include "Person.h"

enum class TicketType
{
    ECONOMY,
    FIRST_CLASS
};

class Reservation
{
private:
    int reservationId;
    float constantPrice;
    Flight *flight;
    Passenger *passenger;
    TicketType ticketType;
    bool isCheckIn;
    bool isFlightFull;

public:
    Reservation(int reservationId, float constantPrice, Flight *flight, Passenger *passenger, TicketType ticketType,
                bool isCheckIn, bool isFlightFull);

    string ticketTypeToString(TicketType type) const
    {
        switch (type)
        {
        case TicketType::ECONOMY:
            return "Economy";
        case TicketType::FIRST_CLASS:
            return "First Class";
        default:
            return "Unknown Ticket Type";
        }
    }
    int getReservationId() const;
    float getConstantPrice() const;
    Flight *getFlight() const;
    Passenger *getPassenger() const;
    TicketType getTicketType() const;
    bool getIsCheckIn() const;
    bool getIsFlightFull() const;

    void setReservationId(int newReservationId);
    void setConstantPrice(float newConstantPrice);
    void setFlight(Flight *newFlight);
    void setPassenger(Passenger *newPassenger);
    void setTicketType(TicketType newTicketType);
    void setIsCheckIn(bool newIsCheckIn);
    void setIsFlightFull(bool newIsFlightFull);
};

class Ticket
{
private:
    int reservationId;
    float constantPrice;
    int flightId;
    int passengerId;
    string ticketType;
    string checkInStatus;
    string flightFullStatus;

public:
    Ticket(const Reservation &reservation)
        : reservationId(reservation.getReservationId()), constantPrice(reservation.getConstantPrice()),
          flightId(reservation.getFlight()->getFlightId()), passengerId(reservation.getPassenger()->getId()),
          ticketType(reservation.ticketTypeToString(reservation.getTicketType())),
          checkInStatus(reservation.getIsCheckIn() ? "Yes" : "No"),
          flightFullStatus(reservation.getIsFlightFull() ? "Yes" : "No") {}

    friend ostream &operator<<(ostream &os, const Ticket &ticket)
    {
        os << "Reservation ID: " << ticket.reservationId << '\n';
        os << "Price: " << fixed << setprecision(2) << ticket.constantPrice << '\n';
        os << "Flight ID: " << ticket.flightId << '\n';
        os << "Passenger ID: " << ticket.passengerId << '\n';
        os << "Ticket Type: " << ticket.ticketType << '\n';
        os << "Check-In: " << ticket.checkInStatus << '\n';
        os << "Flight Full: " << ticket.flightFullStatus << '\n';

        return os;
    }
};


extern vector<Reservation> reservations;
extern int reservationCount;

#endif