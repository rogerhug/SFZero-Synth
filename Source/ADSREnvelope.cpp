//
//  ADSREnvelope.cpp
//  AudioKit Core
//
//  Created by Shane Dunne, revision history on Github.
//  Copyright © 2018 AudioKit. All rights reserved.
//
#include "ADSREnvelope.hpp"

#include <cmath>



    void ADSREnvelope::init(int t)
    {
        int silenceSamples = int(0.01 * 44100);     // always 10 mSec
     
            envDesc.clear();
            envDesc.push_back({ 0.0, 0.0, 0.0, -1 });               // kIdle: 0 forever
            envDesc.push_back({ 1.0, 0.0, 0.0, silenceSamples });   // kSilence in 10 mSec
        if (t == 0) {
            envDesc.push_back({ 0.0, 1.0, exp(-1.5), 1 });                  // kAttack
            envDesc.push_back({ 1.0, sustainFraction, exp(-4.95),  1 });      // kDecay
            envDesc.push_back({ sustainFraction, sustainFraction, 0.0, -1 });           // kSustain
            envDesc.push_back({ sustainFraction, 0.0, exp(-4.95),  441});    // kRelease
           
        }
        if (t==1)
        {
            envDesc.push_back({ 0.0, 1.0, exp(-1.5), (int)attackSamples });                  // kAttack
            envDesc.push_back({ 1.0, sustainFraction, exp(-4.95),  (int)decaySamples });      // kDecay
            envDesc.push_back({ sustainFraction, sustainFraction, 0.0, -1 });           // kSustain
            envDesc.push_back({ sustainFraction, 0.0, exp(-4.95),  (int)releaseSamples });    // kRelease
        }
        else if (t == 2)
        {
            envDesc.push_back({ 0.0, 1.0, 0.99999,  (int)attackSamples });                    // kAttack
            envDesc.push_back({ 1.0, sustainFraction, exp(-11.05),  (int)decaySamples });     // kDecay
            envDesc.push_back({ sustainFraction, sustainFraction, 0.0, -1 });           // kSustain
            envDesc.push_back({ sustainFraction, 0.0, exp(-11.05),  (int)releaseSamples });   // kRelease
        }
        else  if (t == 3)
        {
            envDesc.push_back({ 0.0, 1.0, 0.0,  (int)attackSamples });                        // kAttack
            envDesc.push_back({ 1.0, sustainFraction, 0.0,  (int)decaySamples });             // kDecay
            envDesc.push_back({ sustainFraction, sustainFraction, 0.0, -1 });           // kSustain
            envDesc.push_back({ sustainFraction, 0.0, 0.0,  (int)releaseSamples });           // kRelease
        }

        env.reset(&envDesc);
    }

    void ADSREnvelope::updateParams()
    {
        
        if (envDesc.size() < 6) return;
      
        envDesc[kAttack].lengthSamples = int(attackSamples);
        envDesc[kDecay].finalValue = sustainFraction;
        envDesc[kDecay].lengthSamples = int(decaySamples);
        envDesc[kSustain].initialValue = envDesc[kSustain].finalValue = sustainFraction;
        envDesc[kRelease].initialValue = sustainFraction;
        envDesc[kRelease].lengthSamples = int(releaseSamples);
    
    }

    void ADSREnvelope::start()
    {
        env.advanceToSegment(kAttack);
    }

    void ADSREnvelope::restart()
    {
        env.advanceToSegment(kSilence);
    }

    void ADSREnvelope::release()
    {
        env.advanceToSegment(kRelease);
    }

    void ADSREnvelope::reset()
    {
        env.reset(&envDesc);
    }


