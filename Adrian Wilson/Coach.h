#ifndef COACH_H
#define COACH_H

#include "Person.h"
#include <string>

class Coach : public Person {
private:
    std::string qualification;
    std::string coachingRole;
    int teamId;

public:
    Coach();
    Coach(int personId, const std::string& personName, int personAge, const std::string& personGender,
          const std::string& coachQualification, const std::string& role, int teamIdentifier = 0);

    // Accessors
    std::string getQualification() const;
    std::string getCoachingRole() const;
    int getTeamId() const;

    // Mutators with validation
    void setQualification(const std::string& newQual);
    void setCoachingRole(const std::string& newRole);
    void setTeamId(int newTeamId);

    // Polymorphic display
    virtual void displayInformation() const override;

    // Storable interface methods
    virtual std::string toRecord() const override;
    virtual void fromRecord(const std::string& record) override;
};

#endif // COACH_H
