/*
  ==============================================================================

    modulator.h
    Created: 23 Apr 2022 10:20:30am
    Author:  r7

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <functional>
//==============================================================================
/*
*/

class modulator  : public juce::Component
                   ,private Timer
                 
{
public:    
   
   
    modulator(AudioProcessorValueTreeState& vts);
    ~modulator() override;
    void paint(juce::Graphics& g)override;
    void mouseUp(const juce::MouseEvent& event) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const MouseEvent& e)override;

    void resized() override;
    void timerCallback()override;
 
    void drawForm(juce::Graphics& g);
    void drawModOut(juce::Graphics& g);

    void drawButts(juce::Graphics& g);

    void setTime(int t, int f);
    void initCurve(int i);


     int x = 123;
    int slider_nb;
    int sliderMod_nb;
    int* steppValues;
    int* ModOutValues;
    int butNb;
    int butNbWv;
    int but_tm;
    bool mDown;
   
   
   
    char ecv[15] = { "" };
    Value SteppValues;
    const char* StepValuesNames() { sprintf(ecv, "steppervalue");  return ecv; }
    const double *stepValuesOut();
    const double* stepModValues();
    const double getTimerBpmvalue() { return double(mBpm) * 3; }
    const int getTimerHostValue() { return but_tm; }
    void serialStepps(AudioProcessorValueTreeState& valueTreeState);
    void unSerialStepps(AudioProcessorValueTreeState& valueTreeState);

    const int getMode() { return cMenu; }
    const int getHostTime() { return timeHost; }
private: 

    int gethight;
    int getwidth;
    int mCount;
    int cMenu;
    int timeHost;
    int mBpm;
    double phaseOut;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (modulator)
};
