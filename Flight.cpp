#include "Reservation.h.cpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<Flight> flights;
int flightCount = 0;

Flight::Flight(int flightId, const string &date, const string &time, const vector<int> &capacity,
               float baseFare, const string &departureCity, const string &arrivalCity,
               AirlineCompany airlineCompany, bool isDelayed)
    : flightId(flightId), date(date), time(time), capacity(capacity), baseFare(baseFare),
      departureCity(departureCity), arrivalCity(arrivalCity), airlineCompany(airlineCompany),
      isDelayed(isDelayed)
{
}

// Getter functions
int Flight::getFlightId() const
{
    return flightId;
}

string Flight::getDate() const
{
    return date;
}

string Flight::getTime() const
{
    return time;
}

const vector<int> &Flight::getCapacity() const
{
    return capacity;
}

float Flight::getBaseFare() const
{
    return baseFare;
}

string Flight::getDepartureCity() const
{
    return departureCity;
}

string Flight::getArrivalCity() const
{
    return arrivalCity;
}

AirlineCompany Flight::getAirlineCompany() const
{
    return airlineCompany;
}

bool Flight::getIsDelayed() const
{
    return isDelayed;
}

// Setter functions
void Flight::setFlightId(int newFlightId)
{
    flightId = newFlightId;
}

void Flight::setDate(const string &newDate)
{
    date = newDate;
}

void Flight::setTime(const string &newTime)
{
    time = newTime;
}

void Flight::setCapacity(const vector<int> &newCapacity)
{
    capacity = newCapacity;
}

void Flight::setBaseFare(float newBaseFare)
{
    baseFare = newBaseFare;
}

void Flight::setDepartureCity(const string &newDepartureCity)
{
    departureCity = newDepartureCity;
}

void Flight::setArrivalCity(const string &newArrivalCity)
{
    arrivalCity = newArrivalCity;
}

void Flight::setAirlineCompany(AirlineCompany newAirlineCompany)
{
    airlineCompany = newAirlineCompany;
}

void Flight::setIsDelayed(bool newIsDelayed)
{
    isDelayed = newIsDelayed;
}