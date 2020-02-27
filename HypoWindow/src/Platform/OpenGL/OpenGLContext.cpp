#include "windowpch.h"
#include "glad/glad.h"

#include "../../HypoWindow/vendor/GLFW/include/GLFW/glfw3.h"

#include "Hypo/Util/Log.h"
#include "OpenGLContext.h"

namespace Hypo
{
	void GLAPIENTRY
		MessageCallback(GLenum source,
			GLenum type,
			GLuint id,
			GLenum severity,
			GLsizei length,
			const GLchar* message,
			const void* userParam)
	{
		if (severity == 0x9146/* DEBUG_SEVERITY_HIGH */) {
			HYPO_CORE_CRITICAL("GL Critical Error: type = {0}, message = {1}", type, message);
		}
		else if (severity == 0x9147 /* DEBUG_SEVERITY_MEDIUM */) {
			HYPO_CORE_ERROR("GL Error: type = {0}, message = {1}", type, message);
		}
		else if (severity == 0x9148 /* DEBUG_SEVERITY_LOW */) {
			HYPO_CORE_WARN("GL Warning: type = {0}, message = {1}", type, message);
		}
		else if (severity == 0x826B /* DEBUG_SEVERITY_NOTIFICATION */) {
			HYPO_CORE_DEBUG("GL Notification: type = {0}, message = {1}", type, message);

		}
	}
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window, const ContextSettings& contextSettings)
	{
		auto* context = new OpenGLContext(reinterpret_cast<GLFWwindow*>(window));
		context->Init(contextSettings);
		return std::unique_ptr<GraphicsContext>(reinterpret_cast<GraphicsContext*>(context));
	}

	OpenGLContext::OpenGLContext(GLFWwindow* window)
		: m_WindowHandle(window)
	{
	}

	OpenGLContext::~OpenGLContext()
	{

	}
	void OpenGLContext::LoadState(RendererState state)
	{
		EnableCullFace(state.Culling);
		EnableBlending(state.Blending);
		EnableDepthTest(state.DepthTest);
		EnableStencilTest(state.StencilTest);
		EnableScissorTest(state.ScissorTest);
		EnableClipPlane(state.ClipPlaneCount);
	}

	RendererState OpenGLContext::RetrieveState()
	{
		return m_GLState;
	}


	void OpenGLContext::ResetState()
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		glEnable(GL_DEPTH_TEST);

		glDisable(GL_BLEND);
		glDisable(GL_SCISSOR_TEST);
		glDisable(GL_STENCIL_TEST);

		m_GLState = RendererState(CullFace::Back, BlendFunction::Disabled, true, false, false, 0);
	}

	void OpenGLContext::EnableCullFace(CullFace cullFace)
	{
		if (m_GLState.Culling != cullFace)
		{
			if (cullFace == CullFace::Disabled && m_GLState.Culling != CullFace::Disabled)
			{
				glDisable(GL_CULL_FACE);
			}
			else if (cullFace != CullFace::Disabled && m_GLState.Culling == CullFace::Disabled)
			{
				glEnable(GL_CULL_FACE);
				int mode = 0;
				switch (cullFace)
				{
				case CullFace::Front:
					mode = GL_FRONT;
				case CullFace::Back:
					mode = GL_BACK;
				case CullFace::FrontAndBack:
					mode = GL_FRONT_AND_BACK;
					break;
				default: HYPO_CORE_ASSERT(false, "Invalid cullFace State!");
				}
				glCullFace(mode);
			}
			m_GLState.Culling = cullFace;
		}
	}

	void OpenGLContext::EnableBlending(BlendFunction blendFunc)
	{
		if (m_GLState.Blending != blendFunc)
		{
			if (blendFunc == BlendFunction::Disabled && m_GLState.Blending != BlendFunction::Disabled)
			{
				glDisable(GL_BLEND);
			}
			else if (blendFunc != BlendFunction::Disabled && m_GLState.Blending == BlendFunction::Disabled)
			{
				glEnable(GL_BLEND);
				int mode = 0;
				switch (blendFunc)
				{
				case BlendFunction::One:
					mode = GL_ONE;
					break;

				case BlendFunction::OneMinusSrcAlpha:
					mode = GL_ONE_MINUS_SRC_ALPHA;
					break;
				default:;
				}
				glBlendFunc(GL_SRC_ALPHA, mode);
			}
			m_GLState.Blending = blendFunc;
		}
	}

	void OpenGLContext::EnableClipPlane(int count)
	{
		if (m_GLState.ClipPlaneCount != count)
		{
			if (m_GLState.ClipPlaneCount < count)
			{
				for (int i = m_GLState.ClipPlaneCount; i < count; i++)
				{
					glEnable(GL_CLIP_DISTANCE0 + i);
				}
			}
			else
			{
				for (int i = count; i < m_GLState.ClipPlaneCount; i++)
				{
					glDisable(GL_CLIP_DISTANCE0 + i);
				}
			}
		}
	}

	void OpenGLContext::EnableDepthTest(bool enabled)
	{
		if (m_GLState.DepthTest && !enabled)
		{
			glDisable(GL_DEPTH_TEST);
		}
		else if (!m_GLState.DepthTest && enabled)
		{
			glEnable(GL_DEPTH_TEST);
		}
	}

	void OpenGLContext::EnableScissorTest(bool enabled)
	{
		if (m_GLState.ScissorTest && !enabled)
		{
			glDisable(GL_SCISSOR_TEST);
		}
		else if (!m_GLState.ScissorTest && enabled)
		{
			glEnable(GL_SCISSOR_TEST);
		}
	}

	void OpenGLContext::EnableStencilTest(bool enabled)
	{
		if (m_GLState.StencilTest && !enabled)
		{
			glDisable(GL_STENCIL_TEST);
		}
		else if (!m_GLState.StencilTest && enabled)
		{
			glEnable(GL_STENCIL_TEST);
		}
	}

	void OpenGLContext::EnableRawState(int state)
	{
		glEnable(state);
	}

	void OpenGLContext::DisableRawState(int state)
	{
		glDisable(state);
	}

	void OpenGLContext::SetScissorRect(Hypo::RectI clip)
	{
		int height;
		glfwGetWindowSize(m_WindowHandle, nullptr, &height);
		glScissor(clip.left, height - clip.GetHeight() - clip.top, clip.GetWidth(), clip.GetHeight());
	}

	void OpenGLContext::Init(const ContextSettings& contextSettings)
	{
		SetActive(true);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextSettings.majorVersion);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextSettings.minorVersion);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		HYPO_CORE_ASSERT(status, "Failed to initialize Glad!");

		HYPO_CORE_INFO("OpenGL Info:");
		HYPO_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
		HYPO_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		HYPO_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));

		// During init, enable debug output
		glEnable(GL_DEBUG_OUTPUT);
		glDebugMessageCallback(MessageCallback, 0);
	}

	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}

	void OpenGLContext::SetActive(bool activate)
	{
		if (activate)
		{
			glfwMakeContextCurrent(m_WindowHandle);
		}
	}
}

