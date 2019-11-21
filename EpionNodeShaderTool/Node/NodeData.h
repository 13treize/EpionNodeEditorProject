#pragma once

#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>

#include	"NodeParam.h"
#include	"../ImguiFunction.h"


/**
 * @file NodeData.h
 * @brief Nodeの基底クラス、Link情報
 * @author treize
 * @date 2019/10/25
 */

namespace	epion::NodeCustom
{


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
			if (id == vec.id	&& slot == vec.slot)	return	true;
			return	false;
		}
		bool	operator!=(const	 LinkData&	vec)const
		{
			if (id != vec.id || slot != vec.slot)	return	true;
			return	false;
		}

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
			archive(CEREAL_NVP(m_input.id), CEREAL_NVP(m_input.slot), CEREAL_NVP(m_input_type),
				CEREAL_NVP(m_output.id), CEREAL_NVP(m_output.slot), CEREAL_NVP(m_output_type));
		};



		int	GetOutputID();
		int	GetOutputSlot();
		SLOT_TYPE GetOutputType();
		void set_output_type(SLOT_TYPE type);

		//right
		int	GetInputID();
		int	GetInputSlot();
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

		std::string StateStr();

	private:
		//left
		LinkData m_output;
		SLOT_TYPE m_output_type;
		//right
		LinkData m_input;
		SLOT_TYPE m_input_type;

	};


	//ノード
	using LinkVector = std::vector<LinkData>;
	class	NodeBase
	{
	public:
		NodeBase();
		NodeBase(int inputs_count, int outputs_count);
		NodeBase(std::string name, int id, const math::FVector2& pos, int inputs_count, int outputs_count);

		virtual	~NodeBase() {}

		void	TitleDraw(ImVec2& offset, ImDrawList*	draw_list, bool is_push);

		virtual	void	Init() = 0;


		virtual	void	Update(ImVec2 offset, ImDrawList*	draw_list) = 0;

		//毎フレームは必要ない
		virtual	void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links) = 0;


		std::string	m_Name;
		int		m_ID;
		math::FVector2	m_Pos;
		ImVec2	m_Size;

		int	m_inputs_count;
		int	m_outputs_count;

		//inputに繋がってるlink data
		LinkVector	m_input_links;

		//outputに繋がってるlink data
		LinkVector	m_output_links;

		std::vector<SLOT_TYPE>	m_input_slot_type;
		std::vector<SLOT_TYPE>	m_output_slot_type;

		std::vector<ImU32>	m_input_slot_color;
		std::vector<ImU32>	m_output_slot_color;

		//inputslotにノードが刺さっているかどうか
		std::vector<bool>	m_is_slot_input;
		//std::vector<INPUT_SLOT_STATE> m_is_slot_input;

		ImVec2 GetInputSlotPos(int slot_no) const;
		ImVec2 GetOutputSlotPos(int slot_no) const;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(CEREAL_NVP(m_Name),
					CEREAL_NVP(m_ID),
					CEREAL_NVP(m_Pos),
					CEREAL_NVP(m_dynamic_slot_type),
					CEREAL_NVP(m_function_call_str));
		}

		void	ResouceInit();
		void	ResouceRender(ImVec2& offset, ImDrawList*	draw_list);
		void	ResouceCreate();

	private:
		// 命名規則被りのせい
		void Initialize();
		void Finalize();
		void	FunctionCallUpdate(std::string	func_name);

	protected:
		//nodeに出す名前
		std::vector<std::string>	m_input_name;
		std::vector<std::string>	m_output_name;

		std::vector<ImVec2>			m_input_pos;
		std::vector<ImVec2>			m_output_pos;


		void	DrawUpdate(ImVec2 offset, ImDrawList*	draw_list);

		void	StrCheck(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links);

		NODE_TYPE	m_node_type;

		/*
		NodeがDynamicなら、こいつに合わせる
		input slotに入っている引数の型が小さいほうに合わせる(VEC1は例外)
		*/

		SLOT_TYPE	m_dynamic_slot_type;
		std::string	get_dynamic_type();

		/*
			ColorPicker
			//ポインタやstlにするとエラー,CheckerboardでMax2つ使用の暫定処置
		*/
		ColorPicker2	m_color_picker[2];
		bool			m_open_popup[2];
		/*
		hlsl生成
		*/

	public:

		std::string		get_shader_str();

		//呼び出し関数定義及び実装
		virtual	std::string		GetFunctionDefStr() = 0;


		//関数呼び出し
		std::string		get_function_call_str();
		std::vector<std::string>&	GetOutStr();
		std::vector<std::string>&	GetInputStr();
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
		void LinkSet(std::vector<NodeLink>&	links);
		void TypeSet(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links);
		void StrSet(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links);

	};
}