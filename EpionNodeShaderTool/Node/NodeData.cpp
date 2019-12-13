#include	"../All.h"
#include	"../epion.h"

#include	"../../../imgui\\imgui.h"
#include	"../../../imgui\\imgui_internal.h"

#include	"NodeData.h"

#include	"NodeParam.h"
#include	"NodeFunction.h"
#include	"../epion_physics/epion_collider.h"

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
//#define DEBUG
namespace epion
{
	std::unique_ptr<Texture>	m_resouce;
	std::unique_ptr<Square>		m_preview;
	std::unique_ptr<VertexShader>	m_vertex;
	std::unique_ptr<PixelShader>	m_pixel;
	bool is_save;
	com_ptr<ID3D11DepthStencilView>	depth_view;

}
namespace	epion::Node
{
	NodeBase::NodeBase(int inputs_count, int outputs_count)
		:m_inputs_count(inputs_count), m_outputs_count(outputs_count)
	{
		Initialize();
	}

	NodeBase::NodeBase(std::string name, int id, const epion::math::FVector2& pos, int inputs_count, int outputs_count)
		:m_Name(name),
		m_ID(id),
		m_Pos(pos),
		m_inputs_count(inputs_count),
		m_outputs_count(outputs_count),
		m_function_call_str(""),
		m_dynamic_slot_type(SLOT_TYPE::VECTOR1),
		m_is_push(false)
	{
		Initialize();
#ifdef DEBUG
		ResouceInit();
#endif
	}

