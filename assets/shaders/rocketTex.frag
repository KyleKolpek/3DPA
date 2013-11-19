#version 120

uniform sampler2D texture;

varying vec2 texCoord;
varying vec4 fragColor;

void main(void)
{
    vec3 objectColor = texture2D(texture, texCoord).xyz;
    gl_FragColor = vec4((objectColor + fragColor.xyz) / 2.0, 1.0);
}
