#version 330 core

#type vertex

layout (location = 0) in vec3 aPos;

layout(std140) uniform Color
{
	vec4 color;
	float offset[3];
} offset;


void main()
{
   vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);

   pos.x += offset.offset[0];
   pos.x += offset.offset[1] * 0.5;
   pos.x += offset.offset[2] * 0.1;
	gl_Position = pos;
}

#type frag

out vec4 FragColor;

layout(std140) uniform Color
{
	vec4 color;
	float offset[3];
} color;

void main()
{
   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
   FragColor = color.color;
   
}