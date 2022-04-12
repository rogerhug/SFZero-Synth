#include "SFZeroAudioProcessor.h"
#include "SFZeroEditor.h"

#include "../module/SFZero/SFZero/SF2Sound.h"
#include "../module/SFZero/SFZero/SF2Sound.h"
#include "../module/SFZero/SFZero/SFZVoice.h"
#include "../module/SFZero/SFZero/SFZDebug.h"

using namespace SFZero;

SFZeroAudioProcessor::SFZeroAudioProcessor()
	: AudioProcessor(BusesProperties().withInput("Input", juce::AudioChannelSet::stereo(), true)
		.withOutput("Output", juce::AudioChannelSet::stereo(), true))

	, loadProgress(0.0)
	, loadThread(this)
	, valueTreeState(*this, &undoManager)
	, parameters(valueTreeState)

{
	#if JUCE_DEBUG
	setupLogging(
		FileLogger::createDefaultAppLogger(
			"SFZero", "SFZero.log", "SFZero started"));
#endif
	parameters.createAllParameters();
	valueTreeState.state = ValueTree(Identifier(JucePlugin_Name));


	formatManager.registerFormat(new WavAudioFormat(), false);
	formatManager.registerFormat(new OggVorbisAudioFormat(), false);
	pUpdate = false;
	buff1 = new double[2048];
	for (int i = 0; i < 128; ++i) {
		synth.addVoice(new SFZVoice());
		// ..and give the synth a sound to play
	}
	



	meterOut = 0;
	mPrevL = 0;
	egGain = 0;
	egFilter = 0;
	rateSmL = 0;
	sampleRateOv = 0.0;
	updateFilter();

	updateOverDrive();
	readInt[2] = 0;

	ampEG.updateParams();
	ampEG.init(0);
	ampEGF.updateParams();
	ampEGF.init(0);
}

SFZeroAudioProcessor::~SFZeroAudioProcessor()
{
}

const String SFZeroAudioProcessor::getName() const
{
    return JucePlugin_Name;
}



void SFZeroAudioProcessor::setSfzFile(File* newSfzFile)
{
	sfzFile = *newSfzFile;
	loadSound();
}


void SFZeroAudioProcessor::setSfzFileThreaded(File* newSfzFile)
{
	loadThread.stopThread(2000);
	sfzFile = *newSfzFile;
	loadThread.startThread();
}


const String SFZeroAudioProcessor::getInputChannelName(int channelIndex) const
{
    return String(channelIndex + 1);
}

const String SFZeroAudioProcessor::getOutputChannelName(int channelIndex) const
{
    return String(channelIndex + 1);
}

bool SFZeroAudioProcessor::isInputChannelStereoPair(int index) const
{
    return true;
}

bool SFZeroAudioProcessor::isOutputChannelStereoPair(int index) const
{
    return true;
}


bool SFZeroAudioProcessor::silenceInProducesSilenceOut() const
{
	return true;
}


double SFZeroAudioProcessor::getTailLengthSeconds() const
{
	//*** What is correct here?  Should we iterate through all the voices to get
	// the longest current release time?
	return 0;
}


int SFZeroAudioProcessor::getNumPrograms()
{
	return 0;
}

int SFZeroAudioProcessor::getCurrentProgram()
{
	return 0;
}

void SFZeroAudioProcessor::setCurrentProgram(int index)
{
}

const String SFZeroAudioProcessor::getProgramName(int index)
{
	return String();
}

void SFZeroAudioProcessor::changeProgramName(int index, const String& newName)
{
}



void SFZeroAudioProcessor::reset()
{
	delayBufferFloat.clear();
	delayBufferDouble.clear();
}

void SFZeroAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	ignoreUnused(samplesPerBlock);

	
	synth.setCurrentPlaybackSampleRate(sampleRate);
	keyboardState.reset();
	// clear extra channels
	
	// prepare processors here
	dsp::ProcessSpec spec;
	spec.sampleRate = sampleRate;
	spec.maximumBlockSize = samplesPerBlock;
	spec.numChannels = getTotalNumOutputChannels();
     sampleRateOv = spec.sampleRate;

	
	

	sampleRate = spec.sampleRate;

	auto& gainUp = overdriveL.get<0>();
	gainUp.setGainDecibels(24);

	auto& bias = overdriveL.get<1>();
	bias.setBias(0.4f);

	auto& wavShaper = overdriveL.get<2>();
	wavShaper.functionToUse = std::tanh;
	

	auto& dcFilter = overdriveL.get<3>();
	dcFilter.state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRate, 2);

	auto& gainDown = overdriveL.get<4>();
	gainDown.setGainDecibels(-18.0f);

	overdriveL.prepare(spec);
	overdriveL.reset();

	auto& gainUpR = overdriveR.get<0>();
	gainUpR.setGainDecibels(24);

	auto& biasR = overdriveR.get<1>();
	biasR.setBias(0.4f);

	auto& wavShaperR = overdriveR.get<2>();
	wavShaperR.functionToUse = std::tanh;

	auto& dcFilterR = overdriveR.get<3>();
	dcFilterR.state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRate,2);

	auto& gainDownR = overdriveR.get<4>();
	gainDownR.setGainDecibels(-18.0f);


	overdriveR.prepare(spec);
	overdriveR.reset();

	
	//ampEG.init();





	DspFilterL.prepare(spec);
	DspFilterL.reset();
	DspFilterR.prepare(spec);
	DspFilterR.reset();
	updateFilter();
	if (isUsingDoublePrecision())
	{
		delayBufferDouble.setSize(2, 12000);
		delayBufferFloat.setSize(1, 1);
	}
	else
	{
		delayBufferFloat.setSize(2, 12000);
		delayBufferDouble.setSize(1, 1);
	}

	reset();
}

void SFZeroAudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
	keyboardState.reset();
	ampEG.reset();
	ampEGF.reset();
}
inline double fastClip(double x, double low, double high)
{
	double x1 = fabs(x - low);
	double x2 = fabs(x - high);
	x = x1 + low + high - x2;

	return x * 0.5;
}
int readeq[20] = { 0 };
void SFZeroAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	jassert(!isUsingDoublePrecision());
	process(buffer, midiMessages, delayBufferFloat);
	
}


int midinoteIn = 0;
int midiChannel = 0;

template<typename FloatType>
void SFZeroAudioProcessor::process(AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer)

{

	//ampEG.init();

ampEG.getSample();
ampEGF.getSample();
	keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);
	double on = 0;
	for (const auto metadata : midiMessages)                                                                
	{
		const auto msg = metadata.getMessage() ;
		if (msg.isNoteOn() == true) {
			ampEG.start();	ampEGF.start();
			midinoteIn = msg.getNoteNumber(); midiChannel = msg.getChannel();
		
		}
		if (msg.isNoteOff() == true) {
			ampEG.release();	ampEGF.release();
			midinoteIn = -1;
		}
		if(msg.isPitchWheel())
		readInt[2] = msg.getPitchWheelValue();
}
		readInt[0] = midinoteIn;
		readInt[1] = midiChannel;	
	// fix velocity in juce_synthesizer.cpp/ void Synthesiser::handleMidiEvent (const MidiMessage& m)---> max 100  
	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
	
	
	read[1] = parameters.mainCutoffValue;
	applyGain(buffer, delayBuffer);
	applyDelay(buffer, delayBuffer);
	for (int channel = 0; channel < getTotalNumInputChannels(); ++channel)
	{
		// MAIN AUDIO PROCESS BLOCK FOR JUCE::DSP FILTER LR
		auto inOutBlockL = juce::dsp::AudioBlock<float>(buffer).getSubsetChannelBlock(0, channel);
		auto inOutBlockR = juce::dsp::AudioBlock<float>(buffer).getSubsetChannelBlock(1, channel);
		auto contextL = juce::dsp::ProcessContextReplacing<float>(inOutBlockL);
		auto contextR = juce::dsp::ProcessContextReplacing<float>(inOutBlockR);
	

		if (parameters.mainFilterModeV.getIndex() > 0) {
			if (parameters.mainCutoffModValue > 0) {  updateFilter();}
			DspFilterL.process(contextL);
			DspFilterR.process(contextR);
		}
	
		if (parameters.ovmode.getIndex() > 0) {
			if (parameters.mainVolumeModValue > 0) { updateOverDrive(); }
			overdriveL.process(contextL);
			overdriveR.process(contextR);
		}

	//  MAIN OUTPUT PEAK LEVEL LEFT
	}	
}

template<typename FloatType>
void SFZeroAudioProcessor::applyGain(AudioSampleBuffer& buffer , AudioBuffer<FloatType>& delayBuffer)
{
	ignoreUnused(delayBuffer);

	float egGainAmp = ampEG.getValue() * parameters.mainVolumeModValue;
	
	 float gainLevel = (parameters.mainVolumeValue*4)//----   not here ## * # egGainAmp;
	
	float peakL = 0;
    for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel)
		buffer.applyGain(channel, 0, buffer.getNumSamples(), gainLevel);

	float* output[2];
	output[0] = buffer.getWritePointer(0);
	output[1] = buffer.getWritePointer(1);
	peakL =  fabs(*output[0]);
	float  METER_ATTACKP = 0.6, METER_DECAYP = 0.05;
	float  xL = (peakL < mPrevL ? METER_DECAYP : METER_ATTACKP);
	peakL = peakL * xL + mPrevL * (1.0 - xL);
	mPrevL = peakL;
}

