#include "../processor/PluginProcessor.h"
#include "PluginEditor.h"

#define WIDTH 1280
#define HEIGHT 1280
#define DEFAULT_NUM_EDGES 8
#define DEFAULT_EDGE_LEN (WIDTH/5.0f)

Editor::Editor(Processor& p) : AudioProcessorEditor(&p), processorRef(p) {
	ignoreUnused(processorRef);
	this->openGLComponent = new OpenGLComponent();
	addAndMakeVisible(openGLComponent);
	openGLComponent->setBounds(0, 0, WIDTH, HEIGHT);

	setSize(WIDTH, HEIGHT);
}

Editor::~Editor() = default;

void Editor::paint(Graphics& graphics) {
}

void Editor::resized() {
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
}
