#pragma once
#define _USE_MATH_DEFINES
#include "../Includes.h"
#include <math.h>
#include <tuple>
#include "../struct.h"


class Base_Radar
{
public:
	// 设置雷达数据
	void SetSize(const float& Size);
	void SetPos(const FVector2& Pos);
	void SetRange(const float& Range);
	void SetCrossColor(const ImColor& Color);
	void SetProportion(const float& Proportion);
	void SetDrawList(ImDrawList* DrawList);
	// 获取雷达数据
	float GetSize();
	FVector2 GetPos();
	// 添加绘制点
	void AddPoint(const FVector& LocalPos, const float& LocalYaw, const FVector& Pos, ImColor Color, int Type = 0, float Yaw = 0.0f);
	// 渲染
	void Render();
public:
	ImDrawList* DrawList = nullptr;
	// 十字显示
	bool ShowCrossLine = true;
	// 十字颜色
	ImColor CrossColor = ImColor(255, 255, 255, 255);
	// 比例
	float Proportion = 2680;
	// 圆点半径
	float CircleSize = 4;
	// 箭头尺寸
	float ArrowSize = 11;
	// 圆弧箭头尺寸
	float ArcArrowSize = 7;
	// 雷达范围
	float RenderRange = 250;
	// 本地Yaw数据
	float LocalYaw = 0.0f;
	// 状态
	bool Opened = true;
	// 雷达绘制类型 0:圆形 1:箭头 2:圆弧箭头
	int  PointType = 0;
private:
	FVector2  Pos{ 0,0 };
	float Width = 200;
	std::vector<std::tuple<FVector2, ImColor, int, float>> Points;
};