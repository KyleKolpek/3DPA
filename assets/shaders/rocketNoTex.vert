#version 130

uniform vec2 translation;
uniform vec2 viewDimensions;

attribute vec2 vertexPosition;
attribute vec4 vertexColor;

varying vec4 fragColor;

void main(void)
{
    //If we need to flip use this equation
    vec2 newTrans = translation/viewDimensions;
    newTrans = vec2(newTrans.x, -newTrans.y);
    vec2 newPos = vertexPosition/viewDimensions;
    newPos = vec2(newPos.x, 1-newPos.y);
    vec2 ndcPos = (newPos+newTrans)*2 - 1;

    //If we don't need to flip use this equation
    //vec2 ndcPos = (vertexPosition + translation)/(viewDimensions))*2 - 1;
    
    fragColor = vertexColor;
    gl_Position = vec4(ndcPos, 0.0, 1.0);
}
