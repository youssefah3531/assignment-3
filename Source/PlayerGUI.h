#pragma once						// PlayerGUI.h
#include <JuceHeader.h>
#include "PlayerAudio.h"

class PlayerGUI : public juce::Component,
    public juce::Button::Listener,
    public juce::Slider::Listener,
    public juce::Timer
{
public:
    PlayerGUI();
    ~PlayerGUI() override;
    void paint(juce::Graphics& g) override;

    void resized() override;
    bool loadFile(const juce::File& file);
    void stop();
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition() const;
    double getLength() const;
    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

private:
    PlayerAudio playerAudio;

    // GUI elements
    juce::TextButton loadButton{ "Load File" };
    juce::TextButton restartButton{ "Restart" };
    juce::TextButton LoopButton{ "loop" };
    juce::TextButton BacktostartButton{ "Backtostart" };
    juce::TextButton GotoendButton{ "Gotoend" };
    juce::TextButton PlayButton{ "play" };
    juce::TextButton PauseButton{ "pause" };
    juce::TextButton MuteButton{ "mute" };
    juce::TextButton stopButton{ "Stop" };
    juce::TextButton setAButton{ "Set A" };
    juce::TextButton setBButton{ "Set B" };
    juce::TextButton abLoopToggleButton{ "AB Loop" };
    juce::Slider volumeSlider;
	juce::Slider positionSlider;
    juce::Slider speedSlider;
    juce::Label titleLabel;
    juce::Label artistLabel;
    juce::Label timeLabel;
    juce::ComboBox playlistBox;
    double progressValue = 0.0;
    std::unique_ptr<juce::ProgressBar> progressBar;
    std::unique_ptr<juce::FileChooser> fileChooser;
    bool isMutedState = false;
    float prevVolume = 0.5f;
    juce::StringArray playlistPaths;

    // Waveform rendering
    juce::AudioFormatManager thumbFormatManager;
    juce::AudioThumbnailCache thumbCache { 100 };
    juce::AudioThumbnail thumbnail { 512, thumbFormatManager, thumbCache };
    juce::Rectangle<int> waveformArea;

    // Event handlers
    void buttonClicked(juce::Button* button) override;
    void sliderValueChanged(juce::Slider* slider) override;
    void timerCallback() override;

    void refreshMetadataLabels();
    void refreshTimeAndProgress();

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerGUI)
};
