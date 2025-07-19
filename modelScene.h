#pragma once
#include "scene.h"
#include "VectorScene.h"
#include "camera.h"
class modelScene : public Scene
{
	camera cam{ glm::vec3(0.0f, 0.0f, 3.0f),  // position
			  glm::vec3(0.0f, 1.0f, 0.0f),  // up vector
			  -90.0f,                       // yaw
			  0.0f };

	VectorScene vecScene;
public:
	float vecAX = 1.0f;
	float vecAY = 1.0f;
	float vecAZ = 1.0f;

	float vecBX = 1.0f;
	float vecBY = 1.0f;
	float vecBZ = 1.0f;

	bool crossVec = false;
	bool croNor = false;
	glm::vec3 center = { 0, 0, 0 };
	float radius = 0.4f;



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
	
};

