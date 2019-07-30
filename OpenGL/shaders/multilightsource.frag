#version 330 core

in vec3 fragPos;
in vec3 fNormal;
in vec2 fTexcoord;

struct DirectionLight{
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}

struct PointLight{
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
}

struct SpotLight{
    vec3 position;
    vec3 direction;
    float innerCutOff;
    float outerCutOff;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}

struct Material{
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
}

uniform DirectionLight dir_light;
#define DOTLIGHTCOUNT 4
uniform DotLight dot_light[DOTLIGHTCOUNT];
uniform SpotLight spot_light;
uniform Material mat;
uniform vec3 viewPos;

out vec4 fragColor;

vec3 CalcDirectionLight(DirectionLight direction_light, vec3 normal, vec3 viewpos){
    vec3 ambient = direction_light.ambient * texture(mat.diffuse, fTexcoord).rgb;

    vec3 diff = max(dot(-direction_light.direction, normal), 0.0);
    vec3 diffuse = direction_light.diffuse * diff * texture(mat.diffuse, fTexcoord).rgb;

    vec3 reflectLight = reflect(normalize(direction_light.direction), normal);
    vec3 view_direction = normalize(viewPos - fragPos);
    vec3 spec = pow(dot(reflectLight, view_direction), 0.0), mat.shininess);
    vec3 specular = direction_light.specular * spec * texture(mat.specular, fTexcoord).rgb;

    return ambient + diffuse + specular;
}

vec3 CalcPointLight(PointLight pointlight, vec3 normal, vec3 viewpos, vec3 fragpos){
    vec3 ambient = pointlight.ambient * texture(mat.ambient, fTexcoord).rgb;

    float distance = length(fragpos - pointlight);
    float attenuation = 1.0 / (pointlight.constant + pointlight.linear * distance + pointlight.quadratic * distance * distance);

    vec3 light_dir = normalize(fragPos - pointlight.position);
    vec3 diff = max(dot(light_dir, normal), 0.0);
    vec3 diffuse = diff * pointlight.diffuse * texture(mat.diffuse, fTexcoord).rgb;

    vec3 reflectLightDir = reflect(-light_dir, normal);
    vec3 viewDir = normalize(viewpos - fragpos);
    vec3 spec = pow(max(dot(reflectLightDir, viewDir), 0.0), mat.shininess);
    vec3 specular = spec * pointlight.specular * texture(mat.specular, fTexcoord).rgb;

    return ambient + diffuse  * attenuation + specular * attenuation;
}

vec3 CalcSpotLight(SpotLight spotlight, vec3 normal, vec3 viewpos, vec3 fragpos){
    vec3 ambient = spotlight.ambient * texture(mat.ambient, fTexcoord).rgb;

    vec3 light_dir = normalize(fragpos - spotlight.position);
    
    float theta = dot(normalize(spotlight.direction), light_dir);
    float epsilon =  spotlight.innerCutOff -  spotlight.outerCutOff;
    float intensity = clamp((theta - spotlight.outerCutOff) / epsilon, 0.0, 1.0);

    vec3 diff = max(dot(-light_dir, normal), 0.0);
    vec3 diffuse = spotlight.diffuse * diff * texture(mat.diffuse, fTexcoord).rgb * intensity;

    vec3 reflect_light_dir = reflect(light_dir, normal);
    vec3 view_direction = normalize(fragpos - viewpos);
    vec3 spec = pow(max(dot(reflect_light_dir, view_direction), 0.0), mat.shininess);
    vec3 specular = spec * spotlight.specular * texture(mat.specular, fTexcoord).rgb * intensity;

    return ambient + diffuse + specular;
}

void main()
{
    
}
