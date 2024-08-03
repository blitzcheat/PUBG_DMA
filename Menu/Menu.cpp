#include"Menu.h"
#include "../Includes.h"
#include "../ImGui/imgui_notify.h"
#include "../Features/Global.h"
#include "../kmbox/KMSeria.h"
#include "../Config/JsonSystem.h"
#include "../Game.h"

int �˵�λ�� = 0;

static bool open = true;

bool ESP_Lite1;

float HuaKuaiTiao = 1.0;
bool �Ƿ��ʼ�� = false;
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
int �������� = 0;
int �㷨 = 0;

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
//��������������������������������������������������������������������������������������������������������
void Helpmarker(const char* Text, ImVec4 Color)
{
	ImGui::TextColored(Color, u8"(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::SetTooltip(Text);
	}
}
//��������������������������������������������������������������������������������������������������������
void Gui::�Զ���˵�()
{
	ImGuiStyle& style = ImGui::GetStyle();
	//printf_s("%u", �Ƿ��ʼ��);

	if (�Ƿ��ʼ�� == false)
	{
		�����ʼ��();
		�Ƿ��ʼ�� = true;
		G::kmbox.ȡ���ô���();
		printf_s("HACK:%u\n", �Ƿ��ʼ��);
	}

	ImGui::SetNextWindowBgAlpha(0);//͸����
	//ImGui::StyleColorsClassic();//���� -> ���� UI ��ʽΪ��������(��������)
	ImGui::SetNextWindowSize({ 810,695 }, 0 << 3);//�������ڴ�С
	ImGui::Begin("LiuTeam", &open, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoDecoration);//������
	//ImGui::Begin("##LiuTeam", &open, ImGuiWindowFlags_NoScrollbar & ImGuiWindowFlags_NoScrollWithMouse & ImGuiWindowFlags_NoBackground & ImGuiWindowFlags_NoDecoration);
	{
		ImGui::SetNextWindowBgAlpha(255);
		ImGui::PushStyleVar(7, 5);//Բ�ǽǶ� ��ʼ
		ImGui::SetCursorPos({ 7,4 });//���������
		//����������������������������������������������������������������������������������������
		ImGui::SetCursorPos(ImVec2(5, 5)); //���������
		if (ImGui::BeginChild("##�����˵�", { 800,53 }, false, 256))// �Ӵ���
		{
			//ImGui::TextGradiented(u8" LiuTeam", 0xF99B7D, 0xA0D8B3, 66);
			//ImGui::SameLine();
			//ImGui::SetCursorPos(ImVec2(60, 16)); //���������

			ImGui::SetCursorPos(ImVec2(5, 5)); //���������
			//ImGui::Image(g_pSRV, { 44,44 });//ͼƬ���
		}
		ImGui::PopStyleVar();//Բ�ǽ���
		ImGui::EndChild();//�Ӵ��ڽ���
		//����������������������������������������������������������������������������������������
		Gui::���ѡ��˵�();
		//����������������������������������������������������������������������������������������
		if (�˵�λ�� == 0)
		{
			Gui::��ҳ�˵�();
		}
		if (�˵�λ�� == 1)
		{
			Gui::͸�Ӳ˵�();
		}
		if (�˵�λ�� == 2)
		{
			Gui::����˵�();
		}
		if (�˵�λ�� == 3)
		{
			Gui::����˵�();
		}
		if (�˵�λ�� == 4)
		{
			Gui::���ò˵�();
		}
		//����������������������������������������������������������������������������������������

		ImGui::PushFont(font_text3);//���忪ʼ
		ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.f); // ��ʽ
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(43.f / 255.f, 43.f / 255.f, 43.f / 255.f, 100.f / 255.f));  // ��ʽ
		ImGui::RenderNotifications(); // ��Ⱦ
		ImGui::PopStyleVar(1); // Don't forget to Pop()
		ImGui::PopStyleColor(1);
		ImGui::PopFont();//�������

		ImGui::End();//�����ڽ���
	}
}
//��������������������������������������������������������������������������������������������������������
void Gui::�����ʼ��()
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
	Colors[ImGuiCol_ChildBg] = ImGui::HexToImVec4("191717", 255); // ������ɫ

	Colors[ImGuiCol_Text] = ImGui::HexToImVec4("FFFFFF", 255); // �ı���ɫ
	Colors[ImGuiCol_CheckMark] = ImGui::HexToImVec4("FFFFFF", 255); // ��ѡ����ɫ
	Colors[ImGuiCol_SliderGrab] = ImGui::HexToImVec4("FFFFFF", 255); // ��������ɫ
	Colors[ImGuiCol_SliderGrabActive] = ImGui::HexToImVec4("FAC8FA", 255); // ������������ɫ

	Colors[ImGuiCol_Button] = ImGui::HexToImVec4("D8D9DA", 50); // ��ť��ɫ
	Colors[ImGuiCol_ButtonHovered] = ImGui::HexToImVec4("D8D9DA", 100); // ��ť�ȵ���ɫ
	Colors[ImGuiCol_ButtonActive] = ImGui::HexToImVec4("D8D9DA", 50); // ��ť������ɫ

	Colors[ImGuiCol_FrameBg] = ImGui::HexToImVec4("D8D9DA", 50); // ���������ɫ
	Colors[ImGuiCol_FrameBgHovered] = ImGui::HexToImVec4("D8D9DA", 50); // ��������ȵ���ɫ
	Colors[ImGuiCol_FrameBgActive] = ImGui::HexToImVec4("61677A", 50); // �������������ɫ

	Colors[ImGuiCol_Tab] = ImGui::HexToImVec4("D8D9DA", 50); // TAB��ɫ
	Colors[ImGuiCol_TabHovered] = ImGui::HexToImVec4("D8D9DA", 130); // TAB�ȵ���ɫ
	Colors[ImGuiCol_TabActive] = ImGui::HexToImVec4("D8D9DA", 130); // TAB������ɫ

	Colors[ImGuiCol_Header] = ImGui::HexToImVec4("D8D9DA", 50); // ������ѡ����ɫ
	Colors[ImGuiCol_HeaderHovered] = ImGui::HexToImVec4("D8D9DA", 130); // �������ȵ���ɫ
	Colors[ImGuiCol_HeaderActive] = ImGui::HexToImVec4("D8D9DA", 130); // ����������ɫ
	//----
	//Colors[ImGuiCol_TextDisabled] = ImGui::HexToImVec4("3D3B4A", 255); // �������ı�����ɫ
	//Colors[ImGuiCol_WindowBg] = ImGui::HexToImVec4("0F0E11", 255); // ���ڱ�������ɫ
	//Colors[ImGuiCol_PopupBg] = ImGui::HexToImVec4("121217", 255); // �������ڱ�������ɫ
	
	//Colors[ImGuiCol_Border] = ImGui::HexToImVec4("F7EFE5",100); // ���ñ߿����ɫ��
	//Colors[ImGuiCol_BorderShadow] = ImGui::HexToImVec4("EBE8E0", 0); // �߿���Ӱ����ɫ
	//Colors[ImGuiCol_TitleBg] = ImGui::HexToImVec4("19171F", 255); // ���ⱳ������ɫ
	//Colors[ImGuiCol_TitleBgCollapsed] = ImGui::HexToImVec4("FFF8F2", 191); // �۵�����ı�����ɫ
	//Colors[ImGuiCol_TitleBgActive] = ImGui::HexToImVec4("121217", 255); // ����ⱳ������ɫ
	//Colors[ImGuiCol_MenuBarBg] = ImGui::HexToImVec4("19171F", 255); // �˵�����������ɫ
	//Colors[ImGuiCol_ScrollbarBg] = ImGui::HexToImVec4("19171F", 255); // ��������������ɫ
	//Colors[ImGuiCol_ScrollbarGrab] = ImGui::HexToImVec4("CDCDD4", 79); // ������ץ�ֵ���ɫ
	//Colors[ImGuiCol_ScrollbarGrabHovered] = ImGui::HexToImVec4("8F8F94", 255); // �����ͣ�ڹ�����ץ����ʱ����ɫ
	//Colors[ImGuiCol_ScrollbarGrabActive] = ImGui::HexToImVec4("0F0E11", 255); // �������ץ�ֵ���ɫ
	//Colors[ImGuiCol_ResizeGrip] = ImGui::HexToImVec4("000000", 0); // ������С���ֵ���ɫ
	//Colors[ImGuiCol_ResizeGripHovered] = ImGui::HexToImVec4("8F8F94", 255); // �����ͣ�ڵ�����С������ʱ����ɫ
	//Colors[ImGuiCol_ResizeGripActive] = ImGui::HexToImVec4("0F0E11", 255); // �������С���ֵ���ɫ
	//Colors[ImGuiCol_PlotLines] = ImGui::HexToImVec4("646362", 161); // ��ͼ��������ɫ
	//Colors[ImGuiCol_PlotLinesHovered] = ImGui::HexToImVec4("40FF00", 255); // �����ͣ�ڻ�ͼ������ʱ����ɫ
	//Colors[ImGuiCol_PlotHistogram] = ImGui::HexToImVec4("646362", 161); // ֱ��ͼ����ɫ
	//Colors[ImGuiCol_PlotHistogramHovered] = ImGui::HexToImVec4("40FF00", 255); // �����ͣ��ֱ��ͼ��ʱ����ɫ
	//Colors[ImGuiCol_TextSelectedBg] = ImGui::HexToImVec4("40FF00", 110); // ѡ���ı��ı�����ɫ

}
//��������������������������������������������������������������������������������������������������������
void Gui::���ѡ��˵�()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	//ImGui::PushStyleColor(1,ImVec4(28,28,28,255));
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶȿ�ʼ
	ImGui::SetCursorPos({ 7,63 });//���������

	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##ѡ��˵�", { 65,630 }, false, 256))//�Ӵ���
	{
		ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.984f, 0.686f, 0.980f, 0.000f));//��ɫ��ʼ
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.000f, 1.000f, 1.000f, 0.129f));//��ɫ��ʼ
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.000f, 1.000f, 1.000f, 0.345f));//��ɫ��ʼ

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		ImGui::PushFont(font_text2);//���忪ʼ
		if (ImGui::Button(obf(ICON_FA_ID_CARD_ALT"").c_str(), ImVec2(40, 39)))
		{
			�˵�λ�� = 0;
		}

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button(obf(ICON_FA_EYE"").c_str(), ImVec2(40, 39)))
		{
			�˵�λ�� = 1;
		}

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button(obf(ICON_FA_MOUSE"").c_str(), ImVec2(40, 39)))
		{
			�˵�λ�� = 2;
		}

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button(obf(ICON_FA_DICE_D6"").c_str(), ImVec2(40, 39)))
		{
			�˵�λ�� = 3;
		}

		ImGui::NewLine();
		ImGui::Text("");
		ImGui::SameLine();
		ImGui::Text("");
		ImGui::SameLine();

		if (ImGui::Button(obf(ICON_FA_COGS"").c_str(), ImVec2(40, 39)))
		{
			�˵�λ�� = 4;
		}
		ImGui::PopStyleColor();//��ɫ����
		ImGui::PopStyleColor();//��ɫ����
		ImGui::PopStyleColor();//��ɫ����
		ImGui::PopFont();//�������

	}


	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�Ӵ��ڵĽ���
}
//��������������������������������������������������������������������������������������������������������
void Gui::��ҳ�˵�()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 77,63 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##��ҳ�˵�", { 730,630 }, false, 256))//�Ӵ��ڿ�ʼ
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		//ImGui::Text(u8"��ҳ�˵�");
		ImGui::TextGradiented(u8"��ҳ�˵�", 0xFFD95A, 0xFFF7D4, 66);

		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		��ҳ�˵�_����();


		//ImGui::NewLine();\

		//*ImGui::PushItemWidth(300);  // ����һ���ؼ��Ŀ������Ϊ300   ��ʼ
		//*
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*ImGui::Text(u8"style.Բ�ǽǶ�ֵ: %.3f", style.FrameRounding);
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*if (ImGui::SliderFloat(u8"Բ�� ������", &style.FrameRounding, 0.0f, 12.0f, "%.3f"))
		//*	style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
		//*
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*ImGui::Text(u8"����ֵ: %.4f", HuaKuaiTiao);
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*ImGui::SliderFloat(u8"������", &HuaKuaiTiao, 1.0000f, 20.0000f, "%.4f");
		//*
		//*ImGui::PopItemWidth();  // �ָ�Ԫ�ؿ��ΪĬ��ֵ ����
		//*
		//*ImGui::Text(u8"");
		//*ImGui::SameLine();
		//*if (ImGui::Button(u8" ���� ", ImVec2(0, 0)))
		//*{
		//*	printf_s("�߼�ֵ:%u", �Ƿ��ʼ��);
		//*}
		//*
		//*//ImGui::Text(u8"");
		//*//ImGui::SameLine();
		//*//ImGui::ColorEdit4("##color", (float*)&style->Colors[ImGuiCol_Text], ImGuiColorEditFlags_AlphaBar | alpha_flags);//��ɫѡ����
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
		//*ImGui::BeginChild("##colors", ImVec2(0, 0), true, 256);//�Ӵ��ڿ�ʼ
		//*ImGui::PushItemWidth(-160);
		//*
		//*ImGui::PushItemWidth(500);  // ����һ���ؼ��Ŀ������Ϊ300   ��ʼ
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
		//*ImGui::PopItemWidth();  // �ָ�Ԫ�ؿ��ΪĬ��ֵ ����
		//*ImGui::EndChild();//�Ӵ��ڵĽ���
		//*//������������������������������������������������������������������������������������
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


	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�Ӵ��ڵĽ���
}

