#pragma	once

namespace	epion
{
	class	ImguiManager	final
	{
	public:
		static	void	Init();
		static	void	Release();

		//	���t���[���K�v�ȏ���
		static	void	Begin();
		static	void	End();
	private:
	};

}