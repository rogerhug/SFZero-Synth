#include "SFZeroEditor.h"
#include "SFZeroAudioProcessor.h"
#include "../module/SFZero/SFZero/SFZSound.h"
#include "../module/SFZero/SFZero/SFZDebug.h"






using namespace SFZero;


enum {
	hMargin = 112,
	vMargin = 112,
	labelHeight = 25,
	progressBarHeight = 30,
	keyboardHeight = 54,
	};

float r = 0;
SFZeroEditor::SFZeroEditor(SFZeroAudioProcessor& ownerFilter)
	: AudioProcessorEditor(ownerFilter),
	audioProcessor(ownerFilter),
		fileLabel(String(), "File... (click here to choose)"),
		pathLabel(String()),
		showingInfo(showingSoundInfo),
		midiKeyboard(ownerFilter.keyboardState, MidiKeyboardComponent::horizontalKeyboard),
	    progressBar(NULL)
	, undoButton(TRANS("Undo"))
	, redoButton(TRANS("Redo"))

	, parameters(ownerFilter.parameters)
	
	{
	

	
#ifdef JUCE_MAC
	Font fileFont("Helvetica", 22.0, Font::bold);
	Font labelFont("Helvetica", 15.0, Font::plain);
#else
	Font fileFont("Ariel", 22.0, Font::bold);
	Font labelFont("Ariel", 15.0, Font::plain);
#endif
		auto* hyperlink1 = (new HyperlinkButton("Git-Source",
			{ "https://github.com/rogerhug/DeadPoolAudio_Modelx4_juce" }));

		addAndMakeVisible(hyperlink1);

		hyperlink1->setBounds(10, 270, 90, 22);

		auto* hyperlink2 = (new HyperlinkButton("Map_Editor",
			{ "http://steveholt.drealm.info/sfZed.html" }));

		addAndMakeVisible(hyperlink2);


		hyperlink2->setBounds(120, 270, 90, 22);
	
	auto* claf = new LookAndFeel_V2;
	addAndMakeVisible(SfZProgrammLabel);
	SfZProgrammLabel.setText("load preset or drop on SFZ.file", juce::dontSendNotification);
	SfZProgrammLabel.setFont(fileFont);
	SfZProgrammLabel.setColour(Label::textColourId, Colours::grey);

	addAndMakeVisible(ReadOutLabel);
	ReadOutLabel.setFont(fileFont);
	ReadOutLabel.setColour(Label::textColourId, Colours::grey);

	addAndMakeVisible(&fileLabel);
	fileLabel.setFont(fileFont);
	fileLabel.setColour(Label::textColourId, Colours::white);
	fileLabel.addClickListener(this);

	addAndMakeVisible(&pathLabel);
	pathLabel.setFont(labelFont);
	pathLabel.setColour(Label::textColourId, Colours::blue);
	pathLabel.addClickListener(this);


	addAndMakeVisible(&infoLabel);
	infoLabel.setFont(labelFont);
	infoLabel.setColour(Label::textColourId, Colours::blue);
	infoLabel.addClickListener(this);


	
	textEntryBox.setMultiLine(true);
	textEntryBox.setReturnKeyStartsNewLine(true);
	textEntryBox.setEnabled(false);
	addAndMakeVisible(textEntryBox);

	textEntryBoxErrors.setMultiLine(true);
	textEntryBoxErrors.setReturnKeyStartsNewLine(true);
	textEntryBoxErrors.setText("Announcement text.");
	addAndMakeVisible(textEntryBoxErrors);




	addAndMakeVisible(&midiKeyboard);
	midiKeyboard.setOctaveForMiddleC(4);


	

	startTimer(1);
	startTimerHz(20);
	
	fileComp.reset(new juce::FilenameComponent("fileComp",
		{},                       // current file
		false,                    // can edit file name,
		false,                    // is directory,
		false,                    // is for saving,
		{},                       // browser wildcard suffix,
		{},                       // enforced suffix,
		"Select file to open"));  // text when nothing selected
	addAndMakeVisible(fileComp.get());
	fileComp->addListener(this);

	
	

	fileComp->setLookAndFeel(claf);
	fileComp.get()->setVisible(true);

	addAndMakeVisible(audioProcessor.gParas);
	audioProcessor.gParas.setLookAndFeel(claf);

	File sfzFile = ownerFilter.getSfzFile();

	
	if (sfzFile != String()) {
		updateFile(&sfzFile);
		showSoundInfo();
		SFZSound* sound = ownerFilter.getSound();
		if (sound && sound->numSubsounds() > 1)
			showSubsound();
		}
	else
		showVersion();


	setSize(650, 360);
	startTimer(1);
	// start a timer which will keep our timecode display updated
	startTimerHz(30);
	parameters.attachControls(
		audioProcessor.gParas.PitchBendSlider
		,audioProcessor.gParas.PitchSlider
		, audioProcessor.gParas.VolumeSlider
		, audioProcessor.gParas.egVolumeSlider
		, audioProcessor.gParas.Cutoff
		,audioProcessor.gParas.FilterGain
		, audioProcessor.gParas.CutMod
		, audioProcessor.gParas.Resonance
		,audioProcessor.gParas.autoQ
		, audioProcessor.gParas.FilterModeCombo
		, audioProcessor.gParas.DelayModeCombo
		, audioProcessor.gParas.DelayTime
		, audioProcessor.gParas.DelayFeed
		, audioProcessor.gParas.DelayLevel
		, audioProcessor.gParas.DelayMix
		, audioProcessor.gParas.OverDOnOffBut
		, audioProcessor.gParas.mainOverDFreqSlider
		, audioProcessor.gParas.OverDriveFreqModSlider
		, audioProcessor.gParas.mainOverDGainUp
		, audioProcessor.gParas.mainOverDThresh
		,audioProcessor.gParas.RingOnOffBut
		, audioProcessor.gParas.RingFrequenceSlider
		, audioProcessor.gParas.RingFrequenceModSlider
		, audioProcessor.gParas.RingLowHzSlider
		,audioProcessor.gParas.egModyPolyButton
		,audioProcessor.gParas.egModeCombo
		,audioProcessor.gParas.egAtackSlider
		, audioProcessor.gParas.egDecaySlider
		, audioProcessor.gParas.egSustainSlider
		, audioProcessor.gParas.egReleaseSlider
		, audioProcessor.gParas.egVeloSensSlider
		, audioProcessor.gParas.egSmoothSensSlider
		, audioProcessor.gParas.egFModeCombo
		, audioProcessor.gParas.egFAtackSlider
		, audioProcessor.gParas.egFDecaySlider
		, audioProcessor.gParas.egFSustainSlider
		, audioProcessor.gParas.egFReleaseSlider
		, audioProcessor.gParas.egFVeloSensSlider
		, audioProcessor.gParas.egFSmoothSensSlider


	);
	audioProcessor.gParas.PitchBendSlider.onValueChange = [this] {
		
	};
	audioProcessor.gParas.PitchSlider.onValueChange = [this] {
		audioProcessor.synthRate(audioProcessor.gParas.PitchSlider.getValue());
	};
	audioProcessor.gParas.VolumeSlider.onValueChange = [this] {};
    audioProcessor.gParas.FilterModeCombo.onChange = [this] {
		audioProcessor.updateFilter();
	};
	audioProcessor.gParas.Cutoff.onValueChange = [this] {
	
		audioProcessor.updateFilter();
	
	};
	audioProcessor.gParas.CutMod.onValueChange = [this] {

		//audioProcessor.updateFilter();
	};
	audioProcessor.gParas.Resonance.onValueChange = [this] {
	
		audioProcessor.updateFilter();
	
	};
	
	audioProcessor.gParas.FilterGain.onValueChange = [this] {
	
		audioProcessor.updateFilter();
	
	};
	audioProcessor.gParas.RingFrequenceSlider.onValueChange = [this] {
		audioProcessor.updateRing();
	};
	audioProcessor.gParas.RingLowHzSlider.onValueChange = [this] {
		audioProcessor.updateRing();
	};
	
	//--------------delay--------------------
	audioProcessor.gParas.DelayModeCombo.onChange = [this] {
		
	};
	audioProcessor.gParas.DelayTime.onValueChange = [this] {};
	audioProcessor.gParas.DelayFeed.onValueChange = [this] {};
	audioProcessor.gParas.DelayLevel.onValueChange = [this] {};
	audioProcessor.gParas.DelayMix.onValueChange = [this] {	};


	//---------------shaper--------------------

	audioProcessor.gParas.OverDOnOffBut.onClick = [this] {audioProcessor.updateOverDrive(); };
	audioProcessor.gParas.mainOverDFreqSlider.onValueChange = [this] {audioProcessor.updateOverDrive(); };
	audioProcessor.gParas.OverDriveFreqModSlider.onValueChange = [this] {audioProcessor.updateOverDrive(); };
	audioProcessor.gParas.mainOverDGainUp.onValueChange = [this] {audioProcessor.updateOverDrive(); };
	audioProcessor.gParas.mainOverDThresh.onValueChange = [this] {audioProcessor.updateOverDrive(); };


	//------------------------amp envelope---------------------------

	audioProcessor.gParas.egModyPolyButton.onClick = [this] {};

	audioProcessor.gParas.egModeCombo.onChange = [this] {

		audioProcessor.ampEG.init(audioProcessor.gParas.egModeCombo.getSelectedItemIndex());
		audioProcessor.ampEG.updateParams();
	};
	audioProcessor.gParas.egAtackSlider.onValueChange = [this] {
		audioProcessor.ampEG.setAttackDurationSeconds(audioProcessor.gParas.egAtackSlider.getValue());
		audioProcessor.ampEG.updateParams();
	};

	audioProcessor.gParas.egDecaySlider.onValueChange = [this] {
		audioProcessor.ampEG.setDecayDurationSeconds(audioProcessor.gParas.egDecaySlider.getValue());
		audioProcessor.ampEG.updateParams();
	};

	audioProcessor.gParas.egSustainSlider.onValueChange = [this] {
	audioProcessor.ampEG.sustainFraction=(audioProcessor.gParas.egSustainSlider.getValue());
	};

	audioProcessor.gParas.egReleaseSlider.onValueChange = [this] {
	audioProcessor.ampEG.setReleaseDurationSeconds(audioProcessor.gParas.egReleaseSlider.getValue());
	audioProcessor.ampEG.updateParams();
	};
	audioProcessor.gParas.egVeloSensSlider.onValueChange = [this] {
	(audioProcessor.gParas.egVeloSensSlider.getValue());
	};

	audioProcessor.gParas.egSmoothSensSlider.onValueChange = [this] {
		(audioProcessor.gParas.egSmoothSensSlider.getValue());
	};
	//------------------------filter envelope---------------------------
	audioProcessor.gParas.egFModeCombo.onChange = [this] {

		audioProcessor.ampEGF.init(audioProcessor.gParas.egFModeCombo.getSelectedItemIndex());
		audioProcessor.ampEGF.updateParams();
	};
	audioProcessor.gParas.egFAtackSlider.onValueChange = [this] {
		audioProcessor.ampEGF.setAttackDurationSeconds(audioProcessor.gParas.egFAtackSlider.getValue());
		audioProcessor.ampEGF.updateParams();
	};

	audioProcessor.gParas.egFDecaySlider.onValueChange = [this] {
		audioProcessor.ampEGF.setDecayDurationSeconds(audioProcessor.gParas.egFDecaySlider.getValue());
		audioProcessor.ampEGF.updateParams();
	};

	audioProcessor.gParas.egFSustainSlider.onValueChange = [this] {
		audioProcessor.ampEGF.sustainFraction = (audioProcessor.gParas.egFSustainSlider.getValue());
	};

	audioProcessor.gParas.egFReleaseSlider.onValueChange = [this] {
		audioProcessor.ampEGF.setReleaseDurationSeconds(audioProcessor.gParas.egFReleaseSlider.getValue());
		audioProcessor.ampEGF.updateParams();
	};
	audioProcessor.gParas.egVeloSensSlider.onValueChange = [this] {
		(audioProcessor.gParas.egVeloSensSlider.getValue());
	};
	audioProcessor.gParas.egFSmoothSensSlider.onValueChange = [this] {
		(audioProcessor.gParas.egFSmoothSensSlider.getValue());
	};
	addAndMakeVisible(audioProcessor.meterV);

	
        for (int i = 0; i < 5; i++) {
		audioProcessor.gParas.MainMenuButtons[i].onClick = [this] {
			audioProcessor.gParas.mainMenuValue();
			audioProcessor.gParas.hideControlMain();
		};
	}

		
		
	
		
}
	




