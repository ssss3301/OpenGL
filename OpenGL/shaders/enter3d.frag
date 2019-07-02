#version 330 core
in vec2 fTexcoord;
uniform sampler2D tex;

out vec4 frag_color;

void main()
{
    frag_color = texture(tex, fTexcoord);
}