#pragma once
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
using namespace glm;

struct Cube {

	vec3 Position;
	vec3 Rotation;
	vec3 Scale;
	float gravity = -0.8f;

	vec3 getMin() const {
		return Position - Scale * 0.5f;
	}

	vec3 getMax() const {
		return Position + Scale * 0.5f;
	}

	mat4 getMatrix() {
		mat4 t = translate(mat4(1.0f), Position);
		mat4 s = scale(mat4(1.0f), Scale);
		mat4 r = yawPitchRoll(Rotation.x, Rotation.y, Rotation.z);
		return t * r * s;
	}

	Cube(vec3 Position, vec3 Rotation, vec3 Scale) : Position(Position), Rotation(Rotation), Scale(Scale) {}
	~Cube() {}
};

struct Sphere {

	vec3 Position;
	vec3 Rotation;
	vec3 Scale;
	float gravity = -0.8f;

	mat4 getMatrix() {
		mat4 t = translate(mat4(1.0f), Position);
		mat4 s = scale(mat4(1.0f), Scale);
		mat4 r = yawPitchRoll(Rotation.x, Rotation.y, Rotation.z);
		return r * s * t;
	}

	Sphere(vec3 Position, vec3 Rotation, vec3 Scale) : Position(Position), Rotation(Rotation), Scale(Scale) {}
	~Sphere() {}

};

