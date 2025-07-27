#pragma once
#include "Scene.h"
#include "VectorScene.h"
#include "objects.h"
#include <vector>

class CollisionScene : public Scene
{
	camera cam{ glm::vec3(0.0f, 0.0f, 3.0f),  // position
			  glm::vec3(0.0f, 1.0f, 0.0f),  // up vector
			  -90.0f,                       // yaw
			  0.0f };

	
	VectorScene* vecScene;
	Sphere* s1;
	Sphere* s2;
	Sphere* s3;
	Cube* c1;
	Cube* c2;
	mat4 mvp;
	
public:
	CollisionScene();
	~CollisionScene();

	void Update(float deltaTime) override;
	void Render() override;
	void HandleEvents(GLFWwindow* window) override;

	void drawSphere(vec3 radius, int stacks, int slices, const glm::mat4& transform);
	std::vector<Sphere*> spheres;
	std::vector<Cube*> Cubes;
	
};

