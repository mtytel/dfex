/* StutterUp.h - takes input from one section of time,
 *             then repeats it a given amount of times increasing volume
 *             each iteration.
 * Author: Matthew Tytel
 */

#ifndef STUTTERUP_H
#define STUTTERUP_H

#include <stdlib.h>
#include "Effect.h"

class StutterUp : public Effect {
public:

    StutterUp() : mFPC(1), mOffset(0), mNumStutter(2), mCurStutter(0), 
     Effect::Effect() {
        mMemory = (sample_t*)malloc(sizeof(sample_t));
    }

    ~StutterUp() { free(mMemory); }

    const Class *GetClass() const { return &cls; }
    static Object *newInstance() { return new StutterUp(); }

    void process(const sample_t* in, sample_t* out, int num);
    void setNumStutter(int num) { mNumStutter = num; }
    void setFPC(int fpc);
    void setOffset(int offset) { mOffset = offset % mFPC; }

protected:

    static Class cls;

    sample_t* mMemory;
    jack_nframes_t mFPC; // Frames per cycle
    long mOffset;
    int mNumStutter;
    int mCurStutter;

    std::istream &Read(std::istream &);
    std::ostream &Write(std::ostream &) const;
};

#endif
