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

Class Oscillator::cls(std::string("Oscillator"), newInstance);

/*float Oscillator::getVal() {

    float fpc = mFPC->getVal();
    float val = mWaveFunc(1.0 * mOffset++ / fpc);

    if (mOffset >= fpc)
        mOffset -= fpc;

    mVal = val * mMax->getVal() + (1 - val) * mMin->getVal();
    return mVal;
}*/

void Oscillator::setWave(int wave) {

    mWaveFunc = WaveMaker::getFunction(wave);
}

xml_node<> &Oscillator::read(xml_node<> &inode) {
/*
    int wave;
    is >> wave;
    setWave(wave);

    free(mFPC);
    free(mMin);
    free(mMax);
    mFPC = readProcessor(is);
    mMin = readProcessor(is);
    mMax = readProcessor(is);
*/
    return inode;
}

xml_node<> &Oscillator::write(xml_node<> &onode) const {

    //os << mFPC << " " << mMin << " " << mMax << endl;
    return onode;
}

