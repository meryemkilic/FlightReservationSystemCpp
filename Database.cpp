#include "Database.h.cpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

#define GENERATE_CUSTOMER_ID() \
    ([]() { \
        static int lastCustomerId = 1000; \
        return ++lastCustomerId; \
    })()

#define GENERATE_PASSENGER_ID() \
    ([]() { \
        static int lastPassengerId = 100; \
        return ++lastPassengerId; \
    })()

#define GENERATE_FLIGHT_ID() \
    ([]() { \
        static int lastFlightId = 3000; \
        return ++lastFlightId; \
    })()

#define GENERATE_RESERVATION_ID() \
    ([]() { \
        static int lastReservationId = 5000; \
        return ++lastReservationId; \
    })()
    

float calculateReservationPrice(const Flight *flight, const Passenger *passenger, TicketType ticketType)
{
    float baseFare = flight->getBaseFare();

    if (passenger->getPassengerType() == PassengerType::CHILD)
    {
        baseFare *= 0.8;
    }

    if (ticketType == TicketType::FIRST_CLASS)
    {
        baseFare *= 1.2;
    }

    return baseFare;
}


bool isFlightCapacityFull(const Flight *flight)
{
    const vector<int> &capacity = flight->getCapacity();
    for (int seatsLeft : capacity)
    {
        if (seatsLeft > 0)
        {
            return false;
        }
    }
    return true;
}

Customer createCustomer(const string &username, const string &password, const string &name, const string &mail, const string &phone)
{
    int id = GENERATE_CUSTOMER_ID();
    Customer customer(id, username, password, name, mail, phone);
    customers.push_back(customer);
    customerCount++;
    return customer;
}

Passenger createPassenger(const string passengerId, const string name, Customer *customer, PassengerType passengerType)
{
    int id = GENERATE_PASSENGER_ID();
    Passenger passenger(id, passengerId, name, customer, passengerType);
    passengers.push_back(passenger);
    passengerCount++;
    return passenger;
}

Flight createFlight(const string &date, const string &time, const vector<int> &capacity, float baseFare, const string &departureCity, const string &arrivalCity,
                    AirlineCompany airlineCompany, bool isDelayed)
{
    int id = GENERATE_FLIGHT_ID();
    Flight flight(id, date, time, capacity, baseFare, departureCity, arrivalCity, airlineCompany, isDelayed);
    flights.push_back(flight);
    flightCount++;
    return flight;
}

void createReservation(Flight *flight, Passenger *passenger, TicketType ticketType,
                              bool isCheckIn, bool isFlightFull)
{
    if (isFlightCapacityFull(flight))
    {
        cout << "Reservation failed. The flight's capacity is full." << endl;
        return;
    }

    int id = GENERATE_RESERVATION_ID();
    float constantPrice = calculateReservationPrice(flight, passenger, ticketType);
    Reservation reservation(id, constantPrice, flight, passenger, ticketType, isCheckIn, isFlightFull);

    vector<int> updatedCapacity = flight->getCapacity();
    for (size_t i = 0; i < updatedCapacity.size(); ++i)
    {
        if (updatedCapacity[i] > 0)
        {
            updatedCapacity[i]--;
            break;
        }
    }
    flight->setCapacity(updatedCapacity);

    reservations.push_back(reservation);
    reservationCount++;
}

void checkIn(int reservationId) {
    int foundIndex = -1;

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].getReservationId() == reservationId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Reservation with ID " << reservationId << " not found." << endl;
        return;
    }

    if (reservations[foundIndex].getIsCheckIn()) {
        cout << "Reservation with ID " << reservationId << " is already checked in." << endl;
        return;
    }

    reservations[foundIndex].setIsCheckIn(true);

    cout << "Check-in for reservation with ID " << reservationId << " completed successfully." << endl;
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

void deleteReservation(int deletedReservationId) {
    int foundIndex = -1;

    for (int i = 0; i < reservationCount; i++) {
        if (reservations[i].getReservationId() == deletedReservationId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) {
        cout << "Reservation with ID " << deletedReservationId << " not found." << endl;
        return;
    }
if (reservations[foundIndex].getIsCheckIn()) {
        cout << "The reservation with ID " << deletedReservationId << " is already checked-in." << endl;

        char choice;
        cout << "Do you want to proceed with the deletion? (y/n): ";
        cin >> choice;

        if (choice != 'y' && choice != 'Y') {
            cout << "Deletion canceled. No changes made." << endl;
            return;
        }
    }

    Flight *associatedFlight = reservations[foundIndex].getFlight();
    vector<int> updatedCapacity = associatedFlight->getCapacity();
    for (size_t i = 0; i < updatedCapacity.size(); ++i) {
        updatedCapacity[i]++;
        break;
    }
    associatedFlight->setCapacity(updatedCapacity);

    Passenger *associatedPassenger = reservations[foundIndex].getPassenger();
    deletePassenger(associatedPassenger->getId());

    reservations.erase(reservations.begin() + foundIndex);
    reservationCount--;

    cout << "Reservation with ID " << deletedReservationId << " deleted successfully, and associated passenger deleted." << endl;
}

void deleteFlight(int deletedFlightId)
{
    int foundIndex = -1;

    for (int i = 0; i < flightCount; i++)
    {
        if (flights[i].getFlightId() == deletedFlightId)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        cout << "Flight with ID " << deletedFlightId << " not found." << endl;
        return;
    }

    Flight *deletedFlight = &flights[foundIndex];

    for (const Reservation &reservation : reservations)
    {
        if (reservation.getFlight() == deletedFlight && reservation.getIsCheckIn())
        {
            cout << "Cannot delete the flight with ID " << deletedFlightId
                 << " because there are passengers checked in." << endl;

            char choice;
            cout << "Do you want to delay the flight instead? (y/n): ";
            cin >> choice;

            if (choice == 'y' || choice == 'Y')
            {
                string newDate, newTime;
                cout << "Enter the new date for the delayed flight (YYYY-MM-DD): ";
                cin >> newDate;
                cout << "Enter the new time for the delayed flight (HH:mm): ";
                cin >> newTime;

                updateFlight(&deletedFlight, &newDate, &newTime);

                cout << "Flight delayed successfully." << endl;
                return;
            }
            else
            {
                cout << "Deletion canceled. No changes made." << endl;
                return;
            }
        }
    }

    for (int i = reservationCount - 1; i >= 0; i--)
    {
        if (reservations[i].getFlight() == deletedFlight)
        {
            reservations.erase(reservations.begin() + i);
            reservationCount--;
        }
    }

    flights.erase(flights.begin() + foundIndex);
    flightCount--;

    cout << "Flight with ID " << deletedFlightId << " deleted successfully." << endl;
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
