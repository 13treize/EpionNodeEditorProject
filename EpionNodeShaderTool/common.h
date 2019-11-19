#pragma	once

//	�L���X�g�֘A
#define	st_cast	static_cast
#define	r_cast	reinterpret_cast
#define	c_cast	const_cast
#define	d_cast	dynamic_cast

#define	sa_cast	safe_cast


#define	I_FOR(value_limit)	for(unsigned	char	i	=0;	i	<value_limit;	i++)

#define	TO_STRING(VariableName)	#	VariableName

namespace	epion
{
	//�V���O���g���A�N���X�e���v���[�g
	template<class	T>
	class	Singleton
	{
	public:
		static	T&	GetInst()	noexcept
		{
			static	T	inst;
			return	inst;
		};
	private:
		void	operator	=(const	Singleton&	obj) {}	//������Z�q�֎~
		Singleton(const	Singleton	&obj) {}				//�R�s�[�R���X�g���N�^�֎~
	protected:
		Singleton() {}									//�O���ł̃C���X�^���X�쐬�͋֎~
		virtual	~Singleton() {};
	};

	//n�����z�񏉊���(�����̔z��̂�)
	template<	class	A, size_t	N, class	T>
	void	set_array_fill(A(&array)[N], const	T	&val)
	{
		std::fill((T*)array, (T*)(array + N), val);
	}

	template<class	T>
	using	com_ptr = Microsoft::WRL::ComPtr<T>;

	//�萔
	constexpr	int CHAR_SIZE = 256;

};

