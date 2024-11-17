#version 330 core

in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

struct Material {
    float ra;
    float rd;
    float rs;
};

struct DirectionalLight {
    vec3 direction;
    vec4 color;
};

uniform Material material;
uniform DirectionalLight dirLight;
uniform vec3 viewPosition;
uniform vec4 objectColor;
uniform float shininess;

void main() {
    vec3 norm = normalize(Normal);

    // Ambient
    vec3 ambient = material.ra * 0.1 * dirLight.color.rgb;

    // Diffuse
    vec3 lightDir = normalize(-dirLight.direction);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = material.rd * diff * dirLight.color.rgb;

    // Specular
    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = material.rs * spec * dirLight.color.rgb;

    vec3 result = (ambient + diffuse + specular) * objectColor.rgb;
    FragColor = vec4(result, objectColor.a);
}
