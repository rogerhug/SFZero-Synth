
#include"Eutils.h"


const StringArray FilterMode::names = { "filter.Off", "filter.Lp", "filter.Hp", "filter.Bp", "filter.Allp","filter.notch","filter.Bell","lowShelf","HighShelf" };
int FilterMode::textToIndex(const String& s)
{
    for (int i = 0; i < kNumberOfFilterModeTypes; i++) if (s == names[i]) return i;
    
    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;
}

void FilterMode::setFromName(String wfName)
{
    index = (FilterModeTypeIndex)textToIndex(wfName);
}

String FilterMode::name()
{
    return names[index];
}

void FilterMode::setIndex(int i)
{
    if (i < 0) i = 0;
    if (i >= kNumberOfFilterModeTypes) i = kNumberOfFilterModeTypes - 1;
    index = (FilterModeTypeIndex)i;
}

void FilterMode::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfFilterModeTypes; i++)
        cb.addItem(names[i], i + 1);
}

const StringArray SamplePlayMode::names = { "Off", "One-shoot", "Seq-loop" ,"Midi"};
int SamplePlayMode::textToIndex(const String& s)
{
    for (int i = 0; i < kNumberOfPlayModeTypes; i++) if (s == names[i]) return i;
    
    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;
}

void SamplePlayMode::setFromName(String wfName)
{
    index = (PlayModeTypeIndex)textToIndex(wfName);
}

String SamplePlayMode::name()
{
    return names[index];
}

void SamplePlayMode::setIndex(int i)
{
    if (i < 0) i = 0;
    if (i >= kNumberOfPlayModeTypes) i = kNumberOfPlayModeTypes - 1;
    index = (PlayModeTypeIndex)i;
}

void SamplePlayMode::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfPlayModeTypes; i++)
        cb.addItem(names[i], i + 1);
}

const StringArray DelayMode::names = { "delay.off", "delay.free", "delay.sync", "delay.mode1","delay.mode2","delay.mode3" };
String DelayMode::name()
{
    return names[index];
}

void DelayMode::setupComboBox(juce::ComboBox &cb) { 
    for (int i = 0; i < kNumberOfTypes; i++)
        cb.addItem(names[i], i + 1);
}


void DelayMode::setIndex(int i) { 
    if (i < 0) i = 0;
    if (i >= kNumberOfTypes) i = kNumberOfTypes - 1;
    index = (DelayModeTypeIndex)i;
}

int DelayMode::textToIndex(const juce::String &s) { 
    for (int i = 0; i < kNumberOfTypes; i++) if (s == names[i]) return i;
    
    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;
}


const StringArray TimeMode::names = { "Off", "<PPQ>", "<CHRONO>", "<SAMPELS>" };

int TimeMode::textToIndex(const juce::String &s) { 
    for (int i = 0; i < kNumberOfTypes; i++) if (s == names[i]) return i;
    
    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;;
}


void TimeMode::setupComboBox(juce::ComboBox &cb) { 
    for (int i = 0; i < kNumberOfTypes; i++)
        cb.addItem(names[i], i + 1);
}


void TimeMode::setIndex(int i) { 
    if (i < 0) i = 0;
    if (i >= kNumberOfTypes) i = kNumberOfTypes - 1;
    index = (TimeModeTypeIndex)i;;
}


void TimeMode::setFromName(juce::String wfName) { 
    index = (TimeModeTypeIndex)textToIndex(wfName);
}


juce::String TimeMode::name() { 
    return names[index];
}

const StringArray TimeDivMode::names = { "Qrt", "1/2", "1/3", "1/4","1/6","1/8","1/12","1/16","1/32","1/64" };

int TimeDivMode::textToIndex(const juce::String &s) {
    for (int i = 0; i < kNumberOfTypes; i++) if (s == names[i]) return i;
    
    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;;
}

juce::String TimeDivMode::name() {
    return names[index];
}
void TimeDivMode::setupComboBox(juce::ComboBox &cb) { 
    for (int i = 0; i < kNumberOfTypes; i++)
        cb.addItem(names[i], i + 1);
}


void TimeDivMode::setIndex(int i) { 
    if (i < 0) i = 0;
    if (i >= kNumberOfTypes) i = kNumberOfTypes - 1;
    index = (TimeDivModeTypeIndex)i;
}


void TimeDivMode::setFromName(juce::String wfName) { 
 index = (TimeDivModeTypeIndex)textToIndex(wfName);
}

const StringArray LfoRtrMode::names = { "Off", "rt16", "rt32", "rt48","rt64","rt96","rt128" };

int LfoRtrMode::textToIndex(const juce::String &s) {
    for (int i = 0; i < kNumberOfTypes; i++) if (s == names[i]) return i;
    
    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;;
}

juce::String LfoRtrMode::name() {
    return names[index];
}
void LfoRtrMode::setupComboBox(juce::ComboBox &cb) {
    for (int i = 0; i < kNumberOfTypes; i++)
        cb.addItem(names[i], i + 1);
}


void LfoRtrMode::setIndex(int i) {
    if (i < 0) i = 0;
    if (i >= kNumberOfTypes) i = kNumberOfTypes - 1;
    index = (LfoRtrModeTypeIndex)i;
}


void LfoRtrMode::setFromName(juce::String wfName) {
    index = (LfoRtrModeTypeIndex)textToIndex(wfName);
}

const StringArray SampelSetMode::names = { "preset", "Drums", "Synth"
};
int SampelSetMode::textToIndex(const juce::String &s) {
    for (int i = 0; i < kNumberOfTypes; i++) if (s == names[i]) return i;
    
    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;;
}
juce::String SampelSetMode::name() { 
   return names[index];
}

