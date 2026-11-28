#ifndef SPECTATOR_H
#define SPECTATOR_H

#include <iostream>
#include <string>
#include <sstream>
#include "Person.h"
using namespace std;

// ============================================================
//  Spectator — inherits Person
//  Represents a fan who attends league matches.
// ============================================================
class Spectator : public Person {
private:
    int ticketsBought;
    double totalSpent;

public:
    // Default constructor
    Spectator() : Person() {
        this->ticketsBought = 0;
        this->totalSpent = 0.0;
    }

    // Parameterised constructor
    Spectator(int personId, string personName, int personAge, string personGender)
        : Person(personId, personName, personAge, personGender) {
        this->ticketsBought = 0;
        this->totalSpent = 0.0;
    }

    // ---- Getters ----
    int getTicketsBought() {
        return ticketsBought;
    }
    double getTotalSpent() {
        return totalSpent;
    }

    // ---- Setters / helpers ----
    void setTicketsBought(int newTickets) {
        if (newTickets < 0) {
            throw NegativeValueException("Tickets bought cannot be negative.");
        }
        this->ticketsBought = newTickets;
    }
    void setTotalSpent(double newTotal) {
        if (newTotal < 0.0) {
            throw NegativeValueException("Total spent cannot be negative.");
        }
        this->totalSpent = newTotal;
    }

    // Called when the spectator buys a ticket
    void recordPurchase(double amount) {
        if (amount < 0.0) {
            throw NegativeValueException("Purchase amount cannot be negative.");
        }
        this->ticketsBought++;
        this->totalSpent += amount;
    }

    // ---- Override pure virtual methods ----
    void displayInformation() {
        cout << "=== Spectator Information ===" << endl;
        cout << "ID             : " << id << endl;
        cout << "Name           : " << name << endl;
        cout << "Age            : " << age << endl;
        cout << "Gender         : " << gender << endl;
        cout << "Tickets Bought : " << ticketsBought << endl;
        cout << fixed;
        cout.precision(2);
        cout << "Total Spent    : $" << totalSpent << endl;
    }

    string toRecord() {
        // Format: id|name|age|gender|ticketsBought|totalSpent
        stringstream ss;
        ss << id << "|" << name << "|" << age << "|" << gender << "|"
           << ticketsBought << "|" << totalSpent;
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->id = stoi(token);
        getline(ss, this->name, '|');
        getline(ss, token, '|'); this->age = stoi(token);
        getline(ss, this->gender, '|');
        getline(ss, token, '|'); this->ticketsBought = stoi(token);
        getline(ss, token, '|'); this->totalSpent = stod(token);
    }
};

#endif
