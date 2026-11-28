#ifndef MATCHRESULT_H
#define MATCHRESULT_H

#include <iostream>
#include <string>
#include <sstream>
#include "Exceptions.h"
using namespace std;


//  MatchResult — Records the outcome of a fixture
class MatchResult {
private:
    int fixtureId;
    int homeTeamId;
    int awayTeamId;
    int homeScore;
    int awayScore;
    bool isRecorded;
    int winnerTeamId;   

public:
    // Default constructor
    MatchResult() {
        this->fixtureId = 0;
        this->homeTeamId = 0;
        this->awayTeamId = 0;
        this->homeScore = 0;
        this->awayScore = 0;
        this->isRecorded = false;
        this->winnerTeamId = -1;
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
    int getHomeScore() {
        return homeScore;
    }
    int getAwayScore() {
        return awayScore;
    }
    bool getIsRecorded() {
        return isRecorded;
    }
    int getWinnerTeamId() {
        return winnerTeamId;
    }

    // ---- Record the result ----
    // Scores must be >= 0 (business rule)
    void recordResult(int fId, int hId, int aId, int hScore, int aScore) {
        if (hScore < 0) {
            throw NegativeValueException("Home score cannot be negative.");
        }
        if (aScore < 0) {
            throw NegativeValueException("Away score cannot be negative.");
        }
        this->fixtureId = fId;
        this->homeTeamId = hId;
        this->awayTeamId = aId;
        this->homeScore = hScore;
        this->awayScore = aScore;
        this->isRecorded = true;

        // Determine winner
        if (hScore > aScore) {
            this->winnerTeamId = hId;
        } else if (aScore > hScore) {
            this->winnerTeamId = aId;
        } else {
            this->winnerTeamId = -1;  // draw
        }
    }

    // ---- Display ----
    void displayResult(string homeName, string awayName) {
        cout << "=== Match Result ===" << endl;
        if (!isRecorded) {
            cout << "Result not yet recorded." << endl;
            return;
        }
        cout << homeName << " " << homeScore << " - " << awayScore << " " << awayName << endl;
        if (winnerTeamId == -1) {
            cout << "Result: DRAW" << endl;
        } else if (winnerTeamId == homeTeamId) {
            cout << "Winner: " << homeName << endl;
        } else {
            cout << "Winner: " << awayName << endl;
        }
    }

    // ---- File record ----
    string toRecord() {
        stringstream ss;
        ss << fixtureId << "|" << homeTeamId << "|" << awayTeamId << "|"
           << homeScore << "|" << awayScore << "|"
           << (isRecorded ? 1 : 0) << "|" << winnerTeamId;
        return ss.str();
    }

    void fromRecord(string record) {
        stringstream ss(record);
        string token;
        getline(ss, token, '|'); this->fixtureId = stoi(token);
        getline(ss, token, '|'); this->homeTeamId = stoi(token);
        getline(ss, token, '|'); this->awayTeamId = stoi(token);
        getline(ss, token, '|'); this->homeScore = stoi(token);
        getline(ss, token, '|'); this->awayScore = stoi(token);
        getline(ss, token, '|'); this->isRecorded = (stoi(token) == 1);
        getline(ss, token, '|'); this->winnerTeamId = stoi(token);
    }
};

#endif
