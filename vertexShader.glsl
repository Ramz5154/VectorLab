#version 450

layout (location = 0) in vec3 aPos;

out vec4 colour;
uniform mat4 u_MVP;

void main() {

gl_Position = u_MVP * vec4(aPos, 1.0);

colour = vec4(0.0f,1.0f,0.0f,0.0f);

}