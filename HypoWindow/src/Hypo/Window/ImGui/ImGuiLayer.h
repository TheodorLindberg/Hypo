#pragma once
namespace Hypo
{
	class ImGuiLayer 
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach(const class Window& window);
		void OnDetach();
		void OnImGuiRender();

		void Begin();
		void End(const class Window& window);
	private:
		float m_Time = 0.0f;
	};
}
