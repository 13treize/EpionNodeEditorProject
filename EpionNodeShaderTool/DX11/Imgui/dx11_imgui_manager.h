#pragma	once

namespace	epion
{
	class	ImguiManager	final
	{
	public:
		static	void	Init();

		static	void	release();

		//	���t���[���K�v�ȏ���
		static	void	begin();
		static	void	end();
	private:
	};

}