#include "../processor/PluginProcessor.h"
#include "PluginEditor.h"

#include "Polygon.h"

using std::complex;
using std::arg;

#define WIDTH 1280
#define HEIGHT 1280
#define DEFAULT_NUM_EDGES 8
#define DEFAULT_EDGE_LEN (WIDTH/5.0f)

VisualizerEditor::VisualizerEditor(
	VisualizerProcessor& p)
	: AudioProcessorEditor(&p), processorRef(p) {
	ignoreUnused(processorRef);
	openGlContext.attachTo(*getTopLevelComponent());
	this->defaultCenter = new Point2D(static_cast<float>(WIDTH) / 2.0f,
	                                  static_cast<float>(HEIGHT) / 2.0f);
	this->polygons = new vector<Polygon*>();
	this->polygons->push_back(
		new Polygon(*this->defaultCenter,
		            DEFAULT_EDGE_LEN,
		            DEFAULT_NUM_EDGES)
	);
	setSize(WIDTH, HEIGHT);
	startTimer(100);
}

VisualizerEditor::~VisualizerEditor() {
	delete this->polygons;
}

void VisualizerEditor::drawFrame(Graphics& g) const {
	VisualizerEditor::drawBackground(g);
	this->drawPolygons(g);
}

void VisualizerEditor::paint(Graphics& graphics) {
	this->drawFrame(graphics);
	this->prepareForNextFrame();
	repaint();
}

void VisualizerEditor::resized() {
	// This is generally where you'll want to lay out the positions of any
	// subcomponents in your editor...
}

void VisualizerEditor::prepareForNextFrame() const {
	for (const Polygon* polygon: *this->polygons) {
		for (Point2D* point: *polygon->vertices) {
			const auto rotationAngle = arg<float>(*point);
			const complex<float> rotationVector = polar(0.5f, rotationAngle);

			complex<float> translatedPoint = *point - polygon->center;

			translatedPoint *= rotationVector;
			*point = translatedPoint + polygon->center;
		}
	}
}

void VisualizerEditor::drawPolygons(Graphics& g) const {
	g.setColour(Colours::orange);
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

void VisualizerEditor::drawBackground(Graphics& g) {
	g.fillAll(Colours::black);
}

void VisualizerEditor::timerCallback() {
	repaint();
}
