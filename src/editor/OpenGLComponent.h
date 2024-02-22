#pragma once

#include <juce_opengl/juce_opengl.h>
using juce::OpenGLContext;
using juce::Component;
using juce::OpenGLRenderer;

class OpenGLComponent final : public Component, public OpenGLRenderer {
public:
	OpenGLComponent();
	~OpenGLComponent();

private:
	OpenGLContext glContext;

	void newOpenGLContextCreated() override;

	void renderOpenGL() override;

	void openGLContextClosing() override;
};
