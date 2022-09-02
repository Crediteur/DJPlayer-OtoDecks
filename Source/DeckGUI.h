/*
  ==============================================================================

	DeckGUI.h
	Created: 17 Aug 2022 2:45:40am
	Author:  Zty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "WaveformDisplay.h"
#include "Customize.h"

//==============================================================================
/* class that handles main GUI components of the DJplayer, mainly buttons and sliders */

class DeckGUI : public juce::Component,
	public juce::Button::Listener,
	public juce::Slider::Listener,
	public juce::FileDragAndDropTarget,
	public juce::Timer
{
public:
	DeckGUI(DJAudioPlayer* player,      // listen to audio file
	juce::AudioFormatManager& formatManagerToUse,
	juce::AudioThumbnailCache& cacheToUse); // draw waveform
	~DeckGUI() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	// implement Button::Listener
	void buttonClicked(juce::Button* button) override;

	// implement Slider::Listener
	void sliderValueChanged(juce::Slider* slider) override;

	// implement FileDragAndDropTarget
	bool isInterestedInFileDrag(const juce::StringArray& files) override;
	void filesDropped(const juce::StringArray& files, int x, int y) override;

	// implement Timer
	void timerCallback() override;

	// functions to toggle and update button attributes
	void togglePlayButton();
	void toggleLoopButton();

	juce::Label deckTitle;
	DJAudioPlayer* player;
	WaveformDisplay waveformDisplay;

private:
	Customize customize { this };
	
	juce::TextButton playButton;
	juce::TextButton loopButton;
	juce::TextButton loadButton;
	
	juce::FileChooser fChooser{ "Select a file..." };

	juce::Slider volSlider;
	juce::Slider speedSlider;
	juce::Slider freqSlider;
	juce::Slider posSlider;
	juce::Label volLabel;
	juce::Label speedLabel;
	juce::Label freqLabel;
	juce::Label posLabel;

	juce::Slider highSlider;
	juce::Slider midSlider;
	juce::Slider lowSlider;
	juce::Label highLabel;
	juce::Label midLabel;
	juce::Label lowLabel;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(DeckGUI)
};
