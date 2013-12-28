#version 400

layout(location=0) in vec4 vert;
layout(location=1) in vec4 normal;
layout(location=2) in vec2 vertexUV;

out vec2 UV;

uniform mat4 ModelMatrix;
uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

void main(void)
{
    gl_Position = (ProjectionMatrix * ViewMatrix * ModelMatrix) * vert;

    UV = vertexUV;
}

