//
//  ADSREnvelope.hpp
//  AudioKit Core
//
//  Created by Shane Dunne, revision history on Github.
//  Copyright © 2018 AudioKit. All rights reserved.
//
#pragma once
#include "EnvelopeGeneratorBase.hpp"


    struct ADSREnvelope
    {

        float sampleRateHz =441;
        float attackSamples = 1;
        float   decaySamples = 2;
        float releaseSamples = 222;
        float sustainFraction = 1;

        enum EG_Segment
        {
            kIdle = 0,
            kSilence,
            kAttack,
            kDecay,
            kSustain,
            kRelease
        };

        enum CurvatureType
        {
            kLinear,        // all segments linear
            kAnalogLike,    // models CEM3310 integrated circuit
            kLinearInDb     // decay and release are linear-in-dB
        };
        void setAttackDurationSeconds(float attackSeconds) { attackSamples = attackSeconds * sampleRateHz; }
        void setDecayDurationSeconds(float decaySeconds) { decaySamples = decaySeconds * sampleRateHz; }
        void setReleaseDurationSeconds(float releaseSeconds) { releaseSamples = releaseSeconds * sampleRateHz; }

        void init(int t);
     
        void updateParams();

        void start();       // called for note-on
        void restart();     // quickly dampen note then start again
        void release();     // called for note-off
        void reset();       // reset to idle state
        bool isIdle() { return env.getCurrentSegmentIndex() == kIdle; }
        bool isPreStarting() { return env.getCurrentSegmentIndex() == kSilence; }
        bool isReleasing() { return env.getCurrentSegmentIndex() == kRelease; }

        inline float getValue()
        {
            return env.getValue();
        }

        inline float getSample()
        {
            float sample;
            env.getSample(sample);
            return sample;
        }

    protected:
        MultiSegmentEnvelopeGenerator env;
        MultiSegmentEnvelopeGenerator::Descriptor envDesc;
      
    };