void SampelSetMode::setFromName(juce::String wfName) { 
   index = (SampelSetModeTypeIndex)textToIndex(wfName);
}

void SampelSetMode::setupComboBox(juce::ComboBox &cb) { 
    for (int i = 0; i < kNumberOfTypes; i++)
        cb.addItem(names[i], i + 1);
}

void SampelSetMode::setIndex(int i) { 
    if (i < 0) i = 0;
    if (i >= kNumberOfTypes) i = kNumberOfTypes - 1;
    index = (SampelSetModeTypeIndex)i;
}



const StringArray SampelHoldMode::names = { "SpHoldOff", "SpHold16", "SpHold32", "SpHold64",
    "SpHold96","SpHold128"
};

juce::String SampelHoldMode::name() {
     return names[index];
}

void SampelHoldMode::setFromName(juce::String wfName) { 
  index = (SampelHoldModeTypeIndex)textToIndex(wfName);
}

void SampelHoldMode::setIndex(int i) { 
    if (i < 0) i = 0;
    if (i >= kNumberOfTypes) i = kNumberOfTypes - 1;
    index = (SampelHoldModeTypeIndex)i;
}

void SampelHoldMode::setupComboBox(juce::ComboBox &cb) { 
    for (int i = 0; i < kNumberOfTypes; i++)
        cb.addItem(names[i], i + 1);
}

int SampelHoldMode::textToIndex(const juce::String &s) { 
    for (int i = 0; i < kNumberOfTypes; i++) if (s == names[i]) return i;
    
    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;;

}
const StringArray MidiCCMode::names = { "Off_>VST3-learn_?cc", "fix-Unused_CCs", "fix-Empty", "fix-Empty" };
int MidiCCMode::textToIndex(const String& s)
{
    for (int i = 0; i < kNumberOfTypes; i++) if (s == names[i]) return i;

    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;;
}

String MidiCCMode::name()
{
    return names[index];
}

void MidiCCMode::setFromName(String wfName)
{
    index = (MidiCCModeTypeIndex)textToIndex(wfName);
}

void MidiCCMode::setIndex(int i)
{
    if (i < 0) i = 0;
    if (i >= kNumberOfTypes) i = kNumberOfTypes - 1;
    index = (MidiCCModeTypeIndex)i;
}

void MidiCCMode::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfTypes; i++)
        cb.addItem(names[i], i + 1);
}

int EQMode::textToIndex(const String& s)
{
    for (int i = 0; i < kNumberOfEQModeTypes; i++) if (s == names[i]) return i;

    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;
}
const StringArray EQMode::names = { "EQ->off", "EQ->soft", "EQ->Punch", "EQ->Punch2" };
String EQMode::name()
{
    return names[index];
}

void EQMode::setFromName(String wfName)
{
    index = (EQModeTypeIndex)textToIndex(wfName);
}

void EQMode::setIndex(int i)
{
    if (i < 0) i = 0;
    if (i >= kNumberOfEQModeTypes) i = kNumberOfEQModeTypes - 1;
    index = (EQModeTypeIndex)i;
}

void EQMode::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfEQModeTypes; i++)
        cb.addItem(names[i], i + 1);
}
const StringArray LimiterMode::names = { "Limit->off", "Limit->short", "Limit->Long", "Limit->Auto" };
int LimiterMode::textToIndex(const String& s)
{
    for (int i = 0; i < kNumberOfLimiterModeTypes; i++) if (s == names[i]) return i;

    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;
}

String LimiterMode::name()
{
    return names[index];
}

void LimiterMode::setFromName(String wfName)
{
    index = (LimiterModeTypeIndex)textToIndex(wfName);
}

void LimiterMode::setIndex(int i)
{
    if (i < 0) i = 0;
    if (i >= kNumberOfLimiterModeTypes) i = kNumberOfLimiterModeTypes - 1;
    index = (LimiterModeTypeIndex)i;
}

void LimiterMode::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfLimiterModeTypes; i++)
        cb.addItem(names[i], i + 1);
}
const StringArray OverDriveMode::names = { "Shape->off", "Shape->Hp", "Shape->Bp", "Shape->Lp" };
int OverDriveMode::textToIndex(const String& s)
{
    for (int i = 0; i < kNumberOfOvModeTypes; i++) if (s == names[i]) return i;

    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;
}

String OverDriveMode::name()
{
    return names[index];
}

void OverDriveMode::setFromName(String wfName)
{
    index = (OverDriveModeTypeIndex)textToIndex(wfName);
}

void OverDriveMode::setIndex(int i)
{
    if (i < 0) i = 0;
    if (i >= kNumberOfOvModeTypes) i = kNumberOfOvModeTypes - 1;
    index = (OverDriveModeTypeIndex)i;
}

void OverDriveMode::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfOvModeTypes; i++)
        cb.addItem(names[i], i + 1);
}
const StringArray ADSRMode::names = { "Env->off", "Env->Analog", "Env->Linear", "Env->Lineardb" };
int ADSRMode::textToIndex(const String& s)
{
    for (int i = 0; i < kNumberOfModeTypes; i++) if (s == names[i]) return i;

    // Were we given an invalid waveform name?
    jassertfalse;
    return 0;
}

String ADSRMode::name()
{
    return names[index];
}

void ADSRMode::setFromName(String wfName)
{
    index = (ADSRModeTypeIndex)textToIndex(wfName);
}

void ADSRMode::setIndex(int i)
{
    if (i < 0) i = 0;
    if (i >= kNumberOfModeTypes) i = kNumberOfModeTypes - 1;
    index = (ADSRModeTypeIndex)i;
}

void ADSRMode::setupComboBox(ComboBox& cb)
{
    for (int i = 0; i < kNumberOfModeTypes; i++)
        cb.addItem(names[i], i + 1);
}
