#version 330 core

out vec4 outColor;

uniform vec3 uColor;

void main() {
    outColor = vec4(uColor, 1.0);
}