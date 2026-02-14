#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;

out vec3 triangleColor;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(inPos, 1.0);
    triangleColor = inColor;
}