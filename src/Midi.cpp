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

#include "Midi.h"

using namespace rapidxml;
using namespace std;

int MidiStream::seqfd; 
vector<MidiControl *> MidiStream::controllers; 
boost::shared_mutex MidiStream::mutex;

boost::thread MidiStream::midiThread(MidiStream::stream);

Class MidiStomp::cls(std::string("MidiStomp"), MidiStomp::newInstance);
Class MidiExpression::cls(std::string("MidiExpression"), 
 MidiExpression::newInstance);

void MidiStream::addController(MidiControl *controller) {

    boost::unique_lock<boost::shared_mutex> lock(MidiStream::mutex);
    MidiStream::controllers.push_back(controller);
}

void MidiStream::readMidi() {
    
    unsigned char inbytes[4];
    int status = read(MidiStream::seqfd, &inbytes, sizeof(inbytes));

    if (status < 0) {
        //TODO Some sort of error checking
    }

    boost::shared_lock<boost::shared_mutex> lock(MidiStream::mutex);
    if (inbytes[0] == SEQ_MIDIPUTC) 
        for (uint i = 0; i < MidiStream::controllers.size(); i++)
            MidiStream::controllers[i]->midiInput(inbytes[1]);
}

void MidiStream::stream() {
    
    MidiStream::seqfd = open(MIDI_DEVICE, O_RDONLY);
    //TODO Some sort of error checking

    while (1) 
        readMidi();
}

MidiControl::MidiControl() : Processor::Processor(), mVal(0), mMatches(0),
 mLowBound(0), mUpBound(-1) {
    MidiStream::addController(this);
}

void MidiControl::process(const sample_t* in, sample_t* out, int num) {
    
    for (int i = 0; i < num; i++)
        out[i] = mVal;
}

void MidiControl::midiInput(unsigned char val) {

    if (mMatches >= mSignal.size() && val >= mLowBound && val <= mUpBound) {
        matchedValue(val);
        mMatches = 0;
    }
    mMatches = val == mSignal[mMatches] ? mMatches + 1 : 0;
}

xml_node<> &MidiControl::read(xml_node<> &inode) {

    char *tok = strtok(inode.first_attribute("id")->value(), ", ");
    mSignal.clear();
    while (tok != NULL) {
        mSignal.push_back(atoi(tok));
        tok = strtok(NULL, ", ");
    }

    xml_node<> *val = inode.first_node("range");
    if (val) {
        char *tok = strtok(inode.first_node("range")->value(), "-, ");
        mLowBound = atoi(tok);

        tok = strtok(NULL, "-, ");
        mUpBound = atoi(tok);
    }
    else {
        mLowBound = 0;
        mUpBound = -1;
    }

    return inode;
}

xml_node<> &MidiControl::write(xml_node<> &onode) const {

    return onode;
}

void MidiStomp::matchedValue(char val) {
    
    mVal = (mToggle && val == mVal) ? kOff : val;
}

xml_node<> &MidiStomp::read(xml_node<> &inode) {

    MidiControl::read(inode);

    mToggle = inode.first_node("toggle") ? 1 : 0;

    return inode;
}

xml_node<> &MidiStomp::write(xml_node<> &onode) const {

    return onode;
}

void MidiExpression::process(const sample_t* in, sample_t* out, int num) {

    sample_t min[num], max[num], decay[num];
    mMin->process(in, min, num);
    mMax->process(in, max, num);
    mDecay->process(in, decay, num);
    
    for (int i = 0; i < num; i++) {    
        mCurVal = mVal * decay[i] + mCurVal * (1 - decay[i]);
        float perc = (mCurVal - mMidiMin) / (mMidiMax - mMidiMin);

        if (mScale == kLin)
            out[i] = perc * max[i] + (1 - perc) * min[i];
        else {
            float logMin = log2(min[i]);
            float logMax = log2(max[i]);
            out[i] = pow(2, perc * logMax + (1 - perc) * logMin);
        }
    }
}

xml_node<> &MidiExpression::read(xml_node<> &inode) {

    MidiControl::read(inode);

    char *scale = inode.first_attribute("scale")->value();
    if (strlen(scale) > 3)
        scale[3] = 0;

    if (strcmp(scale, "lin") == 0)
        mScale = kLin;
    else
        mScale = kExp;
    
    mMidiMin = atoi(inode.first_attribute("midimin")->value());
    mMidiMax = atoi(inode.first_attribute("midimax")->value());

    delete mMin;
    mMin = tryReadProcessor(inode, "min", DEFAULTMIN);
    delete mMax;
    mMax = tryReadProcessor(inode, "max", DEFAULTMAX);
    delete mDecay;
    mDecay = tryReadProcessor(inode, "decay", DEFAULTDECAY);

    return inode;
}

xml_node<> &MidiExpression::write(xml_node<> &onode) const {

    return onode;
}

