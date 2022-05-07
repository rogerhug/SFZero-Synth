/*
  ==============================================================================

    repeaterGui.cpp
    Created: 27 Apr 2022 8:21:24am
    Author:  r7

  ==============================================================================
*/

#include <JuceHeader.h>
#include "repeaterGui.h"
repeaterGuiMod::repeaterGuiMod(AudioProcessorValueTreeState& vts)
{
}

repeaterGuiMod::~repeaterGuiMod()
{
}

void repeaterGuiMod::paint(juce::Graphics& g)
{
    g.drawText("modulatorSteps +", 0, 0, getWidth(), 20, juce::Justification::centred, true);
    g.drawText("modulatorSteps -", 0, 40, getWidth(), 20, juce::Justification::centred, true);




    for (int i = 0; i < 9; i++) {
        g.drawRect(i * 22, 20, 22, 15);
        g.drawRect(i * 22, 60, 22, 15);

    }
    g.drawText("0", 0, 20, 22, 15, juce::Justification::centred, true);
    g.drawText("8", 22, 20, 22, 15, juce::Justification::centred, true);
    g.drawText("16", 44, 20, 22, 15, juce::Justification::centred, true);
    g.drawText("32", 66, 20, 22, 15, juce::Justification::centred, true);
    g.drawText("3", 88, 20, 22, 15, juce::Justification::centred, true);
    g.drawText("6", 110, 20, 22, 15, juce::Justification::centred, true);
    g.drawText("12", 132, 20, 22, 15, juce::Justification::centred, true);
    g.drawText("24", 154, 20, 22, 15, juce::Justification::centred, true);
    g.drawText("48", 175, 20, 22, 15, juce::Justification::centred, true);


    g.drawText("0", 0, 60, 22, 15, juce::Justification::centred, true);
    g.drawText("8", 22, 60, 22, 15, juce::Justification::centred, true);
    g.drawText("16", 44, 60, 22, 15, juce::Justification::centred, true);
    g.drawText("32", 66, 60, 22, 15, juce::Justification::centred, true);
    g.drawText("3", 88, 60, 22, 15, juce::Justification::centred, true);
    g.drawText("6", 110, 60, 22, 15, juce::Justification::centred, true);
    g.drawText("12", 132, 60, 22, 15, juce::Justification::centred, true);
    g.drawText("24", 154, 60, 22, 15, juce::Justification::centred, true);
    g.drawText("48", 175, 60, 22, 15, juce::Justification::centred, true);
}
void repeaterGuiMod::mouseUp(const juce::MouseEvent& event)
{
}
void repeaterGuiMod::mouseDown(const juce::MouseEvent& event)
{
}
void repeaterGuiMod::mouseDrag(const MouseEvent& e)
{
    const int hightY = e.getPosition().getY();
    const int widthX = e.getPosition().getX();

    posY = hightY;

    if (hightY > 20 && hightY < 40)
    {
        mPstage = 1;
        posXm1 = widthX / 25;
      

    }


    if (hightY > 40 && hightY < 60)
    {
        mPstage = 2;
        posXm2 = widthX / 25;
      
    }

    if (hightY > 60 && hightY < 80)
    {
        mPstage = 3;
        posXm3 = widthX / 25;

    }
  
}

//==============================================================================
repeaterGui::repeaterGui(AudioProcessorValueTreeState& vts)

{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    posY = 0;
    posXt1 = 0;
    posXt2 = 0;
    posXm1 = 0;
    posXm2 = 0;
    mDown = false;
    mPstage = 0;
}

repeaterGui::~repeaterGui()
{
}

