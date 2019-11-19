#pragma	once

namespace	epion
{
	class	ImguiManager	final
	{
	public:
		static	void	Init();
		static	void	Release();

		//	毎フレーム必要な処理
		static	void	Begin();
		static	void	End();
	private:
	};

}