void Gui::��ҳ�˵�_����()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 5,5 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##��ҳ�˵�_����", ImVec2(720, 620), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"��ҳ����", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		ImGui::Text(u8"");
		ImGui::SameLine();
		ImGui::Text(u8"NyL: Ҫ�����������Ϸ.");


	}
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�����ڵĽ���
}

void Gui::͸�Ӳ˵�()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	//ImGui::PushStyleColor(1,ImVec4(28,28,28,255));
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 77,63 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##ESP1", { 730,630 }, false, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		͸�Ӳ˵�_����();

		
	}
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�����ڵĽ���
}

void Gui::͸�Ӳ˵�_����()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 5,5 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##ESP2", ImVec2(720, 620), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"�Ӿ� >> ��ʾ����", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("##ESPset", tab_bar_flags))
		{
			if (ImGui::BeginTabItem(u8"����"))
			{
				͸�Ӳ˵�_����();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"���"))
			{
				͸�Ӳ˵�_���();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"��Ʒ"))
			{
				͸�Ӳ˵�_��Ʒ();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"�ؾ�"))
			{
				͸�Ӳ˵�_�ؾ�();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"�״�"))
			{
				͸�Ӳ˵�_�״�();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"��ɫ"))
			{
				͸�Ӳ˵�_��ɫ();
				ImGui::EndTabItem();
			}
			ImGui::EndTabBar();
		}
	}
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�����ڵĽ���
}

