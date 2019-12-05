#pragma once

namespace ImGui
{
	class FileBrowser;
}
namespace	epion::GUI
{
	class ExplorerWindow	final
	{
	public:
		void Init();
		void Update();
	private:
		void LocationSet();
		void NameSet();

	};
}