#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Vec3.h"
#include "Scene.h"
#include "VectorScene.h"

Scene* currentScene;
bool locked = true;
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)//function to close the window
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if(key == GLFW_KEY_TAB && action == GLFW_PRESS){
        locked = !locked;
    }

}

VectorScene* currentSceneVec = nullptr;

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (currentSceneVec)
        currentSceneVec->HandleMouse(xpos, ypos);
}


int main() {
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "VectorLab", nullptr, nullptr);
    if (!window) {
        printf("window failed to create");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);

    currentSceneVec = new VectorScene();
    currentScene = currentSceneVec; // Both point to same instance 

    glfwSetCursorPosCallback(window, mouse_callback);
 
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

     if (locked) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
     else {
         glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
     }
        currentScene->HandleEvents(window);
        currentScene->Update();
        currentScene->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
