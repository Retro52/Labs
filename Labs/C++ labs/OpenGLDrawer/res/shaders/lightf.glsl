#version 330 core

out vec4 FragColor;

in vec3 Normal;
in vec3 FragPos;
in vec2 TexCoords;

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

uniform vec3 ProjPos;
uniform DirLight dirLight;
uniform int NR_POINT_LIGHTS;
uniform PointLight pointLights[16];

vec3 CalcLight(DirLight dirLight, PointLight pointLights[16], vec3 normal, vec3 fragPos, vec3 viewDir);

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(ProjPos - FragPos);
    vec3 result = CalcLight(dirLight, pointLights, norm, FragPos, viewDir);
    FragColor = vec4(result, 1.0f);

}

vec3 CalcLight(DirLight dirLight, PointLight pointLights[16], vec3 norm, vec3 FragPos, vec3 viewDir)
{
    // calculating directional light impact
    vec3 result = CalcDirLight(dirLight, norm, viewDir);

    // calculating point lights impact
    for(int i = 0; i < NR_POINT_LIGHTS; i++)
    {
        result += CalcPointLight(pointLights[i], norm, FragPos, viewDir);
    }
    // returning result
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
    vec3 ambient  = light.ambient  * vec3(1.0f, 1.0f, 1.0f);
    vec3 diffuse  = light.diffuse  * diff * vec3(1.0f, 1.0f, 1.0f) ;

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
    vec3 ambient  = light.ambient  * vec3(1.0f, 1.0f, 1.0f) ;
    vec3 diffuse  = light.diffuse  * diff * vec3(1.0f, 1.0f, 1.0f) ;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    return (ambient + diffuse);
}