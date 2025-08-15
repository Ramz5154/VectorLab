#include <glad/glad.h>
#include "CollisionScene.h"
#include "objects.h"
#include "collision.h"
#include "VectorScene.h"
#include "modelScene.h"
#include "camera.h"
#include "shader.h"


using namespace glm;


CollisionScene::CollisionScene(Shader* shader) : shader(shader)
{
    vecScene = new VectorScene;
   

    spheres.push_back(s1 = new Sphere(vec3(1.5f, 10.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f)));
    spheres.push_back(s2 = new Sphere(vec3(0.0f, 5.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f)));
    spheres.push_back(s3 = new Sphere(vec3(0.0f, 10.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(1.0f)));

    Cubes.push_back(c1 = new Cube(vec3(-6.0f, 15.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.5f)));
    Ground.push_back(c2 = new Cube(vec3(0.0f, -6.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(40.5f, 5.5f, 30.5f)));
    Cubes.push_back(c3 = new Cube(vec3(7.0f, 45.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(2.5f)));
    
}

CollisionScene::~CollisionScene()
{
}


void CollisionScene::Update(float deltaTime)
{
    shader->use();
    for (auto obj : Cubes) {
        obj->velocity += obj->gravity * deltaTime;
        obj->Position += obj->velocity * deltaTime;
        glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
       
            glm::mat4 model = obj->getMatrix();
            
            mvp = proj * cam.GetViewMatrix() * model;
            shader->setMat4("u_MVP", glm::value_ptr(mvp));
            drawCube();
            
    }

    for (auto flo : Ground) {
        glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        glm::mat4 modelFloor = flo->getMatrix();
        mvp = proj * cam.GetViewMatrix() * modelFloor;
        shader->setMat4("u_MVP", glm::value_ptr(mvp));
        drawCube();

    }

    if (Cubes.size() >= 0 && Ground.size() >= 0) {
        collision::AABBAABBCollisionAction(Cubes, Ground, deltaTime);
    }
        collision::SphereAABBCollisionAction(spheres, Ground, Cubes);
    

    for (auto obj : spheres) {
        obj->velocity += obj->gravity * deltaTime;
        obj->Position += obj->velocity * deltaTime;
        glm::mat4 proj = glm::perspective(glm::radians(90.0f), 800.0f / 600.0f, 0.1f, 100.0f);

      
        glm::mat4 model = obj->getMatrix();
        mvp = proj * cam.GetViewMatrix() * model;
        shader->setMat4("u_MVP", glm::value_ptr(mvp));
        
        glUniform3f(glGetUniformLocation(shader->ID, "u_col"),1.0f, 0.4f, 0.0f);
        drawSphere(obj->Scale, 12, 24);
        //glUseProgram(0);
   }
    // if object i is a sphere add it to the sphere vector if cube, cube vector 
    // make a cubeSphere detection that takes both vectors 
   
    //TODO: multiple detections 
    //for (int i = 0; i < spheres.size(); i++) {
    //    for (int j = i+1; j < spheres.size(); j++) {

    //        if (collision::SphereSphereCollisionDetection(*spheres[i], *spheres[j])) {
    //            //printf("detected");

    //            collision::SphereSphereCollisionAction(*spheres[i], *spheres[j], deltaTime);
    //        }
    //    }
    //}
}

void CollisionScene::Render()
{
    glUniform3f(glGetUniformLocation(shader->ID, "u_col"), 0.0f, 0.4f, 0.4f);
    glBegin(GL_TRIANGLES);
    glNormal3f(0, 0, 1); // face normal
    glVertex3f(-1, -1, 1);
    glVertex3f(1, -1, 1);
    glVertex3f(1, 1, 1);

    glVertex3f(-1, -1, 1);
    glVertex3f(1, 1, 1);
    glVertex3f(-1, 1, 1);
   
    glEnd();
   
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
        s1->Position.x -= 0.01f * speed;
       
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        s1->Position.x += 0.01f * speed;
      
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        s1->Position.z -= 0.01f * speed;

    }
  
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        s1->Position.z += 0.01f * speed;

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
  
    if (c1->velocity.y == 0.0f)
        grounded = true;
    else
    grounded = false;

    if (grounded) {
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            c1->velocity.y += 10.51;
          
        }
    }
  
}

void CollisionScene::drawSphere(vec3 radius, int stacks = 12, int slices = 24) {
    

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



                vec4 p1 = vec4(MaxRadius * x * zr0, MaxRadius * y * zr0, MaxRadius * z0, 1.0f);
                vec4 p2 = vec4(MaxRadius * x * zr1, MaxRadius * y * zr1, MaxRadius * z1, 1.0f);

                if (fabs(p1.w) > 1e-6f) p1 /= p1.w;
                if (fabs(p2.w) > 1e-6f) p2 /= p2.w;

                glVertex3f(p1.x, p1.y, p1.z);
                glVertex3f(p2.x, p2.y, p2.z);

            }
            glEnd();
        }
    }


void CollisionScene::drawCube() {
    //Define the 8 corners of a cube centered at(0, 0, 0), each side = 1 unit

    std::vector<Vec3> corners = {
        Vec3(-0.5f, -0.5f, -0.5f), // 0
        Vec3(0.5f, -0.5f, -0.5f), // 1
        Vec3(0.5f,  0.5f, -0.5f), // 2
        Vec3(-0.5f,  0.5f, -0.5f), // 3
        Vec3(-0.5f, -0.5f,  0.5f), // 4
        Vec3(0.5f, -0.5f,  0.5f), // 5
        Vec3(0.5f,  0.5f,  0.5f), // 6
        Vec3(-0.5f,  0.5f,  0.5f)  // 7
    };
    //12 edges of cube
    std::vector<std::pair<int, int>> edges = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, // back face
        {4, 5}, {5, 6}, {6, 7}, {7, 4}, // front face
        {0, 4}, {1, 5}, {2, 6}, {3, 7}  // connecting edges
    };
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_LINE_LOOP);
    for (const auto& edge : edges) { //goes through all the pairs
        for (int i = 0; i < 2; ++i) { //if i == 0 use first edge if i == 1 use second edge    // edge 1 = start edge 2 = end , starts at 1 corner ends at another 
            const Vec3& v = corners[i == 0 ? edge.first : edge.second]; // edges come in pairs first is the first number and second is second 
            //for example if {7,4} is called it will call the 7th index in the corner vector and the fourth so {7,4} = Vec3(-0.5f,  0.5f,  0.5f), Vec3(-0.5f, -0.5f,  0.5f)

           // Turn the 3D point into a 4D point so the matrix can move (translate), rotate, and scale it properly
            glm::vec4 p = glm::vec4(v.x, v.y, v.z, 1.0f);

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
