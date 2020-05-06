#version 330 core

#type vertex

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

layout(std140) uniform Transform
{
	mat4 u_ProjectionViewMatrix;
	mat4 u_ViewMatrix;
	mat4 u_ModelMatrix;
	vec3 u_ViewPos;
};


void main()
{
	vec4 position = u_ProjectionViewMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
	gl_Position = position;

	v_TexCoord = a_TexCoord;
}

#type frag

out vec4 FragColor;


in vec2 v_TexCoord;


uniform sampler2D texture1;

void main()
{
	FragColor = texture(texture1, v_TexCoord);
}