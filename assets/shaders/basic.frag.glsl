#version 330 core

out vec4 outColor;

uniform sampler2D uDiffuseTexture;

void main() {
    outColor = texture(uDiffuseTexture, vec2(0.0, 0.0));
    outColor = vec4(1.0, 0.0, 0.0, 1.0);
}