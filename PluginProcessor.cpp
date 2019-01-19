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
vector< vector<int> > chords {
    { 41, 48 , 55, 56, 58, 63 },
    { 44 , 51 , 56, 58 , 61, 63 },
    { 42 , 49, 56, 60 , 61 , 66 },
    {48, 49, 56 , 58 , 63 },
    { 51, 52, 59, 61, 68 },
    {39, 46, 58, 63, 67, 68 } ,
    { 48, 58 , 63 , 65, 68 },
    {41, 48, 58 , 63, 67 } ,
    {41, 48, 57, 62, 65 },
    {46 , 53 , 60, 63, 68, 73, 74 },
    { 44, 51, 58, 61, 66, 72 , 73 },
    { 43, 50 , 58 , 60 , 65 , 72 , 73 },
    { 41, 48 , 55 ,56 ,58 , 64}
};






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
    
    
    MidiMessage m;
 
    
    
    {
    buffer.clear();
        
        
        MidiBuffer processedMidi;
        int time;
    
        
        for (MidiBuffer::Iterator i (midiMessages); i.getNextEvent (m, time);)
        {
            if (m.isNoteOn() && m.getNoteNumber() == 58 ) // reset the array position and play first chord
                
            {
                chordsPosition = 0;
                // play the first chord in the array
                int chordSize = chords[chordsPosition].size();
                //int chordSize = 6;
                
                // for notes in current  chord
                for ( int i = 0; i < chordSize; i++) {
                    int NewNote = chords[chordsPosition][i];
                    m = MidiMessage::noteOn(m.getChannel(), NewNote, m.getVelocity());
                    processedMidi.addEvent(m, time);
                }
                
                
            }
            
            
            
            
            
            
            else if (m.isNoteOn() && m.getNoteNumber() == 59 )
                
            {
                // move chord pointer back one space if it is not at zero
                if (chordsPosition > 0)
                { chordsPosition -= 1 ;}
                
                // now play chord at new pointer position
                
                int chordSize = chords[chordsPosition].size();
                
                for ( int i = 0; i < chordSize; i++) {
                    int NewNote = chords[chordsPosition][i];
                    m = MidiMessage::noteOn(m.getChannel(), NewNote, m.getVelocity());
                    processedMidi.addEvent(m, time);
                }
                
                
                //int NewNote = m.getNoteNumber() + waylotrans -12;
                // playing[m.getNoteNumber()]= NewNote;
                // m = MidiMessage::noteOn(m.getChannel(), NewNote , m.getVelocity());
                
            }
            
            /*
            else if (m.isNoteOn() && m.getNoteNumber() == 60 )
                
            {
                int chordSize = chords[chordsPosition].size();
                
                for ( int i = 0; i < chordSize; i++) {
                    int NewNote = chords[chordsPosition][i];
                    m = MidiMessage::noteOn(m.getChannel(), NewNote, m.getVelocity());
                    processedMidi.addEvent(m, time);
                }
                
            }
             */
            
            /*
            
            else if (m.isNoteOn() && m.getNoteNumber() == 61 )
                
            {
                int chordSize = chords[chordsPosition].size();
                // now play chord at current pointer position
                for ( int i = 0; i < chordSize; i++) {
                    int NewNote = chords[chordsPosition][i];
                    m = MidiMessage::noteOn(m.getChannel(), NewNote, m.getVelocity());
                    processedMidi.addEvent(m, time);
                }//
                
                
                
            }
            
            */
            else if (m.isNoteOn() && m.getNoteNumber() == 60 )
                
            {
                
                // move pointer forward unless it as end then do nothing
                if ( chordsPosition < 12 )
                {
                    chordsPosition += 1;
                }
                
                else if ( chordsPosition ==12 )
                {
                    chordsPosition = 0;
                }
                
                else {}
                
                int chordSize = chords[chordsPosition].size();
                // play chord at current position
                
                // now play chord at current pointer position
                for ( int i = 0; i < chordSize; i++) {
                    int NewNote = chords[chordsPosition][i];
                    m = MidiMessage::noteOn(m.getChannel(), NewNote, m.getVelocity());
                    processedMidi.addEvent(m, time);
                }//
                
                
                
                
            }
            else if (m.isNoteOff())
                
            {
                // send note off at current pointer position
                
                //for (int j = 0; j <= 16 ; j++) {
                    for (int i = 0; i < 128; ++i){
                        m = MidiMessage::noteOff(1, i, 0.0f);
                        processedMidi.addEvent(m, time);
                    }
                
                
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

