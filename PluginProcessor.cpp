/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include <iostream>
#include <vector>

using namespace std;


//==============================================================================
WaylochorderAudioProcessor::WaylochorderAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

WaylochorderAudioProcessor::~WaylochorderAudioProcessor()
{
}

// global variables for plugin








//==============================================================================
const String WaylochorderAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool WaylochorderAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool WaylochorderAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool WaylochorderAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double WaylochorderAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int WaylochorderAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int WaylochorderAudioProcessor::getCurrentProgram()
{
    return 0;
}

void WaylochorderAudioProcessor::setCurrentProgram (int index)
{
}

const String WaylochorderAudioProcessor::getProgramName (int index)
{
    return {};
}

void WaylochorderAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void WaylochorderAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void WaylochorderAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool WaylochorderAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif
void WaylochorderAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)

{
    
    for (int i = getNumInputChannels(); i < getNumOutputChannels(); ++i)
    {buffer.clear (i, 0, buffer.getNumSamples());}
    
    MidiBuffer processedMidi;
    int time;
    MidiMessage m;
    int chordLength = 3;
    for(MidiBuffer::Iterator i (midiMessages); i.getNextEvent(m, time);)
    {
        if(m.isNoteOn()) {
    for(int i = 0;i<chordLength;i++) {

        int interval = 60 + i*12;
        MidiMessage n = MidiMessage::noteOn(m.getChannel(), interval, m.getFloatVelocity());
        processedMidi.addEvent(n, time);
    }
        }
        else if(m.isNoteOff())
        {
            MidiMessage n = MidiMessage::allNotesOff(m.getChannel());
            processedMidi.addEvent(n, time);
        }
    }
    midiMessages.swapWith(processedMidi);
    

}

    

//==============================================================================
bool WaylochorderAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* WaylochorderAudioProcessor::createEditor()
{
    return new WaylochorderAudioProcessorEditor (*this);
}

//==============================================================================
void WaylochorderAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void WaylochorderAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new WaylochorderAudioProcessor();
}

