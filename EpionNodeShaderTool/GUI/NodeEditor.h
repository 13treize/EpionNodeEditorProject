#pragma once
namespace	epion::GUI
{
	class NodeWindow;
	class NodeDragWindow;
	class SettingWindow;
	class NodePreviewWindow;

	class NodeEditor final
	{
	public:
		static	void	Init();
		static	void	Update();
		static	void	Render();

	private:
		static NodeWindow	m_node_window;
		static NodeDragWindow	m_node_drag_window;
		static SettingWindow	m_node_setting_window;
		static NodePreviewWindow	m_node_preview_window;
	};
}
