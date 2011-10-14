/* 
 * Copyright 2011 Matthew Tytel
 *
 * dfex is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * dfex is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with dfex.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MIDI_H
#define MIDI_H

#include <stdlib.h>
#include <sys/soundcard.h>
#include <fcntl.h>
#include <boost/thread.hpp>
#include <iostream>

#include "Processor.h"
#include "Constant.h"

#define MIDI_DEVICE "/dev/sequencer"
#define DEFAULTMAX 1
#define DEFAULTMIN 0
#define DEFAULTDECAY 1

class MidiControl;

class MidiStream {
public:

    static void addController(MidiControl *controller);
    static void readMidi();
    static void stream();

protected:
    
    static boost::shared_mutex mutex;
    static boost::thread midiThread;
    static int seqfd;
    static std::vector<MidiControl*> controllers;
};

class MidiControl : public Processor {
public:
    enum { kOff = -1 };

    MidiControl();
    virtual ~MidiControl() { }

    virtual void process(const sample_t* in, sample_t* out, int num);
    void midiInput(unsigned char val);
    virtual void matchedValue(char val) { mVal = val; }

protected:

    sample_t mVal;
    uint mMatches;
    std::vector<unsigned char> mSignal;
    uint mLowBound, mUpBound;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};


class MidiStomp : public MidiControl {
public:

    MidiStomp() : MidiControl(), mToggle(0) { }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new MidiStomp(); }
    void matchedValue(char val);

protected:

    static Class cls;
    int mToggle;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};


class MidiExpression : public MidiControl {
public:
    
    enum { kExp, kLin };

    MidiExpression() : MidiControl(), mMidiMax(0), mMidiMin(0), mScale(0), 
     mCurVal(0) {
        mMin = new Constant(DEFAULTMIN);
        mMax = new Constant(DEFAULTMAX);
        mDecay = new Constant(DEFAULTDECAY);
    }

    ~MidiExpression() {
        delete mMin;
        delete mMax;
        delete mDecay;
    }

    const Class *getClass() const { return &cls; }
    static Object *newInstance() { return new MidiExpression(); }

    virtual void process(const sample_t* in, sample_t* out, int num);

protected:

    static Class cls;

    char mMidiMax, mMidiMin;
    uint mScale;
    sample_t mCurVal;
    Processor *mMax, *mMin, *mDecay;

    virtual rapidxml::xml_node<> &read(rapidxml::xml_node<> &);
    virtual rapidxml::xml_node<> &write(rapidxml::xml_node<> &) const;
};

#endif
