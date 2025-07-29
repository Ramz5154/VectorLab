#include "CollisionScene.h"
#include "objects.h"
#include "collision.h"
#include "VectorScene.h"
#include "modelScene.h"
#include "camera.h"

using namespace glm;

CollisionScene::CollisionScene()
{
    vecScene = new VectorScene;
  
    spheres.push_back(s1 = new Sphere(vec3(1.5f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.5f)));
    spheres.push_back(s2 = new Sphere(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.5f)));
    spheres.push_back(s3 = new Sphere(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.5f)));

    Cubes.push_back(c1 = new Cube(vec3(-6.0f, 15.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.5f)));
    Ground.push_back(c2 = new Cube(vec3(0.0f, -6.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(40.5f,5.5f,30.5f)));
    Cubes.push_back(c3 = new Cube(vec3(7.0f, 45.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.5f)));
   
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update(float deltaTime)
{
    for (auto obj : Cubes) {
        obj->velocity += obj->gravity * deltaTime;
        obj->Position += obj->velocity * deltaTime;
        for (auto flo : Ground) {
            glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);

            glm::mat4 model = obj->getMatrix();
            glm::mat4 modelFloor = flo->getMatrix();
            mvp = proj * cam.GetViewMatrix() * model;
            vecScene->drawCube(mvp);
            mvp = proj * cam.GetViewMatrix() * modelFloor;
            vecScene->drawCube(mvp);

        }
    }

    if (Cubes.size() >= 0 && Ground.size() >= 0) {
        collision::AABBAABBCollisionAction(Cubes, Ground, deltaTime);
    }

    

   /* for (auto obj : spheres) {
        obj->Position.y += -9.8f * deltaTime;
        glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);


        glm::mat4 model = obj->getMatrix();
        mvp = proj * cam.GetViewMatrix() * model;
        drawSphere(obj->Scale, 12, 24, mvp);
   }*/
    // if object i is a sphere add it to the sphere vector if cube, cube vector 
    // make a cubeSphere detection that takes both vectors 
   
    //TODO: multiple detections 
    for (int i = 0; i < spheres.size(); i++) {
        for (int j = i+1; j < spheres.size(); j++) {

            if (collision::SphereSphereCollisionDetection(*spheres[i], *spheres[j])) {
                //printf("detected");

                collision::SphereSphereCollisionAction(*spheres[i], *spheres[j], deltaTime);
            }
        }
    }
}

void CollisionScene::Render()
{
   
}

void CollisionScene::HandleEvents(GLFWwindow* window)
{

    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    cam.HandleMouse(xpos, ypos);

    //bool forward = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;

    //bool back = glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS;

    //bool left = glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS;

    ////which makes our thumb point right but we subtarct to get left;
    //bool right = glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS;

    //cam.camInput(forward, back, left, right);

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        c3->Position.x -= 0.01f * speed;
       
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        c3->Position.x += 0.01f * speed;
      
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        c3->Position.z -= 0.01f * speed;

    }
  
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        c3->Position.z += 0.01f * speed;

    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        c3->Position.y += 0.01f * speed;

    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        c1->Position.x -= 0.01f * speed;

    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        c1->Position.x += 0.01f * speed;

    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        c1->Position.z -= 0.01f * speed;

    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        c1->Position.z += 0.01f * speed;

    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        c1->Position.y += 0.01f * speed;

    }
  
}

void CollisionScene::drawSphere(vec3 radius, int stacks = 12, int slices = 24, const mat4& transform = mat4(1.0f)) {
    

        float MaxRadius = std::max({ radius.x,radius.y,radius.z });

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



                vec4 p1 = transform * vec4(MaxRadius * x * zr0, MaxRadius * y * zr0, MaxRadius * z0, 1.0f);
                vec4 p2 = transform * vec4(MaxRadius * x * zr1, MaxRadius * y * zr1, MaxRadius * z1, 1.0f);

                if (fabs(p1.w) > 1e-6f) p1 /= p1.w;
                if (fabs(p2.w) > 1e-6f) p2 /= p2.w;

                glVertex3f(p1.x, p1.y, p1.z);
                glVertex3f(p2.x, p2.y, p2.z);

            }
            glEnd();
        }
    }


