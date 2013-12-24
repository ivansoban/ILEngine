#version 400

layout(location=0) in vec4 vert;
layout(location=1) in vec4 color;
out vec4 ex_Color;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
    gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * vert;
    ex_Color = color;
}

