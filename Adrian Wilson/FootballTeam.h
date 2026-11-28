#ifndef FOOTBALLTEAM_H
#define FOOTBALLTEAM_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Player.h"
#include "Coach.h"
using namespace std;

// ============================================================
//  FootballTeam — Aggregates Players and Coaches
//  Tracks team standings in the league.
// ============================================================
class FootballTeam {
private:
    int teamId;
    string name;
    string parish;
    string registrationNumber;
    string leagueStatus;    // "Registered", "Suspended", "Unregistered"

    vector<Player> players;
    vector<Coach> coaches;

    // League standing statistics
    int points;
    int matchesPlayed;
    int wins;
    int draws;
    int losses;
    int goalsFor;
    int goalsAgainst;

public:
    // Default constructor
    FootballTeam() {
        this->teamId = 0;
        this->name = "?";
        this->parish = "?";
        this->registrationNumber = "?";
        this->leagueStatus = "Unregistered";
        this->points = 0;
        this->matchesPlayed = 0;
        this->wins = 0;
        this->draws = 0;
        this->losses = 0;
        this->goalsFor = 0;
        this->goalsAgainst = 0;
    }

    // Parameterised constructor
    FootballTeam(int id, string teamName, string teamParish,
                 string regNumber, string status) {
        if (teamName.empty()) {
            throw InvalidDataException("Team name cannot be empty.");
        }
        if (regNumber.empty()) {
            throw InvalidDataException("Registration number cannot be empty.");
        }
        if (status != "Registered" && status != "Suspended" && status != "Unregistered") {
            throw InvalidDataException("League status must be Registered, Suspended, or Unregistered.");
        }
        this->teamId = id;
        this->name = teamName;
        this->parish = teamParish;
        this->registrationNumber = regNumber;
        this->leagueStatus = status;
        this->points = 0;
        this->matchesPlayed = 0;
        this->wins = 0;
        this->draws = 0;
        this->losses = 0;
        this->goalsFor = 0;
        this->goalsAgainst = 0;
    }

    // ---- Getters ----
    int getTeamId() {
        return teamId;
    }
    string getName() {
        return name;
    }
    string getParish() {
        return parish;
    }
    string getRegistrationNumber() {
        return registrationNumber;
    }
    string getLeagueStatus() {
        return leagueStatus;
    }
    int getPoints() {
        return points;
    }
    int getMatchesPlayed() {
        return matchesPlayed;
    }
    int getWins() {
        return wins;
    }
    int getDraws() {
        return draws;
    }
    int getLosses() {
        return losses;
    }
    int getGoalsFor() {
        return goalsFor;
    }
    int getGoalsAgainst() {
        return goalsAgainst;
    }
    int getGoalDifference() {
        return goalsFor - goalsAgainst;
    }
    vector<Player>& getPlayers() {
        return players;
    }
    vector<Coach>& getCoaches() {
        return coaches;
    }

    // ---- Setters ----
    void setName(string newName) {
        if (newName.empty()) {
            throw InvalidDataException("Team name cannot be empty.");
        }
        this->name = newName;
    }
    void setParish(string newParish) {
        this->parish = newParish;
    }
    void setLeagueStatus(string newStatus) {
        if (newStatus != "Registered" && newStatus != "Suspended" && newStatus != "Unregistered") {
            throw InvalidDataException("League status must be Registered, Suspended, or Unregistered.");
        }
        this->leagueStatus = newStatus;
    }

    // ---- Business rule: eligibility check ----
    // A team is eligible to play only if it is Registered
    bool isEligibleForFixture() {
        return leagueStatus == "Registered";
    }

    // ---- Player management ----
    void addPlayer(Player p) {
        // Check for duplicate jersey number within the team
        for (int i = 0; i < (int)players.size(); i++) {
            if (players[i].getJerseyNumber() == p.getJerseyNumber()) {
                throw DuplicateEntryException("Jersey number " + to_string(p.getJerseyNumber()) + " is already taken in this team.");
            }
        }
        players.push_back(p);
    }

    void removePlayer(int playerId) {
        for (int i = 0; i < (int)players.size(); i++) {
            if (players[i].getId() == playerId) {
                players.erase(players.begin() + i);
                return;
            }
        }
        throw PlayerNotFoundException("Player with ID " + to_string(playerId) + " not found in team.");
    }

