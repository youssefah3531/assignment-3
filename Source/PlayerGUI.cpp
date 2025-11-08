#include "PlayerGUI.h"
#include <cmath>
PlayerGUI::PlayerGUI()
{
    // Add buttons
    for (auto* btn : { &loadButton, &restartButton , &stopButton,&PlayButton,&LoopButton,&PauseButton,&MuteButton,&BacktostartButton,&GotoendButton, &setAButton, &setBButton, &abLoopToggleButton })
    {
        btn->addListener(this);
        addAndMakeVisible(btn);
    }

    // Volume slider
    volumeSlider.setRange(0.0, 1.0, 0.01);
    volumeSlider.setValue(0.5);
    volumeSlider.addListener(this);
    addAndMakeVisible(volumeSlider);

	// Position slider
	positionSlider.setRange(0.0, 1.0, 0.001);
	positionSlider.setValue(0.0);
	positionSlider.addListener(this);
	addAndMakeVisible(positionSlider);

    // Speed slider (0.5x - 2.0x)
    speedSlider.setRange(0.5, 2.0, 0.01);
    speedSlider.setValue(1.0);
    speedSlider.addListener(this);
    addAndMakeVisible(speedSlider);

    // Metadata labels
    titleLabel.setText("Title:", juce::dontSendNotification);
    artistLabel.setText("Artist:", juce::dontSendNotification);
    timeLabel.setText("00:00 / 00:00", juce::dontSendNotification);
    addAndMakeVisible(titleLabel);
    addAndMakeVisible(artistLabel);
    addAndMakeVisible(timeLabel);

    // Playlist
    addAndMakeVisible(playlistBox);
    playlistBox.onChange = [this]()
    {
        const int idx = playlistBox.getSelectedItemIndex();
        if (idx >= 0)
        {
            if (idx < playlistPaths.size())
            {
                juce::File file(playlistPaths[idx]);
                if (file.existsAsFile())
                {
                    playerAudio.loadFile(file);
                    thumbnail.setSource(new juce::FileInputSource(file));
                    refreshMetadataLabels();
                    positionSlider.setValue(0.0, juce::dontSendNotification);
                    speedSlider.setValue(1.0, juce::dontSendNotification);
                }
            }
        }
    };

    // Progress bar
    progressBar = std::make_unique<juce::ProgressBar>(progressValue);
    addAndMakeVisible(*progressBar);

    // Start timer to refresh UI
    startTimerHz(30);

    // Waveform formats
    thumbFormatManager.registerBasicFormats();
}

