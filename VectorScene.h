#pragma once
#include "Scene.h"
#include "Vec3.h"
#include "Mat4.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class VectorScene : public Scene
{
public:
	VectorScene();
	~VectorScene();
	void Update() override;
	void HandleEvents() override;
	void Render() override;

	void drawVector(const Vec3 vec, const Vec3& origin);

	void drawSquare(const glm::mat4& transform);

	
};

