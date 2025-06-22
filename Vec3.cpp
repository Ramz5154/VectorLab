#include "Vec3.h"


Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::~Vec3()
{
}


float Vec3::length() const
{
	return std::sqrt(x*x + y*y + z+z);
}

Vec3 Vec3::normalize() const
{
	return Vec3();
}

float Vec3::dot(const Vec3& other) const
{
	return 0.0f;
}

Vec3 Vec3::cross(const Vec3& other) const
{
	return Vec3();
}

void Vec3::print() const {

	std::cout << x << y << z;
}