PlayerGUI::~PlayerGUI()
{
}
void PlayerGUI::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    playerAudio.prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void PlayerGUI::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    playerAudio.getNextAudioBlock(bufferToFill);
}
void PlayerGUI::releaseResources()
{
    playerAudio.releaseResources();
}
void PlayerGUI::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::darkgrey);

    // Draw waveform
    if (waveformArea.getHeight() > 0)
    {
        g.setColour(juce::Colours::black.withAlpha(0.5f));
        g.fillRoundedRectangle(waveformArea.toFloat(), 4.0f);
        g.setColour(juce::Colours::lightgrey);
        g.drawRoundedRectangle(waveformArea.toFloat(), 4.0f, 1.0f);

        if (thumbnail.getTotalLength() > 0.0)
        {
            g.setColour(juce::Colours::aqua);
            thumbnail.drawChannels(g, waveformArea, 0.0, thumbnail.getTotalLength(), 1.0f);

            const double len = playerAudio.getLength();
            const double pos = playerAudio.getPosition();
            if (len > 0.0)
            {
                const float x = (float)(waveformArea.getX() + (waveformArea.getWidth() * (pos / len)));
                g.setColour(juce::Colours::red);
                g.drawLine(x, (float)waveformArea.getY(), x, (float)waveformArea.getBottom(), 2.0f);
            }
        }
        else
        {
            g.setColour(juce::Colours::grey);
            g.drawFittedText("Load a file to view waveform", waveformArea, juce::Justification::centred, 1);
        }
    }
}
void PlayerGUI::resized()
{
    int y = 20;
    loadButton.setBounds(20, y, 100, 30);
    restartButton.setBounds(130, y, 70, 30);
    stopButton.setBounds(205, y, 70, 30);
    PlayButton.setBounds(280, y, 60, 30);
    PauseButton.setBounds(345, y, 60, 30);
    MuteButton.setBounds(410, y, 60, 30);
    LoopButton.setBounds(475, y, 60, 30);
    BacktostartButton.setBounds(540, y, 90, 30);
    GotoendButton.setBounds(635, y, 80, 30);
    setAButton.setBounds(720, y, 60, 30);
    setBButton.setBounds(785, y, 60, 30);
    abLoopToggleButton.setBounds(850, y, 80, 30);

    y += 40;
    playlistBox.setBounds(20, y, 300, 24);
    titleLabel.setBounds(330, y, getWidth() - 350, 24);
    y += 28;
    artistLabel.setBounds(330, y, getWidth() - 350, 24);

    y += 32;
	positionSlider.setBounds(20, y, getWidth() - 40, 24);
    y += 28;
    // Waveform area
    waveformArea = juce::Rectangle<int>(20, y, getWidth() - 40, 60);
    y += 68;

    timeLabel.setBounds(20, y, 200, 20);
    progressBar->setBounds(230, y, getWidth() - 250, 20);

    y += 28;
    volumeSlider.setBounds(20, y, getWidth() - 40, 24);
    y += 28;
    speedSlider.setBounds(20, y, getWidth() - 40, 24);
}
void PlayerGUI::buttonClicked(juce::Button* button)
{
    if (button == &loadButton)
    {
        fileChooser = std::make_unique<juce::FileChooser>(
            "Select an audio file...",
            juce::File{},
            "*.wav;*.mp3");

        fileChooser->launchAsync(
            juce::FileBrowserComponent::openMode | juce::FileBrowserComponent::canSelectFiles | juce::FileBrowserComponent::canSelectMultipleItems,
            [this](const juce::FileChooser& fc)
            {
                auto results = fc.getResults();
                if (results.isEmpty()) return;
                playlistBox.clear(juce::dontSendNotification);
                playlistPaths.clear();
                int i = 1;
                for (auto& file : results)
                {
                    playlistBox.addItem(file.getFileName(), i);
                    playlistPaths.add(file.getFullPathName());
                    ++i;
                }
                // Auto-load first
                auto first = results.getReference(0);
                if (first.existsAsFile())
                {
                    playerAudio.loadFile(first);
                    thumbnail.setSource(new juce::FileInputSource(first));
                    refreshMetadataLabels();
                    playlistBox.setSelectedItemIndex(0, juce::sendNotification);
                    positionSlider.setValue(0.0, juce::dontSendNotification);
                    speedSlider.setValue(1.0, juce::dontSendNotification);
                }
            });
    }
    if (button == &PlayButton)
    {
        playerAudio.play();
    }
    if (button == &PauseButton)
    {
        playerAudio.pause();
    }
    if (button == &LoopButton)
    {
		playerAudio.loop();
    }
    if (button == &MuteButton)
    {
        if (!isMutedState && volumeSlider.getValue() > 0.0)
            prevVolume = (float)volumeSlider.getValue();
        isMutedState = !isMutedState;
        volumeSlider.setValue(isMutedState ? 0.0 : prevVolume);
    }
    if (button == &BacktostartButton)
    {
        playerAudio.backtostart();
    }
    if (button == &GotoendButton)
    {
        playerAudio.gotoend();
    }
    if (button == &restartButton)
    {
        playerAudio.setPosition(0.0);
        playerAudio.play();
    }

    if (button == &stopButton)
    {
        playerAudio.stop();
        playerAudio.setPosition(0.0);
    }

    if (button == &setAButton)
    {
        playerAudio.setLoopPoints(playerAudio.getPosition(), playerAudio.getPointB());
    }
    if (button == &setBButton)
    {
        playerAudio.setLoopPoints(playerAudio.getPointA(), playerAudio.getPosition());
    }
    if (button == &abLoopToggleButton)
    {
        playerAudio.enableABLoop(!playerAudio.isABLoopEnabled());
    }

}
void PlayerGUI::sliderValueChanged(juce::Slider* slider)
{
    if (slider == &volumeSlider)
        playerAudio.setGain((float)slider->getValue());
	if (slider == &positionSlider)
		playerAudio.setPosition(slider->getValue() * playerAudio.getLength());
    if (slider == &speedSlider)
        playerAudio.setSpeed(speedSlider.getValue());
}

void PlayerGUI::timerCallback()
{
    refreshTimeAndProgress();
    repaint(waveformArea);
}

static juce::String formatTime(double seconds)
{
    if (seconds < 0.0) seconds = 0.0;
    int total = (int)std::round(seconds);
    int mins = total / 60;
    int secs = total % 60;
    return juce::String::formatted("%02d:%02d", mins, secs);
}

void PlayerGUI::refreshMetadataLabels()
{
    auto title = playerAudio.getTitle();
    auto artist = playerAudio.getArtist();
    auto fileName = playerAudio.getFileName();
    if (title.isEmpty()) title = fileName;
    if (artist.isEmpty()) artist = juce::String();
    titleLabel.setText("Title: " + title, juce::dontSendNotification);
    artistLabel.setText("Artist: " + artist, juce::dontSendNotification);
}

void PlayerGUI::refreshTimeAndProgress()
{
    const double len = playerAudio.getLength();
    const double pos = playerAudio.getPosition();
    if (len > 0.0)
    {
        positionSlider.setValue(pos / len, juce::dontSendNotification);
        progressValue = pos / len;
        timeLabel.setText(formatTime(pos) + " / " + formatTime(len), juce::dontSendNotification);
    }
}

// Public wrappers declared in header
bool PlayerGUI::loadFile(const juce::File& file)
{
    const bool ok = playerAudio.loadFile(file);
    if (ok)
    {
        refreshMetadataLabels();
        positionSlider.setValue(0.0, juce::dontSendNotification);
        speedSlider.setValue(1.0, juce::dontSendNotification);
        thumbnail.setSource(new juce::FileInputSource(file));
    }
    return ok;
}

void PlayerGUI::stop()
{
    playerAudio.stop();
}

void PlayerGUI::setGain(float gain)
{
    playerAudio.setGain(gain);
}

void PlayerGUI::setPosition(double pos)
{
    playerAudio.setPosition(pos);
}

double PlayerGUI::getPosition() const
{
    return playerAudio.getPosition();
}

double PlayerGUI::getLength() const
{
    return playerAudio.getLength();
}