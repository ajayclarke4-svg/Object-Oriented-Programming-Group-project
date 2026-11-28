#ifndef COACH_H
#define COACH_H

#include "Person.h"
#include <string>

class Coach : public Person {
private:
    string qualification;
    string coachingRole;
    int teamId;
public:
    Coach(){
        qualification = "?";
        coachingRole = "?";
        teamId = 0;
    };
    Coach(string coachQualification, string role, int teamIdentifier = 0): Person(0, "?", 0, "?") {
        setQualification(coachQualification);
        setCoachingRole(role);
        setTeamId(teamIdentifier);
    };

    // Accessors
    string getQualification(){
        return qualification;
    };
    string getCoachingRole(){
        return coachingRole;
    };
    int getTeamId(){
        return teamId;
    };

    // Mutators with validation
    void setQualification(string newQual){
        if (newQual.empty()) {
            throw InvalidDataException("Coach qualification cannot be empty.");
        }
        qualification = newQual;
    };
    void setCoachingRole(string newRole){
        if (newRole.empty()) {
            throw InvalidDataException("Coaching role cannot be empty.");
        }
        coachingRole = newRole;
    };
    void setTeamId(int newTeamId){
        if (newTeamId < 0) {
            throw InvalidDataException("Team ID cannot be negative.");
        }
        teamId = newTeamId;
    };

    // Polymorphic display
    virtual void displayInformation() override{
        cout << "[Coach] ID: " << id
              << " | Name: " << name
              << " | Age: " << age
              << " | Gender: " << gender
              << " | Role: " << coachingRole
              << " | Qualification: " << qualification
              << " | Team ID: " << teamId << std::endl;
    };

    // Storable interface methods
    virtual string toRecord() override{

    };
    virtual void fromRecord() override{
        string record;

    };
};

#endif // COACH_H

