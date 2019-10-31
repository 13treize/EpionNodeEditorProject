#pragma once

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../EpionNodeShaderTool/epion.h"


//ImGuiぜってえ許さねえ!!!
namespace	epion::ImColor
{
	namespace	U32
	{
		static ImU32	RED = IM_COL32(250, 0, 0, 250);
		static ImU32	GREEN = IM_COL32(0, 250, 0, 250);
		static ImU32	BLUE = IM_COL32(0, 0, 250, 250);
		static ImU32	BLACK = IM_COL32(0, 0, 0, 250);


		static ImU32	LAWNGREEN = IM_COL32(124, 252, 0, 250);

		static ImU32	YELLOW = IM_COL32(255, 255, 0, 250);
		static ImU32	LIGHTBLUE = IM_COL32(0, 255, 255, 250);

		static ImU32	REDPURPLE = IM_COL32(255, 0, 124, 250);
	}

	namespace	Vec4
	{
		static ImVec4	WHITE = { 255, 255, 255, 255 };
	}

}

namespace	epion::NodeCustom
{
	static constexpr	int	SLOT_POS = 10;

	static constexpr int	SLOT_INPUT_FLOAT = 8;

	static constexpr float SLOT_INPUT_POS_X = -60.0f;
	const	ImVec2	SLOT_INPUT_POS = { SLOT_INPUT_POS_X, -static_cast<float>(SLOT_INPUT_FLOAT) };

	static constexpr	float	NODE_SLOT_RADIUS = 5.0f;
	const	ImVec2	NODE_FONT_POS = { 64.0f, 10.0f };
	const ImU32	LEFT_RECT_COLOR = IM_COL32(120, 120, 120, 200);
	const ImU32	RIGHT_RECT_COLOR = IM_COL32(60, 60, 60, 200);

	//enum class Script
	enum class SLOT_TYPE :unsigned char
	{
		VECTOR1 = 1,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		COLOR,
		TEXTURE2D,
		BOOLEAN,
	};
	class NodeFunction
	{
	public:
		static void SetInputSlotFloat(ImVec2& set_cursor, float x, std::string label, float& num);
		static void SetInputSlotFloat2(ImVec2& set_cursor, std::string label, math::FVector2& num);
		static void SetInputSlotFloat3(ImVec2& set_cursor, std::string label, math::FVector3& num);
		static void SetInputSlotFloat4(ImVec2& set_cursor, std::string label, math::FVector4& num);

		static std::string get_type(SLOT_TYPE type);

		static std::string get_slot_type_name(SLOT_TYPE type);

		static void set_slot_data(math::FVector4& data, std::string& str, SLOT_TYPE type);

		static void NodeCircle(ImDrawList*	draw_list, const ImVec2& centre, float radius, ImU32 color, SLOT_TYPE type = SLOT_TYPE::VECTOR1);
	};



	class	InputSlotState	final
	{
	public:
		InputSlotState()
		{
		}
		InputSlotState(std::string name, int no, SLOT_TYPE type)
			:slot_name(name), slot_no(no), slot_type(type)
		{
		}
		~InputSlotState()
		{
		}

		std::string		slot_name;
		unsigned int	slot_no;
		SLOT_TYPE		slot_type;
	};



	//ノードをつなげる、情報を保持
	class	NodeLink
	{
	public:
		NodeLink();
		NodeLink(int output_id, int output_slot, int input_id, int input_slot);

		NodeLink(int output_id, int output_slot, SLOT_TYPE output_type, int input_id, int input_slot, SLOT_TYPE input_type);

		~NodeLink();

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(CEREAL_NVP(m_input_id), CEREAL_NVP(m_input_slot), CEREAL_NVP(m_input_type),
				CEREAL_NVP(m_output_id), CEREAL_NVP(m_output_slot), CEREAL_NVP(m_output_type));
		};

		int	get_output_id();
		int	get_output_slot();
		SLOT_TYPE get_output_type();

