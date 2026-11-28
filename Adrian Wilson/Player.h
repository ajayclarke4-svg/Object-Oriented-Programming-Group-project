//Player Header File
#ifndef PLAYER_H
#define PLAYER_H
#include "Person.h"
#include "filemanager.h"
#include "Exceptions.h"
#include <string>


// Step 1: the Player's own data only. Inheritance from Person comes next.
class Player : public Person {
private:
    string position;
    int jerseyNumber;
    int goals;
    string playingStatus;
    int teamId;
public:

    Player(){
        position = "?";
        jerseyNumber = 0;
        goals = 0;
        playingStatus = "?";
        teamId = 0;
    }
    Player(string playerPosition, int shirtNumber, int goalsScored, string status, int teamId): Person(0,"?",0,"?"){
        this-> position = playerPosition;
        this-> jerseyNumber = shirtNumber;
        this-> goals = goalsScored;
        this-> playingStatus = status;
        this-> teamId = teamId;
    };

    //Getter 
    string getPosition(){
        return position;
    };
    int getJerseyNumber(){
        return jerseyNumber;
    };
    int getGoals(){
        return goals;
    };
    string getPlayingStatus(){
        return playingStatus;
    };
    int getteamID(){
        return teamId;
    }

    //Setter
    void setPosition(string newPosition){
        if (newPosition.empty()) {
            throw InvalidDataException("Player position cannot be empty.");
        }
        position = newPosition;     
    };
    void setJerseyNumber(int newNumber){
        if (newNumber < 1 || newNumber > 99) {
            throw InvalidDataException("Jersey number must be between 1 and 99. Provided: " + FileManager::toText(newNumber));
        }
        jerseyNumber = newNumber;
    };
    void setPlayingStatus(string newStatus){
        if (newStatus.empty()) {
            throw InvalidDataException("Playing status cannot be empty.");
        }
        playingStatus = newStatus;
        
    };
    void addGoals(int newGoals){
        if (newGoals < 0) {
                throw NegativeValueException("Goals cannot be negative. Provided: " + FileManager::toText(newGoals));
            }
            goals = newGoals;
    };
    void Player::setTeamId(int newTeamId) {
    if (newTeamId < 0) {
            throw InvalidDataException("Team ID cannot be negative.");
        }
        teamId = newTeamId;
    }

    // Output
    void displayInformation(){
        cout << "[Player] ID: " << id
              << " | Name: " << name
              << " | Age: " << age
              << " | Gender: " << gender
              << " | Pos: " << position
              << " | Jersey: #" << jerseyNumber
              << " | Goals: " << goals
              << " | Status: " << playingStatus
              << " | Team ID: " << teamId << endl;
    };

    virtual string toRecord( ) override{
       
    }

    virtual void fromRecord () override{
        string record;
        vector<string> fields = FileManager::splitFields(record);
        if (fields.size() < 9) {
            throw InvalidDataException("Player record requires 9 fields: " + record);
        }
        setTeamId(FileManager::toInt(fields[0]));

        setName(fields[1]);
        
        int a = FileManager::toInt(fields[2]);

        if (a < 18) {
            throw InvalidDataException("Player " + fields[1] + " does not meet minimum age rule.");
        }

        setAge(a);
        setGender(fields[3]);
        setPosition(fields[4]);
        setJerseyNumber(FileManager::toInt(fields[5]));
        addGoals(FileManager::toInt(fields[6]));
        setPlayingStatus(fields[7]);
        setTeamId(FileManager::toInt(fields[8]));
        }

};

#endif
