#include "Switch.h"

using namespace std;

Class Switch::cls(string("Switch"), newInstance);
const string Switch::mappings[NUMEFFECTS] = {
 "123\tqwaszx",
 "45678ertyuidfghjcvbn",
 "90-=op[]\\kl;'\nm,./"};

void Switch::process(const sample_t* in, sample_t* out, int num) {
    
    mEffects[mCur]->process(in, out, num);
    postProcess(in, out, num);
}

void Switch::keyInput(char c) {

    for (int i = 0; i < NUMEFFECTS; i++) {
        if (mappings[i].find(c) != -1)
            mCur = i;
    }
}

