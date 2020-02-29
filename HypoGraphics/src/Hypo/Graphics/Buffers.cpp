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

	VertexBuffer::Ptr VertexBuffer::Create(gsl::span<float> data, bool dynamic)
	{
		return new OpenGLVertexBuffer(data);
	}

	VertexBuffer::Ptr VertexBuffer::Create(unsigned size, bool dynamic)
	{
		return new OpenGLVertexBuffer(size);
	}
	

	IndexBuffer::Ptr IndexBuffer::Create(gsl::span<ElementIndex> data, bool dynamic)
	{
		return new OpenGLIndexBuffer(data);
	}

	IndexBuffer::Ptr IndexBuffer::Create(unsigned size, bool dynamic)
	{
		return new OpenGLIndexBuffer(size);
	}

	VertexArray::Ptr VertexArray::Create()
	{
		return new OpenGLVertexArray();	
	}
}
