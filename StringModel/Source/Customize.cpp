/*
  ==============================================================================

    Customize.cpp
    Created: 10 Oct 2019 10:02:42am
    Author:  Lily H

  ==============================================================================
*/

#include "Customize.h"
#include "BinaryData.h"
#include <math.h>
//==============================================================================
Customize::Customize(StringModelAudioProcessor& p):
processor(p),playButton("play",DrawableButton::ButtonStyle::ImageStretched),myString(p)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setSize(500,250);
    addAndMakeVisible(myString);
    addAndMakeVisible(&title);
   title.setText("This is a string",dontSendNotification);

   // static Typeface::Ptr myType2 = Typeface::createSystemTypefaceFor(BinaryData::Amagro_bold_ttf,
   //                                                            BinaryData::Amagro_bold_ttfSize);
   // Font* myFont2 = new Font(myType2);
   // myFont2->setSizeAndStyle(30, 2, 1.0, 0.0);
   // title.setFont(*myFont2);
   title.setFont(Font(30.0f, Font::bold));

   title.setColour(Label::ColourIds::textColourId , Colours::black);
    
    
    addAndMakeVisible(&sonic);
    sonic.setText("Sonic Attributes",dontSendNotification);
    addAndMakeVisible(&physics);
    physics.setText("Physical Appearance Attributes",dontSendNotification);
    
    Path butoutline = Path();
    butoutline.addRectangle(200, 200, 50, 50);
    //playButton.setShape(butoutline, true, true, false);
    std::unique_ptr<Drawable> buttonOff;
    std::unique_ptr<Drawable> buttonOn;
     
     buttonOff = Drawable::createFromImageData(BinaryData::ButtonOff_png, BinaryData::ButtonOff_pngSize);
     buttonOn = Drawable::createFromImageData(BinaryData::ButtonOn_png, BinaryData::ButtonOn_pngSize);
    playButton.setClickingTogglesState(true);
    playButton.setImages(buttonOn.get(), buttonOn.get(),buttonOff.get());
    playButton.onStateChange = [this] {playButtonClicked(87,playButton.isDown());};
    addAndMakeVisible(playButton);

    // static Typeface::Ptr myType = Typeface::createSystemTypefaceFor(BinaryData::Ubuntu_L_ttf,
    //                                                                 BinaryData::Ubuntu_L_ttfSize);
    // Font* myFont = new Font(myType);
    Font* myFont = new Font(14.0f);
    //myFont->setSizeAndStyle(30, 2, 1.0, 0.0);
    
    
    tauSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    tauSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    addAndMakeVisible(&tauSlider);
    addAndMakeVisible (&taulabel);
    taulabel.setText ("Sustain", dontSendNotification);//(fundamental time constant)
    taulabel.attachToComponent (&tauSlider, true);
    taulabel.setFont(*myFont);
    taulabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    
    
    omegaSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    omegaSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    addAndMakeVisible(&omegaSlider);
    addAndMakeVisible (&omegalabel);
    omegalabel.setText ("Pitch", dontSendNotification);//(frequency dependent damping)
    omegalabel.attachToComponent (&omegaSlider, true);
    omegalabel.setFont(*myFont);
    omegalabel.setColour(Label::ColourIds::textColourId , Colours::black);
  


    pSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    pSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    //pSlider.onValueChange = [this] {sanitycheck(1);};
    addAndMakeVisible(&pSlider);
    addAndMakeVisible (&plabel);
    plabel.setText ("Roundness", dontSendNotification);//(frequency dependent damping)
    plabel.attachToComponent (&pSlider, true);
    plabel.setFont(*myFont);
    plabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    lSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    lSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    lSlider.setRange(0.0f,500.0f);
    lSlider.setValue(300.0f);
    //lSlider.onValueChange = [this] {sanitycheck(0);};
    addAndMakeVisible(&lSlider);
    addAndMakeVisible (&llabel);
    llabel.setText ("Length", dontSendNotification);//(frequency dependent damping)
    llabel.attachToComponent (&lSlider, true);
    llabel.setFont(*myFont);
    llabel.setColour(Label::ColourIds::textColourId , Colours::black);
   
    

    
    ASlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    ASlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    ASlider.setRange(10.0f,100.0f);
    ASlider.setValue(10.0f);
    addAndMakeVisible(&ASlider);
    addAndMakeVisible (&Alabel);
    Alabel.setText ("Thickness", dontSendNotification);//(frequency dependent damping)
    Alabel.attachToComponent (&ASlider, true);
    Alabel.setFont(*myFont);
    Alabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
  
    dispersionSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    dispersionSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    addAndMakeVisible(&dispersionSlider);
    addAndMakeVisible (&dispersionlabel);
    dispersionlabel.setText ("Dispersion", dontSendNotification);//(inharmonicity)
    dispersionlabel.attachToComponent (&dispersionSlider, true);
    dispersionlabel.setFont(*myFont);
    dispersionlabel.setColour(Label::ColourIds::textColourId , Colours::black);
   

    alphaSlider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    alphaSlider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    alphalabel.setText ("Alpha1", dontSendNotification);//(shape of drum)
    alphalabel.attachToComponent (&alphaSlider, true);
    alphalabel.setFont(*myFont);
    alphalabel.setColour(Label::ColourIds::textColourId , Colours::black);
    
    alpha2Slider.setSliderStyle(Slider::SliderStyle::LinearHorizontal);
    alpha2Slider.setTextBoxStyle(Slider::TextEntryBoxPosition::NoTextBox , true, 0, 0);
    alpha2label.setText ("Alpha2", dontSendNotification);//(shape of drum)
    alpha2label.attachToComponent (&alpha2Slider, true);
    alpha2label.setFont(*myFont);
    alpha2label.setColour(Label::ColourIds::textColourId , Colours::black);

    
    //addAndMakeVisible(&alphaSlider);
    //addAndMakeVisible (&alphalabel);
    //addAndMakeVisible(&alpha2Slider);
    //addAndMakeVisible (&alpha2label);
  
    //dimSelection = new AudioProcessorValueTreeState::ComboBoxAttachment (processor.tree,"dimtype",dimMenu);
    tauTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"tau",tauSlider);//this class maintains a connection between slider and parameter in apvts
   omegaTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"omega",omegaSlider);
    pTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"p",pSlider);
    dispersionTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"dispersion",dispersionSlider);
    alphaTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"alpha1",alphaSlider);
    alpha2Tree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"alpha2",alpha2Slider);
    lengthTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"length",lSlider);
     thicknessTree= new AudioProcessorValueTreeState::SliderAttachment(processor.tree,"thickness",ASlider);
    
}

