#include"Menu.h"
#include "../Includes.h"
#include "../ImGui/imgui_notify.h"
#include "../Features/Global.h"
#include "../kmbox/KMSeria.h"
#include "../Config/JsonSystem.h"
#include "../Game.h"

int 菜单位置 = 0;

static bool open = true;

bool ESP_Lite1;

float HuaKuaiTiao = 1.0;
bool 是否初始化 = false;
static ImGuiColorEditFlags alpha_flags = 0;
int CUSTOM_CA = 32;
int CUSTOM_KEY = 32;
int CUSTOM_KEY1 = 32;
int CUSTOM_KEY2 = 32;
static char WBtxt0[128] = "1920";
static char WBtxt1[128] = "1080";

bool Box_State = false;
char Box_State_buffer[256];
static int BOX_3 = 0;

int window_menu_button_position = 0;
int 跳过击倒 = 0;
int 算法 = 0;

static float  yizhi_default = 1.000f;
const float   yizhi_min = 0.100f;
const float   yizhi_max = 2.000f;


static int InputTextCallback(ImGuiInputTextCallbackData* data) {
	if (data->EventFlag == ImGuiInputTextFlags_CallbackResize) {
		// Resize string callback
		std::string* str = (std::string*)data->UserData;
		IM_ASSERT(data->Buf == str->c_str());
		str->resize(data->BufTextLen);
		data->Buf = (char*)str->c_str();
	}
	return 0;
}
//————————————————————————————————————————————————————
void Helpmarker(const char* Text, ImVec4 Color)
{
	ImGui::TextColored(Color, u8"(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip(Text);
	}
}
//————————————————————————————————————————————————————
void Gui::自定义菜单()
{
	ImGuiStyle& style = ImGui::GetStyle();
	//printf_s("%u", 是否初始化);

	if (是否初始化 == false)
	{
		主题初始化();
		是否初始化 = true;
		G::kmbox.取可用串口();
		printf_s("HACK:%u\n", 是否初始化);
	}

	ImGui::SetNextWindowBgAlpha(0);//透明度
	//ImGui::StyleColorsClassic();//主题 -> 设置 UI 样式为经典主题(垃圾东西)
	ImGui::SetNextWindowSize({ 810,695 }, 0 << 3);//置主窗口大小
	ImGui::Begin("LiuTeam", &open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);//主窗口
	//ImGui::Begin("##LiuTeam", &open, ImGuiWindowFlags_NoScrollbar & ImGuiWindowFlags_NoScrollWithMouse & ImGuiWindowFlags_NoBackground & ImGuiWindowFlags_NoDecoration);
	{
		ImGui::SetNextWindowBgAlpha(255);
		ImGui::PushStyleVar(7, 5);//圆角角度 开始
		ImGui::SetCursorPos({ 7,4 });//置组件坐标
		//————————————————————————————————————————————
		ImGui::SetCursorPos(ImVec2(5, 5)); //置组件坐标
		if (ImGui::BeginChild("##顶部菜单", { 800,53 }, false, 256))// 子窗口
		{
			//ImGui::TextGradiented(u8" LiuTeam", 0xF99B7D, 0xA0D8B3, 66);
			//ImGui::SameLine();
			//ImGui::SetCursorPos(ImVec2(60, 16)); //置组件坐标

			ImGui::SetCursorPos(ImVec2(5, 5)); //置组件坐标
			//ImGui::Image(g_pSRV, { 44,44 });//图片组件
		}
		ImGui::PopStyleVar();//圆角结束
		ImGui::EndChild();//子窗口结束
		//————————————————————————————————————————————
		Gui::左边选择菜单();
		//————————————————————————————————————————————
		if (菜单位置 == 0)
		{
			Gui::主页菜单();
		}
		if (菜单位置 == 1)
		{
			Gui::透视菜单();
		}
		if (菜单位置 == 2)
		{
			Gui::自瞄菜单();
		}
		if (菜单位置 == 3)
		{
			Gui::杂项菜单();
		}
		if (菜单位置 == 4)
		{
			Gui::设置菜单();
		}
		//————————————————————————————————————————————

		ImGui::PushFont(font_text3);//字体开始
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f); // 样式
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));  // 样式
		ImGui::RenderNotifications(); // 渲染
		ImGui::PopStyleVar(1); // Don't forget to Pop()
		ImGui::PopStyleColor(1);
		ImGui::PopFont();//字体结束

		ImGui::End();//主窗口结束
	}
}
//————————————————————————————————————————————————————
void Gui::主题初始化()
{
	ImGuiStyle& style = ImGui::GetStyle();

	style.WindowRounding = 3;
	style.FrameRounding = 4;
	style.GrabRounding = 12;
	style.GrabMinSize = 9;
	style.ScrollbarSize = 11;

	style.FramePadding = { 6,0 };
	style.WindowPadding = { 6,8 };
	style.ItemSpacing = { 6.5,2 };
	style.ButtonTextAlign = { 0.5,0.65 };

	ImVec4* Colors = ImGui::GetStyle().Colors;
	Colors[ImGuiCol_ChildBg] = ImGui::HexToImVec4("191717", 255); // 背景颜色

	Colors[ImGuiCol_Text] = ImGui::HexToImVec4("FFFFFF", 255); // 文本颜色
	Colors[ImGuiCol_CheckMark] = ImGui::HexToImVec4("FFFFFF", 255); // 填选框颜色
	Colors[ImGuiCol_SliderGrab] = ImGui::HexToImVec4("FFFFFF", 255); // 滑块条颜色
	Colors[ImGuiCol_SliderGrabActive] = ImGui::HexToImVec4("FAC8FA", 255); // 滑块条按下颜色

	Colors[ImGuiCol_Button] = ImGui::HexToImVec4("D8D9DA", 50); // 按钮颜色
	Colors[ImGuiCol_ButtonHovered] = ImGui::HexToImVec4("D8D9DA", 100); // 按钮热点颜色
	Colors[ImGuiCol_ButtonActive] = ImGui::HexToImVec4("D8D9DA", 50); // 按钮按下颜色

	Colors[ImGuiCol_FrameBg] = ImGui::HexToImVec4("D8D9DA", 50); // 组件背景颜色
	Colors[ImGuiCol_FrameBgHovered] = ImGui::HexToImVec4("D8D9DA", 50); // 组件背景热点颜色
	Colors[ImGuiCol_FrameBgActive] = ImGui::HexToImVec4("61677A", 50); // 组件背景按下颜色

	Colors[ImGuiCol_Tab] = ImGui::HexToImVec4("D8D9DA", 50); // TAB颜色
	Colors[ImGuiCol_TabHovered] = ImGui::HexToImVec4("D8D9DA", 130); // TAB热点颜色
	Colors[ImGuiCol_TabActive] = ImGui::HexToImVec4("D8D9DA", 130); // TAB按下颜色

	Colors[ImGuiCol_Header] = ImGui::HexToImVec4("D8D9DA", 50); // 下拉框选中颜色
	Colors[ImGuiCol_HeaderHovered] = ImGui::HexToImVec4("D8D9DA", 130); // 下拉框热点颜色
	Colors[ImGuiCol_HeaderActive] = ImGui::HexToImVec4("D8D9DA", 130); // 下拉框按下颜色
	//----
	//Colors[ImGuiCol_TextDisabled] = ImGui::HexToImVec4("3D3B4A", 255); // 不可用文本的颜色
	//Colors[ImGuiCol_WindowBg] = ImGui::HexToImVec4("0F0E11", 255); // 窗口背景的颜色
	//Colors[ImGuiCol_PopupBg] = ImGui::HexToImVec4("121217", 255); // 弹出窗口背景的颜色
	
	//Colors[ImGuiCol_Border] = ImGui::HexToImVec4("F7EFE5",100); // 设置边框的颜色。
	//Colors[ImGuiCol_BorderShadow] = ImGui::HexToImVec4("EBE8E0", 0); // 边框阴影的颜色
	//Colors[ImGuiCol_TitleBg] = ImGui::HexToImVec4("19171F", 255); // 标题背景的颜色
	//Colors[ImGuiCol_TitleBgCollapsed] = ImGui::HexToImVec4("FFF8F2", 191); // 折叠标题的背景颜色
	//Colors[ImGuiCol_TitleBgActive] = ImGui::HexToImVec4("121217", 255); // 活动标题背景的颜色
	//Colors[ImGuiCol_MenuBarBg] = ImGui::HexToImVec4("19171F", 255); // 菜单栏背景的颜色
	//Colors[ImGuiCol_ScrollbarBg] = ImGui::HexToImVec4("19171F", 255); // 滚动条背景的颜色
	//Colors[ImGuiCol_ScrollbarGrab] = ImGui::HexToImVec4("CDCDD4", 79); // 滚动条抓手的颜色
	//Colors[ImGuiCol_ScrollbarGrabHovered] = ImGui::HexToImVec4("8F8F94", 255); // 鼠标悬停在滚动条抓手上时的颜色
	//Colors[ImGuiCol_ScrollbarGrabActive] = ImGui::HexToImVec4("0F0E11", 255); // 活动滚动条抓手的颜色
	//Colors[ImGuiCol_ResizeGrip] = ImGui::HexToImVec4("000000", 0); // 调整大小把手的颜色
	//Colors[ImGuiCol_ResizeGripHovered] = ImGui::HexToImVec4("8F8F94", 255); // 鼠标悬停在调整大小把手上时的颜色
	//Colors[ImGuiCol_ResizeGripActive] = ImGui::HexToImVec4("0F0E11", 255); // 活动调整大小把手的颜色
	//Colors[ImGuiCol_PlotLines] = ImGui::HexToImVec4("646362", 161); // 绘图线条的颜色
	//Colors[ImGuiCol_PlotLinesHovered] = ImGui::HexToImVec4("40FF00", 255); // 鼠标悬停在绘图线条上时的颜色
	//Colors[ImGuiCol_PlotHistogram] = ImGui::HexToImVec4("646362", 161); // 直方图的颜色
	//Colors[ImGuiCol_PlotHistogramHovered] = ImGui::HexToImVec4("40FF00", 255); // 鼠标悬停在直方图上时的颜色
	//Colors[ImGuiCol_TextSelectedBg] = ImGui::HexToImVec4("40FF00", 110); // 选中文本的背景颜色

}
//————————————————————————————————————————————————————
void Gui::左边选择菜单()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	//ImGui::PushStyleColor(1,ImVec4(28,28,28,255));
	ImGui::PushStyleVar(7, 5);//圆角角度开始
	ImGui::SetCursorPos({ 7,63 });//置组件坐标

	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##选择菜单", { 65,630 }, false, 256))//子窗口
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.984f, 0.686f, 0.980f, 0.000f));//颜色开始
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.000f, 1.000f, 1.000f, 0.129f));//颜色开始
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.000f, 1.000f, 1.000f, 0.345f));//颜色开始

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		ImGui::PushFont(font_text2);//字体开始
		if (ImGui::Button(obf(ICON_FA_ID_CARD_ALT"").c_str(), ImVec2(40, 39)))
		{
			菜单位置 = 0;
		}

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button(obf(ICON_FA_EYE"").c_str(), ImVec2(40, 39)))
		{
			菜单位置 = 1;
		}

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button(obf(ICON_FA_MOUSE"").c_str(), ImVec2(40, 39)))
		{
			菜单位置 = 2;
		}

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button(obf(ICON_FA_DICE_D6"").c_str(), ImVec2(40, 39)))
		{
			菜单位置 = 3;
		}

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button(obf(ICON_FA_COGS"").c_str(), ImVec2(40, 39)))
		{
			菜单位置 = 4;
		}
		ImGui::PopStyleColor();//颜色结束
		ImGui::PopStyleColor();//颜色结束
		ImGui::PopStyleColor();//颜色结束
		ImGui::PopFont();//字体结束

	}


	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//子窗口的结束
}
//————————————————————————————————————————————————————
void Gui::主页菜单()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 77,63 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##主页菜单", { 730,630 }, false, 256))//子窗口开始
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		//ImGui::Text(u8"主页菜单");
		ImGui::TextGradiented(u8"主页菜单", 0xFFD95A, 0xFFF7D4, 66);

		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		主页菜单_公告();


		//ImGui::NewLine();\

		//*ImGui::PushItemWidth(300);  // 将下一个控件的宽度设置为300   开始
		//*
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*ImGui::Text(u8"style.圆角角度值: %.3f", style.FrameRounding);
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*if (ImGui::SliderFloat(u8"圆角 滑块条", &style.FrameRounding, 0.0f, 12.0f, "%.3f"))
		//*	style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
		//*
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*ImGui::Text(u8"滑块值: %.4f", HuaKuaiTiao);
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*ImGui::SliderFloat(u8"滑块条", &HuaKuaiTiao, 1.0000f, 20.0000f, "%.4f");
		//*
		//*ImGui::PopItemWidth();  // 恢复元素宽度为默认值 结束
		//*
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*if (ImGui::Button(u8" 更改 ", ImVec2(0, 0)))
		//*{
		//*	printf_s("逻辑值:%u", 是否初始化);
		//*}
		//*
		//*//ImGui::Text(u8"");
		//*//ImGui::SameLine();
		//*//ImGui::ColorEdit4("##color", (float*)&style->Colors[ImGuiCol_Text], ImGuiColorEditFlags_AlphaBar | alpha_flags);//颜色选择器
		//*//const char* name = ImGui::GetStyleColorName(0);
		//*//ImGui::SameLine(0.0f, style->ItemInnerSpacing.x);
		//*//ImGui::TextUnformatted(name);
		//*
		//*static ImGuiTextFilter filter;
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*filter.Draw("Filter colors", ImGui::GetFontSize() * 16);
		//*
		//*static ImGuiColorEditFlags alpha_flags = 0;
		//*if (ImGui::RadioButton("Opaque", alpha_flags == ImGuiColorEditFlags_None)) { alpha_flags = ImGuiColorEditFlags_None; } ImGui::SameLine();
		//*if (ImGui::RadioButton("Alpha", alpha_flags == ImGuiColorEditFlags_AlphaPreview)) { alpha_flags = ImGuiColorEditFlags_AlphaPreview; } ImGui::SameLine();
		//*if (ImGui::RadioButton("Both", alpha_flags == ImGuiColorEditFlags_AlphaPreviewHalf)) { alpha_flags = ImGuiColorEditFlags_AlphaPreviewHalf; } ImGui::SameLine();
		//*
		//*ImGui::NewLine();
		//*
		//*ImGui::BeginChild("##colors", ImVec2(0, 0), true, 256);//子窗口开始
		//*ImGui::PushItemWidth(-160);
		//*
		//*ImGui::PushItemWidth(500);  // 将下一个控件的宽度设置为300   开始
		//*for (int i = 0; i < ImGuiCol_COUNT; i++)
		//*{
		//*	const char* name = ImGui::GetStyleColorName(i);
		//*	if (!filter.PassFilter(name))
		//*		continue;
		//*	ImGui::PushID(i);
		//*	ImGui::ColorEdit4("##color", (float*)&style.Colors[i], ImGuiColorEditFlags_AlphaBar | alpha_flags);
		//*
		//*	ImGui::SameLine(0.0f, style.ItemInnerSpacing.x);
		//*	ImGui::TextUnformatted(name);
		//*	ImGui::PopID();
		//*}
		//*ImGui::PopItemWidth();  // 恢复元素宽度为默认值 结束
		//*ImGui::EndChild();//子窗口的结束
		//*//——————————————————————————————————————————
		//*ImGui::Text("Main");
		//*ImGui::SliderFloat2("WindowPadding", (float*)&style.WindowPadding, 0.0f, 20.0f, "%.0f");
		//*ImGui::SliderFloat2("FramePadding", (float*)&style.FramePadding, 0.0f, 20.0f, "%.0f");
		//*ImGui::SliderFloat2("CellPadding", (float*)&style.CellPadding, 0.0f, 20.0f, "%.0f");
		//*ImGui::SliderFloat2("ItemSpacing", (float*)&style.ItemSpacing, 0.0f, 20.0f, "%.0f");
		//*ImGui::SliderFloat2("ItemInnerSpacing", (float*)&style.ItemInnerSpacing, 0.0f, 20.0f, "%.0f");
		//*ImGui::SliderFloat2("TouchExtraPadding", (float*)&style.TouchExtraPadding, 0.0f, 10.0f, "%.0f");
		//*ImGui::SliderFloat("IndentSpacing", &style.IndentSpacing, 0.0f, 30.0f, "%.0f");
		//*ImGui::SliderFloat("ScrollbarSize", &style.ScrollbarSize, 1.0f, 20.0f, "%.0f");
		//*ImGui::SliderFloat("GrabMinSize", &style.GrabMinSize, 1.0f, 20.0f, "%.0f");
		//*ImGui::Text("Borders");
		//*ImGui::SliderFloat("WindowBorderSize", &style.WindowBorderSize, 0.0f, 1.0f, "%.0f");
		//*ImGui::SliderFloat("ChildBorderSize", &style.ChildBorderSize, 0.0f, 1.0f, "%.0f");
		//*ImGui::SliderFloat("PopupBorderSize", &style.PopupBorderSize, 0.0f, 1.0f, "%.0f");
		//*ImGui::SliderFloat("FrameBorderSize", &style.FrameBorderSize, 0.0f, 1.0f, "%.0f");
		//*ImGui::SliderFloat("TabBorderSize", &style.TabBorderSize, 0.0f, 1.0f, "%.0f");
		//*ImGui::Text("Rounding");
		//*ImGui::SliderFloat("WindowRounding", &style.WindowRounding, 0.0f, 12.0f, "%.0f");
		//*ImGui::SliderFloat("ChildRounding", &style.ChildRounding, 0.0f, 12.0f, "%.0f");
		//*ImGui::SliderFloat("FrameRounding", &style.FrameRounding, 0.0f, 12.0f, "%.0f");
		//*ImGui::SliderFloat("PopupRounding", &style.PopupRounding, 0.0f, 12.0f, "%.0f");
		//*ImGui::SliderFloat("ScrollbarRounding", &style.ScrollbarRounding, 0.0f, 12.0f, "%.0f");
		//*ImGui::SliderFloat("GrabRounding", &style.GrabRounding, 0.0f, 12.0f, "%.0f");
		//*ImGui::SliderFloat("LogSliderDeadzone", &style.LogSliderDeadzone, 0.0f, 12.0f, "%.0f");
		//*ImGui::SliderFloat("TabRounding", &style.TabRounding, 0.0f, 12.0f, "%.0f");
		//*ImGui::Text("Alignment");
		//*ImGui::SliderFloat2("WindowTitleAlign", (float*)&style.WindowTitleAlign, 0.0f, 1.0f, "%.2f");
		//*int window_menu_button_position = style.WindowMenuButtonPosition + 1;
		//*if (ImGui::Combo("WindowMenuButtonPosition", (int*)&window_menu_button_position, "None\0Left\0Right\0"))
		//*	style.WindowMenuButtonPosition = window_menu_button_position - 1;
		//*ImGui::Combo("ColorButtonPosition", (int*)&style.ColorButtonPosition, "Left\0Right\0");
		//*ImGui::SliderFloat2("ButtonTextAlign", (float*)&style.ButtonTextAlign, 0.0f, 1.0f, "%.2f");
		//*ImGui::SliderFloat2("SelectableTextAlign", (float*)&style.SelectableTextAlign, 0.0f, 1.0f, "%.2f");
		//*ImGui::Text("Safe Area Padding");
		//*ImGui::SliderFloat2("DisplaySafeAreaPadding", (float*)&style.DisplaySafeAreaPadding, 0.0f, 30.0f, "%.0f");

	}


	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//子窗口的结束
}

