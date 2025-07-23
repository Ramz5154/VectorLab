#include "CollisionScene.h"
#include "Sphere.h"
#include "collision.h"
#include "VectorScene.h"
#include "modelScene.h"

using namespace glm;

CollisionScene::CollisionScene()
{
    vecScene = new VectorScene;
    s1 = new Sphere(vec3(1.5f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.5f));
    s2 = new Sphere(vec3(0.0f, 0.0f, 0.0f), vec3(1.0f, 1.0f, 1.0f), vec3(0.5f));
}

CollisionScene::~CollisionScene()
{
}

void CollisionScene::Update(double deltaTime)
{
   
    s1->getMatrix();
    if (collision::SphereSphereCollisionDetection(*s1, *s2)) {
        printf("detected");  
        
    }
  collision::SphereSphereCollisionAction(*s1, *s2);
}

void CollisionScene::Render()
{
   drawSphere(s1->Scale, 12, 24, s1->getMatrix());
   drawSphere(s2->Scale, 12, 24, s2->getMatrix());
 
}

void CollisionScene::HandleEvents(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        s1->Position.x += 0.01f;
       
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        s1->Position.x -= 0.01f;
      
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        s1->Position.y += 0.01f;

    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        s1->Position.y -= 0.01f;

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


