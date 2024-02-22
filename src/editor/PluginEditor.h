#pragma once

#include <complex>
#include <juce_opengl/juce_opengl.h>
#include "../processor/PluginProcessor.h"
#include "Polygon.h"

typedef std::complex<float> Point2D;

using namespace juce;

class VisualizerEditor final : public AudioProcessorEditor, public Timer {
public:
	explicit VisualizerEditor(
		VisualizerProcessor&);

	~VisualizerEditor() override;


	void paint(Graphics&) override;

	void resized() override;

private:
	void prepareForNextFrame() const;

	void drawPolygons(Graphics& g) const;

	static void drawBackground(Graphics& g);

	void drawFrame(Graphics& g) const;

	void timerCallback() override;

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	VisualizerProcessor& processorRef;

	Point2D* defaultCenter;
	vector<Polygon*>* polygons;
	OpenGLContext openGlContext;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VisualizerEditor)
};
