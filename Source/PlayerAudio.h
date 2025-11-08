#pragma once							// PlayerAudio.h
#include <JuceHeader.h>

class PlayerAudio
{
public:
    PlayerAudio();
    ~PlayerAudio();

    void prepareToPlay(int samplesPerBlockExpected, double sampleRate);
    void getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill);
    void releaseResources();

    bool loadFile(const juce::File& file);
    void play();
    void pause();
    void loop();
    void backtostart();
    void gotoend();
    void mute();
    void stop();
    void setGain(float gain);
    void setPosition(double pos);
    double getPosition() const;
    double getLength() const;

    // Metadata
    juce::String getTitle() const;
    juce::String getArtist() const;
    juce::String getFileName() const;

    // Speed control (1.0 = normal)
    void setSpeed(double ratio);
    double getSpeed() const;

    // A-B loop
    void setLoopPoints(double aSeconds, double bSeconds);
    void enableABLoop(bool shouldEnable);
    bool isABLoopEnabled() const;
    double getPointA() const;
    double getPointB() const;

private:
    juce::AudioFormatManager formatManager;
    bool pendingLoop = false;
    std::unique_ptr<juce::AudioFormatReaderSource> readerSource;
    juce::AudioTransportSource transportSource;

    // Speed control
    std::unique_ptr<juce::ResamplingAudioSource> resamplerSource;
    double currentSpeedRatio = 1.0;

    // Metadata / file info
    juce::String currentTitle;
    juce::String currentArtist;
    juce::String currentFileName;

    // A-B loop
    bool abLoopEnabled = false;
    double pointA = 0.0;
    double pointB = 0.0;

    // JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(PlayerAudio)
};