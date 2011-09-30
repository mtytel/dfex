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

#include "Controller.h"

using namespace rapidxml;
using namespace std;

Class Controller::cls(std::string("Controller"), newInstance);
const string Controller::mappings[3] = {
 "123\tqwaszx",
 "45678ertyuidfghjcvbn",
 "90-=op[]\\kl;'\nm,./"};

void Controller::process(const sample_t* in, sample_t* out, int num) {
    sample_t rate[num], max[num], min[num];
    mRate->process(in, rate, num);
    mMax->process(in, max, num);
    mMin->process(in, min, num);

    for (int i = 0; i < num; i ++) {
        out[i] = mCur;
        mCur += mDir * rate[i] / 48000.0;
        mCur = min[i] > mCur ? min[i] : mCur;
        mCur = max[i] < mCur ? max[i] : mCur;
    }
}

void Controller::keyInput(char c) {

    for (int i = 0; i < 3; i++) {
        if (mappings[i].find(c) != string::npos)
            mDir = i - 1;
    }
}

xml_node<> &Controller::read(xml_node<> &inode) {
    free(mRate);
    mRate = tryReadProcessor(inode, "rate", DEFAULTRATE);
    free(mMin);
    mMin = tryReadProcessor(inode, "min", DEFAULTMIN);
    free(mMax);
    mMax = tryReadProcessor(inode, "max", DEFAULTMAX);

    return inode;
}

xml_node<> &Controller::write(xml_node<> &onode) const {

    return onode;
}

