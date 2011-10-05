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

#include "Switch.h"

using namespace std;
using namespace rapidxml;

Class Switch::cls(string("Switch"), newInstance);

void Switch::process(const sample_t* in, sample_t* out, int num) {

    sample_t silent[num], buffer[num];
    memset(silent, 0, num * sizeof(sample_t));

    sample_t cur[num];
    mController->process(in, cur, num);

    uint val = fmin(cur[num - 1], mProcessors.size() - 1);
    mProcessors[val]->process(in, out, num);

    for (uint p = 0; p < mProcessors.size(); p++) {
        if (p != val) {
            mProcessors[p]->process(silent, buffer, num);
            Process::combine(buffer, out, num);
        }
    }

    postProcess(in, out, num);
}

xml_node<> &Switch::read(xml_node<> &inode) {

    ProcessorList::read(inode);
    delete mController;
    mController = Processor::tryReadProcessor(inode, "control", DEFAULTCONTROL);

    return inode;
}

xml_node<> &Switch::write(xml_node<> &onode) const {

    return onode;
}

