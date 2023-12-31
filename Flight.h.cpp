#ifndef FLIGHT_H
#define FLIGHT_H

using namespace std;
#include <string>
#include <iostream>
#include <vector>

enum class AirlineCompany
{
    PEGASUS,
    TURKISH_AIRLINES,
    ANADOLU_JET
};

class Flight
{

private:
    int flightId;
    string date;
    string time;
    vector<int> capacity;
    float baseFare;
    string departureCity;
    string arrivalCity;
    AirlineCompany airlineCompany;
    bool isDelayed;

public:
    Flight(int flightId, const string &date, const string &time, const vector<int> &capacity,
           float baseFare, const string &departureCity, const string &arrivalCity,
           AirlineCompany airlineCompany, bool isDelayed);

    // Getter functions
    int getFlightId() const;
    string getDate() const;
    string getTime() const;
    const vector<int> &getCapacity() const;
    float getBaseFare() const;
    string getDepartureCity() const;
    string getArrivalCity() const;
    AirlineCompany getAirlineCompany() const;
    bool getIsDelayed() const;

    // Setter functions
    void setFlightId(int newFlightId);
    void setDate(const string &newDate);
    void setTime(const string &newTime);
    void setCapacity(const vector<int> &newCapacity);
    void setBaseFare(float newBaseFare);
    void setDepartureCity(const string &newDepartureCity);
    void setArrivalCity(const string &newArrivalCity);
    void setAirlineCompany(AirlineCompany newAirlineCompany);
    void setIsDelayed(bool newIsDelayed);
};

extern vector<Flight> flights;
extern int flightCount;
#endif