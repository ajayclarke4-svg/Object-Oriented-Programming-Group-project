#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <string>
#include "Exceptions.h"
using namespace std;

// ============================================================
//  Person — Abstract base class
//  Player, Coach, Spectator, MatchOfficial and
//  LeagueCommissioner will inherit from it.
// ============================================================
class Person {
protected:
    int id;
    string name;
    int age;
    string gender;

public:
    // Default constructor
    Person() {
        id = 0;
        name = "?";
        age = 0;
        gender = "?";
    }

    // Parameterised constructor
    Person(int personId, string personName, int personAge, string personGender) {
        this->id = personId;
        this->name = personName;
        this->age = personAge;
        this->gender = personGender;
    }

    virtual ~Person() {}

    // ---- Getters ----
    int getId() {
        return id;
    }
    string getName() {
        return name;
    }
    int getAge() {
        return age;
    }
    string getGender() {
        return gender;
    }

    // ---- Setters (with validation) ----
    void setId(int newId) {
        if (newId < 0) {
            throw InvalidDataException("Person ID cannot be negative.");
        }
        this->id = newId;
    }
    void setName(string newName) {
        if (newName.empty()) {
            throw InvalidDataException("Person name cannot be empty.");
        }
        this->name = newName;
    }
    void setAge(int newAge) {
        if (newAge < 0 || newAge > 120) {
            throw InvalidDataException("Person age must be between 0 and 120.");
        }
        this->age = newAge;
    }
    void setGender(string newGender) {
        if (newGender.empty()) {
            throw InvalidDataException("Person gender cannot be empty.");
        }
        this->gender = newGender;
    }

    // ---- Pure virtual methods ----
    // Every kind of person must implement these
    virtual void displayInformation() = 0;
    virtual string toRecord() = 0;
    virtual void fromRecord(string record) = 0;
};

#endif
