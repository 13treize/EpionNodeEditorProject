#pragma once
namespace	epion
{
	class	Texture;
	class	Square;
	class	VertexShader;
	class	PixelShader;

	class	Preview	final
	{
	public:
		static bool Init(std::wstring	ps_name);
		static void Render();

	private:
		static math::FVector4 time;
		static std::unique_ptr<Square> m_preview;
		static std::unique_ptr<VertexShader> m_vertex;
		static std::unique_ptr<PixelShader> m_pixel;
		static std::unique_ptr<Texture> m_preview_tex[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];

	};
}