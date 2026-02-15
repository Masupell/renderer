#version 330 core

layout (location = 0) in vec3 inPos;
layout (location = 1) in vec3 inColor;
layout (location = 2) in vec2 inTexCoord;

out vec3 triangleColor;
out vec2 texCoord;

uniform mat4 projection;

void main()
{
    gl_Position = projection * vec4(inPos, 1.0);
    triangleColor = inColor;
    texCoord = inTexCoord;
}