#include "graphicspch.h"
#include "OpenGLVertexArray.h"
#include "glad/glad.h"
#include "Hypo/System/Util/Log.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hypo
{

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Float:    return GL_FLOAT;
		case ShaderDataType::Float2:   return GL_FLOAT;
		case ShaderDataType::Float3:   return GL_FLOAT;
		case ShaderDataType::Float4:   return GL_FLOAT;
		case ShaderDataType::Mat3:     return GL_FLOAT;
		case ShaderDataType::Mat4:     return GL_FLOAT;
		case ShaderDataType::Int:      return GL_INT;
		case ShaderDataType::Int2:     return GL_INT;
		case ShaderDataType::Int3:     return GL_INT;
		case ShaderDataType::Int4:     return GL_INT;
		case ShaderDataType::Bool:     return GL_BOOL;
		}

		HYPO_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}


	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer::Ptr buffer, Shader::Ptr shader)
	{
		glBindVertexArray(m_RendererID);
		buffer->Bind();

		const auto& layout = buffer->GetLayout();
		int stride = layout.GetStride();

		if(layout.GetElements().size() == 0)
		{
			HYPO_CORE_ERROR("[OpenGL] VertexBuffer::AddVertexBuffer, buffer without valid layout supplied, no attribute will be bound");
			return;
		}
		
		OpenGLShader* openGLShader = shader.Cast<OpenGLShader>();
		
		for (const auto& element : layout)
		{
			int location = openGLShader->GetAttributeLocation(element.Name);

			if (location == -1) HYPO_CORE_ERROR("Invalid attribute {}", element.Name);
			
			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				stride,
				reinterpret_cast<void*>(static_cast<uInt64>(element.Offset)));
		}
		m_Buffers.push_back(buffer);
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer::Ptr buffer)
	{
		glBindVertexArray(m_RendererID);
		buffer->Bind();
		m_IndexBuffer = buffer;
		glBindVertexArray(0);
	}

	IndexBuffer::Ptr OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}

}
