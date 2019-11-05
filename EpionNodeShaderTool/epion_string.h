#pragma	once
#include	"epion_math//epion_math.h"

namespace	epion
{
	class	StringConverter
	{
	public:
		//char → wchar_t
		static	void to_wchar(const char* str, wchar_t* ret, unsigned int	max_size = 256);

		//wchar_t → char
		static void to_char(const wchar_t* str, char* ret, unsigned int	max_size = 256);

		//string → wstring
		static	std::wstring	to_wstring(const std::string&	str);

		//wstring → string
		static void to_string(std::wstring str, std::string ret, unsigned int	max_size = 256);

		//	引数からファイルパスを取得
		static	std::string		get_file_path(const std::string&	file_name);
		static	std::wstring	get_file_path(const std::wstring&	file_name);


		//	引数の拡張子を取得
		static	std::string	get_extension(const std::string&	str_);

		//std::to_string FVector2
		static	std::string		to_string2(epion::math::FVector2&	vec2, std::string	str = ",");
		static	std::string		to_string2(float x,float y, std::string	str = ",");

		static	std::string		to_string3(math::FVector3&	vec3, std::string	str = ",");
		static	std::string		to_string3(float x, float y, float z,std::string	str = ",");

		//std::to_string FVector4
		static	std::string		to_string4(epion::math::FVector4&	vec4, std::string	str = ",");
		static	std::string		to_string4(float x, float y, float z, float w,std::string	str = ",");

		static	std::string		get_space(int num);

	};
}

