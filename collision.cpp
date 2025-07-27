#include "collision.h"
#include <algorithm>
#include <vector>
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

void collision::AABBAABBCollisionAction(std::vector<Cube*>& cubes, float delta)
{

	for (int i = 0; i < cubes.size(); i++) {
		for (int j = i + 1; j < cubes.size(); j++) {
			float overlapX = std::min(cubes[i]->getMax().x, cubes[j]->getMax().x) - std::max(cubes[i]->getMin().x, cubes[j]->getMin().x);
			float overlapY = std::min(cubes[i]->getMax().y, cubes[j]->getMax().y) - std::max(cubes[i]->getMin().y, cubes[j]->getMin().y);
			float overlapZ = std::min(cubes[i]->getMax().z, cubes[j]->getMax().z) - std::max(cubes[i]->getMin().z, cubes[j]->getMin().z);
			if (overlapX < overlapY && overlapX < overlapZ) {
				
				cubes[i]->Position.x += (cubes[i]->Position.x < cubes[j]->Position.x ? -overlapX : overlapX);
			}
			else if (overlapY < overlapZ) {
				
				cubes[i]->Position.y += (cubes[i]->Position.y < cubes[j]->Position.y ? -overlapY : overlapY);
				cubes[i]->velocity.y = 0.0f; 
			}
			else {
				
				cubes[i]->Position.z += (cubes[i]->Position.z < cubes[j]->Position.z ? -overlapZ : overlapZ);
			}

		}
	}
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



