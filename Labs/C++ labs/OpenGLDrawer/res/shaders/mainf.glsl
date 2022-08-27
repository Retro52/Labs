#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;
in mat3 TBN;

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
	sampler2D texture_normal1;
	sampler2D texture_height1;
	sampler2D texture_diffuse1;
	sampler2D texture_specular1;
};

uniform vec3 ProjPos;
uniform Material material;
uniform DirLight dirLight;
uniform int NR_POINT_LIGHTS;
uniform PointLight pointLights[16];
uniform int drawMode;

vec3 CalcLight(DirLight dirLight, PointLight pointLights[16], vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
	vec3 result;
	vec3 norm;
	vec3 viewDir;
	/* Unlit */
	if (drawMode == 2 || drawMode == 4)
	{
		result = texture(material.texture_diffuse1, TexCoords).rgb;
	}
	else if(drawMode == 7)
	{
		result = texture(material.texture_specular1, TexCoords).rgb;
	}
	else if (drawMode == 8)
	{
		result = texture(material.texture_normal1, TexCoords).rgb;
	}
	else if (drawMode == 9)
	{
		result = texture(material.texture_height1, TexCoords).rgb;
	}
	else
	{
		norm = normalize(texture( material.texture_normal1, TexCoords ).rgb * 2.0 - 1.0);
		viewDir = normalize(TBN * ProjPos - TBN * FragPos);
		result = CalcLight(dirLight, pointLights, norm, FragPos, viewDir);
	}
	FragColor = vec4(result, 1.0f);
}

vec3 CalcLight(DirLight dirLight, PointLight pointLights[16], vec3 norm, vec3 FragPos, vec3 viewDir)
{
	vec3 result;
	if (drawMode != 6)
	{
		// calculating directional light impact
		result = CalcDirLight(dirLight, norm, viewDir);
	}

	if (drawMode != 5)
	{
		// calculating point lights impact
		for(int i = 0; i < NR_POINT_LIGHTS; i++)
		{
			result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
		}
	}
	// returning result
	return result;
}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction * TBN);
	vec3 reflectDir = reflect(-lightDir, normal);

	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// specular shading

	//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);

	// combine results
	vec3 ambient  = light.ambient;
	vec3 diffuse  = light.diffuse * diff;
	vec3 specular = light.specular * spec;

	if (drawMode == 3)
	{
		ambient = ambient * vec3(1.0f, 1.0f, 1.0f);
		diffuse = diffuse * vec3(1.0f, 1.0f, 1.0f);
		return (ambient + diffuse);
	}
	else
	{
		ambient = ambient * vec3(texture(material.texture_diffuse1, TexCoords));
		diffuse = diffuse * vec3(texture(material.texture_diffuse1, TexCoords));
		specular = specular * vec3(texture(material.texture_specular1, TexCoords));
	}

	return (ambient + diffuse + specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir;
	lightDir = normalize(light.position * TBN - FragPos);

	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);

	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);

	//	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0f);

	// attenuation
	float distance    = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

	// combine results
	vec3 ambient  = light.ambient;
	vec3 diffuse  = light.diffuse * diff;
	vec3 specular = light.specular * spec;

	if (drawMode == 3)
	{
		ambient = ambient * vec3(1.0f, 1.0f, 1.0f);
		diffuse = diffuse * vec3(1.0f, 1.0f, 1.0f);
		ambient  *= attenuation;
		diffuse  *= attenuation;
		return (ambient + diffuse);
	}
	else
	{
		ambient = ambient * vec3(texture(material.texture_diffuse1, TexCoords));
		diffuse = diffuse * vec3(texture(material.texture_diffuse1, TexCoords));
		specular = specular * vec3(texture(material.texture_specular1, TexCoords));
	}

	ambient  *= attenuation;
	diffuse  *= attenuation;
	specular *= attenuation;
	return (ambient + diffuse + specular);
}