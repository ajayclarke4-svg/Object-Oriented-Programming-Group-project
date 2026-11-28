#ifndef STORABLE_H
#define STORABLE_H

#include <string>

class Storable {
public:
    virtual ~Storable() {}
    virtual std::string toRecord() const = 0;
    virtual void fromRecord(const std::string& record) = 0;
};

#endif