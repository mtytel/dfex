#include "Switch.h"

using namespace std;

Class Switch::cls(string("Switch"), newInstance);
const string Switch::mappings[NUMEFFECTS] = {
 "123\tqwaszx",
 "45678ertyuidfghjcvbn",
 "90-=op[]\\kl;'\nm,./"};

void Switch::process(const sample_t* in, sample_t* out, int num) {
    
    mEffects[mCur]->process(in, out, num);
    
    for (int i = 0; i < num; i++)
        out[i] = out[i] * mWet + in[i] * (1 - mWet);

    postProcess(in, out, num);
}

void Switch::keyInput(char c) {

    for (int i = 0; i < NUMEFFECTS; i++) {
        if (mappings[i].find(c) != -1)
            mCur = i;
    }
}

istream &Switch::read(istream &is) {

    Effect::read(is); 
    string cont;
    int i = 0;

    for (is >> cont; cont == CONT && i < NUMEFFECTS; is >> cont, i++)
        mEffects[i] = Effect::readEffect(is);

    return is;
}

ostream &Switch::write(ostream &os) const {

    Effect::write(os);
    os << endl;
    //FIXME
    for (int i = 0; i < NUMEFFECTS; i++)
        os << "- " << mEffects[i];
    os << END << endl;

    return os;
}

