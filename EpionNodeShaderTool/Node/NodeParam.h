#pragma once
#include	"../../../imgui\\imgui.h"

namespace	epion::ImColor
{
	namespace	U32
	{
		static ImU32 RED = IM_COL32(250, 0, 0, 250);
		static ImU32 GREEN = IM_COL32(0, 250, 0, 250);
		static ImU32 BLUE = IM_COL32(0, 0, 250, 250);
		static ImU32 BLACK = IM_COL32(0, 0, 0, 250);
		static ImU32 LAWNGREEN = IM_COL32(124, 252, 0, 250);
		static ImU32 YELLOW = IM_COL32(255, 255, 0, 250);
		static ImU32 LIGHTBLUE = IM_COL32(0, 255, 255, 250);
		static ImU32 REDPURPLE = IM_COL32(255, 0, 124, 250);
		static ImU32 PURPLE = IM_COL32(255, 0, 255, 250);
		static ImU32 WHITE = IM_COL32(255, 255, 255, 250);
		static ImU32 ZERO = IM_COL32(0, 0, 0, 0);
	}

	namespace	Vec4
	{
		static ImVec4	WHITE = { 255, 255, 255, 255 };
	}
}

namespace	epion::NodeCustom
{
	enum class SLOT_TYPE
	{
		VECTOR1 = 1,
		VECTOR2,
		VECTOR3,
		VECTOR4,
		BOOLEAN,
		TEXTURE2D,
		SAMPLERSTATE,
		POS,//inputÇÃÇ›ÅAàµÇ¢ÇÕVECTOR3ìØÇ∂
		UV,	//inputÇÃÇ›ÅAàµÇ¢ÇÕVECTOR2ìØÇ∂
		COLOR,//inputÇÃÇ›ÅAàµÇ¢ÇÕVECTOR3ìØÇ∂
	};

	enum class NODE_TYPE :unsigned char
	{
		NORMAL,
		DYNAMIC,
		MASTER,
		VARIABLE,
	};

	//éhÇ≥Ç¡ÇΩnodeÇÃêî
	enum class INPUT_SLOT_STATE :unsigned char
	{
		ZERO,
		ONE,
		OUTOFRANGE,
	};

	static constexpr int SLOT_POS = 10;
	static constexpr float SLOT_INPUT_RECT_X = -70.0f;
	static constexpr float SLOT_INPUT_FLOAT = 8;

	const ImVec2 NODE_MIN_SIZE = { 80.0f, 50.0f };

	static constexpr float NODE_SIZE = 35.0f;

	static constexpr float SLOT_INPUT_POS_X = -60.0f;
	const ImVec2 SLOT_INPUT_POS = { SLOT_INPUT_POS_X, -SLOT_INPUT_FLOAT };

	static constexpr float NODE_SLOT_RADIUS = 5.0f;
	const ImVec2 NODE_FONT_ADD_POS = { 10.0f, 5.0f };


	const ImU32 RECT_COLOR = IM_COL32(60, 60, 60, 200);
	const ImU32 TITLE_BAR_COLOR = IM_COL32(40, 40, 40, 250);

	const	ImVec2	NODE_WINDOW_PADDING = { 165.0f, 165.0f };

}