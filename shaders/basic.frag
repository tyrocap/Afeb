#version 330 core

out vec4 glFragColor;
in vec3 fragColor;

void main() {
    glFragColor = vec4(fragColor, 1.0f);
}