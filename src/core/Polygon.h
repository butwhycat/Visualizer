#pragma once

#include <complex>
using namespace juce;
using std::vector;
using std::polar;
using namespace std::complex_literals;
typedef std::complex<float> Point2D;

#define PI (MathConstants<float>::pi)
#define TWO_PI (MathConstants<float>::twoPi)
#define SQRT_2 (MathConstants<float>::sqrt2)

class Polygon {
public:
	explicit Polygon(const Point2D center, const float edgeLength, const int numEdges)
		: vertices(nullptr), center(center), edgeLength(edgeLength), numEdges(numEdges) {
		vertices = new vector<Point2D*>();
		Point2D vertexOffset = polar(edgeLength / SQRT_2,
		                             TWO_PI / static_cast<float>(numEdges));
		for (auto i = 0; i < numEdges; ++i) {
			auto vertexToAdd = new Point2D(center);
			*vertexToAdd += vertexOffset;
			vertices->push_back(vertexToAdd);
			vertexOffset *= polar(1.0f, TWO_PI / static_cast<float>(numEdges));
		}
	}

	vector<Point2D*>* vertices;
	Point2D center;

private:
	float edgeLength;
	int numEdges;
};
