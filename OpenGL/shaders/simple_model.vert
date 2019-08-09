#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;

uniform mat4 proj_mat;
uniform mat4 model_mat;
uniform mat4 view_mat;
out vec2 fTexcoord;

void main()
{
    fTexcoord = aTexcoord;
    gl_Position = proj_mat * view_mat * model_mat * vec4(aPosition, 1.0f);
}