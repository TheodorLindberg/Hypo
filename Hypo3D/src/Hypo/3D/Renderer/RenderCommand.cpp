#include "hypo3dpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

#include "RendererAPI.h"

namespace Hypo
{
	RendererAPI* RenderCommand::s_RendererAPI = new Hypo::OpenGLRendererAPI();
}