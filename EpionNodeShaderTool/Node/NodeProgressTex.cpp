#include	"../All.h"
#include	"DirectXTex.h"
#include	"../epion.h"
#include	"../DX11//ShaderManager.h"
#include	"../DX11//shader_reflection.h"
#include	"../DX11//buffer.h"
#include	"../DX11//InputLayout.h"

#include	"NodeProgressTex.h"
namespace	epion
{
	//LoadNodeResouce::LoadNodeResouce()
	//{
	//}
	//LoadNodeResouce::~LoadNodeResouce()
	//{
	//}
	//void LoadNodeResouce::create(epion::com_ptr<ID3D11Device>& device)
	//{
	//	CD3D11_TEXTURE2D_DESC	tdesc(DXGI_FORMAT_R32G32B32A32_FLOAT, 1920, 1080, 1, 1,
	//		D3D11_BIND_SHADER_RESOURCE
	//		| D3D11_BIND_RENDER_TARGET
	//		| D3D11_BIND_UNORDERED_ACCESS,
	//		D3D11_USAGE_DEFAULT, 0, 1, 0, 0);
	//	device->CreateTexture2D(&tdesc, nullptr, Texture.GetAddressOf());


	//	// ShaderResourceView も作る
	//	CD3D11_SHADER_RESOURCE_VIEW_DESC	vdesc(D3D11_SRV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 1, 0, 1, 0);
	//	device->CreateShaderResourceView(Texture.Get(), &vdesc, &shader_resouce_view);

	//	// RenderTargetView も作る
	//	CD3D11_RENDER_TARGET_VIEW_DESC	rdesc(D3D11_RTV_DIMENSION_TEXTURE2D, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, 1);
	//	device->CreateRenderTargetView(Texture.Get(), &rdesc, &render_target_view);

	//	// UnorderedAccessVieww も作る
	//	CD3D11_UNORDERED_ACCESS_VIEW_DESC  uodesc(Texture.Get(),
	//		D3D11_UAV_DIMENSION_TEXTURE2D, DXGI_FORMAT_UNKNOWN, 0, 0, 1);
	//	device->CreateUnorderedAccessView(Texture.Get(), &uodesc, &unordered_access_view);

	//	HRESULT	hr = S_OK;
	//	std::vector<TexVertex>	vertices
	//	{
	//		{
	//			//pos				uv					color
	//			{{-0.5f,	+0.5f,	0.0f,0.0f},{	0.0f,	0.0f},{	1.0f,	1.0f,	1.0f,	0.0f}},
	//			{{+0.5f,	+0.5f,	0.0f,0.0f},{	1.0f,	0.0f},{	1.0f,	1.0f,	1.0f,	0.0f}},
	//			{{-0.5f,	-0.5f,	0.0f,0.0f},{	0.0f,	1.0f},{	1.0f,	1.0f,	1.0f,	0.0f}},
	//			{{+0.5f,	-0.5f,	0.0f,0.0f},{	1.0f,	1.0f},{	1.0f,	1.0f,	1.0f,	0.0f}},
	//		}
	//	};

	//	vertex_shader = std::make_unique<VertexShader>();
	//	pixel_shader = std::make_unique<PixelShader>();

	//	shader_refrection = std::make_unique<ShaderReflection>();

	//	vertex_buffer = std::make_unique<VertexBuffer>();
	//	input_layout = std::make_unique<InputLayout>();

	//	vertex_shader->create(L"HLSLShader\\square_vertex_shader.hlsl");
	//	pixel_shader->create(L"HLSLShader\\tests.hlsl");

	//	shader_refrection->set_layout(vertex_shader->get_blob());

	//	vertex_buffer->create<TexVertex>(vertices);

	//	input_layout->create(shader_refrection->get_layout(), vertex_shader->get_blob());
	//}
	//void LoadNodeResouce::draw(
	//	com_ptr<ID3D11DeviceContext>& device,
	//	com_ptr<ID3D11ShaderResourceView>&view,
	//	com_ptr<ID3D11SamplerState> &state
	//	)
	//{
	//	CD3D11_VIEWPORT viewp(0.0f, 0.0f, 1920, 1080);
	//	device->RSSetViewports(1, &viewp);

	//	// ブレンドするので Zバッファは使わない
	//	//iContext->OMSetDepthStensilState(iZDisable, 0);

	//	// Unordered Access View を設定する。RTV は NULL
	//	ID3D11RenderTargetView* ZERO_RTV = nullptr;
	//	device->OMSetRenderTargetsAndUnorderedAccessViews(
	//		1,      // NumViews
	//		&ZERO_RTV,
	//		NULL,   // depth buffer
	//		1,      // UAVStartSlot
	//		1,      // NumUAVs
	//		&unordered_access_view,
	//		NULL
	//	);

	//	device->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//	vertex_shader->set_state();
	//	input_layout->set_state();
	//	pixel_shader->set_state();
	//	device->PSSetShaderResources(0, 1, &view);
	//	device->PSSetSamplers(0, 1, &state);
	//	device->Draw(4, 0);

	//}
}
