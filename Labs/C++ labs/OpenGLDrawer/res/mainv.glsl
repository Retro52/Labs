#version 330 core

layout (location = 0) in vec3 v_position;
layout (location = 1) in vec2 v_texCoord;
layout (location = 2) in vec3 v_normals;

out vec4 a_color;
out vec2 a_texCoord;
out vec3 a_normal;
out vec3 a_position;
out vec3 a_projPos;
out vec3 FragPos;

uniform mat4 model;
uniform vec3 proj_pos;
uniform mat4 project_view;

void main()
{
	a_texCoord = v_texCoord;
	a_color = vec4(1.0f,1.0f,1.0f,1.0f);
	gl_Position = project_view * model * vec4(v_position, 1.0);
	a_normal = mat3(transpose(inverse(model))) * v_normals;
	FragPos = vec3(model * vec4(v_position, 1.0));
}