void Gui::主页菜单_公告()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 5,5 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##主页菜单_公告", ImVec2(720, 620), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"主页公告", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		ImGui::Text(u8"");
		ImGui::SameLine();
		ImGui::Text(u8"NyL: 要保号需合理演戏.");


	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//主窗口的结束
}

void Gui::透视菜单()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	//ImGui::PushStyleColor(1,ImVec4(28,28,28,255));
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 77,63 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##ESP1", { 730,630 }, false, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		透视菜单_分组();

		
	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//主窗口的结束
}

void Gui::透视菜单_分组()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 5,5 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##ESP2", ImVec2(720, 620), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"视觉 >> 显示设置", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("##ESPset", tab_bar_flags))
		{
			if (ImGui::BeginTabItem(u8"串流"))
			{
				透视菜单_串流();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"玩家"))
			{
				透视菜单_玩家();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"物品"))
			{
				透视菜单_物品();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"载具"))
			{
				透视菜单_载具();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"雷达"))
			{
				透视菜单_雷达();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"颜色"))
			{
				透视菜单_颜色();
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//主窗口的结束
}

void Gui::透视菜单_串流()
{
	if (ImGui::BeginChild("##串流画面", ImVec2(708, 557), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"视觉 >> 串流", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		if (ImGui::BeginTable("split##10", 4))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 5));//设置组件高度 开始
			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"左右", u8"\uf304 X", F::Global.Menu.新窗口X_, IM_ARRAYSIZE(F::Global.Menu.新窗口X_));//输入框
			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"上下", u8" Y", F::Global.Menu.新窗口Y_, IM_ARRAYSIZE(F::Global.Menu.新窗口Y_));//输入框
			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"宽度", u8" 宽", F::Global.Menu.新窗口W_, IM_ARRAYSIZE(F::Global.Menu.新窗口W_));//输入框
			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"高度", u8" 高", F::Global.Menu.新窗口H_, IM_ARRAYSIZE(F::Global.Menu.新窗口H_));//输入框
			ImGui::PopStyleVar();//设置组件高度 结束

			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"串流模式", &F::Global.GameData.串流模式);

			ImGui::TableNextColumn();
			if (ImGui::Button(u8"\uf0c7 应用", ImVec2(70, 30))) {//ICON_FA_SAVE
				float XX = std::stof(F::Global.Menu.新窗口X_);
				float YY = std::stof(F::Global.Menu.新窗口Y_);
				float WW = std::stof(F::Global.Menu.新窗口W_);
				float HH = std::stof(F::Global.Menu.新窗口H_);

				F::Global.GameData.新窗口X = XX;
				F::Global.GameData.新窗口Y = YY;
				F::Global.GameData.新窗口W = WW;
				F::Global.GameData.新窗口H = HH;

				//设置矩阵W H
				F::Global.GameData.Width = (int)WW / 2;
				F::Global.GameData.Height = (int)HH / 2;

				glfwSetWindowPos(window1, F::Global.GameData.新窗口X, F::Global.GameData.新窗口Y);//移动窗口
				glfwSetWindowSize(window1, F::Global.GameData.新窗口W, F::Global.GameData.新窗口H);//改变窗口大小
			}
			ImGui::EndTable();//结束
		}


		ImGui::EndChild();//主窗口的结束
	}
}

