#include "graphicspch.h"
#include <gsl/span>
#include "Hypo/Graphics/Buffers.h"

#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "glad/glad.h"
#include "Platform/OpenGL/OpenGLIndexBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Hypo
{
	void init(void* ptr)
	{
		gladLoadGLLoader((GLADloadproc)ptr);
	}

	VertexBuffer::Ptr VertexBuffer::Create(gsl::span<const float> data, BufferUsage usage)
	{
		switch (usage)
		{
		case Hypo::BufferUsage::Static:
			return new OpenGLVertexBuffer(data);
			break;
		case Hypo::BufferUsage::Stream:
			return new OpenGLVertexBufferDynamic(data);
			break;
		case Hypo::BufferUsage::Dynamic:
			return new OpenGLVertexBufferDynamic(data);
			break;
		default:
			break;
		}
	}

	VertexBuffer::Ptr VertexBuffer::Create(unsigned size, BufferUsage usage )
	{
		switch (usage)
		{
		case Hypo::BufferUsage::Static:
			return new OpenGLVertexBuffer(size);
			break;
		case Hypo::BufferUsage::Stream:
			return new OpenGLVertexBufferDynamic(size);
			break;
		case Hypo::BufferUsage::Dynamic:
			return new OpenGLVertexBufferDynamic(size);
			break;
		default:
			break;
		}
	}
	

	IndexBuffer::Ptr IndexBuffer::Create(gsl::span<const ElementIndex> data, BufferUsage usage)
	{
		return new OpenGLIndexBuffer(data);
	}

	IndexBuffer::Ptr IndexBuffer::Create(unsigned size, BufferUsage usage)
	{
		return new OpenGLIndexBuffer(size);
	}

	VertexArray::Ptr VertexArray::Create()
	{
		return new OpenGLVertexArray();	
	}
}
