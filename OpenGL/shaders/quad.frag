#version 330 core
in vec2 fTexcoord;
uniform sampler2D mainTex;
out vec4 fragColor;

void main()
{
    fragColor = vec4(vec3(1.0 - texture(mainTex, fTexcoord)), 1.0);
}