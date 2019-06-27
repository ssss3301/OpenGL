#version 330 core
layout (location = 0) in vec3 vert_coord;
layout (location = 1) in vec2 tex_coord;

out vec2 fTexCoord;
uniform mat4 trans_mat;

void main()
{
    gl_Position = trans_mat * vec4(vert_coord, 1.0f);
    fTexCoord = tex_coord;
}