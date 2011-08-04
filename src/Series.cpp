#include "Series.h"

using namespace std;

Class Series::cls(string("Series"), newInstance);

void Series::process(const sample_t* in, sample_t* out, int num) {
    const sample_t* from = in;
    sample_t* to = mEffects.size() % 2 ? out : mBuffer;

    for (int i = 0; i < mEffects.size(); i++) {
        mEffects[i]->process(from, to, num);
        from = to;
        to = from == out ? mBuffer : out;
    }

    postProcess(in, out, num);
}


istream &Series::read(istream &is) {

    Effect::read(is);    
    EffectsList::read(is);

    return is;
}

ostream &Series::write(ostream &os) const {

    Effect::write(os);
    EffectsList::write(os);

    return os;
}
