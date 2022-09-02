/* 
	CM2005 - Final Project
	github.com/crediteur

	If encountering any difficulties enable in Projucer options:
	- using namespace juce; enabled
	- JUCE_MODAL_LOOPS_PERMITTED=1 under preprocessor definitions
 */

#pragma once

#include <JuceHeader.h>
#include "DJAudioPlayer.h"
#include "DeckGUI.h"
#include "PlaylistComponent.h"

//==============================================================================
/* main class container head for other components */

class MainComponent : public juce::AudioAppComponent
{
public:
	MainComponent();
	~MainComponent() override;

	// mandatory component virtual functions
	void prepareToPlay(int samplesPerBlockExpected, double sampleRate) override;
	void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill) override;
	void releaseResources() override;

	void paint(juce::Graphics& g) override;
	void resized() override;

private:
	//==============================================================================
	juce::MixerAudioSource mixerSource;

	// initialize audio and gui for set 1 & 2
	DJAudioPlayer player1{ formatManager };
	DJAudioPlayer player2{ formatManager };
	DeckGUI deckGUI1{ &player1, formatManager, thumbCache };
	DeckGUI deckGUI2{ &player2, formatManager, thumbCache };

	// draw waveform
	juce::AudioFormatManager formatManager;
	juce::AudioThumbnailCache thumbCache{ 100 };

	PlaylistComponent playlistComponent{ &deckGUI1, &deckGUI2 };

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
