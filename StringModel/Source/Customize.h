/*
  ==============================================================================

    Customize.h
    Created: 10 Oct 2019 10:02:42am
    Author:  Lily H

  ==============================================================================
*/
#pragma once

#include <juce_audio_processors/juce_audio_processors.h>

using namespace juce;

#include "PluginProcessor.h"
#include "theString.h"
//==============================================================================
/*
 */
class Customize    : public Component
{
public:
    Customize(StringModelAudioProcessor&);
    ~Customize();
    
    void paint (Graphics&) override;
    void resized() override;
    //float getsliderval(int seq);
    void changeGUI(int dim);
    void playButtonClicked(int midiNote, bool isDown);
   
private:
    //Label title;
    
    Slider tauSlider;
    Slider omegaSlider;
    Slider lSlider;
    Slider pSlider;
    Slider dispersionSlider;
    Slider alphaSlider;
    Slider alpha2Slider;
    Slider ASlider;

    DrawableButton playButton;
    Label taulabel;
    
    Label omegalabel;
    Label llabel;
    Label plabel;
    Label dispersionlabel;
    Label alphalabel;
    Label alpha2label;
 
    Label title,sonic,physics;
    Label Alabel;
    
    theString myString;
    
    StringModelAudioProcessor& processor;
    
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> tauTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> omegaTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> pTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> dispersionTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> alphaTree;
    ScopedPointer <AudioProcessorValueTreeState::SliderAttachment> alpha2Tree;
    ScopedPointer<AudioProcessorValueTreeState::ComboBoxAttachment> dimSelection;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> lengthTree;
    ScopedPointer<AudioProcessorValueTreeState::SliderAttachment> thicknessTree;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Customize)
};