void Gui::透视菜单_玩家()
{
	if (ImGui::BeginChild("##玩家数组", ImVec2(708, 557), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"视觉 >> 玩家", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		if (ImGui::BeginTable("split", 4))
		{
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"方框", &F::Global.Menu.玩家方框);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"骨骼", &F::Global.Menu.玩家骨骼);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"射线", &F::Global.Menu.玩家射线);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"血量", &F::Global.Menu.玩家血条);
			//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"雷达", &ESP_Lite1);
			//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"体力", &ESP_Lite1);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"人物信息", &F::Global.Menu.玩家信息);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"队友显示", &F::Global.Menu.队友显示);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"地图雷达", &F::Global.Menu.地图雷达);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"调试模式", &F::Global.Menu.调试数据模式);
			//
			ImGui::TableNextColumn();
			ImGui::SetNextItemWidth(110);//设置组件宽度 此函数为设置下面一个组件的宽度
			ImGui::SliderFloat(u8"骨骼粗细", &F::Global.Menu.骨骼粗细, 1.0f, 10.0f, "%.1f");
			ImGui::EndTable();//结束
		}


		ImGui::EndChild();//主窗口的结束
	}
}

void Gui::透视菜单_颜色()
{
	if (ImGui::BeginChild("##颜色窗口-物品", ImVec2(708, 88), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"颜色 >> 物品", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线
		if (ImGui::BeginTable("物品项颜色列表", 5))
		{
			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##1", (float*)&F::Global.Color.载具, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"载具");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##2", (float*)&F::Global.Color.枪械, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"枪械");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##3", (float*)&F::Global.Color.配件, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"配件");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##4", (float*)&F::Global.Color.防具, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"防具");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##5", (float*)&F::Global.Color.药品, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"药品");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##6", (float*)&F::Global.Color.投掷, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"投掷");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##7", (float*)&F::Global.Color.空投盒子, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"空投盒子");

			ImGui::EndTable();//结束
		}
		ImGui::EndChild();//主窗口的结束
	}
	
}

void Gui::透视菜单_雷达()
{
	if (ImGui::BeginChild("##透视菜单_雷达", ImVec2(720, 110), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"视觉 >> 雷达", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		ImGui::Text(u8"");
		ImGui::SameLine();
		if (ImGui::BeginTable("split", 3))
		{
			float ProportionMin = 50.f, ProportionMax = 1500.f;
			float RadarRangeMin = 100.f, RadarRangeMax = 300.f;
			float RadarPointSizeProportionMin = 0.8f, RadarPointSizeProportionMax = 2.f;
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"雷达", &F::Global.Menu.雷达);

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"雷达大小", &F::Global.Menu.RadarRange, RadarRangeMin, RadarRangeMax, "%.1f");

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"点位大小", &F::Global.Menu.RadarPointSizeProportion, RadarPointSizeProportionMin, RadarPointSizeProportionMax, "%.1f");

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"缩放大小", &F::Global.Menu.Proportion, ProportionMin, ProportionMax, "%.1f");

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"窗口坐标X", &F::Global.Menu.RadarX, 0, F::Global.GameData.Width * 2, "%.1f");

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"窗口坐标Y", &F::Global.Menu.RadarY, 0, F::Global.GameData.Height * 2, "%.1f");

			static float floattoint = (float)F::Global.Menu.RadarType;
			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"雷达样式", &floattoint, 0, 2, "%.0f");
			F::Global.Menu.RadarType = floattoint;



		}
		ImGui::EndTable();//结束

	}
	ImGui::EndChild();//主窗口的结束
}

