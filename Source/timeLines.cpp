/*
  ==============================================================================

    timeLines.cpp
    Created: 16 Feb 2022 2:26:57pm
    Author:  r7

  ==============================================================================
*/

#include <JuceHeader.h>
#include "timeLines.h"

//==============================================================================
timeLines::timeLines()

{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    seqlenght = 16;
    mainlfoselect = 0;
    Blocksize = 512;
    currentPositionPpq=0;
    tm1.Start();
    IcurrentPosition = 0;
    tr1off = 0;
    setTime = 0;
    bPm = 60;
}

timeLines::~timeLines()
{
}

void timeLines::setTimes(int t)
{
    setTime = t;
    for(int i=0;i<10;++i)
    division(i);
}

int timeOuts1[16] = { 0,0,0,0,0,0,0 };
int timeOuts2[16] = { 0,0,0,0,0,0,0 };


double fixdivision[10] = { 7,7,7,7,7,7,7 };
int Timelines[10] = { 0,0,0,0,0,0,0,0 };
int TimeCounts[10] = { 0,0,0,0,0,0,0,0 };
int offsetPerSteps[10] = { 8,8,8,8,8,8,8,8 };

void timeLines::prepare(int sr, int size)
{
    Blocksize = size;
    Sampelrate = sr;
    SampelsInMinute = (sr * 60);
    ppqPositions.resize(size);
    IcurrentPosition = 0;
  
}

const double timeLines::getPpqPerSample()
{
    auto SampelsPerBeat = SampelsInMinute / info.bpm;
    return 1 / SampelsPerBeat;
}

void timeLines::processTimeHost(AudioPlayHead* playhead, int nFrames,int selectSp)
{
    const int size =seqlenght;
    const int sizeSHmain = mainlfoSh;
    if (playhead != nullptr)
        playhead->getCurrentPosition(info);
    auto ppqPerSample = getPpqPerSample();
    double offset = 0.0;

    if (info.isPlaying > 0) {
       
        if (setTime == 1)
        {
            tm1.End();
           
            for (int sample = 0; sample < nFrames; ++sample)
            {
            
                    ppqPositions[sample] = info.ppqPosition+offset;
                    offset += ppqPerSample;
                    const double pos = ppqPositions[sample];

                    currentPositionPpq = pos;
                   
                   
                 
                   
                }
             
        

            data1[0] = 0;
            data1[1] = 0;
            data1[2] = 0;

          
          
         
       /*
            timeOuts1[0] = (fmod(currentPositionPpq * fixdivision[0], size));
           timeOuts1[2] = fmod(currentPositionPpq * fixdivision[0], 1.0) * 960.0 + 0.5;

            timeOuts2[0] = (fmod(currentPositionPpq * fixdivision[1], size));
            timeOuts2[2] = fmod(currentPositionPpq * fixdivision[1], 1.0) * 960.0+0.5;
*/
           

         
        }
      
    }
}
int scount1 = 0;
double rateS[10] = { 0,0,0,0,0,0,0 };
void timeLines::prosessTimeSampels(int sampel_t, int nFrames,int bpm,int div)
{
    const int sizeSHmain = mainlfoSh;
    double offset = 0.0;
    const int kBeatDiv = 4;
    const int kBeatDiv32 = 8;
 
    const int size = 16;
    Sampelrate = 44100;
    double divide = 0;
    if (div == 0) { divide = 12; }// Vst3 sampelTime dividers
    if (div == 1) { divide = 8; }
    if (div == 2) { divide = 6; }
    if (div == 3) { divide = 4; }
    if (div == 4) { divide = 2.5; }
    if (div == 5) { divide = 2; }
    if (div == 6) { divide = 1.5; }
    if (div == 7) { divide = 1; }
    if (div == 8) { divide = 0.5; }
    if (div == 9) { divide = 0.25; }

    int samplesPerBeat0 = (Sampelrate) * 60.0 / bpm  * divide/4;
    int samplesPerBeat1 = (Sampelrate) * 60.0 / bpm * divide/4;

    int samplePos = sampel_t;
  
  

      
            for (int s = 0; s < nFrames; s++)
            {

        
               

                int mod0 = (samplePos + s) % (samplesPerBeat0 * kBeatDiv) ;
                IcurrentPositionS1 = mod0 / (samplesPerBeat0/ kBeatDiv) ;
                rateS[0] = (double)mod0 / (samplesPerBeat0 / kBeatDiv);
               
                int mod1 = (samplePos + s) % (samplesPerBeat1 * kBeatDiv);
                IcurrentPositionS2 = mod1 / (samplesPerBeat1 / kBeatDiv);
                rateS[1] = (double)mod1 / (samplesPerBeat1 / kBeatDiv);


              
            
  

    timeOuts2[0] = (IcurrentPositionS2 % size);
    timeOuts2[2] = divide;//fmod((rateS[1]), 1.0) * 960.0 + 0.5;

    }
    

}


