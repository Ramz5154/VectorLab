#pragma once
#include "Scene.h"
#include "VectorScene.h"
#include "objects.h"
#include <vector>
#include "shader.h"

class CollisionScene : public Scene
{
	camera cam{ glm::vec3(0.0f, 5.0f, 12.0f),  // position
			  glm::vec3(0.0f, 1.0f, 0.0f),  // up vector
			  -90.0f,                       // yaw
			  -40.0f };

	Shader* shader;

	VectorScene* vecScene;
	Sphere* s1;
	Sphere* s2;
	Sphere* s3;
	Cube* c1;
	Cube* c2;
	Cube* c3;
	mat4 mvp;
	float speed = 8.0f;
	bool grounded;
public:

	CollisionScene(Shader* shader);
	~CollisionScene();

	void Update(float deltaTime) override;
	void Render() override;
	void HandleEvents(GLFWwindow* window) override;

	void drawSphere(vec3 radius, int stacks, int slices);
	void drawCube();
	std::vector<Sphere*> spheres;
	std::vector<Cube*> Cubes;
	std::vector<Cube*> Ground;
	
};

