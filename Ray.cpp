#include "Ray.h"

Ray::Ray() : origin(0.0f), direction(0.0f, 0.0f, -1.0f)
{
}

Ray::Ray(const glm::vec3& o, const glm::vec3& d) : origin(o), direction(glm::normalize(d))
{
}

glm::vec3 Ray::at(float t) const
{
	//origin = where the ray starts
	//direction = the direction it points(usually normalized)
	//t = how far you are from the object

	//If the math returns t = 2.0, that means
	//Starting at(0, 0, 3)
	//Moving in direction(0, 0, -1)
	//After 2 units, the ray hits the sphere
	//So hit point is : P(2) = (0, 0, 1)

	//If t < 0, it means the object is behind the ray's origin — no hit.
	//If t is very large, the object is very far away.
	return  origin + t * direction;
}
