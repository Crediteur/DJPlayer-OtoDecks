/*
  ==============================================================================

	WaveformDisplay.h
	Created: 21 Aug 2022 4:43:38pm
	Author:  Zty

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/* class that handles drawing and callback of the wave graphic */

class WaveformDisplay : public juce::Component,
	public juce::ChangeListener
{
public:
	WaveformDisplay(juce::AudioFormatManager& formatManagerToUse,
					juce::AudioThumbnailCache& cacheToUse);
	~WaveformDisplay() override;

	void paint(juce::Graphics&) override;
	void resized() override;

	void loadURL(juce::URL audioURL);

	void changeListenerCallback(juce::ChangeBroadcaster* source) override;

	void setPositionRelative(double pos);

private:
	juce::AudioThumbnail audioThumb;
	bool fileLoaded;
	double position;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(WaveformDisplay)
};
