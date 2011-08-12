#ifndef WAVEMAKER_H
#define WAVEMAKER_H

#include <math.h>
#include <stdlib.h>
#include "Setup.h"

#define PI 3.141529

typedef double(*waveFunction)(double);

class WaveMaker {
public:

    enum {kOn, kOff, kSine, kCos, kSquare, kSawRise, kSawFall};

    static sample_t* createWave(int, int, float, float, int offset = 0);
    static waveFunction getFunction(int type);

protected:

    static double on(double val) { return 1; }
    static double off(double val) { return 0; }
    static double sine(double val);
    static double cosine(double val);
    static double square(double val);
    static double sawRise(double val);
    static double sawFall(double val);
};

#endif
