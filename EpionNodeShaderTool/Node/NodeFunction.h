#pragma once
namespace	epion::NodeCustom
{
	class NodeFunction
	{
	public:
		static std::string SetVarFloat(const std::string& in, const std::string& out);
		static std::string SetVarFloat2(const std::string& in_x, const std::string& in_y, const std::string& out);
		static std::string SetVarFloat3(const std::string& in, const std::string& out);
		static std::string SetVarFloat4(const std::string& in, const std::string& out);

		//vectorの数値を文字列に変換
		static std::string SetInputToString(float str);
		static std::string SetInputToString2(math::FVector2 str);
		static std::string SetInputToString3(math::FVector3 str);
		static std::string SetInputToString4(math::FVector4 str);


		static void SetInputSlotFloat(ImVec2& set_cursor, const std::string& label, float& num);
		static void SetInputSlotFloat(ImVec2& set_cursor, float x, const std::string& label, float& num);

		static void SetInputSlotFloat2(ImVec2& set_cursor, math::FVector2& num, int label_num = 0);
		static void SetInputSlotUV(ImVec2& set_cursor);
		static void SetInputSlotTexture2D(ImVec2& set_cursor);
		static void SetInputSlotSamplerState(ImVec2& set_cursor);
		static void SetInputSlotColor(ImVec2& set_cursor, bool& popup, math::FVector3& num, int label_num = 0);

		//最後の引数はImguiでのバグ誘発防止
		static void SetInputSlotDynamic(ImVec2& set_cursor, math::FVector4& num, SLOT_TYPE type, int label_num = 0);

		//引数にNodeのnameとid、nameに関してはDynamic時考慮
		static std::string SetDefineOutName(std::string	str, int id);

		//関数定義
		static std::string SetFuncCall(const std::string& str);

		//out指定の引数を定義
		static std::string SetDefineOutStr1(const std::string& str);
		static std::string SetDefineOutStr2(const std::string& str);
		static std::string SetDefineOutStr3(const std::string& str);
		static std::string SetDefineOutStr4(const std::string& str);
		static std::string SetDefineOutSamplerState(const std::string& str, int num);
		static std::string SetDefineOutDynamic(const std::string& str, SLOT_TYPE type);

		static void InputRectDraw(ImDrawList*	draw_list, ImVec2 pos, SLOT_TYPE type);
		static std::string GetType(SLOT_TYPE type);
		static std::string GetSlotTypeName(SLOT_TYPE type);
		static void SetSlotData(math::FVector4& data, std::string& str, SLOT_TYPE type);
		static void NodeCircle(ImDrawList*	draw_list, const ImVec2& centre, float radius, ImU32 color, SLOT_TYPE type = SLOT_TYPE::VECTOR1);
	};
}