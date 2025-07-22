
#pragma once
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/euler_angles.hpp>

using namespace glm;

struct transform {
	vec3 Position;
	vec3 Rotation = vec3(0.0f);
	vec3 Scale = vec3(1.0f);

	mat4 getMatrix() {
		mat4 t = translate(mat4(1.0f), Position);
		mat4 s = scale(mat4(1.0f), Scale);
		mat4 r = yawPitchRoll(Rotation.x, Rotation.y, Rotation.z);
		return t * s * r;
	}
};