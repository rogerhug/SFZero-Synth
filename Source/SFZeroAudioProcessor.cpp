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
	, gParas(valueTreeState)
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
	mPrefV = 0;
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



	fPhi = 0.0;
	twoPi = (float)6.2831853;
	fprev = 0.f;
	updateRing();
	loop1on = new bool[10];
	for (int i = 0; i < 10; i++)
		loop1on[i] = false;
	     looplenght = 4;

		 PitchBendBack = false;
		 midinoteIn = 0;
		 midiChannel = 0;
		 timeX.setBpm(60);
		 timeX.setTimes(1);
		 PitchBendVal = 8192;
	
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


double phasePitch = 1;
double phaseVolume = 1;
double phaseDt = 1;
double phaseDf = 1;
double phaseRing = 1;
double phaseShape = 1;
void SFZeroAudioProcessor::ModulatorOn()
{
if(gParas.mod.stepModValues()[0]>0.1){
  	updateFilter();
}
if (gParas.mod.stepModValues()[1] > 0.1) {
	phasePitch = 1 - (phaseStepper * gParas.mod.stepModValues()[1]);
}
if (gParas.mod.stepModValues()[2] > 0.1) {
	phaseVolume = 1 - (phaseStepper * gParas.mod.stepModValues()[2]);
}
if (gParas.mod.stepModValues()[3] > 0.1) {
	phaseDt = 1 - (phaseStepper * gParas.mod.stepModValues()[3]);
}
if (gParas.mod.stepModValues()[4] > 0.1) {
	phaseDf = 1 - (phaseStepper * gParas.mod.stepModValues()[4]);
}
if (gParas.mod.stepModValues()[5] > 0.1) {
	phaseRing = 1 - (phaseStepper * gParas.mod.stepModValues()[5]);
}
if (gParas.mod.stepModValues()[6] > 0.1) {
	phaseShape = 1 - (phaseStepper * gParas.mod.stepModValues()[6]);
}

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

void SFZeroAudioProcessor::updateCurrentTimeInfoFromHost()
{
	if (auto* ph = getPlayHead())
	{
		AudioPlayHead::CurrentPositionInfo newTime;

		if (ph->getCurrentPosition(newTime))
		{
			lastPosInfo = newTime;  // Successfully got the current time from the host..
			return;
		}
	}

	// If the host fails to provide the current time, we'll just reset our copy to a default..
	lastPosInfo.resetToDefault();
}



void SFZeroAudioProcessor::reset()
{
	delayBufferFloat.clear();
	delayBufferDouble.clear();
}

void SFZeroAudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	ignoreUnused(samplesPerBlock);

	updateRing();
	timeX.prepare(sampleRate, samplesPerBlock);
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



	DspDcL.prepare(spec);
	DspDcL.reset();
	DspDcR.prepare(spec);
	DspDcR.reset();

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




template<typename FloatType>
void SFZeroAudioProcessor::process(AudioBuffer<FloatType>& buffer, MidiBuffer& midiMessages, AudioBuffer<FloatType>& delayBuffer)

{
	if(parameters.egmode.getIndex()>0)
	ampEG.getSample();
	if (parameters.egFmode.getIndex() > 0)
	ampEGF.getSample();

	keyboardState.processNextMidiBuffer(midiMessages, 0, buffer.getNumSamples(), true);

	double on = 0;
	for (const auto metadata : midiMessages)                                                                
	{
		const auto msg = metadata.getMessage() ;

		
         midiChannel = msg.getChannel();
		if (msg.isNoteOn() == true) {
			ampEG.start();	ampEGF.start();
			midinoteIn = msg.getNoteNumber();
			
		
		}
		if (msg.isNoteOff() == true) {
		
				midinoteIn = -1;
	
		if(midinoteIn<0){ ampEG.release();	ampEGF.release(); }
				}
		
		//readInt[0] = msg.isAllSoundOff();
		if (msg.isPitchWheel()) {
			//readInt[2] = msg.getPitchWheelValue();
			PitchBendBack = true;
			if(msg.getPitchWheelValue()!=0)
			parameters.mainPitchBendValue= msg.getPitchWheelValue();

		}
		

		
	
}
			
	//readInt[1] = parameters.mainPitchBendValue;

	
	synth.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
    synth.handlePitchWheel(midiChannel, parameters.mainPitchBendValue*phasePitch);

	if (parameters.RingOnOffValue == true) {
		applyRing(buffer);
	}
	
	
	applyDelay(buffer, delayBuffer);
	for (int channel = 0; channel < getTotalNumInputChannels(); ++channel)
	{
		// MAIN AUDIO PROCESS BLOCK FOR JUCE::DSP FILTER LR
		auto inOutBlockL = juce::dsp::AudioBlock<float>(buffer).getSubsetChannelBlock(0, channel);
		auto inOutBlockR = juce::dsp::AudioBlock<float>(buffer).getSubsetChannelBlock(1, channel);
		auto contextL = juce::dsp::ProcessContextReplacing<float>(inOutBlockL);
		auto contextR = juce::dsp::ProcessContextReplacing<float>(inOutBlockR);

		if (parameters.mainFilterModeV.getIndex() > 0) {
			if (parameters.mainCutoffModValue > 0) { updateFilter(); }
			DspFilterL.process(contextL);
			DspFilterR.process(contextR);
		}

		if (parameters.OverdriveModevalue==true) {
			
			overdriveL.process(contextL);
			overdriveR.process(contextR);
			if (parameters.OverdriveFreqModValue > 0)
				updateOverDrive();
		}


		if (parameters.mainVolumeValue > 0.07) {
			DspDcL.process(contextL);
			DspDcR.process(contextR);
		}
	}

	applylooper(buffer);
updateCurrentTimeInfoFromHost();
	if (gParas.mod.getHostTime() > 0) {
		if (gParas.mod.getHostTime() == 1) {
			timeX.tm1.Start();
			timeX.timerChrono(0);
			phaseStepper = gParas.mod.stepValuesOut()[timeX.getHtime1()[0]];
			ModulatorOn();
		}
		if (gParas.mod.getHostTime() == 2) {
			timeX.tm1.End();
			ModulatorOn();
			
			timeX.prosessTimeSampels(lastPosInfo.timeInSamples, buffer.getNumSamples(),lastPosInfo.bpm,gParas.mod.butNb);
			phaseStepper = gParas.mod.stepValuesOut()[timeX.getHtime2()[0]];
		}

		
	
	}


    applyGain(buffer);

	readInt[0] = timeX.getHtime1()[0];
	//readInt[1] = 3 + lastPosInfo.timeInSamples;
	readInt[2] = timeX.getHtime2()[0];
	
}

template<typename FloatType>
void SFZeroAudioProcessor::applyGain(AudioBuffer<FloatType>& buffer)
{


	

	const float egGainAmpF = parameters.mainVolumeModValue ;
	const float gainLevel = parameters.mainVolumeValue;// 0.01 + (float(parameters.mainVolumeValue * egGainAmpF));
	
		*DspDcL.state = *dsp::IIR::Coefficients<float>::makePeakFilter(44100, 200, 0.1, egGainAmpF);
		*DspDcR.state = *dsp::IIR::Coefficients<float>::makePeakFilter(44100, 200, 0.1, egGainAmpF);
		
	float peakL = 0;

   for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel) {
	auto channelData = buffer.getWritePointer(channel);
	
	for (auto i = 0; i < buffer.getNumSamples(); ++i)
	{	channelData[i] *= gainLevel*phaseVolume;   }
	
}		
	
	float* output[2];
	output[0] = buffer.getWritePointer(0);
	output[1] = buffer.getWritePointer(1);
	peakL = 0.5;// fabs(*output[0]);
	float  METER_ATTACKP = 0.6, METER_DECAYP = 0.05;
	float  xL = (peakL < mPrevL ? METER_DECAYP : METER_ATTACKP);
	peakL = peakL * xL + mPrevL * (1.0 - xL);
	mPrevL = peakL;
}

