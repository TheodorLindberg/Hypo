#version 440 core
#name Default

#type Vertex

in layout(location = 0) vec3 a_Position;
in layout(location = 1) vec3 a_Normal;
in layout(location = 2) vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec3 v_Position;
out vec3 v_Normal;

layout(std140) uniform Transform
{
	mat4 u_ProjectionViewMatrix;
	mat4 u_ViewMatrix;
	mat4 u_ModelMatrix;
	vec3 u_ViewPos;
} transform;

void main()
{
	v_Position = vec3(transform.u_ModelMatrix * vec4(a_Position, 1.0));
	v_Normal = mat3(transpose(inverse(transform.u_ModelMatrix))) * a_Normal;

	gl_Position = transform.u_ProjectionViewMatrix * vec4(v_Position, 1.0);
	v_TexCoord = a_TexCoord;

}

#type Fragment


out vec4 color;

in vec2 v_TexCoord;
in vec3 v_Normal;
in vec3 v_Position;

uniform sampler2D texture1;

layout(std140) uniform Transform
{
	mat4 u_ProjectionViewMatrix;
	mat4 u_ViewMatrix;
	mat4 u_ModelMatrix;
	vec3 u_ViewPos;
} transform;

struct DirLight {
	vec3 direction;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight {
	vec3 position;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct SpotLight {
	vec3 position;
	vec3 direction;
	float cutOff;
	float outerCutOff;

	float constant;
	float linear;
	float quadratic;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};


layout(std140) uniform DirLightBlock
{
	DirLight light;
} dirLight;

layout(std140) uniform PointLightsBlock
{
	PointLight lights[6];
} pointLights;

layout(std140) uniform SpotLightBlock
{
	SpotLight light;
} spotLight;


// function prototypes
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main()
{
	// properties
	
	vec3 norm = normalize(v_Normal);
	vec3 viewDir = normalize(transform.u_ViewPos - v_Position);
	
	// == =====================================================
	// Our lighting is set up in 3 phases: directional, point lights and an optional flashlight
	// For each phase, a calculate function is defined that calculates the corresponding color
	// per lamp. In the main() function we take all the calculated colors and sum them up for
	// this fragment's final color.
	// == =====================================================
	// phase 1: directional lighting
	vec3 result = { 0,0,0 };// CalcDirLight(dirLight, norm, viewDir);
	// phase 2: point lights
	for (int i = 0; i < 5; i++)
		result += CalcPointLight(pointLights.lights[i], norm, v_Position, viewDir);
	// phase 3: spot light
	//result += CalcSpotLight(spotLight, norm, FragPos, viewDir);

	color = vec4(vec3(texture(texture1, v_TexCoord)), 1.f);
	color = vec4(result, 1.f);
}

// calculates the color when using a directional light.
vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-light.direction);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(texture1, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(texture1, v_TexCoord));
	//vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	return (ambient + diffuse /*+ specular*/);
}

// calculates the color when using a point light.
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// combine results
	vec3 ambient = light.ambient * vec3(texture(texture1, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(texture1, v_TexCoord));
	vec3 specular = light.specular * spec * vec3(texture(texture1, v_TexCoord));
	ambient *= attenuation;
	diffuse *= attenuation;
	specular *= attenuation;
	return vec3(ambient + diffuse + specular);
}

// calculates the color when using a spot light.
vec3 CalcSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
	vec3 lightDir = normalize(light.position - fragPos);
	// diffuse shading
	float diff = max(dot(normal, lightDir), 0.0);
	// specular shading
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 1);
	// attenuation
	float distance = length(light.position - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	// spotlight intensity
	float theta = dot(lightDir, normalize(-light.direction));
	float epsilon = light.cutOff - light.outerCutOff;
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);
	// combine results
	vec3 ambient = light.ambient * vec3(texture(texture1, v_TexCoord));
	vec3 diffuse = light.diffuse * diff * vec3(texture(texture1, v_TexCoord));
	//vec3 specular = light.specular * spec * vec3(texture(material.specular, TexCoords));
	ambient *= attenuation * intensity;
	diffuse *= attenuation * intensity;
	//specular *= attenuation * intensity;
	return (ambient + diffuse /*+ specular*/);
}