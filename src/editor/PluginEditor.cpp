#include "../processor/PluginProcessor.h"
#include "PluginEditor.h"

#include "Polygon.h"

#define WIDTH 1280
#define HEIGHT 1280
#define DEFAULT_NUM_EDGES 4
#define DEFAULT_EDGE_LEN (WIDTH/5.0f)

VisualizerAudioProcessorEditor::VisualizerAudioProcessorEditor(
	VisualizerAudioProcessor& p)
	: AudioProcessorEditor(&p), processorRef(p) {
	ignoreUnused(processorRef);
	this->defaultCenter = new Point2D(static_cast<float>(WIDTH) / 2.0f,
	                                  static_cast<float>(HEIGHT) / 2.0f);
	this->polygons = new vector<Polygon*>();
	this->polygons->push_back(
		new Polygon(*this->defaultCenter,
		            DEFAULT_EDGE_LEN,
		            DEFAULT_NUM_EDGES)
	);
	setSize(WIDTH, HEIGHT);
}

VisualizerAudioProcessorEditor::~VisualizerAudioProcessorEditor() {
	delete this->polygons;
}

void VisualizerAudioProcessorEditor::drawFrame(Graphics& g) const {
	VisualizerAudioProcessorEditor::drawBackground(g);
	this->drawPolygons(g);
}

void VisualizerAudioProcessorEditor::paint(Graphics& graphics) {
	this->drawFrame(graphics);
	this->prepareForNextFrame();
}

void VisualizerAudioProcessorEditor::resized() {
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
}

void VisualizerAudioProcessorEditor::prepareForNextFrame() const {
	for (const Polygon* polygon: *this->polygons) {
		for (Point2D* point: *polygon->vertices) {
			*point *= polar(1.0f, TWO_PI / 3600.0f);
		}
	}
}

void VisualizerAudioProcessorEditor::drawPolygons(Graphics& g) const {
	g.setColour (Colours::orange);
	for (const Polygon* polygon: *this->polygons) {
		juce::Path path;
		path.startNewSubPath(polygon->vertices->at(0)->real(),
		                     polygon->vertices->at(0)->imag());
		for (const Point2D* point: *polygon->vertices) {
			const Point<float> jucePoint{point->real(), point->imag()};
			path.lineTo(jucePoint);
		}
		path.closeSubPath();
		g.fillPath(path);
	}
}

void VisualizerAudioProcessorEditor::drawBackground(Graphics& g) {
	g.fillAll(Colours::black);
}
