
#pragma once
#include "../JuceLibraryCode/JuceHeader.h"

class FilterMode
{
private:
    enum FilterModeTypeIndex {
        kOff,kLp, kBp2, kHp, kNp,kAp,kBL,kHs,kLs,
        kNumberOfFilterModeTypes
    } index;
    
    static int textToIndex(const String& s);

    
public:
    // default constructor
    FilterMode() : index(kOff) {}
    
    // set to default state after construction
    void setToDefault() { index = kOff; }
    
    // get index as a 0-based integer
    int getIndex() { return (int)index; }
    
    // serialize: get human-readable name of this waveform
    String name();
    
    // deserialize: set index based on given name
    void setFromName(String wfName);
    
    // set index directly as an integer
    void setIndex(int i);
    
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    
public:
    // waveform names: ordered list of string literals
    static const StringArray names;
    
    static const int kChoices = kNumberOfFilterModeTypes;
    
    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi +0.5f)]; }
};
class EQMode
{
private:
    enum EQModeTypeIndex {
        kOff, kLp, kBp2, kHp,
        kNumberOfEQModeTypes
    } index;

    static int textToIndex(const String& s);


public:
    // default constructor
    EQMode() : index(kOff) {}

    // set to default state after construction
    void setToDefault() { index = kOff; }

    // get index as a 0-based integer
    int getIndex() { return (int)index; }

    // serialize: get human-readable name of this waveform
    String name();

    // deserialize: set index based on given name
    void setFromName(String wfName);

    // set index directly as an integer
    void setIndex(int i);

    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);

public:
    // waveform names: ordered list of string literals
    static const StringArray names;

    static const int kChoices = kNumberOfEQModeTypes;

    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi + 0.5f)]; }
};
class SamplePlayMode
{
private:
    enum PlayModeTypeIndex {
        kOff, kOneShoot, kOneShootLoop,kMidi,
        kNumberOfPlayModeTypes
    } index;
    
    static int textToIndex(const String& s);
    

    
public:
    // default constructor
    SamplePlayMode() : index(kOff) {}
    
    // set to default state after construction
    void setToDefault() { index = kOff; }
    
    // get index as a 0-based integer
    int getIndex() { return (int)index; }
    
    // serialize: get human-readable name of this waveform
    String name();
    
    // deserialize: set index based on given name
    void setFromName(String wfName);
    
    // set index directly as an integer
    void setIndex(int i);
    
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    
public:
    // waveform names: ordered list of string literals
    static const StringArray names;
    
    static const int kChoices = kNumberOfPlayModeTypes;
    
    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi +0.5f)]; }
};

class DelayMode
{
private:
    enum DelayModeTypeIndex {
        kOff, kfree, kSync1, kSync2,kChorus,kFlange,
        kNumberOfTypes
    } index;
    
    static int textToIndex(const String& s);
    
    
    
public:
    // default constructor
    DelayMode() : index(kOff) {}
    
    // set to default state after construction
    void setToDefault() { index = kOff; }
    
    // get index as a 0-based integer
    int getIndex() { return (int)index; }
    
    // serialize: get human-readable name of this waveform
    String name();
    
    // deserialize: set index based on given name
    void setFromName(String wfName);
    
    // set index directly as an integer
    void setIndex(int i);
    
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    
public:
    // waveform names: ordered list of string literals
    static const StringArray names;
    
    static const int kChoices = kNumberOfTypes;
    
    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi +0.5f)]; }
};




class TimeMode
{
private:
    enum TimeModeTypeIndex {
        kOff, kTimer, kVst, kMidi,
        kNumberOfTypes
    } index;
    
    static int textToIndex(const String& s);
    
    
    
public:
    // default constructor
    TimeMode() : index(kOff) {}
    
    // set to default state after construction
    void setToDefault() { index = kOff; }
    
    // get index as a 0-based integer
    int getIndex() { return (int)index; }
    
    // serialize: get human-readable name of this waveform
    String name();
    
    // deserialize: set index based on given name
    void setFromName(String wfName);
    
    // set index directly as an integer
    void setIndex(int i);
    
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    
public:
    // waveform names: ordered list of string literals
    static const StringArray names;
    
    static const int kChoices = kNumberOfTypes;
    
    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi +0.5f)]; }
};


class TimeDivMode
{
private:
    enum TimeDivModeTypeIndex {
        k0125, k0250, k050, k0750,k100,k125,k150,k175,k200,k400,
        kNumberOfTypes
    } index;
    
    static int textToIndex(const String& s);
    
    
    
public:
    // default constructor
    TimeDivMode() : index(k175) {}
    
    // set to default state after construction
    void setToDefault() { index = k175; }
    
    // get index as a 0-based integer
    int getIndex() { return (int)index; }
    
    // serialize: get human-readable name of this waveform
    String name();
    
    // deserialize: set index based on given name
    void setFromName(String wfName);
    
    // set index directly as an integer
    void setIndex(int i);
    
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    
public:
    // waveform names: ordered list of string literals
    static const StringArray names;
    
    static const int kChoices = kNumberOfTypes;
    
    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi +0.5f)]; }
};


class LfoRtrMode
{
private:
    enum LfoRtrModeTypeIndex {
        kOff, k16, k32, k48,k64,k96,k128,
        kNumberOfTypes
    } index;
    
    static int textToIndex(const String& s);
    
    
    
public:
    // default constructor
    LfoRtrMode() : index(kOff) {}
    
    // set to default state after construction
    void setToDefault() { index = kOff; }
    