template<typename FloatType>
void SFZeroAudioProcessor::applyDelay(AudioBuffer<FloatType>&b, AudioBuffer<FloatType>& delayBuffer)
{
	double time_t = parameters.mainDelayTimeValue;
	double mix_t = parameters.mainDelayMixValue;
	auto sw = parameters.mainDelayModeV;
	switch (parameters.mainDelayModeV.getIndex())
	{
	case 0:
		 mix_t = 0;
		break;
	case 1:
		break;
	case 2:
		if (time_t > 0.0 && time_t<0.25) { time_t = 0.25; }
		if (time_t > 0.25 && time_t < 0.5) { time_t = 0.5; }
		if (time_t > 0.55 && time_t < 0.75) { time_t = 0.75; }
		else
			time_t = 0.999999;
		break;
	case 3:
		time_t *= 0.1;
		break;
	case 4:
		time_t *= 0.07;
		break;
	case 5:
		time_t *= 0.2;
		break;
	default:
			break;

	}
	auto numSamples = b.getNumSamples();

	auto delayPos = 0;

	for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
	{
		auto channelData = b.getWritePointer(channel);
		auto delayData = delayBuffer.getWritePointer(jmin(channel, delayBuffer.getNumChannels() - 1));
		delayPos = delayPosition;

		for (auto i = 0; i < numSamples; ++i)
		{
			auto in = channelData[i];
			channelData[i] += delayData[delayPos]*mix_t;
			delayData[delayPos] = ((delayData[delayPos]* parameters.mainDelayFeedValue) + (in*parameters.mainDelayMixValue)) ;

			if (++delayPos >= (delayBuffer.getNumSamples()*time_t))
				delayPos = 0;
		}
	}

	delayPosition = delayPos;
}



bool SFZeroAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}


AudioProcessorEditor* SFZeroAudioProcessor::createEditor()
{
	return new SFZeroEditor(*this);
}


void SFZeroAudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// There's something weird about JUCE's DynamicObjects that doesn't allow
	// them to be used as stack-allocated variables.
	DynamicObject::Ptr state = new DynamicObject();
	state->setProperty("sfzFilePath", sfzFile.getFullPathName());
	SFZSound* sound = getSound();
	if (sound) {
		int subsound = sound->selectedSubsound();
		if (subsound != 0)
			state->setProperty("subsound", subsound);
	}

	MemoryOutputStream out(destData, false);
	JSON::writeToStream(out, var(state));


	auto stateParas = valueTreeState.copyState();
	std::unique_ptr<XmlElement> xml(stateParas.createXml());
	copyXmlToBinary(*xml, destData);
}

void SFZeroAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	MemoryInputStream in(data, sizeInBytes, false);
	var state = JSON::parse(in);
	var pathVar = state["sfzFilePath"];
	if (pathVar.isString()) {
		String sfzFilePath = pathVar.toString();
		if (!sfzFilePath.isEmpty()) {
			File file(sfzFilePath);
			statefile.createLegalFileName(sfzFilePath);
			setSfzFile(&file);
			SFZSound* sound = getSound();
			if (sound) {
				var subsoundVar = state["subsound"];
				if (subsoundVar.isInt())
					sound->useSubsound(int(subsoundVar));
			}
		}
	}
	pUpdate = true;


	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(valueTreeState.state.getType()))

		{valueTreeState.replaceState(ValueTree::fromXml(*xmlState));}

}

void SFZeroAudioProcessor::synthRate(double s)
{
	float n = 1-(s / 240);
	float rateSm = n * getSampleRate()*2 ;
	const float METER_ATTACKR = 0.5, METER_DECAYR = 0.05;
	const float xLG = (rateSm < rateSmL ? METER_DECAYR : METER_ATTACKR);
	rateSm = rateSm * xLG + rateSm * (1.0 - xLG);
	synth.setCurrentPlaybackSampleRate(rateSm);
	readInt[3] = (int)rateSm;
}

