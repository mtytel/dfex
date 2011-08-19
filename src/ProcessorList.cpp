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

#include "ProcessorList.h"
#include "Series.h"

using namespace rapidxml;
using namespace std;

Class ProcessorList::cls(std::string("ProcessorList"), newInstance);

void ProcessorList::addProcessor(Processor* p) {
    mProcessors.push_back(p);
}

void ProcessorList::readWaveModifier(xml_node<> &inode, vector<Series*> *fx) {

}

xml_node<> &ProcessorList::read(xml_node<> &inode) {
/*
    Effect::read(is);
    string tok;
    
    vector<Series*> *fx = new vector<Series*>();

    for (is >> tok; tok == CONT; is >> tok) {
        Series *ser = new Series();
        ser->addProcessor(readProcessor(is));
        fx->push_back(ser);
    }

    if (fx->size() == 0) {
        int numProcessor = atoi(tok.c_str());
        if (numProcessor == 0) {
            cerr << "Expected effects list or number, found: " << tok << endl;
            exit(1);
        }

        for (int i = 0; i < numProcessor; i++) {
            Series *ser = new Series();
            ser->addProcessor(new Processor());
            fx->push_back(ser);
        }
    }

    for (is >> tok; tok == MOD; is >> tok)
        readWaveModifier(is, fx);

    for (int i = 0; i < fx->size(); i++) 
        addProcessor((*fx)[i]);
*/
    return inode;
}

xml_node<> &ProcessorList::write(xml_node<> &onode) const {
/*
    Effect::write(os);

    for (int i = 0; i < mProcessors.size(); i++)
        os << CONT << " " << mProcessors[i] << endl;
    
    os << END << endl;
    */
    return onode;
}

