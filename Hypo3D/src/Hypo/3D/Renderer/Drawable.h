#pragma once
#include <Hypo/Graphics/Shader/Shader.h>
namespace Hypo
{
	class Drawable
	{
	public:
		virtual void Submit() = 0;
		virtual Shader::Ptr& GetShader() = 0;
	private:

	};
}