#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

out vec3 fNormal;
out vec3 fragPos;

void main()
{
    gl_Position =  proj_mat * view_mat * model_mat * vec4(aPos,  1.0f);
    fragPos = vec3(model_mat * vec4(aPos, 1.0f));
    fNormal = mat3(transpose(inverse(model_mat))) * aNormal; 
}