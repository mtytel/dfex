#include "Stutter.h"

using namespace std;

Class Stutter::cls(string("Stutter"), newInstance);

void Stutter::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {
        if (mCurStutter) 
            out[i] = mMemory[mOffset];
        else
            out[i] = mMemory[mOffset] = in[i];

        if (++mOffset >= mFPC) {
            mOffset = 0;
            mCurStutter = (mCurStutter + 1) % mNumStutter;
        }

        out[i] = out[i] * mWet + in[i] * (1 - mWet);
    }
}

void Stutter::setFPC(int fpc) {

    mFPC = fpc;
    mMemory = (sample_t*)realloc(mMemory, fpc * sizeof(sample_t));
}

istream &Stutter::Read(istream &is) {

    Effect::Read(is);
    is >> mFPC >> mNumStutter;
    setFPC(mFPC);
    
    return is;
}

ostream &Stutter::Write(ostream &os) const {

    Effect::Write(os);
    os << mFPC << ' ' << mNumStutter << endl;

    return os;
}
