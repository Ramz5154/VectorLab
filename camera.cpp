#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


camera::camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch) : Position(position), up(up), yaw(yaw), pitch(pitch)
{

}

camera::camera()
{
}

camera::~camera()
{
}

glm::mat4 camera::GetViewMatrix() const
{
  return glm::lookAt(Position, Position + cameraFront, up);
}

void camera::camInput(bool forward, bool back, bool left, bool right)
{
    float cameraSpeed = 0.1f;
    if (forward) {
        Position += cameraSpeed * cameraFront;
    }
    if (back) {
        Position -= cameraSpeed * cameraFront;
    }
    if (left) {
        Position -= glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
    }
    if (right) {
        Position += glm::normalize(glm::cross(cameraFront, up)) * cameraSpeed;
    }
}

void camera::HandleMouse(double xpos, double ypos)
{
    float xoffset;
    float yoffset;
    extern bool locked;

    //look right yaw increases 
    // look up pitch increases 

      // If this is the first time we're getting mouse input,
// just record the current position to avoid a big jump
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    // Calculate how much the mouse moved this frame (offset)
    if (locked) {//free to move // press tab to get your curser
        // Horizontal movement (left/right)
        xoffset = (xpos - lastX) * 0.1f;
        // Vertical movement (up/down), reversed because screen Y goes down as mouse goes up
        yoffset = (lastY - ypos) * 0.1f;
    }
    else {
        // If camera is locked, don't move
        xoffset = 0.0f;
        yoffset = 0.0f;
    }

    // Save the current mouse position for the next frame
    lastX = xpos;
    lastY = ypos;

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

