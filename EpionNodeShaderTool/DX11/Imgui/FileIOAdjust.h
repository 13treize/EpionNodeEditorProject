#pragma once
namespace	epion::GUI
{
	/*
		Editor�ŗp����json(���Ԍ`��)��hlsl�̊Ǘ�(�p�X)
	
	*/
	class FileIOAdjust final
	{
	public:
		FileIOAdjust();
		~FileIOAdjust();

		void Init();
		void Update();

	private:
		std::string m_import_json_name;
		std::string	m_export_json_name;


		std::string m_import_json_path_name;
		std::string m_export_json_path_name;

		std::string	m_json_path;
		std::string	m_json_import_name;
		std::string	m_json_import;

		std::string	m_shader_path;
		std::string	m_shader_generate_name;
		std::string	m_shader_generate;

		void PathSetting();
		void JsonImport();
		void JsonSave();
		void ShaderGenerate();
	};
}