void Gui::透视菜单_物品()//(开发中..)//static
{
	if (ImGui::BeginChild("##物品透视选择", ImVec2(708, 557), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"视觉 >> 物品   ", 0xFFD95A, 0xFFF7D4, 66); ImGui::SameLine(); 
		ImGui::HotkeyYai(u8"分组切换键 ", F::Global.Menu.分组切换键, { 130,23 }); ImGui::SameLine();
		ImGui::HotkeyYai(u8"物透开关 ", F::Global.Menu.物透开关热键, { 130,23 }); ImGui::SameLine();
		if (ImGui::Button(obf(u8"保存").c_str(), ImVec2(50, 24)))
		{
			for (size_t i = 0; i < F::Global.Menu.ItemsNames.size(); ++i) {
				std::string itemName = F::Global.Menu.ItemsNames[i];
				int groupIndex = F::Global.Menu.itemgrounp[i].物品组;
				std::string groupName = F::Global.Menu.items[groupIndex];

				std::cout << "物品名: " << itemName << ", 所在组: " << groupName << std::endl;

			}
		}

		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线
		//————————————————————————————————————————————————————————

		static ImGuiTableFlags flags =
			ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
			| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
			| ImGuiTableFlags_ScrollY;

		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::HexToImVec4("191717", 255));//设置颜色
		ImGui::SetNextItemWidth(708); // 设置整个列表框的宽度
		ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 506.0f), ImVec2(-1, 506.0f));

		if (ImGui::BeginTable("ExampleTable", 2, flags)) // 2表示列数
		{
			ImGui::TableSetupColumn(u8"名字");
			ImGui::TableSetupColumn(u8"物品组");
			ImGui::TableHeadersRow();

			for (int row = 0; row < F::Global.Menu.ItemsNames.size(); ++row)
			{
				ImGui::TableNextRow();
				for (int column = 0; column < 2; ++column)
				{
					ImGui::TableSetColumnIndex(column);
					if (column == 0)
					{
						// 第一列显示名字
						ImGui::Text("%s", F::Global.Menu.ItemsNames[row].c_str());
					}
					else
					{
						// 第二列使用下拉框组件显示物品组
						char combo_label[32];
						sprintf(combo_label, "##物品组%d", row); // 为每行创建唯一的标签
						if (ImGui::BeginCombo(combo_label, F::Global.Menu.items[F::Global.Menu.itemgrounp[row].物品组]))
						{
							for (int i = 0; i < IM_ARRAYSIZE(F::Global.Menu.items); ++i)
							{
								if (ImGui::Selectable(F::Global.Menu.items[i], F::Global.Menu.itemgrounp[row].物品组 == i))
									F::Global.Menu.itemgrounp[row].物品组 = i;
							}
							ImGui::EndCombo();
						}
					}
				}
			}

			ImGui::EndTable();
		}










		ImGui::PopStyleColor();//恢复颜色
		ImGui::EndChild();//主窗口的结束
	}
}

