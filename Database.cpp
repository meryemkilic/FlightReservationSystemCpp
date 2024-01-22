#include <string>
#include <iostream>
#include <vector>
#include "File.cpp"
using namespace std;

#define GENERATE_CUSTOMER_ID() \
    ([]() { \
        static int lastCustomerId = 1000; \
        return ++lastCustomerId; })()

#define GENERATE_PASSENGER_ID() \
    ([]() { \
        static int lastPassengerId = 100; \
        return ++lastPassengerId; })()

#define GENERATE_FLIGHT_ID() \
    ([]() { \
        static int lastFlightId = 3000; \
        return ++lastFlightId; })()

#define GENERATE_RESERVATION_ID() \
    ([]() { \
        static int lastReservationId = 5000; \
        return ++lastReservationId; })()

float calculateReservationPrice(const Flight *flight, const Passenger *passenger, TicketType ticketType)
{
    float baseFare = flight->getBaseFare();

    if (passenger->getPassengerType() == PassengerType::ADULT)
    {
        baseFare *= 5.8;
    }

    if (ticketType == TicketType::FIRST_CLASS)
    {
        baseFare *= 9.2;
    }

    return baseFare;
}

bool isFlightCapacityFull(const Flight *flight)
{
    const int capacity = flight->getCapacity();

    if (capacity > 0)
    {
        return false;
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

Passenger *createPassenger(const string passengerId, const string name, Customer *customer, PassengerType passengerType, int flightId)
{
    for (const Reservation &reservation : reservations)
    {
        if (passengerId == reservation.getPassenger()->getPassengerId() && reservation.getFlight()->getFlightId() == flightId)
        {
            cout << "This flight has already been booked for this person. You cannot book the same flight a second time." << endl;
            return nullptr;
        }
    }

    int id = GENERATE_PASSENGER_ID();
    Passenger newPassenger(id, passengerId, name, customer, passengerType);
    passengers.push_back(newPassenger);
    passengerCount++;

    // Yeni yolcu başarıyla oluşturuldu, dolayısıyla bu noktaya ulaşıldığında fonksiyonun normal şekilde tamamlanması sağlanır.
    return &passengers.back(); // Eklenen son yolcu işaretçisi döndürülüyor.
}

Flight createFlight(const string &date, const string &time, const int capacity, float baseFare, const string &departureCity, const string &arrivalCity,
                    AirlineCompany airlineCompany, bool isDelayed)
{
    int id = GENERATE_FLIGHT_ID();
    Flight flight(id, date, time, capacity, baseFare, departureCity, arrivalCity, airlineCompany, isDelayed);
    flights.push_back(flight);
    flightCount++;
    return flight;
}

void createReservation(Flight *flight, Passenger *passenger, TicketType ticketType)
{
    if (isFlightCapacityFull(flight))
    {
        cout << "Reservation failed. The flight's capacity is full." << endl;
        return;
    }

    int id = GENERATE_RESERVATION_ID();
    float constantPrice = calculateReservationPrice(flight, passenger, ticketType);
    Reservation reservation(id, constantPrice, flight, passenger, ticketType, false, false);

    int updatedCapacity = flight->getCapacity();
    if (updatedCapacity > 0)
    {
        updatedCapacity--;
    }

    flight->setCapacity(updatedCapacity);

    reservations.push_back(reservation);
    reservationCount++;
}

void checkIn(int reservationId)
{
    int foundIndex = -1;

    for (int i = 0; i < reservationCount; i++)
    {
        if (reservations[i].getReservationId() == reservationId)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        cout << "Reservation with ID " << reservationId << " not found." << endl;
        return;
    }

    if (reservations[foundIndex].getIsCheckIn())
    {
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

void deleteReservation(int deletedReservationId)
{
    int foundIndex = -1;

    for (int i = 0; i < reservationCount; i++)
    {
        if (reservations[i].getReservationId() == deletedReservationId)
        {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1)
    {
        cout << "Reservation with ID " << deletedReservationId << " not found." << endl;
        return;
    }

    if (reservations[foundIndex].getIsCheckIn())
    {
        cout << "The reservation with ID " << deletedReservationId << " is already checked-in." << endl;

        char choice;
        cout << "Do you want to proceed with the deletion? (y/n): ";
        cin >> choice;

        if (choice != 'y' && choice != 'Y')
        {
            cout << "Deletion canceled. No changes made." << endl;
            return;
        }
    }

    Flight *associatedFlight = reservations[foundIndex].getFlight();
    associatedFlight->setCapacity(associatedFlight->getCapacity() + 1);

    Passenger *associatedPassenger = reservations[foundIndex].getPassenger();
    deletePassenger(associatedPassenger->getId());

    reservations.erase(reservations.begin() + foundIndex);
    reservationCount--;

    cout << "Reservation with ID " << deletedReservationId << " deleted successfully, and associated passenger deleted." << endl;
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
                deletedFlight->setIsDelayed(true);

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

void displayNotifications(const Customer *customerAccount, const vector<Reservation> &reservations, bool &hasNotification, int &trigger)
{
    cout << "\n----------       - Notifications -       ----------\n";

    for (const Reservation &reservation : reservations)
    {
        if ((reservation.getPassenger()->getCustomer() == customerAccount) && reservation.getFlight()->getIsDelayed())
        {
            hasNotification = true;
            if (trigger == 0)
            {
                cout << "You have a notification.\n";
            }
            else
            {
                cout << "You have existing notifications.\n";
            }
            cout << "Dear " << customerAccount->getName() << ",\nYour "
                 << reservation.getFlight()->getDepartureCity() << " - "
                 << reservation.getFlight()->getArrivalCity() << " flight number "
                 << reservation.getFlight()->getFlightId() << " was delayed.\n"
                 << "We are sorry for the delay, we wish you a pleasant flight!\n";

            trigger = 1;
            break;
        }
    }

    if (!hasNotification)
    {
        cout << "\nYou have no notifications.\n";
    }
}

void createTicket(const string &reservationsFilename, Customer *customer)
{
    vector<Reservation> myReservations = readReservationsFromFile(reservationsFilename, customer);

    for (const Reservation &res : reservations)
    {
        Ticket ticket(res);
        string ticketFilename = "ticket_" + to_string(res.getReservationId()) + ".txt";
        ofstream ticketFile(ticketFilename);

        if (!ticketFile.is_open())
        {
            cerr << "Error opening ticket file: " << ticketFilename << endl;
            continue;
        }

        ticketFile << ticket;
        ticketFile.close();

        cout << "Ticket written to file: " << ticketFilename << endl;
    }
}