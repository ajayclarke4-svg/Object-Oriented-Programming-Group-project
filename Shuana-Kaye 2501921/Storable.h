#ifndef STORABLE_H
#define STORABLE_H

#include <string>
// Storable and Person holds base methods that allows you to write to a files 
class Storable {
public:
    virtual ~Storable() {}
    virtual string toRecord() = 0;
    virtual void fromRecord() = 0;
};

#endif