template<typename FloatType>
void SFZeroAudioProcessor::applyDelay(AudioBuffer<FloatType>& b, AudioBuffer<FloatType>& delayBuffer)
{
	double time_t = parameters.mainDelayTimeValue*phaseDt;
	double mix_t = parameters.mainDelayMixValue*phaseDf;
	auto sw = parameters.mainDelayModeV;
	switch (parameters.mainDelayModeV.getIndex())
	{
	case 0:
		mix_t = 0;
		break;
	case 1:
		break;
	case 2:
		if (time_t > 0.0 && time_t < 0.25) { time_t = 0.25; }
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


	auto delayPos = 0;


	for (auto channel = 0; channel < getTotalNumOutputChannels(); ++channel)
	{
		auto channelData = b.getWritePointer(channel);
		auto delayData = delayBuffer.getWritePointer(jmin(channel, delayBuffer.getNumChannels() - 1));
		delayPos = delayPosition;
		auto numSamples = b.getNumSamples();
		for (auto i = 0; i < numSamples; ++i)
		{



			if (parameters.mainDelayModeV.getIndex() > 0) {

				auto in = channelData[i];
				channelData[i] += delayData[delayPos] * mix_t;
				delayData[delayPos] = ((delayData[delayPos] * parameters.mainDelayFeedValue) + (in * parameters.mainDelayMixValue));

				if (++delayPos >= (delayBuffer.getNumSamples() * time_t))
					delayPos = 0;


			}

		}
	}

	delayPosition = delayPos;
	
}

template<typename FloatType>
void SFZeroAudioProcessor::applyRing(AudioBuffer<FloatType>& buffer)
{

	for (int channel = 0; channel < getTotalNumOutputChannels(); ++channel) {
		for (auto i2 = 0; i2 < buffer.getNumSamples(); ++i2)
		{

			auto channelData = buffer.getWritePointer(0);
			auto channelData1 = buffer.getWritePointer(1);



			float a, b, c, d, g;
			float p, dp, tp = twoPi, fb, fp, fp2;

			p = fPhi;
			dp = fdPhi;
			fb = ffb;
			fp = fprev;
			if (sampleRateOv != 0.0)
			{
				a = float(channelData[i2]);
				b = float(channelData1[i2]);


				g = (float)sin(p);
				p = (float)fmod(p + dp, tp);

				fp = (fb * fp + a) * g;
				fp2 = (fb * fp + b) * g;

				c = fp;
				d = fp2;

				channelData[i2] += c;
				channelData1[i2] += d;
			}


			fPhi = p;
			fprev = fp;





		}
	}
}
bool loopdev = false;
void SFZeroAudioProcessor::setloop1(const bool* i,int n)
{
	for (auto l = 0; l < 5; ++l)
	loop1on[l] = i[l];
	if (n == 1) {
		loopdev = true;
		if (loop1on[0] == true) { looplenght = 1; 	}
		if (loop1on[1] == true) { looplenght = 2; 	}
		if (loop1on[2] == true) { looplenght = 3; 	}
		if (loop1on[3] == true) { looplenght = 4; 	}
	}
	
	if (n == 2) {
		loopdev = true;
		if (loop1on[0] == true) { looplenght = 6; }
		if (loop1on[1] == true) { looplenght = 8; }
		if (loop1on[2] == true) { looplenght = 9; }
		if (loop1on[3] == true) { looplenght = 12; }
}
		if(n == 3) {
			loopdev = true;
			if (loop1on[0] == true) { looplenght = 16; }
			if (loop1on[1] == true) { looplenght = 24; }
			if (loop1on[2] == true) { looplenght = 32; }
			if (loop1on[3] == true) { looplenght = 48; }
		
	}
	if (n == 0)
		loopdev = false;
	
}
float buffloopL[88200] = { 0 };
float buffloopR[88200] = { 0 };
template<typename FloatType>
void SFZeroAudioProcessor::applylooper(AudioBuffer<FloatType>& b)
{
	auto loopPos = 0;
	auto loopPos2 = 0;

	loopPos = loopPosition;
	loopPos2 = loopPosition2;

	auto numSamples = b.getNumSamples();
	for (auto i = 0; i < numSamples; ++i)
	{
		auto channelDataLoopL = b.getWritePointer(0);
		auto channelDataLoopR = b.getWritePointer(1);
		const int loopLenght = (getSampleRate()/ looplenght)*2;

		auto in = channelDataLoopL[i];
		auto inR = channelDataLoopR[i];
		int stl = 0;
		bool StOn = false;
		if (midinoteIn > 0)
			StOn = true;
              
		if (++loopPos2 > loopLenght)
			loopPos2 = 0;

			if (loopdev == true ) {

				if (++loopPos > loopLenght)
					loopPos = 0;
			
				channelDataLoopL[i] += (buffloopL[++loopPos]);
				channelDataLoopR[i] += (buffloopR[++loopPos]);

			}
			else  
				if (++stl > 100) {
					StOn = false;
					stl = 0;
					if (stl < 50) {
						memset(buffloopL, 0, 88200 * sizeof(double));
						memset(buffloopL, 0, 88200 * sizeof(double));
					}
				}
				else
	     	
	
				
				buffloopL[loopPos2] = in;
				buffloopR[loopPos2] = inR;

				
		
		
	}
	loopPosition = loopPos;
	loopPosition2 = loopPos2;

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
	valueTreeState.state.setProperty("sf1", sfzFile.getFullPathName().toRawUTF8(), nullptr);
	
	auto stateParas = valueTreeState.copyState();
	std::unique_ptr<XmlElement> xml(stateParas.createXml());
	copyXmlToBinary(*xml, destData);
	

}

void SFZeroAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{

	pUpdate = true;
	

	std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

	if (xmlState.get() != nullptr)
		if (xmlState->hasTagName(valueTreeState.state.getType()))

		{valueTreeState.replaceState(ValueTree::fromXml(*xmlState));}
	     gParas.mod.unSerialStepps(valueTreeState);

		 sFile.referTo(valueTreeState.state.getPropertyAsValue("sf1", nullptr, true));
		
		if (!sFile.toString().isEmpty()) {
			File file(sFile.toString());
			statefile.createLegalFileName(sFile.toString());
			setSfzFile(&file);
			
			
		}
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
	if (parameters.egFmode.getIndex() > 0.) {
		 egFilterAmp = ampEGF.getValue() * (parameters.mainCutoffModValue);
	
	}
	if (parameters.egFmode.getIndex() == 0) {
		egFilterAmp = 1;// 

	}

	//parameters.mainCutoffValue *= 1 - (phaseStepper * gParas.mod.stepModValues()[0]);
	float freq = 20 + (parameters.mainCutoffValue * 10000) *(egFilterAmp);
	
	freq *= 1-(phaseStepper * gParas.mod.stepModValues()[0]);
	

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
float egmod = 0;
void SFZeroAudioProcessor::updateOverDrive()
{
	

     egmod = 1-(ampEG.getValue()*parameters.OverdriveFreqModValue);
	
	const float freq = (2000-(parameters.OverdriveFreqValue* (egmod*1999)));
	const float gainUp = -35 + (parameters.OverdriveGainUpValue * 70);
	const float gainTh = -35 + (parameters.OverdriveThreshValue* 60);
	
	
	if (sampleRateOv != 0.0)
	{
		

			overdriveL.get<0>().setGainDecibels((gainUp));
			*overdriveL.get<3>().state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRateOv, freq);
			overdriveL.get<4>().setGainDecibels((gainTh));

			overdriveR.get<0>().setGainDecibels((gainUp));
			*overdriveR.get<3>().state = *dsp::IIR::Coefficients<float>::makeHighPass(sampleRateOv, freq);
			overdriveR.get<4>().setGainDecibels((gainTh));
		
		


		
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

