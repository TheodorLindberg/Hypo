#pragma once
#include "Hypo/Core.h"

namespace Hypo
{

	enum class CullFace
	{
		Disabled = 0,
		Front,
		Back,
		FrontAndBack,
		Default = Back //Default for OpenGL
	};
	enum class BlendFunction
	{
		Disabled = 0,
		One,
		OneMinusSrcAlpha,
		Default = OneMinusSrcAlpha
	};
	struct RendererState
	{
		CullFace Culling;
		BlendFunction Blending;
		bool DepthTest;
		bool ScissorTest;
		bool StencilTest;

		//a ClipPlaneCount of 1 will enable GL_CLIP_PLANE0, and ClipPlaneCount4 will enable GL_CLIP_PLANE0 - GL_CLIP_PLANE3
		int ClipPlaneCount;

		RendererState(CullFace cullFace = CullFace::Default,
			BlendFunction blending = BlendFunction::Default,
			bool depthTest = true,
			bool scissorTest = false,
			bool stencilTest = false,
			int clipPlaneCount = 0)
			: Culling(cullFace), Blending(blending), DepthTest(depthTest), ScissorTest(scissorTest), StencilTest(stencilTest), ClipPlaneCount(clipPlaneCount)

		{}
	};
}