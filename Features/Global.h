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

		int 新窗口X;
		int 新窗口Y;
		int 新窗口W;
		int 新窗口H;
		bool 串流模式;

		int 进程PID = 0;
		bool GameBase;

	}GameData;
	struct _KeyBind
	{
		bool isAim;
		bool 战斗模式;
	}KeyBind;

	struct _Aim
	{
		bool 锁定;

		FVector 自瞄坐标{};
		DWORD64 自瞄地址 = 0;
		float 屏幕当前 = 0;
		int 自瞄血量 = 0;

	}Aim;



	struct _Menu
	{
	public:
		bool 菜单开关 = true;
		bool 透视开关;
		bool FOV显示;
		bool 队友显示 = true;
		bool 地图雷达 = false;
		bool 玩家方框 = true;
		bool 玩家骨骼 = true;
		bool 玩家射线 = true;
		bool 玩家血条 = true;
		bool 玩家信息 = true;
		float 骨骼粗细 = 1;

		bool 可视判断;
		bool 自瞄器连接状态;
		int KMBOX端口号 = 6;
		char 控制器波特率[128] = "115200";
		int 自瞄按键 = 5;
		int 自瞄子按键 = VK_LSHIFT;
		bool 热键合并 = false;
		int 自瞄位置 = 8;
		float 自瞄FOV = 80.f;
		float 自瞄速度 = 4.0f;
		float 自瞄帧数 = 60.0f;
		float 自瞄X速 = 10.0f;
		float 自瞄Y速 = 12.0f;

		int 扳机按键 = 6;
		float 扳机延迟 = 10.0f;
		
		int 分组切换键 = VK_DELETE;
		int 物透开关热键 = VK_NUMPAD7;
		bool 物透开关 = false;

		char 新窗口X_[128] = "2560";
		char 新窗口Y_[128] = "0";
		char 新窗口W_[128] = "2560";
		char 新窗口H_[128] = "1440";

		int 刷新数据按键 = VK_F12;

		int 自瞄类型 = 0;
		int window_menu_button_position = 0;
		int 自瞄部位列表索引 = 0;
		ImColor 可视颜色 = ImColor(0, 255,0);
		ImColor 不可视颜色 = ImColor(255, 0, 0);
		ImColor 方框颜色 = ImColor(255, 0, 0);
		ImColor 骨骼颜色 = ImColor(255, 0, 0);
		ImColor 名字颜色 = ImColor(255, 0, 0);
		ImColor 总体颜色 = ImColor(255, 0, 0);

		char 可用端口号[30][20] = {};
		int 端口索引值 = 0;
		const char* COM选择项;

		bool 无后座;
		bool 快速开枪;

		char 当前物品组 = 'A';//当前物品组
		const char* items[5] = {"A","B","C","D","E"};    // 下拉框的选项
		std::array<ItemGrounp, 128> itemgrounp;
		std::vector<int> groupA; // A组物品
		std::vector<int> groupB; // B组物品
		std::vector<int> groupC; // C组物品
		std::vector<int> groupD; // D组物品
		std::vector<int> groupE; // E组物品
		std::vector<std::string> ItemsNames = {
			// 根据 EntityNameIDMap 提取出的名称
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
			u8"M416", // 注意这里有重复项
			u8"QBU8",
			u8"M16A4",
			u8"QB95",
			u8"Groza",
			u8"SLR",
			u8"mxng",//莫辛纳甘
			u8"pjp",//迫击炮
			u8"SCAR-L",
			u8"Kar98k",
			u8"Mini14",
			u8"xhq",//信号枪
			u8"M762",
			u8"MK47",
			u8"ACE32",
			u8"P90",
			u8"fms",//法玛斯
			u8"Vector",
			u8"yncfq",//野牛冲锋枪
			u8"UZI",
			u8"VSS",
			u8"Win94",
			u8"tmx",//汤姆逊
			u8"UMP9",
			u8"S12K",
			u8"sdsp",//霰弹手喷
			u8"MP5K",
			u8"AMR",
			u8"P1911",
			u8"M79",
			u8"P92",
			u8"MG3",
			u8"急救包",
			u8"医疗箱",
			u8"止疼",
			u8"饮料",
			u8"售货级",
			u8"肾上腺素",
			u8"绷带",


			u8"二倍镜",
			u8"三倍镜",
			u8"四倍镜",
			u8"六倍镜",
			u8"八倍镜",
			u8"十五倍镜",
			u8"垂直",
			u8"全息",
			u8"红点",
			u8"枪托",
			u8"枪消",
			u8"普扩",
			u8"枪补",
			u8"托腮",
			u8"狙扩",
			u8"狙消",
			u8"狙补",
			u8"快扩",

			u8"吉利服",
			u8"二头盔",
			u8"三头盔",
			u8"一背包",
			u8"二背包",
			u8"三背包",
			u8"一级甲",
			u8"二级甲",
			u8"三级甲",
			u8"呼救器",

			u8"手雷",
			u8"C4炸弹",
			u8"烟雾弹",
			u8"篮圈手雷",
			u8"黏土炸弹",

		};

		bool 调试数据模式;

		bool 雷达;
		float RadarRange = 150;//雷达边框大小
		float RadarPointSizeProportion = 1.f; //雷达远点
		bool ShowRadarCrossLine = true;//显示雷达10字线
		ImColor RadarCrossLineColor = ImColor(220, 220, 220, 255);//10字线颜色
		// 0: circle 1: arrow 2: circle with arrow
		int RadarType = 2; // 雷达样式
		float Proportion = 220; //缩放比例
		float RadarX;
		float RadarY;


		bool Debug;//调试类名
	}Menu;

	struct _Color
	{
	public:
		ImColor 载具 = ImGui::HexToImVec4("b0adac", 255);
		ImColor 枪械 = ImGui::HexToImVec4("ff795e", 255);
		ImColor 配件 = ImGui::HexToImVec4("1640D6", 255);
		ImColor 防具 = ImGui::HexToImVec4("860A35", 255);
		ImColor 药品 = ImGui::HexToImVec4("9FBB73", 255);
		ImColor 投掷 = ImGui::HexToImVec4("D0A2F7", 255);
		ImColor 空投盒子 = ImGui::HexToImVec4("AF2655", 255);

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



struct _分散
{
	VMMDLL_SCATTER_HANDLE LastVehiclePawn;
	VMMDLL_SCATTER_HANDLE 本人分散;
	VMMDLL_SCATTER_HANDLE 雷达分散;

	VMMDLL_SCATTER_HANDLE 结构临时分散;
	VMMDLL_SCATTER_HANDLE 结构分散;
	VMMDLL_SCATTER_HANDLE ScatterDebug;

	VMMDLL_SCATTER_HANDLE 载具分散;
	VMMDLL_SCATTER_HANDLE 物品分散;
	VMMDLL_SCATTER_HANDLE 盒子分散;
	VMMDLL_SCATTER_HANDLE 地面物品分散;
	VMMDLL_SCATTER_HANDLE 怪物分散;
}inline 分散;




struct _Data
{
	bool 游戏状态 = false;
	bool 游戏数据 = false;
	uintptr_t ShieldPtr;//解密指针
	uintptr_t GNames;//需要解密

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
	ULONG 地图判断;
	DWORD 地图X;
	DWORD 地图Y;
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
	int 观战人数;

}inline Local;

struct player_bone
{
public:

	FVector 头部, 颈部, 骨盆, 左肩, 左肘, 左手, 右肩, 右肘, 右手,
		左臀, 左膝, 左脚, 右臀, 右膝, 右脚;
	bool 是否倒地;
	player_bone(
		bool _是否倒地, FVector _头部, FVector _颈部, FVector _骨盆, FVector _左肩,
		FVector _左肘, FVector _左手, FVector _右肩, FVector _右肘,
		FVector _右手, FVector _左臀, FVector _左膝, FVector _左脚,
		FVector _右臀, FVector _右膝, FVector _右脚) {
		this->是否倒地 = _是否倒地;
		this->头部 = _头部; this->颈部 = _颈部; this->骨盆 = _骨盆; this->左肩 = _左肩;
		this->左肘 = _左肘; this->左手 = _左手; this->右肩 = _右肩; this->右肘 = _右肘;
		this->右手 = _右手; this->左臀 = _左臀; this->左膝 = _左膝; this->左脚 = _左脚;
		this->右臀 = _右臀; this->右膝 = _右膝; this->右脚 = _右脚;
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
	bool 是否倒地;
	int Audience;
	int Teamid;
	float Health;
	float MaxHealth;
	FVector 自瞄坐标;
	float 敌人朝向;
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

