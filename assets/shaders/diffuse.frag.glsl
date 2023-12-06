#version 330 core

in vec2 aUV;
out vec4 outColor;

uniform sampler2D uTexture;

void main() {
    outColor = texture(uTexture, aUV);
}