#ifndef PARALLEL_H
#define PARALLEL_H

#include "Effect.h"

class Parallel : public Effect {
public:

    Parallel() : mLeft(0), mRight(0), Effect::Effect() { }
    ~Parallel() {}

    const Class *GetClass() const { return &mClass; }
    static Object *newInstance() { return new Parallel(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setLeft(Effect *left) { mLeft = left; }
    void setRight(Effect *right) { mRight = right; }

protected:

    static Class mClass;

    Effect *mLeft;
    Effect *mRight;
    sample_t mOutRight[MAXBUFFER];

    std::istream &Read(std::istream &);
    std::ostream &Write(std::ostream &) const;
};

#endif
