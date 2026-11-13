#ifndef MATCHRESULT_H
#define MATCHRESULT_H

class MatchResult {
    private:
        int homeScore;
        int awayScore;
    public:
        MatchResult();
        MatchResult(int homeScore, int awayScore);
        MatchResult(const MatchResult& MR);
        void getWinner();
};

#endif // MATCHRESULT_H