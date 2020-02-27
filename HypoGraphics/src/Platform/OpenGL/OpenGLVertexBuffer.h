#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/Graphics/Buffers.h"
#include "Platform/OpenGL/OpenGLBuffer.h"
namespace Hypo
{
	class HYPO_GRAPHICS_API OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(uInt32 size);
		OpenGLVertexBuffer(gsl::span<float> data);
		
		void Update(gsl::span<float> data, uInt32 offset) override;
		void Bind() override;
		void Unbind() override;
	private:	
		OpenGLBuffer m_Buffer;
	};
}
