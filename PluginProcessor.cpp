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

int playing[127]; // array to hold notes playing
int numChords; // num of chords in chord sequence
int numNotes ; // number of notes in a chord
int note; // a midi note value
int chordsPosition = 0; // pointer to postion in chord array
vector<int> chord;
// initialize the chord array to 3 chords
vector< vector<int> > chords { { 60, 67 , 72 },
                                { 72 , 79 , 84 },
                                { 77, 84, 89 } };






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
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    MidiMessage m; // the current MIDI message in the for loop
    //int NoteNumberWaylo ;
    
    /* iterate through the input buffer, process our MIDI, add it to the output buffer
     for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
     {
     
     if (m.isNoteOn())
     {
     m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber()+1, m.getVelocity());
     }
     processedMidi.addEvent (m, time);
     if (m.isNoteOff())
     {
     m = MidiMessage::noteOn(m.getChannel(), m.getNoteNumber()+1, m.getVelocity());
     }
     processedMidi.addEvent (m, time);
     
     }
     */
    {
        buffer.clear();
        
        
        MidiBuffer processedMidi;
        int time;
        MidiMessage m;
        
        for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
        {
            if (m.isNoteOn() && m.getNoteNumber() < 58 ) // reset the array position and play first chord
                
            {
                chordsPosition = 0;
                // play the first chord in the array
                //m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
                // for notes in current  chord
                /*
                m = MidiMessage::noteOn(m.getChannel(), NewNote , m.getVelocity());
                processedMidi.addEvent (m, time);
                 */
                
            }
            
            else if (m.isNoteOff() && m.getNoteNumber() < 58 )
            
            {
               // send note offs for first chord in array
                // for notes in current  chord
               // m = MidiMessage::noteOff(m.getChannel(), m.getNoteNumber(), m.getVelocity());
                //processedMidi.addEvent (m, time);
            }
            
            else if (m.isNoteOn() && m.getNoteNumber() == 59 )
                
            {
                // move chord pointer back one space if it is not at zero
                if (chordsPosition > 0)
                { chordsPosition -= 1 ;}
                
                // now play chord at new pointer position
                
                
                //int NewNote = m.getNoteNumber() + waylotrans -12;
               // playing[m.getNoteNumber()]= NewNote;
               // m = MidiMessage::noteOn(m.getChannel(), NewNote , m.getVelocity());
                
            }
            else if (m.isNoteOff() && m.getNoteNumber() == 59)
                
            {
                /*
                int NewNote = playing[m.getNoteNumber()];
                playing[m.getNoteNumber()] = NULL;
                m = MidiMessage::noteOff(m.getChannel(), NewNote , m.getVelocity());
                 */
                
            }
            
            else if (m.isNoteOn() && m.getNoteNumber() == 60 )
                
            {

                // now play chord at current pointer position
            }
            else if (m.isNoteOff() && m.getNoteNumber() == 60)
                
            {
                // send note off at current pointer position
                
                /*
                int NewNote = playing[m.getNoteNumber()];
                playing[m.getNoteNumber()] = NULL;
                m = MidiMessage::noteOff(m.getChannel(), NewNote , m.getVelocity());
                 */
                
            }
            
            else if (m.isNoteOn() && m.getNoteNumber() == 61 )
                
            {
                
                // now play chord at current pointer position
                
                
                
            }
            else if (m.isNoteOff() && m.getNoteNumber() == 61)
                
            {
                // send note off at current pointer position
                
                /*
                int NewNote = playing[m.getNoteNumber()];
                playing[m.getNoteNumber()] = NULL;
                m = MidiMessage::noteOff(m.getChannel(), NewNote , m.getVelocity());
                 */
                
            }
            
            else if (m.isNoteOn() && m.getNoteNumber() > 61 )
                
            {
                
                // move pointer forward unless it as end then do nothing
                if ( chordsPosition < numChords  - 1 )
                {
                    chordsPosition += 1;
                }
                
                // play chord at current position
                
                
                
            }
            else if (m.isNoteOff() && m.getNoteNumber() > 61)
                
            {
                // send note off at current pointer position
                
                /*
                int NewNote = playing[m.getNoteNumber()];
                playing[m.getNoteNumber()] = NULL;
                m = MidiMessage::noteOff(m.getChannel(), NewNote , m.getVelocity());
                 */
                
            }
            
            else if (m.isAftertouch())
            {
            }
            else if (m.isPitchWheel())
            {
            }
            
           // processedMidi.addEvent (m, time);
        }
        
        midiMessages.swapWith (processedMidi);
    }
            
            

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* channelData = buffer.getWritePointer (channel);

        // ..do something to the data...
    }
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