SFZeroEditor::~SFZeroEditor()
{
	delete progressBar;
}


void SFZeroEditor::paint(Graphics& g)
{
	g.setGradientFill(ColourGradient(Colours::black, 0, 0,
		Colours::darkgrey, 0, (float)getHeight(), false));
	g.fillAll();

	

}


void SFZeroEditor::resized()
{
	ReadOutLabel.setBounds(225, 0, 400, 30);

	//textEntryBoxErrors.setBounds(500, 200, 200, 300);
	audioProcessor.gParas.setBounds(220, 30, 580, 280);
  // SfZProgrammLabel.setBounds(200, 20, 400, 20);
	//fileComp.get()->setBounds(200, 40, 450, 70);

	fileLabel.setBounds(20, 0, 200, 30);
	pathLabel.setBounds(20, 30, 200, 30);

	infoLabel.setBounds(20, 60, 200, 20);
    textEntryBox.setBounds(20, 80, 200, 190);
    midiKeyboard.setBounds(20, 290, 620, 70);




}


void SFZeroEditor::labelClicked(Label* clickedLabel)
{
	if (clickedLabel == &fileLabel)
		chooseFile();

	else if (clickedLabel == &pathLabel) {
		if (showing == showingSubsound) {
			SFZeroAudioProcessor* processor = getProcessor();
			SFZSound* sound = processor->getSound();
			if (sound) {
				PopupMenu menu;
				int selectedSubsound = sound->selectedSubsound();
				int numSubsounds = sound->numSubsounds();
				for (int i = 0; i < numSubsounds; ++i) {
					menu.addItem(
						i + 1, sound->subsoundName(i), true, (i == selectedSubsound));
					}
				int result = menu.getNumItems();
				if (result != 0) {
					sound->useSubsound(result - 1);
					showSubsound();
					}
				}
			}
		
		else if (showing == showingVersion)
			showPath();
		else
			showVersion();
		}
	
	else if (clickedLabel == &infoLabel) {
		if (showingInfo == showingSoundInfo)
			showVoiceInfo();
		else
			showSoundInfo();
		}
}
	bool sw = false;
