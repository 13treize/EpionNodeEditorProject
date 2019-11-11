#pragma once
namespace	epion
{
	class	Texture2D;
	class	Square;
	class	VertexShader;
	class	PixelShader;

	class	Preview	final
	{
	public:
		static bool Init(std::wstring ps_name, std::vector<std::string>& tex_name,int use_tex = 0);
		static void Render();

	private:
		static math::FVector4 time;
		static int m_used_tex;

		static std::unique_ptr<Square> m_preview;
		static std::unique_ptr<VertexShader> m_vertex;
		static std::unique_ptr<PixelShader> m_pixel;
		static std::unique_ptr<Texture2D> m_preview_tex[D3D11_COMMONSHADER_SAMPLER_SLOT_COUNT];

	};
}