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

#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "Setup.h"
#include "Class.h"
#include "Process.h"

class Processor : public Object {
public:

    Processor() { }
    virtual ~Processor() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Processor(); }
    static Processor *readProcessor(rapidxml::xml_node<> &);
    static Processor *tryReadProcessor(rapidxml::xml_node<> &, const char *, 
     float);
    static Processor *createConstant(const char *);

    virtual void process(const sample_t* in, sample_t* out, int num);
    virtual void postProcess(const sample_t* in, sample_t* out, int num) { }

    virtual void keyInput(char c) { }

    friend rapidxml::xml_node<> &operator<<(rapidxml::xml_node<> &onode, 
     const Processor &p) { return p.write(onode); }
    friend rapidxml::xml_node<> &operator>>(rapidxml::xml_node<> &inode, 
     Processor &p) { return p.read(inode); }

protected:

    static Class cls;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
