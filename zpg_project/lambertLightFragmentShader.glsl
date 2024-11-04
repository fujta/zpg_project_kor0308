#version 330 core

#define MAX_LIGHTS 10

in vec3 FragPos;
in vec3 Normal;
out vec4 out_Color;

struct Light {
    vec4 position;
    vec4 color;
    vec4 objectColor;
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
        vec4 ambient = vec4(0.1) * lights[i].color;

        // Diffuse
        float diff = max(dot(normal, lightDir), 0.0);
        vec4 diffuse = diff * lights[i].color * 2.8; // boosted diffuse by 2.8 cuz absolutely dont know how to do it properly

        ambient *= attenuation;
        diffuse *= attenuation;

        finalColor += ambient + diffuse;
    }

    finalColor *= objectColor;
    finalColor = clamp(finalColor, 0.0, 1.0);

    out_Color = finalColor;
}
