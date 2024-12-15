#version 330 core

#define MAX_LIGHTS 10

in vec3 FragPos;
in vec3 Normal;
in vec2 uvc;
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
uniform vec3 viewPosition;
uniform float shininess;

uniform sampler2D textureUnitID;
uniform bool hasTexture;
uniform vec4 objectColor;

void main() {
    vec3 norm = normalize(Normal);
    vec4 finalColor = vec4(0.0);

    // Ambient
    vec4 ambient = lights[0].material.ra * vec4(0.1, 0.1, 0.1, 1.0);
    vec4 baseColor = hasTexture ? texture(textureUnitID, uvc) : objectColor;
    finalColor += ambient * baseColor;

    for (int i = 0; i < numberOfLights; i++) {
        float distance = clamp(length(vec3(lights[i].position) - FragPos), 0.0, 10.0);
        float constant = 1.0;
        float linear = 0.09;
        float quadratic = 0.032;

        float attenuation = 1.0 / (constant + linear * distance + quadratic * (distance * distance));

        // Diffuse component
        vec3 lightDir = normalize(vec3(lights[i].position) - FragPos);
        float diff = max(dot(norm, lightDir), 0.0);
        vec4 diffuse = lights[i].material.rd * diff * lights[i].color;

        // Specular component
        vec3 viewDir = normalize(viewPosition - FragPos);
        vec3 reflectDir = reflect(-lightDir, norm);
        float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
        vec4 specular = lights[i].material.rs * spec * lights[i].color;

        diffuse *= attenuation;
        specular *= attenuation;

        // Combine results for this light
        finalColor += (diffuse * baseColor) + specular;
    }

    out_Color = finalColor;
}
