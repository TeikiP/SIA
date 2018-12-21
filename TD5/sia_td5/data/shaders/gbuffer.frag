#version 410 core

uniform float specular_coef;

in vec3 vert_color;
in vec3 vert_normal;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec3 out_normal;


void main()
{
    out_color = vec4(vert_color, specular_coef);
    out_normal = normalize((vert_normal + 1) / 2);
}
