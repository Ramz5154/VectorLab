#pragma once
#include "Vec3.h"
#include <glm/glm.hpp>

class Ray //A ray is a straight line that starts at a point and goes forever in one direction.
{
public:
	glm::vec3 direction; // where you are pointing 
	glm::vec3 orgin; // where it starts
	Ray();
	Ray(const glm::vec3& o, const glm::vec3& d);

	glm::vec3 at(float t) const;
};

