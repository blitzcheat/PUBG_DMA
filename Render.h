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
	void ��Ʒ����();
	void Attath();
	std::vector<player_data> ����õ��������;
	std::vector<Item> ����õ���Ʒ����;
	std::vector<PackgeItem> ����õĺ�������;
	std::vector<Item> ����õĵ�����Ʒ����;
	std::vector<vehicle> ����õ��ؾ�����;

	std::vector<Actor> ��������;

	std::vector<player_bone> bonedata;
	FVector ������Ʒ(FVector ItemScreenLocation);
	BOOL DrawItem(string PackageItemName, OUT FVector* ItemScreenLocation, ImColor Color, FLOAT EntityDistance);
	BOOL DrawItem(string PackageItemObjName, FVector2 ItemScreenLocation, ImColor Color, FLOAT EntityDistance);
};

namespace G { inline Render render; };