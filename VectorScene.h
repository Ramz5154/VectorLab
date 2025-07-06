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

	glm::vec3 center = { 10, 0, 0 };
	float radius = 0.4f;
	

	glm::vec3 up = { 0, 1, 0 };
	glm::vec3 target = { 0, 0, 0 };
	glm::vec3 eye = { 0, 0, 5 };
	

	Ray cameraRay;    // build ray

	float yaw = -90.0f;    // Facing forward along -Z
	float pitch = 0.0f;
	float lastX = 400;     // Half of your window width
	float lastY = 300;     // Half of your window height
	bool firstMouse = true;
	bool fired = false;
	float cameraSpeed = 0.1f;
	std::vector<glm::vec3> hitPoints;
	glm::vec3 cameraFront = { 0.0f, 0.0f, -1.0f };
	 // direction you're looking



	void HandleMouse(double xpos, double ypos);

	void drawSphere( float radius, int stacks, int slices, const glm::mat4& transform = glm::mat4(1.0f));

	VectorScene();
	~VectorScene();
	void Update() override;
	void HandleEvents(GLFWwindow* window) override;
	void Render() override;

	void drawVector(const Vec3& vec, const Vec3& origin, const glm::mat4& transform);

	void drawCube(const glm::mat4& transform);
	
	
};

