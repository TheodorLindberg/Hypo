#pragma once
#include <string>
#include <functional>

#include "Exports.h"
#include "Hypo/System/Events/Event.h"
#include "Context/GraphicsContext.h"

namespace Hypo
{
	namespace WindowStyle
	{
		enum WindowStyle
		{
			None = 0,      ///< No border / title bar (this flag and all others are mutually exclusive)
			Titlebar = BIT(1), ///< Title bar + fixed border
			Resize = BIT(2), ///< Title bar + resizable border + maximize button
			Close = BIT(3), ///< Title bar + close button
			Fullscreen = BIT(4), ///< Fullscreen mode (this flag and all others are mutually exclusive)

			Default = Titlebar | Resize | Close ///< Default window style

		};
	}
	struct WindowProps
	{
		std::string Title; ///< Window Title
		unsigned int Width; ///< The width of the window
		unsigned int Height; ///< The height of the window
		int Left; ///< The x coordinate of the windows top left corner
		int Top; ///< The y coordinate of the windows top left corner
		uInt32 Style;///< The Style of the window
		bool VSync;

		WindowProps(const std::string& title = "Hypo Window",
			unsigned int width = 1280,
			unsigned int height = 720,
			int top = 300,
			int left = 300,
			uInt32 style = WindowStyle::Default,
			bool vsync = true)
			: Title(title), Width(width), Height(height), Left(left), Top(top), Style(style), VSync(vsync)
		{
		}
	};

	class HYPO_WINDOW_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		Window() = default;
		virtual ~Window(){};

		virtual void Display() = 0;

		//Window size/position
		virtual unsigned int GetWidth() const  = 0;
		virtual unsigned int GetHeight() const  = 0;

		virtual unsigned int GetLeft() const  = 0;
		virtual unsigned int GetTop() const  = 0;

		virtual Vec2U GetSize() const = 0;
		virtual Vec2I GetPosition() const = 0;

		//Setters
		virtual void SetSize(Vec2U newSize) = 0;
		virtual void SetPosition(Vec2I newPosition) = 0;
		virtual void SetTitle(const std::string& title) = 0;

		//Window attributes
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual bool PollEvent(Event& event) = 0;
		virtual void EnablePollEvent(bool enabled) = 0;
		virtual bool PollEventEnabled() const = 0;

		virtual void EnableImGui() = 0;
		virtual void DisableImGui() = 0;
		virtual void BeginImGui() = 0;
		virtual void EndImGui() = 0;
		
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;
		virtual GraphicsContext* GetGraphicsContext() const = 0;
		static Window* Create(const WindowProps& props = WindowProps(), const ContextSettings& settings = ContextSettings());
		static Window* GetActiveWindow() { return m_ActiveWindow; }
	private:
		static Window* m_ActiveWindow;

	};
}
