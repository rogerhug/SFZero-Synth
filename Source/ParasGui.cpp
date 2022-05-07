/*
  ==============================================================================

    ParasGui.cpp
    Created: 30 Mar 2022 10:28:32am
    Author:  r7

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ParasGui.h"
#include"PluginParameters.h"
//==============================================================================
ParasGui::ParasGui(AudioProcessorValueTreeState& vts)
    :mod(vts)
    ,looper(vts)
    ,loopermod(vts)
{

    auto* claf = new CustomLookAndFeel();
    addLookAndFeel(claf, "Custom Look And Feel");
    auto* fxlaf = new CustomLookAndFeel();
    addLookAndFeel(fxlaf, "Custom Look And Feel");
    auto* modlaf = new CustomLookAndFeel();
    addLookAndFeel(modlaf, "Custom Look And Feel");

    claf->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::red);
    fxlaf->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::blueviolet);
    modlaf->setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::goldenrod);

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

    addAndMakeVisible(mod);
    addAndMakeVisible(looper);
    addAndMakeVisible(loopermod);


    for (int i = 0; i < 3; i++) {
        mvalue = 0;
        addAndMakeVisible(MainMenuButtons[i]);
        //  MainMenuButtons[i].setLookAndFeel(claf);
        MainMenuButtons[i].setClickingTogglesState(true);
        MainMenuButtons[i].setRadioGroupId(42230);
        MainMenuButtons[i].setColour(juce::TextButton::buttonOnColourId, juce::Colours::blue);
        MainMenuButtons[i].setBounds(10 + i * 133, 0, 133, 24);

        if (i == 0)

        MainMenuButtons[i].setToggleState(true, juce::dontSendNotification);
        MainMenuButtons[i].setColour(juce::TextButton::buttonColourId, juce::Colours::green);


        MainMenuButtons[0].setButtonText("Main");
        MainMenuButtons[1].setButtonText("FxMod");
        MainMenuButtons[2].setButtonText("Modulator");
      //  MainMenuButtons[3].setButtonText("Midi");
      //  MainMenuButtons[4].setButtonText("Utils");


    }



    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(juce::Slider::LinearBar);

        slider.setPopupDisplayEnabled(true, false, this);
        slider.setColour(Slider::ColourIds::backgroundColourId, Colours::silver);


    };
    auto initCombo = [this](ComboBox& combop)
    {
        addAndMakeVisible(combop);
        combop.setEditableText(false);
        combop.setJustificationType(Justification::centredLeft);
        combop.setTextWhenNothingSelected("");

        combop.setTextWhenNoChoicesAvailable(TRANS("(no choices)"));
    };

    initSlider(VolumeSlider);
    VolumeSlider.setTextValueSuffix("Volume");
    initSlider(OverDriveFreqModSlider);
    OverDriveFreqModSlider.setTextValueSuffix("EnveloPe");


    initSlider(PitchSlider);
    PitchSlider.setTextValueSuffix("BPM/Rate");

    initSlider(PitchBendSlider);
    PitchBendSlider.setTextValueSuffix("Bender");
 //   PitchBendSlider.setValue(8129, juce::dontSendNotification);

    initCombo(FilterModeCombo);
    FilterMode::setupComboBox(FilterModeCombo);
    initSlider(Cutoff);
    Cutoff.setTextValueSuffix("Cutoff");
    Cutoff.setLookAndFeel(claf);
    initSlider(CutMod);
    CutMod.setTextValueSuffix("E-Mod");
    initSlider(Resonance);
    Resonance.setTextValueSuffix("Resonance");
    Resonance.setLookAndFeel(claf);
    initSlider(FilterGain);
    FilterGain.setLookAndFeel(claf);
    FilterGain.setTextValueSuffix("SHELF");

    //---------------Fx-----------------------

    initCombo(DelayModeCombo);
    DelayMode::setupComboBox(DelayModeCombo);
    initSlider(DelayTime);
    DelayTime.setTextValueSuffix("Time");
    initSlider(DelayTimeMod);
    DelayTimeMod.setTextValueSuffix("T+lfo");
    initSlider(DelayFeed);
    DelayFeed.setTextValueSuffix("Feed");
    initSlider(DelayFeedMod);
    DelayFeedMod.setTextValueSuffix("F+lfo");
    initSlider(DelayMix);
    DelayMix.setTextValueSuffix("Mix");
    initSlider(DelayMixMod);
    initSlider(DelayLevel);
    DelayLevel.setTextValueSuffix("E-Mod");
    initSlider(DelayLevelMod);
    DelayLevelMod.setTextValueSuffix("V+lfo");

    //  initCombo(OverDModeCombo);
    //  OverDriveMode::setupComboBox(OverDModeCombo);
    addAndMakeVisible(OverDOnOffBut);
    OverDOnOffBut.setButtonText("Shape/on");
    OverDOnOffBut.setClickingTogglesState(true);
    OverDOnOffBut.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    OverDOnOffBut.setColour(juce::TextButton::buttonColourId, juce::Colours::white);
    OverDOnOffBut.setLookAndFeel(claf);
    OverDOnOffBut.setToggleState(false, juce::dontSendNotification);


    //RingOnOffBut.setLookAndFeel(claf);
    initSlider(mainOverDFreqSlider);
    mainOverDFreqSlider.setTextValueSuffix("Freq");
    initSlider(mainOverDGainUp);
    mainOverDGainUp.setTextValueSuffix("GainUp");
    initSlider(mainOverDThresh);
    mainOverDThresh.setTextValueSuffix("Thresh");

    addAndMakeVisible(RingOnOffBut);
    RingOnOffBut.setButtonText("RingMod/on");
    RingOnOffBut.setClickingTogglesState(true);
    RingOnOffBut.setColour(juce::TextButton::buttonOnColourId, juce::Colours::green);
    RingOnOffBut.setColour(juce::TextButton::buttonColourId, juce::Colours::white);

    RingOnOffBut.setToggleState(false, juce::dontSendNotification);
    RingOnOffBut.setLookAndFeel(claf);

    initSlider(RingFrequenceSlider);
    RingFrequenceSlider.setTextValueSuffix("RingHz");
    initSlider(RingFrequenceModSlider);
    RingFrequenceModSlider.setTextValueSuffix("E-Mod");
    initSlider(RingLowHzSlider);
    RingLowHzSlider.setTextValueSuffix("RingLh");

    //--------------envelope---------------
    //-----------------amp----------
    initCombo(egModeCombo);
    ADSRMode::setupComboBox(egModeCombo);
    initSlider(egAtackSlider);
    egAtackSlider.setTextValueSuffix("Attack");
    initSlider(egDecaySlider);
    egDecaySlider.setTextValueSuffix("Decay");
    initSlider(egSustainSlider);
    egSustainSlider.setTextValueSuffix("Sustain");
    initSlider(egReleaseSlider);
    egReleaseSlider.setTextValueSuffix("Release");
    initSlider(egVeloSensSlider);
    egVeloSensSlider.setTextValueSuffix("Velo+-");
    initSlider(egSmoothSensSlider);
    egSmoothSensSlider.setTextValueSuffix("Smooth");

    //-----------------filter----------
    initCombo(egFModeCombo);
    ADSRMode::setupComboBox(egFModeCombo);
    initSlider(egFAtackSlider);
    egFAtackSlider.setTextValueSuffix("AttackF");
    initSlider(egFDecaySlider);
    egFDecaySlider.setTextValueSuffix("DecayF");
    initSlider(egFSustainSlider);
    egFSustainSlider.setTextValueSuffix("SustainF");
    initSlider(egFReleaseSlider);
    egFReleaseSlider.setTextValueSuffix("ReleaseF");
    initSlider(egFVeloSensSlider);
    egFVeloSensSlider.setTextValueSuffix("Velo+-");
    initSlider(egFSmoothSensSlider);
    egFSmoothSensSlider.setTextValueSuffix("Smoothf");
    addAndMakeVisible(meterlevelUV);

    egModeCombo.setVisible(false);
    egAtackSlider.setVisible(false);
    egDecaySlider.setVisible(false);
    egSustainSlider.setVisible(false);
    egReleaseSlider.setVisible(false);
    //OverDModeCombo.setVisible(false);
    OverDOnOffBut.setVisible(false);
    mainOverDFreqSlider.setVisible(false);
    OverDriveFreqModSlider.setVisible(false);
    mainOverDGainUp.setVisible(false);
    mainOverDThresh.setVisible(false);
    RingOnOffBut.setVisible(false);
    RingFrequenceSlider.setVisible(false);
    RingFrequenceModSlider.setVisible(false);
    RingLowHzSlider.setVisible(false);

    mod.setVisible(false);
    loopermod.setVisible(false);



}
ParasGui::~ParasGui()
{
}

void ParasGui::paint (juce::Graphics& g)
{
   
}

void ParasGui::resized()
{
    VolumeSlider.setBounds(290, 155, 120, 30);
    PitchBendSlider.setBounds(290, 190, 120, 30);
    PitchSlider.setBounds(290, 225, 120, 30);
    
 // egModyPolyButton.setBounds(10, 125, 125, 20);
   meterlevelUV.setBounds(290, 130, 120, 15);
   
   
   DelayModeCombo.setBounds(290, 30, 120, 20);
    DelayTime.setBounds(290, 50, 120, 20);
   // DelayTimeMod.setBounds(150, 120, 125, 20);
    DelayFeed.setBounds(290, 70, 120, 20);
  //  DelayFeedMod.setBounds(10, 140, 125, 20);
    DelayMix.setBounds(290, 90, 120, 20);
   // DelayMixMod.setBounds(150, 160, 125, 20);
   // DelayLevel.setBounds(290, 70, 125, 20);
  //  DelayLevelMod.setBounds(150, 180, 125, 20);
   
    egModeCombo.setBounds(10, 150, 125, 20);
    egAtackSlider.setBounds(10, 170, 125, 20);
    egDecaySlider.setBounds(10, 190, 125, 20);
    egSustainSlider.setBounds(10, 210, 125, 20);
    egReleaseSlider.setBounds(10, 230, 125, 20);
    // egVeloSensSlider.setBounds(10, 280, 125, 20);
   // egSmoothSensSlider.setBounds(10, 250, 125, 20);

    egFModeCombo.setBounds(10, 30, 125, 20);
    egFAtackSlider.setBounds(10, 50, 125, 20);
    egFDecaySlider.setBounds(10, 70, 125, 20);
    egFSustainSlider.setBounds(10, 90, 125, 20);
    egFReleaseSlider.setBounds(10, 110, 125, 20);
  //  egFVeloSensSlider.setBounds(10, 120, 125, 20);
  //    egFSmoothSensSlider.setBounds(10, 120, 125, 20);

    FilterModeCombo.setBounds(150, 30, 120, 20);
    Cutoff.setBounds(150, 50, 120, 20);
    CutMod.setBounds(150, 70, 120, 20);
    Resonance.setBounds(150, 90, 120, 20);
    FilterGain.setBounds(150, 110, 120, 20);


   



   // OverDModeCombo.setBounds(290, 150, 120, 20);
    OverDOnOffBut.setBounds(290, 150, 120, 20);
    mainOverDFreqSlider.setBounds(290, 170, 120, 20);
    OverDriveFreqModSlider.setBounds(290, 190, 120, 20);
    mainOverDGainUp.setBounds(290, 210, 120, 20);
    mainOverDThresh.setBounds(290, 230, 120, 20);

    RingOnOffBut.setBounds(150, 160, 120, 20);
    RingFrequenceSlider.setBounds(150, 180, 120, 20);
   // RingFrequenceModSlider.setBounds(150, 200, 120, 20);
    RingLowHzSlider.setBounds(150, 200, 120, 20);

    // This method is where you should set the bounds of any child
    // components that your component contains..
    mod.setBounds(60, 70, 300, 140);
    looper.setBounds(40, 140, 200, 100);
    //loopermod.setBounds(10, 210, 200, 160);
}

void ParasGui::hideFx()
{
    if (LfoModulationSampel.getToggleState() == true)
    {

       
    }
}

int ParasGui::mainMenuValue()
{ 
    if (MainMenuButtons[0].getToggleState() > 0) { mvalue = 0; }
    if (MainMenuButtons[1].getToggleState() > 0) { mvalue = 1; }
    if (MainMenuButtons[2].getToggleState() > 0) { mvalue = 2; }
    if (MainMenuButtons[3].getToggleState() > 0) { mvalue = 3; }
    if (MainMenuButtons[4].getToggleState() > 0) { mvalue = 4; }
    return mvalue;
}

void ParasGui::hideControlMain()
{
    if (mvalue == 0) {

        PitchSlider.setVisible(true);
        PitchBendSlider.setVisible(true);
        VolumeSlider.setVisible(true);
        meterlevelUV.setVisible(true);


        egFModeCombo.setVisible(true);
        egFAtackSlider.setVisible(true);
        egFDecaySlider.setVisible(true);
        egFSustainSlider.setVisible(true);
        egFReleaseSlider.setVisible(true);
        FilterModeCombo.setVisible(true);
        FilterModeCombo.setVisible(true);
        Cutoff.setVisible(true);
        CutMod.setVisible(true);
        Resonance.setVisible(true);
        FilterGain.setVisible(true);

        DelayModeCombo.setVisible(true);
        DelayTime.setVisible(true);
        DelayFeed.setVisible(true);
        DelayMix.setVisible(true);
        DelayLevel.setVisible(true);

        egModeCombo.setVisible(false);
        egAtackSlider.setVisible(false);
        egDecaySlider.setVisible(false);
        egSustainSlider.setVisible(false);
        egReleaseSlider.setVisible(false);
       // OverDModeCombo.setVisible(false);
        OverDOnOffBut.setVisible(false);
        mainOverDFreqSlider.setVisible(false);
        OverDriveFreqModSlider.setVisible(false);
        mainOverDGainUp.setVisible(false);
        mainOverDThresh.setVisible(false);
        RingOnOffBut.setVisible(false);
        RingFrequenceSlider.setVisible(false);
        RingFrequenceModSlider.setVisible(false);
        RingLowHzSlider.setVisible(false);
        mod.setVisible(false);
        looper.setVisible(true);
        loopermod.setVisible(false);

    }
    if (mvalue == 1) {

        VolumeSlider.setVisible(false);
        meterlevelUV.setVisible(false);
        PitchSlider.setVisible(false);
        PitchBendSlider.setVisible(false);

        egFModeCombo.setVisible(true);
        egFAtackSlider.setVisible(true);
        egFDecaySlider.setVisible(true);
        egFSustainSlider.setVisible(true);
        egFReleaseSlider.setVisible(true);
        FilterModeCombo.setVisible(true);
        FilterModeCombo.setVisible(true);
        Cutoff.setVisible(true);
        CutMod.setVisible(true);
        Resonance.setVisible(true);
        FilterGain.setVisible(true);

        DelayModeCombo.setVisible(true);
        DelayTime.setVisible(true);
        DelayFeed.setVisible(true);
        DelayMix.setVisible(true);
        DelayLevel.setVisible(true);

        egModeCombo.setVisible(true);
        egAtackSlider.setVisible(true);
        egDecaySlider.setVisible(true);
        egSustainSlider.setVisible(true);
        egReleaseSlider.setVisible(true);

        //OverDModeCombo.setVisible(true);
        OverDOnOffBut.setVisible(true);
        mainOverDFreqSlider.setVisible(true);
        OverDriveFreqModSlider.setVisible(true);
        mainOverDGainUp.setVisible(true);
        mainOverDThresh.setVisible(true);
        RingOnOffBut.setVisible(true);
        RingFrequenceSlider.setVisible(true);
        RingFrequenceModSlider.setVisible(true);
        RingLowHzSlider.setVisible(true);
        mod.setVisible(false);
        looper.setVisible(false);
        loopermod.setVisible(false);
    }
    if (mvalue == 2) {

        VolumeSlider.setVisible(false);
        meterlevelUV.setVisible(false);
        PitchSlider.setVisible(false);
        PitchBendSlider.setVisible(false);


        egFModeCombo.setVisible(false);
        egFAtackSlider.setVisible(false);
        egFDecaySlider.setVisible(false);
        egFSustainSlider.setVisible(false);
        egFReleaseSlider.setVisible(false);
        FilterModeCombo.setVisible(false);
        Cutoff.setVisible(false);
        CutMod.setVisible(false);
        Resonance.setVisible(false);
        FilterGain.setVisible(false);

        DelayModeCombo.setVisible(false);
        DelayTime.setVisible(false);
        DelayFeed.setVisible(false);
        DelayMix.setVisible(false);
        DelayLevel.setVisible(false);
        

        egModeCombo.setVisible(false);
        egAtackSlider.setVisible(false);
        egDecaySlider.setVisible(false);
        egSustainSlider.setVisible(false);
        egReleaseSlider.setVisible(false);

        //OverDModeCombo.setVisible(false);
        OverDOnOffBut.setVisible(false);
        mainOverDFreqSlider.setVisible(false);
        OverDriveFreqModSlider.setVisible(false);
        mainOverDGainUp.setVisible(false);
        mainOverDThresh.setVisible(false);
        RingOnOffBut.setVisible(false);
        RingFrequenceSlider.setVisible(false);
        RingFrequenceModSlider.setVisible(false);
        RingLowHzSlider.setVisible(false);
        mod.setVisible(true);
        looper.setVisible(false);
        loopermod.setVisible(true);
    }
}
