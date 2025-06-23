#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Vec3.h"


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)//function to close the window
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

int main() {

    Vec3 a (1, 2, 3);
    Vec3 b(4, 5, 6);
   

    if (!glfwInit()) return -1;

    GLFWwindow* window = glfwCreateWindow(800, 600, "VectorLab", nullptr, nullptr);
    if (!window) {
        printf("window failed to create");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    a.dot(b);
    a.cross(b);
    glfwSetKeyCallback(window, key_callback);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//grey background
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
