#version 330 core

uniform vec3 light_color;
uniform vec3 object_color;
uniform vec3 light_pos;

in vec3 fNormal;
in vec3 fragWorldPos;
uniform vec3 viewPos;

void main()
{
    float ambient_factor = 0.1f;
    vec3 ambient_color = ambient_factor * light_color;
    vec3 light_direction = normalize(light_pos - fragWorldPos);
    vec3 diffuse_color = max(dot(normalize(fNormal), light_direction), 0.0) * light_color;

    vec3 reflect_light_direction = reflect(-light_direction, normalize(fNormal));
    vec3 view_direction = normalize(viewPos - fragWorldPos);
    float spec = pow(max(dot(reflect_light_direction, view_direction), 0.0), 128);
    float spec_strength = 0.6f;
    vec3 spec_color = spec_strength * spec * light_color;

    gl_FragColor = vec4((ambient_color + diffuse_color + spec_color) * object_color, 1.0f);
}