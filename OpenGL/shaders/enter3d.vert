#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec2 vTexcoord;

uniform mat4 matModel;
uniform mat4 matView;
uniform mat4 matProj;

out vec2 fTexcoord;

void main()
{
    gl_Position = matProj * matView * matModel * vec4(vPos, 1.0f);
    fTexcoord = vTexcoord;
}