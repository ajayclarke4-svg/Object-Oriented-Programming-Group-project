#ifndef FIXTURE_H
#define FIXTURE_H



class Fixture {
    private:
        string date;
        string time;
        string status;
    public:
        Fixture();
        Fixture(string date, string time, string status);
        Fixture(const Fixture& F);
        void setDate(string date);
        void setTime(string time);
        void setStatus(string status);
        string getDate();
        string getTime();
        string getStatus();
};

#endif // FIXTURE_H