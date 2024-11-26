#version 330 core

in vec2 uvc; // Texture coordinates from vertex shader
out vec4 frag_colour;

uniform sampler2D textureUnitID; // Sampler for texture
uniform bool hasTexture;         // Flag to determine if texture is used
uniform vec4 objectColor;        // Fallback color if no texture is provided

void main() {
    if (hasTexture) {
        frag_colour = texture(textureUnitID, uvc); // Use texture color
    } else {
        frag_colour = objectColor; // Use fallback color
    }
}
