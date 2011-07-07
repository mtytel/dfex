/* QualityControl.cpp - a bit crush effect
 * Author: Matthew Tytel
 */

#include "QualityControl.h"

using namespace std;

Class QualityControl::cls(string("QualityControl"), newInstance);

void QualityControl::process(const sample_t* in, sample_t* out, int num) {

    for (int i = 0; i < num; i++) {

        if (++mPos > mRatio) { 
            mCurVal = in[i];
            mPos = 0;
        }
        out[i] = mCurVal;
    }
}

istream &QualityControl::Read(istream &is) {

    Effect::Read(is);
    is >> mRatio;
    
    return is;
}

ostream &QualityControl::Write(ostream &os) const {

    Effect::Write(os);
    os << mRatio << endl;

    return os;
}
