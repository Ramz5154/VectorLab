#include "modelScene.h"

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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        eye += cameraSpeed * cameraFront;// move in the direction of the front of the camera 
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        eye -= cameraSpeed * cameraFront;// move in the opposite direction of the front of the camera 
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        eye -= glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;// think of the right hand rulle point fingers to first vector (cameraFront) then curl them up pos of (up) 
    //which makes our thumb point right but we subtarct to get left;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        eye += glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
}

void modelScene::Render()
{
   
    glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(eye, eye + cameraFront, up);
	glm::vec3 vecto = vec3(-3.0f * vecAX, 3.0f * vecAY, 2.0f * vecAZ);
	glm::vec3 her = vec3(2 * vecBX,-2 * vecBY,0 * vecBZ);
    glm::vec3 heme = cross(vecto, her);
	
	glm::mat4 model = mat4(1.0f);
  
	mat4 mvp = proj * view * model;

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

void modelScene::HandleMouse(double xpos, double ypos)
{
	float xoffset;
    float yoffset;
    extern bool locked;
   
    //look right yaw increases 
    // look up pitch increases 

      // If this is the first time we're getting mouse input,
// just record the current position to avoid a big jump
    if (firstMouse) {
        vecScene.lastX = xpos;
        vecScene.lastY = ypos;
        firstMouse = false;
    }

    // Calculate how much the mouse moved this frame (offset)
    if (locked) {//free to move // press tab to get your curser
        // Horizontal movement (left/right)
        xoffset = (xpos - vecScene.lastX) * 0.1f;
        // Vertical movement (up/down), reversed because screen Y goes down as mouse goes up
        yoffset = (vecScene.lastY - ypos) * 0.1f;
    }
    else {
        // If camera is locked, don't move
        xoffset = 0.0f;
        yoffset = 0.0f;
    }

    // Save the current mouse position for the next frame
    vecScene.lastX = xpos;
    vecScene.lastY = ypos;

    // Update the yaw (left/right) and pitch (up/down) based on mouse movement
    yaw += xoffset;
    pitch += yoffset;

    // Limit how far we can look up or down (to prevent flipping over)
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    // Calculate the new direction the camera should face based on yaw and pitch
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch)); // forward/back
    direction.y = sin(glm::radians(pitch)); // up/down
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch)); // left/right

    // Make sure the direction vector is length 1
    cameraFront = glm::normalize(direction);

}
