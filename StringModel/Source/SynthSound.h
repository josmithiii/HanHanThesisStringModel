/*
  ==============================================================================

    SynthSound.h
    Created: 10 Oct 2019 10:03:03am
    Author:  Lily H

  ==============================================================================
*/

#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

using namespace juce;

class SynthSound: public SynthesiserSound
{
public:
    bool appliesToNote(int /*midinotes*/) override
    {
        return true;
    }
    bool appliesToChannel(int /*midichannel*/) override
    {
        return true;
    }
};
