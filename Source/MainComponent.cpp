#include "MainComponent.h"

MainComponent::MainComponent()
{
    addAndMakeVisible(player1);
    addAndMakeVisible(player2);

    // Mixer UI
    addAndMakeVisible(mixToggle);
    addAndMakeVisible(activeOutputBox);
    activeOutputBox.addItem("Player 1", 1);
    activeOutputBox.addItem("Player 2", 2);
    activeOutputBox.setSelectedId(1);

    setSize(900, 700);
    setAudioChannels(0, 2);
}

MainComponent::~MainComponent()
{
    shutdownAudio();
}

void MainComponent::prepareToPlay(int samplesPerBlockExpected, double sampleRate)
{
    player1.prepareToPlay(samplesPerBlockExpected, sampleRate);
    player2.prepareToPlay(samplesPerBlockExpected, sampleRate);
    tempMixBuffer.setSize(2, samplesPerBlockExpected);
}

void MainComponent::getNextAudioBlock(const juce::AudioSourceChannelInfo& bufferToFill)
{
    auto* outBuf = bufferToFill.buffer;
    if (outBuf == nullptr) return;
    outBuf->clear(bufferToFill.startSample, bufferToFill.numSamples);

    const bool mixing = mixToggle.getToggleState();
    const int activeId = activeOutputBox.getSelectedId();

    if (mixing)
    {
        player1.getNextAudioBlock(bufferToFill);

        tempMixBuffer.setSize(outBuf->getNumChannels(), bufferToFill.numSamples, false, false, true);
        tempMixBuffer.clear();
        juce::AudioSourceChannelInfo tempInfo(&tempMixBuffer, 0, bufferToFill.numSamples);
        player2.getNextAudioBlock(tempInfo);
        for (int ch = 0; ch < outBuf->getNumChannels(); ++ch)
            outBuf->addFrom(ch, bufferToFill.startSample, tempMixBuffer, ch, 0, bufferToFill.numSamples, 1.0f);
    }
    else
    {
        if (activeId == 1)
        {
            player1.getNextAudioBlock(bufferToFill);
        }
        else
        {
            player2.getNextAudioBlock(bufferToFill);
        }
    }
}

void MainComponent::releaseResources()
{
    player1.releaseResources();
    player2.releaseResources();
}

void MainComponent::resized()
{
    auto area = getLocalBounds();
    auto controls = area.removeFromBottom(40).reduced(10);

    mixToggle.setBounds(controls.removeFromLeft(80));
    activeOutputBox.setBounds(controls.removeFromLeft(120));

    auto half = area.getHeight() / 2;
    player1.setBounds(area.removeFromTop(half).reduced(10));
    player2.setBounds(area.reduced(10));
}