void timeLines::division(int n)
{
    n = 0;
    if (setTime == 3) {

        if (dividers[n] == 0) { fixdivision[n] = 0.125; }// Vst3 ppq dividers
        if (dividers[n] == 1) { fixdivision[n] = 0.25; }
        if (dividers[n] == 2) { fixdivision[n] = 0.5; }
        if (dividers[n] == 3) { fixdivision[n] = 1.0000; }
        if (dividers[n] == 4) { fixdivision[n] = 1.5; }
        if (dividers[n] == 5) { fixdivision[n] = 2.0000; }
        if (dividers[n] == 6) { fixdivision[n] = 3; }
        if (dividers[n] == 7) { fixdivision[n] = 4.0000; }
        if (dividers[n] == 8) { fixdivision[n] = 8; }
        if (dividers[n] == 9) { fixdivision[n] = 16; }
    }
    if (setTime == 1) {
        if (dividers[n] == 0) { fixdivision[n] = 0.33333/8; } // chrono dividers
        if (dividers[n] == 1) { fixdivision[n] = 0.33333/4; }
        if (dividers[n] == 2) { fixdivision[n] = 0.125; }
        if (dividers[n] == 3) { fixdivision[n] = 0.33333/2; }
        if (dividers[n] == 4) { fixdivision[n] = 0.25; }
        if (dividers[n] == 5) { fixdivision[n] = 0.33333; }
        if (dividers[n] == 6) { fixdivision[n] = 0.5; }
        if (dividers[n] == 7) { fixdivision[n] = 0.6666666; }
        if (dividers[n] == 8) { fixdivision[n] = 0.6666666*2; }
        if (dividers[n] == 9) { fixdivision[n] = 0.66666*4; }

    }
    if (setTime == 2) {

        if (dividers[n] == 9) { fixdivision[n] = 12; }// Vst3 sampelTime dividers
        if (dividers[n] == 8) { fixdivision[n] = 8; }
        if (dividers[n] == 7) { fixdivision[n] = 6; }
        if (dividers[n] == 6) { fixdivision[n] = 4; }
        if (dividers[n] == 5) { fixdivision[n] = 2.5; }
        if (dividers[n] == 4) { fixdivision[n] = 2; }
        if (dividers[n] == 3) { fixdivision[n] = 1.5; }
        if (dividers[n] == 2) { fixdivision[n] = 1; }
        if (dividers[n] == 1) { fixdivision[n] = 0.5; }
        if (dividers[n] == 0) { fixdivision[n] = 0.25; }
    }
   
}

double timeLines::timerChrono(int selectSp)
{ 
 // in reaper i have the plug recording activatet eg(for just monitoring) ..else not comes this info right
    // if (info.isPlaying > 0) {   //vst               
    //if(setTime == 2){              //app
 
    const int size = 16;
    const int sizeSHmain = mainlfoSh;
   
     if (setTime == 1) {
        
         tm1.Start();  
         tm1.CalcDuration();
        data1[0]=tm1.TestLatency512().count(); //----------readers to gui(Plugineditor/timercallback())
       data1[1] = tm1.GetDuration().count(); 
     

         //--Time ++--------------------------------
        // Blocksize = 441;
         for(int sp=0;sp<7;++sp){
        Timelines[0]= (tm1.GetDuration().count() - 1);  }  
         const double offsetC = tm1.TestLatency512().count() / 512 * Blocksize;

         //--pseudo offset calc 9 to> || 8 to< ---eg takt 1/16 

        
         if (fixdivision[selectSp] == 7) { offsetPerSteps[selectSp] = 4; }//------------mode 1/16
         if (fixdivision[selectSp] == 5) { offsetPerSteps[selectSp] = 6; }//------------mode 1/8
         if (fixdivision[selectSp] == 3) { offsetPerSteps[selectSp] = 8; }//------------mode 1/4    

         //-------  offset+ for 1-7 engine times----------------------------

         const int timeCounts1 = timeOuts1[0] % offsetPerSteps[0];

         if (timeOuts1[0] % offsetPerSteps[0] == timeCounts1) {
        //     Timelines[0] += offsetC * fixdivision[0];
         }

        

         //-----------time mode-------------------

       
         const double t1 = ((tm1.GetDuration().count() - 1)*0.1) / 100 * bPm * fixdivision[0];//-----------vst
         const double t2 = (Timelines[1] * 0.01) / 100 * 120 * fixdivision[1];


             
         
            timeOuts1[0] = (int)fmod(t1, size);
             timeOuts1[2] = fmod(t1, 1.0) * 960 + 0.5;
            

            
         }
        return  0;

       // }
  //  if(setTime <2){ tm1.End(); }
 //if (info.isPlaying == 0) { tm1.End();; }// app

// if (info.ppqLoopEnd - info.ppqPosition == 0) { tm1.Zero(); }
    
}




const int *timeLines::getHtime1()
{
    return timeOuts1;
}

const int* timeLines::getHtime2()
{
    return timeOuts2;
}






