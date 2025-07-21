#include "CollisionScene.h"
#include "Sphere.h"
#include "collision.h"
#include "VectorScene.h"
#include "modelScene.h"

using namespace glm;

CollisionScene::CollisionScene()
{
    vecScene = new VectorScene;
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update(double deltaTime)
{
    s1 = new Sphere(2.0f, vec3(0, 0, -5));
    s2 = new Sphere(3.0f, vec3(2, 2, 2));
     
    if (collision::collisionDetection(*s1, *s2)) {
        printf("detected");
    }
}

void CollisionScene::Render()
{
    vecScene->drawSphere(s1->radius, 12, 8, mat4(1.0f));
}

void CollisionScene::HandleEvents(GLFWwindow* window)
{
}
