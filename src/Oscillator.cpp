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

#include "Oscillator.h"

using namespace rapidxml;
using namespace std;

Class Oscillator::cls(std::string("Oscillator"), newInstance);

void Oscillator::process(const sample_t* in, sample_t* out, int num) {
    sample_t fpc[num], max[num], min[num];
    mFPC->process(in, fpc, num);
    mMax->process(in, max, num);
    mMin->process(in, min, num);

    for (int i = 0; i < num; i ++) {
        float val = mWaveFunc(1.0 * mOffset++ / fpc[i]);
        out[i] = val * max[i] + (1 - val) * min[i];

        if (mOffset >= fpc[i])
            mOffset -= fpc[i];
    }
}

void Oscillator::setWave(int wave) {

    mWaveFunc = WaveMaker::getFunction(wave);
}

void Oscillator::setFPC(float fpc) { 
    free(mFPC);
    mFPC = new Constant(fpc); 
}

xml_node<> &Oscillator::read(xml_node<> &inode) {
    int wave;
    wave = atof(inode.first_attribute("wave")->value());
    setWave(wave);

    free(mFPC);
    mFPC = tryReadProcessor(inode, "fpc", DEFAULTFPC);
    free(mMin);
    mMin = tryReadProcessor(inode, "min", DEFAULTMIN);
    free(mMax);
    mMax = tryReadProcessor(inode, "max", DEFAULTMAX);

    return inode;
}

xml_node<> &Oscillator::write(xml_node<> &onode) const {

    return onode;
}

