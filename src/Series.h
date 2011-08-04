#ifndef SERIES_H
#define SERIES_H

#include "EffectsList.h"

class Series : public EffectsList {
public:

    Series() : EffectsList::EffectsList() { }
    ~Series() { }

    static Object *newInstance() { return new Series(); }
    const Class *getClass() const { return &cls; }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    sample_t mBuffer[MAXBUFFER];

    std::istream &read(std::istream &);
    std::ostream &write(std::ostream &) const;
};

#endif
