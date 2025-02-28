#pragma once
#include "Hypo/Core.h"
#include <memory>
#include <queue>

#include "Hypo/Window/Window.h"
#include "Hypo/Window/ImGui/ImGuiLayer.h"

struct GLFWwindow;

namespace Hypo
{
	struct ContextSettings;

	class HYPO_WINDOW_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props, const ContextSettings& contextSettings);
		virtual ~WindowsWindow();
		
		void Display() override;
		
		unsigned int GetWidth() const override;
		unsigned int GetHeight() const override;
		unsigned int GetLeft() const override;
		unsigned int GetTop() const override;
		Vec2U GetSize() const override;
		Vec2I GetPosition() const override;

		RectI GetViewRect() const override;
		//Setters
		void SetSize(Vec2U newSize) override;
		void SetPosition(Vec2I newPosition) override;
		void SetTitle(const std::string& title) override;

		//Attributes
		void SetEventCallback(const EventCallbackFn& callback) override;
		bool PollEvent(Event& event) override;
		void EnablePollEvent(bool enabled) override;
		bool PollEventEnabled() const override;

		
		void EnableImGui() override
		{
			m_ImGui.OnAttach(*this);
		}
		void DisableImGui() override
		{

			m_ImGui.OnDetach();
		}
		void BeginImGui() override
		{

			m_ImGui.Begin();
		}
		void EndImGui() override
		{
			m_ImGui.End(*this);
		}

		void SetVSync(bool enabled) override;
		bool IsVSync() const override;
		void* GetNativeWindow() const override;
		GraphicsContext* GetGraphicsContext() const override { return m_Context.get(); };

		virtual void* GetGladProc() override;

		void PushEvent(Event& event);
	private:
		void Init(const WindowProps& props, const ContextSettings& contextSettings);
		void InitEventCallbacks();
		void Shutdown();
	public:
		const WindowEventFlowControl& GetEventFlowControl() const override { return m_EventFlowControl;  };
		WindowEventFlowControl& GetEventFlowControl() override {return m_EventFlowControl; }
	private:


		class WindowData
		{
		public:
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			bool PushEventToStack;
			Window* window;

			std::queue<Event>* eventQueue;

			EventCallbackFn EventCallback;

		};

		GLFWwindow* m_Window;

		std::unique_ptr<GraphicsContext> m_Context;

		WindowData m_Data;
		std::queue<Event> m_EventQueue;
		ImGuiLayer m_ImGui;
		WindowEventFlowControl m_EventFlowControl;
	};

	void IMGUI_SYMBOL_DEFINITION()
	{

		ImGui::ShowDemoWindow(nullptr);
	}
}
