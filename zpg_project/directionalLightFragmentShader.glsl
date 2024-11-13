#version 330 core

in vec3 FragPos;   // Pozice fragmentu ve svìtových souøadnicích
in vec3 Normal;    // Normála fragmentu

out vec4 FragColor; // Barva výstupu

uniform vec3 viewPosition; // Pozice kamery

// Struktura pro smìrové svìtlo
struct DirectionalLight {
    vec3 direction; // Smìr svìtla
    vec4 color;     // Barva svìtla (RGB + intenzita)
};

uniform DirectionalLight dirLight;

uniform vec4 objectColor; // Barva objektu
uniform float shininess;  // Lesklost povrchu (faktor spekulárního lesku)

void main() {
    // Ambientní složka
    vec3 ambient = 0.1 * dirLight.color.rgb;

    // Difúzní složka
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-dirLight.direction); // Smìr od fragmentu ke svìtlu
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * dirLight.color.rgb;

    // Spekulární složka
    vec3 viewDir = normalize(viewPosition - FragPos); // Smìr od fragmentu ke kameøe
    vec3 reflectDir = reflect(-lightDir, norm);      // Odražený smìr svìtla
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), shininess);
    vec3 specular = spec * dirLight.color.rgb;

    // Kombinace složek osvìtlení
    vec3 result = (ambient + diffuse + specular) * objectColor.rgb;
    FragColor = vec4(result, objectColor.a); // Výstupní barva
}
