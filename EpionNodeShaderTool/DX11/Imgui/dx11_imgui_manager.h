#pragma	once

namespace	epion
{
	class	ImguiManager	final
	{
	public:
		static	void	Init();

		static	void	release();

		//	毎フレーム必要な処理
		static	void	begin();
		static	void	end();
	private:
	};

}