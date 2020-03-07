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
		return new OpenGLVertexBuffer(data);
	}

	VertexBuffer::Ptr VertexBuffer::Create(unsigned size, BufferUsage usage )
	{
		return new OpenGLVertexBuffer(size);
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
