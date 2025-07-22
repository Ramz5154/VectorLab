#pragma once
#include "Scene.h"
#include "VectorScene.h"
#include "Sphere.h"

class CollisionScene : public Scene
{
	VectorScene* vecScene;
	Sphere* s1;
	Sphere* s2;
public:
	CollisionScene();
	~CollisionScene();

	void Update(double deltaTime) override;
	void Render() override;
	void HandleEvents(GLFWwindow* window) override;

	void drawSphere(vec3 radius, int stacks, int slices, const glm::mat4& transform);

};

