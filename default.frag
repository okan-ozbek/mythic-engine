#version 330 core
out vec4 FragColor;

in vec3 colorRGB;
in vec2 texture2D;

uniform sampler2D tex0;

void main()
{
    FragColor = texture(tex0, texture2D);
}