void Gui::͸�Ӳ˵�_����()
{
	if (ImGui::BeginChild("##��������", ImVec2(708, 557), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"�Ӿ� >> ����", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		if (ImGui::BeginTable("split##10", 4))
		{
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(8, 5));//��������߶� ��ʼ
			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"����", u8"\uf304 X", F::Global.Menu.�´���X_, IM_ARRAYSIZE(F::Global.Menu.�´���X_));//�����
			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"����", u8" Y", F::Global.Menu.�´���Y_, IM_ARRAYSIZE(F::Global.Menu.�´���Y_));//�����
			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"���", u8" ��", F::Global.Menu.�´���W_, IM_ARRAYSIZE(F::Global.Menu.�´���W_));//�����
			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"�߶�", u8" ��", F::Global.Menu.�´���H_, IM_ARRAYSIZE(F::Global.Menu.�´���H_));//�����
			ImGui::PopStyleVar();//��������߶� ����

			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����ģʽ", &F::Global.GameData.����ģʽ);

			ImGui::TableNextColumn();
			if (ImGui::Button(u8"\uf0c7 Ӧ��", ImVec2(70, 30))) {//ICON_FA_SAVE
				float XX = std::stof(F::Global.Menu.�´���X_);
				float YY = std::stof(F::Global.Menu.�´���Y_);
				float WW = std::stof(F::Global.Menu.�´���W_);
				float HH = std::stof(F::Global.Menu.�´���H_);

				F::Global.GameData.�´���X = XX;
				F::Global.GameData.�´���Y = YY;
				F::Global.GameData.�´���W = WW;
				F::Global.GameData.�´���H = HH;

				//���þ���W H
				F::Global.GameData.Width = (int)WW / 2;
				F::Global.GameData.Height = (int)HH / 2;

				glfwSetWindowPos(window1, F::Global.GameData.�´���X, F::Global.GameData.�´���Y);//�ƶ�����
				glfwSetWindowSize(window1, F::Global.GameData.�´���W, F::Global.GameData.�´���H);//�ı䴰�ڴ�С
			}
			ImGui::EndTable();//����
		}


		ImGui::EndChild();//�����ڵĽ���
	}
}

void Gui::͸�Ӳ˵�_���()
{
	if (ImGui::BeginChild("##�������", ImVec2(708, 557), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"�Ӿ� >> ���", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		if (ImGui::BeginTable("split", 4))
		{
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����", &F::Global.Menu.��ҷ���);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����", &F::Global.Menu.��ҹ���);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����", &F::Global.Menu.�������);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"Ѫ��", &F::Global.Menu.���Ѫ��);
			//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�״�", &ESP_Lite1);
			//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����", &ESP_Lite1);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"������Ϣ", &F::Global.Menu.�����Ϣ);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"������ʾ", &F::Global.Menu.������ʾ);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"��ͼ�״�", &F::Global.Menu.��ͼ�״�);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����ģʽ", &F::Global.Menu.��������ģʽ);
			//
			ImGui::TableNextColumn();
			ImGui::SetNextItemWidth(110);//���������� �˺���Ϊ��������һ������Ŀ��
			ImGui::SliderFloat(u8"������ϸ", &F::Global.Menu.������ϸ, 1.0f, 10.0f, "%.1f");
			ImGui::EndTable();//����
		}


		ImGui::EndChild();//�����ڵĽ���
	}
}

void Gui::͸�Ӳ˵�_��ɫ()
{
	if (ImGui::BeginChild("##��ɫ����-��Ʒ", ImVec2(708, 88), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"��ɫ >> ��Ʒ", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���
		if (ImGui::BeginTable("��Ʒ����ɫ�б�", 5))
		{
			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##1", (float*)&F::Global.Color.�ؾ�, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"�ؾ�");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##2", (float*)&F::Global.Color.ǹе, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"ǹе");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##3", (float*)&F::Global.Color.���, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"���");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##4", (float*)&F::Global.Color.����, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"����");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##5", (float*)&F::Global.Color.ҩƷ, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"ҩƷ");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##6", (float*)&F::Global.Color.Ͷ��, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"Ͷ��");

			ImGui::TableNextColumn();
			ImGui::ColorEdit4("MyColor##7", (float*)&F::Global.Color.��Ͷ����, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel);
			ImGui::SameLine(); ImGui::Text(u8"��Ͷ����");

			ImGui::EndTable();//����
		}
		ImGui::EndChild();//�����ڵĽ���
	}
	
}

void Gui::͸�Ӳ˵�_�״�()
{
	if (ImGui::BeginChild("##͸�Ӳ˵�_�״�", ImVec2(720, 110), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"�Ӿ� >> �״�", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		ImGui::Text(u8"");
		ImGui::SameLine();
		if (ImGui::BeginTable("split", 3))
		{
			float ProportionMin = 50.f, ProportionMax = 1500.f;
			float RadarRangeMin = 100.f, RadarRangeMax = 300.f;
			float RadarPointSizeProportionMin = 0.8f, RadarPointSizeProportionMax = 2.f;
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�״�", &F::Global.Menu.�״�);

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"�״��С", &F::Global.Menu.RadarRange, RadarRangeMin, RadarRangeMax, "%.1f");

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"��λ��С", &F::Global.Menu.RadarPointSizeProportion, RadarPointSizeProportionMin, RadarPointSizeProportionMax, "%.1f");

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"���Ŵ�С", &F::Global.Menu.Proportion, ProportionMin, ProportionMax, "%.1f");

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"��������X", &F::Global.Menu.RadarX, 0, F::Global.GameData.Width * 2, "%.1f");

			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"��������Y", &F::Global.Menu.RadarY, 0, F::Global.GameData.Height * 2, "%.1f");

			static float floattoint = (float)F::Global.Menu.RadarType;
			ImGui::TableNextColumn(); ImGui::SliderFloat(u8"�״���ʽ", &floattoint, 0, 2, "%.0f");
			F::Global.Menu.RadarType = floattoint;



		}
		ImGui::EndTable();//����

	}
	ImGui::EndChild();//�����ڵĽ���
}

