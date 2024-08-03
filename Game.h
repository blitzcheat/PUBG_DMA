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
		ǹе,
		���,
		����,
		ҩƷ,
		Ͷ��,
		ProGrenade,
		�ؾ�,
		��Ͷ,
		����,
		����,
		��Ϸ��
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
		Ī���ɸ�,
		�Ȼ���,
		SCARL,
		Kar98k,
		Mini14,
		�ź�ǹ,
		M762,
		MK47,
		ACE32,
		P90,
		����˹,
		Vector,
		Ұţ���ǹ,
		UZI,
		VSS,
		Win94,
		��ķѷ,
		UMP9,
		S12K,
		��������,
		MP5K,
		AMR,
		P1911,
		M79,
		P92,
		MG3,
		JS9,

		���Ȱ�,
		ҽ����,
		ֹ��,
		����,
		�ۻ���,
		��������,
		����,


		������,
		������,
		�ı���,
		������,
		�˱���,
		ʮ�屶��,
		��ֱ,
		ȫϢ,
		���,
		ǹ��,
		ǹ��,
		����,
		ǹ��,
		����,
		����,
		����,
		�Ѳ�,
		����,

		������,
		��ͷ��,
		��ͷ��,
		һ����,
		������,
		������,
		һ����,
		������,
		������,
		������,
		//����Կ��,

		����,
		C4ը��,
		����,
		��Ȧ����,
		���ը��,

		���˻����,
		����,
		������,
		�γ�,
		�ı�,
		Ħͧ,
		���˻�,
		����,
		����,
		����,
		��ͧ,
		NIVA,
		ԽҰĦ��,
		KILLTRUCK,
		TUK,
		�ܳ�,
		����,
		Ħ��,
		SCOOTER,
		SMOBILE,
		Ƥ��,
		AIRCRAFT,
		װ�׳�,
		���г�,
		Helicopter,
		����,

		��������,
		��Ͷ����,
		������Ͷ,
		С��Ͷ��,


		
		AKM_�ֳ�,
		AUG_�ֳ�,
		AWM_�ֳ�,
		S686_�ֳ�,
		BerylM762_�ֳ�,
		Ұţ���ǹ_�ֳ�,
		�˹�_�ֳ�,
		ʮ����_�ֳ�,
		ɳĮ֮ӥ_�ֳ�,
		DBS_�ֳ�,
		DP28_�ֳ�,
		M416_�ֳ�,
		SLR_�ֳ�,
		P18C_�ֳ�,
		G36C_�ֳ�,
		Groza_�ֳ�,
		Kar98k_�ֳ�,
		Mk12_�ֳ�,
		K2_�ֳ�,
		AMR_�ֳ�,
		M16A4_�ֳ�,
		P1911_�ֳ�,
		M249_�ֳ�,
		M24_�ֳ�,
		P92_�ֳ�,
		����_�ֳ�,
		QBU_�ֳ�,
		MG3_�ֳ�,
		Mini14_�ֳ�,
		Mk14_�ֳ�,
		Mk47Mutant_�ֳ�,
		MP5K_�ֳ�,
		R1895_�ֳ�,
		Ī���ɸ�_�ֳ�,
		P90_�ֳ�,
		ƽ�׹�_�ֳ�,
		��ȭ���Ͳ_�ֳ�,
		QBZ_�ֳ�,
		R45_�ֳ�,
		S12K_�ֳ�,
		��������_�ֳ�,
		SCARL_�ֳ�,
		����_�ֳ�,
		SKS_�ֳ�,
		��ķѷ_�ֳ�,
		UMP9_�ֳ�,
		MicroUzi_�ֳ�,
		Vector_�ֳ�,
		VSS_�ֳ�,
		Ыʽ���ǹ_�ֳ�,
		Win94_�ֳ�,
		S1897_�ֳ�,
		�ź�ǹ_�ֳ�,
		C4_�ֳ�,
		ȼ�յ�_�ֳ�,
		����_�ֳ�,
		ƻ��_�ֳ�,





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
struct ������Ϣ
{
	string ����;
	ImColor ��ɫ;
};
struct Actor
{
	uint64_t pActor;
	uint64_t RootComponent;
	FVector Location;
	string Name;
	int ��Ʒ������;
	Game::EntityType Type;
	Game::EItemType Ҫ���ֵ���Ʒ����;

	ImColor Color;
};

struct PackgeItem : public Actor
{
	uintptr_t DroppedItemGroup;
	������Ϣ info[100];
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
	std::vector<Player> ��_�������;
	std::vector<Item> ��_��Ʒ����;
	std::vector<Item> ��_������Ʒ����;
	std::vector<PackgeItem> ��_��������;

	std::vector<vehicle> ��_�ؾ�����;

	std::vector<Actor> ��������;
	bool Attath();

	bool GameData();
	bool CacheData();
	

public:
	std::vector<Actor> �������黺��;

	std::vector<Player> ��_������黺��;
	std::vector<Item> ��_��Ʒ���黺��;
	std::vector<Item> ��_������Ʒ���黺��;
	std::vector<PackgeItem> ��_�������龏��;

	std::vector<vehicle> ��_�ؾ����黺��;
};

namespace G { inline auto engine = std::make_unique<EngineThread>(); }
