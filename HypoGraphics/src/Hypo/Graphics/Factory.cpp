#include "graphicspch.h"
#include "Hypo/Graphics/Shader/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hypo
{
	Shader::Ptr Shader::Create(const ShaderData& data)
	{
		return new OpenGLShader(data);
	}
}
