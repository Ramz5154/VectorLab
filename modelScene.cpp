#include "modelScene.h"
#include "camera.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    cam.HandleMouse(xpos, ypos);


    bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;
       
    bool back = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;
       
    bool left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;
       
    //which makes our thumb point right but we subtarct to get left;
    bool right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;
      
    cam.camInput(forward, back, left, right);

}

void modelScene::Render()
{
   
    glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  
	glm::vec3 vecto = vec3(-3.0f * vecAX, 3.0f * vecAY, 2.0f * vecAZ);
	glm::vec3 her = vec3(2 * vecBX,-2 * vecBY,0 * vecBZ);
    glm::vec3 heme = cross(vecto, her);
	
	glm::mat4 model = mat4(1.0f);
  
	mat4 mvp = proj * cam.GetViewMatrix() * model;

    ImGui::Begin("Vector Controls");
    ImGui::SliderFloat("Vec A X", &vecAX, 0.0f, 5.0f);
    ImGui::SliderFloat("Vec A Y", &vecAY, 0.0f, 5.0f);
    ImGui::SliderFloat("Vec A Z", &vecAZ, 0.0f, 5.0f);

    ImGui::SliderFloat("Vec B X", &vecBX, 0.0f, 5.0f);
    ImGui::SliderFloat("Vec B Y", &vecBY, 0.0f, 5.0f);
    ImGui::SliderFloat("Vec B Z", &vecBZ, 0.0f, 5.0f);

    if (ImGui::Button("cross")) crossVec = !crossVec;
    if (ImGui::Button("normalize")) croNor = !croNor;
    ImGui::End();

    if (croNor) {
        heme = normalize(heme);
        vecto = normalize(vecto);
        her = normalize(her);
    }

	vecScene.drawVector(her,glm::vec3(0.0f,0.0f,0.0f), mvp);
    glColor3f(0.0f, 1.0f, 0.0f);
	vecScene.drawVector(vecto, glm::vec3(0.0f, 0.0f, 0.0f), mvp);
	glColor3f(1.0f, 0.3f, 0.0f);
    if (crossVec) vecScene.drawVector(heme, glm::vec3(0.0f, 0.0f, 0.0f), mvp);
  
	glColor3f(1.0f, 1.0f, 1.0f);

   
}