void Gui::͸�Ӳ˵�_��Ʒ()//(������..)//static
{
	if (ImGui::BeginChild("##��Ʒ͸��ѡ��", ImVec2(708, 557), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"�Ӿ� >> ��Ʒ   ", 0xFFD95A, 0xFFF7D4, 66); ImGui::SameLine(); 
		ImGui::HotkeyYai(u8"�����л��� ", F::Global.Menu.�����л���, { 130,23 }); ImGui::SameLine();
		ImGui::HotkeyYai(u8"��͸���� ", F::Global.Menu.��͸�����ȼ�, { 130,23 }); ImGui::SameLine();
		if (ImGui::Button(obf(u8"����").c_str(), ImVec2(50, 24)))
		{
			for (size_t i = 0; i < F::Global.Menu.ItemsNames.size(); ++i) {
				std::string itemName = F::Global.Menu.ItemsNames[i];
				int groupIndex = F::Global.Menu.itemgrounp[i].��Ʒ��;
				std::string groupName = F::Global.Menu.items[groupIndex];

				std::cout << "��Ʒ��: " << itemName << ", ������: " << groupName << std::endl;

			}
		}

		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���
		//����������������������������������������������������������������������������������������������������������������

		static ImGuiTableFlags flags =
			ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Sortable | ImGuiTableFlags_SortMulti
			| ImGuiTableFlags_RowBg | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_NoBordersInBody
			| ImGuiTableFlags_ScrollY;

		ImGui::PushStyleColor(ImGuiCol_FrameBg, ImGui::HexToImVec4("191717", 255));//������ɫ
		ImGui::SetNextItemWidth(708); // ���������б��Ŀ��
		ImGui::SetNextWindowSizeConstraints(ImVec2(-1, 506.0f), ImVec2(-1, 506.0f));

		if (ImGui::BeginTable("ExampleTable", 2, flags)) // 2��ʾ����
		{
			ImGui::TableSetupColumn(u8"����");
			ImGui::TableSetupColumn(u8"��Ʒ��");
			ImGui::TableHeadersRow();

			for (int row = 0; row < F::Global.Menu.ItemsNames.size(); ++row)
			{
				ImGui::TableNextRow();
				for (int column = 0; column < 2; ++column)
				{
					ImGui::TableSetColumnIndex(column);
					if (column == 0)
					{
						// ��һ����ʾ����
						ImGui::Text("%s", F::Global.Menu.ItemsNames[row].c_str());
					}
					else
					{
						// �ڶ���ʹ�������������ʾ��Ʒ��
						char combo_label[32];
						sprintf(combo_label, "##��Ʒ��%d", row); // Ϊÿ�д���Ψһ�ı�ǩ
						if (ImGui::BeginCombo(combo_label, F::Global.Menu.items[F::Global.Menu.itemgrounp[row].��Ʒ��]))
						{
							for (int i = 0; i < IM_ARRAYSIZE(F::Global.Menu.items); ++i)
							{
								if (ImGui::Selectable(F::Global.Menu.items[i], F::Global.Menu.itemgrounp[row].��Ʒ�� == i))
									F::Global.Menu.itemgrounp[row].��Ʒ�� = i;
							}
							ImGui::EndCombo();
						}
					}
				}
			}

			ImGui::EndTable();
		}










		ImGui::PopStyleColor();//�ָ���ɫ
		ImGui::EndChild();//�����ڵĽ���
	}
}

void Gui::͸�Ӳ˵�_�ؾ�()
{
	if (ImGui::BeginChild("##��ɫ����-��Ʒ", ImVec2(708, 557), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"�Ӿ� >> �ؾ�", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���
		if (ImGui::BeginTable("split", 4))
		{
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����", &F::Global.MenuE.car1);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"������", &F::Global.MenuE.car2);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�γ�", &F::Global.MenuE.car3);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�ı�", &F::Global.MenuE.car4);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"Ħͧ", &F::Global.MenuE.car5);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"���˻�", &F::Global.MenuE.car6);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����", &F::Global.MenuE.car7);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����", &F::Global.MenuE.car8);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����", &F::Global.MenuE.car9);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"��ͧ", &F::Global.MenuE.car10);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"NIVA", &F::Global.MenuE.car11);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"ԽҰĦ��", &F::Global.MenuE.car12);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"KILLTRUCK", &F::Global.MenuE.car13);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"TUK", &F::Global.MenuE.car14);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�ܳ�", &F::Global.MenuE.car15);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"Ħ��", &F::Global.MenuE.car16);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"Helicopter", &F::Global.MenuE.car17);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"AIRCRAFT", &F::Global.MenuE.car18);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"װ�׳�", &F::Global.MenuE.car19);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"���г�", &F::Global.MenuE.car20);/*
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����Ȯ", &F::Global.MenuE.car21);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�����׳�", &F::Global.MenuE.car22);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"���ҹ�", &F::Global.MenuE.car23);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"��", &F::Global.MenuE.car24);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"������", &F::Global.MenuE.car25);*/
			
			//ImGui::SameLine(); Helpmarker(u8"ESP", style.Colors[ImGuiCol_Text]);
			ImGui::EndTable();
		}
		ImGui::EndChild();//�����ڵĽ���
	}
}

void Gui::����˵�()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	//ImGui::PushStyleColor(1,ImVec4(28,28,28,255));
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 77,63 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##AIM", { 730,630 }, false, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		//ImGui::TextGradiented(u8"����˵�", 0xFFD95A, 0xFFF7D4, 66);

		//ImGui::NewLine();//�µ�һ��
		//ImGui::Separator();//�ָ���
		����˵�_��׼();
		����˵�_����();

	}
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�����ڵĽ���
}

