#version 330

in vec3 FragPos;
in vec3 Normal;
out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec3 viewPosition;
//uniform vec4 objectColor; TODO: add object color when needed

void main() {
    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0) * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPosition - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec4 diffuse = diff * lightColor;

    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    vec4 specular = vec4(0.5, 0.5, 0.5, 1.0) * spec * lightColor;

    out_Color = ambient + diffuse + specular;
}