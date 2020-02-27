#include "graphicspch.h"
#include <gsl/span>
#include "Hypo/Graphics/Buffers.h"

#include "Platform/OpenGL/OpenGLVertexBuffer.h"
#include "glad/glad.h"

namespace Hypo
{
	void init(void* ptr)
	{
		gladLoadGLLoader((GLADloadproc)ptr);
	}

	VertexBuffer::Ptr VertexBuffer::Create(gsl::span<float> data, bool dynamic)
	{
		return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(data));
	}

	VertexBuffer::Ptr VertexBuffer::Create(unsigned size, bool dynamic)
	{
		return std::shared_ptr<VertexBuffer>(new OpenGLVertexBuffer(size));
	}
}
