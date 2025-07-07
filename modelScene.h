#pragma once
#include "scene.h"
#include "VectorScene.h"

class modelScene : public Scene
{
	VectorScene vecScene;
public:

	modelScene();
	~modelScene();
	void Update() override;
	void HandleEvents(GLFWwindow* window) override;
	void Render() override;

};