bool offloop[5] = { false,false, false, false, false };
void SFZeroEditor::timerCallback()
{ 
	/*	*/
	sprintf(lbt, "midiIn->::channel %i::note %i::bender %i::rateHz %i",
		audioProcessor.PitchBendBack
		, audioProcessor.gParas.mod.getTimerHostValue()
		, audioProcessor.readInt[0]
		, audioProcessor.readInt[2]


	);
	ReadOutLabel.setText(lbt, juce::dontSendNotification);

	audioProcessor.gParas.meterlevelUV.meterIn(audioProcessor.mPrevL);

	if (getProcessor()->pUpdate == true) {
		update();
		showTable();
	}
	
#ifdef JUCE_DEBUG
	getProcessor()->relayLogMessages();
#endif

	if (showing == showingProgress) {
		SFZeroAudioProcessor* processor = getProcessor();
		if (processor->loadProgress >= 1.0) {
			SFZSound* sound = processor->getSound();
			if (sound && sound->numSubsounds() > 1) {
				showSubsound();
				
			}
			else
		
				showPath();
			showSoundInfo();
			}
		}

	if (showingInfo == showingVoiceInfo)
		showVoiceInfo();

	if (audioProcessor.gParas.looper.Vmode()>0) {
		

		if (audioProcessor.gParas.looper.Vmode() == 1)
			audioProcessor.setloop1(audioProcessor.gParas.looper.loopOn1(), 1);
		if (audioProcessor.gParas.looper.Vmode() == 2)
			audioProcessor.setloop1(audioProcessor.gParas.looper.loopOn2(), 2);
		if (audioProcessor.gParas.looper.Vmode() == 3)
			audioProcessor.setloop1(audioProcessor.gParas.looper.loopOn3(), 3);
		
		sw = true;
	}

	if (audioProcessor.gParas.looper.Vmode() == 0 && sw == true)
	{
		audioProcessor.setloop1(offloop,0 );
		sw = false;
	}

	if (audioProcessor.gParas.mod.mDown == true) {
		if (audioProcessor.gParas.mod.getMode() == 0)
			audioProcessor.gParas.mod.serialStepps(audioProcessor.valueTreeState);
		else
			if (audioProcessor.gParas.mod.getMode() == 1)
				audioProcessor.timeX.setDivides(audioProcessor.gParas.mod.butNb,0 );
			else
				if (audioProcessor.gParas.mod.getMode() == 2)
					audioProcessor.gParas.mod.initCurve(audioProcessor.gParas.mod.butNbWv);
				else
					if (audioProcessor.gParas.mod.getMode() == 3) {
						audioProcessor.timeX.setTimes(audioProcessor.gParas.mod.getTimerHostValue());
						audioProcessor.timeX.division(audioProcessor.gParas.mod.getTimerHostValue());
					}
			else
				if (audioProcessor.gParas.mod.getMode() == 4)
					audioProcessor.timeX.setBpm(audioProcessor.gParas.mod.getTimerBpmvalue());
	}


	if (audioProcessor.PitchBendBack == true) {
		audioProcessor.gParas.PitchBendSlider.setValue(audioProcessor.parameters.mainPitchBendValue);
	
		audioProcessor.PitchBendBack = false;
	}

}