void Gui::透视菜单_载具()
{
	if (ImGui::BeginChild("##颜色窗口-物品", ImVec2(708, 557), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"视觉 >> 载具", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线
		if (ImGui::BeginTable("split", 4))
		{
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"吉普", &F::Global.MenuE.car1);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"四驱车", &F::Global.MenuE.car2);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"轿车", &F::Global.MenuE.car3);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"蹦蹦", &F::Global.MenuE.car4);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"摩艇", &F::Global.MenuE.car5);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"无人机", &F::Global.MenuE.car6);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"公交", &F::Global.MenuE.car7);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"五菱", &F::Global.MenuE.car8);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"库佩", &F::Global.MenuE.car9);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"游艇", &F::Global.MenuE.car10);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"NIVA", &F::Global.MenuE.car11);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"越野摩托", &F::Global.MenuE.car12);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"KILLTRUCK", &F::Global.MenuE.car13);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"TUK", &F::Global.MenuE.car14);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"跑车", &F::Global.MenuE.car15);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"摩托", &F::Global.MenuE.car16);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"Helicopter", &F::Global.MenuE.car17);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"AIRCRAFT", &F::Global.MenuE.car18);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"装甲车", &F::Global.MenuE.car19);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"自行车", &F::Global.MenuE.car20);/*
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"地狱犬", &F::Global.MenuE.car21);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"死亡甲虫", &F::Global.MenuE.car22);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"熔岩怪", &F::Global.MenuE.car23);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"狼", &F::Global.MenuE.car24);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"半人马", &F::Global.MenuE.car25);*/
			
			//ImGui::SameLine(); Helpmarker(u8"ESP", style.Colors[ImGuiCol_Text]);
			ImGui::EndTable();
		}
		ImGui::EndChild();//主窗口的结束
	}
}

void Gui::自瞄菜单()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	//ImGui::PushStyleColor(1,ImVec4(28,28,28,255));
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 77,63 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##AIM", { 730,630 }, false, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		//ImGui::TextGradiented(u8"自瞄菜单", 0xFFD95A, 0xFFF7D4, 66);

		//ImGui::NewLine();//新的一行
		//ImGui::Separator();//分割线
		自瞄菜单_瞄准();
		自瞄菜单_武器();

	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//主窗口的结束
}

void Gui::自瞄菜单_瞄准()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 5,5 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##自瞄菜单_瞄准", ImVec2(720, 185), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //同行
		ImGui::TextGradiented(u8"瞄准 >> 基础设置", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		if (ImGui::BeginTable("AIM_Base", 2))//TAB开始
		{
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"FOV显示*", &F::Global.Menu.FOV显示);
			ImGui::SameLine();
			Helpmarker(u8"屏幕中心显示自瞄的范围", style.Colors[ImGuiCol_Text]);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"动态FOV*", &ESP_Lite1);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"帧数同步*", &ESP_Lite1);
			ImGui::TableNextColumn();
			ImGui::PushItemWidth(50);  // 置控件的宽度设置 开始  此函数为设置下方所有组件
			ImGui::InputText(u8"##游戏分辨率X", WBtxt0, IM_ARRAYSIZE(WBtxt0));
			ImGui::SameLine();
			ImGui::InputText(u8"游戏分辨率*", WBtxt1, IM_ARRAYSIZE(WBtxt1));
			ImGui::PopItemWidth();  // 恢复控件的宽度设置 结束
			ImGui::SameLine();
			if (ImGui::Button(obf(u8"获取").c_str(), ImVec2(45, 24)))
			{
				//printf("暂未开发\n");

			}
		}

		ImGui::EndTable();//TAB结束
		//————————————————————————————————————————
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线
		//————————————————————————————————————————
		ImGui::NewLine(); //新的一行
		ImGui::Text(u8"鼠标盒子状态:");
		ImGui::SameLine(); //下一行不换行

		if (F::Global.Menu.自瞄器连接状态 == true)
		{
			sprintf_s(Box_State_buffer, u8"已连接");
			ImGui::TextGradiented(Box_State_buffer, 0x20FF00, 0xFAF7F0, 66);
		}
		else {
			if (F::Global.Menu.自瞄器连接状态 == false)
			{
				sprintf_s(Box_State_buffer, u8"未连接");
				ImGui::TextGradiented(Box_State_buffer, 0xFF0000FF, 0xFAF7F0, 66);
			}
		}

		if (ImGui::BeginTable("AIM_Base_BOX", 3))//TAB开始
		{
			static bool buttonDisabled = false;

			if (buttonDisabled) {
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);//设置静态禁用状态
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f); // 可选：降低禁用组件的透明度
			}

			ImGui::TableNextColumn(); ImGui::RadioButton(u8"KmBox", &F::Global.Menu.自瞄类型, 0);
			ImGui::TableNextColumn(); ImGui::RadioButton(u8"NYL-API", &F::Global.Menu.自瞄类型, 1);
			ImGui::TableNextColumn(); ImGui::RadioButton(u8"易键鼠-Not", &F::Global.Menu.自瞄类型, 2);
			ImGui::TableNextColumn();
			F::Global.Menu.COM选择项 = F::Global.Menu.可用端口号[F::Global.Menu.端口索引值];
			if (ImGui::BeginCombo(u8"端口号", F::Global.Menu.COM选择项, 0))
			{
				for (int n = 0; n < IM_ARRAYSIZE(F::Global.Menu.可用端口号); n++) {
					if (F::Global.Menu.可用端口号[n] == nullptr || strlen(F::Global.Menu.可用端口号[n]) == 0) {
						continue;
					}
					const bool is_selected = (F::Global.Menu.端口索引值 == n);
					if (ImGui::Selectable(F::Global.Menu.可用端口号[n], is_selected)) {
						F::Global.Menu.端口索引值 = n;
					}
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}


			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"波特率", "", F::Global.Menu.控制器波特率, IM_ARRAYSIZE(F::Global.Menu.控制器波特率));//输入框

			ImGui::TableNextColumn();

			if (buttonDisabled) {
				ImGui::PopItemFlag();//撤销禁用状态
				ImGui::PopStyleVar();//撤销透明状态
			}
			if (F::Global.Menu.自瞄类型 == 0)
			{
				if (F::Global.Menu.自瞄器连接状态 == true)
				{
					if (ImGui::Button(obf(u8"断开连接").c_str(), ImVec2(70, 24)))
					{
						F::Global.Menu.自瞄器连接状态 = false;
						buttonDisabled = false;
						G::kmbox.close();
						printf("控制器 -> 断开控制器成功.\n");
					}
				}
				else {
					if (F::Global.Menu.自瞄器连接状态 == false)
					{
						if (ImGui::Button(obf(u8"连接盒子").c_str(), ImVec2(70, 24)))
						{
							//波特率
							int 控制器波特率 = std::stof(F::Global.Menu.控制器波特率);

							//连接
							if (G::kmbox.open(F::Global.Menu.COM选择项, 控制器波特率))
							{
								F::Global.Menu.自瞄器连接状态 = true;
								buttonDisabled = true;
								printf("NYL - >串口 %s\n", F::Global.Menu.COM选择项);
								printf("NYL - >波特率 %d\n", 控制器波特率);
								printf("控制器 -> 连接控制器成功!\n");
							}
							else
							{
								F::Global.Menu.自瞄器连接状态 = false;
								printf("控制器 -> 连接控制器失败.\n");
							}



						}
					}
				}
				ImGui::SameLine(); //同行
				if (ImGui::Button(obf(u8"刷新端口").c_str(), ImVec2(70, 24)))
				{
					G::kmbox.取可用串口();
				}
			}
			if (F::Global.Menu.自瞄类型 == 1) {
				if (F::Global.Menu.自瞄器连接状态 == true)
				{
					if (ImGui::Button(obf(u8"断开连接").c_str(), ImVec2(70, 24)))
					{
						F::Global.Menu.自瞄器连接状态 = false;
						buttonDisabled = false;
						printf("控制器 -> 断开API成功.\n");
					}
				}
				else {
					if (F::Global.Menu.自瞄器连接状态 == false)
					{
						if (ImGui::Button(obf(u8"连接盒子").c_str(), ImVec2(70, 24)))
						{
							F::Global.Menu.自瞄器连接状态 = true;
							buttonDisabled = true;
							printf("控制器 -> 连接API成功!\n");
						}
					}
				}
			}

		}
		ImGui::EndTable();//TAB结束


		/*ImGui::Text(u8"");
		//ImGui::SameLine();
		//ImGui::Hotkey(u8"自瞄热键 ", CUSTOM_KEY, 70, { 100,23 });*/

		//ImGui::PushFont(font_text1);
		//ImGui::TextColored(style.Colors[ImGuiCol_Text], u8"  >> ImGui Tool Yai <<");
		//ImGui::PopFont();

		//ImGui::PushFont(font_text2);
		////ImGui::TextColored(style.Colors[ImGuiCol_Text], obf(ICON_FA_SAVE" ImGui Tools").c_str());
		//if (ImGui::Button(obf(ICON_FA_KISS"").c_str(), ImVec2(40, 40)))
		//{
		//	printf_s("font_text1:%f\n", font_text1->FontSize);
		//	printf_s("font_text2:%f\n\n", font_text2->FontSize);
		//	//tab = 1;
		//}
		//ImGui::PopFont();



	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//主窗口的结束
}

