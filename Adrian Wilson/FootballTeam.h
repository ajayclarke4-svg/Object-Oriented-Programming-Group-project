

#ifndef FOOTBALLTEAM_H
#define FOOTBALLTEAM_H

#include <string>
#include <vector>
#include "Storable.h"
#include "Player.h"
#include "Coach.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class FootballTeam : public Storable {
private:
    int teamId;
    string name;
    string parish;
    string registrationNumber;
    int squadSize;
    string leagueStatus;

    int points;
    int matchesPlayed;
    int wins;
    int draws;
    int losses;
    int goalsFor;
    int goalsAgainst;

    vector<Player> players;
    vector<Coach> coaches;
public:
    FootballTeam() {
        teamId = 0;
        name = "?";
        parish = "?";
        registrationNumber = "?";
        squadSize = 0;
        leagueStatus = "Unregistered";

        points = 0;
        matchesPlayed = 0;
        wins = 0;
        draws = 0;
        losses = 0;
        goalsFor = 0;
        goalsAgainst = 0;
    }
    FootballTeam(
        int newTeamId,
        string newName,
        string newParish,
        string regNum,
        string status) 
    {
        setTeamId(newTeamId);
        setName(newName);
        setParish(newParish);
        setRegistrationNumber(regNum);
        setLeagueStatus(status);

        squadSize = 0;

        points = 0;
        matchesPlayed = 0;
        wins = 0;
        draws = 0;
        losses = 0;
        goalsFor = 0;
        goalsAgainst = 0;
    }

    //=====================
    // GETTERS
    //=====================

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
    int getSquadSize() {
        return squadSize;
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

    //=====================
    // SETTERS
    //=====================

    void setTeamId(int newId) {

        if (newId < 0) {
            throw InvalidDataException(
                "Team ID cannot be negative.");
        }

        teamId = newId;
    }
    void setName(string newName) {

        if (newName.empty()) {
            throw InvalidDataException(
                "Team name cannot be empty.");
        }

        name = newName;
    }
    void setParish(string newParish) {

        if (newParish.empty()) {
            throw InvalidDataException(
                "Parish cannot be empty.");
        }

        parish = newParish;
    }
    void setRegistrationNumber(string regNum) {

        if (regNum.empty()) {
            throw InvalidDataException(
                "Registration number cannot be empty.");
        }

        registrationNumber = regNum;
    }
    void setLeagueStatus(string status) {

        if (
            status != "Registered" &&
            status != "Unregistered" &&
            status != "Suspended"
        ) {
            throw InvalidDataException(
                "Invalid League Status.");
        }

        leagueStatus = status;
    }

    //=====================
    // PLAYERS
    //=====================

    void addPlayer(Player player) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].getId() == player.getId()) {
                throw InvalidDataException("Player already exists.");
            }
        }
        player.setTeamId(teamId);

        players.push_back(player);

        squadSize = players.size();
    }
    bool removePlayer(int playerId) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].getId() == playerId) {
                players.erase(players.begin() + i);

                squadSize = players.size();
                return true;
            }
        }
        return false;
    }
    Player* findPlayer(int playerId) {
        for (int i = 0; i < players.size(); i++) {
            if (players[i].getId() == playerId) {
                return &players[i];
            }
        }
        return nullptr;
    }

    //=====================
    // COACHES
    //=====================

    void addCoach(Coach coach) {
        for (int i = 0; i < coaches.size(); i++) {
            if (coaches[i].getId() == coach.getId()) {
                throw InvalidDataException("Coach already exists.");
            }
        }
        coach.setTeamId(teamId);

        coaches.push_back(coach);
    }
    bool removeCoach(int coachId) {
        for (int i = 0; i < coaches.size(); i++) {
            if (coaches[i].getId() == coachId) {
                    coaches.erase(
                    coaches.begin() + i);

                return true;
            }
        }
        return false;
    }
    Coach* findCoach(int coachId) {
        for (int i = 0; i < coaches.size(); i++) {
            if (coaches[i].getId()
                == coachId) {

                return &coaches[i];
            }
        }
        return nullptr;
    }

    //=====================
    // TEAM STATS
    //=====================

    void recordMatchResult(int goalsScored, int goalsConceded ) {
        if (
            goalsScored < 0 ||
            goalsConceded < 0
        ) {
            throw NegativeValueException(
                "Goals cannot be negative.");
        }
        matchesPlayed++;
        goalsFor += goalsScored;
        goalsAgainst += goalsConceded;

        if (goalsScored > goalsConceded) {
            wins++;
            points += 3;
        }
        else if (goalsScored == goalsConceded) {
            draws++;
            points += 1;
        }
        else {
            losses++;
        }
    }

    //=====================
    // DISPLAY
    //=====================

    void displayInformation() {

        cout << "\n[TEAM]"
             << "\nID: " << teamId
             << "\nName: " << name
             << "\nParish: " << parish
             << "\nReg#: " << registrationNumber
             << "\nStatus: " << leagueStatus
             << "\nPlayers: " << squadSize
             << "\nPoints: " << points
             << endl;
    }

    //=====================
    // FILE HANDLING
    //=====================

    string toRecord() {
        return
            FileManager::toText(teamId) + "," + name + "," + parish + "," + registrationNumber + "," +
            FileManager::toText(squadSize) + "," + leagueStatus + "," +
            FileManager::toText(points) + "," +
            FileManager::toText(matchesPlayed) + "," +
            FileManager::toText(wins) + "," +
            FileManager::toText(draws) + "," +
            FileManager::toText(losses) + "," +
            FileManager::toText(goalsFor) + "," +
            FileManager::toText(goalsAgainst);
    }

    void fromRecord(string record) {
        vector<string> fields =
            FileManager::splitFields(record);
        if (fields.size() < 13) {
            throw runtime_error(
                "FootballTeam record requires 13 fields.");
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
};

#endif