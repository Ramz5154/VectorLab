#version 450

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNor;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 u_MVP;
uniform mat4 u_Model;

void main() {
    FragPos = vec3(u_Model * vec4(aPos, 1.0)); 
    Normal = mat3(transpose(inverse(u_Model))) * aNor; // or just: Normal = aNor;

    gl_Position = u_MVP * vec4(aPos, 1.0);
}