    Player* findPlayer(int playerId) {
        for (int i = 0; i < (int)players.size(); i++) {
            if (players[i].getId() == playerId) {
                return &players[i];
            }
        }
        return nullptr;
    }

    // ---- Coach management ----
    void addCoach(Coach c) {
        coaches.push_back(c);
    }

    void removeCoach(int coachId) {
        for (int i = 0; i < (int)coaches.size(); i++) {
            if (coaches[i].getId() == coachId) {
                coaches.erase(coaches.begin() + i);
                return;
            }
        }
        throw InvalidDataException("Coach with ID " + to_string(coachId) + " not found in team.");
    }

    // ---- League standing update ----
    // Called after each match to update standings
    // Rule: Win = 3 pts, Draw = 1 pt, Loss = 0 pts
    void recordMatchResult(int scored, int conceded) {
        if (scored < 0) {
            throw NegativeValueException("Goals scored cannot be negative.");
        }
        if (conceded < 0) {
            throw NegativeValueException("Goals conceded cannot be negative.");
        }
        matchesPlayed++;
        goalsFor += scored;
        goalsAgainst += conceded;

        if (scored > conceded) {
            wins++;
            points += 3;
        } else if (scored == conceded) {
            draws++;
            points += 1;
        } else {
            losses++;
        }
    }

    // ---- Display ----
    void displayTeamInfo() {
        cout << "=== Team Information ===" << endl;
        cout << "ID                  : " << teamId << endl;
        cout << "Name                : " << name << endl;
        cout << "Parish              : " << parish << endl;
        cout << "Registration No.    : " << registrationNumber << endl;
        cout << "League Status       : " << leagueStatus << endl;
        cout << "Players Registered  : " << players.size() << endl;
        cout << "Coaches Registered  : " << coaches.size() << endl;
    }

    void displayStandings() {
        cout << "=== Team Standings ===" << endl;
        cout << "Team              : " << name << endl;
        cout << "Matches Played    : " << matchesPlayed << endl;
        cout << "Wins              : " << wins << endl;
        cout << "Draws             : " << draws << endl;
        cout << "Losses            : " << losses << endl;
        cout << "Goals For         : " << goalsFor << endl;
        cout << "Goals Against     : " << goalsAgainst << endl;
        cout << "Goal Difference   : " << getGoalDifference() << endl;
        cout << "Points            : " << points << endl;
    }

    void displayPlayers() {
        cout << "=== Players of " << name << " ===" << endl;
        if (players.empty()) {
            cout << "No players registered." << endl;
            return;
        }
        for (int i = 0; i < (int)players.size(); i++) {
            players[i].displayInformation();
            cout << "--------------------------" << endl;
        }
    }

    void displayCoaches() {
        cout << "=== Coaches of " << name << " ===" << endl;
        if (coaches.empty()) {
            cout << "No coaches registered." << endl;
            return;
        }
        for (int i = 0; i < (int)coaches.size(); i++) {
            coaches[i].displayInformation();
            cout << "--------------------------" << endl;
        }
    }

    // ---- File record ----
    string toRecord() {
        stringstream ss;
        ss << teamId << "|" << name << "|" << parish << "|"
           << registrationNumber << "|" << leagueStatus << "|"
           << points << "|" << matchesPlayed << "|" << wins << "|"
           << draws << "|" << losses << "|" << goalsFor << "|" << goalsAgainst;
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->teamId = stoi(token);
        getline(ss, this->name, '|');
        getline(ss, this->parish, '|');
        getline(ss, this->registrationNumber, '|');
        getline(ss, this->leagueStatus, '|');
        getline(ss, token, '|'); this->points = stoi(token);
        getline(ss, token, '|'); this->matchesPlayed = stoi(token);
        getline(ss, token, '|'); this->wins = stoi(token);
        getline(ss, token, '|'); this->draws = stoi(token);
        getline(ss, token, '|'); this->losses = stoi(token);
        getline(ss, token, '|'); this->goalsFor = stoi(token);
        getline(ss, token, '|'); this->goalsAgainst = stoi(token);
    }
};

#endif
