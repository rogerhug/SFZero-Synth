#ifndef __PLUGINEDITOR_H_A8E24640__
#define __PLUGINEDITOR_H_A8E24640__

#include "../JuceLibraryCode/JuceHeader.h"
#include "SFZeroAudioProcessor.h"
#include "ClickableLabel.h"
#include"PluginParameters.h"


#include"../module/SFZero/SFZero/SFZSynth.h"




class SFZeroEditor  :
	public AudioProcessorEditor, public Timer,
	public ClickableLabel::ClickListener,
	
	public FilenameComponentListener

{
	public:
		SFZeroEditor(SFZeroAudioProcessor& ownerFilter);
		~SFZeroEditor();

		
		void	paint(Graphics& g);
		void	resized();
		void	labelClicked(Label* clickedLabel);
		void	timerCallback()override;


		void filenameComponentChanged(FilenameComponent* fileComponentThatHasChanged) override
		{
			auto* f = fileComp.get();
			File sfzFile(f->getLocationToBrowse());
			setFile(&sfzFile);
				
			
		}
		void update()
		{
			SFZeroAudioProcessor* processor = getProcessor();
			File file = processor->getSfzFile();
			
			SfZProgrammLabel.setText(file.getParentDirectory().getFullPathName(), juce::dontSendNotification);
			getProcessor()->pUpdate = false;
			updateFile(&file);
			showSoundInfo();
		}
		String showTable();
	protected:
		// pathLabel options.
		enum {
			showingVersion,
			showingPath,
			showingProgress,
			showingSubsound,
			};

		// infoLabel options.
		enum {
			showingSoundInfo,
			showingVoiceInfo,
			};

		ClickableLabel	fileLabel;
		ClickableLabel	pathLabel;
		ClickableLabel 	infoLabel;
		int	showing, showingInfo;
		MidiKeyboardComponent	midiKeyboard;
		MidiKeyboardStateListener *midi1;
	
		ProgressBar*	progressBar;

		
		
	
		SFZeroAudioProcessor* getProcessor() const {
			return static_cast<SFZeroAudioProcessor*> (getAudioProcessor());
			return static_cast<SFZeroAudioProcessor*> (getProcessor());
			}

	

		void	chooseFile();
		void	setFile(File* newFile);
		void	updateFile(File* file);
		void	showSoundInfo();
		void	showVoiceInfo();
		void	showVersion();
		void	showPath();
		void	showProgress();
		void	hideProgress();
		void	showSubsound();

	
private:

	std::unique_ptr<juce::FilenameComponent> fileComp;
	PluginParameters& parameters;
	ResizableCornerComponent* resizer;


	Label SfZProgrammLabel;
	Label ReadOutLabel;
	 TextEditor textEntryBox;
	 TextEditor textEntryBoxErrors;
	TableListBox table;
	char lbt[200];
	SFZeroAudioProcessor& audioProcessor;
	
	TextButton undoButton, redoButton;
	
	
	};


#endif  // __PLUGINEDITOR_H_A8E24640__
