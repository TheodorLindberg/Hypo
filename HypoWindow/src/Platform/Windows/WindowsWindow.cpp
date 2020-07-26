#include "windowpch.h"

#include "WindowsWindow.h"
#include <GLFW/glfw3.h>

#include "Platform/OpenGL/OpenGLContext.h"
#include "Hypo/System/Util/Log.h"

namespace Hypo
{
	Window* Window::m_ActiveWindow = nullptr;

	static bool s_GLFWInitialized = false;

	static void GLFWErrorCallback(int error, const char* description)
	{
		HYPO_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	Window* Window::Create(const WindowProps& props, const ContextSettings& contextSettings)
	{
		auto* window = new WindowsWindow(props, contextSettings);
		Window::m_ActiveWindow = window;
		return window;
	}

	WindowsWindow::WindowsWindow(const WindowProps& props, const ContextSettings& contextSettings)
		: m_EventFlowControl([this](Event& data)->bool { this->PushEvent(data); return true; })
	{
		Init(props, contextSettings);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Display()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	unsigned WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	unsigned WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	unsigned WindowsWindow::GetLeft() const
	{
		int x;
		glfwGetWindowPos(m_Window, &x, nullptr);
		return x;
	}

	unsigned WindowsWindow::GetTop() const
	{
		int y;
		glfwGetWindowPos(m_Window, nullptr, &y);
		return y;
	}

	Vec2U WindowsWindow::GetSize() const
	{
		int width, height;
		glfwGetWindowSize(m_Window, &width, &height);
		return Vec2U{ width,height };
	}

	Vec2I WindowsWindow::GetPosition() const
	{
		int x, y;
		glfwGetWindowPos(m_Window, &x, &y);
		return Vec2I{x,y};
	}

	RectI WindowsWindow::GetViewRect() const
	{
		return RectFromSize<int>(GetPosition(), Vec2I{ GetSize() });
	}

	void WindowsWindow::SetSize(Vec2U newSize)
	{
		glfwSetWindowSize(m_Window, newSize.x, newSize.y);
	}

	void WindowsWindow::SetPosition(Vec2I newPosition)
	{
		glfwSetWindowPos(m_Window, newPosition.x, newPosition.y);
	}

	void WindowsWindow::SetTitle(const std::string& title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
	}

	void WindowsWindow::SetEventCallback(const EventCallbackFn& callback)
	{
		m_Data.EventCallback = callback;
	}

	bool WindowsWindow::PollEvent(Event& event)
	{
		if (m_EventQueue.empty())
		{
			event = Event(EventType::None, EventCategoryNone);
			return false;
		}
		else {
			event = m_EventQueue.front();
			m_EventQueue.pop();
			return true;
		}
	}

	void WindowsWindow::EnablePollEvent(bool enabled)
	{
		m_Data.PushEventToStack = enabled;
	}

	bool WindowsWindow::PollEventEnabled() const
	{
		return m_Data.PushEventToStack;
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}

	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}

	void* WindowsWindow::GetGladProc()
	{
		return glfwGetProcAddress;
	}

	void WindowsWindow::PushEvent(Event& event)
	{
		if (m_Data.PushEventToStack)
			m_EventQueue.push(event);

		if (m_Data.EventCallback)
			m_Data.EventCallback(event);
	}

	void  WindowsWindow::Init(const WindowProps& props, const ContextSettings& contextSettings)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;
		m_Data.eventQueue = &m_EventQueue;
		m_Data.window = this;
		m_Data.PushEventToStack = true;

		HYPO_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);
		if (!s_GLFWInitialized)
		{
			// TODO: glfwTerminate on system shutdown
			int success = glfwInit();
			HYPO_CORE_ASSERT(success, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}
		m_Window = glfwCreateWindow((int)m_Data.Width, (int)m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);

		if(!m_Window)
		{
			HYPO_CORE_CRITICAL("Could not create window!");
		}
		m_Context = GraphicsContext::Create(m_Window);

	
		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		InitEventCallbacks();
	}
	void WindowsWindow::InitEventCallbacks()
	{
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				data.Width = width;
				data.Height = height;

				Event e(EventType::WindowResize, EventCategoryWindow);
				e.windowResize = WindowResizeEvent(width, height);
				data.window->GetEventFlowControl().In(e);
				
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				Event e(EventType::WindowClose, EventCategoryWindow);
				data.window->GetEventFlowControl().In(e);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				switch (action)
				{
				case GLFW_PRESS:
				{
					Event e(EventType::KeyPressed, EventCategoryInput | EventCategoryKeyboard);
					e.key = KeyEvent(key, scancode, mods);
					data.window->GetEventFlowControl().In(e);
					break;
				}
				case GLFW_RELEASE:
				{
					Event e(EventType::KeyReleased, EventCategoryInput | EventCategoryKeyboard);
					e.key = KeyEvent(key, scancode, mods);
					data.window->GetEventFlowControl().In(e);
					break;
				}
				case GLFW_REPEAT:
				{
					Event e(EventType::KeyPressed, EventCategoryInput | EventCategoryKeyboard);
					e.key = KeyEvent(key, scancode, mods);
					data.window->GetEventFlowControl().In(e);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				Event e(EventType::KeyTyped, EventCategoryInput | EventCategoryKeyboard);
				e.text = TextEvent(keycode);
				data.window->GetEventFlowControl().In(e);

			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));
				
				switch (action)
				{
				case GLFW_PRESS:
				{
					Event e(EventType::MouseButtonPressed, EventCategoryInput | EventCategoryMouse);
					double x, y;
					glfwGetCursorPos( static_cast<GLFWwindow*>(data.window->GetNativeWindow()), &x, &y);
					e.mouseButton = MouseButtonEvent(button, static_cast<float>(x), static_cast<float>(y));
					data.window->GetEventFlowControl().In(e);
					break;
				}
				case GLFW_RELEASE:
				{
					Event e(EventType::MouseButtonReleased, EventCategoryInput | EventCategoryMouse);
					double x, y;
					glfwGetCursorPos(static_cast<GLFWwindow*>(data.window->GetNativeWindow()), &x, &y);
					e.mouseButton = MouseButtonEvent(button, static_cast<float>(x), static_cast<float>(y));
					data.window->GetEventFlowControl().In(e);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				Event e(EventType::MouseScrolled, EventCategoryInput | EventCategoryMouse);
				double x, y;
				glfwGetCursorPos(reinterpret_cast<GLFWwindow*>(data.window->GetNativeWindow()), &x, &y);
				e.mouseScroll = MouseScrollEvent(static_cast<float>(xOffset), static_cast<float>(yOffset), static_cast<float>(x), static_cast<float>(y));
				data.window->GetEventFlowControl().In(e);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *static_cast<WindowData*>(glfwGetWindowUserPointer(window));

				Event e(EventType::MouseMoved, EventCategoryInput | EventCategoryMouse);
				e.mouseMove = MouseMoveEvent(static_cast<float>(xPos), static_cast<float>(yPos));
				data.window->GetEventFlowControl().In(e);
			});
	}


	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}
	
}
