#ifndef STUTTER_H
#define STUTTER_H

#include <stdlib.h>
#include <math.h>
#include "Modifier.h"
#include "EffectsList.h"

#define MEMORYSIZE 480000

class Stutter : virtual public EffectsList, virtual public Modifier {
public:

    Stutter() : mSingle(0), mOffset(0), mCycleOffset(0), Modifier::Modifier() {
        memset(mMemory, 0, MEMORYSIZE * 2 * sizeof(sample_t));
        memset(mBuffer, 0, MAXBUFFER * sizeof(sample_t));
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Stutter(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setOffset(int offset) { mOffset = offset % MEMORYSIZE; }

protected:

    static Class cls;

    sample_t mMemory[MEMORYSIZE * 2];
    sample_t mBuffer[MAXBUFFER];
    int mSingle;
    long mOffset, mCycleOffset;

    virtual std::istream &read(std::istream &);
    virtual std::ostream &write(std::ostream &) const;
};

#endif
