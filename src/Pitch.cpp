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

#include "Pitch.h"

using namespace rapidxml;
using namespace std;

Class Pitch::cls(string("Pitch"), newInstance);

Pitch::Pitch() : Effect::Effect(), mTransformOffset(0) { 
    mInput = (double*)fftw_malloc(sizeof(double) * BUFFERSIZE); 
    mResult = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * BUFFERSIZE); 
    mInvResult = (double*)fftw_malloc(sizeof(double) * BUFFERSIZE); 

    mForward = fftw_plan_dft_r2c_1d(BUFFERSIZE, mInput, mResult, FFTW_MEASURE);
    mBackward = fftw_plan_dft_c2r_1d(BUFFERSIZE, mResult, mInvResult,
     FFTW_MEASURE);
}

Pitch::~Pitch() { 
    fftw_free(mInput); 
    fftw_free(mResult); 
    fftw_free(mInvResult); 

    fftw_free(mForward);
    fftw_free(mBackward);
}

void Pitch::process(const sample_t* in, sample_t* out, int num) {

    memmove(mMemory, mMemory + num, (TRANSFORMSIZE - num) * sizeof(sample_t));
    for (int i = 0; i < num; i++)
        mMemory[TRANSFORMSIZE - num + i] = in[i];

    for (int i = 0; i < TRANSFORMSIZE; i++)
        mInput[i] = mMemory[i] * sin(PI * i / TRANSFORMSIZE);

    fftw_execute(mForward);

    for (int i = TRANSFORMSIZE / 2 - 1; i >= 0; i--) {
        mResult[i * 2][0] = mResult[i][0];
        mResult[i * 2][1] = mResult[i][1];
        mResult[i * 2 + 1][0] = 0;
        mResult[i * 2 + 1][1] = 0;
    }

    fftw_execute(mBackward);
    for (int i = 0; i < num; i++)
        out[num - i - 1] = mInvResult[TRANSFORMSIZE - i - 1] / TRANSFORMSIZE;

    postProcess(in, out, num);
}

xml_node<> &Pitch::read(xml_node<> &inode) {
    
    Effect::read(inode);
    return inode;
}

xml_node<> &Pitch::write(xml_node<> &onode) const {
    
    return onode;
}

