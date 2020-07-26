#pragma once
#include "RendererAPI.h"

namespace Hypo
{
	class HYPO_3D_API RenderCommand
	{
	public:
		static inline void Clear(RendererAPI::ClearFlags flags)
		{
			s_RendererAPI->Clear(flags);
		}
		static inline void SetClearColor(Vec4F color)
		{
			s_RendererAPI->SetClearColor(color);
		}
		static inline void DrawIndexed(VertexArray::Ptr& vertexArray, MeshType type = MeshType::Triangles)
		{
			s_RendererAPI->DrawIndexed(vertexArray, type);
		}
		/*static inline void DrawInstanced(const BatchRendererBuffer::Ptr& batchRenderBuffer)
		{
			s_RendererAPI->DrawInstanced(batchRenderBuffer);
		}*/
	private:
		static RendererAPI* s_RendererAPI;
	};

}