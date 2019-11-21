#include	<array>

#include	"../epion.h"
#include	"dx11_device.h"

namespace
{

}
namespace	epion
{
	com_ptr<ID3D11Device>			Device::device;
	com_ptr<ID3D11DeviceContext>	Device::device_context;

	HRESULT	Device::Create()
	{
		unsigned	int	create_device_flags = 0;
#ifdef	_DEBUG
		create_device_flags |= D3D11_CREATE_DEVICE_FLAG::D3D11_CREATE_DEVICE_DEBUG;
#endif
		//動作する機能について
		std::array	feature_levels =
		{
			D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0,
		};
		unsigned	int	num_feature_levels = static_cast<unsigned	int>(feature_levels.size());
		D3D_FEATURE_LEVEL	g_feature_level = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

		return	::D3D11CreateDevice(
			nullptr,										//アダプタ
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,		//ドライバタイプ
			nullptr,										//ソフトウェアドライバモジュール
			create_device_flags,							//デバイスフラグ
			feature_levels.data(),							//フィーチャーレベル
			num_feature_levels,								//フィーチャーレベル配列の数
			D3D11_SDK_VERSION,								//SDKバージョン
			device.ReleaseAndGetAddressOf(),				//デバイスへのポインタ変数
			&g_feature_level,								//フィーチャーレベルへのポインタ
			device_context.ReleaseAndGetAddressOf());
	}

	void	Device::set_up()
	{
		HRESULT	hr = S_OK;
		constexpr	std::array	driver_types =
		{
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_REFERENCE,
		};
		constexpr	unsigned	int	num_driver_types = static_cast<unsigned	int>(driver_types.size());
		I_FOR(num_driver_types)
		{
			hr = Create();
			if (SUCCEEDED(hr))
			{
				break;
			}
		}
	}
}//epion