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

void ProcessorList::readModifier(xml_node<> &inode) {
    
}

void ProcessorList::initList(xml_node<> &inode) {
    
    xml_node<> *pList = inode.first_node("processors");
    if (pList) {
        for (xml_node<> *proc = pList->first_node(); proc;
         proc = proc->next_sibling()) {
            Series *s = new Series();
            Processor *p = Processor::readProcessor(*proc);
            s->addProcessor(p);
            addProcessor(s);
        }
    }
    else {
        xml_node<> *sizeNode = inode.first_node("size");

        if (!sizeNode) {
            cerr << "Expected size or processors tag in ProcessorsList" << endl;
            exit(1);
        }

        int size = atof(sizeNode->value());
        for (int i = 0; i < size; i++) {
            Series *s = new Series();
            s->addProcessor(new Processor());
            addProcessor(s);
        }
    }
}

xml_node<> &ProcessorList::read(xml_node<> &inode) {

    Effect::read(inode);
    initList(inode);

    xml_node<> *mList = inode.first_node("modifiers");
    if (mList) {
        for (xml_node<> *modNode = mList->first_node(); modNode; 
         modNode = modNode->next_sibling())
            readModifier(*modNode);
    }

    return inode;
}

xml_node<> &ProcessorList::write(xml_node<> &onode) const {

    return onode;
}

