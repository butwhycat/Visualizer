#include "OpenGLComponent.h"

OpenGLComponent::OpenGLComponent() {
	setOpaque(true);
	glContext.setRenderer(this);

	// todo change this to false once i have audio clock from Processor
	glContext.setContinuousRepainting(true);

	glContext.attachTo(*this);
}

OpenGLComponent::~OpenGLComponent() {
	glContext.detach();
}


void OpenGLComponent::newOpenGLContextCreated() {
}

void OpenGLComponent::renderOpenGL() {
}

void OpenGLComponent::openGLContextClosing() {
}
