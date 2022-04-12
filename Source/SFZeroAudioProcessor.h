#ifndef __PLUGINPROCESSOR_H_7DD34D53__
#define __PLUGINPROCESSOR_H_7DD34D53__

#include "../JuceLibraryCode/JuceHeader.h"
#include "../module/SFZero/SFZero/SFZSynth.h"
#include"PluginParameters.h"
#include"ParasGui.h"
#include"UVmeter.h"
#include"ADSREnvelope.hpp"

using namespace dsp;

namespace SFZero {
	class SFZSound;
	}


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

	
		int getNumPrograms();
		int getCurrentProgram();
		void setCurrentProgram(int index);
		const String getProgramName(int index);
		void changeProgramName(int index, const String& newName);
		
		void getStateInformation(MemoryBlock& destData) override;
		void setStateInformation(const void* data, int sizeInBytes) override;
		void synthRate(double s);
		void updateFilter();
		void updateOverDrive();
		MidiKeyboardState	keyboardState;
		ADSREnvelope ampEG;
		ADSREnvelope ampEGF;


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
	template <typename FloatType>
	void process(AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer);
	template <typename FloatType>
	void applyGain(AudioSampleBuffer& buffer, AudioBuffer<FloatType>& delayBuffer);
	template <typename FloatType>
	void applyDelay(AudioBuffer<FloatType>&, AudioBuffer<FloatType>& delayBuffer);

	AudioBuffer<float> delayBufferFloat;
	AudioBuffer<double> delayBufferDouble;
	int delayPosition = 0;
	double* buff1;
	dsp::ProcessorDuplicator <dsp::IIR::Filter<float>, dsp::IIR::Coefficients <float>> DspFilterL, DspFilterR;
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


	//JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SFZeroAudioProcessor);
	};


#endif  // __PLUGINPROCESSOR_H_7DD34D53__


