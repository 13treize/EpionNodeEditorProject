#pragma once

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../epion.h"
#include	"../ImguiFunction.h"

/**
 * @file NodeData.h
 * @brief Node�̊��N���X�ALink���
 * @author treize
 * @date 2019/10/25
 */


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

	static constexpr	float	SLOT_INPUT_RECT_X = -70.0f;

	static constexpr float	SLOT_INPUT_FLOAT = 8;

	const	ImVec2		NODE_MIN_SIZE = { 80.0f, 50.0f };

	static constexpr float	NODE_SIZE = 35.0f;

	static constexpr float SLOT_INPUT_POS_X = -60.0f;
	const	ImVec2	SLOT_INPUT_POS = { SLOT_INPUT_POS_X, -SLOT_INPUT_FLOAT };

	static constexpr	float	NODE_SLOT_RADIUS = 5.0f;
	const	ImVec2	NODE_FONT_POS = { 10.0f, 5.0f };

	const ImU32	RECT_COLOR = IM_COL32(60, 60, 60, 200);

	//enum class Script
	enum class SLOT_TYPE
	{
		VECTOR1 = 1,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		BOOLEAN,
		TEXTURE2D,
		POS,//input�̂݁A������VECTOR3����
		UV,	//input�̂݁A������VECTOR2����
		COLOR,//input�̂݁A������VECTOR3����
	};

	class NodeFunction
	{
	public:
		//vector�̐��l�𕶎���ɕϊ�
		static std::string SetInputToString(float str);
		static std::string SetInputToString2(math::FVector2 str);
		static std::string SetInputToString3(math::FVector3 str);
		static std::string SetInputToString4(math::FVector4 str);


		static void SetInputSlotFloat(ImVec2& set_cursor, float x, std::string label, float& num);
		static void SetInputSlotFloat2(ImVec2& set_cursor, math::FVector2& num, int label_num = 0);
		static void SetInputSlotUV(ImVec2& set_cursor);
		static void SetInputSlotColor(ImVec2& set_cursor, bool& popup, math::FVector3& num, int label_num = 0);

		//�Ō�̈�����Imgui�ł̃o�O�U���h�~
		static void SetInputSlotDynamic(ImVec2& set_cursor, math::FVector4& num, SLOT_TYPE type, int label_num = 0);

		//������Node��name��id�Aname�Ɋւ��Ă�Dynamic���l��
		static std::string SetDefineOutName(std::string	str,int id);

		//out�w��̈������`
		static std::string SetDefineOutStr1(std::string	str);
		static std::string SetDefineOutStr2(std::string	str);
		static std::string SetDefineOutStr3(std::string	str);
		static std::string SetDefineOutStr4(std::string	str);

		static void InputRectDraw(ImDrawList*	draw_list, ImVec2 pos, SLOT_TYPE type);

		static std::string GetType(SLOT_TYPE& type);

		static std::string GetSlotTypeName(SLOT_TYPE type);

		static void SetSlotData(math::FVector4& data, std::string& str, SLOT_TYPE type);

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

	struct LinkData
	{
		int id;
		int slot;
		bool	operator==(const	 LinkData&	vec)const
		{
			if (id == vec.id	&& slot == vec.slot)
			{
				return	true;
			};
			return	false;
		}
		bool	operator!=(const	 LinkData&	vec)const
		{
			if (id != vec.id || slot != vec.slot)
			{
				return	true;
			};
			return	false;
		}

	};


	//�m�[�h���Ȃ���A����ێ�

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
			archive(CEREAL_NVP(m_input.id), CEREAL_NVP(m_input.slot), CEREAL_NVP(m_input_type),
				CEREAL_NVP(m_output.id), CEREAL_NVP(m_output.slot), CEREAL_NVP(m_output_type));
		};



		int	get_output_id();
		int	get_output_slot();
		SLOT_TYPE get_output_type();
		void set_output_type(SLOT_TYPE type);

		//right
		int	get_input_id();
		int	get_input_slot();
		SLOT_TYPE get_input_type();
		void set_input_type(SLOT_TYPE type);

		bool	operator==(const	NodeLink&	vec)const
		{
			if (m_output.id == vec.m_output.id	&&
				m_output.slot == vec.m_output.slot	&&
				m_input.id == vec.m_input.id	&&
				m_input.slot == vec.m_input.slot)
			{
				return	true;
			};
			return	false;
		}
		bool	operator!=(const	NodeLink&	vec)const
		{
			if (m_output.id != vec.m_output.id ||
				m_output.slot != vec.m_output.slot ||
				m_input.id != vec.m_input.id ||
				m_input.slot != vec.m_input.slot)
			{
				return	true;
			};
			return	false;
		}

		bool m_is_hit;
		bool m_is_delete;

		std::string StateStr();

	private:
		//left
		LinkData m_output;
		SLOT_TYPE m_output_type;
		//right
		LinkData m_input;
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
	enum class NODE_TYPE :unsigned char
	{
		NORMAL,
		DYNAMIC,
		MASTER,
	};
	//�m�[�h
	using LinkVector = std::vector<LinkData>;
	class	NodeBase
	{
	public:
		NodeBase();
		NodeBase(std::string name, int id, const math::FVector2& pos, const ImVec2& size, int inputs_count, int outputs_count);

		void	Update(ImVec2& offset, ImDrawList*	draw_list);

		virtual	~NodeBase() {}

		virtual	void	Init() = 0;

		void	Update();

		virtual	void	InputUpdate(ImVec2 offset, ImDrawList*	draw_list) = 0;
		virtual	void	OutputUpdate(ImVec2 offset, ImDrawList*	draw_list) = 0;

		//���t���[���͕K�v�Ȃ�
		virtual	void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links) = 0;


		std::string	m_Name;
		int		m_ID;
		math::FVector2	m_Pos;
		ImVec2	m_Size;

		int	m_inputs_count;
		int	m_outputs_count;

		//input�Ɍq�����Ă�link data
		LinkVector	m_input_links;

		//output�Ɍq�����Ă�link data
		LinkVector	m_output_links;

		std::vector<SLOT_TYPE>	m_input_slot_type;
		std::vector<SLOT_TYPE>	m_output_slot_type;

		std::vector<ImU32>	m_input_slot_color;
		std::vector<ImU32>	m_output_slot_color;

		//inputslot�Ƀm�[�h���h�����Ă��邩�ǂ���
		std::vector<bool>	m_is_input;

		ImVec2 GetInputSlotPos(int slot_no) const;
		ImVec2 GetOutputSlotPos(int slot_no) const;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(CEREAL_NVP(m_Name),
				CEREAL_NVP(m_ID),
				CEREAL_NVP(m_Pos),
				//CEREAL_NVP(m_input_slot_type),
				//CEREAL_NVP(m_output_slot_type),
				CEREAL_NVP(m_dynamic_slot_type),
				//CEREAL_NVP(m_input_name),
				//CEREAL_NVP(m_output_name),
				CEREAL_NVP(m_inputs_count),
				CEREAL_NVP(m_outputs_count),
				CEREAL_NVP(m_function_call_str));
		}

		//com_ptr<ID3D11DepthStencilView> m_depth_view;
		//std::unique_ptr<Texture>	m_resouce;
		//std::unique_ptr<Square>		m_preview;

		void	ResouceInit();
		void	ResouceRender(ImVec2& offset, ImDrawList*	draw_list);
		void	ResouceCreate();

	private:
		void	function_call_update(std::string	func_name);

	protected:
		//node�ɏo�����O
		std::vector<std::string>	m_input_name;
		std::vector<std::string>	m_output_name;

		std::vector<ImVec2>			m_input_pos;
		std::vector<ImVec2>			m_output_pos;


		void	i_update(ImVec2 offset, ImDrawList*	draw_list);
		void	o_update(ImVec2 offset, ImDrawList*	draw_list);
		void	str_check(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links);

		NODE_TYPE	m_node_type;

		/*
		Node��Dynamic�Ȃ�A�����ɍ��킹��
		input slot�ɓ����Ă�������̌^���������ق��ɍ��킹��(VEC1�͗�O)
		*/

		SLOT_TYPE	m_dynamic_slot_type;
		std::string	get_dynamic_type();
		/*
			hlsl����
		*/
	public:

		std::string		get_shader_str();

		//�Ăяo���֐���`�y�ю���
		virtual	std::string		get_function_def_str() = 0;


		//�֐��Ăяo��
		std::string		get_function_call_str();
		std::vector<std::string>&	GetOutStr();
		std::vector<std::string>&	GetInputStr();
	protected:

		//main���ł̌Ăяo��
		std::string	m_function_call_str;

		//�Ăяo���֐���`�y�ю���
		std::string	m_function_def_str;

		//�h����ł̕ϐ�
		std::vector<std::string>	m_out_str;

		//�h����ł̈���
		std::vector<std::string>	m_input_str;

		//���I�Ȍ^
		void link_set(std::vector<NodeLink>&	links);

		void type_set(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links);

		void str_set(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links);
	};
}