#ifndef STADIUM_H
#define STADIUM_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Exceptions.h"
using namespace std;

//  Stadium — Represents a match venue
class Stadium {
private:
    int stadiumId;
    string name;
    string location;
    int capacity;
    string fieldCondition;  // "Excellent", "Good", "Fair", "Poor"
    double ticketPrice;
    int ticketsSold;

public:
    // Default constructor
    Stadium() {
        this->stadiumId = 0;
        this->name = "?";
        this->location = "?";
        this->capacity = 0;
        this->fieldCondition = "Good";
        this->ticketPrice = 0.0;
        this->ticketsSold = 0;
    }

    // Parameterised constructor
    Stadium(int id, string stadiumName, string stadiumLocation,
            int stadiumCapacity, string condition, double price) {
        if (stadiumName.empty()) {
            throw InvalidDataException("Stadium name cannot be empty.");
        }
        if (stadiumCapacity <= 0) {
            throw InvalidDataException("Stadium capacity must be greater than zero.");
        }
        if (price < 0.0) {
            throw NegativeValueException("Ticket price cannot be negative.");
        }
        this->stadiumId = id;
        this->name = stadiumName;
        this->location = stadiumLocation;
        this->capacity = stadiumCapacity;
        this->fieldCondition = condition;
        this->ticketPrice = price;
        this->ticketsSold = 0;
    }

    // ---- Getters ----
    int getStadiumId() {
        return stadiumId;
    }
    string getName() {
        return name;
    }
    string getLocation() {
        return location;
    }
    int getCapacity() {
        return capacity;
    }
    string getFieldCondition() {
        return fieldCondition;
    }
    double getTicketPrice() {
        return ticketPrice;
    }
    int getTicketsSold() {
        return ticketsSold;
    }
    int getSeatsRemaining() {
        return capacity - ticketsSold;
    }

    // ---- Setters ----
    void setName(string newName) {
        if (newName.empty()) {
            throw InvalidDataException("Stadium name cannot be empty.");
        }
        this->name = newName;
    }
    void setLocation(string newLocation) {
        this->location = newLocation;
    }
    void setCapacity(int newCapacity) {
        if (newCapacity <= 0) {
            throw InvalidDataException("Capacity must be greater than zero.");
        }
        this->capacity = newCapacity;
    }
    void setFieldCondition(string newCondition) {
        this->fieldCondition = newCondition;
    }
    void setTicketPrice(double newPrice) {
        if (newPrice < 0.0) {
            throw NegativeValueException("Ticket price cannot be negative.");
        }
        this->ticketPrice = newPrice;
    }
    void setTicketsSold(int sold) {
        this->ticketsSold = sold;
    }

    // ---- Business rule: ticket sales cannot exceed capacity ----
    void sellTickets(int qty) {
        if (qty <= 0) {
            throw InvalidDataException("Quantity of tickets must be greater than zero.");
        }
        if (ticketsSold + qty > capacity) {
            throw CapacityExceededException(
                "Cannot sell " + to_string(qty) + " tickets. Only " +
                to_string(getSeatsRemaining()) + " seats remaining at " + name + ".");
        }
        this->ticketsSold += qty;
    }

    // ---- Reset ticket sales for a new fixture ----
    void resetTicketSales() {
        this->ticketsSold = 0;
    }

    // ---- Display ----
    void displayInformation() {
        cout << "=== Stadium Information ===" << endl;
        cout << "ID               : " << stadiumId << endl;
        cout << "Name             : " << name << endl;
        cout << "Location         : " << location << endl;
        cout << "Capacity         : " << capacity << endl;
        cout << "Field Condition  : " << fieldCondition << endl;
        cout << fixed << setprecision(2);
        cout << "Ticket Price     : $" << ticketPrice << endl;
        cout << "Tickets Sold     : " << ticketsSold << endl;
        cout << "Seats Remaining  : " << getSeatsRemaining() << endl;
    }

    // ---- File record ----
    string toRecord() {
        stringstream ss;
        ss << stadiumId << "|" << name << "|" << location << "|"
           << capacity << "|" << fieldCondition << "|" << ticketPrice << "|" << ticketsSold;
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->stadiumId = stoi(token);
        getline(ss, this->name, '|');
        getline(ss, this->location, '|');
        getline(ss, token, '|'); this->capacity = stoi(token);
        getline(ss, this->fieldCondition, '|');
        getline(ss, token, '|'); this->ticketPrice = stod(token);
        getline(ss, token, '|'); this->ticketsSold = stoi(token);
    }
};

#endif
