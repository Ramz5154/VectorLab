#pragma once
#include <glm/glm.hpp>
using namespace glm;
struct Sphere {
	float radius;
	vec3 center;

	Sphere(float r, vec3 center) : radius(r), center(center) {}
	Sphere() : radius(1.0f), center(0.0f,0.0f,0.0f) {}
	~Sphere() {}
};