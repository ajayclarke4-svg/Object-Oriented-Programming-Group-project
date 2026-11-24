#include "Coach.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>

Coach::Coach()
    : Person(0, "Unknown Coach", 30, "Unspecified"),
      qualification("JFF Level 1"), coachingRole("Assistant Coach"), teamId(0) {}

Coach::Coach(int personId, const std::string& personName, int personAge, const std::string& personGender,
             const std::string& coachQualification, const std::string& role, int teamIdentifier)
    : Person(personId, personName, personAge, personGender) {
    setQualification(coachQualification);
    setCoachingRole(role);
    setTeamId(teamIdentifier);
}

std::string Coach::getQualification() const {
    return qualification;
}

std::string Coach::getCoachingRole() const {
    return coachingRole;
}

int Coach::getTeamId() const {
    return teamId;
}

void Coach::setQualification(const std::string& newQual) {
    if (newQual.empty()) {
        throw InvalidDataException("Coach qualification cannot be empty.");
    }
    qualification = newQual;
}

void Coach::setCoachingRole(const std::string& newRole) {
    if (newRole.empty()) {
        throw InvalidDataException("Coaching role cannot be empty.");
    }
    coachingRole = newRole;
}

void Coach::setTeamId(int newTeamId) {
    if (newTeamId < 0) {
        throw InvalidDataException("Team ID cannot be negative.");
    }
    teamId = newTeamId;
}

void Coach::displayInformation() const {
    std::cout << "[Coach] ID: " << id
              << " | Name: " << name
              << " | Age: " << age
              << " | Gender: " << gender
              << " | Role: " << coachingRole
              << " | Qualification: " << qualification
              << " | Team ID: " << teamId << std::endl;
}

std::string Coach::toRecord() const {
    std::vector<std::string> fields;
    fields.push_back(FileManager::toText(id));
    fields.push_back(name);
    fields.push_back(FileManager::toText(age));
    fields.push_back(gender);
    fields.push_back(qualification);
    fields.push_back(coachingRole);
    fields.push_back(FileManager::toText(teamId));
    return FileManager::joinFields(fields);
}

void Coach::fromRecord(const std::string& record) {
    std::vector<std::string> fields = FileManager::splitFields(record);
    if (fields.size() < 7) {
        throw FileException("Coach record requires 7 fields: " + record);
    }
    setId(FileManager::toInt(fields[0]));
    setName(fields[1]);
    setAge(FileManager::toInt(fields[2]));
    setGender(fields[3]);
    setQualification(fields[4]);
    setCoachingRole(fields[5]);
    setTeamId(FileManager::toInt(fields[6]));
}
