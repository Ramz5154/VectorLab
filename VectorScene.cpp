#include "VectorScene.h"
#include <GLFW/glfw3.h>
#include "Vec3.h"
#include "Mat4.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "Sphere.h"
#include "Ray.h" 
#include "collision.h"
#include <cmath>

using namespace glm;

bool intersectRaySphere(const Ray& ray, const glm::vec3& center, float radius, float& outT) { // Checks if this ray hits the sphere.
                                                                                             // If it does, returns true and sets outT = distance (t) the ray had to travel to hit.

    glm::vec3 oc = ray.origin - center; // This computes the vector from the sphere center to the ray origin

    float a = glm::dot(ray.direction, ray.direction);
    float b = 2.0f * glm::dot(oc, ray.direction);
    float c = glm::dot(oc, oc) - radius * radius; // The distance from ray origin to the sphere center, squared — minus the radius squared
   /* If the ray is far away, c is large.
      If the ray starts inside the sphere, c can be negative.*/
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0.0f)//If discriminant < 0: no real solution = no hit
     return false;          //If discriminant > 0 : real solution = ray hits sphere

    float sqrtDisc = sqrt(discriminant);
    float t0 = (-b - sqrtDisc) / (2.0f * a);
    float t1 = (-b + sqrtDisc) / (2.0f * a);
    //These are the two possible t values(entry and exit) where the ray intersects the sphere.

    outT = (t0 >= 0.0f) ? t0 : t1;
    return outT >= 0.0f;
}


VectorScene::VectorScene()
{
    hitPoints.reserve(5);
}

VectorScene::~VectorScene()
{
}

void VectorScene::Update(double deltaTime)
{
    

    Ray ray(cam.Position, cam.cameraFront); // origin & direction
 
    float radius = 0.3f;
    float hitT;

    if (intersectRaySphere(ray, center, radius, hitT)) {
        glm::vec3 hitPoint = ray.at(hitT);
       // std::cout << "Hit at: (" << hitPoint.x << ", " << hitPoint.y << ", " << hitPoint.z << ")\n";
    }
    else {
        //std::cout << "No hit\n";
    }
}

void VectorScene::HandleEvents(GLFWwindow* window)
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

     if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS)
    {
        float hitT;
        if (intersectRaySphere(cameraRay, center, radius, hitT)) {
            glm::vec3 hitPoint = cameraRay.at(hitT);
            hitPoints.push_back(hitPoint);
          
        }
    }
}

void VectorScene::Render()
{
  
    cameraRay = Ray(cam.Position, cam.cameraFront);
    float time = glfwGetTime();
    glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    

    glm::mat4 model = glm::mat4(1.0f);
    
    
    model =  glm::translate(model, glm::vec3(center.x,center.y,center.z)) * glm::rotate(glm::mat4(1.0f), glm::radians(20.0f * time), glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 mvp = proj * cam.GetViewMatrix() * model;

    
    drawCube(mvp);
  
  
  
    glm::vec3 rayStart(cameraRay.origin.x, cameraRay.origin.y, cameraRay.origin.z);
    glm::vec3 rayDir(cameraRay.direction.x, cameraRay.direction.y, cameraRay.direction.z);
    drawVector(rayDir * 5.0f, rayStart, glm::mat4(1.0f));
    
  
    for (const auto p : hitPoints) {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, p);
        model = glm::scale(model,glm::vec3(0.1f));
        glm::mat4 mvp = proj * cam.GetViewMatrix() * model;
        glColor3f(1.0f, 0.0f, 0);
        drawSphere(1.0f, 12, 24, mvp);
        glColor3f(1.0f, 1.0f, 1.0f);
    }

    if (hitPoints.size() > 4)
        hitPoints.erase(hitPoints.begin() + 0);
              
    
}



