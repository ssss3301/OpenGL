#version 330 core

struct material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};

struct light {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};

uniform material m;
uniform light l;
uniform vec3 viewPosition;

in vec3 fragPosition;
in vec3 fNormal;
in vec2 fTexcoord;

out vec4 fragColor;

void main()
{
    vec3 ambient_color = l.ambient  * vec3(texture(m.diffuse, fTexcoord));

    vec3 lightDirection =  normalize(l.position - fragPosition);
    vec3 diffuse_color = max(dot(lightDirection, normalize(fNormal)), 0.0) * vec3(texture(m.diffuse, fTexcoord)) * l.diffuse;

    vec3 viewDir = normalize(viewPosition - fragPosition);
    vec3 reflectDir = reflect(-lightDirection, normalize(fNormal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), m.shininess);
    vec3 specular_color = spec * (vec3(texture(m.specular, fTexcoord))) * l.specular;

    fragColor = vec4(ambient_color + diffuse_color + specular_color, 1.0f);
}