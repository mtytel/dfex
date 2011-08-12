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

#include "Effect.h"

using namespace std;

Class Effect::cls(string("Effect"), newInstance);

Effect* Effect::readEffect(istream &is) {
    
    string clsName;
    is >> clsName;
    
    const Class *eCls = Class::ForName(clsName);
    if (!eCls) {
        cerr << "Error reading configuration: No Effect '" 
         << clsName << "'" << endl;
        exit(1);
    }
    Effect *e = dynamic_cast<Effect *>(eCls->NewInstance());
    is >> *e;

    return e;
}

void Effect::process(const sample_t* in, sample_t* out, int num) {
    memcpy(out, in, num * sizeof(sample_t));
    postProcess(in, out, num);
}

void Effect::postProcess(const sample_t* in, sample_t* out, int num) {
    float wet = mWet.getVal();

    for (int i = 0; i < num; i++)
        out[i] = out[i] * wet + in[i] * (1 - wet);
}

istream &Effect::read(istream &is) {
    
    is >> mWet;
    return is;
}

ostream &Effect::write(ostream &os) const {
    
    os << mWet;
    return os;
}