void Gui::����˵�_��׼()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 5,5 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##����˵�_��׼", ImVec2(720, 185), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //ͬ��
		ImGui::TextGradiented(u8"��׼ >> ��������", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		if (ImGui::BeginTable("AIM_Base", 2))//TAB��ʼ
		{
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"FOV��ʾ*", &F::Global.Menu.FOV��ʾ);
			ImGui::SameLine();
			Helpmarker(u8"��Ļ������ʾ����ķ�Χ", style.Colors[ImGuiCol_Text]);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"��̬FOV*", &ESP_Lite1);
			ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"֡��ͬ��*", &ESP_Lite1);
			ImGui::TableNextColumn();
			ImGui::PushItemWidth(50);  // �ÿؼ��Ŀ������ ��ʼ  �˺���Ϊ�����·��������
			ImGui::InputText(u8"##��Ϸ�ֱ���X", WBtxt0, IM_ARRAYSIZE(WBtxt0));
			ImGui::SameLine();
			ImGui::InputText(u8"��Ϸ�ֱ���*", WBtxt1, IM_ARRAYSIZE(WBtxt1));
			ImGui::PopItemWidth();  // �ָ��ؼ��Ŀ������ ����
			ImGui::SameLine();
			if (ImGui::Button(obf(u8"��ȡ").c_str(), ImVec2(45, 24)))
			{
				//printf("��δ����\n");

			}
		}

		ImGui::EndTable();//TAB����
		//��������������������������������������������������������������������������������
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���
		//��������������������������������������������������������������������������������
		ImGui::NewLine(); //�µ�һ��
		ImGui::Text(u8"������״̬:");
		ImGui::SameLine(); //��һ�в�����

		if (F::Global.Menu.����������״̬ == true)
		{
			sprintf_s(Box_State_buffer, u8"������");
			ImGui::TextGradiented(Box_State_buffer, 0x20FF00, 0xFAF7F0, 66);
		}
		else {
			if (F::Global.Menu.����������״̬ == false)
			{
				sprintf_s(Box_State_buffer, u8"δ����");
				ImGui::TextGradiented(Box_State_buffer, 0xFF0000FF, 0xFAF7F0, 66);
			}
		}

		if (ImGui::BeginTable("AIM_Base_BOX", 3))//TAB��ʼ
		{
			static bool buttonDisabled = false;

			if (buttonDisabled) {
				ImGui::PushItemFlag(ImGuiItemFlags_Disabled, true);//���þ�̬����״̬
				ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f); // ��ѡ�����ͽ��������͸����
			}

			ImGui::TableNextColumn(); ImGui::RadioButton(u8"KmBox", &F::Global.Menu.��������, 0);
			ImGui::TableNextColumn(); ImGui::RadioButton(u8"NYL-API", &F::Global.Menu.��������, 1);
			ImGui::TableNextColumn(); ImGui::RadioButton(u8"�׼���-Not", &F::Global.Menu.��������, 2);
			ImGui::TableNextColumn();
			F::Global.Menu.COMѡ���� = F::Global.Menu.���ö˿ں�[F::Global.Menu.�˿�����ֵ];
			if (ImGui::BeginCombo(u8"�˿ں�", F::Global.Menu.COMѡ����, 0))
			{
				for (int n = 0; n < IM_ARRAYSIZE(F::Global.Menu.���ö˿ں�); n++) {
					if (F::Global.Menu.���ö˿ں�[n] == nullptr || strlen(F::Global.Menu.���ö˿ں�[n]) == 0) {
						continue;
					}
					const bool is_selected = (F::Global.Menu.�˿�����ֵ == n);
					if (ImGui::Selectable(F::Global.Menu.���ö˿ں�[n], is_selected)) {
						F::Global.Menu.�˿�����ֵ = n;
					}
					if (is_selected) {
						ImGui::SetItemDefaultFocus();
					}
				}
				ImGui::EndCombo();
			}


			ImGui::TableNextColumn(); ImGui::InputTextWithHint(u8"������", "", F::Global.Menu.������������, IM_ARRAYSIZE(F::Global.Menu.������������));//�����

			ImGui::TableNextColumn();

			if (buttonDisabled) {
				ImGui::PopItemFlag();//��������״̬
				ImGui::PopStyleVar();//����͸��״̬
			}
			if (F::Global.Menu.�������� == 0)
			{
				if (F::Global.Menu.����������״̬ == true)
				{
					if (ImGui::Button(obf(u8"�Ͽ�����").c_str(), ImVec2(70, 24)))
					{
						F::Global.Menu.����������״̬ = false;
						buttonDisabled = false;
						G::kmbox.close();
						printf("������ -> �Ͽ��������ɹ�.\n");
					}
				}
				else {
					if (F::Global.Menu.����������״̬ == false)
					{
						if (ImGui::Button(obf(u8"���Ӻ���").c_str(), ImVec2(70, 24)))
						{
							//������
							int ������������ = std::stof(F::Global.Menu.������������);

							//����
							if (G::kmbox.open(F::Global.Menu.COMѡ����, ������������))
							{
								F::Global.Menu.����������״̬ = true;
								buttonDisabled = true;
								printf("NYL - >���� %s\n", F::Global.Menu.COMѡ����);
								printf("NYL - >������ %d\n", ������������);
								printf("������ -> ���ӿ������ɹ�!\n");
							}
							else
							{
								F::Global.Menu.����������״̬ = false;
								printf("������ -> ���ӿ�����ʧ��.\n");
							}



						}
					}
				}
				ImGui::SameLine(); //ͬ��
				if (ImGui::Button(obf(u8"ˢ�¶˿�").c_str(), ImVec2(70, 24)))
				{
					G::kmbox.ȡ���ô���();
				}
			}
			if (F::Global.Menu.�������� == 1) {
				if (F::Global.Menu.����������״̬ == true)
				{
					if (ImGui::Button(obf(u8"�Ͽ�����").c_str(), ImVec2(70, 24)))
					{
						F::Global.Menu.����������״̬ = false;
						buttonDisabled = false;
						printf("������ -> �Ͽ�API�ɹ�.\n");
					}
				}
				else {
					if (F::Global.Menu.����������״̬ == false)
					{
						if (ImGui::Button(obf(u8"���Ӻ���").c_str(), ImVec2(70, 24)))
						{
							F::Global.Menu.����������״̬ = true;
							buttonDisabled = true;
							printf("������ -> ����API�ɹ�!\n");
						}
					}
				}
			}

		}
		ImGui::EndTable();//TAB����


		/*ImGui::Text(u8"");
		//ImGui::SameLine();
		//ImGui::Hotkey(u8"�����ȼ� ", CUSTOM_KEY, 70, { 100,23 });*/

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
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�����ڵĽ���
}

