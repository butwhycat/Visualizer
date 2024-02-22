#pragma once

#include <complex>
#include "OpenGLComponent.h"
#include "../processor/PluginProcessor.h"
#include "Polygon.h"

typedef std::complex<float> Point2D;

using namespace juce;

class Editor final : public AudioProcessorEditor, public Timer {
public:
	explicit Editor(
		Processor&);

	~Editor() override;

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
	Processor& processorRef;

	Point2D* defaultCenter;
	vector<Polygon*>* polygons;
	OpenGLComponent openGLComponent;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Editor)
};
