#version 330 core

#define MAX_LIGHTS 10

in vec3 FragPos;
in vec3 Normal;
out vec4 out_Color;

struct Material {
    float ra;
    float rd;
    float rs;
};

struct Light {
    vec4 position;
    vec4 color;
    Material material;
};

uniform int numberOfLights;
uniform Light lights[MAX_LIGHTS];
uniform vec4 objectColor;

void main() {
    vec3 normal = normalize(Normal);
    vec4 finalColor = vec4(0.0);

    for (int i = 0; i < numberOfLights; i++) {
        vec3 lightPos = vec3(lights[i].position.xyz);
        vec3 lightDir = normalize(lightPos - FragPos);
        float distance = clamp(length(lightPos - FragPos), 0.0, 10.0);

        float constant = 1.5;
        float linear = 0.14;
        float quadratic = 0.07;
        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        // Ambient
        vec4 ambient = lights[i].material.ra * vec4(0.1) * lights[i].color;

        // Diffuse
        float diff = max(dot(normal, lightDir), 0.0);
        vec4 diffuse = lights[i].material.rd * diff * lights[i].color;

        // Apply attenuation
        ambient *= attenuation;
        diffuse *= attenuation;

        finalColor += ambient + diffuse;
    }

    // Apply object color
    finalColor *= objectColor;

    // Clamp final color
    finalColor = clamp(finalColor, 0.0, 1.0);

    out_Color = finalColor;
}
