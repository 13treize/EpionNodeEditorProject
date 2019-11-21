
#include	"../All.h"
#include	"../epion.h"
#include	"Cube.h"


namespace	epion
{
	Cube::Cube(const std::wstring& model,com_ptr<ID3DBlob>& blob)
	{
		m_file_name= model;
		m_obj = std::make_unique<ObjMesh>(m_file_name,blob);
		m_pos = { 0,0,0 };
		m_scale = { 1,1,1 };
		m_angle = { 0,0,0 };


	}
	Cube::~Cube()
	{
	}

	void	Cube::Update()
	{
		DirectX::XMMATRIX	mw = DirectX::XMMatrixIdentity();

		DirectX::XMMATRIX	s, r, t;

		//マトリクスはそのまま計算できる。
		//　拡大行列作成
		s = DirectX::XMMatrixScaling(m_scale.x, m_scale.y, m_scale.z);

		//　回転行列作成
		r = DirectX::XMMatrixRotationRollPitchYaw(m_angle.x, m_angle.y, m_angle.z);

		//　移動行列作成
		t = DirectX::XMMatrixTranslation(m_pos.x, m_pos.y, m_pos.z);

		//　行列合成と変換

		//XMFLOAT4X4へ変換はStore、逆はLoad命令を使ってください。
		mw = s * r	*t;
		XMStoreFloat4x4(&m_world_matrix, mw);
	}


	void	Cube::Render(const	DirectX::XMFLOAT4X4& view,const	DirectX::XMFLOAT4X4& projection)
	{

		DirectX::XMFLOAT4X4 world_view_projection;	//ローカル座標からプロジェクション座標への変換マトリクス
		DirectX::XMFLOAT4X4 world;					//法線を取る為ののワールド座標　光と、面の計算用

		//プロジェクションとワーロドとビューをコンスタントバッファに別々に送ってGPUで合成すると並列処理分、計算される。
		//ならば、最初から計算されたローカル２D変換マトリクスとワーロドマトリクスを渡す方が良いかも。

		DirectX::XMMATRIX  WP = DirectX::XMLoadFloat4x4(&m_world_matrix) * DirectX::XMLoadFloat4x4(&view) * DirectX::XMLoadFloat4x4(&projection);

		DirectX::XMStoreFloat4x4(&world_view_projection, WP);
		DirectX::XMStoreFloat4x4(&world, DirectX::XMLoadFloat4x4(&m_world_matrix));

		m_obj->Render(world_view_projection, world);
	}

	//set関数
	void	Cube::SetPos(math::FVector3&	pos_)
	{
		m_pos = pos_;
	}
	void	Cube::SetScale(math::FVector3&	scale_)
	{
		m_scale = scale_;
	}
	void	Cube::SetAngle(math::FVector3&	angle_)
	{
		m_angle = angle_;
	}

	//get関数
	math::FVector3&Cube::GetPos()
	{
		return	m_pos;
	}
	math::FVector3&	Cube::GetScale()
	{
		return	m_scale;
	}
	math::FVector3&	Cube::GetAngle()
	{
		return	m_angle;
	}
	std::wstring&	Cube::GetFileName()
	{
		return	m_file_name;
	}

}