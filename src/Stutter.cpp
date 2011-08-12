#include "Stutter.h"

using namespace std;

Class Stutter::cls(string("Stutter"), newInstance);

void Stutter::process(const sample_t* in, sample_t* out, int num) {

    memset(out, 0, num * sizeof(sample_t));
    int curOffset = mOffset, fpc;
    
    for (int i = 0; i < num; i++) {
        fpc = round(mFPC->getVal());

        sample_t val = (mCycleOffset >= fpc && mSingle) ? 0 : in[i];
        mMemory[mOffset] = mMemory[mOffset + MEMORYSIZE] = val;

        if (++mOffset >= MEMORYSIZE)
            mOffset = 0;
        if (++mCycleOffset >= fpc * mEffects.size())
            mCycleOffset = 0;
    }

    for (int st = 0; st < mEffects.size(); st++) {
        int stIndex = (MEMORYSIZE + curOffset - st * fpc) % MEMORYSIZE;
        mEffects[st]->process(&mMemory[stIndex], mBuffer, num);
        Process::combine(mBuffer, out, num);
    }

    postProcess(in, out, num);
}

istream &Stutter::read(istream &is) {

    EffectsList::read(is);
    free(mFPC);
    mFPC = Parameter::readParameter(is);
    is >> mSingle;

    return is;
}

ostream &Stutter::write(ostream &os) const {

    EffectsList::write(os);
    return os;
}
