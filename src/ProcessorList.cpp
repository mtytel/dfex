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
#include "Oscillator.h"
#include "Series.h"

using namespace rapidxml;
using namespace std;

Class ProcessorList::cls(std::string("ProcessorList"), newInstance);

void ProcessorList::addProcessor(Processor* p) {

    mProcessors.push_back(p);
}

void ProcessorList::readList(xml_node<> &inode, vector<Series*> *procs) {
    
    xml_node<> *pList = inode.first_node("processors");
    if (pList) {
        for (xml_node<> *proc = pList->first_node(); proc;
         proc = proc->next_sibling()) {
            Series *s = new Series();
            Processor *p = Processor::readProcessor(*proc);
            s->addProcessor(p);
            procs->push_back(s);
        }
    }
    else {
        xml_node<> *sizeNode = inode.first_node("size");

        if (!sizeNode) {
            cerr << "Expected size or processors tag in ProcessorsList" << endl;
            exit(1);
        }

        int size = atof(sizeNode->value());
        for (int i = 0; i < size; i++)
            procs->push_back(new Series());
    }
}

void ProcessorList::loadAllModifications(xml_node<> &node, int length, 
 vector<pair<xml_node<> *, Oscillator*> > *mods) {

    xml_node<> *next;

    for (xml_node<> *chi = node.first_node(); chi; chi = chi->next_sibling()) {
        if (chi->first_attribute("mod")) {
            Oscillator *o = new Oscillator();
            *chi->first_node() >> *o;
            o->setFPC(length);
            mods->push_back(pair<xml_node<>*, Oscillator*>(chi, o)); 
            chi->remove_all_nodes();
        }
        else
            loadAllModifications(*chi, length, mods);
    }
}

void ProcessorList::readModifier(xml_node<> &inode, vector<Series*> *procs) {

    vector<pair<xml_node<>*, Oscillator*> > mods;
    loadAllModifications(inode, procs->size(), &mods);
    xml_document<> doc;

    sample_t vals[mods.size()][procs->size()], blank[procs->size()];

    for (int m = 0; m < mods.size(); m++)
        mods[m].second->process(blank, vals[m], procs->size());

    for (int p = 0; p < procs->size(); p++) {
        for (int m = 0; m < mods.size(); m++) {
            ostringstream buffer;
            buffer << vals[m][p];
            char *val = doc.allocate_string(buffer.str().c_str());
            mods[m].first->value(val);
        }

        (*procs)[p]->addProcessor(Processor::readProcessor(inode));
    }

    for (int i = 0; i < mods.size(); i++)
        free(mods[i].second);
}

xml_node<> &ProcessorList::read(xml_node<> &inode) {

    Effect::read(inode);
    vector<Series*> procs;
    readList(inode, &procs);

    xml_node<> *mList = inode.first_node("modifiers");
    if (mList) {
        for (xml_node<> *modNode = mList->first_node(); modNode; 
         modNode = modNode->next_sibling())
            readModifier(*modNode, &procs);
    }

    for (int i = 0; i < procs.size(); i++)
        addProcessor(procs[i]);

    return inode;
}

xml_node<> &ProcessorList::write(xml_node<> &onode) const {

    return onode;
}

