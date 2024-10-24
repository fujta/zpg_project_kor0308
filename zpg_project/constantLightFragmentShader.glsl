#version 330

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;

uniform vec3 lightColor; 
uniform vec3 objectColor;
uniform vec3 lightPosition;

void main(void) {
    vec3 ambient = 0.1 * lightColor;
    vec4 color = vec4(ambient * objectColor, 1.0);
    out_Color = color;
}
