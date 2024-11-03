#version 330

in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
out vec4 out_Color;

uniform vec4 objectColor = vec4(0.385, 0.647, 0.812, 1.0);

void main(void) {
    out_Color = objectColor;
}
