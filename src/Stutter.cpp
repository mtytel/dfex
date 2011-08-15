/* 
 * Copyright 2011 Matthew Tytel
 *
 * dfex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dfex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dfex.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Stutter.h"

using namespace std;

Class Stutter::cls(string("Stutter"), newInstance);

void Stutter::process(const sample_t* in, sample_t* out, int num) {

    memset(out, 0, num * sizeof(sample_t));
    int curOffset = mOffset, fpcPrev = round(mFPC->getLastVal()), fpc;
    
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
        int stIndex = (MEMORYSIZE + curOffset - st * fpcPrev) % MEMORYSIZE;

        sample_t fit[num];
        Process::fit(&mMemory[stIndex], fit, num + st * (fpcPrev - fpc), num);

        mEffects[st]->process(fit, mBuffer, num);
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
