#pragma	once
#include	"../epion.h"
namespace	epion
{
	class	Device	final
	{
	public:
		static	com_ptr<ID3D11Device>	&GetDevice()
		{
			return	device;
		}

		static	com_ptr<ID3D11DeviceContext>	&GetContext()
		{
			return	device_context;
		}

		static	HRESULT	Create();
		static	void	set_up();

	private:
		static	com_ptr<ID3D11Device>			device;
		static	com_ptr<ID3D11DeviceContext>	device_context;
	};
}	//namespace	epion