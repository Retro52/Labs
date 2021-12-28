#version 330 core

in vec3 a_color;

out vec4 f_color;

void main()
{
    f_color = vec4(a_color, 1.0f);
}