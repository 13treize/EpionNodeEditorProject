#pragma once

namespace	epion::Node::Dx11
{
	/**
	* @brief Node�ŋK�肵�Ă���萔�o�b�t�@�Ǘ�
	*/
	struct	CBefferBase	abstract
	{
		virtual ~CBefferBase() {}
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
	struct	CBuffer2	final
	{
		math::FVector4	Pos;
		math::FVector4	Target;
		math::FVector4	Up;
	};
	struct	CBuffer3	final
	{
		DirectX::XMFLOAT4X4	WorldViewProjection;
		DirectX::XMFLOAT4X4	World;
	};


	/**
	* @brief	���̃G�f�B�^�ŋK�肳��Ă�萔�o�b�t�@�̊Ǘ�
	* @details	TODO ���[�U�[���ɒ񋟂���Ƃ��̍l��
	*/

	class	ConstantBufferManager
	{
	public:
		static bool Create();
		static void	UpdateCBuffer0(math::FVector4&	Time, math::FVector2&	ScreenSize);
		static void	UpdateCBuffer1(math::FVector4&	LightColor, math::FVector4&	LightDir, math::FVector4&	AmbientColor);
		static void	UpdateCBuffer2(math::FVector3&	Pos, math::FVector3&	Target, math::FVector3&	Up);
		static void	UpdateCBuffer3(const	DirectX::XMFLOAT4X4&	WorldViewProjection,	const	DirectX::XMFLOAT4X4&	World);

	private:
		static void CreateDesc(D3D11_BUFFER_DESC& desc, UINT size);

		static com_ptr<ID3D11Buffer>	m_constant_buffer0;
		static com_ptr<ID3D11Buffer>	m_constant_buffer1;
		static com_ptr<ID3D11Buffer>	m_constant_buffer2;
		static com_ptr<ID3D11Buffer>	m_constant_buffer3;

	};

	/**
	* @brief	���̃G�f�B�^�ŋK�肳��Ă�Sampler�̊Ǘ�
	* @details	TODO ���[�U�[���ɒ񋟂���Ƃ��̍l��
	*/

	class	SamplerStateManager	final
	{
	public:
		static bool Create(int index, D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE address);
		static void SetState(int index);

	private:
		static com_ptr<ID3D11SamplerState>	m_sampler_states[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];
	};

	/**
	* @brief	���̃G�f�B�^�ŋK�肳��Ă�Sampler�̊Ǘ�
	* @details	TODO ���[�U�[���ɒ񋟂���Ƃ��̍l��
	*/

	class DepthStencilStateManager	final
	{
	public:
		static bool Create();
		static void SetState();

	private:
		static com_ptr<ID3D11DepthStencilState>	m_depth_stencil_state;
	};

}