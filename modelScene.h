#pragma once
#include "scene.h"
#include "VectorScene.h"

class modelScene : public Scene
{
	VectorScene vecScene;
public:
	float vecLength = 1.0f;
	bool crossVec = false;
	bool croNor = false;
	glm::vec3 center = { 0, 0, 0 };
	float radius = 0.4f;


	glm::vec3 up = { 0, 1, 0 };
	glm::vec3 target = { 0, 0, 0 };
	glm::vec3 eye = { 0, 0, 5 };


	Ray cameraRay;    // build ray

	float yaw = -90.0f;    // Facing forward along -Z
	float pitch = 0.0f;
	
	bool firstMouse = true;
	bool fired = false;
	float cameraSpeed = 0.1f;
	std::vector<glm::vec3> hitPoints;
	glm::vec3 cameraFront = { 0.0f, 0.0f, -1.0f };


	modelScene();
	~modelScene();
	void Update() override;
	void HandleEvents(GLFWwindow* window) override;
	void Render() override;
	void HandleMouse(double xpos, double ypos) override;
};

