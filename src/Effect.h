#ifndef EFFECT_H
#define EFFECT_H

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Setup.h"
#include "Class.h"
#include "Process.h"

class Effect : public Object {
public:

    Effect() : mWet(1.0) { }
    virtual ~Effect() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Effect(); }
    static Effect* readEffect(std::istream &is);

    virtual void process(const sample_t* in, sample_t* out, int num);
    virtual void postProcess(const sample_t* in, sample_t* out, int num);

    void setWet(float wet) { mWet = wet; }
    virtual void keyInput(char c) { }

    friend std::ostream &operator<<(std::ostream &os, const Effect &b)
     {return b.write(os);}
    friend std::istream &operator>>(std::istream &is, Effect &b)
     {return b.read(is);}

protected:

    static Class cls;

    float mWet; 

    virtual std::istream &read(std::istream &);
    virtual std::ostream &write(std::ostream &) const;
};

#endif
