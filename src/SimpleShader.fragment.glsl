#version 400

in vec2 UV;

out vec3 out_Color;

uniform sampler2D textureSampler;

void main(void)
{
    out_Color = texture( textureSampler, UV ).rgb;
}
