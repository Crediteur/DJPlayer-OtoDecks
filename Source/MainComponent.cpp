#include "MainComponent.h"
using namespace juce;

//==============================================================================
/* main class container head for other components */

MainComponent::MainComponent()
{
    // Make sure you set the size of the component after
    // you add any child components.
    setSize (900, 900);

    // Some platforms require permissions to open input channels so request that here
    if (RuntimePermissions::isRequired (RuntimePermissions::recordAudio)
        && ! RuntimePermissions::isGranted (RuntimePermissions::recordAudio))
    {
        RuntimePermissions::request (RuntimePermissions::recordAudio,
                                           [&] (bool granted) { setAudioChannels (granted ? 2 : 0, 2); });
    }
    else
    {
        // Specify the number of input and output channels that we want to open
        setAudioChannels (2, 2);
    }

    addAndMakeVisible(deckGUI1);
    addAndMakeVisible(deckGUI2);

    deckGUI1.deckTitle.setText("DeckGUI 1", dontSendNotification);
    deckGUI2.deckTitle.setText("DeckGUI 2", dontSendNotification);
    
    addAndMakeVisible(playlistComponent);

    // register audio file formats
    formatManager.registerBasicFormats();

}

MainComponent::~MainComponent()
{
    // This shuts down the audio device and clears the audio source.
    shutdownAudio();
}

//==============================================================================
/* tells the source to prepare for playing */
void MainComponent::prepareToPlay (int samplesPerBlockExpected, double sampleRate)
{
    // call players in mixed audio channel
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);

    mixerSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    mixerSource.addInputSource(&player1, false);
    mixerSource.addInputSource(&player2, false);
}

/* called repeatedly to fetch subsequent blocks of audio data */
void MainComponent::getNextAudioBlock (const AudioSourceChannelInfo& bufferToFill)
{
    mixerSource.getNextAudioBlock(bufferToFill);
}

/* allows the source to release anything it no longer needs after playback has stopped */
void MainComponent::releaseResources()
{
    player1.releaseResources();
    player2.releaseResources();
    mixerSource.releaseResources();
}

//==============================================================================
/* components override this method to draw their content */
void MainComponent::paint (Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));
}

/* called when this component's size has been changed ie. window resized */
void MainComponent::resized()
{
    //set deckGUI 1 & 2 to half size of main component
    //                              x, y,          width,      height
    deckGUI1.setBounds(             0, 0, getWidth() / 2, getHeight() * 3/5);
    deckGUI2.setBounds(getWidth() / 2, 0, getWidth() / 2, getHeight() * 3/5);

    playlistComponent.setBounds(0, getHeight() * 3/5, getWidth(), getHeight() * 2/5);

    DBG("MainComponent::resized");
}

