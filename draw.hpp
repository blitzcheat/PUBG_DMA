
#include "Features/Global.h"
#include "Radar/Radar.h"
#define TXT_DEFAULT		(1 << 0)
#define TXT_LEFT		(1 << 1)
#define TXT_TOP			(1 << 2)
#define TXT_CENTERX		(1 << 3)
#define TXT_CENTERY		(1 << 4)
#define TXT_CENTERXY	TXT_CENTERX | TXT_CENTERY


namespace draw
{
	inline void RadarSetting(Base_Radar& Radar)
	{
		if (!F::Global.Menu.雷达) return;
		// Radar window
		ImGui::Begin("Radar", 0, ImGuiWindowFlags_NoBackground);
		ImGui::SetWindowSize("Radar", { F::Global.Menu.RadarRange * 2,F::Global.Menu.RadarRange * 2 });
		ImGui::SetWindowPos("Radar", ImVec2{ F::Global.Menu.RadarX ,F::Global.Menu.RadarY });//窗口位置
		//Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
		Radar.SetDrawList(ImGui::GetWindowDrawList());
		Radar.SetPos({ ImGui::GetWindowPos().x + F::Global.Menu.RadarRange, ImGui::GetWindowPos().y + F::Global.Menu.RadarRange });
		Radar.SetProportion(F::Global.Menu.Proportion * 10);
		Radar.SetRange(F::Global.Menu.RadarRange);
		Radar.SetSize(F::Global.Menu.RadarRange * 2);
		Radar.SetCrossColor(F::Global.Menu.RadarCrossLineColor);

		Radar.ArcArrowSize *= F::Global.Menu.RadarPointSizeProportion;
		Radar.ArrowSize *= F::Global.Menu.RadarPointSizeProportion;
		Radar.CircleSize *= F::Global.Menu.RadarPointSizeProportion;

		Radar.ShowCrossLine = F::Global.Menu.ShowRadarCrossLine;
		Radar.Opened = true;
		ImGui::End();

	}
	inline void 绘制线条(FVector2 point1, FVector2 point2, ImColor color, float thickness)
	{
		ImGui::GetWindowDrawList()->AddLine(
			{ point1.X,point1.Y },
			{ point2.X,point2.Y }, color, thickness);
	}
	inline void DrawRect(float x, float y, float w, float h, ImColor color, int thickness)
	{
		ImGui::GetForegroundDrawList()->AddRect(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.f, 0.f, thickness);
	}
	inline void DrawFilledRect(float x, float y, float w, float h, ImColor color)
	{
		ImGui::GetForegroundDrawList()->AddRectFilled(ImVec2(x, y), ImVec2(x + w, y + h), color, 0.f, 0.f);
	}
	inline void 横向血条(float x, float y, float w, float h, float Health, float MaxHealth)
	{
		float f_w = w < 70.f ? 70.f : 100.f;
		float _Health = Health / MaxHealth * 100;
		ImColor clr = ImColor(0, 255, 0);
		if (_Health > 80.0f)clr = ImColor(0, 255, 0);
		else if (_Health > 60.0f)clr = ImColor(124, 252, 0);
		else if (_Health > 40.0f)clr = ImColor(255, 255, 0);
		else if (_Health > 15.0f)clr = ImColor(255, 215, 0);
		else clr = ImColor(255, 0, 0);

		float hp_h = w - (Health / MaxHealth * w);
		
		DrawFilledRect(x - (f_w - w) / 2 - 1, y - 5, f_w + 2, 6, ImColor(0, 0, 0, 150));
		DrawFilledRect(x - (f_w - w) / 2, y - 4, f_w * Health / MaxHealth, 4, clr);

		/*绘制线条(FVector2(x, y - 5), FVector2(x + w, y - 5), ImColor(0, 0, 0), 5);
		绘制线条(FVector2(x+1, y - 5), FVector2(x + w - hp_h-1, y - 5), clr, 3);*/
	}
	inline void 绘制血条(float x, float y, float h, float Health, float MaxHealth, int a)
	{
		ImColor color;
		float dwDrawWidth;
		float borderWidth = 6.f;  // 血条边框的宽度设置为 6
		float fillWidth = borderWidth - 1; // 填充宽度小于边框宽度

		if (a == 1) {
			color = ImColor(141, 75, 187);
			dwDrawWidth = Health * h / MaxHealth;
			DrawRect(x - borderWidth, y, borderWidth, h, ImColor(255, 255, 255), 1.0f);
			DrawFilledRect(x - fillWidth, y + h - dwDrawWidth + 1, fillWidth-1, dwDrawWidth - 2, color);
		}
		else {
			if (Health == MaxHealth)
			{
				color = ImColor(0, 255, 0);
			}
			else
			{
				color = ImColor(255, 0, 0);
			}
			dwDrawWidth = Health * h / MaxHealth;
			DrawRect(x - borderWidth, y, borderWidth, h, ImColor(255, 255, 255), 1.0f);
			DrawFilledRect(x - fillWidth, y + h - dwDrawWidth + 1, fillWidth-1, dwDrawWidth - 1, color);
		}
	}
	inline void 绘制文本(float x, float y, const short align, ImColor color, const char* fmt, ...)
	{
		x = (float)x;
		y = (float)y;
		char buf[1024] = { 0 };
		va_list va_alist;
		va_start(va_alist, fmt);
		_vsnprintf_s(buf, sizeof(buf) - 1, fmt, va_alist);

		va_end(va_alist);

		if (align)
		{
			ImVec2 WH = ImGui::CalcTextSize(buf);

			if (align & TXT_LEFT)
				x -= WH.x;

			if (align & TXT_TOP)
				y -= WH.y;

			if (align & TXT_CENTERX)
				x -= (WH.x / 2);

			if (align & TXT_CENTERY)
				y -= (WH.y / 2);
		}

		ImGui::GetForegroundDrawList()->AddText({ x,y }, color, buf);
	}

	inline VOID CircleFilled(FLOAT X, FLOAT Y, FLOAT Radius, ImVec4 Color, INT Segments)
	{
		return ImGui::GetForegroundDrawList()->AddCircleFilled(ImVec2(X, Y), Radius, ImGui::ColorConvertFloat4ToU32(ImVec4(Color)), Segments);
	}

	inline float 绘制文本2(float x, float y, const short align, ImColor color, const char* fmt, ...)
	{
		x = (float)x;
		y = (float)y;
		char buf[1024] = { 0 };
		va_list va_alist;
		va_start(va_alist, fmt);
		_vsnprintf_s(buf, sizeof(buf) - 1, fmt, va_alist);

		va_end(va_alist);
		ImVec2 WH = ImGui::CalcTextSize(buf);
		if (align)
		{


			if (align & TXT_LEFT)
				x -= WH.x;

			if (align & TXT_TOP)
				y -= WH.y;

			if (align & TXT_CENTERX)
				x -= (WH.x / 2);

			if (align & TXT_CENTERY)
				y -= (WH.y / 2);
		}

		ImGui::GetForegroundDrawList()->AddText({ x,y }, color, buf);
		return x - WH.x / 2;
	}

}