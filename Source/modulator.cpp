/*
  ==============================================================================

    modulator.cpp
    Created: 23 Apr 2022 10:20:30am
    Author:  r7

  ==============================================================================
*/

#include <JuceHeader.h>
#include "modulator.h"

//==============================================================================
modulator::modulator(AudioProcessorValueTreeState& vts)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    steppValues = new int[16];
    ModOutValues = new int[16];
    butNb = 0;
    butNbWv = 0;
     gethight=100;
     getwidth=180;
    slider_nb = 0;
    sliderMod_nb = 0;
    for (int i = 0; i < 16; i++) {
        steppValues[i] = sin(i / (double)16 * double_Pi ) * 85;
        ModOutValues[i] = 180;
    }
    repaint();
   
    mDown = false;
    mCount = 0;
    cMenu = 0;
    mBpm = 20;
    but_tm = 0;
    startTimer(1);
    startTimerHz(30);
    phaseOut = 0;
}

modulator::~modulator()
{
}
int xf = 0;
int yf = 0;
bool tf = false;
inline int minmax100(int a) {
    int result = 0; result = a;
    if (result > 100) { result = 100; }
    if (result < 0) { result = 0; }
    return result;
}
inline double minmax1(double a) {
    double result = 0; result = a;
    if (result > 1) { result = 1; }
    if (result < 0) { result = 0; }
    return result;
}
void modulator::mouseDown(const juce::MouseEvent& event)
{
   
    mDown = true;
    mouseDrag(event);
    
}
int butvalue[8] = { 0 };
int butvalueWv[8] = { 0 };
void modulator::mouseDrag(const MouseEvent& event)
{ 

     const int hightY = event.getPosition().getY();
     const int widthX = event.getPosition().getX();

    int xposT = widthX;
        
        if (xposT < 90  && hightY < 15) {
            cMenu = 4;
       
            mBpm = minmax100(widthX);
        }

        int xposT_m = widthX;
        if (widthX < 130) { xposT_m = 130; }
        if (widthX > 280) { xposT_m = 280; }


        if (xposT_m > 130 && hightY < 15) {
            cMenu = 5;
            but_tm = (xposT_m - 110) / 47.5;
            timeHost = but_tm;
          
        }



     int xpos = widthX;
     if (widthX < 0) { xpos = 0; }
     if (widthX > 100) { xpos = 100; }
  
        const int slidposx= (xpos)/ 6 - 0.5;
        if (xpos < 100 && hightY > 20 && hightY < 140) {
            cMenu = 0;
            slider_nb = slidposx;
            steppValues[slidposx] = minmax100(hightY-25);
        }

        const int but_n     = minmax100(hightY-25)/16;
        const int but_nWv   = minmax100((hightY-25)/16);
        const int slideposy = minmax100(hightY-25)/16;

        int xposB = widthX;
        int xposBWv = widthX;
        int xposMWv = widthX;
       
        if (widthX < 100) { xposB = 100; }
        if (widthX > 120) { xposB = 120; }
        if (xposB > 105 && xposB < 120 && hightY > 20 && hightY< 140) {
            for (int i = 0; i < 7; i++)
               
                butvalue[i] = 0;
                butNb = but_n;
                butvalue[but_n] = 1; 
                cMenu = 1;
        }
        if (widthX < 130) { xposBWv = 130; }
        if (widthX > 170) { xposBWv = 170; }
        if (xposBWv > 130 && xposBWv < 170 && hightY > 20 && hightY < 140) {
            for (int i = 0; i < 7; i++)

            butvalueWv[i] = 0;
           cMenu = 2;
            butNbWv = but_nWv;
            butvalueWv[but_nWv] = 1;
            initCurve(but_nWv);
          

        }

        if (widthX < 180) { xposMWv = 180; }
        if (widthX > 280) { xposMWv = 280; }
        if (xposMWv > 180 && xposMWv < 280 && hightY > 20 && hightY < 140) {
           
            sliderMod_nb = slideposy;
            ModOutValues[slideposy] = xposMWv;
            cMenu = 3;
        
        }
        
       
        repaint();
       
}
char lbt[20]{ 0 };
void modulator::paint(juce::Graphics& g)

{
 
    g.setColour(juce::Colours::white);

    sprintf(lbt, "p1 %i::p2 %i ", cMenu, mCount);

    g.drawRect(0, 0, getWidth(), getHeight(), 1);
   
    g.setColour(juce::Colours::lightgreen);
    g.fillRect(1, 1, getWidth()-1, getHeight()-1);
    g.setFont(14.0f);
    g.setColour(juce::Colours::white);
  //  g.drawText(lbt, 100,120,200,20, juce::Justification::centred, true);
    drawForm(g);
    drawButts(g);
    drawModOut(g);
   
}

