#ifndef EFFECT_H
#define EFFECT_H

#include <jack/jack.h>
#include <string.h>

#define MAXBUFFER 1024

typedef jack_default_audio_sample_t sample_t;

class Effect {
public:

    virtual void process(const sample_t* in, sample_t* out, int num){
        memcpy(out, in, num * sizeof(sample_t));
    }

    Effect(float wet) : mWet(wet) {}
    virtual ~Effect() {}

protected:
    char mOn;
    float mWet; 
};

#endif
