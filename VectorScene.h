#pragma once
#include "Scene.h"
#include "Vec3.h"
class VectorScene : public Scene
{
public:
	VectorScene();
	~VectorScene();
	void Update() override;
	void HandleEvents() override;
	void Render() override;

	void drawVector(const Vec3& vec, const Vec3& origin);


};

