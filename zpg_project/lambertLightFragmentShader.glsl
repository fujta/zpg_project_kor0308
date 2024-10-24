#version 330 core

in vec3 FragPos;
in vec3 Normal;
out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec4 lightColor;
//uniform vec4 objectColor;

void main(void) {
    vec3 normal = normalize(Normal);
    vec3 lightVector = normalize(lightPosition - FragPos);

    // Lambertùv zákon: difuzní složka
    float dot_product = max(dot(lightVector, normal), 0.0);
    vec4 diffuse = dot_product * lightColor;

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    out_Color = ambient + diffuse;
}
