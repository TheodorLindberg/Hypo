#pragma once
#include "Hypo/3D/Renderer/RendererAPI.h"
#include "Hypo/3D/Exports.h"
namespace Hypo
{
	class HYPO_3D_API OpenGLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const Vec4F& color) override;
		void Clear(ClearFlags flags) override;
		void DrawIndexed(const VertexArray::Ptr& vertexArray, MeshType type) override;
		//void DrawInstanced(const BatchRendererBuffer::Ptr& batchRendererBuffer) override;
	private:
	};
}
