#ifndef SERIES_H
#define SERIES_H

#include "Effect.h"

#define CONT "-"
#define END "end"

class Series : public Effect {
public:

    Series() : mFirst(0), mNext(0), Effect::Effect() { }
    ~Series() { }

    static Object *newInstance() { return new Series(); }
    const Class *GetClass() const { return &cls; }

    void process(const sample_t* in, sample_t* out, int num);
    void setFirst(Effect *first) { mFirst = first; }
    void setNext(Effect *next) { mNext = next; }

protected:

    static Class cls;

    Effect *mFirst;
    Effect *mNext;
    sample_t mBuffer[MAXBUFFER];

    std::istream &Read(std::istream &);
    std::ostream &Write(std::ostream &) const;
};

#endif
