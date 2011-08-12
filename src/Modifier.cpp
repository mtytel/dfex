#include "Modifier.h"

using namespace std;

istream &Modifier::read(istream &is) {
    
    Effect::read(is);
    free(mPar);
    mPar = Parameter::readParameter(is);
    return is;
}

ostream &Modifier::write(ostream &os) const {
    
    Effect::write(os);
    os << *mPar;
    return os;
}
