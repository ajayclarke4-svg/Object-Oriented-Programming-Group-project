#ifndef FIXTURE_H
#define FIXTURE_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "MatchResult.h"
using namespace std;


//  Fixture — Represents a scheduled match between two teams
class Fixture {
private:
    int fixtureId;
    int homeTeamId;
    int awayTeamId;
    int stadiumId;
    string date;        // format: "YYYY-MM-DD"
    string time;        // format: "HH:MM"
    string status;      // "Scheduled", "Completed", "Cancelled"
    vector<int> assignedOfficialIds;
    MatchResult matchResult;
    int ticketsSold;

public:
    // Default constructor
    Fixture() {
        this->fixtureId = 0;
        this->homeTeamId = 0;
        this->awayTeamId = 0;
        this->stadiumId = 0;
        this->date = "?";
        this->time = "?";
        this->status = "Scheduled";
        this->ticketsSold = 0;
    }

    // Parameterised constructor
    Fixture(int fId, int homeId, int awayId, int stadId,
            string matchDate, string matchTime) {
        if (homeId == awayId) {
            throw InvalidDataException("Home team and away team cannot be the same.");
        }
        if (matchDate.empty()) {
            throw InvalidDataException("Fixture date cannot be empty.");
        }
        if (matchTime.empty()) {
            throw InvalidDataException("Fixture time cannot be empty.");
        }
        this->fixtureId = fId;
        this->homeTeamId = homeId;
        this->awayTeamId = awayId;
        this->stadiumId = stadId;
        this->date = matchDate;
        this->time = matchTime;
        this->status = "Scheduled";
        this->ticketsSold = 0;
    }

    // ---- Getters ----
    int getFixtureId() {
        return fixtureId;
    }
    int getHomeTeamId() {
        return homeTeamId;
    }
    int getAwayTeamId() {
        return awayTeamId;
    }
    int getStadiumId() {
        return stadiumId;
    }
    string getDate() {
        return date;
    }
    string getTime() {
        return time;
    }
    string getStatus() {
        return status;
    }
    int getTicketsSold() {
        return ticketsSold;
    }
    MatchResult& getMatchResult() {
        return matchResult;
    }
    vector<int>& getAssignedOfficialIds() {
        return assignedOfficialIds;
    }

    // ---- Setters ----
    void setDate(string newDate) {
        if (newDate.empty()) {
            throw InvalidDataException("Date cannot be empty.");
        }
        this->date = newDate;
    }
    void setTime(string newTime) {
        if (newTime.empty()) {
            throw InvalidDataException("Time cannot be empty.");
        }
        this->time = newTime;
    }
    void setStatus(string newStatus) {
        this->status = newStatus;
    }

    // ---- Check if a team is involved in this fixture ----
    bool involvesTeam(int teamId) {
        return homeTeamId == teamId || awayTeamId == teamId;
    }

    // ---- Assign a match official to this fixture ----
    void assignOfficial(int officialId) {
        // Check for duplicate
        for (int i = 0; i < (int)assignedOfficialIds.size(); i++) {
            if (assignedOfficialIds[i] == officialId) {
                throw DuplicateEntryException("Official " + to_string(officialId) + " is already assigned to this fixture.");
            }
        }
        assignedOfficialIds.push_back(officialId);
    }

    // ---- Check if official is already assigned ----
    bool hasOfficial(int officialId) {
        for (int i = 0; i < (int)assignedOfficialIds.size(); i++) {
            if (assignedOfficialIds[i] == officialId) {
                return true;
            }
        }
        return false;
    }

    // ---- Record match result ----
    void recordResult(int homeScore, int awayScore) {
        matchResult.recordResult(fixtureId, homeTeamId, awayTeamId, homeScore, awayScore);
    }

    // ---- Complete the fixture ----
    // Business rule: a result must be recorded before marking complete
    void completeFixture() {
        if (!matchResult.getIsRecorded()) {
            throw FixtureNotCompletedException("Fixture " + to_string(fixtureId) + " has no recorded result yet.");
        }
        this->status = "Completed";
    }

    // ---- Add ticket sales ----
    void addTicketSales(int qty) {
        this->ticketsSold += qty;
    }

    // ---- Display ----
    void displayInformation(string homeName = "", string awayName = "", string stadiumName = "") {
        cout << "=== Fixture Information ===" << endl;
        cout << "Fixture ID   : " << fixtureId << endl;
        cout << "Home Team    : " << (homeName.empty() ? to_string(homeTeamId) : homeName) << endl;
        cout << "Away Team    : " << (awayName.empty() ? to_string(awayTeamId) : awayName) << endl;
        cout << "Stadium      : " << (stadiumName.empty() ? to_string(stadiumId) : stadiumName) << endl;
        cout << "Date         : " << date << endl;
        cout << "Time         : " << time << endl;
        cout << "Status       : " << status << endl;
        cout << "Tickets Sold : " << ticketsSold << endl;
        cout << "Officials    : ";
        if (assignedOfficialIds.empty()) {
            cout << "None assigned";
        } else {
            for (int i = 0; i < (int)assignedOfficialIds.size(); i++) {
                cout << assignedOfficialIds[i];
                if (i + 1 < (int)assignedOfficialIds.size()) cout << ", ";
            }
        }
        cout << endl;
    }

    // ---- File record ----
    string toRecord() {
        stringstream ss;
        ss << fixtureId << "|" << homeTeamId << "|" << awayTeamId << "|"
           << stadiumId << "|" << date << "|" << time << "|" << status << "|" << ticketsSold;
        // Append official IDs separated by ','
        ss << "|";
        for (int i = 0; i < (int)assignedOfficialIds.size(); i++) {
            ss << assignedOfficialIds[i];
            if (i + 1 < (int)assignedOfficialIds.size()) ss << ",";
        }
        // Append match result
        ss << "|" << matchResult.toRecord();
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->fixtureId = stoi(token);
        getline(ss, token, '|'); this->homeTeamId = stoi(token);
        getline(ss, token, '|'); this->awayTeamId = stoi(token);
        getline(ss, token, '|'); this->stadiumId = stoi(token);
        getline(ss, this->date, '|');
        getline(ss, this->time, '|');
        getline(ss, this->status, '|');
        getline(ss, token, '|'); this->ticketsSold = stoi(token);

        // Parse official IDs (comma-separated)
        string officialStr;
        getline(ss, officialStr, '|');
        if (!officialStr.empty()) {
            stringstream oSS(officialStr);
            string oid;
            while (getline(oSS, oid, ',')) {
                if (!oid.empty()) {
                    assignedOfficialIds.push_back(stoi(oid));
                }
            }
        }

        // Parse match result
        string resultRecord;
        getline(ss, resultRecord);
        if (!resultRecord.empty()) {
            matchResult.fromRecord(resultRecord);
        }
    }
};

#endif
