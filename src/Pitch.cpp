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

Pitch::Pitch() : Effect::Effect() { 
    mInput = (double*)fftw_malloc(sizeof(double) * BUFFERSIZE); 
    mResult = (fftw_complex*)fftw_malloc(sizeof(fftw_complex) * BUFFERSIZE); 
    mInvResult = (double*)fftw_malloc(sizeof(double) * BUFFERSIZE); 

    mForward = fftw_plan_dft_r2c_1d(BUFFERSIZE, mInput, mResult, FFTW_MEASURE);
    mBackward = fftw_plan_dft_c2r_1d(BUFFERSIZE, mResult, mInvResult,
     FFTW_MEASURE);
}

void Pitch::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {
        mInput[i] = in[i] * (2 - cos(3.1415 * 2 * i / num) / 2);
    }

    fftw_execute(mForward);

    for (int i = num / 2; i >= 0; i--) {
        mResult[i * 2][0] = mResult[i][0];
        mResult[i * 2][1] = mResult[i][1];
        mResult[i][0] = 0;
        mResult[i][1] = 0;
    }

    fftw_execute(mBackward);
    for (int i = 0; i < num; i++)
        out[i] = mInvResult[i] / BUFFERSIZE;
}

xml_node<> &Pitch::read(xml_node<> &inode) {
    
    Effect::read(inode);
    return inode;
}

xml_node<> &Pitch::write(xml_node<> &onode) const {
    
    return onode;
}

