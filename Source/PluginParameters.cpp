/*
  ==============================================================================

    PluginParameters.cpp
    Created: 29 Mar 2022 1:17:58pm
    Author:  r7

  ==============================================================================
*/

#include <JuceHeader.h>
#include "PluginParameters.h"

//==============================================================================

const String PluginParameters::mainPitchBend_Id = "pitchBender";
const String PluginParameters::mainPitchBend_Name = TRANS("PitchBender");
const String PluginParameters::mainPitchBend_Label;

const String PluginParameters::mainPitch_Id = "mainPitch";
const String PluginParameters::mainPitch_Name = TRANS("MainPitch");
const String PluginParameters::mainPitch_Label;

const String PluginParameters::mainVolume_Id = "mainVolume";
const String PluginParameters::mainVolume_Name = TRANS("MainVolume");
const String PluginParameters::mainVolume_Label;

const String PluginParameters::mainVolumeMod_Id = "mainVolumeMod";
const String PluginParameters::mainVolumeMod_Name = TRANS("MainVolumeMod");
const String PluginParameters::mainVolumeMod_Label;

const String PluginParameters::mainCutoff_Id = "maincut";
const String PluginParameters::mainCutoff_Name = TRANS("MainCut");
const String PluginParameters::mainCutoff_Label;

const String PluginParameters::mainFilterGain_Id = "mainfiltergain";
const String PluginParameters::mainFilterGain_Name = TRANS("MainFilterGain");
const String PluginParameters::mainFilterGain_Label;


const String PluginParameters::mainCutoffMod_Id = "maincutm";
const String PluginParameters::mainCutoffMod_Name = TRANS("MainCutm");
const String PluginParameters::mainCutoffMod_Label;


const String PluginParameters::mainResonance_Id = "main1res";
const String PluginParameters::mainResonance_Name = TRANS("MainRes");
const String PluginParameters::mainResonance_Label;

const String PluginParameters::mainAutoResonance_Id = "mainAutores";
const String PluginParameters::mainAutoResonance_Name = TRANS("MainAutoRes");
const String PluginParameters::mainAutoResonance_Label;

const String PluginParameters::mainFilterMode_Id = "mainvcfm";
const String PluginParameters::mainFilterMode_Name = TRANS("MainVcfm");
const String PluginParameters::mainFilterMode_Label;

const String PluginParameters::mainDelayMode_Id = "mainDelayMode";
const String PluginParameters::mainDelayMode_Name = TRANS("MainDelayMode");
const String PluginParameters::mainDelayMode_Label;

const String PluginParameters::mainDelayTime_Id = "mainDelayTime";
const String PluginParameters::mainDelayTime_Name = TRANS("MainDelayTime");
const String PluginParameters::mainDelayTime_Label;

const String PluginParameters::mainDelayFeed_Id = "mainDelayFeed";
const String PluginParameters::mainDelayFeed_Name = TRANS("MainDelayFeed");
const String PluginParameters::mainDelayFeed_Label;

const String PluginParameters::mainDelayLevel_Id = "mainDelayLevel";
const String PluginParameters::mainDelayLevel_Name = TRANS("MainDelayLevel");
const String PluginParameters::mainDelayLevel_Label;

const String PluginParameters::mainDelayMix_Id = "mainDelayMix";
const String PluginParameters::mainDelayMix_Name = TRANS("MainDelayMix");
const String PluginParameters::mainDelayMix_Label;




const String PluginParameters::OverdriveMode_Id = "overdriveMode";
const String PluginParameters::OverdriveMode_Name = TRANS("OverdriveMode");
const String PluginParameters::OverdriveMode_Label;


const String PluginParameters::OverdriveFreq_Id = "overdriveFreq";
const String PluginParameters::OverdriveFreq_Name = TRANS("OverdriveFreq");
const String PluginParameters::OverdriveFreq_Label;

const String PluginParameters::OverdriveFreqMod_Id = "overdriveFreqMod";
const String PluginParameters::OverdriveFreqMod_Name = TRANS("OverdriveFreqMod");
const String PluginParameters::OverdriveFreqMod_Label;


