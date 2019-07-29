#version 330 core
layout (location = 0) in vec3 vPos;
layout (location = 1) in vec3 vNormal;

uniform mat4 proj_mat;
uniform mat4 view_mat;
uniform mat4 model_mat;

out vec3 fNormal;
out vec3 fragWorldPos;

void main()
{
    gl_Position = proj_mat * view_mat * model_mat * vec4(vPos, 1.0f);
    fNormal = vNormal;
    fragWorldPos = vec3(model_mat * vec4(vPos, 1.0f));
}