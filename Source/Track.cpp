/*
  ==============================================================================

	Track.cpp
	Created: 29 Aug 2022 3:01:07am
	Author:  Zty

  ==============================================================================
*/

#include "Track.h"
#include <filesystem>
using namespace juce;

/* class to handle the track object */
//initalize file type, title, and file path on object creation

Track::Track(File _file) :
	file{ _file },
	URL{ juce::URL{ _file } },
	title{ _file.getFileNameWithoutExtension().trim() },
	fileExtension{_file.getFileExtension()}

{
	DBG("Track::Track: Created new track: " << title << " from subpath: " << URL.getSubPath());
}

bool Track::operator==(const juce::String& track) const
{
	return title == track;
}