void repeaterGui::paint (juce::Graphics& g)
{
   

    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    
      if (mDown == true && posY>20 && posY <40) {
        g.setColour(juce::Colours::green);
        g.fillRect(10 + posXt1 * 44, 20, 44, 20);
    }
    if (mDown == false && posY > 20 && posY < 40) {
        g.setColour(juce::Colours::grey);
       g.fillRect( 10+posXt1*44, 20, 44,20);
    }

    if (mDown == true && posY > 40 && posY < 60) {
        g.setColour(juce::Colours::green);
        g.fillRect(10 + posXt2 * 44, 40, 44, 20);
    }
    if (mDown == false && posY > 40 && posY < 60) {
        g.setColour(juce::Colours::grey);
        g.fillRect(10 + posXt2 * 44, 40, 44, 20);
    }


    if (mDown == true && posY > 60 && posY < 80) {
        g.setColour(juce::Colours::green);
        g.fillRect(10 + posXt3 * 44, 60, 44, 20);
    }
    if (mDown == false && posY > 60 && posY < 80) {
        g.setColour(juce::Colours::grey);
        g.fillRect(10 + posXt3 * 44, 60, 44, 20);
    }

    g.setColour (juce::Colours::white);
    g.setFont (14.0f);
    


    g.setColour(juce::Colours::red);
   // g.fillRect(posXm1 * 22, 82, 22, 15);
  //  g.fillRect(posXm2 * 22, 120, 22, 15);
    //g.fillRect(posXm3 * 22, 141, 22, 15);


    g.setColour(juce::Colours::white);
    
    g.drawText("repeater/looper", 0, 0, getWidth(), 20,juce::Justification::centred, true);
    for (int i = 0; i < 4; i++) {
        g.drawRect(10+i * 44, 20, 44, 20);
        g.drawRect(10+i * 44, 42, 44, 20);
        g.drawRect(10 + i * 44, 64, 44, 20);
    }


    g.drawText("1/1", 10, 20, 44, 20, juce::Justification::centred, true);
    g.drawText("1/2", 54, 20, 44, 20, juce::Justification::centred, true);
    g.drawText("1/3", 98, 20, 44, 20, juce::Justification::centred, true);
    g.drawText("1/4", 142, 20, 44, 20, juce::Justification::centred, true);


    g.drawText("1/6", 10, 40, 44, 20, juce::Justification::centred, true);
    g.drawText("1/8", 54, 40, 44, 20, juce::Justification::centred, true);
    g.drawText("1/9", 98, 40, 44, 20, juce::Justification::centred, true);
    g.drawText("1/12", 142, 40, 44, 20, juce::Justification::centred, true);

    g.drawText("1/16", 10, 62, 44, 20, juce::Justification::centred, true);
    g.drawText("1/24", 54, 62, 44, 20, juce::Justification::centred, true);
    g.drawText("1/32", 98, 62, 44, 20, juce::Justification::centred, true);
    g.drawText("1/48", 142, 62, 44, 20, juce::Justification::centred, true);

   
    
}

void repeaterGui::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
bool loops1[15];
bool loops2[15];
bool loops3[15];
void repeaterGui::mouseUp(const juce::MouseEvent& event)
{
    
    mDown = false;

    mPstage = 0;
    repaint();
}

void repeaterGui::mouseDown(const juce::MouseEvent& event)
{
    mDown = true;
    mouseDrag(event);

}

void repeaterGui::mouseDrag(const MouseEvent& e)
{
    for (int i = 0; i < 10; i++) {
        loops1[i] = false;
        loops2[i] = false;
        loops3[i] = false;
        mPstage = 0;

        const int hightY = e.getPosition().getY();
        const int widthX = e.getPosition().getX();

        posY = hightY;

        if (hightY > 20 && hightY < 40 )
        {  
            mPstage = 1;
            posXt1 = widthX / 50;
           loops1[posXt1] = true;
           
        }
             else
            loops1[i] = false;
            
        if ( hightY > 40 && hightY < 60)
        {
            mPstage = 2;
            posXt2 = widthX / 50;
            loops2[posXt2] = true;
        }
        else
           loops2[i] = false;

        if (hightY > 60 && hightY < 80)
        {
            mPstage = 3;
            posXt3 = widthX / 50;
            loops3[posXt3] = true;
        }
        else
            loops3[i] = false;
      

       
    }

    repaint();
}

const bool *repeaterGui::loopOn1()
{

    return loops1;
}
const bool* repeaterGui::loopOn2()
{

    return loops2;
}
const bool* repeaterGui::loopOn3()
{
    return loops3;
}