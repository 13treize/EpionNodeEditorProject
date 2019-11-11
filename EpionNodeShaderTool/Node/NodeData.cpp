#include "../All.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	"NodeParam.h"

#include	"NodeData.h"
#include	"../epion_physics/epion_collider.h"
#include	"../epion_string.h"

#include	"../DX11/dx11_device.h"
#include	"../DX11/dx11_dxgi.h"
#include	"../DX11/RenderTarget.h"
#include	"../DX11/texture.h"
#include	"../DX11/square.h"

#include	"../ShaderGenerate/ShaderGenerate.h"
#include	"../ImguiFunction.h"

namespace
{

}
namespace epion
{
	std::unique_ptr<Texture>	m_resouce;
	std::unique_ptr<Square>		m_preview;
	std::unique_ptr<VertexShader>	m_vertex;
	std::unique_ptr<PixelShader>	m_pixel;
	bool is_save;
	com_ptr<ID3D11DepthStencilView>	depth_view;

}
namespace	epion::NodeCustom
{
	std::string	NodeFunction::SetVarFloat(const std::string& in, const std::string& out) {return "    float " + out + "=" + in + ";\n";}
	std::string	NodeFunction::SetVarFloat2(const std::string& in_x, const std::string& in_y, const std::string& out) { return"    float2 " + out + "=" + "float2(" + in_x + "," + in_y + ");\n";}
	std::string	NodeFunction::SetVarFloat3(const std::string& in, const std::string& out) { return ""; }
	std::string	NodeFunction::SetVarFloat4(const std::string& in, const std::string& out) { return ""; }

	std::string	NodeFunction::SetInputToString(float str) { return std::to_string(str);}
	std::string	NodeFunction::SetInputToString2(math::FVector2 str) { return "float2(" + StringConverter::to_string2(str, ",") + ")";}
	std::string	NodeFunction::SetInputToString3(math::FVector3 str) { return "float3(" + StringConverter::to_string3(str, ",") + ")";}
	std::string	NodeFunction::SetInputToString4(math::FVector4 str) { return "float4(" + StringConverter::to_string4(str, ",") + ")";}

	void NodeFunction::SetInputSlotFloat(ImVec2& set_cursor, const std::string& label, float& num)
	{
		ImGui::SetCursorScreenPos(set_cursor + ImVec2(SLOT_INPUT_POS_X, -SLOT_INPUT_FLOAT));
		ImGui::SetNextItemWidth(30.0f);
		ImGui::InputFloat(label.c_str(), &num, 0.0f, 1.0f, "%.2f");
	}

	void NodeFunction::SetInputSlotFloat(ImVec2& set_cursor, float x, const std::string& label, float& num)
	{
		ImGui::SetCursorScreenPos(set_cursor + ImVec2(x, -SLOT_INPUT_FLOAT));
		ImGui::SetNextItemWidth(30.0f);
		ImGui::InputFloat(label.c_str(), &num, 0.0f, 1.0f, "%.2f");
	}
	void NodeFunction::SetInputSlotFloat2(ImVec2& set_cursor, math::FVector2& num, int label_num)
	{
		SetInputSlotFloat(set_cursor, SLOT_INPUT_POS_X, StringConverter::get_space(1 + (label_num + 1) * 2), num.x);
		SetInputSlotFloat(set_cursor, SLOT_INPUT_POS_X * 2, StringConverter::get_space(2 + (label_num + 1) * 2), num.y);
	}

	void NodeFunction::SetInputSlotUV(ImVec2& set_cursor)
	{
		ImGui::SetCursorScreenPos(set_cursor + ImVec2(-50, -SLOT_INPUT_FLOAT));
		ImGui::TextColored(ImColor::Vec4::WHITE, "%s", "uv");
	}
	void NodeFunction::SetInputSlotTexture2D(ImVec2& set_cursor)
	{
		ImGui::SetCursorScreenPos(set_cursor + ImVec2(-50, -SLOT_INPUT_FLOAT));
		ImGui::TextColored(ImColor::Vec4::WHITE, "%s", "tex");
	}
	void NodeFunction::SetInputSlotSamplerState(ImVec2& set_cursor)
	{
		ImGui::SetCursorScreenPos(set_cursor + ImVec2(-50, -SLOT_INPUT_FLOAT));
		ImGui::TextColored(ImColor::Vec4::WHITE, "%s", "ss");
	}

