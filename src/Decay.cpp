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

#include "Decay.h"

using namespace rapidxml;
using namespace std;

Class Decay::cls(std::string("Decay"), Decay::newInstance);

void Decay::process(const sample_t* in, sample_t* out, int num) {

    sample_t decay[num];
    mDecay->process(in, decay, num);
    
    for (int i = 0; i < num; i++) {    
        mCurVal = in[i] * decay[i] + mCurVal * (1 - decay[i]);
        out[i] = mCurVal;
    }
}

xml_node<> &Decay::read(xml_node<> &inode) {

    Processor::read(inode);

    delete mDecay;
    mDecay = tryReadProcessor(inode, "decay", DEFAULTDECAY);

    return inode;
}

xml_node<> &Decay::write(xml_node<> &onode) const {

    return onode;
}

