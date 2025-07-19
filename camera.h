#pragma once
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class camera
{
public: 
	camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch);
	camera();
	~camera();

	glm::vec3 up = { 0, 1, 0 };
	glm::vec3 target = { 0, 0, 0 };
	glm::vec3 Position;
	glm::vec3 cameraFront = { 0.0f, 0.0f, -1.0f };

	float yaw;    // Facing forward along -Z
	float pitch;
	float lastX = 400;     // Half of your window width
	float lastY = 300;     // Half of your window height
	bool firstMouse = true;



	glm::mat4 GetViewMatrix() const; 
	void camInput(bool forward, bool back, bool left, bool right);
	void HandleMouse(double xpos, double ypos);

};

