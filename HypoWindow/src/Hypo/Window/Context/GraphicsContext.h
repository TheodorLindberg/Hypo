#pragma once
#include "Hypo/Core.h"
#include "Hypo/Window/Context/RenderState.h"
#include "Hypo/Config.h"

namespace Hypo
{
	struct ContextSettings
	{
		explicit ContextSettings(unsigned int depth = 24, unsigned int stencil = 24, unsigned int antialiasing = 20, unsigned int major = 3, unsigned int minor = 3) :
			depthBits(depth),
			stencilBits(stencil),
			antialiasingLevel(antialiasing),
			majorVersion(major),
			minorVersion(minor)
		{}

		unsigned int depthBits;
		unsigned int stencilBits;
		unsigned int antialiasingLevel;
		unsigned int majorVersion;
		unsigned int minorVersion;

	};
	class GraphicsContext
	{
	public:
		virtual ~GraphicsContext() = default;
		virtual void SwapBuffers() = 0;
		virtual void SetActive(bool activate) = 0;

		virtual void LoadState(RendererState state) = 0;
		virtual RendererState RetrieveState() = 0;
		virtual void ResetState() = 0;

		virtual void EnableCullFace(CullFace cullFace = CullFace::Default) = 0;

		virtual void EnableBlending(BlendFunction blendFunc = BlendFunction::Default) = 0;

		//a count of 1 will enable GL_CLIP_PLANE0, and count will enable GL_CLIP_PLANE0 - GL_CLIP_PLANE3 in OpenGL
		virtual void EnableClipPlane(int count = 1) = 0;

		virtual void EnableDepthTest(bool enabled) = 0;

		virtual void EnableScissorTest(bool enabled) = 0;

		virtual void EnableStencilTest(bool enabled) = 0;

		virtual void EnableRawState(int state) = 0;
		virtual void DisableRawState(int state) = 0;

		virtual void SetScissorRect(RectI bounds) = 0;
		static std::unique_ptr<GraphicsContext> Create(void* window, const ContextSettings& contextSettings = ContextSettings());
	};

}