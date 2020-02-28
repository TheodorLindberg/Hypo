#include "graphicspch.h"
#include "OpenGLUniformBuffer.h"

#include "glad/glad.h"
#include "Hypo/System/Util/Log.h"

namespace Hypo
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(UniformBinder::Ptr& binder)
		: m_Binder(binder)
	{
		m_Buffer.LoadEmpty<GL_UNIFORM_BUFFER>(binder->GetBufferSize(), true);
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
	}

	const std::string& OpenGLUniformBuffer::GetBinderName()
	{
		return m_Binder->GetName();
	}


	bool OpenGLUniformBuffer::Set(const char* name, int value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(int));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, int value1, int value2)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int2); offset != -1)
		{
			Vec2F vec{ value1, value2 };
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec2F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, int value1, int value2, int value3)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int3); offset != -1)
		{
			Vec3F vec(value1, value2, value3);
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec3F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, int value1, int value2, int value3, int value4)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int4); offset != -1)
		{
			Vec4F vec(value1, value2, value3, value4);
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec4F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, Vec2I value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int2); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec2I));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, Vec3I& value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int3); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec3I));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, Vec4I& value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int4); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec4I));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, float value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(float));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, float value1, float value2)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float2); offset != -1)
		{
			Vec2F vec{ value1, value2 };
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec2F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, float value1, float value2, float value3)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float3); offset != -1)
		{
			Vec3F vec{ value1, value2, value3 };
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec3F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, float value1, float value2, float value3, float value4)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float4); offset != -1)
		{
			Vec4F vec{ value1, value2, value3, value4 };
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec4F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, Vec2F value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float2); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec2F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, Vec3F& value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float3); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec3F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, Vec4F& value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float4); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec4F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, bool value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Bool); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(bool));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, const glm::mat3& value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Mat3); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value[0][0], sizeof(glm::mat3));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, const glm::mat4& value)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Mat4); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value[0][0], sizeof(glm::mat4));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::Set(const char* name, Byte* data, int size)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Struct); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, data, size);
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, int value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(int));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, int value1, int value2, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int2, index); offset != -1)
		{
			Vec2I vec{ value1, value2 };
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec2I));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, int value1, int value2, int value3, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int3, index); offset != -1)
		{
			Vec3I vec(value1, value2, value3);
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec3I));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, int value1, int value2, int value3, int value4, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int4, index); offset != -1)
		{
			Vec4I vec(value1, value2, value3, value4);
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec4I));
			return true;
			HYPO_CORE_INFO("Could not bind uniform {}", name);
		}
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, Vec2I value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int2, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec2I));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, Vec3I& value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int3, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec3I));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, Vec4I& value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Int4, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec4I));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, float value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(float));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, float value1, float value2, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float2, index); offset != -1)
		{
			Vec2F vec(value1, value2);
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec2F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, float value1, float value2, float value3, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float3, index); offset != -1)
		{
			Vec3F vec{ value1, value2, value3 };
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec3F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, float value1, float value2, float value3, float value4,
		int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float4, index); offset != -1)
		{
			Vec4F vec{ value1, value2, value3, value4 };
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &vec, sizeof(Vec4F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, Vec2F value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float2, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec2F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, Vec3F& value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float3, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec3F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, Vec4F& value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Float4, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(Vec4F));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, bool value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Bool, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(bool));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, const glm::mat3& value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Mat3, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(glm::mat3));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, const glm::mat4& value, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Mat4, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, &value, sizeof(glm::mat4));
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

	bool OpenGLUniformBuffer::SetArray(const char* name, Byte* data, int size, int index)
	{
		if (const auto offset = m_Binder->GetUniformOffset(name, ShaderDataType::Struct, index); offset != -1)
		{
			m_Buffer.Update<GL_UNIFORM_BUFFER>( offset, data, size);
			return true;
		}
		HYPO_CORE_INFO("Could not bind uniform {}", name);
		return false;
	}

}