void VectorScene::drawVector(const glm::vec3& vec, const glm::vec3 origin, const glm::mat4 transform) {
    glm::vec4 p0 = transform * glm::vec4(origin.x, origin.y, origin.z, 1.0f);
    glm::vec4 p1 = transform * glm::vec4(origin.x + vec.x, origin.y + vec.y, origin.z + vec.z, 1.0f);

    if (fabs(p0.w) > 1e-6f) p0 /= p0.w;
    if (fabs(p1.w) > 1e-6f) p1 /= p1.w;

    glBegin(GL_LINES);
    glVertex3f(p0.x, p0.y, p0.z);
    glVertex3f(p1.x, p1.y, p1.z);
    glEnd();
}


void VectorScene::drawCube(const glm::mat4& transform) {
    //Define the 8 corners of a cube centered at(0, 0, 0), each side = 1 unit
    
    std::vector<Vec3> corners = {
        Vec3(-0.5f, -0.5f, -0.5f), // 0
        Vec3( 0.5f, -0.5f, -0.5f), // 1
        Vec3( 0.5f,  0.5f, -0.5f), // 2
        Vec3(-0.5f,  0.5f, -0.5f), // 3
        Vec3(-0.5f, -0.5f,  0.5f), // 4
        Vec3( 0.5f, -0.5f,  0.5f), // 5
        Vec3( 0.5f,  0.5f,  0.5f), // 6
        Vec3(-0.5f,  0.5f,  0.5f)  // 7
    };
    //12 edges of cube
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
    };
    
    glBegin(GL_LINES);
    for (const auto& edge : edges) { //goes through all the pairs
        for (int i = 0; i < 2; ++i) { //if i == 0 use first edge if i == 1 use second edge    // edge 1 = start edge 2 = end , starts at 1 corner ends at another 
            const Vec3& v = corners[i == 0 ? edge.first : edge.second]; // edges come in pairs first is the first number and second is second 
            //for example if {7,4} is called it will call the 7th index in the corner vector and the fourth so {7,4} = Vec3(-0.5f,  0.5f,  0.5f), Vec3(-0.5f, -0.5f,  0.5f)

           // Turn the 3D point into a 4D point so the matrix can move (translate), rotate, and scale it properly
            glm::vec4 p = transform * glm::vec4(v.x, v.y, v.z, 1.0f); 

            if (fabs(p.w) > 1e-6f) {
                p.x /= p.w;// Divide by w to turn the 4D point into a 3D one (perspective divide)
                p.y /= p.w;// This makes far objects look smaller and close ones look bigger
                p.z /= p.w;// We skip it if w is almost zero to avoid errors
            }

            glVertex3f(p.x, p.y, p.z); //makes vector / line
        }
    }
    glEnd();
}





void VectorScene::drawSphere( float radius, int stacks = 12, int slices = 24, const glm::mat4& transform ) {

   

    for (int i = 0; i <= stacks; ++i) {
        float lat0 = glm::pi<float>() * (-0.5f + float(i - 1) / stacks);
        float z0 = sin(lat0);
        float zr0 = cos(lat0);

        float lat1 = glm::pi<float>() * (-0.5f + float(i) / stacks);
        float z1 = sin(lat1);
        float zr1 = cos(lat1);

      
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j <= slices; ++j) {
            float lng = 2 * glm::pi<float>() * float(j) / slices;
            float x = cos(lng);
            float y = sin(lng);


            glm::vec4 p1 = transform * glm::vec4(radius * x * zr0, radius * y * zr0, radius * z0, 1.0f);
            glm::vec4 p2 = transform * glm::vec4(radius * x * zr1, radius * y * zr1, radius * z1, 1.0f);

            


            if (fabs(p1.w) > 1e-6f) p1 /= p1.w;
            if (fabs(p2.w) > 1e-6f) p2 /= p2.w;

            glVertex3f(p1.x, p1.y, p1.z);
            glVertex3f(p2.x, p2.y, p2.z);

        }
        glEnd();
    }
}

