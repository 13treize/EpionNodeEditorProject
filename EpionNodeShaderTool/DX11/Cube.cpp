#include	"../epion.h"
#include	"Cube.h"


namespace	epion
{
	Cube::Cube()
	{
		file_name=	L"data//cube.obj";
		obj = std::make_unique<ObjMesh>(file_name);
		pos = { 0,0,0 };
		scale = { 10,10,10 };
		angle = { 0,0,0 };


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
		s = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);

		//　回転行列作成
		r = DirectX::XMMatrixRotationRollPitchYaw(angle.x*0.01745f, angle.y*0.01745f, angle.z*0.01745f);

		//　移動行列作成
		t = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);

		//　行列合成と変換

		//XMFLOAT4X4へ変換はStore、逆はLoad命令を使ってください。
		mw = s * r	*t;
		XMStoreFloat4x4(&matWorld, mw);
	}


	void	Cube::Render(const	DirectX::XMFLOAT4X4& view,
		const	DirectX::XMFLOAT4X4& projection,
		const	math::FVector4& light)
	{

		Color color = {1,0,0,255};
		DirectX::XMFLOAT4X4 world_view_projection;	//ローカル座標からプロジェクション座標への変換マトリクス
		DirectX::XMFLOAT4X4 world;					//法線を取る為ののワールド座標　光と、面の計算用

		//プロジェクションとワーロドとビューをコンスタントバッファに別々に送ってGPUで合成すると並列処理分、計算される。
		//ならば、最初から計算されたローカル２D変換マトリクスとワーロドマトリクスを渡す方が良いかも。

		DirectX::XMMATRIX  WP = DirectX::XMLoadFloat4x4(&matWorld) * DirectX::XMLoadFloat4x4(&view) * DirectX::XMLoadFloat4x4(&projection);

		DirectX::XMStoreFloat4x4(&world_view_projection, WP);
		DirectX::XMStoreFloat4x4(&world, DirectX::XMLoadFloat4x4(&matWorld));

		obj->Render(world_view_projection, world, light,color);
	}

	//set関数
	void	Cube::set_pos(math::FVector3&	pos_)
	{
		pos = pos_;
	}
	void	Cube::set_scale(math::FVector3&	scale_)
	{
		scale = scale_;
	}
	void	Cube::set_angle(math::FVector3&	angle_)
	{
		angle = angle_;
	}

	//get関数
	math::FVector3&Cube::get_pos()
	{
		return	pos;
	}
	math::FVector3&	Cube::get_scale()
	{
		return	scale;
	}
	math::FVector3&	Cube::get_angle()
	{
		return	angle;
	}
	std::wstring&	Cube::get_file_name()
	{
		return	file_name;
	}

}