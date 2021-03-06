#ifndef __PLUGINPROCESSOR_H_7DD34D53__
#define __PLUGINPROCESSOR_H_7DD34D53__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../module/SFZero/SFZero/SFZSynth.h"
#include"PluginParameters.h"
#include"ParasGui.h"
#include"UVmeter.h"
#include"ADSREnvelope.hpp"
#include"timeLines.h"

using namespace dsp;

namespace SFZero {
	class SFZSound;
	}

class CParamSmooth
{
public:
	CParamSmooth() { a = 0.09; b = 1. - a; z = 0.; };
	~CParamSmooth() {};
	void a1(double a1) {
		a = a1; b = 1. - a;
	}
	inline double Process(double in) { z = (in * b) + (z * a); return z; }
private:
	double a, b, z;
};
class SFZeroAudioProcessor  : public AudioProcessor

{
	public:
		SFZeroAudioProcessor();
		~SFZeroAudioProcessor();
		

		void reset();
		void prepareToPlay(double sampleRate, int samplesPerBlock);
		void releaseResources();
		void processBlock(AudioBuffer<float>& buffer, MidiBuffer& midi);

		AudioProcessorEditor* createEditor();
		bool hasEditor() const;
	
		const String getName() const;


		void	setSfzFile(File* newSfzFile);
		void	setSfzFileThreaded(File* newSfzFile);
		File	getSfzFile() { return sfzFile; }

		const String getInputChannelName(int channelIndex) const;
		const String getOutputChannelName(int channelIndex) const;
		bool isInputChannelStereoPair(int index) const;
		bool isOutputChannelStereoPair(int index) const;

		bool acceptsMidi() const override { return true; }
		bool producesMidi() const override { return true; }
		juce::MidiBuffer midiBuffer;
		void addMessageToBuffer(const juce::MidiMessage& message)
		{
			auto timestamp = message.getTimeStamp();
			auto sampleNumber = (int)(timestamp * getSampleRate());
			midiBuffer.addEvent(message, sampleNumber);
		}


		bool silenceInProducesSilenceOut() const;
		double getTailLengthSeconds() const;
	
		void ModulatorOn();
		int getNumPrograms();
		int getCurrentProgram();
		void setCurrentProgram(int index);
		const String getProgramName(int index);
		void changeProgramName(int index, const String& newName);
		void updateCurrentTimeInfoFromHost();
		void getStateInformation(MemoryBlock& destData) override;
		void setStateInformation(const void* data, int sizeInBytes) override;
		void synthRate(double s);
		void updateFilter();
		void updateOverDrive();
		static float mydsp_faustpower2_f(float value) {
			return value * value;
		}
		void updateRing()
		{

			fdPhi = (float)(twoPi * 100.0 * (((float(parameters.RingHzValue) * 0.0017))) + (160.0 * (0.1+float(parameters.RingLHzValue) * 0.50065)) / getSampleRate());
			ffb = 0.95f * 0.2;

		}
		
		void setloop1(const bool* i,int n);
	
		
		MidiKeyboardState	keyboardState;
		ADSREnvelope ampEG;
		ADSREnvelope ampEGF;
		timeLines timeX;
		Value sFile;
		double phaseStepper = 0;
		double read[10] = { 0,0,0,0 };
		int readInt[10] = { 0,0,0,0 };

		double loadProgress;
	
		SFZero::SFZSound*	getSound();
		int      	numVoicesUsed();
		String   	voiceInfoString();
		bool pUpdate;
		File statefile;
		int midinoto;
		double velo;
		double meterOut;
		float mPrevL;
		float egGain;
		float egFilter;
		float rateSmL;
		UVmeter meterV;
		float mPrefV;
		bool PitchBendBack;
		int PitchBendVal;
		int midinoteIn;
		int midiChannel;
		UndoManager undoManager;
	    AudioProcessorValueTreeState valueTreeState;
		ParasGui gParas;


	int midiNumber;
	PluginParameters parameters;
#if JUCE_DEBUG
		void	relayLogMessages();
#endif

	protected:
		class LoadThread : public Thread {
			public:
				LoadThread(SFZeroAudioProcessor* processor);
				void	run();

			protected:
				SFZeroAudioProcessor* processor;
			};
		friend class LoadThread;

		File sfzFile;
		SFZero::SFZSynth synth;
		double startTime;
		AudioFormatManager formatManager;
		LoadThread	loadThread;
	
		void	loadSound(Thread* thread = NULL);
	
	
private:

	CParamSmooth smlevel, smlevel1,loop1, loop1R;;
	template <typename FloatType>
	void process(AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer);
	template <typename FloatType>
	void applyGain(AudioBuffer<FloatType>& buffer);
	template <typename FloatType>
	void applyDelay(AudioBuffer<FloatType>&, AudioBuffer<FloatType>& delayBuffer);
	template <typename FloatType>
	void applyRing(AudioBuffer<FloatType>& buffer);
	template <typename FloatType>
	void applylooper(AudioBuffer<FloatType>& buffer);
	AudioBuffer<float> delayBufferFloat;
	AudioBuffer<double> delayBufferDouble;
	int delayPosition = 0;
	int loopPosition = 0;
	int loopPosition2 = 0;
	double* buff1;
	dsp::ProcessorDuplicator <dsp::IIR::Filter<float>, dsp::IIR::Coefficients <float>> DspFilterL, DspFilterR,DspDcL, DspDcR;
	using GainProcessor = Gain<float>;
	using BiasProcessor = Bias<float>;
	using DriveProcessor = WaveShaper<float>;
	using DCFilter = ProcessorDuplicator<IIR::Filter<float>,IIR::Coefficients<float>>;
	enum
	{
		preGainIndex,
		biasIndex,
		shaperIndex,
		filterIndex,
		postGainIndex
	};
	ProcessorChain<GainProcessor, BiasProcessor, DriveProcessor, DCFilter, GainProcessor> overdriveL, overdriveR;

	double sampleRateOv = 0.0;
	float fPhi;
	float fdPhi;
	float nul;
	float twoPi;
	float ffb, fprev;

	float fRec1[2];
	int fSampleRate;
	float fConst1;
	float fConst2;
	float fRec2[2];
	float fRec3[2];
	float fRec0[3];

	bool *loop1on;
	int looplenght;
	AudioPlayHead::CurrentPositionInfo lastPosInfo;
	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SFZeroAudioProcessor);
	};


#endif  // __PLUGINPROCESSOR_H_7DD34D53__


