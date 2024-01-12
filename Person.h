#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

enum class PassengerType
{
    ADULT,
    CHILD
};

class Person
{
private:
    int id;
    string userName;
    string password;
    string name;
    string email;
    string phone;
    bool isManager; // Yeni eklenen özellik

public:
    virtual ~Person() {}
    Person(int id, const string &username, const string &password, const string &name, const string &mail, const string &phone, bool isManager);
    Person();

    int getId() const;
    string getUsername() const;
    string getPassword() const;
    string getName() const;
    string getMail() const;
    string getPhone() const;
    bool getIsManager() const; // Yeni eklenen fonksiyon

    void setId(int newId);
    void setUsername(const string &newUsername);
    void setPassword(const string &newPassword);
    void setName(const string &newName);
    void setMail(const string &newMail);
    void setPhone(const string &newPhone);
    void setIsManager(bool newIsManager); // Yeni eklenen fonksiyon
    virtual bool isCustomer() const { return false; } 
};

class Customer : public Person
{
public:
    Customer(int id, const string &username, const string &password, const string &name, const string &mail, const string &phone);
    Customer();
        bool isCustomer() const override { return true; }

};

class Manager : public Person
{
public:
    Manager(int id, const string &username, const string &password);
};

class Passenger : public Person
{
private:
    Customer *customer;
    string passengerId;
    PassengerType passengerType;

public:
    Passenger(int id, const string passengerId, const string name, Customer *customer, PassengerType passengerType);
    Passenger();
    Customer *getCustomer() const;
    void setCustomer(Customer *newCustomer);
    string getPassengerId() const;
    void setPassengerId(const std::string &newPassengerId);
    PassengerType getPassengerType() const;
    void setPassengerType(PassengerType newPassengerType);
};

extern vector<Customer> customers;
extern int customerCount;
extern vector<Passenger> passengers;
extern int passengerCount;

#endif