void modulator::mouseUp(const juce::MouseEvent& event)
{
    mDown = false;
}



void modulator::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void modulator::timerCallback()
{
   
   
}

void modulator::drawForm(juce::Graphics& g)
{

       const int heightM = 50;
       const int row = 30;
    
       g.setColour(juce::Colours::white);

       for (int i = 0; i < 16; i++) {

           if (steppValues[i] < 50) {
               g.fillRect(12+i*5, row + steppValues[i], 4,  minmax100(heightM - (steppValues[i])));
           }
           else {
               g.fillRect(12 + i * 5, row + heightM, 4, minmax100(steppValues[i]-heightM  ));
           }


       }



    
}

void modulator::drawModOut(juce::Graphics& g)
{
    const int row = 20; 
    for (int i = 0; i < 7; i++) {
     g.setColour(juce::Colours::red);
        g.fillRect(181,row+ 5+i*15, 99, 15);
     g.setColour(juce::Colours::white);
  
       g.drawRect(180, row + 5 + i * 15, 100, 14);
    
   
 g.fillRect(ModOutValues[i], row + 5 + i*15,  280 - ModOutValues[i], 13);

    
}
   

    g.setColour(juce::Colours::black);
    g.drawText("cut", 180, row + 5, 60, 14, juce::Justification::centred, true);
    g.drawText("pitch", 180, row + 20, 60, 14, juce::Justification::centred, true);
    g.drawText("vol", 180, row + 35, 60, 14, juce::Justification::centred, true);
    g.drawText("delayT", 180, row + 50, 60, 14, juce::Justification::centred, true);
    g.drawText("delayF", 180, row + 65, 60, 14, juce::Justification::centred, true);
    g.drawText("Ring", 180, row + 80, 60, 14, juce::Justification::centred, true);
    g.drawText("Shape", 180,row + 95,  60, 14, juce::Justification::centred, true);

   //------------------tempo/Bpm----------------------
    g.setColour(juce::Colours::red);
    g.fillRect(5, 0, 95, 20);
    g.setColour(juce::Colours::white);
    g.drawRect(5, 0, 95, 20);
    g.fillRect(5+mBpm,0, 95 - mBpm, 19);
    g.setColour(juce::Colours::black);
    char bp[10] = { "" };
    sprintf(bp,"TimerBpm %i", mBpm*3);
    g.drawText(bp,5, 0, 95, 20,  juce::Justification::centred, true);
}

void modulator::drawButts(juce::Graphics& g)
{
    const int row = 20;
    g.setColour(juce::Colours::white);
    for (int i = 0; i < 7; i++) 
     g.drawRect(102,row+5+ i * 15, 30, 14);
     g.fillRect(102, row + 5+butNb*15, 30, 14);

    g.setColour(juce::Colours::black);
    g.drawText("1/1", 102, row + 5, 30, 14, juce::Justification::centred, true);
    g.drawText("1/2", 102, row + 20, 30, 14, juce::Justification::centred, true);
    g.drawText("1/4", 102, row + 35, 30, 14, juce::Justification::centred, true);
    g.drawText("1/8", 102, row + 50, 30, 14, juce::Justification::centred, true);
    g.drawText("1/16", 102, row + 65, 30, 14, juce::Justification::centred, true);
    g.drawText("1/32", 102, row + 80, 30, 14, juce::Justification::centred, true);
    g.drawText("1/64", 102, row + 95, 30, 14, juce::Justification::centred, true);
    g.setColour(juce::Colours::white);
    for (int i = 0; i < 7; i++)

        g.drawRect(135, row + 5 + i * 15, 40, 14);
    g.fillRect(135, row + 5 + butNbWv * 15, 40, 14);

    g.setColour(juce::Colours::black);
    g.drawText("zero", 135, row + 5, 40, 14, juce::Justification::centred, true);
    g.drawText("sine", 135, row + 20, 40, 14, juce::Justification::centred, true);
    g.drawText("sawup", 135, row + 35, 40, 14, juce::Justification::centred, true);
    g.drawText("sawdn", 135, row + 50, 40, 14, juce::Justification::centred, true);
    g.drawText("sqrt", 135, row + 65, 40, 14, juce::Justification::centred, true);
    g.drawText("rndm", 135,row + 80,  40, 14, juce::Justification::centred, true);
    g.drawText("rndm", 135,row + 95,  40, 14, juce::Justification::centred, true);


    //----------------Time mode butts----------------------------

    for (int i = 0; i < 4; i++)
        g.drawRect(110+ i * 45, 0 , 45, 19);
    g.setColour(juce::Colours::white);
    g.fillRect(110+ but_tm * 45, 0 , 45, 19);
    g.setColour(juce::Colours::black);
    g.drawText("Off", 110, 0, 45, 19, juce::Justification::centred, true);
    g.drawText("Int", 155, 0, 45, 19, juce::Justification::centred, true);
    g.drawText("VST", 200, 0, 45, 19, juce::Justification::centred, true);
    g.drawText("Midi", 245, 0, 45, 19, juce::Justification::centred, true);
}

