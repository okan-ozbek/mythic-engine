#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColorRGB;
layout (location = 2) in vec2 aTexure2D;

out vec3 colorRGB;
out vec2 texture2D;

uniform float scale;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(aPosition, 1.0);
    colorRGB = aColorRGB;
    texture2D = aTexure2D;
};