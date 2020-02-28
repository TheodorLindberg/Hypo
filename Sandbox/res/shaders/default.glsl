#version 440 core
#name Light

#type Vertex

in layout(location = 0) vec3 a_Position;
in layout(location = 1) vec2 a_TexCoord;

out vec2 v_TexCoord;
out vec3 v_Position;

layout(std140) uniform Transform
{ 
	mat4 u_ProjectionViewMatrix;
	mat4 u_ViewMatrix;
	mat4 u_ModelMatrix;
} transform;

void main()
{
	vec4 position = transform.u_ProjectionViewMatrix * transform.u_ModelMatrix * vec4(a_Position, 1.0);
	v_Position = vec3(position);
	gl_Position = position;
	v_TexCoord = a_TexCoord;

}

#type Fragment

out vec4 color;

layout(std140) uniform Light
{ 
	mat4 data;
	float u_Color[5];
	vec4 u_Diffuse[2];
	mat4 mat[5];
	float first;
	float second;
	float thierd;
} lights[10];

void main()
{	

	color = vec4(1,1,1,1) * lights[0].data;
	for(int i = 0; i < 10; i++) {
		color += vec4(lights[i].u_Color[0],1,1,1) * vec4(lights[i].u_Color[1],1,1,1) * lights[i].u_Diffuse[0]* lights[i].u_Diffuse[1];
	}
}