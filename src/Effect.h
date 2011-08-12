#ifndef EFFECT_H
#define EFFECT_H

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Setup.h"
#include "Class.h"
#include "Process.h"
#include "Parameter.h"

class Effect : public Object {
public:

    Effect(float wet = 1.0) { mWet = Parameter::Parameter(wet); }
    virtual ~Effect() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Effect(); }
    static Effect *readEffect(std::istream &is);

    virtual void process(const sample_t* in, sample_t* out, int num);
    virtual void postProcess(const sample_t* in, sample_t* out, int num);

    virtual void keyInput(char c) { }

    friend std::ostream &operator<<(std::ostream &os, const Effect &b)
     {return b.write(os);}
    friend std::istream &operator>>(std::istream &is, Effect &b)
     {return b.read(is);}

protected:

    static Class cls;

    Parameter mWet; 

    virtual std::istream &read(std::istream &);
    virtual std::ostream &write(std::ostream &) const;
};

#endif
