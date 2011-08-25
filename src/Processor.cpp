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

#include "Processor.h"
#include "Constant.h"

using namespace rapidxml;
using namespace std;

Class Processor::cls(string("Processor"), newInstance);

Processor *Processor::createConstant(const char *val) {

    float num = atof(val);

    if (num || val[0] == '0')
        return new Constant(num);
    
    cerr << "Error reading configuration: " << val << 
     " is not a valid Processor" << endl;
    exit(1);
}

Processor* Processor::readProcessor(xml_node<> &inode) {
    
    string clsName = string(inode.name());
    if (clsName.empty())
        return createConstant(inode.value());

    const Class *eCls = Class::ForName(clsName);
    if (!eCls) {
        cerr << "Error reading configuration: No Processor '" 
         << clsName << "'" << endl;
        exit(1);
    }
    Processor *p = dynamic_cast<Processor *>(eCls->NewInstance());
    inode >> *p;

    return p;
}

Processor *Processor::tryReadProcessor(rapidxml::xml_node<> &node, 
 const char *tag, float defaultVal) {

    xml_node<> *found_node = node.first_node(tag);
    if (found_node) 
        return Processor::readProcessor(*found_node->first_node());
    
    return new Constant(defaultVal);
}

void Processor::process(const sample_t* in, sample_t* out, int num) {

    memcpy(out, in, num * sizeof(sample_t));
}

xml_node<> &Processor::read(xml_node<> &inode) {
    
    return inode;
}

xml_node<> &Processor::write(xml_node<> &onode) const {
    
    return onode;
}

