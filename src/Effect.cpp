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

istream &Effect::Read(istream &is) {
    
    is >> mWet;
    return is;
}

ostream &Effect::Write(ostream &os) const {
    
    os << GetClass()->GetName() << ' ' << mWet << ' '; 
    return os;
}
