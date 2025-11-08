#include "PlayerAudio.h"

PlayerAudio::PlayerAudio()
{
    formatManager.registerBasicFormats();
	resamplerSource = std::make_unique<juce::ResamplingAudioSource>(&transportSource, false, 2);
}
PlayerAudio::~PlayerAudio()
{

}
void PlayerAudio::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    transportSource.prepareToPlay(samplesPerBlockExpected, sampleRate);
    if (resamplerSource != nullptr)
        resamplerSource->prepareToPlay(samplesPerBlockExpected, sampleRate);
}
void PlayerAudio::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    if (pendingLoop && !transportSource.isLooping())
    {
        const double pos = transportSource.getCurrentPosition();
        const double len = transportSource.getLengthInSeconds();
        const double eps = 0.05;

        if (len > 0.0 && (pos >= len - eps || !transportSource.isPlaying()))
        {
            transportSource.setLooping(true);
            transportSource.setPosition(0.0);
            transportSource.start();

            pendingLoop = false;
        }
    }
    // Handle A-B loop
    if (abLoopEnabled)
    {
        const double current = transportSource.getCurrentPosition();
        if (pointB > pointA && current >= pointB)
            transportSource.setPosition(pointA);
    }

    if (resamplerSource != nullptr)
    {
        resamplerSource->getNextAudioBlock(bufferToFill);
    }
    else
    {
        transportSource.getNextAudioBlock(bufferToFill);
    }
}

void PlayerAudio::releaseResources()
{
    if (resamplerSource != nullptr)
        resamplerSource->releaseResources();
    transportSource.releaseResources();
}

bool PlayerAudio::loadFile(const juce::File& file)
{
    if (file.existsAsFile())
    {
        if (auto* reader = formatManager.createReaderFor(file))
        {
            // 🔑 Disconnect old source first
            transportSource.stop();
            transportSource.setSource(nullptr);
            readerSource.reset();

            // Create new reader source
            readerSource = std::make_unique<juce::AudioFormatReaderSource>(reader, true);

            // Attach safely
            transportSource.setSource(readerSource.get(),
                0,
                nullptr,
                reader->sampleRate);
            // Update metadata
            currentFileName = file.getFileName();
            currentTitle = reader->metadataValues.getValue("title", juce::String());
            currentArtist = reader->metadataValues.getValue("artist", juce::String());
            // Reset A-B loop range to full length
            pointA = 0.0;
            pointB = readerSource->getTotalLength() / reader->sampleRate;
            transportSource.start();
        }
    }
    return true;
}

void PlayerAudio::play()
{
    transportSource.start();
}
void PlayerAudio::pause()
{
    transportSource.stop();
}

void PlayerAudio::loop()
{
    pendingLoop = !pendingLoop;
}




void PlayerAudio::backtostart()
{
    transportSource.setPosition(0.0);
    transportSource.start();
}
void PlayerAudio::gotoend()
{
    transportSource.setPosition(transportSource.getLengthInSeconds());
}
void PlayerAudio::mute()
{

}
void PlayerAudio::stop()
{
    transportSource.stop();
    setPosition(0.0);
}
void PlayerAudio::setGain(float gain)
{
    transportSource.setGain(gain);
}
void PlayerAudio::setPosition(double pos)
{
    transportSource.setPosition(pos);
}
double PlayerAudio::getPosition() const
{
    return transportSource.getCurrentPosition();
}
double PlayerAudio::getLength() const
{
    return transportSource.getLengthInSeconds();
}

// Metadata accessors
juce::String PlayerAudio::getTitle() const { return currentTitle; }
juce::String PlayerAudio::getArtist() const { return currentArtist; }
juce::String PlayerAudio::getFileName() const { return currentFileName; }

// Speed control
void PlayerAudio::setSpeed(double ratio)
{
    if (ratio <= 0.0) ratio = 0.01;
    currentSpeedRatio = ratio;
    if (resamplerSource != nullptr)
        resamplerSource->setResamplingRatio(currentSpeedRatio);
}

double PlayerAudio::getSpeed() const
{
    return currentSpeedRatio;
}

// A-B loop
void PlayerAudio::setLoopPoints(double aSeconds, double bSeconds)
{
    pointA = juce::jmax(0.0, aSeconds);
    pointB = juce::jmax(pointA, bSeconds);
}

void PlayerAudio::enableABLoop(bool shouldEnable)
{
    abLoopEnabled = shouldEnable;
}

bool PlayerAudio::isABLoopEnabled() const
{
    return abLoopEnabled;
}

double PlayerAudio::getPointA() const { return pointA; }
double PlayerAudio::getPointB() const { return pointB; }