const String PluginParameters::OverdriveGainUp_Id = "overdriveGainUp";
const String PluginParameters::OverdriveGainUp_Name = TRANS("OverdriveGainUp");
const String PluginParameters::OverdriveGainUp_Label;

const String PluginParameters::OverdriveThresh_Id = "overdriveThresh";
const String PluginParameters::OverdriveThresh_Name = TRANS("OverdriveThresh");
const String PluginParameters::OverdriveThresh_Label;

const String PluginParameters::RingMode_Id = "ringMode";
const String PluginParameters::RingMode_Name = TRANS("RingMode");
const String PluginParameters::RingMode_Label;

const String PluginParameters::RingHz_Id = "ringHz";
const String PluginParameters::RingHz_Name = TRANS("RingHz");
const String PluginParameters::RingHz_Label;

const String PluginParameters::RingMod_Id = "ringMod";
const String PluginParameters::RingMod_Name = TRANS("RingMod");
const String PluginParameters::RingMod_Label;

const String PluginParameters::RingLHz_Id = "ringLHz";
const String PluginParameters::RingLHz_Name = TRANS("RingLHz");
const String PluginParameters::RingLHz_Label;

const String PluginParameters::egModePoly_Id = "egModePoly";
const String PluginParameters::egModePoly_Name = TRANS("EgModePoly");
const String PluginParameters::egModePoly_Label;

const String PluginParameters::egMode_Id = "egMode";
const String PluginParameters::egMode_Name = TRANS("EgMode");
const String PluginParameters::egMode_Label;

const String PluginParameters::egAttack_Id = "egAttack";
const String PluginParameters::egAttack_Name = TRANS("EgAttack");
const String PluginParameters::egAttack_Label;

const String PluginParameters::egDecay_Id = "egDecay";
const String PluginParameters::egDecay_Name = TRANS("EgDecay");
const String PluginParameters::egDecay_Label;

const String PluginParameters::egSustain_Id = "egSustain";
const String PluginParameters::egSustain_Name = TRANS("EgSustain");
const String PluginParameters::egSustain_Label;

const String PluginParameters::egRelease_Id = "egRelease";
const String PluginParameters::egRelease_Name = TRANS("EgRelease");
const String PluginParameters::egRelease_Label;

const String PluginParameters::egVeloSens_Id = "egVeloSens";
const String PluginParameters::egVeloSens_Name = TRANS("EgVelosens");
const String PluginParameters::egVeloSens_Label;

const String PluginParameters::egSmSens_Id = "egSmSens";
const String PluginParameters::egSmSens_Name = TRANS("EgSmSens");
const String PluginParameters::egSmSens_Label;

const String PluginParameters::egFMode_Id = "egFMode";
const String PluginParameters::egFMode_Name = TRANS("EgFMode");
const String PluginParameters::egFMode_Label;


const String PluginParameters::egFAttack_Id = "egFAttack";
const String PluginParameters::egFAttack_Name = TRANS("EgFAttack");
const String PluginParameters::egFAttack_Label;

const String PluginParameters::egFDecay_Id = "egFDecay";
const String PluginParameters::egFDecay_Name = TRANS("EgFDecay");
const String PluginParameters::egFDecay_Label;

const String PluginParameters::egFSustain_Id = "egFSustain";
const String PluginParameters::egFSustain_Name = TRANS("EgFSustain");
const String PluginParameters::egFSustain_Label;

const String PluginParameters::egFRelease_Id = "egFRelease";
const String PluginParameters::egFRelease_Name = TRANS("EgFRelease");
const String PluginParameters::egFRelease_Label;

const String PluginParameters::egFVeloSens_Id = "egFVeloSens";
const String PluginParameters::egFVeloSens_Name = TRANS("EgFVelosens");
const String PluginParameters::egFVeloSens_Label;

const String PluginParameters::egFSmSens_Id = "egFSmSens";
const String PluginParameters::egFSmSens_Name = TRANS("EgFSmSens");
const String PluginParameters::egFSmSens_Label;


