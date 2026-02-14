#version 330 core

in vec3 triangleColor;
out vec4 FragColor;

void main()
{
    FragColor = vec4(triangleColor, 1.0f);
}