#version 120

uniform vec2 translation;

attribute vec2 vertexPosition;
attribute vec4 vertexColor;

varying vec4 fragColor;

void main(void)
{
    gl_Position = vec4(vertexPosition + translation, 0.0, 1.0);
    fragColor = vertexColor;
}
