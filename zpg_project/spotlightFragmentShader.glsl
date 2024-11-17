#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Material {
    float ra;
    float rd;
    float rs;
};

struct Spotlight {
    vec3 position;
    vec3 direction;
    vec4 color;

    float cutOff;
    float outerCutOff;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Spotlight spotlight;
uniform vec3 viewPosition;
uniform vec4 objectColor;
uniform float shininess;

void main() {
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(spotlight.position - FragPos);

    // Ambientní složka
    vec3 ambient = material.ra * 0.1 * spotlight.color.rgb;

    // Difúzní složka
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.rd * diff * spotlight.color.rgb;

    // Spekulární složka
    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = material.rs * spec * spotlight.color.rgb;

    // Spotlight intensity
    float theta = dot(lightDir, normalize(-spotlight.direction));
    float epsilon = spotlight.cutOff - spotlight.outerCutOff;
    float intensity = clamp((theta - spotlight.outerCutOff) / epsilon, 0.0, 1.0);

    // Combine results
    vec3 result = (ambient + (diffuse + specular) * intensity) * objectColor.rgb;
    FragColor = vec4(result, objectColor.a);
}
