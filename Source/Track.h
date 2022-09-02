/*
  ==============================================================================

	Track.h
	Created: 29 Aug 2022 3:01:07am
	Author:  Zty

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

/* class to handle the track object */

class Track
{
public:
	Track(juce::File _file);
	juce::File file;
	juce::URL URL;
	juce::String title;
	juce::String length;
	juce::String fileExtension;

	// enable comparison search operations
	bool operator==(const juce::String& other) const;
};