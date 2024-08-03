#pragma once
#include "Game.h"
#include "struct.h"
#include "Features/Global.h"
#include "draw.hpp"

using namespace draw;
class Render
{
public:
	void Init();
	void 物品绘制();
	void Attath();
	std::vector<player_data> 处理好的玩家数组;
	std::vector<Item> 处理好的物品数组;
	std::vector<PackgeItem> 处理好的盒子数组;
	std::vector<Item> 处理好的地面物品数组;
	std::vector<vehicle> 处理好的载具数组;

	std::vector<Actor> 调试数组;

	std::vector<player_bone> bonedata;
	FVector 叠加物品(FVector ItemScreenLocation);
	BOOL DrawItem(string PackageItemName, OUT FVector* ItemScreenLocation, ImColor Color, FLOAT EntityDistance);
	BOOL DrawItem(string PackageItemObjName, FVector2 ItemScreenLocation, ImColor Color, FLOAT EntityDistance);
};

namespace G { inline Render render; };