void Gui::自瞄菜单_武器()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 5,195 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##自瞄菜单_武器", ImVec2(720, 250), true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"瞄准 >> 武器设置", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("##武器标签栏", tab_bar_flags))
		{
			if (ImGui::BeginTabItem(u8"瞄准参数"))
			{
				自瞄菜单_武器_参数();
				ImGui::EndTabItem();
			}

			/*if (ImGui::BeginTabItem(u8"步枪"))
			{
				自瞄菜单_武器_步枪();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"连狙"))
			{
				ImGui::Text(u8"连狙区");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"栓狙"))
			{
				ImGui::Text(u8"栓狙区");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"冲锋枪"))
			{
				ImGui::Text(u8"冲锋枪区");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"霰弹枪"))
			{
				ImGui::Text(u8"霰弹枪区");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"其他"))
			{
				ImGui::Text(u8"其他枪区");
				ImGui::EndTabItem();
			}*/
			ImGui::EndTabBar();
		}

		//ImGui::Text(u8"");
		/*ImGui::SameLine();
		ImGui::Hotkey(u8"自瞄热键 ", CUSTOM_KEY, 70, { 100,23 });*/

		//ImGui::PushFont(font_text1);
		//ImGui::TextColored(style.Colors[ImGuiCol_Text], u8"  >> ImGui Tool Yai <<");
		//ImGui::PopFont();

		//ImGui::PushFont(font_text2);
		////ImGui::TextColored(style.Colors[ImGuiCol_Text], obf(ICON_FA_SAVE" ImGui Tools").c_str());
		//if (ImGui::Button(obf(ICON_FA_KISS"").c_str(), ImVec2(40, 40)))
		//{
		//	printf_s("font_text1:%f\n", font_text1->FontSize);
		//	printf_s("font_text2:%f\n\n", font_text2->FontSize);
		//	//tab = 1;
		//}
		//ImGui::PopFont();



	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//主窗口的结束
}

void Gui::自瞄菜单_武器_参数()
{
	if (ImGui::BeginTable("AIM_Base_W1", 3))//TAB开始
	{
		//ImGui::TableNextColumn(); ImGui::Hotkey(u8"父热键 ", CUSTOM_KEY1, 60, { 100,23 });
		ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"父热键 ", F::Global.Menu.自瞄按键, { 130,23 });
		ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"子热键 ", F::Global.Menu.自瞄子按键, { 130,23 });
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"热键合并", &F::Global.Menu.热键合并);
		/*ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"后坐力抑制", &ESP_Lite1);
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"呼吸抑制", &ESP_Lite1);*/

		ImGui::TableNextColumn();
		if (ImGui::Combo(u8"自瞄位置", (int*)&F::Global.Menu.自瞄部位列表索引, u8"头\0脖子\0胸甲\0屁股\0"))
		{
			/*if (F::Global.Menu.自瞄部位列表索引 == 0)
			{
				F::Global.Menu.自瞄位置 = 46;
			}
			if (F::Global.Menu.自瞄部位列表索引 == 1)
			{
				F::Global.Menu.自瞄位置 = 45;
			}
			if (F::Global.Menu.自瞄部位列表索引 == 2)
			{
				F::Global.Menu.自瞄位置 = 1;
			}
			if (F::Global.Menu.自瞄部位列表索引 == 3)
			{
				F::Global.Menu.自瞄位置 = 6;
			}*/
			//printf("位置: %d\n", F::Global.Menu.自瞄位置);


		}

		//ImGui::PushItemWidth(88);  // 置控件的宽度设置   开始
		//ImGui::Combo(u8"跳过击倒", (int*)&跳过击倒, u8"从不\0始终\0优先存活\0");
		//ImGui::PopItemWidth();  // 恢复控件的宽度设置 结束

		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"可视检查", &ESP_Lite1);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"弹道预测", &ESP_Lite1);

		//ImGui::TableNextColumn(); ImGui::SliderFloat(u8"瞄准距离", &HuaKuaiTiao, 1.0f, 1000.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"FOV", &F::Global.Menu.自瞄FOV, 1.0f, 360.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"X轴速度", &F::Global.Menu.自瞄X速, 1.0f, 20.0f, "%.3f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"Y轴速度", &F::Global.Menu.自瞄Y速, 1.0f, 20.0f, "%.3f");
		//ImGui::TableNextColumn(); ImGui::SliderFloat(u8"自瞄速度", &F::Global.Menu.自瞄速度, 1.0f, 100.0f, "%.2f");
		//ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"扳机按键 ", F::Global.Menu.扳机按键, { 130,23 });

		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"帧数", &F::Global.Menu.自瞄帧数, 1.0f, 240.0f, "%.0f");
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"可视判断", &F::Global.Menu.可视判断);
		//ImGui::TableNextColumn(); ImGui::SliderFloat(u8"扳机延迟", &F::Global.Menu.扳机延迟, 10.0f, 3000.0f, "%.0f");

		//ImGui::TableNextColumn();
		//
		//ImGui::PushItemWidth(88);  // 置控件的宽度设置   开始
		//ImGui::Combo(u8"算法", (int*)&算法, u8"旧模式\0新模式\0");
		//ImGui::PopItemWidth();  // 恢复控件的宽度设置 结束

		//ImGui::TableNextColumn(); ImGui::SliderScalar(u8"抑制Pitch", ImGuiDataType_Float, &yizhi_default, &yizhi_min, &yizhi_max, "%.3f");
		//ImGui::TableNextColumn();
		//ImGui::TableNextColumn(); ImGui::SliderScalar(u8"抑制Yaw", ImGuiDataType_Float, &yizhi_default, &yizhi_min, &yizhi_max, "%.3f");






		//ImGui::SameLine();
		//Helpmarker(u8"屏幕中心显示自瞄的范围", style.Colors[ImGuiCol_Text]);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"动态FOV", &ESP_Lite1);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"帧数同步", &ESP_Lite1);
		//ImGui::TableNextColumn();
		//ImGui::PushItemWidth(50);  // 置控件的宽度设置   开始
		//ImGui::InputText(u8"##游戏分辨率X", WBtxt0, IM_ARRAYSIZE(WBtxt0));
		//ImGui::SameLine();
		//ImGui::InputText(u8"游戏分辨率", WBtxt1, IM_ARRAYSIZE(WBtxt1));
		//ImGui::PopItemWidth();  // 恢复控件的宽度设置 结束
		//ImGui::SameLine();
		//if (ImGui::Button(obf(u8"获取").c_str(), ImVec2(45, 24)))
		//{

		//}
	}
	ImGui::EndTable();//TAB结束


}

