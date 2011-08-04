#include "EffectsList.h"
#include "Series.h"

using namespace std;

Class EffectsList::cls(string("EffectsList"), newInstance);

void EffectsList::addEffect(Effect* e) {
    mEffects.push_back(e);
}

void EffectsList::readWaveModifier(istream &is, vector<Series*> *fx) {

    string name;
    int waveType;
    float min, max;
    is >> name >> waveType >> min >> max;

    const Class *cls = Class::ForName(name);
    sample_t* wave = WaveMaker::createWave(waveType, fx->size(), min, max);

    for (int i = 0; i < fx->size(); i++) {
        Modifier *m = dynamic_cast<Modifier*>(cls->NewInstance());
        m->setVal(wave[i]);
        (*fx)[i]->addEffect(m);
    }
}

istream &EffectsList::read(istream &is) {

    Effect *e;
    string tok;
    
    vector<Series*> *fx = new vector<Series*>();

    for (is >> tok; tok == CONT; is >> tok) {
        Series *ser = new Series();
        ser->addEffect(readEffect(is));
        fx->push_back(ser);
    }
    
    if (fx->size() == 0) {
        int numEffects = atoi(tok.c_str());
        if (numEffects == 0) {
            cerr << "Expected effects list or number, found: " << tok << endl;
            exit(1);
        }

        for (int i = 0; i < numEffects; i++) {
            Series *ser = new Series();
            ser->addEffect(new Effect());
            fx->push_back(ser);
        }
    }

    for (is >> tok; tok == MOD; is >> tok)
        readWaveModifier(is, fx);

    for (int i = 0; i < fx->size(); i++) 
        addEffect((*fx)[i]);

    return is;
}

ostream &EffectsList::write(ostream &os) const {

    Effect::write(os);

    for (int i = 0; i < mEffects.size(); i++)
        os << CONT << " " << mEffects[i] << endl;
    
    os << END << endl;
    return os;
}

