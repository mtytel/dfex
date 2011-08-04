#ifndef VOLUME_H
#define VOLUME_H

#include <stdlib.h>
#include "Modifier.h"

class Volume : virtual public Modifier {
public:

    Volume() : Modifier::Modifier(1) { }

    ~Volume() { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new Volume(); }

    void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;
};

#endif
