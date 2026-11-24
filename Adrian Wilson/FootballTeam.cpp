#include "FootballTeam.h"
#include "Exceptions.h"
#include "FileManager.h"
#include <iostream>
#include <iomanip>

FootballTeam::FootballTeam()
    : teamId(0), name("Unknown Team"), parish("Kingston"), registrationNumber("KPFL-000"),
      squadSize(0), leagueStatus("Unregistered"),
      points(0), matchesPlayed(0), wins(0), draws(0), losses(0), goalsFor(0), goalsAgainst(0) {}

FootballTeam::FootballTeam(int id, const std::string& teamName, const std::string& teamParish,
                           const std::string& regNumber, const std::string& status)
    : points(0), matchesPlayed(0), wins(0), draws(0), losses(0), goalsFor(0), goalsAgainst(0) {
    setTeamId(id);
    setName(teamName);
    setParish(teamParish);
    setRegistrationNumber(regNumber);
    setLeagueStatus(status);
    squadSize = 0;
}

int FootballTeam::getTeamId() const {
    return teamId;
}

std::string FootballTeam::getName() const {
    return name;
}

std::string FootballTeam::getParish() const {
    return parish;
}

std::string FootballTeam::getRegistrationNumber() const {
    return registrationNumber;
}

int FootballTeam::getSquadSize() const {
    return static_cast<int>(players.size());
}

std::string FootballTeam::getLeagueStatus() const {
    return leagueStatus;
}

bool FootballTeam::isEligibleForFixture() const {
    return (leagueStatus == "Registered");
}

int FootballTeam::getPoints() const {
    return points;
}

int FootballTeam::getMatchesPlayed() const {
    return matchesPlayed;
}

int FootballTeam::getWins() const {
    return wins;
}

int FootballTeam::getDraws() const {
    return draws;
}

int FootballTeam::getLosses() const {
    return losses;
}

int FootballTeam::getGoalsFor() const {
    return goalsFor;
}

int FootballTeam::getGoalsAgainst() const {
    return goalsAgainst;
}

int FootballTeam::getGoalDifference() const {
    return goalsFor - goalsAgainst;
}

const std::vector<Player>& FootballTeam::getPlayers() const {
    return players;
}

const std::vector<Coach>& FootballTeam::getCoaches() const {
    return coaches;
}

void FootballTeam::setTeamId(int id) {
    if (id < 0) {
        throw InvalidDataException("Team ID cannot be negative.");
    }
    teamId = id;
}

void FootballTeam::setName(const std::string& newName) {
    if (newName.empty()) {
        throw InvalidDataException("Team name cannot be empty.");
    }
    name = newName;
}

void FootballTeam::setParish(const std::string& newParish) {
    if (newParish.empty()) {
        throw InvalidDataException("Parish cannot be empty.");
    }
    parish = newParish;
}

void FootballTeam::setRegistrationNumber(const std::string& regNumber) {
    if (regNumber.empty()) {
        throw InvalidDataException("Registration number cannot be empty.");
    }
    registrationNumber = regNumber;
}

void FootballTeam::setLeagueStatus(const std::string& newStatus) {
    if (newStatus != "Registered" && newStatus != "Unregistered" && newStatus != "Suspended") {
        throw InvalidDataException("Invalid league status: " + newStatus + ". Must be Registered, Unregistered, or Suspended.");
    }
    leagueStatus = newStatus;
}

void FootballTeam::setStats(int pts, int played, int w, int d, int l, int gf, int ga) {
    if (pts < 0 || played < 0 || w < 0 || d < 0 || l < 0 || gf < 0 || ga < 0) {
        throw NegativeValueException("Team statistics values cannot be negative.");
    }
    points = pts;
    matchesPlayed = played;
    wins = w;
    draws = d;
    losses = l;
    goalsFor = gf;
    goalsAgainst = ga;
}

void FootballTeam::addPlayer(const Player& player) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].getId() == player.getId()) {
            throw InvalidDataException("Player with ID " + FileManager::toText(player.getId()) + " already exists in team " + name);
        }
        if (players[i].getJerseyNumber() == player.getJerseyNumber()) {
            throw InvalidDataException("Jersey #" + FileManager::toText(player.getJerseyNumber()) + " is already taken by " + players[i].getName());
        }
    }
    Player p = player;
    p.setTeamId(teamId);
    players.push_back(p);
    squadSize = static_cast<int>(players.size());
}

bool FootballTeam::removePlayer(int playerId) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].getId() == playerId) {
            players.erase(players.begin() + i);
            squadSize = static_cast<int>(players.size());
            return true;
        }
    }
    return false;
}

Player* FootballTeam::findPlayer(int playerId) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].getId() == playerId) {
            return &players[i];
        }
    }
    return nullptr;
}

const Player* FootballTeam::findPlayer(int playerId) const {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].getId() == playerId) {
            return &players[i];
        }
    }
    return nullptr;
}

bool FootballTeam::updatePlayer(const Player& updatedPlayer) {
    for (size_t i = 0; i < players.size(); i++) {
        if (players[i].getId() == updatedPlayer.getId()) {
            // Check jersey number collision with other players
            for (size_t j = 0; j < players.size(); j++) {
                if (i != j && players[j].getJerseyNumber() == updatedPlayer.getJerseyNumber()) {
                    throw InvalidDataException("Jersey #" + FileManager::toText(updatedPlayer.getJerseyNumber()) + " is already used by another player.");
                }
            }
            players[i] = updatedPlayer;
            players[i].setTeamId(teamId);
            return true;
        }
    }
    return false;
}

