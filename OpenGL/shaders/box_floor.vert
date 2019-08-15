#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec2 aTexcoord;

out vec2 fTexcoord;
uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

void main()
{
    gl_Position = proj_mat * view_mat * model_mat * vec4(aPosition, 1.0f);
    fTexcoord = aTexcoord;
}