void Gui::����˵�_����()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 5,195 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##����˵�_����", ImVec2(720, 250), true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"��׼ >> ��������", 0xFFD95A, 0xFFF7D4, 66);
		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
		if (ImGui::BeginTabBar("##������ǩ��", tab_bar_flags))
		{
			if (ImGui::BeginTabItem(u8"��׼����"))
			{
				����˵�_����_����();
				ImGui::EndTabItem();
			}

			/*if (ImGui::BeginTabItem(u8"��ǹ"))
			{
				����˵�_����_��ǹ();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"����"))
			{
				ImGui::Text(u8"������");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"˨��"))
			{
				ImGui::Text(u8"˨����");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"���ǹ"))
			{
				ImGui::Text(u8"���ǹ��");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"����ǹ"))
			{
				ImGui::Text(u8"����ǹ��");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem(u8"����"))
			{
				ImGui::Text(u8"����ǹ��");
				ImGui::EndTabItem();
			}*/
			ImGui::EndTabBar();
		}

		//ImGui::Text(u8"");
		/*ImGui::SameLine();
		ImGui::Hotkey(u8"�����ȼ� ", CUSTOM_KEY, 70, { 100,23 });*/

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
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�����ڵĽ���
}

void Gui::����˵�_����_����()
{
	if (ImGui::BeginTable("AIM_Base_W1", 3))//TAB��ʼ
	{
		//ImGui::TableNextColumn(); ImGui::Hotkey(u8"���ȼ� ", CUSTOM_KEY1, 60, { 100,23 });
		ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"���ȼ� ", F::Global.Menu.���鰴��, { 130,23 });
		ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"���ȼ� ", F::Global.Menu.�����Ӱ���, { 130,23 });
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�ȼ��ϲ�", &F::Global.Menu.�ȼ��ϲ�);
		/*ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����������", &ESP_Lite1);
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"��������", &ESP_Lite1);*/

		ImGui::TableNextColumn();
		if (ImGui::Combo(u8"����λ��", (int*)&F::Global.Menu.���鲿λ�б�����, u8"ͷ\0����\0�ؼ�\0ƨ��\0"))
		{
			/*if (F::Global.Menu.���鲿λ�б����� == 0)
			{
				F::Global.Menu.����λ�� = 46;
			}
			if (F::Global.Menu.���鲿λ�б����� == 1)
			{
				F::Global.Menu.����λ�� = 45;
			}
			if (F::Global.Menu.���鲿λ�б����� == 2)
			{
				F::Global.Menu.����λ�� = 1;
			}
			if (F::Global.Menu.���鲿λ�б����� == 3)
			{
				F::Global.Menu.����λ�� = 6;
			}*/
			//printf("λ��: %d\n", F::Global.Menu.����λ��);


		}

		//ImGui::PushItemWidth(88);  // �ÿؼ��Ŀ������   ��ʼ
		//ImGui::Combo(u8"��������", (int*)&��������, u8"�Ӳ�\0ʼ��\0���ȴ��\0");
		//ImGui::PopItemWidth();  // �ָ��ؼ��Ŀ������ ����

		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"���Ӽ��", &ESP_Lite1);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����Ԥ��", &ESP_Lite1);

		//ImGui::TableNextColumn(); ImGui::SliderFloat(u8"��׼����", &HuaKuaiTiao, 1.0f, 1000.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"FOV", &F::Global.Menu.����FOV, 1.0f, 360.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"X���ٶ�", &F::Global.Menu.����X��, 1.0f, 20.0f, "%.3f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"Y���ٶ�", &F::Global.Menu.����Y��, 1.0f, 20.0f, "%.3f");
		//ImGui::TableNextColumn(); ImGui::SliderFloat(u8"�����ٶ�", &F::Global.Menu.�����ٶ�, 1.0f, 100.0f, "%.2f");
		//ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"������� ", F::Global.Menu.�������, { 130,23 });

		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"֡��", &F::Global.Menu.����֡��, 1.0f, 240.0f, "%.0f");
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�����ж�", &F::Global.Menu.�����ж�);
		//ImGui::TableNextColumn(); ImGui::SliderFloat(u8"����ӳ�", &F::Global.Menu.����ӳ�, 10.0f, 3000.0f, "%.0f");

		//ImGui::TableNextColumn();
		//
		//ImGui::PushItemWidth(88);  // �ÿؼ��Ŀ������   ��ʼ
		//ImGui::Combo(u8"�㷨", (int*)&�㷨, u8"��ģʽ\0��ģʽ\0");
		//ImGui::PopItemWidth();  // �ָ��ؼ��Ŀ������ ����

		//ImGui::TableNextColumn(); ImGui::SliderScalar(u8"����Pitch", ImGuiDataType_Float, &yizhi_default, &yizhi_min, &yizhi_max, "%.3f");
		//ImGui::TableNextColumn();
		//ImGui::TableNextColumn(); ImGui::SliderScalar(u8"����Yaw", ImGuiDataType_Float, &yizhi_default, &yizhi_min, &yizhi_max, "%.3f");






		//ImGui::SameLine();
		//Helpmarker(u8"��Ļ������ʾ����ķ�Χ", style.Colors[ImGuiCol_Text]);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"��̬FOV", &ESP_Lite1);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"֡��ͬ��", &ESP_Lite1);
		//ImGui::TableNextColumn();
		//ImGui::PushItemWidth(50);  // �ÿؼ��Ŀ������   ��ʼ
		//ImGui::InputText(u8"##��Ϸ�ֱ���X", WBtxt0, IM_ARRAYSIZE(WBtxt0));
		//ImGui::SameLine();
		//ImGui::InputText(u8"��Ϸ�ֱ���", WBtxt1, IM_ARRAYSIZE(WBtxt1));
		//ImGui::PopItemWidth();  // �ָ��ؼ��Ŀ������ ����
		//ImGui::SameLine();
		//if (ImGui::Button(obf(u8"��ȡ").c_str(), ImVec2(45, 24)))
		//{

		//}
	}
	ImGui::EndTable();//TAB����


}

