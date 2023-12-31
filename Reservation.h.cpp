#ifndef RESERVATION_H
#define RESERVATION_H

using namespace std;
#include <string>
#include <iostream>
#include <vector>
#include "Flight.h.cpp"
#include "Person.h.cpp"

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

extern vector<Reservation> reservations;
extern int reservationCount;

#endif