String SFZeroEditor::showTable()
{
	
	return String();
}


void SFZeroEditor::chooseFile()
{
	
	FileChooser chooser(
		"Select an SFZ file...",
		String(),
		"*.sfz;*.SFZ;*.sf2;*.SF2");
	if (chooser.browseForFileToOpen()) {
		
		File sfzFile(chooser.getResult());
		setFile(&sfzFile);
	}
}


void SFZeroEditor::setFile(File* newFile)
{
	SFZeroAudioProcessor* processor = getProcessor();
	processor->setSfzFileThreaded(newFile);

	updateFile(newFile);
	showProgress();
}


void SFZeroEditor::updateFile(File* file)
{
	fileLabel.setText(file->getFileName()+("----->cklick here load.sfz"), dontSendNotification);
	fileLabel.setColour(Label::textColourId, Colours::green);
	showPath();
}


void SFZeroEditor::showSoundInfo()
{
	SFZeroAudioProcessor* processor = getProcessor();
	SFZSound* sound = processor->getSound();
	if (sound) {
		infoLabel.setText("SFZ::Map_info", dontSendNotification);
		textEntryBox.setText(sound->getSampelsT() + sound->getErrorsString());
		showingInfo = showingSoundInfo;
	}
}


void SFZeroEditor::showVoiceInfo()
{
	SFZeroAudioProcessor* processor = getProcessor();
	infoLabel.setText("Midi_Voice_info", dontSendNotification);
	//infoLabel.setText(processor->voiceInfoString(), dontSendNotification);
	textEntryBox.setText(processor->voiceInfoString());
	showingInfo = showingVoiceInfo;
}


