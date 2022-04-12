/*
  ==============================================================================

    PluginParameters.h
    Created: 29 Mar 2022 1:17:58pm
    Author:  r7

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Eutils.h"

typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;
typedef AudioProcessorValueTreeState::SliderAttachment SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment ButtonAttachment;



struct PluginParameters
{
    // Id's are symbolic names, Names are human-friendly names for GUI
    // Labels are supplementary, typically used for units of measure

    //-----------Mainparas-------------------
    static const String mainPitch_Id, mainPitch_Name, mainPitch_Label;
    static const String mainVolume_Id, mainVolume_Name, mainVolume_Label;
    static const String mainVolumeMod_Id, mainVolumeMod_Name, mainVolumeMod_Label;

    static const String mainCutoff_Id, mainCutoff_Name, mainCutoff_Label;
    static const String mainResonance_Id, mainResonance_Name, mainResonance_Label;
    static const String mainAutoResonance_Id, mainAutoResonance_Name, mainAutoResonance_Label;
    static const String mainFilterGain_Id, mainFilterGain_Name, mainFilterGain_Label;
    static const String mainFilterMode_Id, mainFilterMode_Name, mainFilterMode_Label;
    static const String mainCutoffMod_Id, mainCutoffMod_Name, mainCutoffMod_Label;

    static const String mainDelayMode_Id, mainDelayMode_Name, mainDelayMode_Label;
    static const String mainDelayTime_Id, mainDelayTime_Name, mainDelayTime_Label;
    static const String mainDelayFeed_Id, mainDelayFeed_Name, mainDelayFeed_Label;
    static const String mainDelayLevel_Id, mainDelayLevel_Name, mainDelayLevel_Label;
    static const String mainDelayMix_Id, mainDelayMix_Name, mainDelayMix_Label;



    static const String OverdriveMode_Id, OverdriveMode_Name, OverdriveMode_Label;
    static const String OverdriveFreq_Id, OverdriveFreq_Name, OverdriveFreq_Label;
    static const String OverdriveGainUp_Id, OverdriveGainUp_Name, OverdriveGainUp_Label;
    static const String OverdriveThresh_Id, OverdriveThresh_Name, OverdriveThresh_Label;

    static const String egMode_Id, egMode_Name, egMode_Label;
    static const String egAttack_Id, egAttack_Name, egAttack_Label;
    static const String egDecay_Id, egDecay_Name, egDecay_Label;
    static const String egSustain_Id, egSustain_Name, egSustain_Label;
    static const String egRelease_Id, egRelease_Name, egRelease_Label;
    static const String egVeloSens_Id, egVeloSens_Name, egVeloSens_Label;

    static const String egFMode_Id, egFMode_Name, egFMode_Label;
    static const String egFAttack_Id, egFAttack_Name, egFAttack_Label;
    static const String egFDecay_Id, egFDecay_Name, egFDecay_Label;
    static const String egFSustain_Id, egFSustain_Name, egFSustain_Label;
    static const String egFRelease_Id, egFRelease_Name, egFRelease_Label;
    static const String egFVeloSens_Id, egFVeloSens_Name, egFVeloSens_Label;


    PluginParameters(AudioProcessorValueTreeState& vts);
    void createAllParameters();
    void detachControls();

    void attachControls(
        //MainParas


        Slider& mainPitchSlider,
        Slider& mainVolumeSlider,
        Slider& mainVolumeSliderMod,
        Slider& mainCutoffSlider,
        Slider& mainFilterGainSlider,
        Slider& mainCutoffModSlider,
        Slider& mainResonanceSlider,
        TextButton &mainAutoResonanceButton,
        ComboBox& mainFilterModusCombox,
        ComboBox& Sp1DelayModeCombox,
        Slider& mainDelayTimeSlider,
        Slider& mainDelayFeedSlider,
        Slider& mainDelayLevelSlider,
        Slider& mainDelayMixSlider,
        ComboBox& OverdriveModeTempSlider,
        Slider& OverdriveFreqSlider,
        Slider& OverdriveGainUpSlider,
        Slider& OverdriveThreshSlider,
        ComboBox &egModeCombo,
        Slider& egAttackSlider,
        Slider& egDecaySlider,
        Slider& egSustainSlider,
        Slider& egReleaseSlider,
        Slider& egVeloSensSlider,
        ComboBox& egFModeCombo,
        Slider& egFAttackSlider,
        Slider& egFDecaySlider,
        Slider& egFSustainSlider,
        Slider& egFReleaseSlider,
        Slider& egFVeloSensSlider

    );
   
    float mainVolumeValue;
    float mainVolumeModValue;
    int mainPitchValue;

    FilterMode mainFilterModeV;
    float mainCutoffValue;
    float mainResonanceValue;
    float mainFilterGainValue;
    bool mainAutoResonanceValue;
    float mainCutoffModValue;

    DelayMode mainDelayModeV;
    float mainDelayTimeValue;
    float mainDelayFeedValue;
    float mainDelayLevelValue;
    float mainDelayMixValue;


    OverDriveMode ovmode;
    int OverdriveModevalue;
    float OverdriveFreqValue;
    float OverdriveGainUpValue;
    float OverdriveThreshValue;
    ADSRMode egmode;
    float egAttackValue;
    float egDecayValue;
    float egSustainValue;
    float egReleaseValue;
    float egVeloSensValue;
    ADSRMode egFmode;
    float egFAttackValue;
    float egFDecayValue;
    float egFSustainValue;
    float egFReleaseValue;
    float egFVeloSensValue;

private:



    // Reference to AudioProcessorValueTreeState object that owns the parameter objects
    AudioProcessorValueTreeState& valueTreeState;

    // Attachment objects link GUI controls to parameters
    //MainParas
    SliderAttachment* mainVolumeAttachment;
    SliderAttachment* mainVolumeModAttachment;
    SliderAttachment* mainPitchAttachment;

    SliderAttachment* mainFilterCutAttachment;
    SliderAttachment* mainFilterCutModAttachment;
    SliderAttachment* mainFilterResAttachment;
    ButtonAttachment* mainFilterAutoResonanceAttachment;
    SliderAttachment* mainFilterGainAttachment;
    ComboBoxAttachment* mainFilterModeAttachment;


    ComboBoxAttachment* mainDelayModeComboxAttachment;
    SliderAttachment* mainDelayTimeAttachment;
    SliderAttachment* mainDelayFeedAttachment;
    SliderAttachment* mainDelayLevelAttachment;
    SliderAttachment* mainDelayMixAttachment;


    ComboBoxAttachment* OverdriveModeAttachment;
    SliderAttachment* OverdriveFreqAttachment;
    SliderAttachment* OverdriveGainUpAttachment;
    SliderAttachment* OverdriveThreshAttachment;

    ComboBoxAttachment* egModeAttachment;
    SliderAttachment* egAttackAttachment;
    SliderAttachment* egDecayAttachment;
    SliderAttachment* egSustainAttachment;
    SliderAttachment* egReleaseAttachment;
    SliderAttachment* egVeloSensAttachment;

    ComboBoxAttachment* egFModeAttachment;
    SliderAttachment* egFAttackAttachment;
    SliderAttachment* egFDecayAttachment;
    SliderAttachment* egFSustainAttachment;
    SliderAttachment* egFReleaseAttachment;
    SliderAttachment* egFVeloSensAttachment;
    
    struct ADSRModeListener : public AudioProcessorValueTreeState::Listener
    {


        ADSRMode& adModes;

        ADSRModeListener(ADSRMode& wf) : AudioProcessorValueTreeState::Listener(), adModes(wf) {}
        void parameterChanged(const String&, float newValue) override
        {
            adModes.setIndex((int)(newValue + 0.5f));
        }
    };

    struct OverDriveModeListener : public AudioProcessorValueTreeState::Listener
    {


        OverDriveMode& ovModes;

        OverDriveModeListener(OverDriveMode& wf) : AudioProcessorValueTreeState::Listener(), ovModes(wf) {}
        void parameterChanged(const String&, float newValue) override
        {
            ovModes.setIndex((int)(newValue + 0.5f));
        }
    };
    

    struct SpFilterModeListener : public AudioProcessorValueTreeState::Listener
    {


        FilterMode& SpFilterModes;

        SpFilterModeListener(FilterMode& wf) : AudioProcessorValueTreeState::Listener(), SpFilterModes(wf) {}
        void parameterChanged(const String&, float newValue) override
        {
            SpFilterModes.setIndex((int)(newValue + 0.5f));
        }
    };


    struct SpDelayModeListener : public AudioProcessorValueTreeState::Listener
    {


        DelayMode& SpDelayModes;

        SpDelayModeListener(DelayMode& wf) : AudioProcessorValueTreeState::Listener(), SpDelayModes(wf) {}
        void parameterChanged(const String&, float newValue) override
        {
            SpDelayModes.setIndex((int)(newValue + 0.5f));
        }
    };

    struct IntegerListener : public AudioProcessorValueTreeState::Listener
    {
        int& workingValue;

        IntegerListener(int& wv) : AudioProcessorValueTreeState::Listener(), workingValue(wv) {}
        void parameterChanged(const String&, float newValue) override
        {

            workingValue = (int)newValue;
        }
    };

    struct FloatListener : public AudioProcessorValueTreeState::Listener
    {
        float& workingValue;
        float scaleFactor;      // multiply parameter values by this to get working value

        FloatListener(float& wv, float sf = 1.0f) : AudioProcessorValueTreeState::Listener(), workingValue(wv), scaleFactor(sf) {}
        void parameterChanged(const String&, float newValue) override
        {
            workingValue = scaleFactor * newValue;
        }
    };

    struct BoolListener : public AudioProcessorValueTreeState::Listener
    {
        bool& workingValue;
        void test(int* p)
        {


        }
        BoolListener(bool& wv) : AudioProcessorValueTreeState::Listener(), workingValue(wv) {}
        void parameterChanged(const String&, float newValue) override
        {
            workingValue = newValue >= 0.5f;
        }
    };

    FloatListener mainVolumeListener;
    FloatListener mainVolumeModListener;
    IntegerListener mainPitchListener;

    SpFilterModeListener mainFilterModusListener;
    FloatListener mainCutoffListener;
    FloatListener mainCutoffListenerMod;
    FloatListener mainResonanceListener;
    BoolListener mainAutoResonanceListener;
    FloatListener mainFilterGainListener;

    SpDelayModeListener mainDelayModeListener;
    FloatListener mainDelayTimeListener;
    FloatListener mainDelayFeedListener;
    FloatListener mainDelayLevelListener;
    FloatListener mainDelayMixListener;



    OverDriveModeListener OverdriveModeListener;
    FloatListener OverdriveFreqListener;
    FloatListener OverdriveGainUpListener;
    FloatListener OverdriveThreshListener;

    ADSRModeListener egModeListener;
    FloatListener egAttacklistener;
    FloatListener egDecaylistener;
    FloatListener egSustainlistener;
    FloatListener egReleaselistener;
    FloatListener egVeloSenslistener;

    ADSRModeListener egFModeListener;
    FloatListener egFAttacklistener;
    FloatListener egFDecaylistener;
    FloatListener egFSustainlistener;
    FloatListener egFReleaselistener;
    FloatListener egFVeloSenslistener;
};