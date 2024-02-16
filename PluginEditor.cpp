#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor(AudioPluginAudioProcessor &p)
		: AudioProcessorEditor(&p), processorRef(p) {
	juce::ignoreUnused(processorRef);
	// Make sure that before the constructor has finished, you've set the
	// editor's size to whatever you need it to be.
	setSize(400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor() {
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint(juce::Graphics &g) {
	g.fillAll (juce::Colours::darkgrey);
	g.setColour (juce::Colours::orange);

	juce::Path path;
	path.startNewSubPath (juce::Point<float> (10, 10));
	path.lineTo (juce::Point<float> (50, 10));
	path.lineTo (juce::Point<float> (50, 50));
	path.lineTo (juce::Point<float> (10, 50));
	path.closeSubPath();

	g.fillPath (path);
}

void AudioPluginAudioProcessorEditor::resized() {
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
}
