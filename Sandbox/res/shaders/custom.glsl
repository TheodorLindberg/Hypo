#version 330 core

#type vertex

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec2 a_TexCoord;

out vec2 TexCoord;

layout(std140) uniform Color
{
	vec4 color;
	float offset[3];
} offset;


void main()
{
   vec4 pos = vec4(aPos.x, aPos.y, aPos.z, 1.0);

gl_Position = pos;

	TexCoord = aTexCoord;
}

#type frag

out vec4 FragColor;

in vec2 TexCoord;

layout(std140) uniform Color
{
	vec4 color;
	float offset[3];
} color;



uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;

void main()
{
   FragColor = texture(ourTexture, TexCoord);   
   FragColor.r = color.color.r;

   if(TexCoord.x > 0.5f && TexCoord.y > 0.5f)
   {
	FragColor = texture(ourTexture2, TexCoord);  
   }

  // FragColor = vec4(TexCoord, 0, 1);
}