void FootballTeam::addCoach(const Coach& coach) {
    for (size_t i = 0; i < coaches.size(); i++) {
        if (coaches[i].getId() == coach.getId()) {
            throw InvalidDataException("Coach with ID " + FileManager::toText(coach.getId()) + " already exists in team " + name);
        }
    }
    Coach c = coach;
    c.setTeamId(teamId);
    coaches.push_back(c);
}

bool FootballTeam::removeCoach(int coachId) {
    for (size_t i = 0; i < coaches.size(); i++) {
        if (coaches[i].getId() == coachId) {
            coaches.erase(coaches.begin() + i);
            return true;
        }
    }
    return false;
}

Coach* FootballTeam::findCoach(int coachId) {
    for (size_t i = 0; i < coaches.size(); i++) {
        if (coaches[i].getId() == coachId) {
            return &coaches[i];
        }
    }
    return nullptr;
}

const Coach* FootballTeam::findCoach(int coachId) const {
    for (size_t i = 0; i < coaches.size(); i++) {
        if (coaches[i].getId() == coachId) {
            return &coaches[i];
        }
    }
    return nullptr;
}

bool FootballTeam::updateCoach(const Coach& updatedCoach) {
    for (size_t i = 0; i < coaches.size(); i++) {
        if (coaches[i].getId() == updatedCoach.getId()) {
            coaches[i] = updatedCoach;
            coaches[i].setTeamId(teamId);
            return true;
        }
    }
    return false;
}

void FootballTeam::recordMatchResult(int scored, int conceded) {
    if (scored < 0 || conceded < 0) {
        throw NegativeValueException("Match goals cannot be negative.");
    }
    matchesPlayed++;
    goalsFor += scored;
    goalsAgainst += conceded;

    if (scored > conceded) {
        wins++;
        points += 3; // Win = 3 points
    } else if (scored == conceded) {
        draws++;
        points += 1; // Draw = 1 point
    } else {
        losses++;    // Loss = 0 points
    }
}

void FootballTeam::resetStats() {
    points = 0;
    matchesPlayed = 0;
    wins = 0;
    draws = 0;
    losses = 0;
    goalsFor = 0;
    goalsAgainst = 0;
}

void FootballTeam::displayInformation() const {
    std::cout << "[Team #" << teamId << "] " << std::left << std::setw(20) << name
              << " | Parish: " << std::setw(12) << parish
              << " | Reg: " << std::setw(10) << registrationNumber
              << " | Status: " << std::setw(12) << leagueStatus
              << " | Squad: " << getSquadSize()
              << " | Pts: " << points << std::endl;
}

void FootballTeam::displayRoster() const {
    std::cout << "\n=======================================================\n";
    std::cout << "ROSTER: " << name << " (ID: " << teamId << ") - Status: " << leagueStatus << "\n";
    std::cout << "Parish: " << parish << " | Reg #: " << registrationNumber << "\n";
    std::cout << "Standings: P:" << matchesPlayed << " W:" << wins << " D:" << draws
              << " L:" << losses << " GF:" << goalsFor << " GA:" << goalsAgainst
              << " GD:" << getGoalDifference() << " PTS:" << points << "\n";
    std::cout << "----------------- COACHING STAFF ----------------------\n";
    if (coaches.empty()) {
        std::cout << "  No coaches registered.\n";
    } else {
        for (size_t i = 0; i < coaches.size(); i++) {
            std::cout << "  ";
            coaches[i].displayInformation();
        }
    }
    std::cout << "----------------- SQUAD PLAYERS -----------------------\n";
    if (players.empty()) {
        std::cout << "  No players registered.\n";
    } else {
        for (size_t i = 0; i < players.size(); i++) {
            std::cout << "  ";
            players[i].displayInformation();
        }
    }
    std::cout << "=======================================================\n";
}

std::string FootballTeam::toRecord() const {
    std::vector<std::string> fields;
    fields.push_back(FileManager::toText(teamId));
    fields.push_back(name);
    fields.push_back(parish);
    fields.push_back(registrationNumber);
    fields.push_back(FileManager::toText(getSquadSize()));
    fields.push_back(leagueStatus);
    fields.push_back(FileManager::toText(points));
    fields.push_back(FileManager::toText(matchesPlayed));
    fields.push_back(FileManager::toText(wins));
    fields.push_back(FileManager::toText(draws));
    fields.push_back(FileManager::toText(losses));
    fields.push_back(FileManager::toText(goalsFor));
    fields.push_back(FileManager::toText(goalsAgainst));
    return FileManager::joinFields(fields);
}

void FootballTeam::fromRecord(const std::string& record) {
    std::vector<std::string> fields = FileManager::splitFields(record);
    if (fields.size() < 13) {
        throw FileException("Team record requires 13 fields: " + record);
    }
    setTeamId(FileManager::toInt(fields[0]));
    setName(fields[1]);
    setParish(fields[2]);
    setRegistrationNumber(fields[3]);
    squadSize = FileManager::toInt(fields[4]);
    setLeagueStatus(fields[5]);
    points = FileManager::toInt(fields[6]);
    matchesPlayed = FileManager::toInt(fields[7]);
    wins = FileManager::toInt(fields[8]);
    draws = FileManager::toInt(fields[9]);
    losses = FileManager::toInt(fields[10]);
    goalsFor = FileManager::toInt(fields[11]);
    goalsAgainst = FileManager::toInt(fields[12]);
}
