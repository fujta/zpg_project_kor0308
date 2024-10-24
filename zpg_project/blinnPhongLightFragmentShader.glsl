#version 330

in vec4 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;

uniform vec3 lightPosition;
uniform vec4 lightColor;
uniform vec4 objectColor;
uniform vec3 viewPosition;
uniform float shininess; 

void main(void) {
    vec3 normal = normalize(ex_worldNormal);
    vec3 lightVector = normalize(lightPosition - vec3(ex_worldPosition));
    vec3 viewDir = normalize(viewPosition - vec3(ex_worldPosition));

    float dot_product = max(dot(lightVector, normal), 0.0);
    vec4 diffuse = dot_product * lightColor * objectColor;

    vec3 halfwayDir = normalize(lightVector + viewDir);
    float spec = pow(max(dot(normal, halfwayDir), 0.0), shininess);
    vec4 specular = spec * lightColor;

    vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
    out_Color = ambient + diffuse + specular;
}
