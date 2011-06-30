/* Effect.h - super class for all effects
 * Author: Matthew Tytel
 */

#ifndef EFFECT_H
#define EFFECT_H

#include <jack/jack.h>
#include <string.h>
#include <iostream>
#include "Class.h"

#define MAXBUFFER 1024

typedef jack_default_audio_sample_t sample_t;

class Effect : public Object {
public:

    Effect() : mWet(1.0), mInputEnabled(1) { }
    virtual ~Effect() { }

    static Effect* readEffect(std::istream &is);
    static sample_t linearInterpolate(sample_t, sample_t, float);

    virtual void process(const sample_t* in, sample_t* out, int num){
        memcpy(out, in, num * sizeof(sample_t));
    }

    void setWet(float wet) { mWet = wet; }
    virtual void input(char c) { }
    void setInputEnabled(char en) { mInputEnabled = en; } 

    friend std::ostream &operator<<(std::ostream &os, const Effect &b)
     {return b.Write(os);}
    friend std::istream &operator>>(std::istream &is, Effect &b)
     {return b.Read(is);}

protected:
    float mWet; 
    static int indent;
    char mInputEnabled;

    //After the class is determined, then read/write data
    virtual std::istream &Read(std::istream &);
    virtual std::ostream &Write(std::ostream &) const;
};

#endif
