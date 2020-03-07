#pragma once
#include "Hypo/Graphics/Exports.h"
#include "Hypo/Graphics/Buffers.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Hypo
{
	class HYPO_GRAPHICS_API OpenGLIndexBuffer : public IndexBuffer
	{
	protected:
		OpenGLIndexBuffer() = default;
	public:
		OpenGLIndexBuffer(uInt32 size);
		OpenGLIndexBuffer(gsl::span<const ElementIndex> data);

		void Update(gsl::span<const ElementIndex> data, uInt32 offset) override {};
		void Bind() override;
		void Unbind() override;
		uInt32 GetCount() const override { return m_Count; };
	protected:
		uInt32 m_Count;
		OpenGLBuffer m_Buffer;
	};
	
	class HYPO_GRAPHICS_API OpenGLIndexBufferDynamic : public OpenGLIndexBuffer
	{
	public:
		OpenGLIndexBufferDynamic(uInt32 size);
		OpenGLIndexBufferDynamic(gsl::span<const ElementIndex> data);

		void Update(gsl::span<const ElementIndex> data, uInt32 offset) override;
	};
}
