#include "collision.h"
#include <algorithm>
#include <vector>
using namespace glm;

void collision::AABBAABBCollisionAction(std::vector<Cube*>& cubes, std::vector<Cube*>& floor,float delta)
{
	////////CUBE / FLOOR
	for (auto cub : cubes) {
		for (auto flo : floor) {
			vec3 max1 = cub->getMax();
			vec3 min1 = cub->getMin();
			vec3 max2 = flo->getMax();
			vec3 min2 = flo->getMin();

			if (max1.x > min2.x && min1.x < max2.x &&
				max1.y > min2.y && min1.y < max2.y &&
				max1.z > min2.z && min1.z < max2.z) {


				float overlapX = std::min(cub->getMax().x, flo->getMax().x) - std::max(cub->getMin().x, flo->getMin().x);
				float overlapY = std::min(cub->getMax().y, flo->getMax().y) - std::max(cub->getMin().y, flo->getMin().y);
				float overlapZ = std::min(cub->getMax().z, flo->getMax().z) - std::max(cub->getMin().z, flo->getMin().z);
				if (overlapX < overlapY && overlapX < overlapZ) {

					cub->Position.x += (cub->Position.x < flo->Position.x ? -overlapX : overlapX);
				}
				else if (overlapY < overlapZ) {

					cub->Position.y += (cub->Position.y < flo->Position.y ? -overlapY : overlapY);
					cub->velocity.y = 0.0f;
				}
				else {

					cub->Position.z += (cub->Position.z < flo->Position.z ? -overlapZ : overlapZ);
				}

			}
		}
}
	
	//////// CUBE / CUBE
	for (int i = 0; i < cubes.size(); i++) {
		for (int j = i + 1; j < cubes.size(); j++) {
			vec3 max1 = cubes[i]->getMax();
			vec3 min1 = cubes[i]->getMin();
			vec3 max2 = cubes[j]->getMax();
			vec3 min2 = cubes[j]->getMin();

			if (max1.x > min2.x && min1.x < max2.x &&
				max1.y > min2.y && min1.y < max2.y &&
				max1.z > min2.z && min1.z < max2.z){


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

void collision::SphereAABBCollisionAction(std::vector<Sphere*>& sph, std::vector<Cube*>& flo, std::vector<Cube*>& cub)
{
	for (auto floor : flo) {
		for (auto sphere : sph) {
			float clampedX = std::max(floor->getMin().x, std::min(sphere->Position.x, floor->getMax().x));
			float clampedY = std::max(floor->getMin().y, std::min(sphere->Position.y, floor->getMax().y));
			float clampedZ = std::max(floor->getMin().z, std::min(sphere->Position.z, floor->getMax().z));
			vec3 closestPoint = vec3(clampedX, clampedY, clampedZ);
			vec3 diff = sphere->Position - closestPoint;
			float distanceSquared = glm::dot(diff, diff);
			float radius = std::max(sphere->Scale.x, std::max(sphere->Scale.y, sphere->Scale.z));
			if (distanceSquared <= radius * radius) {
				vec3 colDir = normalize(diff);
				float penetration = radius - sqrt(distanceSquared);
				sphere->Position += colDir * penetration;
				if (colDir.y > 0.5f) {
					sphere->velocity.y = 0.0f;
				}

			}
		}
	}



	for (auto cube : cub) {
		for (auto sphere : sph) {
			float clampedX = std::max(cube->getMin().x, std::min(sphere->Position.x, cube->getMax().x));
			float clampedY = std::max(cube->getMin().y, std::min(sphere->Position.y, cube->getMax().y));
			float clampedZ = std::max(cube->getMin().z, std::min(sphere->Position.z, cube->getMax().z));
			vec3 closestPoint = vec3(clampedX, clampedY, clampedZ);
			vec3 diff = sphere->Position - closestPoint;
			float distanceSquared = glm::dot(diff, diff);
			float radius = std::max(sphere->Scale.x, std::max(sphere->Scale.y, sphere->Scale.z));
			if (distanceSquared <= radius * radius) {
			vec3 colDir = normalize(diff);
			float penetration = radius - sqrt(distanceSquared);
			sphere->Position += colDir * penetration * 0.5f;
			cube->Position -= colDir * penetration * 0.5f;
			cube->velocity.y = 0.0f;

			}


		}

	}

	for (int i = 0; i < sph.size(); i++) {
		for (int j = i + 1; j < sph.size(); j++) {
			
			float distance = glm::length(sph[i]->Position - sph[j]->Position);
			float radius1 = std::max({ sph[i]->Scale.x, sph[i]->Scale.y, sph[i]->Scale.z });
			float radius2 = std::max({ sph[j]->Scale.x, sph[j]->Scale.y, sph[j]->Scale.z });
			if (distance <= radius1 + radius2) {
				vec3 direction = glm::normalize(sph[i]->Position - sph[j]->Position);
				float penetration = (radius1 + radius2) - distance;

				
				sph[i]->Position += direction * (penetration * 0.5f);
				sph[j]->Position -= direction * (penetration * 0.5f);
			}
		}
	}
}