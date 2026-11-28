#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <string>
#include <sstream>
#include "Person.h"
using namespace std;

// ============================================================
//  Player — inherits Person
//  Represents a football player in the league.
// ============================================================
class Player : public Person {
private:
    string position;
    int jerseyNumber;
    int goals;
    string playingStatus;   // "Active" or "Suspended"
    int teamId;

public:
    // Default constructor
    Player() : Person() {
        this->position = "?";
        this->jerseyNumber = 1;
        this->goals = 0;
        this->playingStatus = "Active";
        this->teamId = 0;
    }

    // Parameterised constructor
    Player(int personId, string personName, int personAge, string personGender,
           string playerPosition, int playerJersey, string playerStatus, int playerTeamId)
        : Person(personId, personName, personAge, personGender) {
        // Rule: player must be at least 16 years old
        if (personAge < 16) {
            throw InvalidDataException("Player age must be at least 16.");
        }
        // Jersey number must be between 1 and 99
        if (playerJersey < 1 || playerJersey > 99) {
            throw InvalidDataException("Jersey number must be between 1 and 99.");
        }
        this->position = playerPosition;
        this->jerseyNumber = playerJersey;
        this->goals = 0;
        this->playingStatus = playerStatus;
        this->teamId = playerTeamId;
    }

    // ---- Getters ----
    string getPosition() {
        return position;
    }
    int getJerseyNumber() {
        return jerseyNumber;
    }
    int getGoals() {
        return goals;
    }
    string getPlayingStatus() {
        return playingStatus;
    }
    int getTeamId() {
        return teamId;
    }

    // ---- Setters ----
    void setPosition(string newPosition) {
        if (newPosition.empty()) {
            throw InvalidDataException("Position cannot be empty.");
        }
        this->position = newPosition;
    }
    void setJerseyNumber(int newJersey) {
        if (newJersey < 1 || newJersey > 99) {
            throw InvalidDataException("Jersey number must be between 1 and 99.");
        }
        this->jerseyNumber = newJersey;
    }
    void setGoals(int newGoals) {
        if (newGoals < 0) {
            throw NegativeValueException("Goals cannot be negative.");
        }
        this->goals = newGoals;
    }
    void addGoal() {
        this->goals++;
    }
    void setPlayingStatus(string newStatus) {
        if (newStatus != "Active" && newStatus != "Suspended") {
            throw InvalidDataException("Playing status must be 'Active' or 'Suspended'.");
        }
        this->playingStatus = newStatus;
    }
    void setTeamId(int newTeamId) {
        this->teamId = newTeamId;
    }

    // ---- Override pure virtual methods ----
    void displayInformation() {
        cout << "=== Player Information ===" << endl;
        cout << "ID            : " << id << endl;
        cout << "Name          : " << name << endl;
        cout << "Age           : " << age << endl;
        cout << "Gender        : " << gender << endl;
        cout << "Position      : " << position << endl;
        cout << "Jersey No.    : " << jerseyNumber << endl;
        cout << "Goals Scored  : " << goals << endl;
        cout << "Status        : " << playingStatus << endl;
        cout << "Team ID       : " << teamId << endl;
    }

    string toRecord() {
        // Format: id|name|age|gender|position|jerseyNumber|goals|playingStatus|teamId
        stringstream ss;
        ss << id << "|" << name << "|" << age << "|" << gender << "|"
           << position << "|" << jerseyNumber << "|" << goals << "|"
           << playingStatus << "|" << teamId;
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->id = stoi(token);
        getline(ss, this->name, '|');
        getline(ss, token, '|'); this->age = stoi(token);
        getline(ss, this->gender, '|');
        getline(ss, this->position, '|');
        getline(ss, token, '|'); this->jerseyNumber = stoi(token);
        getline(ss, token, '|'); this->goals = stoi(token);
        getline(ss, this->playingStatus, '|');
        getline(ss, token, '|'); this->teamId = stoi(token);
    }
};

#endif
