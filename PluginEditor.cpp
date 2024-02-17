#include "PluginProcessor.h"
#include "PluginEditor.h"

VisualizerAudioProcessorEditor::VisualizerAudioProcessorEditor(VisualizerAudioProcessor &p)
		: AudioProcessorEditor(&p), processorRef(p) {
	juce::ignoreUnused(processorRef);

	setSize(1280, 720);
}

VisualizerAudioProcessorEditor::~VisualizerAudioProcessorEditor() = default;

void VisualizerAudioProcessorEditor::paint(juce::Graphics &g) {
	g.fillAll(juce::Colours::darkgrey);
	g.setColour(juce::Colours::orange);

	juce::Path path;
	path.startNewSubPath(juce::Point<float>(10, 10));
	path.lineTo(juce::Point<float>(50, 10));
	path.lineTo(juce::Point<float>(50, 50));
	path.lineTo(juce::Point<float>(10, 50));
	path.closeSubPath();

//	g.fillPath (path);
}

void VisualizerAudioProcessorEditor::resized() {
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
}
