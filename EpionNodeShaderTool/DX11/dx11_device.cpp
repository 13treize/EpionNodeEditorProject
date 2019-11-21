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
		//���삷��@�\�ɂ���
		std::array	feature_levels =
		{
			D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_10_0,
		};
		unsigned	int	num_feature_levels = static_cast<unsigned	int>(feature_levels.size());
		D3D_FEATURE_LEVEL	g_feature_level = D3D_FEATURE_LEVEL::D3D_FEATURE_LEVEL_11_0;

		return	::D3D11CreateDevice(
			nullptr,										//�A�_�v�^
			D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_HARDWARE,		//�h���C�o�^�C�v
			nullptr,										//�\�t�g�E�F�A�h���C�o���W���[��
			create_device_flags,							//�f�o�C�X�t���O
			feature_levels.data(),							//�t�B�[�`���[���x��
			num_feature_levels,								//�t�B�[�`���[���x���z��̐�
			D3D11_SDK_VERSION,								//SDK�o�[�W����
			device.ReleaseAndGetAddressOf(),				//�f�o�C�X�ւ̃|�C���^�ϐ�
			&g_feature_level,								//�t�B�[�`���[���x���ւ̃|�C���^
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