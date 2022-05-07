/*
  ==============================================================================

    ParasGui.h
    Created: 30 Mar 2022 10:28:32am
    Author:  r7

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include"Eutils.h"
#include"UVmeter.h"
#include"customLook.h"
#include"modulator.h"
#include"repeaterGui.h"
//==============================================================================
/*
*/
class ParasGui  : public juce::Component
{
public:
    ParasGui(AudioProcessorValueTreeState& vts);
    ~ParasGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void hideFx();
    Slider VolumeSlider;
    Slider egVolumeSlider;
    Slider PitchSlider;
    Slider PitchBendSlider;
    int showOn = 1;
    UVmeter meterlevelUV;
    void show(int s) { showOn = 1; }
   
    TextButton LfoModulationSampel;
    TextButton MainMenuButtons[5];
    int mainMenuValue();

    Slider Cutoff;
    Slider Resonance;
    Slider FilterGain;
    Slider FilterSmooth;
    TextButton autoQ;
    ComboBox FilterModeCombo;
    Slider CutMod;

    ComboBox DelayModeCombo;
    Slider DelayTime;
    Slider DelayFeed;
    Slider DelayMix;
    Slider DelayLevel;
    Slider DelayTimeMod;
    Slider DelayFeedMod;
    Slider DelayMixMod;
    Slider DelayLevelMod;

    //--------fx-------------
   // ComboBox OverDModeCombo;
    TextButton OverDOnOffBut;
    Slider mainOverDFreqSlider;
    Slider OverDriveFreqModSlider;
    Slider mainOverDGainUp;
    Slider mainOverDThresh;

    TextButton RingOnOffBut;
    Slider RingFrequenceSlider;
    Slider RingFrequenceModSlider;
    Slider RingLowHzSlider;

    //---------amp-----
    TextButton egModyPolyButton;
    ComboBox egModeCombo;
    Slider egAtackSlider;
    Slider egDecaySlider;
    Slider egSustainSlider;
    Slider egReleaseSlider;
    Slider egVeloSensSlider;
    Slider egSmoothSensSlider;
    //-------filter----
    ComboBox egFModeCombo;
    Slider egFAtackSlider;
    Slider egFDecaySlider;
    Slider egFSustainSlider;
    Slider egFReleaseSlider;
    Slider egFVeloSensSlider;
    Slider egFSmoothSensSlider;

    //---------looper--------

    modulator mod;
    repeaterGui looper;
    repeaterGuiMod loopermod;

   
    void hideControlMain();
private:
    double meterlevel;
    int mvalue;
    void addLookAndFeel(juce::LookAndFeel* laf, const juce::String& name) { }
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ParasGui)
};
