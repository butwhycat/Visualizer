#pragma once

#include "Polygon.h"
#include "../processor/PluginProcessor.h"
#include <complex>

typedef std::complex<float> Point2D;

using namespace juce;

class VisualizerAudioProcessorEditor final : public AudioProcessorEditor {
public:
	explicit VisualizerAudioProcessorEditor(
		VisualizerAudioProcessor&);

	~VisualizerAudioProcessorEditor() override;


	void paint(Graphics&) override;

	void resized() override;

private:
	void prepareForNextFrame() const;

	void drawPolygons(Graphics& g) const;

	static void drawBackground(Graphics& g) ;

	void drawFrame(Graphics& g) const;

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	VisualizerAudioProcessor& processorRef;

	Point2D* defaultCenter;
	vector<Polygon*>* polygons;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualizerAudioProcessorEditor)
};