void Gui::����˵�_����_��ǹ()
{
	if (ImGui::BeginTable("AIM_Base_W1", 3))//TAB��ʼ
	{
		//ImGui::TableNextColumn(); ImGui::Hotkey(u8"���ȼ� ", CUSTOM_KEY1, 60, { 100,23 });
		ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"���ȼ� ", CUSTOM_KEY1, { 130,23 });
		ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"���ȼ� ", CUSTOM_KEY2, { 130,23 });
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�ȼ��ϲ�", &ESP_Lite1);
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����������", &ESP_Lite1);
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"��������", &ESP_Lite1);

		ImGui::TableNextColumn();

		ImGui::PushItemWidth(88);  // �ÿؼ��Ŀ������   ��ʼ
		ImGui::Combo(u8"��������", (int*)&��������, u8"�Ӳ�\0ʼ��\0���ȴ��\0");
		ImGui::PopItemWidth();  // �ָ��ؼ��Ŀ������ ����

		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"���Ӽ��", &ESP_Lite1);
		ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����Ԥ��", &ESP_Lite1);

		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"��׼����", &HuaKuaiTiao, 1.0f, 1000.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"FOV", &HuaKuaiTiao, 1.0f, 1000.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"X���ٶ�", &HuaKuaiTiao, 1.0f, 1000.0f, "%.3f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"Y���ٶ�", &HuaKuaiTiao, 1.0f, 1000.0f, "%.3f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"�����Ա���", &HuaKuaiTiao, 1.0f, 80.0f, "%.0f");
		ImGui::TableNextColumn(); ImGui::SliderFloat(u8"֡��", &HuaKuaiTiao, 1.0f, 240.0f, "%.0f");

		ImGui::TableNextColumn();

		ImGui::PushItemWidth(88);  // �ÿؼ��Ŀ������   ��ʼ
		ImGui::Combo(u8"�㷨", (int*)&�㷨, u8"��ģʽ\0��ģʽ\0");
		ImGui::PopItemWidth();  // �ָ��ؼ��Ŀ������ ����

		ImGui::TableNextColumn(); ImGui::SliderScalar(u8"����Pitch", ImGuiDataType_Float, &yizhi_default, &yizhi_min, &yizhi_max, "%.3f");
		ImGui::TableNextColumn();
		ImGui::TableNextColumn(); ImGui::SliderScalar(u8"����Yaw", ImGuiDataType_Float, &yizhi_default, &yizhi_min, &yizhi_max, "%.3f");






		//ImGui::SameLine();
		//Helpmarker(u8"��Ļ������ʾ����ķ�Χ", style.Colors[ImGuiCol_Text]);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"��̬FOV", &ESP_Lite1);
		//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"֡��ͬ��", &ESP_Lite1);
		//ImGui::TableNextColumn();
		//ImGui::PushItemWidth(50);  // �ÿؼ��Ŀ������   ��ʼ
		//ImGui::InputText(u8"##��Ϸ�ֱ���X", WBtxt0, IM_ARRAYSIZE(WBtxt0));
		//ImGui::SameLine();
		//ImGui::InputText(u8"��Ϸ�ֱ���", WBtxt1, IM_ARRAYSIZE(WBtxt1));
		//ImGui::PopItemWidth();  // �ָ��ؼ��Ŀ������ ����
		//ImGui::SameLine();
		//if (ImGui::Button(obf(u8"��ȡ").c_str(), ImVec2(45, 24)))
		//{

		//}
	}
	ImGui::EndTable();//TAB����


}

void Gui::����˵�()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 77,63 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##����˵�", { 730,630 }, false, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"##������", 0xFFD95A, 0xFFF7D4, 66);

		if (ImGui::BeginTable("##����TAB", 2))//TAB��ʼ
		{
			//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�޺�����", &F::Global.Menu.�޺���);
			//ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"���ٿ�ǹ", &F::Global.Menu.���ٿ�ǹ);


		}ImGui::EndTable();//TAB����
		

		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���


	}
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�����ڵĽ���
}

void Gui::���ò˵�()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 77,63 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##���ò˵�", { 730,630 }, false, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		//ImGui::TextGradiented(u8"���ò˵�", 0xFFD95A, 0xFFF7D4, 66);

		//ImGui::NewLine();//�µ�һ��
		//ImGui::Separator();//�ָ���

		//����������������������������������������������������������������������������������������������������������������
		���ò˵�_�����ļ�();

		���ò˵�_����();



	}
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�Ӵ��ڵĽ���
}

void Gui::���ò˵�_�����ļ�()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 5,5 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##���ò˵�_�����ļ�", { 720,90 }, true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"���ò˵� >> ����", 0xFFD95A, 0xFFF7D4, 66);

		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		//����������������������������������������������������������������������������������������������������������������
		ImGui::SetCursorPos(ImVec2(5, 45));//���������
		static char �����ļ���[128] = "Config";
		ImGui::SetNextItemWidth(180);//���������� �˺���Ϊ��������һ������Ŀ��
		ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(10, 5));//��������߶� ��ʼ
		ImGui::InputTextWithHint("##����", u8"\uf0c7 �����ļ���", �����ļ���, IM_ARRAYSIZE(�����ļ���));//�����
		//ImGui::InputTextWithHint("##����", u8"\uf0c7 �����ļ���", (char*)cfgName.c_str(), cfgName.size(), ImGuiInputTextFlags_CallbackResize, InputTextCallback, (void*)&cfgName);
		//����������������������������������������������������������������������������������������������������������������
		ImGui::SameLine();
		ImGui::PopStyleVar();//��������߶� ����

		ImGui::Checkbox(u8"��������", &F::Global.Menu.Debug);

		if (ImGui::Button(u8"\uf0c7 ����", ImVec2(70, 30))) {//ICON_FA_SAVE
			//save(FileH::getProjCfgPath() + "\\" + cfgName + obf(".ini"));
			printf_s("������־: ��������Ϊ %s �������ļ�\n", �����ļ���);

			if (!U::Config.DirectoryExists(E("Config")))
			{
				U::Config.CreatFolder(�����ļ���);
				U::Config.CreatConfigeFile(�����ļ���);
			}

			JsonSystem::HandleConfig(�����ļ���, ConfigHandle::Save);

			//memset(�����ļ���, 0, sizeof(�����ļ���));

			ImGuiToast ff(ImGuiToastType_Success, 5000);//����ͼ��ͳ���ʱ��
			ff.set_title(u8" ");//���ڱ���
			ff.set_content(u8" �����ļ�������� ");//��������
			ImGui::InsertNotification(ff);//��������
			//�����ļ��� == "Default";

		}
		ImGui::SameLine(); //��һ�в�����
		if (ImGui::Button(u8"\uf233 ����", ImVec2(70, 30))) {//ICON_FA_SERVER
			//save(FileH::getProjCfgPath() + "\\" + cfgName + obf(".ini"));
			printf_s("������־: ��������Ϊ %s �������ļ�\n", �����ļ���);


			if (!U::Config.DirectoryExists(E("Config")))
			{
				U::Config.CreatFolder(�����ļ���);
				U::Config.CreatConfigeFile(�����ļ���);
			}
			JsonSystem::HandleConfig(�����ļ���, ConfigHandle::Load);

			//�����ļ��� == "Default";
			//memset(�����ļ���, 0, sizeof(�����ļ���));
		}


	}
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�Ӵ��ڵĽ���
}

