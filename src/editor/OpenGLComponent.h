#pragma once

#include <juce_opengl/juce_opengl.h>
#include "../core/Vertex.h"
#include "../core/Polygon.h"


using juce::OpenGLContext;
using juce::Component;
using juce::OpenGLRenderer;
using juce::OpenGLHelpers;
using juce::Colours::black;
using std::vector;
using std::complex;
using std::arg;

class OpenGLComponent final : public Component, public OpenGLRenderer {
public:
	OpenGLComponent();

	~OpenGLComponent() override;

private:
	void newOpenGLContextCreated() override;

	void prepareForNextFrame() const;

	void renderOpenGL() override;

	void openGLContextClosing() override;

	void drawFrame();

	void drawBackground();

	void drawPolygons();

	OpenGLContext glContext;
	Point2D* defaultCenter{};
	vector<Polygon*>* polygons{};
	vector<Vertex> vertexBuffer;
	vector<unsigned int> indexBuffer;

	unsigned int* vbo;
	unsigned int* indexBufferObject;
};
