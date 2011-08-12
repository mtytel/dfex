#ifndef EFFECTSLIST_H
#define EFFECTSLIST_H

#include <vector>
#include <stdlib.h>

#include "Modifier.h"
#include "WaveMaker.h"

#define CONT "-"
#define MOD "+"
#define END "end"

class Series;

class EffectsList : public Effect {
public:

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new EffectsList(); }

    void addEffect(Effect* e);
    void createList(Class *cls, int waveType, int num);
    void readWaveModifier(std::istream &is, std::vector<Series*> *fx); 
    int size() { return mEffects.size(); }

protected:

    static Class cls;

    std::vector<Effect*> mEffects;

    std::istream &read(std::istream &);
    std::ostream &write(std::ostream &) const;
};

#endif
