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

#include "Harmonizer.h"

using namespace rapidxml;
using namespace std;

Class Harmonizer::cls(string("Harmonizer"), newInstance);

void Harmonizer::process(const sample_t* in, sample_t* out, int num) {

    sample_t root[num];
    mRoot->process(in, root, num);

    for (int i = 0; i < num; i++)
        out[i] = root[i] / round(in[i]);

    postProcess(in, out, num);
}

xml_node<> &Harmonizer::read(xml_node<> &inode) {
    
    Effect::read(inode);

    delete mRoot;
    mRoot = Processor::tryReadProcessor(inode, "root", DEFAULTROOT);

    return inode;
}

xml_node<> &Harmonizer::write(xml_node<> &onode) const {
    
    return onode;
}

