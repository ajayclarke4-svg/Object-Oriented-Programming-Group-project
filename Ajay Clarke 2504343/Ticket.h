#ifndef TICKET_H
#define TICKET_H

#include <iostream>
#include <string>
#include <sstream>
#include "Exceptions.h"
using namespace std;

// ============================================================
//  Ticket — Standalone class (does not inherit Product)
//  Represents a match-day ticket sold to a Spectator.
//  GCT (General Consumption Tax) = 15%
// ============================================================
class Ticket {
private:
    int ticketId;
    int fixtureId;
    string category;    // "VIP", "Grandstand", "Bleachers"
    double price;
    bool isSold;
    int spectatorId;

    static const double GCT_RATE;   // 0.15 — defined below

public:
    // Default constructor
    Ticket() {
        this->ticketId = 0;
        this->fixtureId = 0;
        this->category = "?";
        this->price = 0.0;
        this->isSold = false;
        this->spectatorId = -1;
    }

    // Parameterised constructor
    Ticket(int tId, int fId, string cat, double ticketPrice) {
        if (cat != "VIP" && cat != "Grandstand" && cat != "Bleachers") {
            throw InvalidDataException("Ticket category must be VIP, Grandstand, or Bleachers.");
        }
        if (ticketPrice < 0.0) {
            throw NegativeValueException("Ticket price cannot be negative.");
        }
        this->ticketId = tId;
        this->fixtureId = fId;
        this->category = cat;
        this->price = ticketPrice;
        this->isSold = false;
        this->spectatorId = -1;
    }

    // ---- Getters ----
    int getTicketId() {
        return ticketId;
    }
    int getFixtureId() {
        return fixtureId;
    }
    string getCategory() {
        return category;
    }
    double getPrice() {
        return price;
    }
    bool getIsSold() {
        return isSold;
    }
    int getSpectatorId() {
        return spectatorId;
    }

    // ---- Setters ----
    void setPrice(double newPrice) {
        if (newPrice < 0.0) {
            throw NegativeValueException("Ticket price cannot be negative.");
        }
        this->price = newPrice;
    }

    // ---- GCT calculations ----
    double calculateTax() {
        return price * GCT_RATE;
    }
    double calculateTotal() {
        return price + calculateTax();
    }

    // ---- Mark ticket as sold ----
    void markAsSold(int specId) {
        if (isSold) {
            throw InvalidDataException("Ticket " + to_string(ticketId) + " is already sold.");
        }
        this->isSold = true;
        this->spectatorId = specId;
    }

    // ---- Display ----
    void displayTicketDetails() {
        cout << "=== Ticket Details ===" << endl;
        cout << "Ticket ID     : " << ticketId << endl;
        cout << "Fixture ID    : " << fixtureId << endl;
        cout << "Category      : " << category << endl;
        cout << fixed;
        cout.precision(2);
        cout << "Price         : $" << price << endl;
        cout << "GCT (15%)     : $" << calculateTax() << endl;
        cout << "Total         : $" << calculateTotal() << endl;
        cout << "Status        : " << (isSold ? "Sold" : "Available") << endl;
        if (isSold) {
            cout << "Spectator ID  : " << spectatorId << endl;
        }
    }

    // ---- File record ----
    string toRecord() {
        stringstream ss;
        ss << ticketId << "|" << fixtureId << "|" << category << "|"
           << price << "|" << (isSold ? 1 : 0) << "|" << spectatorId;
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->ticketId = stoi(token);
        getline(ss, token, '|'); this->fixtureId = stoi(token);
        getline(ss, this->category, '|');
        getline(ss, token, '|'); this->price = stod(token);
        getline(ss, token, '|'); this->isSold = (stoi(token) == 1);
        getline(ss, token, '|'); this->spectatorId = stoi(token);
    }
};

// Static constant definition
const double Ticket::GCT_RATE = 0.15;

#endif
