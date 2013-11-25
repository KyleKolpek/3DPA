#version 120

uniform sampler2D texSampler;

varying vec2 texCoord;
varying vec4 fragColor;

void main(void)
{
    vec4 objectColor = texture2D(texSampler, texCoord);
    gl_FragColor = vec4(objectColor * fragColor);
}