void Gui::���ò˵�_����()
{
	ImGuiStyle& style = ImGui::GetStyle();

	ImGui::SetNextWindowBgAlpha(255);
	ImGui::PushStyleVar(7, 5);//Բ�ǽǶ�
	ImGui::SetCursorPos({ 5,100 });//���������
	//ImGui::BeginChild("##colors", ImVec2(730, 630), true, ImGuiWindowFlags_AlwaysVerticalScrollbar | ImGuiWindowFlags_AlwaysHorizontalScrollbar | ImGuiWindowFlags_NavFlattened);
	if (ImGui::BeginChild("##���ò˵�_����", { 720,525 }, true, 256))//�����ô�С
	{
		ImGui::SetCursorPos(ImVec2(5, 5));//���������
		//ImGui::NewLine(); //�µ�һ��
		//ImGui::SameLine(); //��һ�в�����
		ImGui::TextGradiented(u8"DeBug >> NYL", 0xFF55BB, 0xFFF7D4, 255);
		ImGui::SameLine();

		static char UiFps[256];
		sprintf_s(UiFps, u8"%.0f Fps", ImGui::GetIO().Framerate);
		ImGui::TextGradiented(UiFps, 0xFF55BB, 0xFFF7D4, 66);

		ImGui::NewLine();//�µ�һ��
		ImGui::Separator();//�ָ���

		//ImGui::CheckFullbox(u8"���Դ�ӡ����", &F::Global.Menu.��������ģʽ);

		//����������������������������������������������������������������������������������������������������������������
		//if (ImGui::BeginTable("GM_", 2))//TAB��ʼ
		//{
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"����GName", &ESP_Lite1);
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"���Թ�����", &ESP_Lite1);
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�������� Name��ID", &ESP_Lite1);
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"��GnameID", &ESP_Lite1);
		//	ImGui::TableNextColumn(); ImGui::CheckFullbox(u8"�������", &ESP_Lite1);
		//	ImGui::TableNextColumn();
		//	ImGui::TableNextColumn(); ImGui::SliderFloat(u8"GName��Χ", &HuaKuaiTiao, 1.0f, 1000.0f, "%.2f");
		//	ImGui::TableNextColumn(); ImGui::SliderFloat(u8"�����㷶Χ", &HuaKuaiTiao, 1.0f, 1000.0f, "%.2f");
		//
		//}
		//ImGui::EndTable();//TAB����
		//
		//ImGui::Separator();//�ָ���
		////����������������������������������������������������������������������������������������������������������������
		//ImGui::TableNextColumn(); ImGui::Hotkey(u8"1�ȼ� ", CUSTOM_KEY, 60, { 130,23 });
		//ImGui::TableNextColumn(); ImGui::HotkeyYai(u8"2�ȼ�    ", CUSTOM_KEY1, { 140,23 });
		//
		//if (ImGui::Button(obf(u8"����").c_str(), ImVec2(50, 24)))
		//{
		//	ImGuiToast ff(ImGuiToastType_Success, 5000);//����ͼ��ͳ���ʱ��
		//	ff.set_title(u8" ");//���ڱ���
		//	ff.set_content(u8" ���Գɹ�������� ");//��������
		//	ImGui::InsertNotification(ff);//��������
		//}

		ImGui::HotkeyYai(u8"ˢ�³���", F::Global.Menu.ˢ�����ݰ���, { 130,23 });
		ImGui::SameLine();
		Helpmarker(u8"����Ϸ��Ч��ȱʧ��ȱ�ٵ�ʱ��һ��!", style.Colors[ImGuiCol_Text]);


		///*text2��0
		//text3��1
		//text1��2*/
		////ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]);//�л�����һ������
		////ImGui::TextGradiented(u8"font_text1 XXXXXX ���� 0", 0xFFD95A, 0xFFF7D4, 66);
		////ImGui::PopFont();//�������
		//ImGui::PushFont(font_text1);//�������
		//ImGui::TextGradiented(u8"Font NYL ����������Ϸ ##1", 0xFFD95A, 0xFFF7D4, 66);
		//ImGui::PopFont();//�������

		//ImGui::PushFont(font_text2);//�������
		////ImGui::SetWindowFontScale(2.f);
		////ImGui::DragFloat("Font scale", &font_text2->Scale, 0.005f, 0.3f, 2.0f, "%.1f");
		////font_text2->Scale = 3.f;
		//ImGui::TextGradiented(u8"Font NYL ����������Ϸ ##2", 0xFFD95A, 0xFFF7D4, 66);
		//ImGui::PopFont();//�������

		//ImGui::PushFont(font_text3);//�������
		//ImGui::TextGradiented(u8"Font NYL ����������Ϸ ##3", 0xFFD95A, 0xFFF7D4, 66);
		//ImGui::PopFont();//�������


		//if (GetAsyncKeyState(CUSTOM_KEY1) & 1) {//��ⰴ���Ƿ���
		//	ImGuiToast ff(ImGuiToastType_Success, 5000);//����ͼ��ͳ���ʱ��
		//	ff.set_title(u8" ");
		//	ff.set_content(u8" ���Գɹ�������� ");
		//	ImGui::InsertNotification(ff);//��������
		//}

		static char kmboxCOMMenter[256] = "km.move(0,100)";

		ImGui::InputTextWithHint("##����ָ��", u8"\uf304 COM", kmboxCOMMenter, IM_ARRAYSIZE(kmboxCOMMenter));//�����
		ImGui::SameLine(); //��һ�в�����
		if (ImGui::Button(obf(u8"����").c_str(), ImVec2(50, 24)))
		{
			//��km.move(0,100)��
			//km.left(1)�������
			//km.left(0)�������
			string kmboxCOMM(kmboxCOMMenter);
			kmboxCOMM += "\r\n";
			G::kmbox.send(kmboxCOMM.c_str());

		}
		ImGui::SameLine(); //��һ�в�����
		if (ImGui::Button(obf(u8"�ƶ�").c_str(), ImVec2(50, 24)))
		{
			G::kmbox.move(0, 100);
		}
		ImGui::SameLine(); //��һ�в�����
		if (ImGui::Button(obf(u8"���").c_str(), ImVec2(50, 24)))
		{
			G::kmbox.send("km.left(1)\r\n");
			G::kmbox.send("km.left(0)\r\n");
		}

		if (ImGui::Button(obf(u8"ˢ��").c_str(), ImVec2(50, 24)))
		{
			G::Mem.ConfigSet();
		}

		/*ImGui::CheckFullbox(u8"�������", &ESP_Lite1);

		if (ESP_Lite1)
		{
			if (F::Global.GameData.�������)
			{
				G::kmbox.send("km.left(1)\r\n");
				G::kmbox.send("km.left(0)\r\n");
			}
		}*/



	}
	ImGui::PopStyleVar();//Բ�ǽ���
	ImGui::EndChild();//�Ӵ��ڵĽ���
}


