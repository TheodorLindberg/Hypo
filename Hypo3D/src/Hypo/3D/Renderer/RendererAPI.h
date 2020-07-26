#pragma once
#include "Hypo/3D/Exports.h"
#include "Hypo/Graphics/Buffers.h"
#include "Hypo/3D/Model/Mesh.h"

namespace Hypo
{


	class HYPO_3D_API RendererAPI
	{
	public:
		enum class API
		{
			None = 0, OpenGL = 1,
		};
		enum ClearCommands
		{
			CLEAR_NONE = BIT(0),
			CLEAR_DEPTH = BIT(1),
			CLEAR_COLOR = BIT(2),
			CLEAR_STENCIL = BIT(3)
		};
		using ClearFlags = uInt16;
	public:
		virtual ~RendererAPI() = default;
		virtual void SetClearColor(const Vec4F& color) = 0;
		virtual void Clear(ClearFlags flags) = 0;

		virtual void DrawIndexed(VertexArray::Ptr& vertexArray, MeshType type = MeshType::Triangles) = 0;
		static API GetAPI();;
	private:
		static API s_API;
	};
}