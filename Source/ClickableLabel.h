/*
  ==============================================================================

    ClickableLabel.h
    Created: 15 Apr 2012 1:59:47pm
    Author:  Steve Folta

  ==============================================================================
*/

#ifndef __CLICKABLELABEL_H_F4AC0009__
#define __CLICKABLELABEL_H_F4AC0009__

#include "../JuceLibraryCode/JuceHeader.h"

class ClickableLabel : public Label {
	public:
		ClickableLabel(
			const String& componentName = "-",
			const String& labelText = "-");

		class JUCE_API ClickListener {
			public:
				virtual ~ClickListener() {}

				virtual void	labelClicked(Label* clickedLabel) = 0;
			};

		void	addClickListener(ClickListener* listener);
		void	removeClickListener(ClickListener* listener);

	protected:
		ListenerList<ClickListener> clickListeners;

		void	mouseUp(const MouseEvent& e);
	};




#endif  // __CLICKABLELABEL_H_F4AC0009__
