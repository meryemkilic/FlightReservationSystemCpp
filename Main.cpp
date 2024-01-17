#include "Database.cpp"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <typeinfo>

using namespace std;

Manager manager(1, "manager", "123");
Person *login()
{
    cout << "\n    - Welcome to Flight Reservation System! -\n";
    cout << "\n------------   - User Login -   ------------\n";

    string enteredUsername;
    string enteredPassword;

    cout << "\nPlease enter your username: ";
    cin >> enteredUsername;

    cout << "Please enter your password: ";
    cin >> enteredPassword;
    if (enteredUsername == "manager" && enteredPassword == "123")
    {
        cout << "\nLogin successful!\n";
        return &manager;
    }

    for (Customer &customer : customers)
    {
        if (enteredUsername == customer.getUsername() && enteredPassword == customer.getPassword())
        {
            cout << "\nLogin successful!\n";
            return &customer;
        }
    }

    cout << "\nLogin failed. Invalid username or password.\n";
    return nullptr;
}

int main()
{
    Person *account = nullptr;
    Customer *customerAccount = nullptr;
    PassengerType passengerType;
    AirlineCompany airlineCompany;

    createCustomer("meryem", "123", "meryem", "meryem@gmail.com", "987654321");
    createFlight("20.01.2024", "12:00", {100}, 500.0, "Istanbul", "Ankara", AirlineCompany::PEGASUS, false);
    createFlight("20.01.2024", "12:00", {100}, 600.0, "Istanbul", "Ankara", AirlineCompany::TURKISH_AIRLINES, false);
    createFlight("20.01.2024", "12:00", {100}, 400.0, "Istanbul", "Ankara", AirlineCompany::ANADOLU_JET, false);

    writeCustomersToFile();
    writeFlightsToFile();
    writeReservationsToFile();
    Passenger *p;
    string username;
    string password;
    string name;
    string surname;
    string email;
    string phone;
    string date;
    string time;
    int flightId;
    int passengerId;
    int customerId;
    int passengerTypeInt;
    int option;
    int capacity;
    float baseFare;
    int resCount = 1;
    int isLoggedIn = 0;
    string pId;
    string departureCity;
    string arrivalCity;
    string airlineComp;
    string addDelay;
    string checkIn;
    string cardNumber;
    string expirationDate;
    string cvv;
    string payment;
    int aircomp;
    int countCase2 = 0;
    int selected;
    int reservationId;
    TicketType ticketType;
    Passenger *selectedPassenger = nullptr;
    Flight *selectedFlight = nullptr;
    Flight *updatedFlight = nullptr;
    Flight *delayedFlight = nullptr;
    Reservation *reservation = nullptr;
    bool hasNotification = false;
    Flight *f;
    int choice;
    int trigger = 0;

    int index;
    while (true)
    {
        if (account == nullptr)
        {
            cout << "\n------------------- Welcome to Flight Reservation System! -------------------\n";
            cout << "Please select the action you want to perform:\n";
            cout << "  1- Login\n";
            cout << "  2- Exit\n";

            int loginChoice;
            cin >> loginChoice;

            if (loginChoice == 1)
            {
                account = login();
            }
            else if (loginChoice == 2)
            {
                cout << "Exiting the system. Goodbye!\n";
                break;
            }
            else
            {
                cout << "Invalid choice. Please try again.\n";
            }
        }
        else if (account->getIsManager())
        {
            cout << "\n-----------------     - Hello Manager! -     -----------------\n";

            cout << "Please select the action you want to perform.\n";
            cout << "\n    1-  Press 1 to create a new flight.   ";
            cout << "\n    2-  Press 2 to create a new customer.   ";
            cout << "\n    3-  Press 3 to create a new reservation.   ";
            cout << "\n    4-  Press 4 to delete a flight.   ";
            cout << "\n    5-  Press 5 to delete a customer.   ";
            cout << "\n    6-  Press 6 to delete a reservation.   ";
            cout << "\n    7-  Press 7 to update a flight.   ";
            cout << "\n    8-  Press 8 to add delay to a flight.   ";
            cout << "\n    9-  Press 9 to view all flights.   ";
            cout << "\n    10- Press 10 to view all reservations.   ";
            cout << "\n    11- Logout\n";

            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "\n----------       - Flight Creation Process -       ----------\n";
                cout << "Please enter flight's information.\n";
                cout << "Please enter the flight's date:   ";
                cin >> date;
                cout << "Please enter flight's time:   ";
                cin >> time;
                cout << "Please enter flight's capacity:   ";
                cin >> capacity;
                cout << "Please enter flight's base fare:   ";
                cin >> baseFare;
                cout << "Please enter departure city:   ";
                cin >> departureCity;
                cout << "Please enter arrival city:   ";
                cin >> arrivalCity;
                cout << "Please choose an Airline Company: (0: Pegasus, 1: Turkish Airlines, 2: Anadolu Jet)   ";
                cin >> aircomp;
                switch (aircomp)
                {
                case 0:
                    airlineCompany = AirlineCompany::PEGASUS;
                    break;
                case 1:
                    airlineCompany = AirlineCompany::TURKISH_AIRLINES;
                    break;
                case 2:
                    airlineCompany = AirlineCompany::ANADOLU_JET;
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;
                }
                createFlight(date, time, {capacity}, baseFare, departureCity, arrivalCity, airlineCompany, false);

                writeFlightsToFile();
                cout << "\nFlight created successfully!\n";
                break;

            case 2:
                cout << "\n----------       - Customer Creation Process -       ----------\n";
                cout << "Please enter customer's information.\n";
                cout << "Please enter customer's username:   ";
                cin >> username;
                cout << "Please enter customer's password:   ";
                cin >> password;
                cout << "Please enter customer's name:   ";
                cin >> name;
                cout << "Please enter customer's email:   ";
                cin >> email;
                cout << "Please enter customer's phone:   ";
                cin >> phone;
                createCustomer(username, password, name, email, phone);
                writeCustomersToFile();
                cout << "\nCustomer created successfully!\n";
                break;

            case 3:
                cout << "\n----------       - Reservation Creation Process -       ----------\n";
                cout << "Please enter reservation's information:\n";
                cout << "Please enter the flight ID for reservation:   ";
                cin >> flightId;
                for (Flight &flight : flights)
                {
                    if (flightId == flight.getFlightId())
                    {
                        selectedFlight = &flight;
                        break;
                    }
                }
                if (selectedFlight != nullptr)
                {
                    cout << "Please enter the passenger ID for reservation:   ";
                    cin >> index;

                    for (Passenger p : passengers)
                    {
                        if (index == p.getId())
                        {
                            selectedPassenger = &p;
                            break;
                        }
                    }

                    if (selectedPassenger != nullptr)
                    {
                        do
                        {
                            cout << "Please choose the ticket type (0: Economy, 1: First Class): ";
                            cin >> option;
                        } while (option < 0 || option > 1);
                        ticketType = (option == 0) ? TicketType::ECONOMY : TicketType::FIRST_CLASS;
                        createReservation(selectedFlight, selectedPassenger, ticketType);
                        writeReservationsToFile();
                        cout << "\nReservation created successfully!\n";
                        break;
                    }
                    else
                    {
                        cout << "\nPassenger not found!\n";
                        break;
                    }
                }
                else
                {
                    cout << "\nFlight not found!\n";
                    break;
                }
                break;

            case 4:
                cout << "\n----------       - Flight Deletion Process -       ----------\n";
                cout << "\nList of all flights:\n";
                for (const Flight &flight : flights)
                {
                    cout << "\nFlight ID: " << flight.getFlightId() << '\n';
                    cout << "Date: " << flight.getDate() << '\n';
                    cout << "Time: " << flight.getTime() << '\n';
                    cout << "Capacity: " << flight.getCapacity() << '\n';
                    cout << "Base Fare: " << flight.getBaseFare() << '\n';
                    cout << "Departure City: " << flight.getDepartureCity() << '\n';
                    cout << "Arrival City: " << flight.getArrivalCity() << '\n';
                    cout << "Airline Company: " << flight.airlineToString(flight.getAirlineCompany()) << '\n';
                    cout << "Is Delayed: " << (flight.getIsDelayed() ? "Yes" : "No") << '\n';
                }
                cout << "\n\nPlease enter the flight ID to delete:   ";
                cin >> flightId;
                deleteFlight(flightId);
                writeFlightsToFile();
                break;

            case 5:
                cout << "\n----------       - Customer Deletion Process -       ----------\n";
                cout << "\nList of all customers:\n";
                for (const Customer &customer : customers)
                {
                    cout << "Customer ID: " << customer.getId() << '\n';
                    cout << "Customer name: " << customer.getName() << '\n';
                    cout << "\n----------\n";
                }
                cout << "\n\nPlease enter the customer ID to delete:   ";
                cin >> customerId;

                deleteCustomer(customerId);
                writeCustomersToFile();
                break;

            case 6:
                cout << "\n----------       - Reservation Deletion Process -       ----------\n";
                if (!reservations.empty())
                {
                    cout << "\nList of all reservations:\n";
                    for (const Reservation &reservation : reservations)
                    {
                        cout << "Reservation ID: " << reservation.getReservationId() << '\n';
                        cout << "Passenger name: " << reservation.getPassenger()->getName() << '\n';
                        cout << "Flight Informations:\nFlight Id: " << reservation.getFlight()->getFlightId() << "     Flight's route: " << reservation.getFlight()->getDepartureCity() << " - " << reservation.getFlight()->getArrivalCity();
                        cout << "\n--------------------------\n";
                    }
                    cout << "\n\nPlease enter the reservation ID to delete:   ";
                    cin >> index;
                    deleteReservation(index);
                    writeReservationsToFile();
                    break;
                }
                else
                {
                    cout << "\nThere are no reservation.\n";
                    break;
                }

            case 7:
                cout << "\n----------       - Flight Update Process -       ----------\n";
                cout << "Please enter the flight ID to update:   ";
                cin >> flightId;
                updatedFlight = findFlightById(flightId);
                if (updatedFlight == nullptr)
                {
                    cout << "\nFlight not found!\n";
                    break;
                }
                cout << "Please enter the new date for the flight:   ";
                cin >> date;
                cout << "Please enter the new time for the flight:   ";
                cin >> time;

                if (updateFlight(&updatedFlight, &date, &time))
                {
                    writeFlightsToFile();
                    cout << "\nFlight updated successfully!\n";
                }
                else
                {
                    cout << "\nFlight update failed!\n";
                }
                break;

            case 8:
                cout << "\n----------       - Add Delay to Flight Process -       ----------\n";
                cout << "Please enter the flight ID to add delay:   ";
                cin >> flightId;
                delayedFlight = findFlightById(flightId);
                if (delayedFlight == nullptr)
                {
                    cout << "\nFlight not found!\n";
                    break;
                }
                delayedFlight->setIsDelayed(true);
                writeFlightsToFile();
                cout << "\nDelay added to the flight successfully!\n";
                break;

            case 9:
                cout << "\n----------       - View All Flights -       ----------\n";
                if (flightCount == 0)
                {
                    cout << "\nNo flights available.\n";
                }
                else
                {
                    cout << "\nList of all flights:\n";
                    for (const Flight &flight : flights)
                    {
                        cout << "\nFlight ID: " << flight.getFlightId() << '\n';
                        cout << "Date: " << flight.getDate() << '\n';
                        cout << "Time: " << flight.getTime() << '\n';
                        cout << "Capacity: " << flight.getCapacity() << '\n';
                        cout << "Base Fare: " << flight.getBaseFare() << '\n';
                        cout << "Departure City: " << flight.getDepartureCity() << '\n';
                        cout << "Arrival City: " << flight.getArrivalCity() << '\n';
                        cout << "Airline Company: " << flight.airlineToString(flight.getAirlineCompany()) << '\n';
                        cout << "Is Delayed: " << (flight.getIsDelayed() ? "Yes" : "No") << '\n';
                        cout << "\n--------------------------\n";
                    }
                }
                break;

            case 10:
                cout << "\n----------       - View All Reservations -       ----------\n";
                if (reservationCount == 0)
                {
                    cout << "\nNo reservations available.\n";
                }
                else
                {
                    cout << "\nList of all reservations:\n";
                    for (const Reservation &reservation : reservations)
                    {
                        cout << "\nReservation ID: " << reservation.getReservationId() << '\n';
                        cout << "Price: " << reservation.getConstantPrice() << '\n';
                        cout << "Flight ID: " << reservation.getFlight()->getFlightId() << '\n';
                        cout << "Passenger ID: " << reservation.getPassenger()->getId() << '\n';
                        cout << "Ticket Type: " << reservation.ticketTypeToString(reservation.getTicketType()) << '\n';
                        cout << "Check-In: " << (reservation.getIsCheckIn() ? "Yes" : "No") << '\n';
                        cout << "Flight Full: " << (reservation.getIsFlightFull() ? "Yes" : "No") << '\n';
                        cout << "\n--------------------------\n";
                    }
                }
                break;

            case 11:
                cout << "Logging out...\n";
                account = nullptr;
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
            }
        }
        else if (!account->getIsManager())
        {
            if (account->isCustomer())
            {
                customerAccount = dynamic_cast<Customer *>(account);
            }
            cout << "\n------------------- Hello " << customerAccount->getName() << "! -------------------\n";
            cout << "Please select the action you want to perform:\n";
            cout << "  1- View all flights\n";
            cout << "  2- View my reservations\n";
            cout << "  3- Create a new reservation\n";
            cout << "  4- Cancel a reservation\n";
            cout << "  5- Check-In\n";
            cout << "  6- Download my e-ticket\n";
            cout << "  7- Notifications\n";
            cout << "  8- Logout\n";

            cin >> choice;

            switch (choice)
            {
            case 1:
                if (flightCount == 0)
                {
                    cout << "\nNo flights available.\n";
                }
                else
                {
                    cout << "\nList of all flights:\n";
                    for (const Flight &flight : flights)
                    {
                        cout << "\nFlight ID: " << flight.getFlightId() << '\n';
                        cout << "Date: " << flight.getDate() << '\n';
                        cout << "Time: " << flight.getTime() << '\n';
                        cout << "Capacity: " << flight.getCapacity() << '\n';
                        cout << "Base Fare: " << flight.getBaseFare() << '\n';
                        cout << "Departure City: " << flight.getDepartureCity() << '\n';
                        cout << "Arrival City: " << flight.getArrivalCity() << '\n';
                        cout << "Airline Company: " << flight.airlineToString(flight.getAirlineCompany()) << '\n';
                        cout << "Is Delayed: " << (flight.getIsDelayed() ? "Yes" : "No") << '\n';
                        cout << "\n--------------------------\n";
                    }
                }
                break;
            case 2:

                for (const Reservation &reservation : reservations)
                {
                    if (reservation.getPassenger()->getCustomer() == customerAccount)
                    {
                        countCase2++;
                        cout << "\nReservation ID: " << reservation.getReservationId() << '\n';
                        cout << "Price: " << reservation.getConstantPrice() << '\n';
                        cout << "Flight ID: " << reservation.getFlight()->getFlightId() << '\n';
                        cout << "Ticket Type: " << reservation.ticketTypeToString(reservation.getTicketType()) << '\n';
                        cout << "Check-In: " << (reservation.getIsCheckIn() ? "Yes" : "No") << '\n';
                        cout << "Flight Full: " << (reservation.getIsFlightFull() ? "Yes" : "No") << '\n';
                        cout << "\n--------------------------\n";
                    }
                }
                if (countCase2 == 0)
                {
                    cout << "\nYou have no reservations.\n";
                }
                break;

            case 3:

                cout << "\n----------       - Reservation Creation Process -       ----------\n";
                cout << "Please enter the flight ID for reservation:   ";
                cin >> flightId;
                // selectedFlight = findFlightById(flightId);
                if (findFlightById(flightId) == nullptr)
                {
                    cout << "\nFlight not found!\n";
                    break;
                }

                cout << "Please enter the passenger information:\n";
                cout << "Passenger ID: ";
                cin >> pId;

                cout << "Passenger Name: ";
                cin >> name;

                do
                {
                    cout << "Passenger Type (0: ADULT, 1: CHILD): ";
                    cin >> passengerTypeInt;
                } while (passengerTypeInt < 0 || passengerTypeInt > 1);

                passengerType = (passengerTypeInt == 0) ? PassengerType::ADULT : PassengerType::CHILD;

                p = createPassenger(pId, name, customerAccount, passengerType, flightId);
                if (p != nullptr)
                {
                    do
                    {
                        cout << "Please choose the ticket type (0: Economy, 1: First Class): ";
                        cin >> selected;
                    } while (selected < 0 || selected > 1);
                    ticketType = (selected == 0) ? TicketType::ECONOMY : TicketType::FIRST_CLASS;

                    createReservation(findFlightById(flightId), p, ticketType);

                    cout << "\n----------       - Payment Information -       ----------\n";
                    cout << "Card Number: ";
                    cin >> cardNumber;
                    cout << "Expiration Date (MM/YYYY): ";
                    cin >> expirationDate;
                    cout << "CVV: ";
                    cin >> cvv;

                    for (const Reservation &reservation : reservations)
                    {
                        if (reservation.getPassenger()->getCustomer() == customerAccount)
                        {
                            cout << "Amount: " << reservation.getConstantPrice() << '\n';
                            break;
                        }
                    }

                    cout << "\nDo you confirm the payment? (Yes/No): ";
                    cin >> payment;

                    if (payment == "Yes" || payment == "yes")
                    {
                        cout << "\nReservation created successfully!\n";
                        cout << "\nPayment successful! Thank you for your reservation.\n";
                        writeReservationsToFile();
                        break;
                    }
                    else
                    {
                        cout << "The reservation could not be created.\n";
                        break;
                    }

                    break;
                }
                break;

            case 4:

                cout << "\n----------       - Reservation Cancellation Process -       ----------\n";
                cout << "This is your reservation's information:\n";

                for (const Reservation &reservation : reservations)
                {
                    if (reservation.getPassenger()->getCustomer() == customerAccount)
                    {
                        countCase2++;
                        cout << "\nReservation ID: " << reservation.getReservationId() << '\n';
                        cout << "Price: " << reservation.getConstantPrice() << '\n';
                        cout << "Flight ID: " << reservation.getFlight()->getFlightId() << '\n';
                        cout << "Ticket Type: " << reservation.ticketTypeToString(reservation.getTicketType()) << '\n';
                        cout << "Check-In: " << (reservation.getIsCheckIn() ? "Yes" : "No") << '\n';
                        cout << "Flight Full: " << (reservation.getIsFlightFull() ? "Yes" : "No") << '\n';
                    }
                }

                if (countCase2 == 0)
                {
                    cout << "\nYou have no reservations.\n";
                    break;
                }

                cout << "\nPlease enter the reservation ID to cancel: ";
                cin >> reservationId;
                reservation = findReservationById(reservationId);

                if (reservation == nullptr)
                {
                    cout << "\nReservation not found!\n";
                    break;
                }
                else if (reservation->getPassenger()->getCustomer() != customerAccount)
                {
                    cout << "\nYou can only cancel your own reservations.\n";
                    break;
                }

                if (reservation->getIsCheckIn())
                {
                    cout << "You cannot cancel this reservation because you have already checked in.\n";
                    break;
                }
                else
                {
                    deleteReservation(reservationId);
                    writeReservationsToFile();
                    cout << "\nReservation canceled successfully!\n";
                    break;
                }

                break;
            case 5:

                cout << "\n----------       - Reservation Check-In Process -       ----------\n";

                for (Reservation &reservation : reservations)
                {
                    if (reservation.getPassenger()->getCustomer() == customerAccount && !reservation.getIsCheckIn())
                    {
                        countCase2++;
                        cout << "\nReservation ID: " << reservation.getReservationId() << '\n';
                        cout << "Price: " << reservation.getConstantPrice() << '\n';
                        cout << "Flight ID: " << reservation.getFlight()->getFlightId() << '\n';
                        cout << "Ticket Type: " << reservation.ticketTypeToString(reservation.getTicketType()) << '\n';
                        cout << "Check-In: " << (reservation.getIsCheckIn() ? "Yes" : "No") << '\n';
                        cout << "Flight Full: " << (reservation.getIsFlightFull() ? "Yes" : "No") << '\n';
                        cout << "Do you want to Check-In? ( Yes - No )   ";
                        cin >> checkIn;

                        if (checkIn == "Yes" || checkIn == "yes")
                        {
                            reservation.setIsCheckIn(true);
                            cout << "\nCheck-In process completed.\n";
                            break;
                        }
                    }
                }

                if (countCase2 == 0)
                {
                    cout << "\nYou have no reservations.\n";
                }

                break;

            case 6:
                void createTicketFile(const Customer *customerAccount);
                for (const Reservation &reservation : reservations)
                {
                    if (reservation.getPassenger()->getCustomer() == customerAccount)
                    {

                        // readReservationsFromFile(RESERVATION_FILE, &createTicket, customerAccount);
                    }
                }

                break;
            case 7:

                displayNotifications(customerAccount, reservations, hasNotification, trigger);
                break;

            case 8:
                cout << "\nLogging out...\n";
                account = nullptr;
                customerAccount = nullptr;
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
            }
        }
    }
    writeCustomersToFile();
    writeFlightsToFile();
    writeReservationsToFile();

    return 0;
}