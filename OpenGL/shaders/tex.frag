#version 330 core
uniform sampler2D tex;
in vec4 v_color;
in vec2 v_texcoord;

out vec4 frag_color;
void main()
{
    frag_color = texture(tex, v_texcoord) * v_color;
}