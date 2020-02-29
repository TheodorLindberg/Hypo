#include "hypo3dpch.h"
#include "OpenGLRendererAPI.h"
#include "glad/glad.h"
#include "Hypo/System/Util/Log.h"


namespace Hypo
{
		
	void OpenGLRendererAPI::SetClearColor(const Vec4F& color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::Clear(ClearFlags flags)
	{
		unsigned int openGLFlags = 0;

		if(flags & ClearCommands::CLEAR_COLOR)
		{
			openGLFlags |= GL_COLOR_BUFFER_BIT;
		}
		if (flags & ClearCommands::CLEAR_STENCIL)
		{
			openGLFlags |= GL_STENCIL_BUFFER_BIT;
		}
		if (flags & ClearCommands::CLEAR_DEPTH)
		{
			openGLFlags |= GL_DEPTH_BUFFER_BIT;
		}
		glClear(openGLFlags);
	}

	void OpenGLRendererAPI::DrawIndexed(const VertexArray::Ptr& vertexArray, MeshType type)
	{
		int mode = 0;
		switch(type)
		{
		case MeshType::Triangles:
			mode = GL_TRIANGLES; break;
		case MeshType::TriangleFan:
			mode = GL_TRIANGLE_FAN; break;
		case MeshType::TriangleStrip:
			mode = GL_TRIANGLE_STRIP; break;
		case MeshType::Quads:
			mode = GL_QUADS; break;
		case MeshType::Lines:	
			mode = GL_LINES; break;
		case MeshType::LineStrip:
			mode = GL_LINE_STRIP; break;
		case MeshType::Points: 
			mode = GL_POINTS;  break;
		default: mode = -1;
			HYPO_CORE_ERROR("Warning unvalid mesh type, skipping render call"); return;
		}

		glDrawElements(mode, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}
	/*
	void OpenGLRendererAPI::DrawInstanced(const BatchRendererBuffer::Ptr& batchRendererBuffer)
	{
		batchRendererBuffer.Cast<OpenGLBatchRendererBuffer>()->Render();
	}*/

}