		//right
		int	get_input_id();
		int	get_input_slot();
		SLOT_TYPE get_input_type();

		bool	operator==(const	NodeLink&	vec)const
		{
			if (m_output_id == vec.m_output_id	&&
				m_output_slot == vec.m_output_slot	&&
				m_input_id == vec.m_input_id	&&
				m_input_slot == vec.m_input_slot)
			{
				return	true;
			};
			return	false;
		}
		bool	operator!=(const	NodeLink&	vec)const
		{
			if (m_output_id != vec.m_output_id ||
				m_output_slot != vec.m_output_slot ||
				m_input_id != vec.m_input_id ||
				m_input_slot != vec.m_input_slot)
			{
				return	true;
			};
			return	false;
		}

	private:
		//left
		int	m_output_id;
		int	m_output_slot;
		SLOT_TYPE m_output_type;
		//right
		int	m_input_id;
		int	m_input_slot;
		SLOT_TYPE m_input_type;

	};

	//input, output
	class NodeStates
	{
	public:
		NodeStates();
		NodeStates(std::string	name, math::FVector2&	pos, SLOT_TYPE type, ImU32	color);

		~NodeStates();

		std::string	name;
		math::FVector2	pos;
		SLOT_TYPE	slot_type;
		ImU32	color;
	};
	//ノード
	class	NodeBase
	{
	public:
		NodeBase();
		NodeBase(std::string name, int id, const math::FVector2& pos, const ImVec2& size, int inputs_count, int outputs_count);

		void	Update(ImVec2& offset, ImDrawList*	draw_list);

		virtual	~NodeBase() {}

		virtual	void	Init() = 0;

		virtual	void	input_update(ImVec2 offset, ImDrawList*	draw_list) = 0;
		virtual	void	output_update(ImVec2 offset, ImDrawList*	draw_list) = 0;
		virtual	void	shader_update(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links) = 0;

		std::string	m_Name;
		int		m_ID;
		math::FVector2	m_Pos;
		ImVec2	m_Size;

		int	m_inputs_count;
		int	m_outputs_count;

		std::vector<SLOT_TYPE>	m_input_slot_type;
		std::vector<SLOT_TYPE>	m_output_slot_type;

		std::vector<ImU32>	m_input_slot_color;
		std::vector<ImU32>	m_output_slot_color;

		//inputslotにノードが刺さっているかどうか
		std::vector<bool>	m_is_input;

		ImVec2 get_input_slot_pos(int slot_no) const;
		ImVec2 get_output_slot_pos(int slot_no) const;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(CEREAL_NVP(m_Name),
				CEREAL_NVP(m_ID),
				CEREAL_NVP(m_Pos),
				CEREAL_NVP(m_input_slot_type),
				CEREAL_NVP(m_function_call_str));
		}

	private:
		void	function_call_update(std::string	func_name);

	protected:
		//nodeに出す名前
		std::vector<std::string>	m_input_name;
		std::vector<std::string>	m_output_name;

		std::vector<ImVec2>			m_input_pos;
		std::vector<ImVec2>			m_output_pos;


		void	i_update(ImVec2 offset, ImDrawList*	draw_list);
		void	o_update(ImVec2 offset, ImDrawList*	draw_list);


		/*
			hlsl生成
		*/
	public:

		std::string		get_shader_str();

		//呼び出し関数定義及び実装
		virtual	std::string		get_function_def_str() = 0;


		//関数呼び出し
		std::string		get_function_call_str();
		std::vector<std::string>&	get_out_str();
		std::vector<std::string>&	get_input_str();
	protected:

		//main内での呼び出し
		std::string	m_function_call_str;

		//呼び出し関数定義及び実装
		std::string	m_function_def_str;

		//派生先での変数
		std::vector<std::string>	m_out_str;

		//派生先での引数
		std::vector<std::string>	m_input_str;

		//動的な型
		void type_set(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links);

		void str_set(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links);
	};

}