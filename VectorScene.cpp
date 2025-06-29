#include "VectorScene.h"
#include <GLFW/glfw3.h>
#include "Vec3.h"
#include "Mat4.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

#include "Ray.h" 
#include <cmath>

bool intersectRaySphere(const Ray& ray, const glm::vec3& center, float radius, float& outT) { // Checks if this ray hits the sphere.
                                                                                             // If it does, returns true and sets outT = distance (t) the ray had to travel to hit.

    glm::vec3 oc = ray.orgin - center; // This computes the vector from the sphere center to the ray origin

    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(oc, ray.direction);
    float c = glm::dot(oc, oc) - radius * radius; // The distance from ray origin to the sphere center, squared — minus the radius squared
   /* If the ray is far away, c is large.
      If the ray starts inside the sphere, c can be negative.*/
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0f)//If discriminant < 0: no real solution = no hit
     return false;          //If discriminant > 0 : real solution = ray hits sphere

    float sqrtDisc = sqrt(discriminant);
    float t0 = (-b - sqrtDisc) / (2.0f * a);
    float t1 = (-b + sqrtDisc) / (2.0f * a);
    //These are the two possible t values(entry and exit) where the ray intersects the sphere.

    outT = (t0 >= 0.0f) ? t0 : t1;
    return outT >= 0.0f;
}


VectorScene::VectorScene()
{
}

VectorScene::~VectorScene()
{
}

void VectorScene::Update()
{
    Ray ray(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1)); // origin & direction
    glm::vec3 center(0, 0, 0); // sphere center
    float radius = 1.0f;
    float hitT;

    if (intersectRaySphere(ray, center, radius, hitT)) {
        glm::vec3 hitPoint = ray.at(hitT);
        std::cout << "Hit at: (" << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << ")\n";
    }
    else {
        std::cout << "No hit\n";
    }
}

void VectorScene::HandleEvents()
{

}

void VectorScene::Render()
{
    Ray ray(glm::vec3(0, 0, 3), glm::vec3(0, 0, -1)); // camera at (0,0,3) looking at origin
    glm::vec3 center(0, 0, 0);
    float radius = 1.0f;
    float hitT;

    if (intersectRaySphere(ray, center, radius, hitT)) {
        glm::vec3 hitPoint = ray.at(hitT);
        std::cout << "Hit at: (" << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << ")\n";
    }
    else {
        std::cout << "No hit\n";
    }

    //Vec3 eye(0, 0, 2);
    Vec3 target(0, 0, 0);
    Vec3 up(0, 1, 0);
    glm::vec3 eye(0, 0, 2);
    float time = glfwGetTime();
    glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(eye, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::scale(model, glm::vec3(1, 1, 1));
    model = glm::rotate(glm::mat4(1.0f), time, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mvp = proj * view * model;


    glm::vec3 a(1, 3, 4);
   

    drawCube(mvp);

    //drawVector(Vec3(1, 1, 0),NULL);
   
}



void VectorScene::drawVector(const Vec3 vec, const Vec3& origin = Vec3(0, 0, 0)) {
    glBegin(GL_LINE_LOOP);
    glVertex3f(origin.x, origin.y, origin.z);
    glVertex3f(origin.x + vec.x, origin.y + vec.y, origin.z + vec.z);
    glEnd();
}


void VectorScene::drawCube(const glm::mat4& transform) {
    std::vector<Vec3> corners = {
        Vec3(-0.5f, -0.5f, -0.5f), // 0
        Vec3( 0.5f, -0.5f, -0.5f), // 1
        Vec3( 0.5f,  0.5f, -0.5f), // 2
        Vec3(-0.5f,  0.5f, -0.5f), // 3
        Vec3(-0.5f, -0.5f,  0.5f), // 4
        Vec3( 0.5f, -0.5f,  0.5f), // 5
        Vec3( 0.5f,  0.5f,  0.5f), // 6
        Vec3(-0.5f,  0.5f,  0.5f)  // 7
    };

    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
    };

    glBegin(GL_LINES);
    for (const auto& edge : edges) {
        for (int i = 0; i < 2; ++i) {
            const Vec3& v = corners[i == 0 ? edge.first : edge.second];
            glm::vec4 p = transform * glm::vec4(v.x, v.y, v.z, 1.0f);

            if (fabs(p.w) > 1e-6f) {
                p.x /= p.w;
                p.y /= p.w;
                p.z /= p.w;
            }

            glVertex3f(p.x, p.y, p.z);
        }
    }
    glEnd();
}

