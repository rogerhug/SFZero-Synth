/*
  ==============================================================================

    repeaterGui.h
    Created: 27 Apr 2022 8:21:24am
    Author:  r7

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/*
*/
class repeaterGuiMod : public juce::Component
{
public:
    repeaterGuiMod(AudioProcessorValueTreeState& vts);
    ~repeaterGuiMod() override;
    void paint(juce::Graphics&) override;

    void mouseUp(const juce::MouseEvent& event) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const MouseEvent& e)override;
private:

    int posXm1;
    int posXm2;
    int posXm3;
    bool mDown;
    int posY;
    int mPstage;

};
class repeaterGui  : public juce::Component
{
public:
    repeaterGui(AudioProcessorValueTreeState& vts);
    ~repeaterGui() override;

    void paint (juce::Graphics&) override;
    void resized() override;
    void mouseUp(const juce::MouseEvent& event) override;
    void mouseDown(const juce::MouseEvent& event) override;
    void mouseDrag(const MouseEvent& e)override;
    const bool *loopOn1();
    const bool* loopOn2();
    const bool* loopOn3();
    const bool changeValue() { return mDown; }
    const int Vmode() { return mPstage; }

private:
    int posXt1;
    int posXt2;
    int posXt3;
    int posXm1;
    int posXm2;
    int posXm3;
    bool mDown;
    int posY;
    int mPstage;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (repeaterGui)
};
