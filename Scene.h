#pragma once
#include <GLFW/glfw3.h>

class Scene {
public:
	virtual ~Scene() {};
	virtual void Update(float deltaTime) = 0;
	virtual void Render() = 0;
	virtual void HandleEvents(GLFWwindow* window) = 0;
	
};

