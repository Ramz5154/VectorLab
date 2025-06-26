#pragma once

#include "Vec3.h"

class Mat4 {
public:
    float m[4][4]; // 4x4 matrix
  
    //Constructors
    Mat4();                         // Defaults to identity
    static Mat4 identity();         // Creates identity matrix
   
    // Transformations
    static Mat4 translation(const Vec3 t);       // Move things
    static Mat4 scale(const Vec3& s);             // Scale things
    static Mat4 rotationX(float radians);         // Rotate around X
    static Mat4 rotationY(float radians);         // Rotate around Y
    static Mat4 rotationZ(float radians);         // Rotate around Z

    // Camera & Projection
    static Mat4 perspective(float fovRadians, float aspect, float near, float far);
    static Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up);

    // Math
    Mat4 operator*(const Mat4& other) const;      // Matrix * Matrix
    Vec3 transformPoint(const Vec3& v) const; // Matrix * Vec3
};
