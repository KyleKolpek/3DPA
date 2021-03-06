#version 120

uniform mat4 modelView;
uniform mat4 normalModelView;
uniform mat4 projection;

attribute vec3 vertexPosition;
attribute vec3 vertexNormal;
attribute vec4 vertexColor;
attribute vec3 cubePosition;

varying vec3 normal;
varying vec3 cameraSpacePos;
varying vec4 fragColor;

void main(void)
{
    vec4 p = modelView * vec4(vertexPosition + cubePosition, 1.0);
    gl_Position = projection * p;
    cameraSpacePos = p.xyz;
    normal = normalize(normalModelView * vec4(vertexNormal, 0.0)).xyz;
    fragColor = vertexColor;
}
