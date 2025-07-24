#include "collision.h"
#include <algorithm>

using namespace glm;


bool collision::SphereSphereCollisionDetection(const Sphere& object1, const Sphere& object2)
{
	float distance = glm::length(object1.Position - object2.Position);
	float radius1 = std::max({ object1.Scale.x, object1.Scale.y, object1.Scale.z });
	float radius2 = std::max({ object2.Scale.x, object2.Scale.y, object2.Scale.z });
	if (distance <= radius1 + radius2) {
		return true;
	} 
	return false;
}
void collision::SphereSphereCollisionAction(Sphere& object1, Sphere& Object2, float delta)
{

		Object2.Position += object1.Scale * delta;
	
}



