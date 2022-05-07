/*
  ==============================================================================

    timeLines.h
    Created: 16 Feb 2022 2:26:57pm
    Author:  r7

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <chrono>
template< typename precision = long double, typename ratio = std::milli >
class TimerX final
{
public:
    //---------------- aliases ----------------
    using timeDuration_t = std::chrono::duration<precision, ratio>;
    using timePoint_t = std::chrono::time_point<std::chrono::system_clock, timeDuration_t>;
    using this_type = TimerX< precision, ratio >;

    inline void Start()  { m_start = std::chrono::system_clock::now(); }
    inline void End()   {  m_end = std::chrono::system_clock::now();   }
    void CalcDuration() {  m_duration = std::max(m_start, m_end) - std::min(m_start, m_end);  }

    timeDuration_t const& GetDuration() const
    {
        return m_duration;
    }
    void Zero()
    {
        m_start = std::chrono::system_clock::now();
        m_end = std::chrono::system_clock::now();
        m_duration = std::max(m_start, m_end) - std::min(m_start, m_end);

    }
    //--------------------------------
    /* TestLatency( i_count )
        Tests the latency / error of the timer class.

        NOTE: this number is how inaccurate your timings can be.
    */

    
    
    static timeDuration_t TestLatency512(size_t const i_count = 512)
      
    {
      
        this_type t;
        timeDuration_t tSum = timeDuration_t::duration::zero();
        for (size_t i = 0; i < i_count; ++i)
        {
            t.Start();
            t.End();
            t.CalcDuration();
            tSum += t.GetDuration();
        }
        return tSum / i_count;
    }
   

private:
    //---------------- private member data ----------------
    timePoint_t     m_start;
    timePoint_t     m_end;
    timeDuration_t  m_duration;

};

using Timer_t = TimerX<>;

//==============================================================================
/*
*/
class timeLines
{
public:
    timeLines();
    ~timeLines();
    void setBpm(int bp) { bPm = bp; }
    void setTimes(int t); 
    void setSequenceLenght(int sqlenght) { seqlenght = sqlenght; }
    void setlatence(int l) { latence = l; }
    int dividers[10] = { 7,7,7,7,7,7,7,7,7 };
    void setDivides(int d, int n) {
        dividers[n] = d; 
        division(n);
    
    }
    void division(int n);

    //-------timer-chrono
    TimerX<double> tm1;
    double timerChrono(int selectsp);

    //------vst-PPQ time------
    void prepare(int sr, int size);
    const double getPpqPerSample(); 
    void processTimeHost(AudioPlayHead* playhead, int nFrames,int selectSp);

    //------vst PPQ sampels--------

    void prosessTimeSampels( int nFrames, int selectSp, int bpm,int div);

   
    //------trigger-GAtes------
    double gates[10] = { 0.3,0.3,0.3,0.3,0.3,0.3,0.3,0.3 };
    void setGate(double g,int n) { gates[n] = g*960; }



    //-----Outputs------
    const int *getHtime1();
    const int* getHtime2();


   
    //*******mainmod


    int data1[10] = { 0,0,0,0,0,0,0 };
    int* getdataOut() { return data1; }
private:
    int setTime;
    int Sampelrate;
    int bPm;
    int tr1off;
    std::atomic<double> currentPositionPpq;
    std::atomic<int> IcurrentPosition;
    std::atomic<int> IcurrentPositionS1;
    std::atomic<int> IcurrentPositionS2;

    double SampelsInMinute;
    AudioPlayHead::CurrentPositionInfo info;
    std::vector<double> ppqPositions;
    std::vector<double> TimeSampelsPositions;
    int seqlenght;
    int mainlfoselect;
    int mainlfoSh;
    int Blocksize;
    int latence;
  
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (timeLines)
};