void SFZeroEditor::showVersion()
{
	struct tm tm;
	//strptime(__DATE__, "%b %d %Y", &tm);
	char str[64];
	sprintf(str, "SFZero beta %d.%d.%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
	pathLabel.setText(str, dontSendNotification);
	pathLabel.setColour(Label::textColourId, Colours::grey);
	hideProgress();
	showing = showingVersion;
}


void SFZeroEditor::showPath()
{
	SFZeroAudioProcessor* processor = getProcessor();
	File file = processor->getSfzFile();
	pathLabel.setText(
		file.getParentDirectory().getFullPathName(), dontSendNotification);
	pathLabel.setColour(Label::textColourId, Colours::rebeccapurple);
	hideProgress();
	showing = showingPath;
}


void SFZeroEditor::showSubsound()
{
	SFZeroAudioProcessor* processor = getProcessor();
	SFZSound* sound = processor->getSound();
	if (sound == NULL)
		return;

	pathLabel.setText(
		sound->subsoundName(sound->selectedSubsound()), dontSendNotification);
	pathLabel.setColour(Label::textColourId, Colours::white);
	hideProgress();
	showing = showingSubsound;
}


void SFZeroEditor::showProgress()
{
	SFZeroAudioProcessor* processor = getProcessor();
	pathLabel.setVisible(false);
	infoLabel.setVisible(false);
	progressBar = new ProgressBar(processor->loadProgress);
	addAndMakeVisible(progressBar);
	int marginedWidth = getWidth() - 2 * hMargin;
	progressBar->setBounds(
		hMargin, vMargin + labelHeight, marginedWidth, progressBarHeight);
	showing = showingProgress;
}


void SFZeroEditor::hideProgress()
{
	if (progressBar == NULL)
		return;

	removeChildComponent(progressBar);
	delete progressBar;
	progressBar = NULL;

	pathLabel.setVisible(true);
	infoLabel.setVisible(true);
}



