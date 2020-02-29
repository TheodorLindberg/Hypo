#pragma once
#include "Hypo/Graphics/Exports.h"

#include "Hypo/Graphics/Buffers.h"
#include "Hypo/Graphics/Shader/Shader.h"

namespace Hypo
{
	class HYPO_GRAPHICS_API OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		~OpenGLVertexArray();
		void Bind() const override;
		void Unbind() const override;

		void AddVertexBuffer(VertexBuffer::Ptr buffer, Shader::Ptr shader) override;
		void SetIndexBuffer(IndexBuffer::Ptr buffer) override;
		bool CheckAttributes(Shader::Ptr shader);
		IndexBuffer::Ptr GetIndexBuffer() const override;

	private:
		friend class OpenGLShader;
		std::vector<VertexBuffer::Ptr> m_Buffers;
		IndexBuffer::Ptr m_IndexBuffer;
		uInt32 m_RendererID;
	};
}
