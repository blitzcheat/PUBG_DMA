#pragma once
#include <array>
#include "../struct.h"
class CFeature_Global
{
public:



	struct _GameData
	{
	public:


		int Width;
		int Height;
		RECT Rect;
		HWND WindowHwnd;

		int �´���X;
		int �´���Y;
		int �´���W;
		int �´���H;
		bool ����ģʽ;

		int ����PID = 0;
		bool GameBase;

	}GameData;
	struct _KeyBind
	{
		bool isAim;
		bool ս��ģʽ;
	}KeyBind;

	struct _Aim
	{
		bool ����;

		FVector ��������{};
		DWORD64 �����ַ = 0;
		float ��Ļ��ǰ = 0;
		int ����Ѫ�� = 0;

	}Aim;



	struct _Menu
	{
	public:
		bool �˵����� = true;
		bool ͸�ӿ���;
		bool FOV��ʾ;
		bool ������ʾ = true;
		bool ��ͼ�״� = false;
		bool ��ҷ��� = true;
		bool ��ҹ��� = true;
		bool ������� = true;
		bool ���Ѫ�� = true;
		bool �����Ϣ = true;
		float ������ϸ = 1;

		bool �����ж�;
		bool ����������״̬;
		int KMBOX�˿ں� = 6;
		char ������������[128] = "115200";
		int ���鰴�� = 5;
		int �����Ӱ��� = VK_LSHIFT;
		bool �ȼ��ϲ� = false;
		int ����λ�� = 8;
		float ����FOV = 80.f;
		float �����ٶ� = 4.0f;
		float ����֡�� = 60.0f;
		float ����X�� = 10.0f;
		float ����Y�� = 12.0f;

		int ������� = 6;
		float ����ӳ� = 10.0f;
		
		int �����л��� = VK_DELETE;
		int ��͸�����ȼ� = VK_NUMPAD7;
		bool ��͸���� = false;

		char �´���X_[128] = "2560";
		char �´���Y_[128] = "0";
		char �´���W_[128] = "2560";
		char �´���H_[128] = "1440";

		int ˢ�����ݰ��� = VK_F12;

		int �������� = 0;
		int window_menu_button_position = 0;
		int ���鲿λ�б����� = 0;
		ImColor ������ɫ = ImColor(0, 255,0);
		ImColor ��������ɫ = ImColor(255, 0, 0);
		ImColor ������ɫ = ImColor(255, 0, 0);
		ImColor ������ɫ = ImColor(255, 0, 0);
		ImColor ������ɫ = ImColor(255, 0, 0);
		ImColor ������ɫ = ImColor(255, 0, 0);

		char ���ö˿ں�[30][20] = {};
		int �˿�����ֵ = 0;
		const char* COMѡ����;

		bool �޺���;
		bool ���ٿ�ǹ;

		char ��ǰ��Ʒ�� = 'A';//��ǰ��Ʒ��
		const char* items[5] = {"A","B","C","D","E"};    // �������ѡ��
		std::array<ItemGrounp, 128> itemgrounp;
		std::vector<int> groupA; // A����Ʒ
		std::vector<int> groupB; // B����Ʒ
		std::vector<int> groupC; // C����Ʒ
		std::vector<int> groupD; // D����Ʒ
		std::vector<int> groupE; // E����Ʒ
		std::vector<std::string> ItemsNames = {
			// ���� EntityNameIDMap ��ȡ��������
			u8"K2",
			u8"M416",
			u8"AWM",
			u8"M24",
			u8"SKS",
			u8"G36C",
			u8"M249",
			u8"DP28",
			u8"MK12",
			u8"MK14",
			u8"AKM",
			u8"M416", // ע���������ظ���
			u8"QBU8",
			u8"M16A4",
			u8"QB95",
			u8"Groza",
			u8"SLR",
			u8"mxng",//Ī���ɸ�
			u8"pjp",//�Ȼ���
			u8"SCAR-L",
			u8"Kar98k",
			u8"Mini14",
			u8"xhq",//�ź�ǹ
			u8"M762",
			u8"MK47",
			u8"ACE32",
			u8"P90",
			u8"fms",//����˹
			u8"Vector",
			u8"yncfq",//Ұţ���ǹ
			u8"UZI",
			u8"VSS",
			u8"Win94",
			u8"tmx",//��ķѷ
			u8"UMP9",
			u8"S12K",
			u8"sdsp",//��������
			u8"MP5K",
			u8"AMR",
			u8"P1911",
			u8"M79",
			u8"P92",
			u8"MG3",
			u8"���Ȱ�",
			u8"ҽ����",
			u8"ֹ��",
			u8"����",
			u8"�ۻ���",
			u8"��������",
			u8"����",


			u8"������",
			u8"������",
			u8"�ı���",
			u8"������",
			u8"�˱���",
			u8"ʮ�屶��",
			u8"��ֱ",
			u8"ȫϢ",
			u8"���",
			u8"ǹ��",
			u8"ǹ��",
			u8"����",
			u8"ǹ��",
			u8"����",
			u8"����",
			u8"����",
			u8"�Ѳ�",
			u8"����",

			u8"������",
			u8"��ͷ��",
			u8"��ͷ��",
			u8"һ����",
			u8"������",
			u8"������",
			u8"һ����",
			u8"������",
			u8"������",
			u8"������",

			u8"����",
			u8"C4ը��",
			u8"����",
			u8"��Ȧ����",
			u8"���ը��",

		};

