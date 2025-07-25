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

void collision::AABBAABBCollisionAction(Cube& object1, Cube& Object2, float delta)
{
}

bool collision::AABBAABBCollisionDetection( const Cube& object1, const Cube& object2)
{
	vec3 max1 = object1.getMax();
	vec3 min1 = object1.getMin();
	vec3 max2 = object2.getMax();
	vec3 min2 = object2.getMin();

	 if( max1.x > min2.x&& min1.x < max2.x &&
	 max1.y > min2.y&& min1.y < max2.y &&
	 max1.z > min2.z&& min1.z < max2.z)
		return true;
	return false;
}



