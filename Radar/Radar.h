#pragma once
#define _USE_MATH_DEFINES
#include "../Includes.h"
#include <math.h>
#include <tuple>
#include "../struct.h"


class Base_Radar
{
public:
	// �����״�����
	void SetSize(const float& Size);
	void SetPos(const FVector2& Pos);
	void SetRange(const float& Range);
	void SetCrossColor(const ImColor& Color);
	void SetProportion(const float& Proportion);
	void SetDrawList(ImDrawList* DrawList);
	// ��ȡ�״�����
	float GetSize();
	FVector2 GetPos();
	// ��ӻ��Ƶ�
	void AddPoint(const FVector& LocalPos, const float& LocalYaw, const FVector& Pos, ImColor Color, int Type = 0, float Yaw = 0.0f);
	// ��Ⱦ
	void Render();
public:
	ImDrawList* DrawList = nullptr;
	// ʮ����ʾ
	bool ShowCrossLine = true;
	// ʮ����ɫ
	ImColor CrossColor = ImColor(255, 255, 255, 255);
	// ����
	float Proportion = 2680;
	// Բ��뾶
	float CircleSize = 4;
	// ��ͷ�ߴ�
	float ArrowSize = 11;
	// Բ����ͷ�ߴ�
	float ArcArrowSize = 7;
	// �״ﷶΧ
	float RenderRange = 250;
	// ����Yaw����
	float LocalYaw = 0.0f;
	// ״̬
	bool Opened = true;
	// �״�������� 0:Բ�� 1:��ͷ 2:Բ����ͷ
	int  PointType = 0;
private:
	FVector2  Pos{ 0,0 };
	float Width = 200;
	std::vector<std::tuple<FVector2, ImColor, int, float>> Points;
};