#ifndef FOOTBALLTEAM_H
#define FOOTBALLTEAM_H

#include <string>
#include <vector>
#include "Storable.h"
#include "Player.h"
#include "Coach.h"

class FootballTeam : public Storable {
private:
    int teamId;
    std::string name;
    std::string parish;
    std::string registrationNumber;
    int squadSize;
    std::string leagueStatus; // "Registered", "Unregistered", "Suspended"

    std::vector<Player> players;
    std::vector<Coach> coaches;

    // League standings statistics
    int points;
    int matchesPlayed;
    int wins;
    int draws;
    int losses;
    int goalsFor;
    int goalsAgainst;

public:
    FootballTeam();
    FootballTeam(int id, const std::string& teamName, const std::string& teamParish,
                 const std::string& regNumber, const std::string& status = "Unregistered");

    // Accessors
    int getTeamId() const;
    std::string getName() const;
    std::string getParish() const;
    std::string getRegistrationNumber() const;
    int getSquadSize() const;
    std::string getLeagueStatus() const;
    bool isEligibleForFixture() const;

    int getPoints() const;
    int getMatchesPlayed() const;
    int getWins() const;
    int getDraws() const;
    int getLosses() const;
    int getGoalsFor() const;
    int getGoalsAgainst() const;
    int getGoalDifference() const;

    const std::vector<Player>& getPlayers() const;
    const std::vector<Coach>& getCoaches() const;

    // Mutators with validation
    void setTeamId(int id);
    void setName(const std::string& newName);
    void setParish(const std::string& newParish);
    void setRegistrationNumber(const std::string& regNumber);
    void setLeagueStatus(const std::string& newStatus);

    void setStats(int pts, int played, int w, int d, int l, int gf, int ga);

    // Player and Coach Management
    void addPlayer(const Player& player);
    bool removePlayer(int playerId);
    Player* findPlayer(int playerId);
    const Player* findPlayer(int playerId) const;
    bool updatePlayer(const Player& player);

    void addCoach(const Coach& coach);
    bool removeCoach(int coachId);
    Coach* findCoach(int coachId);
    const Coach* findCoach(int coachId) const;
    bool updateCoach(const Coach& coach);

    // League Operations
    void recordMatchResult(int scored, int conceded);
    void resetStats();

    // Display
    void displayInformation() const;
    void displayRoster() const;

    // Storable interface methods
    virtual std::string toRecord() const override;
    virtual void fromRecord(const std::string& record) override;
};

#endif // FOOTBALLTEAM_H