PluginParameters::PluginParameters(AudioProcessorValueTreeState& vts)
    : valueTreeState(vts)
    //attachment
    , mainVolumeAttachment(nullptr)
    , mainVolumeModAttachment(nullptr)
    , mainPitchBendAttachment(nullptr)
    , mainPitchAttachment(nullptr)
    , mainFilterCutAttachment(nullptr)
    , mainFilterCutModAttachment(nullptr)
    , mainFilterResAttachment(nullptr)
    , mainFilterAutoResonanceAttachment(nullptr)
    , mainFilterGainAttachment(nullptr)
    , mainFilterModeAttachment(nullptr)
    , mainDelayModeComboxAttachment(nullptr)
    , mainDelayTimeAttachment(nullptr)
    , mainDelayFeedAttachment(nullptr)
    , mainDelayLevelAttachment(nullptr)
    , mainDelayMixAttachment(nullptr)

    , OverdriveModeAttachment(nullptr)
    , OverdriveFreqAttachment(nullptr)
    , OverdriveFreqModAttachment(nullptr)
    , OverdriveGainUpAttachment(nullptr)
    , OverdriveThreshAttachment(nullptr)
    , RingOnOffAttachment(nullptr)
    ,RingHzAttachment(nullptr)
    ,RingModAttachment(nullptr)
    ,RingLHzAttachment(nullptr)
    , egModePolyAttachment(nullptr)
    , egModeAttachment(nullptr)
    , egAttackAttachment(nullptr)
    , egDecayAttachment(nullptr)
    , egSustainAttachment(nullptr)
    , egReleaseAttachment(nullptr)
    , egVeloSensAttachment(nullptr)
    , egSmSensAttachment(nullptr)
    , egFModeAttachment(nullptr)
    , egFAttackAttachment(nullptr)
    , egFDecayAttachment(nullptr)
    , egFSustainAttachment(nullptr)
    , egFReleaseAttachment(nullptr)
    , egFVeloSensAttachment(nullptr)
    , egFSmSensAttachment(nullptr)
   
          //listeners
    , mainVolumeListener(mainVolumeValue)
    , mainVolumeModListener(mainVolumeModValue)
    , mainPitchBendListener(mainPitchBendValue)
    , mainPitchListener(mainPitchValue)
    , mainFilterModusListener(mainFilterModeV)
    , mainCutoffListener(mainCutoffValue)
    , mainCutoffListenerMod(mainCutoffModValue)
    , mainResonanceListener(mainResonanceValue)
   ,mainAutoResonanceListener(mainAutoResonanceValue)
    ,mainFilterGainListener(mainFilterGainValue)
    ,mainDelayModeListener(mainDelayModeV)
    , mainDelayTimeListener(mainDelayTimeValue)
    , mainDelayFeedListener(mainDelayFeedValue)
    , mainDelayLevelListener(mainDelayLevelValue)
    , mainDelayMixListener(mainDelayMixValue)

    , OverdriveModeListener(OverdriveModevalue)
    , OverdriveFreqListener(OverdriveFreqValue)
    , OverdriveFreqModListener(OverdriveFreqModValue)
    , OverdriveGainUpListener(OverdriveGainUpValue)
    , OverdriveThreshListener(OverdriveThreshValue)
    ,RingOnOffListener(RingOnOffValue)
    ,RingHzListener(RingHzValue)
    ,RingModListener(RingModValue)
    ,RingLHzListener(RingLHzValue)
    , egModePolyListener(egModePolyValue)
    , egModeListener(egmode)
    , egAttacklistener(egAttackValue)
    , egDecaylistener(egDecayValue)
    , egSustainlistener(egSustainValue)
    , egReleaselistener(egReleaseValue)
    , egVeloSenslistener(egVeloSensValue)
    , egSmSenslistener(egSmSensValue)
    , egFModeListener(egFmode)
    , egFAttacklistener(egFAttackValue)
    , egFDecaylistener(egFDecayValue)
    , egFSustainlistener(egFSustainValue)
    , egFReleaselistener(egFReleaseValue)
    , egFVeloSenslistener(egFVeloSensValue)
    , egFSmSenslistener(egFSmSensValue)
{

    mainVolumeValue = 1.0f;
    mainVolumeModValue = 1.0f;
    mainPitchValue = 120;
    mainPitchBendValue = 8921;
    mainFilterModeV.setIndex(0);
    mainCutoffValue = 0.99f;
    mainCutoffModValue = 1.0f;
    mainResonanceValue = 0.3f;
    mainAutoResonanceValue = false;
    mainFilterGainValue = 0.5f;
    mainDelayModeV.setIndex(0);
    mainDelayTimeValue = 0.5f;
    mainDelayFeedValue = 0.5f;
    mainDelayLevelValue = 0.5f;
    mainDelayMixValue = 0.0f;


    ovmode.setIndex(0);
    OverdriveModevalue = false;
    OverdriveFreqValue = 0.7f;
    OverdriveFreqModValue = 0.0f;
    OverdriveGainUpValue = 0.5f;
    OverdriveThreshValue = 0.7f;

    RingOnOffValue = false;
    RingHzValue = 0.0f;
    RingModValue = 0.5f;
    RingLHzValue = 0.3f;

    egModePolyValue = true;
    egmode.setIndex(0);
    egAttackValue = 0.0f;
    egDecayValue = 1.0f;
    egSustainValue = 1.0f;
    egReleaseValue = 0.5f;
    egVeloSensValue = 0.0f;
    egSmSensValue = 0.2f;
   
    egFmode.setIndex(0);
    egFAttackValue = 0.0f;
    egFDecayValue = 1.0f;
    egFSustainValue = 1.0f;
    egFReleaseValue = 0.5f;
    egFVeloSensValue = 0.0f;
    egFSmSensValue = 0.2f;

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}





