#pragma once

/**
* @file ArtisticAdjustment.h
* @brief Т▓Ро
* @author treize
* @date 2019/11/20
*/

namespace	epion::Node
{

	/**
	* @brief ReplaceColor	class
	* @details	InputSlot 0 In(clor)
	* @details	InputSlot 1 From(COLOR)
	* @details	InputSlot 2 To(COLOR)
	* @details	InputSlot 3 Range(float)
	* @details	InputSlot 4 Fuzziness(float)
	*/

	class ReplaceColorNode final :public	NodeBase
	{
	public:
		ReplaceColorNode();
		ReplaceColorNode(int id, const  math::FVector2& pos);
		~ReplaceColorNode();
		void	Init()override;
		void	Update(ImVec2 offset, ImDrawList*	draw_list)	override;
		void	ShaderUpdate(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)	override;

		std::string	GetFunctionDefStr()	override;

		template<class Archive>
		void serialize(Archive & archive)
		{
			archive(
				cereal::base_class<NodeBase>(this),
				cereal::make_nvp("In",m_in),
				cereal::make_nvp("From",m_from),
				cereal::make_nvp("To",m_to),
				cereal::make_nvp("Range", m_range),
				cereal::make_nvp("Fuzziness", m_fuzziness));
		};

	private:
		math::FVector3 m_in;
		math::FVector3 m_from;
		math::FVector3 m_to;
		float m_range;
		float m_fuzziness;
	};
}