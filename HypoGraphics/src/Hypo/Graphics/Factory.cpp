#include "graphicspch.h"
#include "Hypo/Graphics/Shader/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"

namespace Hypo
{
	Shader::Ptr Shader::Create(const ShaderData& data)
	{
		return new OpenGLShader(data);
	}

	Hypo::UniformBuffer::Ptr Hypo::UniformBuffer::Create(UniformBinder::Ptr& binder)
	{
		return new OpenGLUniformBuffer(binder);
	}
}

