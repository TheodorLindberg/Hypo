#include "graphicspch.h"
#include "Hypo/Graphics/Shader/Shader.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Platform/OpenGL/OpenGLUniformBuffer.h"
#include "Hypo/Graphics/Texture/Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"

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

	Hypo::ObjPtr<Hypo::Texture2D> Hypo::Texture2D::Create(TextureData& data)
	{
		return new OpenGLTexture2D(data);
	}
}

