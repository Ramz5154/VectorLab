#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Vec3.h"
#include "Scene.h"
#include "VectorScene.h"

Scene* currentScene;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)//function to close the window
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {

    Vec3 a (10, 2, 3);
    Vec3 b(1, 2, 3);
   
   
    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "VectorLab", nullptr, nullptr);
    if (!window) {
        printf("window failed to create");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    a.length();
    Vec3 c = b.normalize();
    Vec3 d = a.normalize();
    std::cout << d.dot(c);
   
    glfwSetKeyCallback(window, key_callback);
    currentScene = new VectorScene();

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//grey background
        glClear(GL_COLOR_BUFFER_BIT);
        currentScene->Update();
        currentScene->Render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
