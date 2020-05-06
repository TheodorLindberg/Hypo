#pragma once
#include "Hypo/Graphics/Exports.h"

#include "Hypo/Graphics/Buffers.h"
#include "Hypo/Graphics/Shader/Shader.h"
#include "Hypo/3D/Model/Mesh.h"

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

		void AddVertexBuffer(VertexBuffer::Ptr buffer) override;
		bool HasIndexBuffer() override { return m_IndexBuffer; };
		uInt32 GetIndicesCount();
		void SetMeshType(MeshType type) override { m_Type = type; };
		MeshType GetMeshType() override { return m_Type; };
	private:
		friend class OpenGLShader;
		MeshType m_Type = MeshType::Triangles;
		std::vector<VertexBuffer::Ptr> m_Buffers;
		IndexBuffer::Ptr m_IndexBuffer;
		uInt32 m_RendererID;
	};
}
