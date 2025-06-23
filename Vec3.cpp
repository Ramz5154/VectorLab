#include "Vec3.h"


Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3::~Vec3()
{
}


float Vec3::length() const
{
	return std::sqrt(x*x + y*y + z*z);
}

Vec3 Vec3::normalize() const
{
	float len = length();
	if (len == 0) return Vec3(0.0, 0.0, 0.0);
	return Vec3(x, y, z) / len;

}

float Vec3::dot(const Vec3& other) const
{

	return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const
{

	return Vec3 (y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

void Vec3::print() const {

	std::cout << "(" << x << ", " << y << ", " << z << ")\n";

}

// opertator overloading section
Vec3 Vec3::operator+(const Vec3& other) const
{
	return Vec3(x + other.x, y + other.y, z + other.z);
}

bool Vec3::operator==(const Vec3& other) const
{
	return x == other.x && y == other.y && z == other.z;
	
}

Vec3 Vec3::operator-(const Vec3& other) const
{
	return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const Vec3& other) const
{
	return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3 Vec3::operator*(float scalar) const
{
	return Vec3( x * scalar, y * scalar, z * scalar);
}

Vec3 Vec3::operator/(float scalar) const
{
	return Vec3(x / scalar, y / scalar, z / scalar);
}
