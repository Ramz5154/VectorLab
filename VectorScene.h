#pragma once
#include "Scene.h"
#include "Vec3.h"
#include "Mat4.h"
#include "Ray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>


class VectorScene : public Scene
{
public:
	glm::vec3 up = { 0, 1, 0 };
	glm::vec3 target = { 0, 0, 0 };
	glm::vec3 eye = { 0, 0, 5 };

	glm::vec3 rayOrgin = eye;         // ray starts at the camera
	glm::vec3 rayd = glm::normalize(target - eye); // direction toward the target
	Ray cameraRay = { rayOrgin, rayd };    // build ray

	float yaw = -90.0f;    // Facing forward along -Z
	float pitch = 0.0f;
	float lastX = 400;     // Half of your window width
	float lastY = 300;     // Half of your window height
	bool firstMouse = true;

	float cameraSpeed = 0.1f;

	glm::vec3 cameraFront = { 0.0f, 0.0f, -1.0f };
	 // direction you're looking



	void HandleMouse(double xpos, double ypos);

	VectorScene();
	~VectorScene();
	void Update() override;
	void HandleEvents(GLFWwindow* window) override;
	void Render() override;

	void drawVector(const Vec3& vec, const Vec3& origin, const glm::mat4& transform);

	void drawCube(const glm::mat4& transform);
	
	
};

