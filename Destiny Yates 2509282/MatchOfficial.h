#ifndef MATCHOFFICIAL_H
#define MATCHOFFICIAL_H

#include <iostream>
#include <string>
#include <sstream>
#include "Person.h"
using namespace std;

// ============================================================
//  MatchOfficial — inherits Person
//  Represents a referee or linesman who officates matches.
// ============================================================
class MatchOfficial : public Person {
private:
    string officiatingRole;   // e.g. "Referee", "Linesman", "Fourth Official"
    string rank;              // e.g. "FIFA", "National", "Regional"
    bool available;

public:
    // Default constructor
    MatchOfficial() : Person() {
        this->officiatingRole = "?";
        this->rank = "?";
        this->available = true;
    }

    // Parameterised constructor
    MatchOfficial(int personId, string personName, int personAge, string personGender,
                  string officialRole, string officialRank)
        : Person(personId, personName, personAge, personGender) {
        if (officialRole.empty()) {
            throw InvalidDataException("Officiating role cannot be empty.");
        }
        if (officialRank.empty()) {
            throw InvalidDataException("Official rank cannot be empty.");
        }
        this->officiatingRole = officialRole;
        this->rank = officialRank;
        this->available = true;
    }

    // ---- Getters ----
    string getOfficiatingRole() {
        return officiatingRole;
    }
    string getRank() {
        return rank;
    }
    bool isAvailable() {
        return available;
    }

    // ---- Setters ----
    void setOfficiatingRole(string newRole) {
        if (newRole.empty()) {
            throw InvalidDataException("Officiating role cannot be empty.");
        }
        this->officiatingRole = newRole;
    }
    void setRank(string newRank) {
        if (newRank.empty()) {
            throw InvalidDataException("Rank cannot be empty.");
        }
        this->rank = newRank;
    }
    void setAvailable(bool isAvail) {
        this->available = isAvail;
    }

    // ---- Override pure virtual methods ----
    void displayInformation() {
        cout << "=== Match Official Information ===" << endl;
        cout << "ID               : " << id << endl;
        cout << "Name             : " << name << endl;
        cout << "Age              : " << age << endl;
        cout << "Gender           : " << gender << endl;
        cout << "Officiating Role : " << officiatingRole << endl;
        cout << "Rank             : " << rank << endl;
        cout << "Available        : " << (available ? "Yes" : "No") << endl;
    }

    string toRecord() {
        // Format: id|name|age|gender|officiatingRole|rank|available
        stringstream ss;
        ss << id << "|" << name << "|" << age << "|" << gender << "|"
           << officiatingRole << "|" << rank << "|" << (available ? 1 : 0);
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->id = stoi(token);
        getline(ss, this->name, '|');
        getline(ss, token, '|'); this->age = stoi(token);
        getline(ss, this->gender, '|');
        getline(ss, this->officiatingRole, '|');
        getline(ss, this->rank, '|');
        getline(ss, token, '|'); this->available = (stoi(token) == 1);
    }
};

#endif
