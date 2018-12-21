#version 330 core

uniform vec3 light_col;

in vec3 vert_color;

out vec4 out_color;

void main()
{
  out_color = vec4(vert_color * light_col * 0.25, 1.f);
}