		bool ��������ģʽ;

		bool �״�;
		float RadarRange = 150;//�״�߿��С
		float RadarPointSizeProportion = 1.f; //�״�Զ��
		bool ShowRadarCrossLine = true;//��ʾ�״�10����
		ImColor RadarCrossLineColor = ImColor(220, 220, 220, 255);//10������ɫ
		// 0: circle 1: arrow 2: circle with arrow
		int RadarType = 2; // �״���ʽ
		float Proportion = 220; //���ű���
		float RadarX;
		float RadarY;


		bool Debug;//��������
	}Menu;

	struct _Color
	{
	public:
		ImColor �ؾ� = ImGui::HexToImVec4("b0adac", 255);
		ImColor ǹе = ImGui::HexToImVec4("ff795e", 255);
		ImColor ��� = ImGui::HexToImVec4("1640D6", 255);
		ImColor ���� = ImGui::HexToImVec4("860A35", 255);
		ImColor ҩƷ = ImGui::HexToImVec4("9FBB73", 255);
		ImColor Ͷ�� = ImGui::HexToImVec4("D0A2F7", 255);
		ImColor ��Ͷ���� = ImGui::HexToImVec4("AF2655", 255);

	}Color;

	struct _MenuE
	{
	public:
		bool Item1;
		bool Item2;
		bool Item3;
		bool Item4;
		bool Item5;
		bool Item6;
		bool Item7;
		bool Item8;
		bool Item9;
		bool Item10;
		bool Item11;
		bool Item12;
		bool Item13;
		bool Item14;
		bool Item15;
		bool Item16;
		bool Item17;
		bool Item18;
		bool Item19;
		bool Item20;
		bool Item21;
		bool Item22;
		bool Item23;
		bool Item24;
		bool Item25;
		bool Item26;
		bool Item27;
		bool Item28;
		bool Item29;
		bool Item30;


		bool Mobs1;
		bool Mobs2;
		bool Mobs3;
		bool Mobs4;
		bool Mobs5;
		bool Mobs6;
		bool Mobs7;
		bool Mobs8;
		bool Mobs9;
		bool Mobs10;
		bool Mobs11;
		bool Mobs12;
		bool Mobs13;
		bool Mobs14;
		bool Mobs15;
		bool Mobs16;
		bool Mobs17;
		bool Mobs18;
		bool Mobs19;
		bool Mobs20;
		bool Mobs21;
		bool Mobs22;
		bool Mobs23;
		bool Mobs24;
		bool Mobs25;
		bool Mobs26;
		bool Mobs27;
		bool Mobs28;
		bool Mobs29;
		bool Mobs30;

		bool car1;
		bool car2;
		bool car3;
		bool car4;
		bool car5;
		bool car6;
		bool car7;
		bool car8;
		bool car9;
		bool car10;
		bool car11;
		bool car12;
		bool car13;
		bool car14;
		bool car15;
		bool car16;
		bool car17;
		bool car18;
		bool car19;
		bool car20;
		bool car21;
		bool car22;
		bool car23;
		bool car24;
		bool car25;


	}MenuE;
};



