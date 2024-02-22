#pragma once

#include <complex>
#include "OpenGLComponent.h"
#include "../processor/PluginProcessor.h"

typedef std::complex<float> Point2D;

using namespace juce;

class Editor final : public AudioProcessorEditor {
public:
	explicit Editor(
		Processor&);

	~Editor() override;

	void paint(Graphics&) override;

	void resized() override;

private:

	// This reference is provided as a quick way for your editor to
	// access the processor object that created it.
	Processor& processorRef;

	OpenGLComponent *openGLComponent;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(Editor)
};
