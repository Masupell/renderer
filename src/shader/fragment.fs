#version 330 core

in vec3 triangleColor;
in vec2 texCoord;

out vec4 FragColor;

uniform sampler2D tex;

void main()
{
    FragColor = texture(tex, texCoord) * vec4(triangleColor, 1.0f);
}