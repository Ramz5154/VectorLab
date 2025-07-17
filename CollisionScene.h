#pragma once
#include "Scene.h"


class CollisionScene : public Scene
{
public:
	CollisionScene();
	~CollisionScene();

	void Update() override;
	void Render() override;
	void HandleEvents(GLFWwindow* window) override;

};

