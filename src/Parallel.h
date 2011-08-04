#ifndef PARALLEL_H
#define PARALLEL_H

#include "EffectsList.h"

class Parallel : public EffectsList {
public:

    Parallel() : EffectsList::EffectsList() { }
    ~Parallel() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Parallel(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    sample_t mBuffer[MAXBUFFER];

    std::istream &read(std::istream &);
    std::ostream &write(std::ostream &) const;
};

#endif
