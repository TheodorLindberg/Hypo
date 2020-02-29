#include "hypo3dpch.h"
#include "RendererAPI.h"

namespace Hypo
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::OpenGL;

	RendererAPI::API RendererAPI::GetAPI()
	{
		return s_API;
	}
}
