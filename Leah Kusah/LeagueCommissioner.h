#ifndef LEAGUECOMMISSIONER_H
#define LEAGUECOMMISSIONER_H

#include <iostream>
#include <string>
#include <sstream>
#include "Person.h"
using namespace std;

// ============================================================
//  LeagueCommissioner — inherits Person
//  The executive head of the football league.
// ============================================================
class LeagueCommissioner : public Person {
private:
    string officeLocation;
    string badgeNumber;
    int yearsInService;

public:
    // Default constructor
    LeagueCommissioner() : Person() {
        this->officeLocation = "?";
        this->badgeNumber = "?";
        this->yearsInService = 0;
    }

    // Parameterised constructor
    LeagueCommissioner(int personId, string personName, int personAge, string personGender,
                       string location, string badge, int years)
        : Person(personId, personName, personAge, personGender) {
        if (location.empty()) {
            throw InvalidDataException("Office location cannot be empty.");
        }
        if (badge.empty()) {
            throw InvalidDataException("Badge number cannot be empty.");
        }
        if (years < 0) {
            throw NegativeValueException("Years in service cannot be negative.");
        }
        this->officeLocation = location;
        this->badgeNumber = badge;
        this->yearsInService = years;
    }

    // ---- Getters ----
    string getOfficeLocation() {
        return officeLocation;
    }
    string getBadgeNumber() {
        return badgeNumber;
    }
    int getYearsInService() {
        return yearsInService;
    }

    // ---- Setters ----
    void setOfficeLocation(string newLocation) {
        if (newLocation.empty()) {
            throw InvalidDataException("Office location cannot be empty.");
        }
        this->officeLocation = newLocation;
    }
    void setBadgeNumber(string newBadge) {
        if (newBadge.empty()) {
            throw InvalidDataException("Badge number cannot be empty.");
        }
        this->badgeNumber = newBadge;
    }
    void setYearsInService(int newYears) {
        if (newYears < 0) {
            throw NegativeValueException("Years in service cannot be negative.");
        }
        this->yearsInService = newYears;
    }

    // ---- Override pure virtual methods ----
    void displayInformation() {
        cout << "=== League Commissioner Information ===" << endl;
        cout << "ID               : " << id << endl;
        cout << "Name             : " << name << endl;
        cout << "Age              : " << age << endl;
        cout << "Gender           : " << gender << endl;
        cout << "Office Location  : " << officeLocation << endl;
        cout << "Badge Number     : " << badgeNumber << endl;
        cout << "Years in Service : " << yearsInService << endl;
    }

    string toRecord() {
        // Format: id|name|age|gender|officeLocation|badgeNumber|yearsInService
        stringstream ss;
        ss << id << "|" << name << "|" << age << "|" << gender << "|"
           << officeLocation << "|" << badgeNumber << "|" << yearsInService;
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->id = stoi(token);
        getline(ss, this->name, '|');
        getline(ss, token, '|'); this->age = stoi(token);
        getline(ss, this->gender, '|');
        getline(ss, this->officeLocation, '|');
        getline(ss, this->badgeNumber, '|');
        getline(ss, token, '|'); this->yearsInService = stoi(token);
    }
};

#endif