	void NodeFunction::SetInputSlotColor(ImVec2& set_cursor,bool& popup, math::FVector3& num, int label_num)
	{
		ImGui::SetCursorScreenPos(set_cursor + SLOT_INPUT_POS + ImVec2(-30, 0));
		popup = ImGui::ColorButton("MyColor", ImVec4(num.x, num.y, num.z, 1.0f), ColorPicker::GetFrag());
		ImGui::SameLine();
		popup |= ImGui::Button("Color");

		ColorPicker::Activate(popup, num);
		num = ColorPicker::GetColor();
	}

	void NodeFunction::SetInputSlotDynamic(ImVec2& set_cursor, math::FVector4& num, SLOT_TYPE type, int label_num)
	{
		switch (type)
		{
		case SLOT_TYPE::VECTOR4:	SetInputSlotFloat(set_cursor, (static_cast<float>(type) - 3)	*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(type) + (label_num + 1) * 4), num.w);
		case SLOT_TYPE::VECTOR3:	SetInputSlotFloat(set_cursor, (static_cast<float>(type) - 2)	*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(type) - 1 + (label_num + 1) * 4), num.z);
		case SLOT_TYPE::VECTOR2:	SetInputSlotFloat(set_cursor, (static_cast<float>(type) - 1)	*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(type) - 2 + (label_num + 1) * 4), num.y);
		case SLOT_TYPE::VECTOR1:	SetInputSlotFloat(set_cursor, static_cast<float>(type)			*SLOT_INPUT_POS_X, StringConverter::get_space(static_cast<int>(type) - 3 + (label_num + 1) * 4), num.x);
			break;
		}

	}

	std::string NodeFunction::SetDefineOutName(std::string	str, int id)
	{
		return str+"_out" + std::to_string(id);
	}

	std::string NodeFunction::SetFuncCall(const std::string& str)	{	return "    " + str + "(";	}

	std::string NodeFunction::SetDefineOutStr1(const std::string& str){	return	"    float " + str + ";\n";}
	std::string NodeFunction::SetDefineOutStr2(const std::string& str){	return	"    float2 " + str + ";\n";}
	std::string NodeFunction::SetDefineOutStr3(const std::string& str){	return	"    float3 " + str + ";\n";}
	std::string NodeFunction::SetDefineOutStr4(const std::string& str){	return	"    float4 " + str + ";\n";}
	std::string NodeFunction::SetDefineOutDynamic(const std::string& str, SLOT_TYPE type){	return	"    "+ GetType(type)+" " + str + ";\n";}


	void NodeFunction::InputRectDraw(ImDrawList*	draw_list, ImVec2 pos, SLOT_TYPE type)
	{
		switch (type)
		{
		default:
		case epion::NodeCustom::SLOT_TYPE::VECTOR1:
		case epion::NodeCustom::SLOT_TYPE::UV:
		case epion::NodeCustom::SLOT_TYPE::TEXTURE2D:
		case epion::NodeCustom::SLOT_TYPE::SAMPLERSTATE:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), ImColor::U32::GREEN, 2.0f);
			break;
		case epion::NodeCustom::SLOT_TYPE::VECTOR2:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X * 2 + 10.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X * 2 + 10.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), ImColor::U32::GREEN, 2.0f);
			break;
		case epion::NodeCustom::SLOT_TYPE::VECTOR3:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X * 3 + 20.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X * 3 + 20.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), ImColor::U32::GREEN, 2.0f);
			break;
		case epion::NodeCustom::SLOT_TYPE::VECTOR4:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X * 4 + 30.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X * 4 + 30.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), ImColor::U32::GREEN, 2.0f);
			break;
		case epion::NodeCustom::SLOT_TYPE::COLOR:
			draw_list->AddRectFilled(pos + ImVec2(SLOT_INPUT_RECT_X * 1.8 + 30.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), IM_COL32(60, 60, 60, 255), 2.0f);
			draw_list->AddRect(pos + ImVec2(SLOT_INPUT_RECT_X * 1.8 + 30.0f, -SLOT_INPUT_FLOAT), pos + ImVec2(-15, SLOT_INPUT_FLOAT), ImColor::U32::GREEN, 2.0f);
			break;
		}

	}
	std::string	NodeFunction::GetType(SLOT_TYPE type)
	{
		std::string	ret_str = "";
		switch (type)
		{
		case SLOT_TYPE::VECTOR1:	ret_str = "float";	break;
		case SLOT_TYPE::VECTOR2:	ret_str = "float2";	break;
		case SLOT_TYPE::VECTOR3:	ret_str = "float3";	break;
		case SLOT_TYPE::VECTOR4:	ret_str = "float4";	break;
		case SLOT_TYPE::COLOR:	break;
		case SLOT_TYPE::TEXTURE2D:	break;
		case SLOT_TYPE::BOOLEAN:	break;
		}
		return ret_str;
	}

	std::string	NodeFunction::GetSlotTypeName(SLOT_TYPE type)
	{
		std::string	ret_str = "";
		switch (type)
		{
		case SLOT_TYPE::VECTOR1:	ret_str = "(1)";	break;
		case SLOT_TYPE::VECTOR2:
		case SLOT_TYPE::UV:			ret_str = "(2)";	break;
		case SLOT_TYPE::VECTOR3:	ret_str = "(3)";	break;
		case SLOT_TYPE::VECTOR4:	ret_str = "(4)";	break;
		case SLOT_TYPE::COLOR:	break;
		case SLOT_TYPE::TEXTURE2D:	break;
		case SLOT_TYPE::BOOLEAN:	break;
		}
		return ret_str;
	}

	void NodeFunction::SetSlotData(math::FVector4& data, std::string& str, SLOT_TYPE type)
	{
		switch (type)
		{
		case SLOT_TYPE::VECTOR1:	str = std::to_string(data.x);			break;
		case SLOT_TYPE::VECTOR2:	str = NodeFunction::GetType(type) + "(" + StringConverter::to_string2(data.x, data.y) + ")";			break;
		case SLOT_TYPE::VECTOR3:	str = NodeFunction::GetType(type) + "(" + StringConverter::to_string3(data.x, data.y, data.z) + ")";	break;
		case SLOT_TYPE::VECTOR4:	str = NodeFunction::GetType(type) + "(" + StringConverter::to_string4(data) + ")";						break;
		}

	}

	void NodeFunction::NodeCircle(ImDrawList*	draw_list, const ImVec2& centre, float radius, ImU32 color, SLOT_TYPE type)
	{
		switch (type)
		{
		case SLOT_TYPE::VECTOR1:	color = ImColor::U32::LIGHTBLUE;	break;
		case SLOT_TYPE::VECTOR2:
		case SLOT_TYPE::UV:			color = ImColor::U32::LAWNGREEN;	break;
		case SLOT_TYPE::VECTOR3:
		case SLOT_TYPE::COLOR:		color = ImColor::U32::YELLOW;	break;
		case SLOT_TYPE::VECTOR4:	color = ImColor::U32::PURPLE;	break;
		case SLOT_TYPE::TEXTURE2D:	color = ImColor::U32::RED;	break;
		case SLOT_TYPE::SAMPLERSTATE:	color = ImColor::U32::WHITE;	break;
		case SLOT_TYPE::BOOLEAN:	break;
		}
		draw_list->AddCircle(centre, NODE_SLOT_RADIUS, color);
	}


	NodeBase::NodeBase()
	{
		//for (int i = 0; i < m_inputs_count; i++)
		//{
		//	m_is_input.push_back(false);

		//	m_input_str.push_back("");
		//	m_input_pos.push_back({});
		//	m_input_slot_color.push_back(0);
		//	m_input_links.push_back({ -1, -1 });
		//}

		//for (int i = 0; i < m_outputs_count; i++)
		//{
		//	m_out_str.push_back("");
		//	m_output_pos.push_back({});
		//	m_output_slot_color.push_back(0);
		//	m_output_links.push_back({ -1, -1 });
		//}
		//if (m_inputs_count < m_outputs_count)
		//{
		//	m_Size = { 55.0f*m_outputs_count ,55.0f*m_outputs_count };
		//}
		//else
		//{
		//	m_Size = { 55.0f*m_inputs_count ,55.0f*m_inputs_count };
		//}
	}
	//test
	void	NodeBase::ResouceInit()
	{
			m_resouce = std::make_unique<Texture>();
			m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\square_vertex_shader.hlsl");
			m_pixel = std::make_unique<PixelShader>(L"test.hlsl");
			m_preview = std::make_unique<Square>(m_vertex->GetBlob());
			is_save=false;
			com_ptr<ID3D11Texture2D>	depth_stencil_buffer;

			D3D11_TEXTURE2D_DESC	texture_desc;

			texture_desc.Width=static_cast<UINT>(m_Size.x);
			texture_desc.Height = static_cast<UINT>(m_Size.x);
			texture_desc.MipLevels = 1;
			texture_desc.ArraySize = 1;
			texture_desc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
			texture_desc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
			texture_desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
			texture_desc.CPUAccessFlags = 0;
			texture_desc.MiscFlags = 0;

			Device::GetDevice()->CreateTexture2D(&texture_desc,
				nullptr,
				depth_stencil_buffer.ReleaseAndGetAddressOf());

			D3D11_DEPTH_STENCIL_VIEW_DESC	depth_stincil_view;
			depth_stincil_view.Format = texture_desc.Format;
			depth_stincil_view.ViewDimension = D3D11_DSV_DIMENSION::D3D11_DSV_DIMENSION_TEXTURE2DMS;
			depth_stincil_view.Flags = 0;
			depth_stincil_view.Texture2D.MipSlice = 0;

			Device::GetDevice()->CreateDepthStencilView(depth_stencil_buffer.Get(),
				&depth_stincil_view,
				depth_view.ReleaseAndGetAddressOf());

			m_resouce->Create(static_cast<u_int>(m_Size.x), static_cast<u_int>(m_Size.x), DXGI_FORMAT_R16G16B16A16_FLOAT);
	}

	//test
	void	NodeBase::ResouceRender(ImVec2& offset, ImDrawList*	draw_list)
	{
		Device::GetContext()->OMSetRenderTargets(1, m_resouce->RenderTargetView.GetAddressOf(), Dxgi::get_dsv().Get());
		float color[4] = { 1,0,0,0 };
		Device::GetContext()->ClearRenderTargetView(m_resouce->RenderTargetView.Get(), color);
		Device::GetContext()->ClearDepthStencilView(Dxgi::get_dsv().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		Device::GetContext()->PSSetShaderResources(0, 1, m_resouce->ShaderResourceView.GetAddressOf());
		m_preview->Render(math::FVector2(0, 0), math::FVector2(m_Size.x, m_Size.x),0, FixColor::Red);
		draw_list->ChannelsSetCurrent(4); // input_slot
		ImGui::SetCursorScreenPos(ImVec2(m_Pos.x + offset.x, m_Pos.y + m_Size.y + offset.y));
		ImGui::Image(m_resouce->ShaderResourceView.Get(), ImVec2(m_Size.x, m_Size.x), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 1));
	}

	void	NodeBase::ResouceCreate()
	{
	}
	NodeBase::NodeBase(int inputs_count, int outputs_count)
		:m_inputs_count(inputs_count), m_outputs_count(outputs_count)
	{
				for (int i = 0; i < m_inputs_count; i++)
		{
			m_is_input.push_back(false);

			m_input_str.push_back("");
			m_input_pos.push_back({});
			m_input_slot_color.push_back(0);
			m_input_links.push_back({ -1, -1 });
		}

		for (int i = 0; i < m_outputs_count; i++)
		{
			m_out_str.push_back("");
			m_output_pos.push_back({});
			m_output_slot_color.push_back(0);
			m_output_links.push_back({ -1, -1 });
		}
		if (m_inputs_count < m_outputs_count)
		{
			m_Size = { 55.0f*m_outputs_count ,55.0f*m_outputs_count };
		}
		else
		{
			m_Size = { 55.0f*m_inputs_count ,55.0f*m_inputs_count };
		}

	}

	NodeBase::NodeBase(std::string name, int id, const epion::math::FVector2& pos, int inputs_count, int outputs_count)
		:m_Name(name),
		m_ID(id),
		m_Pos(pos),
		m_inputs_count(inputs_count),
		m_outputs_count(outputs_count),
		m_function_call_str(""),
		m_dynamic_slot_type(SLOT_TYPE::VECTOR1)
	{
		for (int i = 0; i < m_inputs_count; i++)
		{
			m_is_input.push_back(false);

			m_input_str.push_back("");
			m_input_pos.push_back({});
			m_input_slot_color.push_back(0);
			m_input_links.push_back({ -1, -1 });
		}

		for (int i = 0; i < m_outputs_count; i++)
		{
			m_out_str.push_back("");
			m_output_pos.push_back({});
			m_output_slot_color.push_back(0);
			m_output_links.push_back({ -1, -1 });
		}
		if (m_inputs_count < m_outputs_count)
		{
			m_Size = { 55.0f*m_outputs_count ,55.0f*m_outputs_count };
		}
		else
		{
			m_Size = { 55.0f*m_inputs_count ,55.0f*m_inputs_count };
		}
#ifdef DEBUG
		ResouceInit();
#endif
	}
	void	NodeBase::Update(ImVec2& offset, ImDrawList*	draw_list)
	{
		ImVec2 node_rect_min = { offset.x + m_Pos.x,offset.y + m_Pos.y };
		ImVec2 node_rect_max = node_rect_min + m_Size;
		ImVec2 node_rect_max2 = node_rect_min + ImVec2(m_Size.x*0.5f, m_Size.y);

		draw_list->ChannelsSetCurrent(1);
		draw_list->AddRectFilled(node_rect_min, node_rect_max, RECT_COLOR, 2.0f);

		if (m_node_type != NODE_TYPE::MASTER)
		{
			draw_list->AddRectFilled(node_rect_min, node_rect_max2, RECT_COLOR, 2.0f);
		}
		draw_list->ChannelsSetCurrent(2); // Foreground
		draw_list->AddRectFilled(node_rect_min, node_rect_min + ImVec2(m_Size.x, 18.0f), IM_COL32(40, 40, 40, 255), 2.0f);
		ImGui::SetCursorScreenPos(node_rect_min + NODE_FONT_POS);	//ÉmÅ[ÉhÇÃï∂éöÇï`âÊÇ∑ÇÈpos
		ImGui::SetWindowFontScale(1.0f);
		ImGui::TextColored(ImColor::Vec4::WHITE, "%s", m_Name.c_str());

#ifdef DEBUG
	ResouceRender( offset, 	draw_list);
	draw_list->ChannelsSetCurrent(0); // input_slot
	ImGui::SetCursorScreenPos(ImVec2(m_Pos.x + offset.x, m_Pos.y + offset.y-15.0f));
	if (ImGui::Button("Save"))
	{
		is_save = true;
	}
	else
	{
		is_save = false;
	}
	if (is_save)
	{
		TextureFileIO::SaveTexture("ts", ".jpg", m_resouce->Texture2D);
	}
#endif
	//	RenderTarget::set(m_resouce->RenderTargetView, Dxgi::get_dsv());
	////			Device::get_context()->PSSetShaderResources(0, 1, m_resouce->ShaderResourceView.GetAddressOf());
	//	m_preview->render(0, math::FVector2(0, 0), math::FVector2(m_Size.x, m_Size.x), 0, FixColor::Red);
	//	draw_list->ChannelsSetCurrent(4); // input_slot
	//	ImGui::SetCursorScreenPos(ImVec2(m_Pos.x + offset.x, m_Pos.y + m_Size.y + offset.y));
	//	ImGui::Image(m_resouce->ShaderResourceView.Get(), ImVec2(m_Size.x, m_Size.x), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 1));
	//	Device::get_context()->OMSetRenderTargets(1, Dxgi::get_rtv().GetAddressOf(), Dxgi::get_dsv().Get());

	}

	void	NodeBase::i_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		for (int i = 0; i < m_inputs_count; i++)
		{
			m_input_pos[i] = offset + GetInputSlotPos(i);
			m_input_pos[i].y += 10.0f;
			draw_list->ChannelsSetCurrent(1);
			ImGui::SetCursorScreenPos(m_input_pos[i] + ImVec2(10.0f, -SLOT_INPUT_FLOAT));
			ImGui::SetWindowFontScale(0.9f);
			ImGui::TextColored(ImColor::Vec4::WHITE, "%s", m_input_name[i].c_str());
			NodeFunction::NodeCircle(draw_list, m_input_pos[i], NODE_SLOT_RADIUS, m_input_slot_color[i], m_input_slot_type[i]);

			draw_list->ChannelsSetCurrent(0); // input_slot
			if (!m_is_input[i])
			{
				draw_list->AddLine(m_input_pos[i] + ImVec2(-20, 0), m_input_pos[i], ImColor::U32::GREEN, 1.0f);

				NodeFunction::InputRectDraw(draw_list, m_input_pos[i], m_input_slot_type[i]);
			}


			draw_list->ChannelsSetCurrent(1);
			if (physics::Collider2D::sphere_and_sphere(math::FVector2(m_input_pos[i].x, m_input_pos[i].y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
			{
				draw_list->AddCircleFilled(m_input_pos[i], NODE_SLOT_RADIUS - 2, ImColor::U32::GREEN);
			}
		}
	}

	void	NodeBase::o_update(ImVec2 offset, ImDrawList*	draw_list)
	{
		for (int i = 0; i < m_outputs_count; i++)
		{
			m_output_pos[i] = offset + this->GetOutputSlotPos(i);
			m_output_pos[i].y += 10.0f;

			//float x = m_output_name[i].size()*10.0f;
			//x=std::clamp(x, 0.0f, 30.0f);
			draw_list->ChannelsSetCurrent(1); // input_slot
			ImGui::SetCursorScreenPos(m_output_pos[i] + ImVec2(-60.0f, -SLOT_INPUT_FLOAT));

			//ImGui::SetCursorScreenPos(m_output_pos[i] + ImVec2(-60.0f+x, -SLOT_INPUT_FLOAT));
			ImGui::SetWindowFontScale(0.9f);
			ImGui::TextColored(ImColor::Vec4::WHITE, "%s", m_output_name[i].c_str());
			NodeFunction::NodeCircle(draw_list, m_output_pos[i], NODE_SLOT_RADIUS, m_output_slot_color[i], m_output_slot_type[i]);
			if (physics::Collider2D::sphere_and_sphere(math::FVector2(m_output_pos[i].x, m_output_pos[i].y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
			{
				draw_list->AddCircleFilled(m_output_pos[i], NODE_SLOT_RADIUS - 2, ImColor::U32::RED);
			}
		}
	}

	void	NodeBase::str_check(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		switch (m_node_type)
		{
		case NODE_TYPE::NORMAL:
		case NODE_TYPE::VARIABLE:
			str_set(nodes_ptr, links);
			break;
		case NODE_TYPE::DYNAMIC:
			type_set(nodes_ptr, links);
			str_set(nodes_ptr, links);
			link_set(links);
			break;
		case NODE_TYPE::MASTER:
			str_set(nodes_ptr, links);
			break;
		}
	}

	//mainä÷êî
	void	NodeBase::function_call_update(std::string	func_name)
	{
	}

	ImVec2 NodeBase::GetInputSlotPos(int slot_no) const
	{
		return ImVec2(m_Pos.x + SLOT_POS,
			m_Pos.y + m_Size.y * (static_cast<float>(slot_no) + 1) / (static_cast<float>(m_inputs_count) + 1));
	}
	ImVec2 NodeBase::GetOutputSlotPos(int slot_no) const
	{
		return ImVec2(m_Pos.x + m_Size.x - SLOT_POS,
			m_Pos.y + m_Size.y * (static_cast<float>(slot_no) + 1) / (static_cast<float>(m_outputs_count) + 1));
	}
	std::string	NodeBase::get_shader_str()
	{
		return	m_function_call_str;
	}


	std::string	NodeBase::get_function_call_str()
	{
		return	m_function_call_str;
	}

	std::vector<std::string>&	NodeBase::GetOutStr()
	{
		return m_out_str;
	}

	std::vector<std::string>&	NodeBase::GetInputStr()
	{
		return m_input_str;
	}


	void NodeBase::type_set(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		//ìÆìIÇ»node
		/*
			input slotÇ…ì¸Ç¡ÇƒÇ¢ÇÈà¯êîÇÃå^Ç™è¨Ç≥Ç¢ÇŸÇ§Ç…çáÇÌÇπÇÈ(VEC1ÇÕó·äO)
		*/

		//ÇªÇ‡ÇªÇ‡åqÇ™Ç¡ÇƒÇ¢ÇÈÇÃÇ©
		for (auto& l : links)
		{
			if (m_ID == l.get_input_id())
			{
				//output nodeÇ©ÇÁïœêîéÊìæ
				//out -in
				m_input_str[l.get_input_slot()] = nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()];
				//å^ÇçáÇÌÇπÇÈ
				//å^Ç™àÍívÇµÇ»Ç¢
				if (m_input_slot_type[l.get_input_slot()] != l.get_output_type())
				{
					switch (m_input_slot_type[l.get_input_slot()])
					{
					case	SLOT_TYPE::VECTOR1:
						m_input_slot_type[l.get_input_slot()] = l.get_output_type();
						break;
					case	SLOT_TYPE::VECTOR2:
						//if (m_input_slot_type[l.get_input_slot()] != SLOT_TYPE::VECTOR1)
						//{
						//	m_input_slot_type[l.get_input_slot()] = l.get_output_type();
						//}
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	break;
						case	SLOT_TYPE::VECTOR3:
						case	SLOT_TYPE::VECTOR4:	m_input_str[l.get_input_slot()] += ".xy";	break;
						}

						break;
					case	SLOT_TYPE::VECTOR3:
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	m_input_slot_type[l.get_input_slot()] = l.get_output_type();	break;
						case	SLOT_TYPE::VECTOR3:	break;
						case	SLOT_TYPE::VECTOR4:	m_input_str[l.get_input_slot()] += ".xyz";	break;
						}
						break;
					case	SLOT_TYPE::VECTOR4:
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	m_input_slot_type[l.get_input_slot()] = l.get_output_type();	break;
						case	SLOT_TYPE::VECTOR3:	m_input_slot_type[l.get_input_slot()] = l.get_output_type();	break;
						case	SLOT_TYPE::VECTOR4:	break;
						}
						break;
					}
				}
			}
		}
		for (int i = 0; i < m_inputs_count; i++)
		{
			for (int j = i + 1; j < m_inputs_count; j++)
			{
				if (m_input_slot_type[i] != m_input_slot_type[j])
				{
					if (m_input_slot_type[i] == SLOT_TYPE::VECTOR1)	m_input_slot_type[i] = m_input_slot_type[j];	break;
					if (m_input_slot_type[j] == SLOT_TYPE::VECTOR1)	m_input_slot_type[j] = m_input_slot_type[i];	break;

					if (static_cast<int>(m_input_slot_type[i]) < static_cast<int>(m_input_slot_type[j]))
					{
						m_input_slot_type[j] = m_input_slot_type[i];
						m_output_slot_type[0] = m_input_slot_type[i];
						break;
					}
					else
					{
						m_input_slot_type[i] = m_input_slot_type[j];
						m_output_slot_type[0] = m_input_slot_type[j];
						break;
					}
				}
			}
		}
	}

	//à¯êîÇ…ì¸ÇÍÇÈÇ∆Ç´
	void	NodeBase::str_set(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		for (auto& l : links)
		{
			if (m_ID == l.get_input_id())
			{
				//éhÇ≥Ç¡ÇΩèÛë‘
				m_is_input[l.get_input_slot()] = true;
				//linedata_set
				m_input_links[l.get_input_slot()] = { l.get_output_id(),l.get_input_slot() };
				//output nodeÇ©ÇÁïœêîéÊìæ
				m_input_str[l.get_input_slot()] = nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()];
				//å^ÇçáÇÌÇπÇÈ
				if (m_input_slot_type[l.get_input_slot()] != l.get_output_type())
				{
					switch (m_input_slot_type[l.get_input_slot()])
					{
					case	SLOT_TYPE::VECTOR1:	m_input_str[l.get_input_slot()] += ".x";	break;
					case	SLOT_TYPE::VECTOR2:
					case	SLOT_TYPE::UV:
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	break;
						case	SLOT_TYPE::VECTOR3:	m_input_str[l.get_input_slot()] += ".xy"; break;
						case	SLOT_TYPE::VECTOR4:m_input_str[l.get_input_slot()] += ".xy"; break;
						}
						break;
					case	SLOT_TYPE::VECTOR3:
					case	SLOT_TYPE::COLOR:
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	m_input_str[l.get_input_slot()] = "float3(" + nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()] + ", 0.0)";	break;
						case	SLOT_TYPE::VECTOR3:	break;
						case	SLOT_TYPE::VECTOR4:	m_input_str[l.get_input_slot()] += ".xyz";	break;
						}
						break;
					case	SLOT_TYPE::VECTOR4:
						switch (l.get_output_type())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	m_input_str[l.get_input_slot()] = "float4(" + nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()] + ",0.0, 0.0)";	break;
						case	SLOT_TYPE::VECTOR3:	m_input_str[l.get_input_slot()] = "float4(" + nodes_ptr[l.get_output_id()]->GetOutStr()[l.get_output_slot()] + "0.0)";	break;
						case	SLOT_TYPE::VECTOR4:	break;
						}
						break;
					}
				}
			}
		}

		for (auto& i : m_input_str)
		{
			m_function_call_str += i + ",";
		}
		for (auto& o : m_out_str)
		{
			m_function_call_str += o + ",";
		}
		m_function_call_str.pop_back();
		m_function_call_str += ");\n";
	}
	void NodeBase::link_set(std::vector<NodeLink>&	links)
	{
		for (auto& l : links)
		{
			if (m_ID == l.get_output_id())	l.set_output_type(m_dynamic_slot_type);
		}
	}


	//NodeLink

	//ÉmÅ[ÉhÇÇ¬Ç»Ç∞ÇÈ
	NodeLink::NodeLink()
	{
	}
	NodeLink::NodeLink(int output_id, int output_slot, int input_id, int input_slot)
		:m_output({ output_id ,output_slot }), m_output_type(SLOT_TYPE::VECTOR1),
		m_input({ input_id, input_slot }), m_input_type(SLOT_TYPE::VECTOR1),
		m_is_hit(false),
		m_is_delete(false)
	{
	}

	NodeLink::NodeLink(int output_id, int output_slot, SLOT_TYPE output_type, int input_id, int input_slot, SLOT_TYPE input_type)
		: m_output({ output_id ,output_slot }), m_output_type(output_type), m_input({ input_id, input_slot }), m_input_type(input_type)
	{
	}
	NodeLink::~NodeLink()
	{
	}


	int	NodeLink::get_output_id()
	{
		return	m_output.id;
	}
	int	NodeLink::get_output_slot()
	{
		return	m_output.slot;
	}
	SLOT_TYPE NodeLink::get_output_type()
	{
		return m_output_type;
	}
	void NodeLink::set_output_type(SLOT_TYPE type)
	{
		m_output_type = type;
	}

	//right
	int	NodeLink::get_input_id()
	{
		return	m_input.id;
	}
	int	NodeLink::get_input_slot()
	{
		return	m_input.slot;
	}
	SLOT_TYPE NodeLink::get_input_type()
	{
		return m_input_type;
	}

	void NodeLink::set_input_type(SLOT_TYPE type)
	{
		m_input_type = type;
	}

	//Debug Text
	std::string  NodeLink::StateStr()
	{
		return
			"out id " + std::to_string(m_output.id) + " " +
			"out slot " + std::to_string(m_output.slot) + " " +
			"in id " + std::to_string(m_input.id) + " " +
			"in slot " + std::to_string(m_input.slot);
	}
}