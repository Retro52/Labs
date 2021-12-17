#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texcoords;
layout (location = 2) in vec3 v_normals;

out vec3 a_color;

uniform mat4 model;
uniform mat4 project_view;
uniform vec3 v_color;

void main()
{
    a_color = v_color;
    gl_Position = project_view * model * vec4(v_position, 1.0);
}