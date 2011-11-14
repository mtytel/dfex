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
    sample_t period[num], max[num], min[num];
    mPeriod->process(in, period, num);
    mMax->process(in, max, num);
    mMin->process(in, min, num);

    for (int i = 0; i < num; i ++) {
        float val = mWaveFunc(1.0 * mOffset++ / period[i]);
        out[i] = val * max[i] + (1 - val) * min[i];

        if (mOffset >= period[i])
            mOffset -= period[i];
    }
}

void Oscillator::setPeriod(float period) { 

    delete mPeriod;
    mPeriod = new Constant(period); 
}

xml_node<> &Oscillator::read(xml_node<> &inode) {
    mWaveFunc = 
     WaveFunctions::getFunction(inode.first_attribute("wave")->value());

    delete mPeriod;
    mPeriod = readParameter(inode, "period", DEFAULTPERIOD);
    delete mMin;
    mMin = readParameter(inode, "min", DEFAULTMIN);
    delete mMax;
    mMax = readParameter(inode, "max", DEFAULTMAX);

    return inode;
}

xml_node<> &Oscillator::write(xml_node<> &onode) const {

    return onode;
}

