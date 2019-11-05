#include	<string>
#include	<string_view>
#include	<filesystem>

#include	"epion_string.h"
#include<clocale>
#include<cstdlib>


namespace
{
	wchar_t wc[256];

}

namespace	epion
{
	//char → wchar_t
	void	StringConverter::to_wchar(const char* str, wchar_t* ret, unsigned int	max_size)
	{
		::setlocale(LC_CTYPE, "jpn");
		size_t	s = 256;
		mbstowcs_s(&s, ret, max_size, str, _TRUNCATE);
	}

	//wchar_t → char
	void	StringConverter::to_char(const wchar_t* str, char* ret, unsigned int	max_size)
	{
		::setlocale(LC_CTYPE, "jpn");
		size_t	s = 256;
		wcstombs_s(&s, ret, max_size, str, _TRUNCATE);
	}

	//string → wstring
	std::wstring	StringConverter::to_wstring(const std::string&	str)
	{
		std::filesystem::path	get_str = str;
		return	get_str.wstring();
	}

	//wstring → string
	void	StringConverter::to_string(std::wstring str, std::string ret, unsigned int	max_size)
	{
		const	wchar_t*	get_str = str.c_str();
		char				get_ret[256] = {};
		to_char(get_str, get_ret, max_size);
		ret = get_ret;
	}

	//	引数からファイルパスを取得
	std::string	StringConverter::get_file_path(const std::string&	file_name)
	{
		std::filesystem::path	file_path = file_name;
		file_path.remove_filename();
		return	file_path.string();
	}

	std::wstring	StringConverter::get_file_path(const std::wstring&	file_name)
	{
		std::filesystem::path	file_path = file_name;
		file_path.remove_filename();
		return	file_path.wstring();
	}

	//	引数の拡張子を取得
	std::string	StringConverter::get_extension(const std::string&	str_)
	{
		std::filesystem::path	file_extension = str_;
		auto	ext_str = file_extension.extension();
		return	ext_str.string();
	}

	std::string	StringConverter::to_string2(math::FVector2&	vec2, std::string	str)
	{
		return	std::to_string(vec2.x) + str + std::to_string(vec2.y);
	}

	std::string	StringConverter::to_string2(float x, float y, std::string	str)
	{
		return	std::to_string(x) + str + std::to_string(y);
	}

	std::string	StringConverter::to_string3(math::FVector3&	vec3, std::string	str)
	{
		return	std::to_string(vec3.x) + str + std::to_string(vec3.y) + str + std::to_string(vec3.z);
	}

	std::string	StringConverter::to_string3(float x, float y, float z, std::string	str)
	{
		return	std::to_string(x) + str + std::to_string(y) + str + std::to_string(z);
	}

	std::string	StringConverter::to_string4(math::FVector4&	vec4, std::string	str)
	{
		return	std::to_string(vec4.x) + str + std::to_string(vec4.y)+ str + std::to_string(vec4.z)+ str + std::to_string(vec4.w);
	}
	std::string	StringConverter::to_string4(float x, float y, float z, float w,std::string	str)
	{
		return	std::to_string(x) + str + std::to_string(y) + str + std::to_string(z) + str + std::to_string(w);
	}


	std::string	StringConverter::get_space(int num)
	{
		std::string		ret_str="";
		for (int i = 0; i < num; i++)
		{
			ret_str += " ";
		}
		return ret_str;
	}

}// namespace epion

