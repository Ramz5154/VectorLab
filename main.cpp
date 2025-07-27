#include <GLFW/glfw3.h>
#include <stdio.h>
#include "Vec3.h"
#include "Scene.h"
#include "VectorScene.h"
#include "modelScene.h"
#include "CollisionScene.h"
#include "camera.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <chrono>

int scene = 3;
Scene* currentScene;
camera* cam;

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
    if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
        scene = 3;
    }

}

VectorScene* currentSceneVec = nullptr;
modelScene* currentSceneMod = nullptr;
CollisionScene* currentSceneCol = nullptr;
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    cam->HandleMouse(xpos, ypos);
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
    glfwSetCursorPosCallback(window, mouse_callback);


    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");


    cam = new camera(glm::vec3(0.0f, 0.0f, 5.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
    currentSceneVec = new VectorScene();
    currentSceneMod = new modelScene();
    currentSceneCol = new CollisionScene();
    currentScene = currentSceneCol; // Both point to same instance 

    auto lastTime = std::chrono::high_resolution_clock::now();
 
    while (!glfwWindowShouldClose(window)) {

        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsedTime = currentTime - lastTime;
        float deltaTime = elapsedTime.count();
        lastTime = currentTime;

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
      
     if (locked) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
     else {
         glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
     }

 ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        currentScene->HandleEvents(window);
        currentScene->Update(deltaTime);
        currentScene->Render();

       
        glfwPollEvents();

       

        ImGui::Begin("Scene Switcher");
        if (ImGui::Button("Model Scene")) {
            scene = 2;
        }
        if (ImGui::Button("Vector Scene")) {
            scene = 1;
        }
        ImGui::Text("Current Scene: %d", scene);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);

        switch (scene) {
        case 1:
            currentScene = currentSceneVec;

            break;
        case 2:
            currentScene = currentSceneMod;
            break;

        case 3:
            currentScene = currentSceneCol;
            break;
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();


    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
