#version 330 core
layout (location = 0) in vec3 vert_pos;
layout (location = 1) in vec3 vert_color;
layout (location = 2) in vec2 tex_coord;

out vec4 v_color;
out vec2 v_texcoord;

void main()
{
    gl_Position = vec4(vert_pos, 1.0f);
    v_color = vec4(vert_color, 1.0f);
    v_texcoord = tex_coord;
}