#include "Person.h.cpp"
#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<Customer> customers;
int customerCount = 0;
vector<Passenger> passengers;
int passengerCount = 0;

Person::Person(int id, const string &userName, const string &password, const string &name, const string &mail, const string &phone, bool isManager)
    : id(id), userName(userName), password(password), name(name), email(mail), phone(phone), isManager(isManager)
{
}

Person::Person()
    : id(0), userName(""), password(""), name(""), email(""), phone(""), isManager(false)
{
}

int Person::getId() const
{
    return id;
}

string Person::getUsername() const
{
    return userName;
}

string Person::getPassword() const
{
    return password;
}

string Person::getName() const
{
    return name;
}

string Person::getMail() const
{
    return email;
}

string Person::getPhone() const
{
    return phone;
}

bool Person::getIsManager() const
{
    return isManager;
}

void Person::setId(int newId)
{
    id = newId;
}

void Person::setUsername(const string &newUsername)
{
    userName = newUsername;
}

void Person::setPassword(const string &newPassword)
{
    password = newPassword;
}

void Person::setName(const string &newName)
{
    name = newName;
}

void Person::setMail(const string &newMail)
{
    email = newMail;
}

void Person::setPhone(const string &newPhone)
{
    phone = newPhone;
}

void Person::setIsManager(bool newIsManager)
{
    isManager = newIsManager;
}

Customer::Customer(int id, const string &username, const string &password, const string &name, const string &mail, const string &phone)
    : Person(id, username, password, name, mail, phone, false)
{
}

Passenger::Passenger()
    : Person(), customer(nullptr), passengerId(""), passengerType(PassengerType::ADULT)
{
}

Customer *Passenger::getCustomer() const
{
    return customer;
}

std::string Passenger::getPassengerId() const
{
    return passengerId;
}

PassengerType Passenger::getPassengerType() const
{
    return passengerType;
}

void Passenger::setCustomer(Customer *newCustomer)
{
    customer = newCustomer;
}

void Passenger::setPassengerId(const std::string &newPassengerId)
{
    passengerId = newPassengerId;
}

void Passenger::setPassengerType(PassengerType newPassengerType)
{
    passengerType = newPassengerType;
}