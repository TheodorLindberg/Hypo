#version 330 core

#type vertex

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec3 a_Color;

out vec3 v_Color;


void main()
{
	vec4 pos = vec4(a_Position.x, a_Position.y, 0, 1.0);

	gl_Position = pos;
	v_Color = a_Color;
}

#type frag

out vec4 FragColor;

in vec3 v_Color;

void main()
{
	FragColor = vec4(v_Color, 1.f);
}