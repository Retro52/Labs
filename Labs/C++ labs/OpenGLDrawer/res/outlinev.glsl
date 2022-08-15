#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texCoord;
layout (location = 2) in vec3 v_normals;


uniform mat4 project_view;
uniform float outlining;
uniform mat4 model;

void main()
{
    gl_Position = project_view * model * vec4(v_position + v_normals * (outlining + 0.1f - 1.0f), 1.0);
//    gl_Position = project_view * model * vec4(v_position, 1.0);
//    gl_Position = project_view * model * vec4(v_position, 1.0);
}
