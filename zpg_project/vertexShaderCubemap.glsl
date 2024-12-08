#version 450 core
layout(location = 0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 fragmentLocalPosition;

void main() {
    vec4 pos = projectionMatrix * viewMatrix * vec4(vp, 1.0);
    gl_Position = pos.xyww;
    fragmentLocalPosition = vp;
}
