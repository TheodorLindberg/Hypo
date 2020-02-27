#version 440 core
#name Default

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

in vec2 v_TexCoord;		
in vec3 v_Position;

uniform sampler2D texture1;

layout(std140) uniform BlobSettings {
	float RadiusInner;
	vec4 InnerColor;
	float RadiusOuter;
	vec4 OuterColor;	
};



void main()
{	
	float dx = v_TexCoord.x  - 0.5;
	float dy = v_TexCoord.y -0.5;
	float dist = sqrt(dx * dx + dy * dy);
	color = mix( InnerColor, OuterColor, smoothstep( RadiusInner, RadiusOuter, dist ));
	
}