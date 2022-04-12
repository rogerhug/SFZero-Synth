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


const String PluginParameters::OverdriveGainUp_Id = "overdriveGainUp";
const String PluginParameters::OverdriveGainUp_Name = TRANS("OverdriveGainUp");
const String PluginParameters::OverdriveGainUp_Label;

const String PluginParameters::OverdriveThresh_Id = "overdriveThresh";
const String PluginParameters::OverdriveThresh_Name = TRANS("OverdriveThresh");
const String PluginParameters::OverdriveThresh_Label;

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


PluginParameters::PluginParameters(AudioProcessorValueTreeState& vts)
    : valueTreeState(vts)
    //attachment
    , mainVolumeAttachment(nullptr)
   , mainVolumeModAttachment(nullptr)
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
    , OverdriveGainUpAttachment(nullptr)
    , OverdriveThreshAttachment(nullptr)
    ,egModeAttachment(nullptr)
    , egAttackAttachment(nullptr)
    , egDecayAttachment(nullptr)
    , egSustainAttachment(nullptr)
    , egReleaseAttachment(nullptr)
    , egVeloSensAttachment(nullptr)
    , egFModeAttachment(nullptr)
    , egFAttackAttachment(nullptr)
    , egFDecayAttachment(nullptr)
    , egFSustainAttachment(nullptr)
    , egFReleaseAttachment(nullptr)
    , egFVeloSensAttachment(nullptr)
   
          //listeners
    , mainVolumeListener(mainVolumeValue)
    , mainVolumeModListener(mainVolumeModValue)
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

    , OverdriveModeListener(ovmode)
    , OverdriveFreqListener(OverdriveFreqValue)
    , OverdriveGainUpListener(OverdriveGainUpValue)
    , OverdriveThreshListener(OverdriveThreshValue)
    , egModeListener(egmode)
    , egAttacklistener(egAttackValue)
    , egDecaylistener(egDecayValue)
    , egSustainlistener(egSustainValue)
    , egReleaselistener(egReleaseValue)
    , egVeloSenslistener(egVeloSensValue)
    , egFModeListener(egFmode)
    , egFAttacklistener(egFAttackValue)
    , egFDecaylistener(egFDecayValue)
    , egFSustainlistener(egFSustainValue)
    , egFReleaselistener(egFReleaseValue)
    , egFVeloSenslistener(egFVeloSensValue)
{

    mainVolumeValue = 1.0;
    mainVolumeModValue = 1.;
    mainPitchValue = 120;
    mainFilterModeV.setIndex(0);
    mainCutoffValue = 0.99;
    mainCutoffModValue = 1.0;
    mainResonanceValue = 0.3;
    mainAutoResonanceValue = false;
    mainFilterGainValue = 0.5;
    mainDelayModeV.setIndex(0);
    mainDelayTimeValue = 0.5;
    mainDelayFeedValue = 0.5;
    mainDelayLevelValue = 0.5;
    mainDelayMixValue = 0.0;


    ovmode.setIndex(0);
    OverdriveFreqValue = 0.7;
    OverdriveGainUpValue = 0.5;
    OverdriveThreshValue = 0.7;

    egmode.setIndex(0);
    egAttackValue = 0.0;
    egDecayValue = 1.0;
    egSustainValue = 1.;
    egReleaseValue = 0.2;
    egVeloSensValue = 0.0;
   
    egFmode.setIndex(0);
    egFAttackValue = 0.0;
    egFDecayValue = 1.0;
    egFSustainValue = 0.5;
    egFReleaseValue = 0.2;
    egFVeloSensValue = 0.0;

    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

}





