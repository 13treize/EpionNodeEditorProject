#pragma once

namespace	epion
{
	/**
	* @brief Node�ŋK�肵�Ă���萔�o�b�t�@�Ǘ�
	*/
	struct	BefferBase	abstract
	{
		virtual ~BefferBase() {}
	};
	struct	CBuffer0	final
	{
		math::FVector4	Time;
		math::FVector2	ScreenSize;
		math::FVector2	Dummy0;
	};

	struct	CBuffer1	final
	{
		math::FVector4	LightColor;		//���C�g�̐F
		math::FVector4	LightDir;		//���C�g�̕���
		math::FVector4	AmbientColor;	//����
	};
	/**
	* @brief ConstantBufferManager	class
	* @details	���̃G�f�B�^�ŋK�肳��Ă�萔�o�b�t�@�̊Ǘ�
	* @details	TODO ���[�U�[���ɒ񋟂���Ƃ��̍l��
	*/

	class	ConstantBufferManager
	{
	public:
		static bool Create();
		static void	UpdateCBuffer0(math::FVector4&	Time, math::FVector2&	ScreenSize);
		static void	UpdateCBuffer1(math::FVector4&	LightColor,	math::FVector4&	LightDir,	math::FVector4&	AmbientColor);

	private:
		static void CreateDesc(D3D11_BUFFER_DESC& desc, UINT size);

		static com_ptr<ID3D11Buffer>	m_constant_buffer0;
		static com_ptr<ID3D11Buffer>	m_constant_buffer1;

	};

}