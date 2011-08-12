#ifndef PARAMETER_H
#define PARAMETER_H

#include <iostream>
#include <stdlib.h>
#include "Class.h"

class Parameter : public Object {
public:

    Parameter(float val = 0) : mVal(val) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Parameter(); }
    static Parameter *checkConstant(std::string *val); 
    static Parameter *readParameter(std::istream &is);

    virtual float getVal() { return mVal; }
    virtual float setVal(float val) { mVal = val; }

    friend std::ostream &operator<<(std::ostream &os, const Parameter &b)
     {return b.write(os);}
    friend std::istream &operator>>(std::istream &is, Parameter &b)
     {return b.read(is);}

protected:

    static Class cls;

    double mVal;

    virtual std::istream &read(std::istream &);
    virtual std::ostream &write(std::ostream &) const;
};

#endif