    // get index as a 0-based integer
    int getIndex() { return (int)index; }
    
    // serialize: get human-readable name of this waveform
    String name();
    
    // deserialize: set index based on given name
    void setFromName(String wfName);
    
    // set index directly as an integer
    void setIndex(int i);
    
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    
public:
    // waveform names: ordered list of string literals
    static const StringArray names;
    
    static const int kChoices = kNumberOfTypes;
    
    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi +0.5f)]; }
};


class SampelSetMode
{
private:
    enum SampelSetModeTypeIndex {kOff,
        kset1, kset2, 
        kNumberOfTypes
    } index;
    
    static int textToIndex(const String& s);
    
    
    
public:
    // default constructor
    SampelSetMode() : index(kOff) {}
    
    // set to default state after construction
    void setToDefault() { index = kOff; }
    
    // get index as a 0-based integer
    int getIndex() { return (int)index; }
    
    // serialize: get human-readable name of this waveform
    String name();
    
    // deserialize: set index based on given name
    void setFromName(String wfName);
    
    // set index directly as an integer
    void setIndex(int i);
    
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    
public:
    // waveform names: ordered list of string literals
    static const StringArray names;
    
    static const int kChoices = kNumberOfTypes;
    
    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi +0.5f)]; }
};



class SampelHoldMode
{
private:
    enum SampelHoldModeTypeIndex {kOff,
        kset16, kset32, kset64, kset96,kset128,
        kNumberOfTypes
    } index;
    
    static int textToIndex(const String& s);
    
    
    
public:
    // default constructor
    SampelHoldMode() : index(kOff) {}
    
    // set to default state after construction
    void setToDefault() { index = kOff; }
    
    // get index as a 0-based integer
    int getIndex() { return (int)index; }
    
    // serialize: get human-readable name of this waveform
    String name();
    
    // deserialize: set index based on given name
    void setFromName(String wfName);
    
    // set index directly as an integer
    void setIndex(int i);
    
    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);
    
public:
    // waveform names: ordered list of string literals
    static const StringArray names;
    
    static const int kChoices = kNumberOfTypes;
    
    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi +0.5f)]; }
};


class MidiCCMode
{
private:
    enum MidiCCModeTypeIndex {
        kOff,
        kVst, kLiv,k1,
        kNumberOfTypes
    } index;

    static int textToIndex(const String& s);



public:
    // default constructor
    MidiCCMode() : index(kOff) {}

    // set to default state after construction
    void setToDefault() { index = kOff; }

    // get index as a 0-based integer
    int getIndex() { return (int)index; }

    // serialize: get human-readable name of this waveform
    String name();

    // deserialize: set index based on given name
    void setFromName(String wfName);

    // set index directly as an integer
    void setIndex(int i);

    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);

public:
    // waveform names: ordered list of string literals
    static const StringArray names;

    static const int kChoices = kNumberOfTypes;

    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi + 0.5f)]; }
};


class LimiterMode
{
private:
    enum LimiterModeTypeIndex {
        kOff, kLp, kBp2, kHp,
        kNumberOfLimiterModeTypes
    } index;

    static int textToIndex(const String& s);


public:
    // default constructor
    LimiterMode() : index(kOff) {}

    // set to default state after construction
    void setToDefault() { index = kOff; }

    // get index as a 0-based integer
    int getIndex() { return (int)index; }

    // serialize: get human-readable name of this waveform
    String name();

    // deserialize: set index based on given name
    void setFromName(String wfName);

    // set index directly as an integer
    void setIndex(int i);

    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);

public:
    // waveform names: ordered list of string literals
    static const StringArray names;

    static const int kChoices = kNumberOfLimiterModeTypes;

    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi + 0.5f)]; }
};

class OverDriveMode
{
private:
    enum OverDriveModeTypeIndex {
        kOff, kLp, kBp2, kHp,
        kNumberOfOvModeTypes
    } index;

    static int textToIndex(const String& s);


public:
    // default constructor
    OverDriveMode() : index(kOff) {}

    // set to default state after construction
    void setToDefault() { index = kOff; }

    // get index as a 0-based integer
    int getIndex() { return (int)index; }

    // serialize: get human-readable name of this waveform
    String name();

    // deserialize: set index based on given name
    void setFromName(String wfName);

    // set index directly as an integer
    void setIndex(int i);

    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);

public:
    // waveform names: ordered list of string literals
    static const StringArray names;

    static const int kChoices = kNumberOfOvModeTypes;

    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi + 0.5f)]; }
};

class ADSRMode
{
private:
    enum ADSRModeTypeIndex {
        kOff, kLinear,  kAnalogLike, kLinearInDb,
        kNumberOfModeTypes
    } index;

    static int textToIndex(const String& s);


public:
    // default constructor
    ADSRMode() : index(kOff) {}

    // set to default state after construction
    void setToDefault() { index = kOff; }

    // get index as a 0-based integer
    int getIndex() { return (int)index; }

    // serialize: get human-readable name of this waveform
    String name();

    // deserialize: set index based on given name
    void setFromName(String wfName);

    // set index directly as an integer
    void setIndex(int i);

    // convenience funtions to allow selecting SynthWaveform from a juce::comboBox
    static void setupComboBox(ComboBox& cb);

public:
    // waveform names: ordered list of string literals
    static const StringArray names;

    static const int kChoices = kNumberOfModeTypes;

    static float textToFloat(const String& s) { return (float)textToIndex(s); }
    static String floatToText(float fi) { return names[(int)(fi + 0.5f)]; }
};