struct _��ɢ
{
	VMMDLL_SCATTER_HANDLE LastVehiclePawn;
	VMMDLL_SCATTER_HANDLE ���˷�ɢ;
	VMMDLL_SCATTER_HANDLE �״��ɢ;

	VMMDLL_SCATTER_HANDLE �ṹ��ʱ��ɢ;
	VMMDLL_SCATTER_HANDLE �ṹ��ɢ;
	VMMDLL_SCATTER_HANDLE ScatterDebug;

	VMMDLL_SCATTER_HANDLE �ؾ߷�ɢ;
	VMMDLL_SCATTER_HANDLE ��Ʒ��ɢ;
	VMMDLL_SCATTER_HANDLE ���ӷ�ɢ;
	VMMDLL_SCATTER_HANDLE ������Ʒ��ɢ;
	VMMDLL_SCATTER_HANDLE �����ɢ;
}inline ��ɢ;




struct _Data
{
	bool ��Ϸ״̬ = false;
	bool ��Ϸ���� = false;
	uintptr_t ShieldPtr;//����ָ��
	uintptr_t GNames;//��Ҫ����

	uintptr_t UWorld;
	
	uintptr_t ULevel;

	uintptr_t Actors;

	uintptr_t GameInstance;



}inline Data;

struct _Local
{
	uintptr_t PlayerController;
	uintptr_t PlayerCameraManager;
	uintptr_t AcknowledgedPawn;
	FLoaclWeaponData LoaclWeaponData;
	uintptr_t Mesh;
	uintptr_t AnimScript;
	uintptr_t TslBaseHUD;


	FVector ControlRotation;
	FVector RecoilADSRotation;
	ULONG ��ͼ�ж�;
	DWORD ��ͼX;
	DWORD ��ͼY;
	bool bWorldMap;
	bool bRadarExtended;
	float WorldMapZoomFactor;
	FVector2 WorldMapPosition;

	float LeanLeft;
	float LeanRight;
	float CameraFov;
	float Tangent;
	FVector CameraPos;
	FVector CameraRotPos;
	FVector AxisX, AxisY, AxisZ;
	int Teamid;
	int ��ս����;

}inline Local;

struct player_bone
{
public:

	FVector ͷ��, ����, ����, ���, ����, ����, �Ҽ�, ����, ����,
		����, ��ϥ, ���, ����, ��ϥ, �ҽ�;
	bool �Ƿ񵹵�;
	player_bone(
		bool _�Ƿ񵹵�, FVector _ͷ��, FVector _����, FVector _����, FVector _���,
		FVector _����, FVector _����, FVector _�Ҽ�, FVector _����,
		FVector _����, FVector _����, FVector _��ϥ, FVector _���,
		FVector _����, FVector _��ϥ, FVector _�ҽ�) {
		this->�Ƿ񵹵� = _�Ƿ񵹵�;
		this->ͷ�� = _ͷ��; this->���� = _����; this->���� = _����; this->��� = _���;
		this->���� = _����; this->���� = _����; this->�Ҽ� = _�Ҽ�; this->���� = _����;
		this->���� = _����; this->���� = _����; this->��ϥ = _��ϥ; this->��� = _���;
		this->���� = _����; this->��ϥ = _��ϥ; this->�ҽ� = _�ҽ�;
	}
};

struct player_data
{
	uint64_t pActor;
	FVector Location;
	uint64_t Mesh;
	uint64_t BoneArry;
	uint64_t PlayerState;
	ImVec4 TeamColor;
	bool �Ƿ񵹵�;
	int Audience;
	int Teamid;
	float Health;
	float MaxHealth;
	FVector ��������;
	float ���˳���;
	int Kill;
	FVector PlayerVelocity;
	FVector PlayerVelocityUp;

	FVector RootLoc;
	FVector HeadLoc;
	wstring Name;
};

struct Item_data
{
	uint64_t Actor;
	FVector Location;
	string Name;
	ImColor Color;
};




namespace F { inline CFeature_Global Global; }

