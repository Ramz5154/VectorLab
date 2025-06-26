#include "Mat4.h"
#include "Vec3.h"
Mat4::Mat4()
{
	
}

Mat4 Mat4::identity()
{
	Mat4 result;
	for (int col = 0; col < 4; col++) {
		for (int row = 0; row < 4; row++) {
			if (col == row) {
				result.m[row][col] = 1.0f;
			}
			else result.m[row][col] = 0.0f;
		}
	}

	return result;
}

Mat4 Mat4::translation(const Vec3 t) {
	Mat4 result = Mat4::identity();

	result.m[3][0] = t.x;
	result.m[3][1] = t.y;
	result.m[3][2] = t.z;

	return result;
}


Mat4 Mat4::scale(const Vec3& s)
{
	Mat4 result = Mat4::identity();
	result.m[0][0] = s.x;
	result.m[1][1] = s.y;
	result.m[2][2] = s.z;
	return result;
}

Mat4 Mat4::rotationX(float radians)
{
	Mat4 result = Mat4::identity();

	float c = std::cos(radians);
	float s = std::sin(radians);

	result.m[1][1] = c;
	result.m[1][2] = s;
	result.m[2][1] = -s;
	result.m[2][2] = c;

	return result;
}

Mat4 Mat4::rotationY(float radians)
{
	Mat4 result = Mat4::identity();

	float c = std::cos(radians);
	float s = std::sin(radians);

	result.m[0][0] = c;
	result.m[2][0] = -s;
	result.m[0][2] = s;
	result.m[2][2] = c;

	return result;
}

Mat4 Mat4::rotationZ(float radians)
{
	Mat4 result = Mat4::identity();

	float c = std::cos(radians);
	float s = std::sin(radians);

	result.m[0][0] = c;
	result.m[0][1] = s;
	result.m[0][1] = -s;
	result.m[1][1] = c;

	return result;
}

Mat4 Mat4::perspective(float fovRadians, float aspect, float near, float far)
{
	Mat4 result = {};

	float t = tanf(fovRadians / 2.0f); // tangent of half the field of view

	result.m[0][0] = 1.0f / (aspect * t);
	result.m[1][1] = 1.0f / t;
	result.m[2][2] = -(far + near) / (far - near);
	result.m[2][3] = -1.0f;
	result.m[3][2] = -(2.0f * far * near) / (far - near);

	return result;
}

Mat4 Mat4::lookAt(const Vec3& eye, const Vec3& center, const Vec3& up)
{
	Vec3 f = (center - eye).normalize();     // Forward
	Vec3 s = f.cross(up).normalize();        // Right
	Vec3 u = s.cross(f);                     // True up

	Mat4 result = Mat4::identity();

	result.m[0][0] = s.x;
	result.m[1][0] = s.y;
	result.m[2][0] = s.z;

	result.m[0][1] = u.x;
	result.m[1][1] = u.y;
	result.m[2][1] = u.z;

	result.m[0][2] = -f.x;
	result.m[1][2] = -f.y;
	result.m[2][2] = -f.z;

	result.m[3][0] = -s.dot(eye);
	result.m[3][1] = -u.dot(eye);
	result.m[3][2] = f.dot(eye); // NOTE: OpenGL uses -f.dot(eye), but this can vary depending on convention

	return result;
}

Mat4 Mat4::operator*(const Mat4& other) const {
	Mat4 result;

	for (int row = 0; row < 4; ++row) {
		for (int col = 0; col < 4; ++col) {
			float sum = 0.0f;

			// Multiply row of this (A) with column of other (B)
			for (int i = 0; i < 4; ++i) {
				sum += m[row][i] * other.m[i][col];
			}

			result.m[row][col] = sum;
		}
	}

	return result;
}


Vec3 Mat4::transformPoint(const Vec3& v) const {
	float x = v.x * m[0][0] + v.y * m[1][0] + v.z * m[2][0] + m[3][0];
	float y = v.x * m[0][1] + v.y * m[1][1] + v.z * m[2][1] + m[3][1];
	float z = v.x * m[0][2] + v.y * m[1][2] + v.z * m[2][2] + m[3][2];
	float w = v.x * m[0][3] + v.y * m[1][3] + v.z * m[2][3] + m[3][3];

	if (fabs(w) > 1e-6f) {
		x /= w;
		y /= w;
		z /= w;
	}
	else {
		std::cout << " Warning: w too small, skipping division\n";
	}


	return Vec3(x, y, z);
}
