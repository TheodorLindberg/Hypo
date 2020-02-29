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
		
		void Update(gsl::span<float> data, uInt32 offset) override {};
		
		BufferLayout GetLayout() override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

		void Bind() override;
		void Unbind() override;
	protected:
		OpenGLVertexBuffer() = default;
		BufferLayout m_Layout;
		OpenGLBuffer m_Buffer;
	};

	class HYPO_GRAPHICS_API OpenGLVertexBufferDynamic : public OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBufferDynamic(uInt32 size);
		OpenGLVertexBufferDynamic(gsl::span<float> data);

		void Update(gsl::span<float> data, uInt32 offset) override;
	};

}
