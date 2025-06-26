#include "VectorScene.h"
#include <GLFW/glfw3.h>
#include "Vec3.h"
#include "Mat4.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

VectorScene::VectorScene()
{
}

VectorScene::~VectorScene()
{
}

void VectorScene::Update()
{

}

void VectorScene::HandleEvents()
{

}

void VectorScene::Render()
{
    float fov = 30.0f * (3.14159f / 180.0f);
    float aspect = 800.0f / 600.0f;
    float near = 0.1f;
    float far = 100.0f;

    Vec3 eye(0, 0, 2);
    Vec3 target(0, 0, 0);
    Vec3 up(0, 1, 0);


    glm::mat4 proj = glm::perspective(glm::radians(30.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);

    glm::mat4 mvp = proj * view * model;




    drawSquare(mvp);

    //drawVector(Vec3(1, 1, 0),NULL);
   
}



void VectorScene::drawVector(const Vec3 vec, const Vec3& origin = Vec3(0, 0, 0)) {
    glBegin(GL_LINE_LOOP);
    glVertex3f(origin.x, origin.y, origin.z);
    glVertex3f(origin.x + vec.x, origin.y + vec.y, origin.z + vec.z);
    glEnd();
}

void VectorScene::drawSquare(const glm::mat4& transform) {
    Vec3 corners[4] = {
        Vec3(-0.5f, -0.5f, 0.0f),
        Vec3(0.5f, -0.5f, 0.0f),
        Vec3(0.5f,  0.5f, 0.0f),
        Vec3(-0.5f,  0.5f, 0.0f),
    };

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 4; ++i) {
        glm::vec4 p = transform * glm::vec4(corners[i].x, corners[i].y, corners[i].z, 1.0f);

        // Perspective division
        if (fabs(p.w) > 1e-6f) {
            p.x /= p.w;
            p.y /= p.w;
            p.z /= p.w;
        }

        // Now draw
        glVertex3f(p.x, p.y, p.z);


        // Print the final position
        std::cout << "Corner " << i << ": (" << p.x << ", " << p.y << ", " << p.z << ")\n";

        // Flatten for OpenGL
        glVertex3f(p.x, p.y, p.z);

    }
    glEnd();
}
