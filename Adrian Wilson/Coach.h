#ifndef COACH_H
#define COACH_H

#include <iostream>
#include <string>
#include <sstream>
#include "Person.h"
using namespace std;

// ============================================================
//  Coach — inherits Person
//  Represents a team coach in the league.
// ============================================================
class Coach : public Person {
private:
    string qualification;
    string coachingRole;    // e.g. "Head Coach", "Assistant Coach"
    int teamId;

public:
    // Default constructor
    Coach() : Person() {
        this->qualification = "?";
        this->coachingRole = "?";
        this->teamId = 0;
    }

    // Parameterised constructor
    Coach(int personId, string personName, int personAge, string personGender,
          string coachQualification, string coachRole, int coachTeamId)
        : Person(personId, personName, personAge, personGender) {
        if (coachQualification.empty()) {
            throw InvalidDataException("Coach qualification cannot be empty.");
        }
        if (coachRole.empty()) {
            throw InvalidDataException("Coaching role cannot be empty.");
        }
        this->qualification = coachQualification;
        this->coachingRole = coachRole;
        this->teamId = coachTeamId;
    }

    // ---- Getters ----
    string getQualification() {
        return qualification;
    }
    string getCoachingRole() {
        return coachingRole;
    }
    int getTeamId() {
        return teamId;
    }

    // ---- Setters ----
    void setQualification(string newQualification) {
        if (newQualification.empty()) {
            throw InvalidDataException("Qualification cannot be empty.");
        }
        this->qualification = newQualification;
    }
    void setCoachingRole(string newRole) {
        if (newRole.empty()) {
            throw InvalidDataException("Coaching role cannot be empty.");
        }
        this->coachingRole = newRole;
    }
    void setTeamId(int newTeamId) {
        this->teamId = newTeamId;
    }

    // ---- Override pure virtual methods ----
    void displayInformation() {
        cout << "=== Coach Information ===" << endl;
        cout << "ID             : " << id << endl;
        cout << "Name           : " << name << endl;
        cout << "Age            : " << age << endl;
        cout << "Gender         : " << gender << endl;
        cout << "Qualification  : " << qualification << endl;
        cout << "Coaching Role  : " << coachingRole << endl;
        cout << "Team ID        : " << teamId << endl;
    }

    string toRecord() {
        // Format: id|name|age|gender|qualification|coachingRole|teamId
        stringstream ss;
        ss << id << "|" << name << "|" << age << "|" << gender << "|"
           << qualification << "|" << coachingRole << "|" << teamId;
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->id = stoi(token);
        getline(ss, this->name, '|');
        getline(ss, token, '|'); this->age = stoi(token);
        getline(ss, this->gender, '|');
        getline(ss, this->qualification, '|');
        getline(ss, this->coachingRole, '|');
        getline(ss, token, '|'); this->teamId = stoi(token);
    }
};

#endif
