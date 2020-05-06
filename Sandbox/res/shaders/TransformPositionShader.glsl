	#version 440 core
#name BasicColor

#type Vertex

in layout(location = 0) vec3 a_Position;

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

}

#type Fragment

out vec4 frag_Color;

layout(std140) uniform SingleColor
{
	vec4 u_Color;
};

void main()
{
	frag_Color = u_Color;
}