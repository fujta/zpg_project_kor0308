#version 330 core

layout(location = 0) in vec3 vp; // Vertex position
layout(location = 1) in vec3 vc; // Vertex color (not used, optional)
layout(location = 2) in vec2 uv; // Texture coordinates

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 uvc; // Texture coordinates for fragment shader

void main() {
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vp, 1.0);
    uvc = uv; // Pass texture coordinates to fragment shader
}
