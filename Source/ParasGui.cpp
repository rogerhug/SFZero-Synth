/*
  ==============================================================================

    ParasGui.cpp
    Created: 30 Mar 2022 10:28:32am
    Author:  r7

  ==============================================================================
*/

#include <JuceHeader.h>
#include "ParasGui.h"

//==============================================================================
ParasGui::ParasGui()
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

    auto initSlider = [this](Slider& slider)
    {
        addAndMakeVisible(slider);
        slider.setSliderStyle(juce::Slider::LinearBar);

        slider.setPopupDisplayEnabled(false, false, this);
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
    initSlider(egVolumeSlider); 
    egVolumeSlider.setTextValueSuffix("EnveloPe");
    

    initSlider(PitchSlider);
    PitchSlider.setSliderStyle(juce::Slider::RotaryHorizontalVerticalDrag);
    PitchSlider.setTextBoxStyle(Slider::TextBoxLeft, false, 100, 17);
    PitchSlider.setTextValueSuffix("BPM/Rate");
    initCombo(FilterModeCombo);
    FilterMode::setupComboBox(FilterModeCombo);
    initSlider(Cutoff);
    Cutoff.setTextValueSuffix("Cutoff");
    Cutoff.setLookAndFeel(claf);
    initSlider(CutMod);
    CutMod.setTextValueSuffix("EnVelope");
    initSlider(Resonance);
    Resonance.setTextValueSuffix("Resonance");
    Resonance.setLookAndFeel(claf);
    initSlider(FilterGain);
    FilterGain.setLookAndFeel(claf);
    FilterGain.setTextValueSuffix("SHELF");

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
    DelayLevel.setTextValueSuffix("Vol");
    initSlider(DelayLevelMod);
    DelayLevelMod.setTextValueSuffix("V+lfo");

    initCombo(OverDModeCombo);
    OverDriveMode::setupComboBox(OverDModeCombo);

    initSlider(mainOverDFreqSlider);
    mainOverDFreqSlider.setTextValueSuffix("Freq");
    initSlider(mainOverDGainUp);
    mainOverDGainUp.setTextValueSuffix("GainUp");
    initSlider(mainOverDThresh);
    mainOverDThresh.setTextValueSuffix("Thresh");



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

    addAndMakeVisible(meterlevelUV);
        

}

ParasGui::~ParasGui()
{
}

void ParasGui::paint (juce::Graphics& g)
{
   
}

void ParasGui::resized()
{
    VolumeSlider.setBounds(150, 170, 120, 17);
    egVolumeSlider.setBounds(150, 190, 120, 20);
    PitchSlider.setBounds(150, 220, 120, 30);
   // LfoModulationSampel.setBounds(10, 20, 50, 30);
 meterlevelUV.setBounds(150, 150, 120, 15);
   
   
   DelayModeCombo.setBounds(290, 20, 125, 20);
    DelayTime.setBounds(290, 40, 125, 20);
   // DelayTimeMod.setBounds(150, 120, 125, 20);
    DelayFeed.setBounds(290, 60, 125, 20);
  //  DelayFeedMod.setBounds(10, 140, 125, 20);
    DelayMix.setBounds(290, 80, 125, 20);
   // DelayMixMod.setBounds(150, 160, 125, 20);
    DelayLevel.setBounds(290, 100, 125, 20);
  //  DelayLevelMod.setBounds(150, 180, 125, 20);
   
    egModeCombo.setBounds(10, 150, 125, 20);
    egAtackSlider.setBounds(10, 170, 125, 20);
    egDecaySlider.setBounds(10, 190, 125, 20);
    egSustainSlider.setBounds(10, 210, 125, 20);
    egReleaseSlider.setBounds(10, 230, 125, 20);
   // egVeloSensSlider.setBounds(10, 280, 125, 20);

    egFModeCombo.setBounds(10, 20, 125, 20);
    egFAtackSlider.setBounds(10, 40, 125, 20);
    egFDecaySlider.setBounds(10, 60, 125, 20);
    egFSustainSlider.setBounds(10, 80, 125, 20);
    egFReleaseSlider.setBounds(10, 100, 125, 20);
  //  egFVeloSensSlider.setBounds(10, 120, 125, 20);

 FilterModeCombo.setBounds(150, 20, 120, 20);
    Cutoff.setBounds(150, 40, 120, 20);
    CutMod.setBounds(150, 60, 120, 20);
    Resonance.setBounds(150, 80, 120, 20);
    FilterGain.setBounds(150, 100, 120, 20);


   



    OverDModeCombo.setBounds(290, 150, 120, 20);
    mainOverDFreqSlider.setBounds(290, 170, 120, 20);
    mainOverDGainUp.setBounds(290, 190, 120, 20);
    mainOverDThresh.setBounds(290, 210, 120, 20);

    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void ParasGui::hideFx()
{
    if (LfoModulationSampel.getToggleState() == true)
    {


    }
}