void PluginParameters::createAllParameters()
{
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
        NormalisableRange<float>(0.01f, 1.0f, 0.001f),
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
        NormalisableRange<float>(0.0f, (float)(OverDriveMode::kChoices - 1), 1.0f),
        (float)ovmode.getIndex(),
        EQMode::floatToText,
        EQMode::textToFloat);
    valueTreeState.addParameterListener(OverdriveMode_Id, &OverdriveModeListener);
    


    valueTreeState.createAndAddParameter(OverdriveFreq_Id, OverdriveFreq_Name, OverdriveFreq_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
        OverdriveFreqValue,
        [](float value) { return String(value); },
        [](const String& text) { return text.getFloatValue(); });
    valueTreeState.addParameterListener(OverdriveFreq_Id, &OverdriveFreqListener);


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


    //---------------------ampenvelope---------------------------------

    valueTreeState.createAndAddParameter(egMode_Id, egMode_Name, egMode_Label,
        NormalisableRange<float>(0.0f, (float)(ADSRMode::kChoices - 1), 1.0f),
        (float)egmode.getIndex(),
        ADSRMode::floatToText,
        ADSRMode::textToFloat);
    valueTreeState.addParameterListener(egMode_Id, &egModeListener);


    valueTreeState.createAndAddParameter(egAttack_Id, egAttack_Name, egAttack_Label,
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
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
        NormalisableRange<float>(0.0f, 1.0f, 0.001f),
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
}

void PluginParameters::detachControls()
{    delete mainVolumeAttachment;
     delete mainVolumeModAttachment;
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
    delete OverdriveGainUpAttachment;
    delete OverdriveThreshAttachment;
    delete egModeAttachment;
    delete egAttackAttachment;
    delete egDecayAttachment;
    delete egSustainAttachment;
    delete egReleaseAttachment;
    delete egVeloSensAttachment;
    delete egFModeAttachment;
    delete egFAttackAttachment;
    delete egFDecayAttachment;
    delete egFSustainAttachment;
    delete egFReleaseAttachment;
    delete egFVeloSensAttachment;
}

void PluginParameters::attachControls(
     Slider& mainPitchSlider
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
    ,ComboBox& OverdriveModeTempSlider
    ,Slider& OverdriveFreqSlider
    ,Slider& OverdriveGainUpSlider
    ,Slider& OverdriveThreshSlider
    ,ComboBox& egModeCombo
    ,Slider& egAttackSlider
    , Slider& egDecaySlider
    , Slider& egSustainSlider
    , Slider& egReleaseSlider
    , Slider& egVeloSensSlider
    , ComboBox& egFModeCombo
    , Slider& egFAttackSlider
    , Slider& egFDecaySlider
    , Slider& egFSustainSlider
    , Slider& egFReleaseSlider
    , Slider& egFVeloSensSlider
  )
{
    detachControls();
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



   OverdriveModeAttachment = new ComboBoxAttachment(valueTreeState, OverdriveMode_Id, OverdriveModeTempSlider);
   OverdriveFreqAttachment = new SliderAttachment(valueTreeState, OverdriveFreq_Id, OverdriveFreqSlider);
   OverdriveGainUpAttachment = new SliderAttachment(valueTreeState, OverdriveGainUp_Id, OverdriveGainUpSlider);
   OverdriveThreshAttachment = new SliderAttachment(valueTreeState, OverdriveThresh_Id, OverdriveThreshSlider);

   egModeAttachment = new ComboBoxAttachment(valueTreeState, egMode_Id, egModeCombo);
   egAttackAttachment = new SliderAttachment(valueTreeState, egAttack_Id, egAttackSlider);
   egDecayAttachment = new SliderAttachment(valueTreeState, egDecay_Id, egDecaySlider);
   egSustainAttachment = new SliderAttachment(valueTreeState, egSustain_Id, egSustainSlider);
   egReleaseAttachment = new SliderAttachment(valueTreeState, egRelease_Id, egReleaseSlider);
   egVeloSensAttachment = new SliderAttachment(valueTreeState, egVeloSens_Id, egVeloSensSlider);

   egFModeAttachment = new ComboBoxAttachment(valueTreeState, egFMode_Id, egFModeCombo);
   egFAttackAttachment = new SliderAttachment(valueTreeState, egFAttack_Id, egFAttackSlider);
   egFDecayAttachment = new SliderAttachment(valueTreeState, egFDecay_Id, egFDecaySlider);
   egFSustainAttachment = new SliderAttachment(valueTreeState, egFSustain_Id, egFSustainSlider);
   egFReleaseAttachment = new SliderAttachment(valueTreeState, egFRelease_Id, egFReleaseSlider);
   egFVeloSensAttachment = new SliderAttachment(valueTreeState, egFVeloSens_Id, egFVeloSensSlider);

}
