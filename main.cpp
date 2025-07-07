#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Vec3.h"
#include "Scene.h"
#include "VectorScene.h"
#include "modelScene.h"
int scene = 1;
Scene* currentScene;
bool locked = true;
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)//handle events
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    if(key == GLFW_KEY_TAB && action == GLFW_PRESS){
        locked = !locked;
    }

    if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
        scene = 1;
    }

    if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
        scene = 2;
    }

}

VectorScene* currentSceneVec = nullptr;
modelScene* currentSceneMod = nullptr;
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
    currentSceneMod = new modelScene();
    currentScene = currentSceneMod; // Both point to same instance 

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

        switch (scene) {
        case 1:
           currentScene = currentSceneMod;
            break;
        case 2:
            currentScene = currentSceneVec;
            break;
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
