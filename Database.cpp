#include "Database.h.cpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

int generateCustomerId()
{
    static int lastCustomerId = 1000;
    return ++lastCustomerId;
}

int generatePassengerId()
{
    static int lastPassengerId = 100;
    return ++lastPassengerId;
}

int generateFlightId()
{
    static int lastFlightId = 3000;
    return ++lastFlightId;
}

Customer createCustomer(const string &username, const string &password, const string &name, const string &mail, const string &phone)
{
    int id = generateCustomerId();
    Customer customer(id, username, password, name, mail, phone);
    customers.push_back(customer);
    customerCount++;
    return customer;
}

Passenger createPassenger(const string passengerId, const string name, Customer *customer, PassengerType passengerType)
{
    int id = generatePassengerId();
    Passenger passenger(id, passengerId, name, customer, passengerType);
    passengers.push_back(passenger);
    passengerCount++;
    return passenger;
}

Flight createFlight(const string &date, const string &time, const vector<int> &capacity, float baseFare, const string &departureCity, const string &arrivalCity,
                    AirlineCompany airlineCompany, bool isDelayed)
{
    int id = generateFlightId();
    Flight flight(id, date, time, capacity, baseFare, departureCity, arrivalCity, airlineCompany, isDelayed);
    flights.push_back(flight);
    flightCount++;
    return flight;
}

void deletePassenger(int deletedPassengerId)
{
    int foundIndex = -1;

    for (int i = 0; i < passengerCount; i++)
    {
        if (passengers[i].getId() == deletedPassengerId)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        cout << "Passenger with ID " << deletedPassengerId << " not found." << endl;
        return;
    }

    passengers.erase(passengers.begin() + foundIndex);
    passengerCount--;

    cout << "Passenger with ID " << deletedPassengerId << " deleted successfully." << endl;
}

void deleteCustomer(int deletedCustomerId)
{
    int foundIndex = -1;
    for (int i = 0; i < customerCount; i++)
    {
        if (customers[i].getId() == deletedCustomerId)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        cout << "Customer with ID " << deletedCustomerId << " not found." << endl;
        return;
    }

    customers.erase(customers.begin() + foundIndex);
    customerCount--;

    cout << "Customer with ID " << deletedCustomerId << " deleted successfully." << endl;

    for (int i = passengerCount - 1; i >= 0; i--)
    {
        if (passengers[i].getCustomer()->getId() == deletedCustomerId)
        {
            deletePassenger(passengers[i].getId());
        }
    }
}

bool updateFlight(Flight **flight, string *newDate, string *newTime)
{
    if (flight == nullptr || *flight == nullptr || newDate == nullptr || newTime == nullptr)
    {
        return false;
    }
    
    (*flight)->setDate(*newDate);
    (*flight)->setTime(*newTime);

    return true;
}
