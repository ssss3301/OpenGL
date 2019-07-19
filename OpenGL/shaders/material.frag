#version 330 core

struct material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct light{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    vec3 position;
};

uniform material mat;
uniform light l;
uniform vec3 viewPos;

in vec3 fNormal;
in vec3 fragPos;

out vec4 fragColor;

void main()
{
    vec3 ambient = l.ambient * mat.ambient;

    vec3 lightDirection = normalize(l.position - fragPos);
    vec3 diffuse = max(dot(normalize(fNormal),lightDirection), 0.0) * mat.diffuse * l.diffuse;

    vec3 reflect_direction =  reflect(-lightDirection,normalize(fNormal));
    vec3 view_direction = normalize(viewPos - fragPos);
    vec3 specular = pow(max(dot(reflect_direction, view_direction), 0.0), mat.shininess) * mat.specular * l.specular;

    fragColor = vec4(ambient + diffuse + specular, 1.0f);
}