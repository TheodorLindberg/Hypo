#pragma once
#include "Hypo/Core.h"
#include "Hypo/Context/GraphicsContext.h"
#include "../../../../HypoWindow/vendor/GLFW/include/GLFW/glfw3.h"


namespace Hypo
{
	class OpenGLContext : public GraphicsContext
	{

	public:
		OpenGLContext(GLFWwindow* window);
		~OpenGLContext();

		void Init(const ContextSettings& contextSettings);
		void SwapBuffers() override;
		void SetActive(bool activate) override;


		void LoadState(RendererState state) override;
		RendererState RetrieveState() override;
		void ResetState() override;

		void EnableCullFace(CullFace cullFace) override;
		void EnableBlending(BlendFunction blendFunc) override;

		void EnableClipPlane(int count) override;
		void EnableDepthTest(bool enabled) override;
		void EnableScissorTest(bool enabled) override;
		void EnableStencilTest(bool enabled) override;
		void EnableRawState(int state) override;
		void DisableRawState(int state) override;
		void SetScissorRect(RectI clip) override;
	private:
		GLFWwindow* m_WindowHandle;

		RendererState m_GLState;
	};
}
