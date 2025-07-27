#pragma once
#include "Scene.h"
#include "Vec3.h"
#include "Mat4.h"
#include "Ray.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "camera.h"

class VectorScene : public Scene
{
	camera cam{ glm::vec3(0.0f, 0.0f, 3.0f),  // position
			  glm::vec3(0.0f, 1.0f, 0.0f),  // up vector
			  -90.0f,                       // yaw
			  0.0f };
	
public:
	
	glm::vec3 center;
	float radius = 0.4f;
		
	Ray cameraRay;    // build ray

	bool fired = false;
	float cameraSpeed = 0.1f;
	std::vector<glm::vec3> hitPoints;
	


	void drawSphere( float radius, int stacks, int slices, const glm::mat4& transform = glm::mat4(1.0f));

	VectorScene();
	~VectorScene();
	void Update(float deltaTime) override;
	void HandleEvents(GLFWwindow* window) override;
	void Render() override;

	void drawVector(const glm::vec3& vec, const glm::vec3 origin, const glm::mat4 transform);

	void drawCube(const glm::mat4& transform);
	
	
};