	void NodeBase::Initialize()
	{
		//m_is_slot_input.reserve(m_inputs_count);
		//assert(m_is_slot_input.capacity() >= m_inputs_count);
		for (int i = 0; i < m_inputs_count; i++)
		{
			m_is_slot_input.push_back(INPUT_SLOT_STATE::ZERO);

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
		if (m_inputs_count == 1 && m_outputs_count == 1)
		{
			m_Size = { 130.0f,55.0f};
		}

		if (m_inputs_count == 0)
		{
			m_Size = { 55.0f *m_outputs_count +30.0f,55.0f*m_outputs_count };
		}

	}
	void NodeBase::Finalize()
	{}

	void	NodeBase::TitleDraw(ImVec2& offset, ImDrawList*	draw_list)
	{
		ImVec2 node_rect_size = m_draw_pos+ m_Size;
		ImVec2 node_rect_max2 =m_draw_pos + ImVec2(m_Size.x*0.5f, m_Size.y);

		draw_list->AddRectFilled(m_draw_pos, node_rect_size, RECT_COLOR, 2.0f);

		if (m_node_type != NODE_TYPE::MASTER)	draw_list->AddRectFilled(m_draw_pos, node_rect_max2, RECT_COLOR, 2.0f);
		draw_list->AddRectFilled(m_draw_pos, m_draw_pos + ImVec2(m_Size.x, 18.0f), TITLE_BAR_COLOR, 2.0f);
		ImGui::SetCursorScreenPos(m_draw_pos + NODE_FONT_ADD_POS);	//ÉmÅ[ÉhÇÃÉ^ÉCÉgÉãï`âÊÇÃç¿ïWÇéwíË
		ImGui::TextColored(ImColors::Vec4::WHITE, "%s", m_Name.c_str());
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
	//	Device::get_context()->OMSetRenderTargets(1, Dxgi::GetRTV().GetAddressOf(), Dxgi::get_dsv().Get());

	}

	void	NodeBase::DrawUpdate(ImVec2 offset, ImDrawList*	draw_list)
	{
		assert(m_is_slot_input.size() == m_inputs_count);
		draw_list->ChannelsSetCurrent(1);
		ImVec2 node_rect_size = m_draw_pos + m_Size;
		if (m_is_push)
		{
			draw_list->AddRect(m_draw_pos, node_rect_size, ImColors::U32::GREEN, 7.0f);
		}
		else
		{
			draw_list->AddRect(m_draw_pos, node_rect_size, ImColors::U32::ZERO, 7.0f);
		}

		for (int i = 0; i < m_inputs_count; i++)
		{
			m_input_pos[i] = offset + GetInputSlotPos(i);
			m_input_pos[i].y += 10.0f;
			ImGui::SetCursorScreenPos(m_input_pos[i] + ImVec2(10.0f, -SLOT_INPUT_FLOAT));
			ImGui::TextColored(ImColors::Vec4::WHITE, "%s", m_input_name[i].c_str());
			NodeFunction::NodeCircle(draw_list, m_input_pos[i], NODE_SLOT_RADIUS, m_input_slot_color[i], m_input_slot_type[i]);

			if (physics::Collider2D::SphereAndSphere(math::FVector2(m_input_pos[i].x, m_input_pos[i].y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
			{
				draw_list->AddCircleFilled(m_input_pos[i], NODE_SLOT_RADIUS - 2, ImColors::U32::GREEN);
			}
		}
		for (int i = 0; i < m_outputs_count; i++)
		{
			m_output_pos[i] = offset + GetOutputSlotPos(i);
			m_output_pos[i].y += 10.0f;

			ImGui::SetCursorScreenPos(m_output_pos[i] + ImVec2(-60.0f, -SLOT_INPUT_FLOAT));

			ImGui::TextColored(ImColors::Vec4::WHITE, "%s", m_output_name[i].c_str());
			NodeFunction::NodeCircle(draw_list, m_output_pos[i], NODE_SLOT_RADIUS, m_output_slot_color[i], m_output_slot_type[i]);
			if (physics::Collider2D::SphereAndSphere(math::FVector2(m_output_pos[i].x, m_output_pos[i].y), math::FVector2(ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y), NODE_SLOT_RADIUS, 2.0f))
			{
				draw_list->AddCircleFilled(m_output_pos[i], NODE_SLOT_RADIUS - 2, ImColors::U32::RED);
			}
		}

		draw_list->ChannelsSetCurrent(0); // input_slot
		for (int i = 0; i < m_inputs_count; i++)
		{
			if (m_is_slot_input[i] !=INPUT_SLOT_STATE::ONE)
			{
				draw_list->AddLine(m_input_pos[i] + ImVec2(-20, 0), m_input_pos[i], ImColors::U32::GREEN, 1.0f);
				NodeFunction::InputRectDraw(draw_list, m_input_pos[i], m_input_slot_type[i]);
			}
		}
	}
	void NodeBase::SetDrawPos(ImVec2& vec2)
	{
		m_draw_pos = vec2 + ImGuiFunction::GetImVec2(m_Pos);
	}

	void	NodeBase::StrCheck(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		switch (m_node_type)
		{
		case NODE_TYPE::NORMAL:
		case NODE_TYPE::VARIABLE:
			StrSet(nodes_ptr, links);
			break;
		case NODE_TYPE::DYNAMIC:
			TypeSet(nodes_ptr, links);
			StrSet(nodes_ptr, links);
			LinkSet(links);
			break;
		case NODE_TYPE::MASTER:
			StrSet(nodes_ptr, links);
			break;
		}
	}

	//mainä÷êî
	void	NodeBase::FunctionCallUpdate(std::string	func_name)
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
	//test
	void	NodeBase::ResouceInit()
	{
		m_resouce = std::make_unique<Texture>();
		m_vertex = std::make_unique<VertexShader>(L"HLSLShader\\square_vertex_shader.hlsl");
		m_pixel = std::make_unique<PixelShader>(L"test.hlsl");
		m_preview = std::make_unique<Square>(m_vertex->GetBlob());
		is_save = false;
		com_ptr<ID3D11Texture2D>	depth_stencil_buffer;

		D3D11_TEXTURE2D_DESC	texture_desc;

		texture_desc.Width = static_cast<UINT>(m_Size.x);
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
		//ID3D11RenderTargetView* dummyRTVs[D3D11_SIMULTANEOUS_RENDER_TARGET_COUNT] = { nullptr };
		//ID3D11ShaderResourceView* dummySRVs[D3D11_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT] = { nullptr };

		//Device::GetContext()->OMSetRenderTargets(_countof(dummyRTVs), dummyRTVs, nullptr);
		//Device::GetContext()->PSSetShaderResources(0, _countof(dummySRVs), dummySRVs);
		Device::GetContext()->OMSetRenderTargets(0, m_resouce->RenderTargetView.GetAddressOf(), Dxgi::GetDSV().Get());
		float color[4] = { 1,0,0,0 };
		Device::GetContext()->ClearRenderTargetView(m_resouce->RenderTargetView.Get(), color);
		Device::GetContext()->ClearDepthStencilView(Dxgi::GetDSV().Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
		Device::GetContext()->PSSetShaderResources(0, 1, m_resouce->m_shader_resource.GetAddressOf());
		m_preview->Render(math::FVector2(0, 0), math::FVector2(m_Size.x, m_Size.x), 0, FixColor::Red);
		draw_list->ChannelsSetCurrent(4); // input_slot
		ImGui::SetCursorScreenPos(ImVec2(m_Pos.x + offset.x, m_Pos.y + m_Size.y + offset.y));
		ImGui::Image(m_resouce->m_shader_resource.Get(), ImVec2(m_Size.x, m_Size.x), ImVec2(0, 0), ImVec2(1, 1), ImVec4(1, 1, 1, 1), ImVec4(0, 0, 0, 1));
	}

	void	NodeBase::ResouceCreate()
	{
	}


	void NodeBase::TypeSet(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		//ìÆìIÇ»node
		/*
			input slotÇ…ì¸Ç¡ÇƒÇ¢ÇÈà¯êîÇÃå^Ç™è¨Ç≥Ç¢ÇŸÇ§Ç…çáÇÌÇπÇÈ(VEC1ÇÕó·äO)
		*/

		//ÇªÇ‡ÇªÇ‡åqÇ™Ç¡ÇƒÇ¢ÇÈÇÃÇ©
		for (auto& l : links)
		{
			if (m_ID == l.GetInputID())
			{
				//output nodeÇ©ÇÁïœêîéÊìæ
				//out -in
				m_input_str[l.GetInputSlot()] = nodes_ptr[l.GetOutputID()]->GetOutStr()[l.GetOutputSlot()];
				//å^ÇçáÇÌÇπÇÈ
				//å^Ç™àÍívÇµÇ»Ç¢
				if (m_input_slot_type[l.GetInputSlot()] != l.GetOutputType())
				{
					switch (m_input_slot_type[l.GetInputSlot()])
					{
					case	SLOT_TYPE::VECTOR1:
						m_input_slot_type[l.GetInputSlot()] = l.GetOutputType();
						break;
					case	SLOT_TYPE::VECTOR2:
						//if (m_input_slot_type[l.GetInputSlot()] != SLOT_TYPE::VECTOR1)
						//{
						//	m_input_slot_type[l.GetInputSlot()] = l.GetOutputType();
						//}
						switch (l.GetOutputType())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	break;
						case	SLOT_TYPE::VECTOR3:
						case	SLOT_TYPE::VECTOR4:	m_input_str[l.GetInputSlot()] += ".xy";	break;
						}

						break;
					case	SLOT_TYPE::VECTOR3:
						switch (l.GetOutputType())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	m_input_slot_type[l.GetInputSlot()] = l.GetOutputType();	break;
						case	SLOT_TYPE::VECTOR3:	break;
						case	SLOT_TYPE::VECTOR4:	m_input_str[l.GetInputSlot()] += ".xyz";	break;
						}
						break;
					case	SLOT_TYPE::VECTOR4:
						switch (l.GetOutputType())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	m_input_slot_type[l.GetInputSlot()] = l.GetOutputType();	break;
						case	SLOT_TYPE::VECTOR3:	m_input_slot_type[l.GetInputSlot()] = l.GetOutputType();	break;
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
	void	NodeBase::StrSet(std::vector<std::unique_ptr<NodeBase>>&	nodes_ptr, std::vector<NodeLink>&	links)
	{
		for (auto& l : links)
		{
			if (m_ID == l.GetInputID())
			{
				//éhÇ≥Ç¡ÇΩèÛë‘
				//if (m_is_slot_input[l.GetInputSlot()] == INPUT_SLOT_STATE::ZERO)
				{
					m_is_slot_input[l.GetInputSlot()] = INPUT_SLOT_STATE::ONE;
				}
				//linedata_set
				m_input_links[l.GetInputSlot()] = { l.GetOutputID(),l.GetInputSlot() };
				//output nodeÇ©ÇÁïœêîéÊìæ
				m_input_str[l.GetInputSlot()] = nodes_ptr[l.GetOutputID()]->GetOutStr()[l.GetOutputSlot()];
				//å^ÇçáÇÌÇπÇÈ
				if (m_input_slot_type[l.GetInputSlot()] != l.GetOutputType())
				{
					switch (m_input_slot_type[l.GetInputSlot()])
					{
					case	SLOT_TYPE::VECTOR1:	m_input_str[l.GetInputSlot()] += ".x";	break;
					case	SLOT_TYPE::VECTOR2:
					case	SLOT_TYPE::UV:
						switch (l.GetOutputType())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	break;
						case	SLOT_TYPE::VECTOR3:	m_input_str[l.GetInputSlot()] += ".xy"; break;
						case	SLOT_TYPE::VECTOR4:m_input_str[l.GetInputSlot()] += ".xy"; break;
						}
						break;
					case	SLOT_TYPE::VECTOR3:
					case	SLOT_TYPE::COLOR:
						switch (l.GetOutputType())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	m_input_str[l.GetInputSlot()] = "float3(" + nodes_ptr[l.GetOutputID()]->GetOutStr()[l.GetOutputSlot()] + ", 0.0)";	break;
						case	SLOT_TYPE::VECTOR3:	break;
						case	SLOT_TYPE::VECTOR4:	m_input_str[l.GetInputSlot()] += ".xyz";	break;
						}
						break;
					case	SLOT_TYPE::VECTOR4:
						switch (l.GetOutputType())
						{
						case	SLOT_TYPE::VECTOR1:	break;
						case	SLOT_TYPE::VECTOR2:	m_input_str[l.GetInputSlot()] = "float4(" + nodes_ptr[l.GetOutputID()]->GetOutStr()[l.GetOutputSlot()] + ",0.0, 0.0)";	break;
						case	SLOT_TYPE::VECTOR3:	m_input_str[l.GetInputSlot()] = "float4(" + nodes_ptr[l.GetOutputID()]->GetOutStr()[l.GetOutputSlot()] + "0.0)";	break;
						case	SLOT_TYPE::VECTOR4:	break;
						}
						break;
					}
				}
			}
			else
			{
				//m_is_slot_input[l.GetInputSlot()]	=false;
				//m_is_slot_input[l.GetInputSlot()] =INPUT_SLOT_STATE::ZERO;
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
	void NodeBase::LinkSet(std::vector<NodeLink>&	links)
	{
		for (auto& l : links)
		{
			if (m_ID == l.GetOutputID())	l.set_output_type(m_dynamic_slot_type);
		}
	}


	//NodeLink

	//ÉmÅ[ÉhÇÇ¬Ç»Ç∞ÇÈ
	NodeLink::NodeLink()
	{
	}
	NodeLink::NodeLink(int output_id,int output_slot, int input_id, int input_slot)
		:m_output({ output_id ,output_slot }), m_output_type(SLOT_TYPE::VECTOR1),
		m_input({ input_id, input_slot }), m_input_type(SLOT_TYPE::VECTOR1),
		m_is_hit(false),	m_is_delete_menu(false)
	{
	}

	NodeLink::NodeLink(int output_id, int output_slot, SLOT_TYPE output_type, int input_id, int input_slot, SLOT_TYPE input_type)
		: m_output({ output_id ,output_slot }), m_output_type(output_type), m_input({ input_id, input_slot }), m_input_type(input_type)
	{
	}
	NodeLink::~NodeLink()
	{
	}


	int	NodeLink::GetOutputID()
	{
		return	m_output.id;
	}
	int	NodeLink::GetOutputSlot()
	{
		return	m_output.slot;
	}
	SLOT_TYPE NodeLink::GetOutputType()
	{
		return m_output_type;
	}
	void NodeLink::set_output_type(SLOT_TYPE type)
	{
		m_output_type = type;
	}

	//right
	int	NodeLink::GetInputID()
	{
		return	m_input.id;
	}
	int	NodeLink::GetInputSlot()
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
	std::string NodeLink::StateStr()
	{
		return
			"out id " + std::to_string(m_output.id) + " " +
			"out slot " + std::to_string(m_output.slot) + " " +
			"in id " + std::to_string(m_input.id) + " " +
			"in slot " + std::to_string(m_input.slot);
	}
}