#version 330 core

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUV;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec2 aUV;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(inPosition, 1.0);
    aUV = inUV;
}