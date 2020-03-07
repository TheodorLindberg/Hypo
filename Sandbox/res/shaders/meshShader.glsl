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
    
    gl_Position = transform.u_ProjectionViewMatrix  * vec4(v_Position, 1.0);
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

layout(std140) uniform Light {
	vec3 color;
	vec3 position;
} light;


void main()
{	


//	float dx = v_TexCoord.x  - 0.5;
//	float dy = v_TexCoord.y -0.5;
//	float dist = sqrt(dx * dx + dy * dy);
//	color = mix( InnerColor, OuterColor, smoothstep( RadiusInner, RadiusOuter, dist ));
	color = texture(texture1, v_TexCoord);
	
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * light.color;
  	
    // diffuse 
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(light.position - v_Position);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * light.color;
    
    // specular
    float specularStrength = 1;
    vec3 viewDir = normalize(transform.u_ViewPos - v_Position);
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * light.color;  
        
    color = vec4(ambient + diffuse + specular, 1) * color;
	//color = vec4(light.color, 1);
	//color = vec4(transform.u_ViewPos, 1);
}