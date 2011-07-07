/* StutterExtend.h - takes input from one section of time,
 *             then repeats it a given amount of times increasing volume
 *             each iteration.
 * Author: Matthew Tytel
 */

#ifndef STUTTEREXTEND_H
#define STUTTEREXTEND_H

#include <stdlib.h>
#include "Effect.h"

class StutterExtend : public Effect {
public:

    StutterExtend() : mFPC(1), mOffset(0), mRatio(1), Effect::Effect() {
        mMemory = (sample_t*)malloc(sizeof(sample_t));
    }

    ~StutterExtend() { free(mMemory); }

    const Class *GetClass() const { return &cls; }
    static Object *newInstance() { return new StutterExtend(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setRatio(int ratio) { mRatio = ratio; }
    void setFPC(int fpc);
    void setOffset(int offset) { mOffset = offset % mFPC; }

protected:

    static Class cls;

    sample_t* mMemory;
    jack_nframes_t mFPC; // Frames per cycle
    long mOffset;
    int mRatio;

    std::istream &Read(std::istream &);
    std::ostream &Write(std::ostream &) const;
};

#endif
