#version 330 core

#define MAX_LIGHTS 10

in vec3 FragPos;
in vec3 Normal;
out vec4 out_Color;

struct Material {
    float ra; // Ambient coefficient
    float rd; // Diffuse coefficient
    float rs; // Specular coefficient
};

struct Light {
    vec4 position;
    vec4 color;
    Material material; // Pøidání materiálu ke svìtlu
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
    for (int i = 0; i < numberOfLights; i++) {
        vec4 ambient = lights[i].material.ra * vec4(0.1, 0.1, 0.1, 1.0) * lights[i].color;
        finalColor += ambient;

        // Diffuse
        vec3 lightDir = normalize(vec3(lights[i].position) - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = lights[i].material.rd * diff * lights[i].color;

        // Specular
        vec3 viewDir = normalize(viewPosition - FragPos);
        vec3 halfwayDir = normalize(lightDir + viewDir);
        float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
        vec4 specular = lights[i].material.rs * spec * lights[i].color;

        finalColor += diffuse * objectColor + specular;
    }

    out_Color = finalColor;
}
