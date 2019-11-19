#include	<array>
#include	<valarray>
#include	"../epion.h"

#include	"renderer.h"

#include	"texture.h"

#include	"square.h"

namespace
{
	unsigned	int	stride = sizeof(epion::SquareVertex);
	unsigned	int	offset = 0;
}


namespace	epion
{
	Square::Square()
	{
	}
	Square::Square(com_ptr<ID3DBlob>&	m_blob)
	{
		HRESULT	hr = S_OK;
		std::vector<SquareVertex>	vertices
		{
			{
				//pos				uv					color
				{{-0.5f,	+0.5f,	0.0f,0.0f},{	0.0f,	0.0f},{	1.0f,	1.0f,	1.0f,	0.0f}},
				{{+0.5f,	+0.5f,	0.0f,0.0f},{	1.0f,	0.0f},{	1.0f,	1.0f,	1.0f,	0.0f}},
				{{-0.5f,	-0.5f,	0.0f,0.0f},{	0.0f,	1.0f},{	1.0f,	1.0f,	1.0f,	0.0f}},
				{{+0.5f,	-0.5f,	0.0f,0.0f},{	1.0f,	1.0f},{	1.0f,	1.0f,	1.0f,	0.0f}},
			}
		};


		shader_refrection = std::make_unique<ShaderReflection>();

		vertex_buffer = std::make_unique<VertexBuffer>();
		input_layout = std::make_unique<InputLayout>();
		shader_refrection->set_layout(m_blob);

		vertex_buffer->create<SquareVertex>(vertices);

		input_layout->Create(shader_refrection->get_layout(), m_blob);

	}

	Square::~Square()
	{}

	void	Square::Render(math::FVector2  d_xy, math::FVector2  d_wh, float angle, Color	data)
	{
		std::valarray<float>	arr_x =
		{
			d_xy.x,				//left-top
			d_xy.x + d_wh.x,	//right-top
			d_xy.x,				//left-bottom
			d_xy.x + d_wh.x,	//right-bottom
		};

		//std::array	arr_y	=
		std::valarray<float>	arr_y =
		{
			d_xy.y,				//left-top
			d_xy.y,				//right-top
			d_xy.y + d_wh.y,	//left-bottom
			d_xy.y + d_wh.y,	//right-bottom
		};

		arr_x = 2.0f	*arr_x / static_cast<float>(Renderer::GetScreenSize().x) - 1.0f;
		arr_y = 1.0f - 2.0f	*arr_y / static_cast<float>(Renderer::GetScreenSize().y);


		std::array<SquareVertex, 4>	v =
		{
			{
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
				{ { 0,	0,	0,	0 },{ 0,	0 },{ 0,	0,	0,	0 } },
			}
		};

		I_FOR(4)
		{
			v[i].pos.x = arr_x[i];
			v[i].pos.y = arr_y[i];
			v[i].pos.z = 0.0f;
			v[i].pos.w = 1.0f;
			v[i].color = data;
		}

		v[0].uv = { 0,0 };
		v[1].uv = { 1,0 };
		v[2].uv = { 0,1 };
		v[3].uv = { 1,1 };

		D3D11_MAPPED_SUBRESOURCE	map_resouce = {};
		Device::GetContext()->Map(vertex_buffer->get_buffer_ptr().Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &map_resouce);
		memcpy(map_resouce.pData, v.data(), sizeof(SquareVertex) * 4);
		Device::GetContext()->Unmap(vertex_buffer->get_buffer_ptr().Get(), 0);


		vertex_buffer->SetState(stride, offset);
		input_layout->SetState();

		Renderer::SetState();

		Renderer::set_2d_draw();

	}
	com_ptr<ID3D11ShaderResourceView>&	Square::get_shader_resouce()
	{
		return	shader_resouce_view;
	}

}