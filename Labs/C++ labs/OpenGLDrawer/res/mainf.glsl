#version 330 core

/* TODO: needs refactoring and cleaning */
in vec4 a_color;
in vec2 a_texCoord;
in vec3 a_normal;
in vec3 a_position;
in vec3 a_projPos;
in vec3 FragPos;

out vec4 f_color;

struct DirLight
{
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	sampler2D diffuse;
	sampler2D specular;
	float shininess;
};

uniform sampler2D u_texture0;
uniform bool shouldCalcLight;
uniform int NR_POINT_LIGHTS;
uniform DirLight dirLight;
uniform PointLight pointLights[16];
//uniform Material material;


vec3 CalcLight(DirLight dirLight, PointLight pointLights[16], vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{

	vec3 norm = normalize(a_normal);
	vec3 viewDir = normalize(a_projPos - FragPos);

	vec3 result = CalcLight(dirLight, pointLights, norm, FragPos, viewDir);

	if (shouldCalcLight)
	{
		vec3 result = CalcLight(dirLight, pointLights, norm, FragPos, viewDir);
		f_color = vec4(result, 1.0f);
	}
	else
	{
		f_color = vec4(a_color.rgb, 1.0f) * texture(u_texture0, a_texCoord);
	}
}


vec3 CalcLight(DirLight dirLight, PointLight pointLights[16], vec3 norm, vec3 FragPos, vec3 viewDir)
{
	vec3 result = CalcDirLight(dirLight, norm, viewDir);

	// phase 2: Point lights
	for(int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
	}
	return result;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
	// combine results
	vec3 ambient  = light.ambient  * vec3(texture(u_texture0, a_texCoord));
//	vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, a_texCoord));
	vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_texture0, a_texCoord));
//	vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, a_texCoord));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, a_texCoord));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, a_texCoord));
//	return (ambient + diffuse + specular);
	return (ambient + diffuse);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);
	// attenuation
	float distance    = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance +
	light.quadratic * (distance * distance));
	// combine results
	vec3 ambient  = light.ambient  * vec3(texture(u_texture0, a_texCoord));
//	vec3 ambient  = light.ambient  * vec3(texture(material.diffuse, a_texCoord));
	vec3 diffuse  = light.diffuse  * diff * vec3(texture(u_texture0, a_texCoord));
//	vec3 diffuse  = light.diffuse  * diff * vec3(texture(material.diffuse, a_texCoord));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, a_texCoord));
//	vec3 specular = light.specular * spec * vec3(texture(material.specular, a_texCoord));
	ambient  *= attenuation;
	diffuse  *= attenuation;
//	specular *= attenuation;
//	return (ambient + diffuse + specular);
	return (ambient + diffuse);
}