#include "OpenGLComponent.h"

OpenGLComponent::OpenGLComponent(): vbo(new unsigned int), indexBufferObject(new unsigned int) {
	setOpaque(true);
	glContext.setRenderer(this);
	// todo change this to false once i have audio clock from Processor
	glContext.setContinuousRepainting(true);
	glContext.attachTo(*this);

	this->defaultCenter = new Point2D(0.5f, 0.5f);
	this->polygons = new vector<Polygon*>();
	this->polygons->push_back(new Polygon(*defaultCenter, 0.1f, 6));
}

OpenGLComponent::~OpenGLComponent() {
	glContext.detach();
	delete this->polygons;
}

void OpenGLComponent::newOpenGLContextCreated() {
	this->glContext.extensions.glGenBuffers(1, vbo);
	this->glContext.extensions.glGenBuffers(1, indexBufferObject);
}

void OpenGLComponent::prepareForNextFrame() const {
	for (const Polygon* polygon: *this->polygons) {
		for (Point2D* point: *polygon->vertices) {
			const auto rotationAngle = arg<float>(*point);
			const complex<float> rotationVector = polar(1.0f, rotationAngle);
			*point *= rotationVector;
		}
	}
}

void OpenGLComponent::renderOpenGL() {
	this->drawFrame();
	this->prepareForNextFrame();
}

void OpenGLComponent::openGLContextClosing() {
}

void OpenGLComponent::drawFrame() {
	this->drawBackground();
	this->drawPolygons();
}

void OpenGLComponent::drawBackground() {
	OpenGLHelpers::clear(Colours::black);
}

void OpenGLComponent::drawPolygons() {
	for (const Polygon* polygon: *this->polygons) {
		juce::Path path;
		path.startNewSubPath(polygon->vertices->at(0)->real(),
		                     polygon->vertices->at(0)->imag());
		for (const Point2D* point: *polygon->vertices) {
			const Point<float> jucePoint{point->real(), point->imag()};
			path.lineTo(jucePoint);
		}
		path.closeSubPath();
	}
}
