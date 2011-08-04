#include "Modifier.h"

using namespace std;

istream &Modifier::read(istream &is) {

    Effect::read(is);
    is >> mVal;
    return is;
}

ostream &Modifier::write(ostream &os) const {

    Effect::write(os);
    os << mVal << " ";
    return os;
}