Customize::~Customize()
{
}

void Customize::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
     draws some placeholder text to get you started.
     
     You should replace everything in this method with your own
     drawing code..
     */

  
    myString.changeParameter(tauSlider.getValue(),
                             pSlider.getValue(),
                             dispersionSlider.getValue(),
                             alphaSlider.getValue(),
                             alpha2Slider.getValue(),
                             omegaSlider.getValue(),
                             lSlider.getValue(),
                             ASlider.getValue());
    myString.repaint();
    processor.dim = 0;
    
}
void Customize::changeGUI(int dim)
{
    if(dim == 1)
    {
        //std::cout<<"dimension? "<<dim<<"\n";
        addAndMakeVisible(&alphaSlider);
        addAndMakeVisible (&alphalabel);
        alpha2Slider.setVisible(false);
        alpha2label.setVisible(false);
    }
    else if (dim == 2)
    {
        addAndMakeVisible(&alpha2Slider);
        addAndMakeVisible (&alpha2label);
        alphaSlider.setVisible(false);
        alphalabel.setVisible(false);
    }
    else if (dim == 0)
    {
        alphaSlider.setVisible(false);
        alphalabel.setVisible(false);
        alpha2Slider.setVisible(false);
        alpha2label.setVisible(false);
    }
    
    
}

void Customize::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    //Rectangle<int> area=getLocalBounds();
    int top = 80;
    tauSlider.setBounds(79,top,150,20);
    omegaSlider.setBounds(79,top+20,150,20);
    pSlider.setBounds(79,top+40,150,20);
    dispersionSlider.setBounds(79,top+60,150,20);
    playButton.setBounds(270,171,50,50);
    //alphaSlider.setBounds(100,60,300,20);
    //alpha2Slider.setBounds(100,80,300,20);
   // dimMenu.setBounds(358,0,150,20);
    
    title.setBounds(178,16,242,32);
    sonic.setBounds(79,42,170,40);
    physics.setBounds(361,42,226,42);
    lSlider.setBounds(358,top,150,20);
    //rhoSlider.setBounds(358,top+20,150,20);
    ASlider.setBounds(358,top+40,150,20);
    //TSlider.setBounds(358,top+60,150,20);
    
    myString.setBounds(10,226,573,200);
    //alphaSlider.setBounds(358,120,150,20);
    //alpha2Slider.setBounds(358,140,150,20);

        
}



void Customize::playButtonClicked(int midiNote,bool isDown)
{
    if(isDown){
        processor.mySynth.noteOn(1,midiNote,120);
        // if (processor.getMidiOutput() != nullptr)
        //            processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOn(1, midiNote, 1.f));

    }
    else{
        //processor.mySynth.noteOff(1, midiNote, 0, true);
        // if (processor.getMidiOutput() != nullptr)
        //     processor.getMidiOutput()->sendMessageNow(MidiMessage::noteOff(1, midiNote, 0.f));
    }
}



