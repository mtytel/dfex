/* Effect.h - super class for all effects
 * Author: Matthew Tytel
 */

#include "Effect.h"

using namespace std;

Effect* Effect::readEffect(istream &is) {
    
    string clsName;
    is >> clsName;
    
    const Class *eCls = Class::ForName(clsName);
    Effect *e = dynamic_cast<Effect *>(eCls->NewInstance());
    is >> *e;

    return e;
}

sample_t Effect::linearInterpolate(sample_t left, sample_t right, float perc) {
    return perc * right + (1 - perc) * left;
}

istream &Effect::Read(istream &is) {
    
    is >> mWet;
    return is;
}

ostream &Effect::Write(ostream &os) const {
    
    os << GetClass()->GetName() << ' ' << mWet << ' '; 
    return os;
}
