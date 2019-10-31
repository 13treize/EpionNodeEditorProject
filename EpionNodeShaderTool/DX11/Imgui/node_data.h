#pragma once
#include	<any>
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/string.hpp>
#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_impl_win32.h"
#include	"../../../imgui\\imgui_impl_dx11.h"
#include	"../../../imgui\\imgui_internal.h"

namespace	epion::NodeCustom
{
	struct	SlotState
	{
		int		SlotID;
		ImVec2	Pos;
	};

	class	ConstantState
	{
	public:
		ImVec2	m_pos;

	private:
	};

	//ÉmÅ[Éh
	class	NodeBase
	{
	public:
		NodeBase();
		NodeBase(std::string name, int id, const ImVec2& pos, int inputs_count, int outputs_count);

		virtual	~NodeBase() {}
		std::string	m_Name;
		int		m_ID;
		ImVec2	m_Pos;
		ImVec2	m_Size;

		int		m_inputs_count;
		int		m_outputs_count;

		/*
			åpè≥êÊÇ≈íÜÇÃïœêîÇÃå^ÅAêîÇéwíË
		*/
		//std::any	input;

		ImVec2 get_input_slot_pos(int slot_no) const;
		ImVec2 get_output_slot_pos(int slot_no) const;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(CEREAL_NVP(m_Name), CEREAL_NVP(m_ID), CEREAL_NVP(m_Pos), CEREAL_NVP(m_Size), CEREAL_NVP(m_inputs_count), CEREAL_NVP(m_outputs_count));
		}

	private:
	};

	struct	PBRInputData
	{
		PBRInputData() {}
		~PBRInputData() {}

		ImVec4	Position;
		ImVec4	Albedo;
		ImVec4	Normal;
		ImVec4	Emission;
		float	Metallic;
		float	Smoothness;
		float	Occulusion;
		float	Alpha;
		float	AlphaChipThreshold;

		//template<class Archive>
		//void serialize(Archive & archive)
		//{
		//	archive(CEREAL_NVP(Position),
		//			CEREAL_NVP(Albedo),
		//			CEREAL_NVP(Normal),
		//			CEREAL_NVP(Emission),
		//			CEREAL_NVP(Metallic),
		//			CEREAL_NVP(Smoothness),
		//			CEREAL_NVP(Occulusion),
		//			CEREAL_NVP(Alpha),
		//			CEREAL_NVP(AlphaChipThreshold));
		//};	
	};

	class	PBRMasterNode :public	NodeBase
	{
	public:
		PBRMasterNode(std::string name, int id, const ImVec2& pos);
		~PBRMasterNode() {}
	private:
		//input
		//PBRInputData	inputdata;
		//template<class Archive>
		//void serialize(Archive & archive)
		//{
		//	archive(CEREAL_NVP(inputdata.Position),
		//		CEREAL_NVP(inputdata.Albedo),
		//		CEREAL_NVP(inputdata.Normal),
		//		CEREAL_NVP(inputdata.Emission),
		//		CEREAL_NVP(inputdata.Metallic),
		//		CEREAL_NVP(inputdata.Smoothness),
		//		CEREAL_NVP(inputdata.Occulusion),
		//		CEREAL_NVP(inputdata.Alpha),
		//		CEREAL_NVP(inputdata.AlphaChipThreshold));
		//};

	};


	class	AddNode :public	NodeBase
	{
	public:
		AddNode(std::string name, int id, const ImVec2& pos);
		~AddNode() {}
	private:
		//input
		struct	Input
		{
			float	input_num1;
			float	input_num2;

		};

		//output
		struct	Output
		{
			float	output_num1;
		};
	};



	//ÉmÅ[ÉhÇÇ¬Ç»Ç∞ÇÈÅAèÓïÒÇï€éù
	class	NodeLink
	{
	public:
		NodeLink() {}

		NodeLink(int input_idx, int input_slot, int output_idx, int output_slot);

		int	m_input_id;
		int	m_input_slot;
		int	m_output_id;
		int	m_output_slot;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(CEREAL_NVP(m_input_id), CEREAL_NVP(m_input_slot), CEREAL_NVP(m_output_id), CEREAL_NVP(m_output_slot));
		};

	private:
	};

}