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

#include "Aliaser.h"

using namespace rapidxml;
using namespace std;

Class Aliaser::cls(string("Aliaser"), newInstance);

void Aliaser::process(const sample_t* in, sample_t* out, int num) {

    sample_t period[num];
    mPeriod->process(in, period, num);

    for (int i = 0; i < num; i++) {

        if (++mOffset >= period[i]) { 
            mCurSamp = in[i];
            mOffset = 0;
        }
        out[i] = mCurSamp;
    }

    postProcess(in, out, num);
}

xml_node<> &Aliaser::read(xml_node<> &inode) {
    
    Effect::read(inode);

    free(mPeriod);
    mPeriod = Processor::tryReadProcessor(inode, "period", DEFAULTPERIOD);

    return inode;
}

xml_node<> &Aliaser::write(xml_node<> &onode) const {
    
    return onode;
}
