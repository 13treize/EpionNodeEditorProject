#include	"../epion.h"
#include	"Renderer.h"
#include	"dx11_device.h"

namespace
{
}

namespace	epion
{
	math::Vector2<int>	Renderer::m_screen_size;

	void	Renderer::set_state()
	{
		Device::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}

	void	Renderer::set_state_list()
	{
		Device::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}


	void	Renderer::set_2d_draw()
	{
		Device::GetContext()->Draw(4, 0);
	}

	void	Renderer::set_drawindexed(unsigned	int	count, unsigned	int	start)
	{
		Device::GetContext()->DrawIndexed(count, start, 0);
	}

	void	Renderer::set_screen_size(int	width_, int	height_)
	{
		m_screen_size.x = width_;
		m_screen_size.y = height_;
	}

	math::Vector2<int>	Renderer::get_screen_size()
	{
		return	m_screen_size;
	}

}