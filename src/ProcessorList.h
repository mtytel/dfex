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

#ifndef PROCESSORLIST_H
#define PROCESSORLIST_H

#include <vector>
#include <stdlib.h>

#include "WaveMaker.h"
#include "Effect.h"

#define CONT "-"
#define MOD "+"
#define END "end"

class Series;

class ProcessorList : public Effect {
public:

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new ProcessorList(); }

    void addProcessor(Processor* p);
    void initList(rapidxml::xml_node<> &inode);
    void readModifier(rapidxml::xml_node<> &); 
    int size() { return mProcessors.size(); }

protected:

    static Class cls;

    std::vector<Processor*> mProcessors;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