void Gui::自瞄菜单_武器_步枪()
{
	if (ImGui::BeginTable("AIM_Base_W1", 3))//TAB开始
	{
		//ImGui::TableNextColumn(); ImGui::Hotkey(u8"父热键 ", CUSTOM_KEY1, 60, { 100,23 });
		ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"父热键 ", CUSTOM_KEY1, { 130,23 });
		ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"子热键 ", CUSTOM_KEY2, { 130,23 });
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"热键合并", &ESP_Lite1);
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"后坐力抑制", &ESP_Lite1);
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"呼吸抑制", &ESP_Lite1);

		ImGui::TableNextColumn();

		ImGui::PushItemWidth(88);  // 置控件的宽度设置   开始
		ImGui::Combo(u8"跳过击倒", (int*)&跳过击倒, u8"从不\0始终\0优先存活\0");
		ImGui::PopItemWidth();  // 恢复控件的宽度设置 结束

		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"可视检查", &ESP_Lite1);
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"弹道预测", &ESP_Lite1);

		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"瞄准距离", &HuaKuaiTiao, 1.0f, 1000.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"FOV", &HuaKuaiTiao, 1.0f, 1000.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"X轴速度", &HuaKuaiTiao, 1.0f, 1000.0f, "%.3f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"Y轴速度", &HuaKuaiTiao, 1.0f, 1000.0f, "%.3f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"非线性比例", &HuaKuaiTiao, 1.0f, 80.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"帧数", &HuaKuaiTiao, 1.0f, 240.0f, "%.0f");

		ImGui::TableNextColumn();

		ImGui::PushItemWidth(88);  // 置控件的宽度设置   开始
		ImGui::Combo(u8"算法", (int*)&算法, u8"旧模式\0新模式\0");
		ImGui::PopItemWidth();  // 恢复控件的宽度设置 结束

		ImGui::TableNextColumn(); ImGui::SliderScalar(u8"抑制Pitch", ImGuiDataType_Float, &yizhi_default, &yizhi_min, &yizhi_max, "%.3f");
		ImGui::TableNextColumn();
		ImGui::TableNextColumn(); ImGui::SliderScalar(u8"抑制Yaw", ImGuiDataType_Float, &yizhi_default, &yizhi_min, &yizhi_max, "%.3f");






		//ImGui::SameLine();
		//Helpmarker(u8"屏幕中心显示自瞄的范围", style.Colors[ImGuiCol_Text]);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"动态FOV", &ESP_Lite1);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"帧数同步", &ESP_Lite1);
		//ImGui::TableNextColumn();
		//ImGui::PushItemWidth(50);  // 置控件的宽度设置   开始
		//ImGui::InputText(u8"##游戏分辨率X", WBtxt0, IM_ARRAYSIZE(WBtxt0));
		//ImGui::SameLine();
		//ImGui::InputText(u8"游戏分辨率", WBtxt1, IM_ARRAYSIZE(WBtxt1));
		//ImGui::PopItemWidth();  // 恢复控件的宽度设置 结束
		//ImGui::SameLine();
		//if (ImGui::Button(obf(u8"获取").c_str(), ImVec2(45, 24)))
		//{

		//}
	}
	ImGui::EndTable();//TAB结束


}

void Gui::杂项菜单()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 77,63 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##杂项菜单", { 730,630 }, false, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"##开发中", 0xFFD95A, 0xFFF7D4, 66);

		if (ImGui::BeginTable("##功能TAB", 2))//TAB开始
		{
			//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"无后座力", &F::Global.Menu.无后座);
			//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"快速开枪", &F::Global.Menu.快速开枪);


		}ImGui::EndTable();//TAB结束
		

		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线


	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//主窗口的结束
}

void Gui::设置菜单()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 77,63 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##设置菜单", { 730,630 }, false, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		//ImGui::TextGradiented(u8"设置菜单", 0xFFD95A, 0xFFF7D4, 66);

		//ImGui::NewLine();//新的一行
		//ImGui::Separator();//分割线

		//————————————————————————————————————————————————————————
		设置菜单_配置文件();

		设置菜单_管理();



	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//子窗口的结束
}

void Gui::设置菜单_配置文件()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 5,5 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##设置菜单_配置文件", { 720,90 }, true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"设置菜单 >> 配置", 0xFFD95A, 0xFFF7D4, 66);

		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		//————————————————————————————————————————————————————————
		ImGui::SetCursorPos(ImVec2(5, 45));//置组件坐标
		static char 配置文件名[128] = "Config";
		ImGui::SetNextItemWidth(180);//设置组件宽度 此函数为设置下面一个组件的宽度
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5));//设置组件高度 开始
		ImGui::InputTextWithHint("##保存", u8"\uf0c7 配置文件名", 配置文件名, IM_ARRAYSIZE(配置文件名));//输入框
		//ImGui::InputTextWithHint("##保存", u8"\uf0c7 配置文件名", (char*)cfgName.c_str(), cfgName.size(), ImGuiInputTextFlags_CallbackResize, InputTextCallback, (void*)&cfgName);
		//————————————————————————————————————————————————————————
		ImGui::SameLine();
		ImGui::PopStyleVar();//设置组件高度 结束

		ImGui::Checkbox(u8"调试类名", &F::Global.Menu.Debug);

		if (ImGui::Button(u8"\uf0c7 保存", ImVec2(70, 30))) {//ICON_FA_SAVE
			//save(FileH::getProjCfgPath() + "\\" + cfgName + obf(".ini"));
			printf_s("操作日志: 保存了名为 %s 的配置文件\n", 配置文件名);

			if (!U::Config.DirectoryExists(E("Config")))
			{
				U::Config.CreatFolder(配置文件名);
				U::Config.CreatConfigeFile(配置文件名);
			}

			JsonSystem::HandleConfig(配置文件名, ConfigHandle::Save);

			//memset(配置文件名, 0, sizeof(配置文件名));

			ImGuiToast ff(ImGuiToastType_Success, 5000);//窗口图标和持续时间
			ff.set_title(u8" ");//窗口标题
			ff.set_content(u8" 配置文件保存完成 ");//窗口内容
			ImGui::InsertNotification(ff);//弹出窗口
			//配置文件名 == "Default";

		}
		ImGui::SameLine(); //下一行不换行
		if (ImGui::Button(u8"\uf233 加载", ImVec2(70, 30))) {//ICON_FA_SERVER
			//save(FileH::getProjCfgPath() + "\\" + cfgName + obf(".ini"));
			printf_s("操作日志: 加载了名为 %s 的配置文件\n", 配置文件名);


			if (!U::Config.DirectoryExists(E("Config")))
			{
				U::Config.CreatFolder(配置文件名);
				U::Config.CreatConfigeFile(配置文件名);
			}
			JsonSystem::HandleConfig(配置文件名, ConfigHandle::Load);

			//配置文件名 == "Default";
			//memset(配置文件名, 0, sizeof(配置文件名));
		}


	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//子窗口的结束
}

