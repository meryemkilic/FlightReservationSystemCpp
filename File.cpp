#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

#include "Flight.cpp"
#include "Person.cpp"
#include "Reservation.cpp"

const char *PASSENGER_FILE = "passengers.txt";
const char *CUSTOMER_FILE = "customers.txt";
const char *RESERVATION_FILE = "reservations.txt";
const char *FLIGHT_FILE = "flights.txt";

Flight *findFlightById(int selectedFlight)
{
    for (Flight &flight : flights)
    {
        if (flight.getFlightId() == selectedFlight)
        {
            return &flight;
        }
    }
    cout << "\nFlight not found.\n"
         << endl;
    return nullptr;
}

Passenger *findPassengerById(int selectedPassenger)
{
    for (Passenger &passenger : passengers)
    {
        if (passenger.getId() == selectedPassenger)
        {
            return &passenger;
        }
    }
    cout << "\nPassenger not found.\n"
         << endl;
    return nullptr;
}

Reservation *findReservationById(int selectedreservationId)
{
    for (Reservation &reservation : reservations)
    {
        if (reservation.getReservationId() == selectedreservationId)
        {
            return &reservation;
        }
    }
    cout << "\nReservation not found.\n"
         << endl;
    return nullptr;
}
 
void writeCustomersToFile()
{

    ofstream file(CUSTOMER_FILE);
    if (!file.is_open())
    {
        cerr << "Error opening customers file" << endl;
        return;
    }
    for (const Customer &customer : customers)
    {
        file << customer.getUsername() << ' ' << customer.getPassword() << ' ' << customer.getId() << ' '
             << customer.getName() << ' ' << customer.getMail() << ' ' << customer.getPhone() << ' '
             << customer.getIsManager() << '\n';
    }

    cout << "Customers written to file successfully." << endl;
}

void writeFlightsToFile()
{
    ofstream file(FLIGHT_FILE);
    if (!file.is_open())
    {
        cerr << "Error opening flights file" << endl;
        return;
    }

    for (const Flight &flight : flights)
    {
        file << flight.getFlightId() << ' ' << flight.getDepartureCity() << ' ' << flight.getArrivalCity() << ' ' << flight.getDate() << ' ' << flight.getTime()
             << ' ' << flight.getBaseFare() << ' ' << flight.airlineToString(flight.getAirlineCompany()) << ' ' << flight.getIsDelayed() << '\n';
    }
    cout << "Flights written to file successfully." << endl;
}

void writeReservationsToFile()
{
    ofstream file(RESERVATION_FILE);
    if (!file.is_open())
    {
        cerr << "Error opening reservations file" << endl;
        return;
    }
    for (const Reservation &reservation : reservations)
    {
        file << reservation.getReservationId() << ' ' << reservation.getPassenger()->getId() << ' ' << reservation.getPassenger()->getName() << ' ' << reservation.getFlight()->getFlightId() << ' '
             << reservation.getFlight()->getDepartureCity() << ' ' << reservation.getFlight()->getArrivalCity() << ' ' << reservation.getConstantPrice()
             << ' ' << reservation.ticketTypeToString(reservation.getTicketType()) << ' ' << reservation.getIsCheckIn() << '\n';
    }

    cout << "Reservations written to file successfully." << endl;
}

vector<Reservation> readReservationsFromFile(const string &filename, Customer *c)
{
    vector<Reservation> matchedReservations;
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Openning File Error!" << endl;
        return matchedReservations;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        int reservationId, passengerId, flightId;
        string passengerName, departureCity, arrivalCity, ticketTypeStr;
        float constantPrice;
        bool isCheckIn;

        ss >> reservationId >> passengerId >> passengerName >> flightId >> departureCity >> arrivalCity >> constantPrice >> ticketTypeStr >> isCheckIn;

        Reservation *res = findReservationById(reservationId);
        if (res != nullptr && res->getPassenger()->getCustomer()->getId() == c->getId())
        {
            matchedReservations.push_back(*res);
        }
    }

    file.close();
    return matchedReservations;
}
