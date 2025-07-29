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

void collision::AABBAABBCollisionAction(std::vector<Cube*>& cubes, std::vector<Cube*>& floor,float delta)
{
	if (CubeFloorCollisionDetection(cubes, floor)) {
		for (int i = 0; i < cubes.size(); i++) {
			for (int j = 0; j < floor.size(); j++) {
				float overlapX = std::min(cubes[i]->getMax().x, floor[j]->getMax().x) - std::max(cubes[i]->getMin().x, floor[j]->getMin().x);
				float overlapY = std::min(cubes[i]->getMax().y, floor[j]->getMax().y) - std::max(cubes[i]->getMin().y, floor[j]->getMin().y);
				float overlapZ = std::min(cubes[i]->getMax().z, floor[j]->getMax().z) - std::max(cubes[i]->getMin().z, floor[j]->getMin().z);
				if (overlapX < overlapY && overlapX < overlapZ) {

					cubes[i]->Position.x += (cubes[i]->Position.x < floor[j]->Position.x ? -overlapX : overlapX);
				}
				else if (overlapY < overlapZ) {

					cubes[i]->Position.y += (cubes[i]->Position.y < floor[j]->Position.y ? -overlapY : overlapY);
					cubes[i]->velocity.y = 0.0f;
				}
				else {

					cubes[i]->Position.z += (cubes[i]->Position.z < floor[j]->Position.z ? -overlapZ : overlapZ);
				}

			}
		}
	}

	if (CubeCubeCollisionDetection(cubes)) {
		for (int i = 0; i < cubes.size(); i++) {
			for (int j = i + 1; j < cubes.size(); j++) {
				float overlapX = std::min(cubes[i]->getMax().x, cubes[j]->getMax().x) - std::max(cubes[i]->getMin().x, cubes[j]->getMin().x);
				float overlapY = std::min(cubes[i]->getMax().y, cubes[j]->getMax().y) - std::max(cubes[i]->getMin().y, cubes[j]->getMin().y);
				float overlapZ = std::min(cubes[i]->getMax().z, cubes[j]->getMax().z) - std::max(cubes[i]->getMin().z, cubes[j]->getMin().z);
				if (overlapX < overlapY && overlapX < overlapZ) {
					float push = overlapX * 0.5f;
					float dir = (cubes[i]->Position.x < cubes[j]->Position.x) ? 1.0f : -1.0f;
					cubes[i]->Position.x -= dir * push;
					cubes[j]->Position.x += dir * push;
				}
				else if (overlapY < overlapZ) {
					float push = overlapY * 0.5f;
					float dir = (cubes[i]->Position.y < cubes[j]->Position.y) ? 1.0f : -1.0f;
					cubes[i]->Position.y -= dir * push;
					cubes[j]->Position.y += dir * push;

					
					cubes[i]->velocity.y = 0.0f;
					cubes[j]->velocity.y = 0.0f;
				}
				else {
					float push = overlapZ * 0.5f;
					float dir = (cubes[i]->Position.z < cubes[j]->Position.z) ? 1.0f : -1.0f;
					cubes[i]->Position.z -= dir * push;
					cubes[j]->Position.z += dir * push;
				}


			}
		}

	}

}

bool collision::CubeFloorCollisionDetection(const std::vector<Cube*>& cubes, const std::vector<Cube*>& floor)
{
	for (auto cub : cubes) {
		for (auto flo : floor) {
			vec3 max1 = cub->getMax();
			vec3 min1 = cub->getMin();
			vec3 max2 = flo->getMax();
			vec3 min2 = flo->getMin();

			if (max1.x > min2.x && min1.x < max2.x &&
				max1.y > min2.y && min1.y < max2.y &&
				max1.z > min2.z && min1.z < max2.z)
				return true;
			
		}
	}
	return false;
}

bool collision::CubeCubeCollisionDetection(const std::vector<Cube*>& cubes)
{
for(int i = 0; i < cubes.size(); i++){
	for (int j = i + 1; j < cubes.size(); j++) {
			vec3 max1 = cubes[i]->getMax();
			vec3 min1 = cubes[i]->getMin();
			vec3 max2 = cubes[j]->getMax();
			vec3 min2 = cubes[j]->getMin();

			if (max1.x > min2.x && min1.x < max2.x &&
				max1.y > min2.y && min1.y < max2.y &&
				max1.z > min2.z && min1.z < max2.z)
				return true;

		}
	}
	return false;
}



