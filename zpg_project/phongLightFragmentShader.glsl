#version 330 core

#define MAX_LIGHTS 10

in vec3 FragPos;
in vec3 Normal;
out vec4 out_Color;

struct Light {
    vec4 position;
    vec4 color;
};

uniform int numberOfLights;
uniform Light lights[MAX_LIGHTS];
uniform vec3 viewPosition;
uniform vec4 objectColor;
uniform float shininess;

void main() {
    vec3 norm = normalize(Normal);
    vec4 finalColor = vec4(0.0);

    // Ambient
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * objectColor;
    finalColor += ambient;

    for (int i = 0; i < numberOfLights; i++) {
        float distance = clamp(length(vec3(lights[i].position) - FragPos), 0.0, 10.0);
        float constant = 1.0;
        float linear = 0.09;
        float quadratic = 0.032;
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        // Diffuse
        vec3 lightDir = normalize(vec3(lights[i].position) - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = diff * lights[i].color;

        // Specular
        vec3 viewDir = normalize(viewPosition - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec4 specular = spec * lights[i].color;

        diffuse *= attenuation;
        specular *= attenuation;

        finalColor += diffuse * objectColor + specular;
    }

    out_Color = finalColor;
}
