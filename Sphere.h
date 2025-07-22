#pragma once
#include <glm/glm.hpp>
#include "transform.h"
using namespace glm;
struct Sphere {
	
	transform trans;

	Sphere(transform trans) : trans(trans) {}
	~Sphere() {}


};