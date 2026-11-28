#ifndef MATCHOFFICIAL_H
#define MATCHOFFICIAL_H

#pragma once
#include <string>
#include "Person.h"
using namespace std;

class MatchOfficial : public Person {
    private:
        string officiatingRole;
        string rank;
        bool Available;
    public:
    // Default constructor
        MatchOfficial(){
            officiatingRole = "";
            rank = "";
            Available = false;
        };
    // Parameterized constructor
        MatchOfficial(string officiatingRole, string rank, bool Available){
            this->officiatingRole = officiatingRole;
            this->rank = rank;
            this->Available = Available;
        };
    // Copy constructor
        MatchOfficial(const MatchOfficial& MO){
            this->officiatingRole = MO.officiatingRole;
            this->rank = MO.rank;
            this->Available = MO.Available;
        };

       //Mutators
        void setOfficiatingRole(string officiatingRole){
            this->officiatingRole = officiatingRole;
        };
        void setRank(string rank){
            this->rank = rank;
        };
        void setAvailable(bool Available){
            this->Available = Available;
        };

        //Accessors
        string getOfficiatingRole(){
            return officiatingRole;
        };
        string getRank(){
            return rank;
        };
        bool getAvailable(){
            return Available;
        };
};

#endif // MATCHOFFICAL_H