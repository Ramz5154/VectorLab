#include "modelScene.h"

using namespace glm;

modelScene::modelScene() {

}

modelScene::~modelScene()
{
}

void modelScene::Update()
{
}

void modelScene::HandleEvents(GLFWwindow* window)
{
}

void modelScene::Render()
{
	mat4 view = glm::lookAt(glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	mat4 proj = perspective(radians(120.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	glm::vec3 vecto = glm::vec3(-3.0f, 3.0f, 2.0f);
	glm::vec3 her(1,-2,0);
	glm::vec3 hem(0,0,0);
	glm::vec3 heme = cross(vecto,her);
	glm::mat4 model = mat4(1.0f);
	mat4 mvp = model * view * proj;
	vecScene.drawVector(her,glm::vec3(0.0f,0.0f,0.0f), mvp);
	vecScene.drawVector(vecto, glm::vec3(0.0f, 0.0f, 0.0f), mvp);
	glColor3f(1.0f, 0.3f, 0.0f);
	vecScene.drawVector(heme, glm::vec3(0.0f, 0.0f, 0.0f), mvp);
	glColor3f(1.0f, 1.0f, 1.0f);
}
