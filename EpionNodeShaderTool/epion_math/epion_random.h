#pragma	once
#include	<random>
namespace	epion::math
{
	//�����̗����N���X
	class	Random	final
	{
	public:
		//�w�肵���͈͂̊Ԃ̗�����Ԃ�
		template<class	T>
		__forceinline	static	T	get_num(T	min_, T	max_);

		//�w�肵���m��(0.0f�`1.0f)��true��Ԃ�
		__forceinline	static	bool	is_get(float	num_);

		//vector�̒��g�ɓ����Ă��鐔�l(�m��)�ɉ����āA�z��̓Y����(�v�f��)��Ԃ�
		template<class	T>
		__forceinline	static	int	discrete_get(const	std::vector<T>&	data);



		//noise�֐�
		float	noise(int	param_);

		/*
			https://cpprefjp.github.io/reference/random/piecewise_constant_distribution.html
		*/
		class	Piecewice
		{
		public:
		};

	private:
		static	std::random_device	rd;	//�n�[�h�E�F�A�G���g���s�[
		static	std::mt19937		mt;	//�����Z���k�c�C�X�^

		//�ꉞ
		//static	std::knuth_b				knu;		//Knuth�̃��I�[�_�[�A���S���Y��B
		//static	std::default_random_engine	def_rd;		//�Ë�����
		//static	std::mt19937_64				mt_64;
		//static	std::ranlux24				ra_24;		//RANKUX�@
		//static	std::ranlux48				ra_48;
		//static	std::minstd_rand			minstd;		//MINSTD�ŏ��W��
		//static	std::minstd_rand0			minstd_0;
	};
}//	namespace epion::math


//����
template<class	T>
__forceinline	static	T	epion::math::Random::get_num(T	min_, T	max_)
{
	mt.seed(rd());
	std::uniform_int_distribution<T>	rand_num(min_, max_);
	return	rand_num(mt);
}
template<>
__forceinline	static	float	epion::math::Random::get_num<float>(float	min_, float	max_)
{
	mt.seed(rd());
	std::uniform_real_distribution<float>	rand_num(min_, max_);
	return	rand_num(mt);
}
template<>
__forceinline	static	double	epion::math::Random::get_num<double>(double	min_, double	max_)
{
	mt.seed(rd());
	std::uniform_real_distribution<double>	rand_num(min_, max_);
	return	rand_num(mt);
}


template<class	T>
__forceinline	static	int	epion::math::Random::discrete_get(const	std::vector<T>&	data)
{
	mt.seed(rd());
	std::discrete_distribution<int>	dist(data.begin(), data.end());
	return	dist(mt);
};
