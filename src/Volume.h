#ifndef VOLUME_H
#define VOLUME_H

#include <stdlib.h>
#include "Modifier.h"

class Volume : public Modifier {
public:

    Volume(float vol = 1.0) : Modifier::Modifier(vol) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Volume(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;
};

#endif