void PluginParameters::createAllParameters()
{

    valueTreeState.createAndAddParameter(mainPitchBend_Id, mainPitchBend_Name, mainPitchBend_Label,
        NormalisableRange<float>(1.0f, 16383.0f, 1.0f),
        mainPitchBendValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainPitchBend_Id, &mainPitchBendListener);

    valueTreeState.createAndAddParameter(mainPitch_Id, mainPitch_Name, mainPitch_Label,
        NormalisableRange<float>(10.0f, 230.0f, 1.0f),
        mainPitchValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainPitch_Id, &mainPitchListener);

    valueTreeState.createAndAddParameter(mainVolume_Id, mainVolume_Name, mainVolume_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001),
        mainVolumeValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainVolume_Id, &mainVolumeListener);

    valueTreeState.createAndAddParameter(mainVolumeMod_Id, mainVolumeMod_Name, mainVolumeMod_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.01),
        mainVolumeModValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainVolumeMod_Id, &mainVolumeModListener);


    valueTreeState.createAndAddParameter(mainCutoff_Id, mainCutoff_Name, mainCutoff_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        mainCutoffValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainCutoff_Id, &mainCutoffListener);

    valueTreeState.createAndAddParameter(mainCutoffMod_Id, mainCutoffMod_Name, mainCutoffMod_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        mainCutoffModValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainCutoffMod_Id, &mainCutoffListenerMod);

    valueTreeState.createAndAddParameter(mainResonance_Id, mainResonance_Name, mainResonance_Label,
        NormalisableRange<float>(0.001f, 1.0f, 0.001f),
        mainResonanceValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainResonance_Id, &mainResonanceListener);


    valueTreeState.createAndAddParameter(mainFilterMode_Id, mainFilterMode_Name, mainFilterMode_Label,
        NormalisableRange<float>(0.0f, (float)(FilterMode::kChoices - 1), 1.0f),
        (float)mainFilterModeV.getIndex(),
        FilterMode::floatToText,
        FilterMode::textToFloat);
    valueTreeState.addParameterListener(mainFilterMode_Id, &mainFilterModusListener);

    valueTreeState.createAndAddParameter(mainFilterGain_Id, mainFilterGain_Name, mainFilterGain_Label,
        NormalisableRange<float>(0.01f, 1.0f, 0.001f),
        mainFilterGainValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainFilterGain_Id, &mainFilterGainListener);


    valueTreeState.createAndAddParameter(mainAutoResonance_Id, mainAutoResonance_Name, mainAutoResonance_Label,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        mainAutoResonanceValue ? 1.0f : 0.0f,
        [](float value) { return value < 0.5f ? "no" : "yes"; },
        [](const String& text) { return text == "yes" ? 1.0f : 0.0f; });
    valueTreeState.addParameterListener(mainAutoResonance_Id, &mainAutoResonanceListener);

    valueTreeState.createAndAddParameter(mainDelayMode_Id, mainDelayMode_Name, mainDelayMode_Label,
        NormalisableRange<float>(0.0f, (float)(DelayMode::kChoices - 1), 1.0f),
        (float)mainDelayModeV.getIndex(),
        DelayMode::floatToText,
        DelayMode::textToFloat);
    valueTreeState.addParameterListener(mainDelayMode_Id, &mainDelayModeListener);


    valueTreeState.createAndAddParameter(mainDelayTime_Id, mainDelayTime_Name, mainDelayTime_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001),
        mainDelayTimeValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainDelayTime_Id, &mainDelayTimeListener);

    valueTreeState.createAndAddParameter(mainDelayFeed_Id, mainDelayFeed_Name, mainDelayFeed_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001),
        mainDelayFeedValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainDelayFeed_Id, &mainDelayFeedListener);


    valueTreeState.createAndAddParameter(mainDelayLevel_Id, mainDelayLevel_Name, mainDelayLevel_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001),
        mainDelayLevelValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainDelayLevel_Id, &mainDelayLevelListener);


    valueTreeState.createAndAddParameter(mainDelayMix_Id, mainDelayMix_Name, mainDelayMix_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001),
        mainDelayMixValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(mainDelayMix_Id, &mainDelayMixListener);



    valueTreeState.createAndAddParameter(OverdriveMode_Id, OverdriveMode_Name, OverdriveMode_Label,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        OverdriveModevalue ? 1.0f : 0.0f,
        [](float value) { return value < 0.5f ? "no" : "yes"; },
        [](const String& text) { return text == "yes" ? 1.0f : 0.0f; });
    valueTreeState.addParameterListener(OverdriveMode_Id, &OverdriveModeListener);
    


    valueTreeState.createAndAddParameter(OverdriveFreq_Id, OverdriveFreq_Name, OverdriveFreq_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        OverdriveFreqValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(OverdriveFreq_Id, &OverdriveFreqListener);

    valueTreeState.createAndAddParameter(OverdriveFreqMod_Id, OverdriveFreqMod_Name, OverdriveFreqMod_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        OverdriveFreqModValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(OverdriveFreqMod_Id, &OverdriveFreqModListener);


    valueTreeState.createAndAddParameter(OverdriveGainUp_Id, OverdriveGainUp_Name, OverdriveGainUp_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        OverdriveGainUpValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(OverdriveGainUp_Id, &OverdriveGainUpListener);


    valueTreeState.createAndAddParameter(OverdriveThresh_Id, OverdriveThresh_Name, OverdriveThresh_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        OverdriveThreshValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(OverdriveThresh_Id, &OverdriveThreshListener);


    valueTreeState.createAndAddParameter(RingMode_Id, RingMode_Name, RingMode_Label,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        RingOnOffValue ? 1.0f : 0.0f,
        [](float value) { return value < 0.5f ? "no" : "yes"; },
        [](const String& text) { return text == "yes" ? 1.0f : 0.0f; });
    valueTreeState.addParameterListener(RingMode_Id, &RingOnOffListener);


    valueTreeState.createAndAddParameter(RingHz_Id, RingHz_Name, RingHz_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.00001f),
        RingHzValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(RingHz_Id, &RingHzListener);

    valueTreeState.createAndAddParameter(RingMod_Id, RingMod_Name, RingMod_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.00001f),
        RingModValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(RingMod_Id, &RingModListener);

    valueTreeState.createAndAddParameter(RingLHz_Id, RingLHz_Name, RingLHz_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.00001f),
        RingLHzValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(RingLHz_Id, &RingLHzListener);

    //---------------------ampenvelope---------------------------------

    valueTreeState.createAndAddParameter(egModePoly_Id, egModePoly_Name, egModePoly_Label,
        NormalisableRange<float>(0.0f, 1.0f, 1.0f),
        egModePolyValue ? 1.0f : 0.0f,
        [](float value) { return value < 0.5f ? "no" : "yes"; },
        [](const String& text) { return text == "yes" ? 1.0f : 0.0f; });
    valueTreeState.addParameterListener(egModePoly_Id, &egModePolyListener);


    valueTreeState.createAndAddParameter(egMode_Id, egMode_Name, egMode_Label,
        NormalisableRange<float>(0.0f, (float)(ADSRMode::kChoices - 1), 1.0f),
        (float)egmode.getIndex(),
        ADSRMode::floatToText,
        ADSRMode::textToFloat);
    valueTreeState.addParameterListener(egMode_Id, &egModeListener);


    valueTreeState.createAndAddParameter(egAttack_Id, egAttack_Name, egAttack_Label,
        NormalisableRange<float>(0.0f, 0.9f, 0.001f),
        egAttackValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egAttack_Id, &egAttacklistener);

    valueTreeState.createAndAddParameter(egDecay_Id, egDecay_Name, egDecay_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        egDecayValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egDecay_Id, &egDecaylistener);

    valueTreeState.createAndAddParameter(egSustain_Id, egSustain_Name, egSustain_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        egSustainValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egSustain_Id, &egSustainlistener);

    valueTreeState.createAndAddParameter(egRelease_Id, egRelease_Name, egRelease_Label,
        NormalisableRange<float>(0.02f, 1.0f, 0.001f),
        egReleaseValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egRelease_Id, &egReleaselistener);

    valueTreeState.createAndAddParameter(egVeloSens_Id, egVeloSens_Name, egVeloSens_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        egVeloSensValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egVeloSens_Id, &egVeloSenslistener);

    valueTreeState.createAndAddParameter(egSmSens_Id, egSmSens_Name, egSmSens_Label,
        NormalisableRange<float>(0.001f, 1.0f, 0.001f),
        egSmSensValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egSmSens_Id, &egSmSenslistener);

    //---------------------filterenvelope---------------------------------
    valueTreeState.createAndAddParameter(egFMode_Id, egFMode_Name, egFMode_Label,
        NormalisableRange<float>(0.0f, (float)(ADSRMode::kChoices - 1), 1.0f),
        (float)egFmode.getIndex(),
        ADSRMode::floatToText,
        ADSRMode::textToFloat);
    valueTreeState.addParameterListener(egFMode_Id, &egFModeListener);

    valueTreeState.createAndAddParameter(egFAttack_Id, egFAttack_Name, egFAttack_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        egFAttackValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egFAttack_Id, &egFAttacklistener);

    valueTreeState.createAndAddParameter(egFDecay_Id, egFDecay_Name, egFDecay_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        egFDecayValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egFDecay_Id, &egFDecaylistener);

    valueTreeState.createAndAddParameter(egFSustain_Id, egFSustain_Name, egFSustain_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        egFSustainValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egFSustain_Id, &egFSustainlistener);

    valueTreeState.createAndAddParameter(egFRelease_Id, egFRelease_Name, egFRelease_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        egFReleaseValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egFRelease_Id, &egFReleaselistener);

    valueTreeState.createAndAddParameter(egFVeloSens_Id, egFVeloSens_Name, egFVeloSens_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        egFVeloSensValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egFVeloSens_Id, &egFVeloSenslistener);

    valueTreeState.createAndAddParameter(egFSmSens_Id, egFSmSens_Name, egFSmSens_Label,
        NormalisableRange<float>(0.001f, 1.0f, 0.001f),
        egFSmSensValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(egFSmSens_Id, &egFSmSenslistener);
}

void PluginParameters::detachControls()
{    delete mainVolumeAttachment;
     delete mainVolumeModAttachment;
     delete mainPitchBendAttachment;
    delete mainPitchAttachment;

    delete mainFilterCutAttachment;
    delete mainFilterCutModAttachment;
    delete mainFilterResAttachment;
    delete mainFilterModeAttachment;
    delete mainFilterAutoResonanceAttachment;
    delete mainFilterGainAttachment;
    delete mainDelayModeComboxAttachment;
    delete mainDelayTimeAttachment;
    delete mainDelayFeedAttachment;
    delete mainDelayLevelAttachment;
    delete mainDelayMixAttachment;

    delete OverdriveModeAttachment;
    delete OverdriveFreqAttachment;
    delete OverdriveFreqModAttachment;
    delete OverdriveGainUpAttachment;
    delete OverdriveThreshAttachment;
    delete RingOnOffAttachment;
    delete RingHzAttachment;
    delete RingModAttachment;
    delete RingLHzAttachment;

    delete egModePolyAttachment;
    delete egModeAttachment;
    delete egAttackAttachment;
    delete egDecayAttachment;
    delete egSustainAttachment;
    delete egReleaseAttachment;
    delete egVeloSensAttachment;
    delete egSmSensAttachment;
    delete egFModeAttachment;
    delete egFAttackAttachment;
    delete egFDecayAttachment;
    delete egFSustainAttachment;
    delete egFReleaseAttachment;
    delete egFVeloSensAttachment;
    delete egFSmSensAttachment;
}

void PluginParameters::attachControls(
     Slider& mainPitchBendSlider
     ,Slider& mainPitchSlider
    , Slider& mainVolumeSlider
    , Slider& mainVolumeModSlider
    ,Slider& mainCutoffSlider
    ,Slider& mainFilterGainSlider
    ,Slider& mainCutoffModSlider
    ,Slider& mainResonanceSlider
    ,TextButton& mainAutoResonanceButton
    ,ComboBox& mainFilterModusCombox
    ,ComboBox& mainDelayModeCombox
    , Slider& mainDelayTimeSlider
    , Slider& mainDelayFeedSlider
    , Slider& mainDelayLevelSlider
    , Slider& mainDelayMixSlider
    ,TextButton& OverdriveModeTempSlider
    ,Slider& OverdriveFreqSlider
    , Slider& OverdriveFreqModSlider
    ,Slider& OverdriveGainUpSlider
    ,Slider& OverdriveThreshSlider
    ,TextButton& RingOnOffBut
    ,Slider& RingHzSlider
    ,Slider& RingModSlider
    ,Slider& RingLHzSlider
    ,TextButton& egModePolyButton
    ,ComboBox& egModeCombo
    ,Slider& egAttackSlider
    , Slider& egDecaySlider
    , Slider& egSustainSlider
    , Slider& egReleaseSlider
    , Slider& egVeloSensSlider
    , Slider& egSmSensSlider
    , ComboBox& egFModeCombo
    , Slider& egFAttackSlider
    , Slider& egFDecaySlider
    , Slider& egFSustainSlider
    , Slider& egFReleaseSlider
    , Slider& egFVeloSensSlider
    , Slider& egFSmSensSlider
  )
{
    detachControls();
    mainPitchBendAttachment = new SliderAttachment(valueTreeState, mainPitchBend_Id, mainPitchBendSlider);
    mainPitchAttachment = new SliderAttachment(valueTreeState, mainPitch_Id, mainPitchSlider);
    mainVolumeAttachment = new SliderAttachment(valueTreeState, mainVolume_Id, mainVolumeSlider);
    mainVolumeModAttachment = new SliderAttachment(valueTreeState, mainVolumeMod_Id, mainVolumeModSlider);

    mainFilterCutAttachment = new SliderAttachment(valueTreeState, mainCutoff_Id, mainCutoffSlider);
    mainFilterCutModAttachment = new SliderAttachment(valueTreeState, mainCutoffMod_Id, mainCutoffModSlider);
    mainFilterResAttachment = new SliderAttachment(valueTreeState, mainResonance_Id, mainResonanceSlider);
    mainFilterAutoResonanceAttachment = new ButtonAttachment(valueTreeState, mainAutoResonance_Id, mainAutoResonanceButton);
    mainFilterGainAttachment = new SliderAttachment(valueTreeState, mainFilterGain_Id, mainFilterGainSlider);
    mainFilterModeAttachment = new ComboBoxAttachment(valueTreeState, mainFilterMode_Id, mainFilterModusCombox);

    mainDelayModeComboxAttachment = new ComboBoxAttachment(valueTreeState, mainDelayMode_Id, mainDelayModeCombox);
   mainDelayTimeAttachment = new SliderAttachment(valueTreeState, mainDelayTime_Id, mainDelayTimeSlider);
   mainDelayFeedAttachment = new SliderAttachment(valueTreeState, mainDelayFeed_Id, mainDelayFeedSlider);
   mainDelayLevelAttachment = new SliderAttachment(valueTreeState, mainDelayLevel_Id, mainDelayLevelSlider);
   mainDelayMixAttachment = new SliderAttachment(valueTreeState, mainDelayMix_Id, mainDelayMixSlider);



   OverdriveModeAttachment = new ButtonAttachment(valueTreeState, OverdriveMode_Id, OverdriveModeTempSlider);
   OverdriveFreqAttachment = new SliderAttachment(valueTreeState, OverdriveFreq_Id, OverdriveFreqSlider);
   OverdriveFreqModAttachment = new SliderAttachment(valueTreeState, OverdriveFreqMod_Id, OverdriveFreqModSlider);
   OverdriveGainUpAttachment = new SliderAttachment(valueTreeState, OverdriveGainUp_Id, OverdriveGainUpSlider);
   OverdriveThreshAttachment = new SliderAttachment(valueTreeState, OverdriveThresh_Id, OverdriveThreshSlider);

   RingOnOffAttachment = new ButtonAttachment(valueTreeState,  RingMode_Id, RingOnOffBut);
   RingHzAttachment = new SliderAttachment(valueTreeState, RingHz_Id, RingHzSlider);
   RingLHzAttachment = new SliderAttachment(valueTreeState, RingLHz_Id, RingLHzSlider);
   RingModAttachment = new SliderAttachment(valueTreeState, RingMod_Id, RingModSlider);
   egModePolyAttachment = new ButtonAttachment(valueTreeState, egModePoly_Id, egModePolyButton);

   egModeAttachment = new ComboBoxAttachment(valueTreeState, egMode_Id, egModeCombo);
   egAttackAttachment = new SliderAttachment(valueTreeState, egAttack_Id, egAttackSlider);
   egDecayAttachment = new SliderAttachment(valueTreeState, egDecay_Id, egDecaySlider);
   egSustainAttachment = new SliderAttachment(valueTreeState, egSustain_Id, egSustainSlider);
   egReleaseAttachment = new SliderAttachment(valueTreeState, egRelease_Id, egReleaseSlider);
   egVeloSensAttachment = new SliderAttachment(valueTreeState, egVeloSens_Id, egVeloSensSlider);
   egSmSensAttachment = new SliderAttachment(valueTreeState, egSmSens_Id, egSmSensSlider);

   egFModeAttachment = new ComboBoxAttachment(valueTreeState, egFMode_Id, egFModeCombo);
   egFAttackAttachment = new SliderAttachment(valueTreeState, egFAttack_Id, egFAttackSlider);
   egFDecayAttachment = new SliderAttachment(valueTreeState, egFDecay_Id, egFDecaySlider);
   egFSustainAttachment = new SliderAttachment(valueTreeState, egFSustain_Id, egFSustainSlider);
   egFReleaseAttachment = new SliderAttachment(valueTreeState, egFRelease_Id, egFReleaseSlider);
   egFVeloSensAttachment = new SliderAttachment(valueTreeState, egFVeloSens_Id, egFVeloSensSlider);
   egFSmSensAttachment = new SliderAttachment(valueTreeState, egFSmSens_Id, egFSmSensSlider);

}
