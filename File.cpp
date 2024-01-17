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

void createTicket(const Reservation *reservation)
{
    if (!reservation)
    {
        cerr << "Invalid reservation\n";
        return;
    }

    ostringstream filenameStream;
    filenameStream << "ticket_" << reservation->getReservationId() << ".txt";
    string filename = filenameStream.str();

    ofstream file(filename);
    if (!file.is_open())
    {
        cerr << "Error opening ticket file" << endl;
        return;
    }

    file << "Reservation ID: " << reservation->getReservationId() << '\n';
    file << "Price: " << fixed << setprecision(2) << reservation->getConstantPrice() << '\n';
    file << "Flight ID: " << reservation->getFlight()->getFlightId() << '\n';
    file << "Passenger ID: " << reservation->getPassenger()->getId() << '\n';
    file << "Ticket Type: " << reservation->ticketTypeToString(reservation->getTicketType()) << '\n';
    file << "Check-In: " << (reservation->getIsCheckIn() ? "Yes" : "No") << '\n';
    file << "Flight Full: " << (reservation->getIsFlightFull() ? "Yes" : "No") << '\n';

    cout << "Ticket created for Reservation ID " << reservation->getReservationId() << endl;
    cout << "Ticket created successfully. Download the " << filename << " file.\n";
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

void readReservationsFromFile(const std::string &filename, void (*processReservation)(const Reservation *), const Customer *customerAccount)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening reservation file" << std::endl;
        return;
    }

    int reservationId, passengerId, flightId;
    std::string passengerName, departureCity, arrivalCity, ticketTypeStr;
    float constantPrice;
    bool isCheckIn;
    Passenger *passenger;
    Flight *flight;

    while (file >> reservationId >> passengerId >> passengerName >> flightId >> departureCity >> arrivalCity >> constantPrice >> ticketTypeStr >> isCheckIn)
    {
        TicketType ticketType;
        if (ticketTypeStr == "Economy")
        {
            ticketType = TicketType::ECONOMY;
        }
        else if (ticketTypeStr == "First Class")
        {
            ticketType = TicketType::FIRST_CLASS;
        }
        else
        {
            std::cerr << "Unknown ticket type: " << ticketTypeStr << std::endl;
            continue;
        }

        passenger = findPassengerById(passengerId);
        flight = findFlightById(flightId);

        if (!passenger || !flight)
        {
            std::cerr << "Invalid passenger or flight ID" << std::endl;
            continue;
        }

        if (passenger->getCustomer() == customerAccount)
        {
            Reservation reservation(reservationId, constantPrice, flight, passenger, ticketType, isCheckIn, false);

            processReservation(&reservation);
        }
    }

    file.close();
}

void createTicketFile(const Customer *customerAccount)
{

    for (Reservation reservation : reservations)
    {
        if (reservation.getPassenger()->getCustomer() == customerAccount)
        {
            Ticket newTicket(reservation);
            string filename = "ticket_" + to_string(reservation.getReservationId()) + ".txt";
            ofstream outputFile(filename);
            if (outputFile.is_open())
            {
                outputFile << newTicket;
                cout << "Ticket information has been written to " << filename << endl;
                outputFile.close();
            }
            else
            {
                cerr << "Unable to open the file." << endl;
            }
        }
    }
}
