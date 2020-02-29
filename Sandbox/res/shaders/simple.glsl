#version 330 core

#type vertex

layout (location = 0) in vec3 aPos;
layout (location = 0) in vec2 aTexCoord;

out vec2 TexCoord;

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