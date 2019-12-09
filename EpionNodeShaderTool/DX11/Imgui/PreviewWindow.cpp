#include	"../../All.h"
#include	"../../epion.h"
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"
#include	"../../ImguiFunction.h"

#include	"PreviewWindow.h"
#include	"../dx11_dxgi.h"

#include	"../../Node/NodeParamDx11.h"
#include	"EpionNodeEditor.h"
//#include	"ImguiNodeContext.h"

#include	"../../Node/NodeData.h"
#include	"../../ImguiFunction.h"

#include	"../../ShaderGenerate/ShaderGenerate.h"
#include	"../square.h"
#include	"../Cube.h"
#include	"../texture.h"
#include	"../../CameraManager.h"

namespace	epion
{

	std::unique_ptr<Square>			Preview::m_preview;

	std::unique_ptr<VertexShader>	Preview::m_vertex;
	std::unique_ptr<PixelShader>	Preview::m_pixel;

	std::unique_ptr<Texture2D>		Preview::m_preview_tex[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];

	math::FVector4					Preview::time;
	int Preview::m_used_tex;

	bool	Preview::Init(const std::wstring&	ps_name, std::vector<std::string>& tex_name,int use_tex)
	{
		m_used_tex = use_tex;
		m_used_tex = std::clamp(m_used_tex, 0, 15);
		m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\square_vertex_shader.hlsl");
		m_pixel = std::make_unique<PixelShader>(ps_name);

		m_preview = std::make_unique<Square>(m_vertex->GetBlob());
		for (int i = 0; i < m_used_tex; i++)
		{
			Node::Dx11::SamplerStateManager::Create(i, D3D11_FILTER_MIN_MAG_MIP_POINT, D3D11_TEXTURE_ADDRESS_WRAP);
			m_preview_tex[i] = std::make_unique<Texture2D>();
			TextureFileIO::LoadTexture(StringConverter::to_wstring(tex_name[i]), m_preview_tex[i]->GetMata(), m_preview_tex[i]->GetImage(), m_preview_tex[i]->GetShaderResouce());
		}
		time.x = 0.0f;
		return true;
	}
	void	Preview::Render()
	{
		time.x += 0.01f;
		m_vertex->SetState();
		m_pixel->SetState();
		for (int i = 0; i < m_used_tex; i++)
		{
			Device::GetContext()->PSSetShaderResources(i, 1, m_preview_tex[i]->GetShaderResouce().GetAddressOf());
			Node::Dx11::SamplerStateManager::SetState(i);
		}
		m_preview->Render(math::FVector2(1450, 650), math::FVector2(400, 400), 0, FixColor::Red);

	}
}