void SFZeroAudioProcessor::updateFilter()
{
	float egFilterAmp = 1;
	if (parameters.mainCutoffModValue > 0.02) {
		 egFilterAmp = ampEGF.getValue() * (parameters.mainCutoffModValue);
	
	}
	float freq = 20 + (parameters.mainCutoffValue * 10000) *(egFilterAmp);
	
	
	

	float res = parameters.mainResonanceValue*6;
	float shelf = parameters.mainFilterGainValue;
	switch (parameters.mainFilterModeV.getIndex())
	{
	case 1:  
		*DspFilterL.state = *dsp::IIR::Coefficients<float>::makeLowPass(44100, freq, res);
		*DspFilterR.state = *dsp::IIR::Coefficients<float>::makeLowPass(44100, freq, res);
         break;
	case 2:
		*DspFilterL.state = *dsp::IIR::Coefficients<float>::makeHighPass(44100, freq, res);
		*DspFilterR.state = *dsp::IIR::Coefficients<float>::makeHighPass(44100, freq, res);
		break;
	case 3:
		*DspFilterL.state = *dsp::IIR::Coefficients<float>::makeBandPass(44100, freq, res);
		*DspFilterR.state = *dsp::IIR::Coefficients<float>::makeBandPass(44100, freq, res);
		break;
	case 4:
		*DspFilterL.state = *dsp::IIR::Coefficients<float>::makeAllPass(44100, freq, res);
		*DspFilterR.state = *dsp::IIR::Coefficients<float>::makeAllPass(44100, freq, res);
		break;
	case 5:
		*DspFilterL.state = *dsp::IIR::Coefficients<float>::makePeakFilter(44100, freq, res,shelf);
		*DspFilterR.state = *dsp::IIR::Coefficients<float>::makePeakFilter(44100, freq, res,shelf);
		break;
	case 6:
		*DspFilterL.state = *dsp::IIR::Coefficients<float>::makeNotch(44100, freq, res);
		*DspFilterR.state = *dsp::IIR::Coefficients<float>::makeNotch(44100, freq, res);
		break;
	case 7:
		*DspFilterL.state = *dsp::IIR::Coefficients<float>::makeLowShelf(44100, freq, res,shelf);
		*DspFilterR.state = *dsp::IIR::Coefficients<float>::makeLowShelf(44100, freq, res, shelf);
		break;
	case 8:
		*DspFilterL.state = *dsp::IIR::Coefficients<float>::makeHighShelf(44100, freq, res, shelf);
		*DspFilterR.state = *dsp::IIR::Coefficients<float>::makeHighShelf(44100, freq, res, shelf);
		break;
	   default:
		break;
	}
}

void SFZeroAudioProcessor::updateOverDrive()
{

	const float freq = 1+(parameters.OverdriveFreqValue*100);
	const float gainUp = -35 + (parameters.OverdriveGainUpValue * 70);
	const float gainTh = -35 + (parameters.OverdriveThreshValue* 60);
	

	if (sampleRateOv != 0.0)
	{


		overdriveL.get<0>().setGainDecibels((gainUp));
		*overdriveL.get<3>().state= *dsp::IIR::Coefficients<float>::makeHighPass(sampleRateOv, freq);
		overdriveL.get<4>().setGainDecibels( (gainTh));

		overdriveR.get<0>().setGainDecibels( (gainUp));
		*overdriveR.get<3>().state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRateOv, freq);
		overdriveR.get<4>().setGainDecibels( (gainTh));
	}
}

SFZSound* SFZeroAudioProcessor::getSound()
{
	SynthesiserSound* sound = synth.getSound(0);
	return dynamic_cast<SFZSound*>(sound);
	
}


int SFZeroAudioProcessor::numVoicesUsed()
{
	return synth.numVoicesUsed();
}


String SFZeroAudioProcessor::voiceInfoString()
{
	return synth.voiceInfoString();
}


#if JUCE_DEBUG
void SFZeroAudioProcessor::relayLogMessages()
{
	relayFifoLogMessages();
}
#endif



void SFZeroAudioProcessor::loadSound(Thread* thread)
{
	loadProgress = 0.0;
	synth.clearSounds();

	if (!sfzFile.existsAsFile()) {
		//***
		return;
		}

	SFZSound* sound;
	String extension = sfzFile.getFileExtension();
	if (extension == ".sf2" || extension == ".SF2")
		sound = new SF2Sound(sfzFile);
	else
		sound = new SFZSound(sfzFile);
	sound->loadRegions();
	sound->loadSamples(&formatManager, &loadProgress, thread);
	if (thread && thread->threadShouldExit()) {
		delete sound;
		return;
		}

	synth.addSound(sound);
}




SFZeroAudioProcessor::LoadThread::LoadThread(SFZeroAudioProcessor* processorIn)
	: Thread("SFZLoad"), processor(processorIn)
{
}


void SFZeroAudioProcessor::LoadThread::run()
{
	processor->loadSound(this);
}




AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SFZeroAudioProcessor();
}

