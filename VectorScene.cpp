#include "VectorScene.h"
#include <GLFW/glfw3.h>
#include "Vec3.h"


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
    drawVector(Vec3(1, 2, 0),NULL);
}


void VectorScene::drawVector(const Vec3& vec, const Vec3& origin = Vec3(0, 0, 0)) {
    glBegin(GL_LINES);
    glVertex3f(origin.x, origin.y, origin.z);
    glVertex3f(origin.x + vec.x, origin.y + vec.y, origin.z + vec.z);
    glEnd();
}