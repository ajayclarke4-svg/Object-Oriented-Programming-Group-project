#ifndef MATCHOFFICAL_H
#define MATCHOFFICAL_H

class MatchOfficial {
    private:
        string officiatingRole;
        string rank;
        bool Available;
    public:
        MatchOfficial();
        MatchOfficial(string officiatingRole, string rank, bool Available);
        MatchOfficial(const MatchOfficial& MO);
        void setOfficiatingRole(string officiatingRole);
        void setRank(string rank);
        void setAvailable(bool Available);
        string getOfficiatingRole();
        string getRank();
        bool getAvailable();
};

#endif // MATCHOFFICAL_H