#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexcoord;

uniform mat4 projMat;
uniform mat4 viewMat;
uniform mat4 modelMat;

out vec3 fragPos;
out vec3 fNormal;
out vec2 fTexcoord;

void main()
{
    gl_Position = projMat * viewMat * modelMat * vec4(aPosition, 1.0f);
    fragPos = vec3(modelMat * vec4(aPosition, 1.0f));
    fNormal = mat3(transpose(inverse(modelMat))) * aNormal;
    fTexcoord = aTexcoord;
}