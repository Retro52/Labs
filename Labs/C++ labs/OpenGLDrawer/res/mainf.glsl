#version 330 core

in vec4 a_color;
in vec2 a_texCoord;
in vec3 a_normal;
in vec3 a_position;
in vec3 a_projPos;
in vec3 FragPos;
in vec3 lightPos;
in vec3 lightColor;

out vec4 f_color;

uniform sampler2D u_texture0;

void main()
{
	/* Object specularity */
	float specularStrength = 0.5;
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	/* Normalizing values */
	vec3 norm = normalize(a_normal);
	vec3 lightDir = normalize(lightPos - FragPos);

	/* Diffuse */
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;
//	vec3 result = (ambientStrength + diffuse) * a_color.rgb;

	/* Specular */
	vec3 viewDir = normalize(a_projPos - FragPos);
	vec3 reflectDir = reflect(- lightDir, norm);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 128);
	vec3 specular = specularStrength * spec * lightColor;

	/* Finalizing lights & applying texture */
	vec3 result = (ambient + diffuse + specular) * a_color.rgb;
	f_color = vec4(result, 1.0f);

	f_color = f_color * texture(u_texture0, a_texCoord);
}
