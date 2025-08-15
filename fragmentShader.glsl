#version 450

out vec4 fragColour;
uniform vec3 lightDir = normalize(vec3(0.5, -1.0, -0.3));
in vec3 FragPos;
in vec3 Normal;
uniform vec3 u_col;

void main() {

fragColour = vec4(u_col,1.0f);

float diff = max(dot(normalize(Normal), -lightDir), 0.0);
vec3 baseColor = u_col * diff;
//fragColour = vec4(baseColor, 1.0);

}