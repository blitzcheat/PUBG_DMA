#pragma once
#include "Includes.h"
#include "struct.h"

namespace Game
{

	typedef enum _EntityType
	{
		EntityTypeUnknown = 0,
		EntityTypePlayer,
		EntityTypeItem,
		EntityTypeItemGroup,
		枪械,
		配件,
		防具,
		药品,
		投掷,
		ProGrenade,
		载具,
		空投,
		盒子,
		大厅,
		游戏內
	}EntityType, * PEntityType;


	typedef enum _EItemType
	{
		UnKnown = 0,

		K2,
		M416,
		AWM,
		M24,
		SKS,
		G36C,
		M249,
		DP28,
		MK12,
		MK14,
		AKM,
		QBU8,
		M16A4,
		QB95,
		Groza,
		SLR,
		莫辛纳甘,
		迫击炮,
		SCARL,
		Kar98k,
		Mini14,
		信号枪,
		M762,
		MK47,
		ACE32,
		P90,
		法玛斯,
		Vector,
		野牛冲锋枪,
		UZI,
		VSS,
		Win94,
		汤姆逊,
		UMP9,
		S12K,
		霰弹手喷,
		MP5K,
		AMR,
		P1911,
		M79,
		P92,
		MG3,
		JS9,

		急救包,
		医疗箱,
		止疼,
		饮料,
		售货级,
		肾上腺素,
		绷带,


		二倍镜,
		三倍镜,
		四倍镜,
		六倍镜,
		八倍镜,
		十五倍镜,
		垂直,
		全息,
		红点,
		枪托,
		枪消,
		普扩,
		枪补,
		托腮,
		狙扩,
		狙消,
		狙补,
		快扩,

		吉利服,
		二头盔,
		三头盔,
		一背包,
		二背包,
		三背包,
		一级甲,
		二级甲,
		三级甲,
		呼救器,
		//神秘钥匙,

		手雷,
		C4炸弹,
		烟雾弹,
		篮圈手雷,
		黏土炸弹,

		无人机侦察,
		吉普,
		四驱车,
		轿车,
		蹦蹦,
		摩艇,
		无人机,
		公交,
		五菱,
		库佩,
		游艇,
		NIVA,
		越野摩托,
		KILLTRUCK,
		TUK,
		跑车,
		罗尼,
		摩托,
		SCOOTER,
		SMOBILE,
		皮卡,
		AIRCRAFT,
		装甲车,
		自行车,
		Helicopter,
		三轮,

		死亡盒子,
		空投箱子,
		超级空投,
		小空投箱,


		
		AKM_手持,
		AUG_手持,
		AWM_手持,
		S686_手持,
		BerylM762_手持,
		野牛冲锋枪_手持,
		撬棍_手持,
		十字弩_手持,
		沙漠之鹰_手持,
		DBS_手持,
		DP28_手持,
		M416_手持,
		SLR_手持,
		P18C_手持,
		G36C_手持,
		Groza_手持,
		Kar98k_手持,
		Mk12_手持,
		K2_手持,
		AMR_手持,
		M16A4_手持,
		P1911_手持,
		M249_手持,
		M24_手持,
		P92_手持,
		砍刀_手持,
		QBU_手持,
		MG3_手持,
		Mini14_手持,
		Mk14_手持,
		Mk47Mutant_手持,
		MP5K_手持,
		R1895_手持,
		莫辛纳甘_手持,
		P90_手持,
		平底锅_手持,
		铁拳火箭筒_手持,
		QBZ_手持,
		R45_手持,
		S12K_手持,
		霰弹手喷_手持,
		SCARL_手持,
		镰刀_手持,
		SKS_手持,
		汤姆逊_手持,
		UMP9_手持,
		MicroUzi_手持,
		Vector_手持,
		VSS_手持,
		蝎式冲锋枪_手持,
		Win94_手持,
		S1897_手持,
		信号枪_手持,
		C4_手持,
		燃烧弹_手持,
		手榴弹_手持,
		苹果_手持,





	}EItemType, * PEItemType;

	typedef struct EntityNameIDTypeMap
	{
		EntityType Type;
		EItemType ItemType;
		ImColor Color;
		const char* Name;

		EntityNameIDTypeMap(EntityType type, const char* name) :Type(type), Color(NULL), Name(name) {}

		EntityNameIDTypeMap(EntityType type, ImColor color, const char* name) :Type(type), Color(color), Name(name) {}


		EntityNameIDTypeMap(EntityType type, ImColor color, const char* name, EItemType itemtype) :Type(type), Color(color), Name(name), ItemType(itemtype) {}

		EntityNameIDTypeMap() :Type(EntityType::EntityTypeUnknown), Color(NULL), Name(nullptr) {}



	}*PEntityNameIDTypeMap;

	void InitNameTypeMap();
	ImVec4 GetTeamColor(DWORD TeamNumber);
	inline std::unordered_map<ULONG, EntityNameIDTypeMap> EntityIDTypeMap = std::unordered_map<ULONG, EntityNameIDTypeMap>();
	inline std::string Mapname;
	namespace DrawOverlay
	{
		inline vector<FVector> ItemList;
		
	}
}

struct Player
{
	uint64_t pActor;
	uint64_t RootComponent;
	uint64_t ActorRootComp;
	uint64_t Mesh;
	uint64_t BoneArray;
	uint64_t PlayerState;
	uint64_t PlayerVehicleComponent;
	ImVec4 TeamColor;
	int Audience;
	int Teamid;
	int Health;
	int Kill;


	wstring Name;
};
struct 盒子信息
{
	string 名称;
	ImColor 颜色;
};
struct Actor
{
	uint64_t pActor;
	uint64_t RootComponent;
	FVector Location;
	string Name;
	int 物品所在组;
	Game::EntityType Type;
	Game::EItemType 要区分的物品类型;

	ImColor Color;
};

struct PackgeItem : public Actor
{
	uintptr_t DroppedItemGroup;
	盒子信息 info[100];
};

struct Item : public Actor
{
	
};

struct vehicle : public Actor
{
	
};

class EngineThread
{
public:
	int ActorCount;
	std::vector<Player> 集_玩家数组;
	std::vector<Item> 集_物品数组;
	std::vector<Item> 集_地面物品数组;
	std::vector<PackgeItem> 集_盒子数组;

	std::vector<vehicle> 集_载具数组;

	std::vector<Actor> 调试数组;
	bool Attath();

	bool GameData();
	bool CacheData();
	

public:
	std::vector<Actor> 调试数组缓存;

	std::vector<Player> 集_玩家数组缓存;
	std::vector<Item> 集_物品数组缓存;
	std::vector<Item> 集_地面物品数组缓存;
	std::vector<PackgeItem> 集_盒子数组緩存;

	std::vector<vehicle> 集_载具数组缓存;
};

namespace G { inline auto engine = std::make_unique<EngineThread>(); }
