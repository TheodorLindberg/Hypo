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
		OpenGLVertexBuffer(gsl::span<const float> data);
		
		void Update(gsl::span<const float> data, uInt32 offset) override {};
		
		BufferLayout GetLayout() override { return m_Layout; }
		void SetLayout(const BufferLayout& layout) override { m_Layout = layout; m_IndicesCount = m_Buffer.GetBufferSize() / layout.GetStride(); }

		void Bind() override;
		void Unbind() override;
		uInt32 GetIndicesCount() { return m_IndicesCount; };
	protected:
		OpenGLVertexBuffer() = default;
		uInt32 m_IndicesCount;
		
		BufferLayout m_Layout;
		OpenGLBuffer m_Buffer;
	};

	class HYPO_GRAPHICS_API OpenGLVertexBufferDynamic : public OpenGLVertexBuffer
	{
	public:
		OpenGLVertexBufferDynamic(uInt32 size);
		OpenGLVertexBufferDynamic(gsl::span<const float> data);

		void Update(gsl::span<const float> data, uInt32 offset) override;
	};

}