void Gui::设置菜单_管理()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//圆角角度
	ImGui::SetCursorPos({ 5,100 });//置组件坐标
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##设置菜单_管理", { 720,525 }, true, 256))//可设置大小
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//置组件坐标
		//ImGui::NewLine(); //新的一行
		//ImGui::SameLine(); //下一行不换行
		ImGui::TextGradiented(u8"DeBug >> NYL", 0xFF55BB, 0xFFF7D4, 255);
		ImGui::SameLine();

		static char UiFps[256];
		sprintf_s(UiFps, u8"%.0f Fps", ImGui::GetIO().Framerate);
		ImGui::TextGradiented(UiFps, 0xFF55BB, 0xFFF7D4, 66);

		ImGui::NewLine();//新的一行
		ImGui::Separator();//分割线

		//ImGui::CheckFullbox(u8"调试打印数据", &F::Global.Menu.调试数据模式);

		//————————————————————————————————————————————————————————
		//if (ImGui::BeginTable("GM_", 2))//TAB开始
		//{
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"调试GName", &ESP_Lite1);
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"调试骨骼点", &ESP_Lite1);
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"调试类型 Name或ID", &ESP_Lite1);
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"子GnameID", &ESP_Lite1);
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"输出内容", &ESP_Lite1);
		//	ImGui::TableNextColumn();
		//	ImGui::TableNextColumn(); ImGui::SliderFloat(u8"GName范围", &HuaKuaiTiao, 1.0f, 1000.0f, "%.2f");
		//	ImGui::TableNextColumn(); ImGui::SliderFloat(u8"骨骼点范围", &HuaKuaiTiao, 1.0f, 1000.0f, "%.2f");
		//
		//}
		//ImGui::EndTable();//TAB结束
		//
		//ImGui::Separator();//分割线
		////————————————————————————————————————————————————————————
		//ImGui::TableNextColumn(); ImGui::Hotkey(u8"1热键 ", CUSTOM_KEY, 60, { 130,23 });
		//ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"2热键    ", CUSTOM_KEY1, { 140,23 });
		//
		//if (ImGui::Button(obf(u8"测试").c_str(), ImVec2(50, 24)))
		//{
		//	ImGuiToast ff(ImGuiToastType_Success, 5000);//窗口图标和持续时间
		//	ff.set_title(u8" ");//窗口标题
		//	ff.set_content(u8" 测试成功内容完成 ");//窗口内容
		//	ImGui::InsertNotification(ff);//弹出窗口
		//}

		ImGui::HotkeyYai(u8"刷新程序", F::Global.Menu.刷新数据按键, { 130,23 });
		ImGui::SameLine();
		Helpmarker(u8"当游戏内效果缺失或缺少的时候按一下!", style.Colors[ImGuiCol_Text]);


		///*text2是0
		//text3是1
		//text1是2*/
		////ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);//切换到第一个字体
		////ImGui::TextGradiented(u8"font_text1 XXXXXX 测试 0", 0xFFD95A, 0xFFF7D4, 66);
		////ImGui::PopFont();//字体结束
		//ImGui::PushFont(font_text1);//字体加载
		//ImGui::TextGradiented(u8"Font NYL 快乐享受游戏 ##1", 0xFFD95A, 0xFFF7D4, 66);
		//ImGui::PopFont();//字体结束

		//ImGui::PushFont(font_text2);//字体加载
		////ImGui::SetWindowFontScale(2.f);
		////ImGui::DragFloat("Font scale", &font_text2->Scale, 0.005f, 0.3f, 2.0f, "%.1f");
		////font_text2->Scale = 3.f;
		//ImGui::TextGradiented(u8"Font NYL 快乐享受游戏 ##2", 0xFFD95A, 0xFFF7D4, 66);
		//ImGui::PopFont();//字体结束

		//ImGui::PushFont(font_text3);//字体加载
		//ImGui::TextGradiented(u8"Font NYL 快乐享受游戏 ##3", 0xFFD95A, 0xFFF7D4, 66);
		//ImGui::PopFont();//字体结束


		//if (GetAsyncKeyState(CUSTOM_KEY1) & 1) {//检测按键是否按下
		//	ImGuiToast ff(ImGuiToastType_Success, 5000);//设置图标和持续时间
		//	ff.set_title(u8" ");
		//	ff.set_content(u8" 测试成功内容完成 ");
		//	ImGui::InsertNotification(ff);//弹出窗口
		//}

		static char kmboxCOMMenter[256] = "km.move(0,100)";

		ImGui::InputTextWithHint("##发送指令", u8"\uf304 COM", kmboxCOMMenter, IM_ARRAYSIZE(kmboxCOMMenter));//输入框
		ImGui::SameLine(); //下一行不换行
		if (ImGui::Button(obf(u8"发送").c_str(), ImVec2(50, 24)))
		{
			//【km.move(0,100)】
			//km.left(1)左键按下
			//km.left(0)左键弹起
			string kmboxCOMM(kmboxCOMMenter);
			kmboxCOMM += "\r\n";
			G::kmbox.send(kmboxCOMM.c_str());

		}
		ImGui::SameLine(); //下一行不换行
		if (ImGui::Button(obf(u8"移动").c_str(), ImVec2(50, 24)))
		{
			G::kmbox.move(0, 100);
		}
		ImGui::SameLine(); //下一行不换行
		if (ImGui::Button(obf(u8"左键").c_str(), ImVec2(50, 24)))
		{
			G::kmbox.send("km.left(1)\r\n");
			G::kmbox.send("km.left(0)\r\n");
		}

		if (ImGui::Button(obf(u8"刷新").c_str(), ImVec2(50, 24)))
		{
			G::Mem.ConfigSet();
		}

		/*ImGui::CheckFullbox(u8"扳机开关", &ESP_Lite1);

		if (ESP_Lite1)
		{
			if (F::Global.GameData.扳机开关)
			{
				G::kmbox.send("km.left(1)\r\n");
				G::kmbox.send("km.left(0)\r\n");
			}
		}*/



	}
	ImGui::PopStyleVar();//圆角结束
	ImGui::EndChild();//子窗口的结束
}


