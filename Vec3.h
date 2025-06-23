#pragma once

#include <cmath>
#include <iostream>

class Vec3
{


public:

	float x, y, z;

	Vec3(float x = 0, float y = 0, float z = 0);
	~Vec3();

	float length() const;


	Vec3 normalize() const;

	float dot(const Vec3& other) const;

	Vec3 cross(const Vec3& other) const;

	void print() const;


	Vec3 operator+(const Vec3& other) const;
	bool operator==(const Vec3& other) const;
	Vec3 operator-(const Vec3& other) const;
	Vec3 operator*(const Vec3& other) const;
	Vec3 operator*(float scalar) const;
	Vec3 operator/(float scalar) const;

};