void modulator::setTime(int t, int f)
{

    mCount = t;



}
double values[16];
void modulator::initCurve(int i)
{
    for (int c = 0; c < 16; c++) {
        switch (i) {
        case 0:
            steppValues[c] = 51;
            break;
        case 1:
            steppValues[c] = sin(c / (double)16 * double_Pi) * 85;
            break;
        case 2:
            steppValues[c] = (c / (double)16 ) * 95;
            break;
        case 3:
            steppValues[c] = 95- (c / (double)16 ) * 95;
            break;
        case 4:
            steppValues[c / 2] = 0;
            steppValues[8+c / 2] = 100;
            break;
        case 5:
            steppValues[c / 4] = 0;
            steppValues[4 + c / 4] = 30;
            steppValues[8 + c / 4] = 70;
            steppValues[12 + c / 4] = 90;
            break;
        case 6:
            steppValues[c / 4] = 90;
            steppValues[4 + c / 4] = 70;
            steppValues[8 + c / 4] = 30;
            steppValues[12 + c / 4] = 10;
         
            break;
           default:
            break;

        }
     values[c] = minmax1(double(steppValues[c]) / 100.0f);
    }
    
     
    repaint();
}

const double *modulator::stepValuesOut()
{
     values[slider_nb] = minmax1(double(steppValues[slider_nb]) / 100);
     return  values;// minmax1(double(steppValues[slider_nb]) / 100);
}
double valuesMod[16];
const double* modulator::stepModValues()
{
    valuesMod[sliderMod_nb] = (double(ModOutValues[sliderMod_nb])-180) / 100;
    return valuesMod;
}
char serialStepValues[200] = { 0 };
double stepsValueIn[50];

void modulator::serialStepps(AudioProcessorValueTreeState& valueTreeState)
{
    
        sprintf(serialStepValues,
            //......................................steps.................................//..buts...//......aux....................
            "%.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f %.2f "                                              
            , stepValuesOut()[0], stepValuesOut()[1], stepValuesOut()[2], stepValuesOut()[3]             
            , stepValuesOut()[4], stepValuesOut()[5], stepValuesOut()[6], stepValuesOut()[7]
            , stepValuesOut()[8], stepValuesOut()[9], stepValuesOut()[10], stepValuesOut()[11]
            , stepValuesOut()[12], stepValuesOut()[13], stepValuesOut()[14], stepValuesOut()[15]           
            , double(butNb), double(butNbWv)                                                 
            , stepModValues()[0], stepModValues()[1], stepModValues()[2], stepModValues()[3] 
            , stepModValues()[4], stepModValues()[5],0);

        valueTreeState.state.setProperty(StepValuesNames(), var(serialStepValues), nullptr);


    

}

void modulator::unSerialStepps(AudioProcessorValueTreeState& valueTreeState)
{
   
        SteppValues.referTo(valueTreeState.state.getPropertyAsValue(StepValuesNames(), nullptr, true));


        for (int y = 0; y <= 200; y += 5) {



            stepsValueIn[y / 5] = SteppValues.getValue().toString().substring(y, y + 4).getDoubleValue();


        


    }
    for (int s = 0; s < 16; s++) {
        steppValues[s] = stepsValueIn[s] * 100;
    }
    butNb = (int)stepsValueIn[16];
    butNbWv = (int)stepsValueIn[17];

    ModOutValues[0] = 180 + (stepsValueIn[18]*100);
    ModOutValues[1] = 180 + (stepsValueIn[19]*100);
    ModOutValues[2] = 180 + (stepsValueIn[20]*100);
    ModOutValues[3] = 180 + (stepsValueIn[21]*100);
    ModOutValues[4] = 180 + (stepsValueIn[22]*100);
    ModOutValues[5] = 180 + (stepsValueIn[23]*100); 
    repaint();
}
