#include "Game.h"

#include "AimBot.hpp"
#include "CThread.h"

using namespace CThread;
bool EngineThread::Attath()
{


	//static auto key_sig = (BYTE*)"\x48\x8B\x44\x24\x00\x3B\x00\x00\x0F\x8D\x00\x00\x00\x00\x48\x83\x3D\x00\x00\x00\x00\x00\x00\x8B";
	//static auto key_mask = "xxxx?x??xx????xxx????x?x";
	////48 8B 44 24 ?? 3B ?? ?? 0F 8D ?? ?? ?? ?? 48 83 3D ?? ?? ?? ?? 00 ?? 8B
	//uint64_t Key = G::Mem.FindPatternExREg(key_sig, key_mask, 0x100000000);
	//printf("Key%p\n", Key);
	//先删掉判断武器

	std::thread(CThread::Cache线程).detach();
	std::thread(CThread::获取数据).detach();
	std::thread(CThread::GetPlayerWeaponData).detach();
	std::thread(CThread::GetPlayerData).detach();
	std::thread(CThread::RadarData).detach();
	//std::thread(CThread::取按键信息).detach();
	AimControl::Attach();
	return true;

}

bool EngineThread::GameData() {
	auto start = std::chrono::high_resolution_clock::now();

	std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator IDTypeMapIt = std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator();
	auto 临时玩家 = Player();
	auto 临时物品 = Item();
	auto 地面物品 = Item();
	auto 盒子物品 = PackgeItem();
	auto 临时载具 = vehicle();
	auto 临时调试数组 = Actor();
	//printf("游戏状态%d 游戏数据 %d\n", Data.游戏状态, Data.游戏数据);
	
	auto Count = G::Mem.Read<int>(Data.Actors + 8);
	this->ActorCount = Count;
	//printf("%d\n", Count);
	if (Count > 1 && Count < 9000) {
		auto Actors = G::Mem.Read<uint64_t>(Data.Actors);

		for (auto i = 0; i < Count; i++) {
			auto pActor = G::Mem.Read<uint64_t>(Actors + i * 8); 
			if (pActor <= 65536) continue;
			auto ObjectID = SDK::DecryptID(pActor); if (ObjectID <= 0) continue;
			if (pActor == Local.AcknowledgedPawn) continue;//判断是否本人



			if (F::Global.Menu.Debug)
			{
					

				if (SDK::GetNames(ObjectID) == E("DroppedItem"))//DroppedItem
				{
					//auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::RootComponent));
					//if (RootComponent <= 65536) continue;
					ULONG_PTR PackageItemPtr = SDK::DecryptCall(G::Mem.Read<ULONG_PTR>(pActor + offsets::DroppedItem));
					if (PackageItemPtr <= 65536) continue;
					ULONG PackageItemObjID = G::Mem.Read<ULONG>(G::Mem.Read<ULONG_PTR>(PackageItemPtr + offsets::物品一) + offsets::物品二);
					//临时调试数组.RootComponent = RootComponent;
					临时调试数组.pActor = pActor;
					临时调试数组.Name = SDK::GetNames(PackageItemObjID);
					调试数组缓存.push_back(临时调试数组);
				}
				else
				{
					auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
					if (RootComponent <= 65536) continue;
					临时调试数组.RootComponent = RootComponent;
					临时调试数组.pActor = pActor;
					临时调试数组.Name = SDK::GetNames(ObjectID);
					调试数组缓存.push_back(临时调试数组);
				}

			}
			if (F::Global.Menu.Debug) continue;

			IDTypeMapIt = Game::EntityIDTypeMap.find(ObjectID);
			if (IDTypeMapIt == Game::EntityIDTypeMap.end()) continue;


			if (IDTypeMapIt->second.Type == Game::EntityType::EntityTypePlayer)//玩家
			{
				auto Mesh = G::Mem.Read<uint64_t>(pActor + offsets::Mesh); if (Mesh <= 65536) continue;

				auto Teamid = G::Mem.Read<int>(pActor + offsets::TeamNumber);
				if (Teamid >= 100000) { Teamid -= 100000; }
				if (Teamid == Local.Teamid && !F::Global.Menu.队友显示)continue;
				auto PlayerState = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::PlayerState));
					
				auto pName = G::Mem.Read<uint64_t>(pActor + offsets::Playname);
				/*ULONG_PTR PlayerVehicleComponent = G::Mem.Read<ULONG_PTR>(pActor + offsets::VehicleRiderComponent);*/
				//printf("PlayerVehicleComponent %p\n", PlayerVehicleComponent);

				//auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::RootComponent));
				//临时玩家.RootComponent = RootComponent;

				临时玩家.pActor = pActor;
				临时玩家.ActorRootComp = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
				临时玩家.Mesh = Mesh;
				临时玩家.Teamid = Teamid;
				临时玩家.PlayerState = PlayerState;
				std::string str = SDK::GetNames(ObjectID);
				std::wstring wstr(str.length(), L'\0\0');
				std::copy(str.begin(), str.end(), wstr.begin());

				//临时玩家.PlayerVehicleComponent = PlayerVehicleComponent;
				临时玩家.Name = SDK::GetPlayName(pName);
				临时玩家.TeamColor = Game::GetTeamColor(IDTypeMapIt->second.Name == "Bot" ? 0 : Teamid);

				this->集_玩家数组缓存.push_back(Player(临时玩家));
			}
			else if (IDTypeMapIt->second.Type == Game::EntityType::EntityTypeItem)//全物品
			{
				//printf("Item %s\n",SDK::GetNames(ObjectID).c_str());
				//if (F::Global.Menu.物透开关) continue;
				ULONG_PTR PackageItemPtr = SDK::DecryptCall(G::Mem.Read<ULONG_PTR>(pActor + offsets::DroppedItem));
				if (!PackageItemPtr) continue;
				ULONG PackageItemObjID = G::Mem.Read<ULONG>(G::Mem.Read<ULONG_PTR>(PackageItemPtr + offsets::物品一) + offsets::物品二);

				IDTypeMapIt = Game::EntityIDTypeMap.find(PackageItemObjID);

				if (IDTypeMapIt == Game::EntityIDTypeMap.end()) continue;

				auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
				if (!RootComponent) continue;
				// printf("pActor %p RootComponent %p\n", pActor, RootComponent);
				临时物品.pActor = pActor;
				临时物品.RootComponent = RootComponent;
				临时物品.Name = IDTypeMapIt->second.Name;
				临时物品.Type = IDTypeMapIt->second.Type;
				临时物品.要区分的物品类型 = Game::EItemType::UnKnown;
				临时物品.要区分的物品类型 = IDTypeMapIt->second.ItemType;
				//临时物品.Color = IDTypeMapIt->second.Color;
				{
					if (IDTypeMapIt->second.Type == Game::EntityType::载具)
					{
						临时物品.Color = F::Global.Color.载具;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::枪械)
					{
						临时物品.Color = F::Global.Color.枪械;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::配件)
					{
						临时物品.Color = F::Global.Color.配件;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::防具)
					{
						临时物品.Color = F::Global.Color.防具;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::药品)
					{
						临时物品.Color = F::Global.Color.药品;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::投掷)
					{
						临时物品.Color = F::Global.Color.投掷;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::空投)
					{
						临时物品.Color = F::Global.Color.空投盒子;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::空投)
					{
						临时物品.Color = F::Global.Color.空投盒子;
					}
				}
				this->集_物品数组缓存.push_back(Item(临时物品));
			}
			else if (IDTypeMapIt->second.Type == Game::EntityType::EntityTypeItemGroup)
			{
				//if (F::Global.Menu.物透开关) continue;

				ULONG_PTR DroppedItemArray = G::Mem.Read<ULONG_PTR>(pActor + offsets::DroppedItemGroup);

				ULONG DroppedItemCount = G::Mem.Read<ULONG>(pActor + offsets::DroppedItemGroup_Count); if (DroppedItemCount < 0 || DroppedItemCount > 100) continue;

				for (ULONG_PTR i = 0; i < DroppedItemCount; i++)
				{
					ULONG_PTR DroppedItemPtr = G::Mem.Read<ULONG_PTR>(DroppedItemArray + i * 0x10);
					if (!DroppedItemPtr) continue;
					ULONG_PTR DroppedItemObj = G::Mem.Read<ULONG_PTR>(DroppedItemPtr + offsets::DroppedItemGroup_UItem);
					if (!DroppedItemObj) continue;
					ULONG DroppedItemObjID = G::Mem.Read<ULONG>(G::Mem.Read<ULONG_PTR>(DroppedItemObj + offsets::物品一) + offsets::物品二); if (!DroppedItemObjID || DroppedItemObjID > 1000000) { continue; }
					IDTypeMapIt = Game::EntityIDTypeMap.find(DroppedItemObjID);

					if (IDTypeMapIt == Game::EntityIDTypeMap.end()) continue;

					地面物品.pActor = DroppedItemPtr;
					地面物品.RootComponent = DroppedItemPtr;
					地面物品.Name = IDTypeMapIt->second.Name;
					地面物品.Type = IDTypeMapIt->second.Type;
					地面物品.要区分的物品类型 = Game::EItemType::UnKnown;
					地面物品.要区分的物品类型 = IDTypeMapIt->second.ItemType;
					//地面物品.Color = IDTypeMapIt->second.Color;
					{
						if (IDTypeMapIt->second.Type == Game::EntityType::载具)
						{
							地面物品.Color = F::Global.Color.载具;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::枪械)
						{
							地面物品.Color = F::Global.Color.枪械;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::配件)
						{
							地面物品.Color = F::Global.Color.配件;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::防具)
						{
							地面物品.Color = F::Global.Color.防具;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::药品)
						{
							地面物品.Color = F::Global.Color.药品;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::投掷)
						{
							地面物品.Color = F::Global.Color.投掷;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::空投)
						{
							地面物品.Color = F::Global.Color.空投盒子;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::空投)
						{
							地面物品.Color = F::Global.Color.空投盒子;
						}
					}

					this->集_地面物品数组缓存.push_back(Item(地面物品));
				}
			}
			else if (IDTypeMapIt->second.Type == Game::EntityType::载具)
			{
				auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
				if (!RootComponent) continue;
				临时载具.pActor = pActor;
				临时载具.RootComponent = RootComponent;
				临时载具.Name = IDTypeMapIt->second.Name;
				临时载具.Type = IDTypeMapIt->second.Type;

				临时载具.要区分的物品类型 = IDTypeMapIt->second.ItemType;
				//printf("有载具 %s\n", IDTypeMapIt->second.Name);
				this->集_载具数组缓存.push_back(vehicle(临时载具));

			}
			//else if (IDTypeMapIt->second.Type == Game::EntityType::盒子)
			//{
			//	continue;
			//	uintptr_t 局_物品数组 = G::Mem.Read<uintptr_t>(pActor + offsets::Packge - 8);
			//	int 局_物品数量 = G::Mem.Read<int>(pActor + offsets::Packge);

			//	if (局_物品数组 <= 0 || 局_物品数量 > 30 || 局_物品数量 < 0)
			//		continue;
			//	if (F::Global.Menu.物透开关) continue;

			//	auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
			//	盒子物品.Actor = pActor;
			//	盒子物品.DroppedItemGroup = 局_物品数组;// G::Mem.Read<uintptr_t>(pActor + offsets::DroppedItemGroup);
			//	盒子物品.RootComponent = RootComponent;
			//	for (size_t n = 0; n < 局_物品数量; n++)
			//	{


			//		uintptr_t ptr1 = G::Mem.Read<uintptr_t>(局_物品数组 + n * 8);
			//		if (!ptr1) continue;
			//		uint32_t PackItemObjID = G::Mem.Read<ULONG>(G::Mem.Read<ULONG_PTR>(ptr1 + offsets::物品一) + offsets::物品二);
			//		IDTypeMapIt = Game::EntityIDTypeMap.find(PackItemObjID);

			//		if (IDTypeMapIt == Game::EntityIDTypeMap.end()) continue;

			//		盒子物品.Name = IDTypeMapIt->second.Name;

			//		this->集_盒子数组緩存.push_back(PackgeItem(盒子物品));
			//	}

			//}
		}
		this->调试数组 = this->调试数组缓存;
		this->集_玩家数组 = this->集_玩家数组缓存;
		this->集_物品数组 = this->集_物品数组缓存;
		this->集_地面物品数组 = this->集_地面物品数组缓存;
		this->集_载具数组 = this->集_载具数组缓存;
		//this->集_盒子数组 = this->集_盒子数组緩存;
		this->调试数组缓存.clear();
		this->集_玩家数组缓存.clear();
		this->集_物品数组缓存.clear();
		this->集_地面物品数组缓存.clear();
		this->集_载具数组缓存.clear();
		//this->集_盒子数组緩存.clear();
			
	}
	
	
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	
	//std::cout << "使用 " << duration.count() << " 毫秒  " << "数据量:" << Count << std::endl;

	return true;
}

std::unordered_map<DWORD, ImVec4> teamColors = {
	{1, ImGui::HexToImVec4("0xAEFFDA", 255)},
	{2, ImGui::HexToImVec4("0x98F89F", 255)},
	{3, ImGui::HexToImVec4("0xD7DBA1", 255)},
	{4, ImGui::HexToImVec4("0x8FC7C5", 255)},
	{5, ImGui::HexToImVec4("0xBCC097", 255)},
	{6, ImGui::HexToImVec4("0xC497F1", 255)},
	{7, ImGui::HexToImVec4("0xE999CF", 255)},
	{8, ImGui::HexToImVec4("0xB8B49D", 255)},
	{9, ImGui::HexToImVec4("0xE9EDA2", 255)},
	{10, ImGui::HexToImVec4("0xF9A8DB", 255)},
	{11, ImGui::HexToImVec4("0x8F80E5", 255)},
	{12, ImGui::HexToImVec4("0x9DF8C6", 255)},
	{13, ImGui::HexToImVec4("0xD181D1", 255)},
	{14, ImGui::HexToImVec4("0xC0A78C", 255)},
	{15, ImGui::HexToImVec4("0xCF9B98", 255)},
	{16, ImGui::HexToImVec4("0xC2CF8C", 255)},
	{17, ImGui::HexToImVec4("0xEE8988", 255)},
	{18, ImGui::HexToImVec4("0x80BEB1", 255)},
	{19, ImGui::HexToImVec4("0xEEF181", 255)},
	{20, ImGui::HexToImVec4("0x9EF8E3", 255)},
	{21, ImGui::HexToImVec4("0xEEAAC9", 255)},
	{22, ImGui::HexToImVec4("0xCAC88E", 255)},
	{23, ImGui::HexToImVec4("0x94F1B0", 255)},
	{24, ImGui::HexToImVec4("0x88D8CC", 255)},
	{25, ImGui::HexToImVec4("0x86FC82", 255)},
	{26, ImGui::HexToImVec4("0xF08CD2", 255)},
	{27, ImGui::HexToImVec4("0x9D8090", 255)},
	{28, ImGui::HexToImVec4("0xEFBECC", 255)},
	{29, ImGui::HexToImVec4("0x9B9A8D", 255)},
	{30, ImGui::HexToImVec4("0xA68BA5", 255)},
	{31, ImGui::HexToImVec4("0x88F2FA", 255)},
	{32, ImGui::HexToImVec4("0xB7FBE4", 255)},
	{33, ImGui::HexToImVec4("0xBBDFE2", 255)},
	{34, ImGui::HexToImVec4("0xE2FFE1", 255)},
	{35, ImGui::HexToImVec4("0x96D08F", 255)},
	{36, ImGui::HexToImVec4("0x958F95", 255)},
	{37, ImGui::HexToImVec4("0xB0DF8E", 255)},
	{38, ImGui::HexToImVec4("0x82AEAB", 255)},
	{39, ImGui::HexToImVec4("0xC7DA8D", 255)},
	{40, ImGui::HexToImVec4("0xC195F5", 255)},
	{41, ImGui::HexToImVec4("0xF4E6A1", 255)},
	{42, ImGui::HexToImVec4("0xC3CFD4", 255)},
	{43, ImGui::HexToImVec4("0xA99392", 255)},
	{44, ImGui::HexToImVec4("0xC9B58E", 255)},
	{45, ImGui::HexToImVec4("0xEAE6AA", 255)},
	{46, ImGui::HexToImVec4("0xD3ACCE", 255)},
	{47, ImGui::HexToImVec4("0xFFF6F4", 255)},
	{48, ImGui::HexToImVec4("0xF495AF", 255)},
	{49, ImGui::HexToImVec4("0xE9C9F7", 255)},
	{50, ImGui::HexToImVec4("0xBFE1B3", 255)}
};

ImVec4 Game::GetTeamColor(DWORD TeamNumber) {
	DWORD teamNumber = TeamNumber % 51;
	auto it = teamColors.find(teamNumber);
	if (it != teamColors.end()) {
		return it->second;
	}
	else {
		return ImGui::HexToImVec4("0xA0F8A658", 255); // 默认颜色
	}
}

void Game::InitNameTypeMap()
{
	std::unordered_map<std::string, EntityNameIDTypeMap> EntityNameIDMap = std::unordered_map<std::string, EntityNameIDTypeMap>();

	/*判断类*/
	{
		EntityNameIDMap[("Chimera_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 1, "Chimera_Main");
		EntityNameIDMap[("Desert_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 2, "Desert_Main");
		EntityNameIDMap[("DihorOtok_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 3, "DihorOtok_Main");
		EntityNameIDMap[("Erangel_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 4, "Erangel_Main");
		EntityNameIDMap[("Range_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 5, "Range_Main");
		EntityNameIDMap[("Savage_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 6, "Savage_Main");
		EntityNameIDMap[("Summerland_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 7, "Summerland_Main");
		EntityNameIDMap[("Heaven_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 8, "Heaven_Main");
		EntityNameIDMap[("Kiki_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 9, "Kiki_Main");
		EntityNameIDMap[("Tiger_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 10, "Tiger_Main");

		EntityNameIDMap[("Baltic_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 4, "Baltic_Main");
		EntityNameIDMap[("Tutorial_Main")] = EntityNameIDTypeMap(EntityType::游戏內, 0, "Tutorial_Main");
		EntityNameIDMap[("TslLobby_Persistent_Main")] = EntityNameIDTypeMap(EntityType::大厅, 0, "TslLobby_Persistent_Main");
	}

	/*主类*/
	{
		EntityNameIDMap[("RegistedPlayer")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("AIPawn_Base_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("AIPawn_Base_Female_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("AIPawn_Base_Male_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("AIPawn_Base_Male_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Pillar_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Female_Pillar_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Male_Pillar_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Female_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Male_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Bot");
		EntityNameIDMap[("PlayerMale_A")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Player");
		EntityNameIDMap[("PlayerMale_A_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Player");
		EntityNameIDMap[("PlayerFemale_A")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Player");
		EntityNameIDMap[("PlayerFemale_A_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, 红色, "Player");
		EntityNameIDMap[("DroppedItem")] = EntityNameIDTypeMap(EntityType::EntityTypeItem, 红色, nullptr);
		EntityNameIDMap[("DroppedItemGroup")] = EntityNameIDTypeMap(EntityType::EntityTypeItemGroup, 红色, nullptr);
	}


	/*载具*/
	{
		EntityNameIDMap[("Weapon_Drone_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"无人机侦察", EItemType::无人机侦察);
		EntityNameIDMap[("Uaz_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"吉普", EItemType::吉普);
		EntityNameIDMap[("BP_ATV_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"四驱车", EItemType::四驱车);
		EntityNameIDMap[("Uaz_A_01")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"吉普", EItemType::吉普);
		EntityNameIDMap[("Uaz_B_01")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"吉普", EItemType::吉普);
		EntityNameIDMap[("Uaz_C_01")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"吉普", EItemType::吉普);
		EntityNameIDMap[("Uaz_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"吉普", EItemType::吉普);
		EntityNameIDMap[("Uaz_B_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"吉普", EItemType::吉普);
		EntityNameIDMap[("Uaz_C_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"吉普", EItemType::吉普);
		EntityNameIDMap[("Dacia_A_01")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Dacia_A_02")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Dacia_A_03")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Dacia_A_01")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Dacia_A_04")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Buggy_A_01")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_02")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_03")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_04")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_05")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_06")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("AquaRail_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩艇", EItemType::摩艇);
		EntityNameIDMap[("BP_Drone_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"无人机", EItemType::无人机);
		EntityNameIDMap[("BP_Van_A_01")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"公交", EItemType::公交);
		EntityNameIDMap[("BP_Van_A_02")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"公交", EItemType::公交);
		EntityNameIDMap[("BP_Van_A_03")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"公交", EItemType::公交);
		EntityNameIDMap[("BP_Porter_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"五菱", EItemType::五菱);
		EntityNameIDMap[("BP_CoupeRB_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"库佩", EItemType::库佩);
		EntityNameIDMap[("Buggy_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_04_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_05_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Buggy_A_06_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"蹦蹦", EItemType::蹦蹦);
		EntityNameIDMap[("Dacia_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Dacia_A_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Dacia_A_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Dacia_A_04_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Boat_PG117_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"游艇", EItemType::游艇);
		EntityNameIDMap[("PG117_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"游艇", EItemType::游艇);
		EntityNameIDMap[("BP_Niva_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_04_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_05_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_06_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Dirtbike_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"越野摩托", EItemType::越野摩托);
		EntityNameIDMap[("BP_Van_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"公交", EItemType::公交);
		EntityNameIDMap[("BP_Van_A_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"公交", EItemType::公交);
		EntityNameIDMap[("BP_Van_A_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"公交", EItemType::公交);
		EntityNameIDMap[("Dacia_A_04_v2")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("AquaRail_A_01")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩艇", EItemType::摩艇);
		EntityNameIDMap[("BP_KillTruck_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"KILLTRUCK", EItemType::KILLTRUCK);
		EntityNameIDMap[("BP_TukTukTuk_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"TUK", EItemType::TUK);
		EntityNameIDMap[("Dacia_A_03_v2_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("Dacia_A_04_v2_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"轿车", EItemType::轿车);
		EntityNameIDMap[("BP_Motorbike_04")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("AquaRail_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩艇", EItemType::摩艇);
		EntityNameIDMap[("BP_Helicopter_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"Helicopter", EItemType::Helicopter);
		EntityNameIDMap[("BP_M_Rony_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"跑车", EItemType::跑车);
		EntityNameIDMap[("BP_M_Rony_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"罗尼", EItemType::罗尼);
		EntityNameIDMap[("BP_M_Rony_A_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"罗尼", EItemType::罗尼);
		EntityNameIDMap[("BP_M_Rony_A_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"罗尼", EItemType::罗尼);
		EntityNameIDMap[("ABP_Motorbike_03")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("ABP_Motorbike_04")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("BP_Mirado_A_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"跑车", EItemType::跑车);
		EntityNameIDMap[("BP_Motorbike_04_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("BP_Motorbike_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("BP_Scooter_01_A_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"SCOOTER", EItemType::SCOOTER);
		EntityNameIDMap[("BP_Scooter_02_A_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"SCOOTER", EItemType::SCOOTER);
		EntityNameIDMap[("BP_Scooter_03_A_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"SCOOTER", EItemType::SCOOTER);
		EntityNameIDMap[("BP_Scooter_04_A_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"SCOOTER", EItemType::SCOOTER);
		EntityNameIDMap[("BP_Snowmobile_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"SMOBILE", EItemType::SMOBILE);
		EntityNameIDMap[("BP_Snowmobile_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"SMOBILE", EItemType::SMOBILE);
		EntityNameIDMap[("BP_Snowmobile_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"SMOBILE", EItemType::SMOBILE);
		EntityNameIDMap[("ABP_Motorbike_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("ABP_Motorbike_04_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("BP_Mirado_Open_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"跑车", EItemType::跑车);
		EntityNameIDMap[("BP_Mirado_Open_04_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"跑车", EItemType::跑车);
		EntityNameIDMap[("BP_TukTukTuk_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"三轮", EItemType::三轮);
		EntityNameIDMap[("BP_TukTukTuk_A_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"三轮", EItemType::三轮);
		EntityNameIDMap[("BP_TukTukTuk_A_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"三轮", EItemType::三轮);
		EntityNameIDMap[("BP_PickupTruck_A_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"皮卡", EItemType::皮卡);
		EntityNameIDMap[("BP_PickupTruck_A_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"皮卡", EItemType::皮卡);
		EntityNameIDMap[("BP_PickupTruck_A_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"皮卡", EItemType::皮卡);
		EntityNameIDMap[("BP_PickupTruck_A_04_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"皮卡", EItemType::皮卡);
		EntityNameIDMap[("BP_PickupTruck_A_05_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"皮卡", EItemType::皮卡);
		EntityNameIDMap[("BP_PickupTruck_B_01_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"皮卡", EItemType::皮卡);
		EntityNameIDMap[("BP_PickupTruck_B_02_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"皮卡", EItemType::皮卡);
		EntityNameIDMap[("BP_PickupTruck_B_03_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"皮卡", EItemType::皮卡);
		EntityNameIDMap[("BP_PickupTruck_B_04_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"皮卡", EItemType::皮卡);
		EntityNameIDMap[("BP_Motorbike_04_Desert")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("ABP_Motorbike_04_Sidecar")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("BP_Motorbike_04_Desert_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"摩托", EItemType::摩托);
		EntityNameIDMap[("BP_DummyTransportAircraft_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"AIRCRAFT", EItemType::AIRCRAFT);
		EntityNameIDMap[("BP_BRDM_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"装甲车", EItemType::装甲车);
		EntityNameIDMap[("Item_Mountainbike_C")] = EntityNameIDTypeMap(EntityType::载具, 白色, u8"自行车", EItemType::自行车);


		//EntityNameIDMap[("Dacia_A_01_v2")] = EntityNameIDTypeMap(EntityType::载具, 白色,u8"轿车");
		//EntityNameIDMap[("BP_PonyCoupe_C")] = EntityNameIDTypeMap(EntityType::载具, 白色,u8"AE86");
		//EntityNameIDMap[("BP_LootTruck_C")] = EntityNameIDTypeMap(EntityType::载具, 白色,u8"物资车");
		//EntityNameIDMap[("BP_Motorglider_C")] = EntityNameIDTypeMap(EntityType::载具, 白色,u8"滑翔机");
		//EntityNameIDMap[("BP_DummyTransportAircraft_C")] = EntityNameIDTypeMap(EntityType::载具, 白色,u8"AIRCRAFT");
		//EntityNameIDMap[("BP_Motorbike_04_SideCar_Desert")] = EntityNameIDTypeMap(EntityType::载具, 白色,u8"摩托");
		//EntityNameIDMap[("BP_Motorbike_04_SideCar_Desert_C")] = EntityNameIDTypeMap(EntityType::载具, 白色,u8"摩托");
	}

	/* 手持武器 */
	{
		EntityNameIDMap[("WeapLunchmeatsAK47_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"AKM", EItemType::AKM_手持);
		EntityNameIDMap[("WeapAK47_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"AKM", EItemType::AKM_手持);
		EntityNameIDMap[("WeapAUG_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"AUG", EItemType::AUG_手持);
		EntityNameIDMap[("WeapAWM_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"AWM", EItemType::AWM_手持);
		EntityNameIDMap[("WeapBerreta686_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"S686", EItemType::S686_手持);
		EntityNameIDMap[("WeapBerylM762_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"BerylM762", EItemType::BerylM762_手持);
		EntityNameIDMap[("WeapBizonPP19_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"野牛冲锋枪", EItemType::野牛冲锋枪_手持);
		EntityNameIDMap[("WeapCowbar_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"撬棍", EItemType::撬棍_手持);
		EntityNameIDMap[("WeapCowbarProjectile_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"撬棍", EItemType::撬棍_手持);
		EntityNameIDMap[("WeapCrossbow_1_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"十字弩", EItemType::十字弩_手持);
		EntityNameIDMap[("WeapDesertEagle_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"沙漠之鹰", EItemType::沙漠之鹰_手持);
		EntityNameIDMap[("WeapDP12_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"DBS", EItemType::DBS_手持);
		EntityNameIDMap[("WeapDP28_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"DP-28", EItemType::DP28_手持);
		EntityNameIDMap[("WeapDuncansHK416_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"M416", EItemType::M416_手持);
		EntityNameIDMap[("WeapHK416_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"M416", EItemType::M416_手持);
		EntityNameIDMap[("WeapFNFal_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"SLR", EItemType::SLR_手持);
		EntityNameIDMap[("WeapG18_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"P18C", EItemType::P18C_手持);
		EntityNameIDMap[("WeapG36C_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"G36C", EItemType::G36C_手持);
		EntityNameIDMap[("WeapGroza_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Groza", EItemType::Groza_手持);
		EntityNameIDMap[("WeapJuliesKar98k_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Kar98k", EItemType::Kar98k_手持);
		EntityNameIDMap[("WeapKar98k_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Kar98k", EItemType::Kar98k_手持);
		EntityNameIDMap[("WeapMk12_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Mk12", EItemType::Mk12_手持);
		EntityNameIDMap[("WeapK2_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"K2", EItemType::K2_手持);
		EntityNameIDMap[("WeapL6_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"AMR", EItemType::AMR_手持);
		EntityNameIDMap[("WeapM16A4_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"M16A4", EItemType::M16A4_手持);
		EntityNameIDMap[("WeapM1911_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"P1911", EItemType::P1911_手持);
		EntityNameIDMap[("WeapM249_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"M249", EItemType::M249_手持);
		EntityNameIDMap[("WeapM24_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"M24", EItemType::M24_手持);
		EntityNameIDMap[("WeapM9_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"P92", EItemType::P92_手持);
		EntityNameIDMap[("WeapMachete_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"砍刀", EItemType::砍刀_手持);
		EntityNameIDMap[("WeapMacheteProjectile_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"砍刀", EItemType::砍刀_手持);
		EntityNameIDMap[("WeapMadsQBU88_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"QBU", EItemType::QBU_手持);
		EntityNameIDMap[("WeapMG3_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"MG3", EItemType::MG3_手持);
		EntityNameIDMap[("WeapMini14_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Mini14", EItemType::Mini14_手持);
		EntityNameIDMap[("WeapMk14_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Mk14", EItemType::Mk14_手持);
		EntityNameIDMap[("WeapMk47Mutant_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Mk47Mutant", EItemType::Mk47Mutant_手持);
		EntityNameIDMap[("WeapMP5K_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"MP5K", EItemType::MP5K_手持);
		EntityNameIDMap[("WeapNagantM1895_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"R1895", EItemType::R1895_手持);
		EntityNameIDMap[("WeapMosinNagant_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"莫辛纳甘", EItemType::莫辛纳甘_手持);
		EntityNameIDMap[("WeapP90_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"P90", EItemType::P90_手持);
		EntityNameIDMap[("WeapPan_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"平底锅", EItemType::平底锅_手持);
		EntityNameIDMap[("WeapPanProjectile_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"平底锅", EItemType::平底锅_手持);
		EntityNameIDMap[("WeapPanzerFaust100M1_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"铁拳火箭筒", EItemType::铁拳火箭筒_手持);
		EntityNameIDMap[("WeapQBU88_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"QBU", EItemType::QBU_手持);
		EntityNameIDMap[("WeapQBZ95_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"QBZ", EItemType::QBZ_手持);
		EntityNameIDMap[("WeapRhino_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"R45", EItemType::R45_手持);
		EntityNameIDMap[("WeapSaiga12_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"S12K", EItemType::S12K_手持);
		EntityNameIDMap[("WeapSawnoff_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"霰弹手喷", EItemType::霰弹手喷_手持);
		EntityNameIDMap[("WeapSCAR-L_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"SCAR-L", EItemType::SCARL_手持);
		EntityNameIDMap[("WeapSickle_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"镰刀", EItemType::镰刀_手持);
		EntityNameIDMap[("WeapSickleProjectile_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"镰刀", EItemType::镰刀_手持);
		EntityNameIDMap[("WeapSKS_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"SKS", EItemType::SKS_手持);
		EntityNameIDMap[("WeapThompson_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"汤姆逊", EItemType::汤姆逊_手持);
		EntityNameIDMap[("WeapUMP_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"UMP9", EItemType::UMP9_手持);
		EntityNameIDMap[("WeapUZI_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Micro Uzi", EItemType::MicroUzi_手持);
		EntityNameIDMap[("WeapVector_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Vector", EItemType::Vector_手持);
		EntityNameIDMap[("WeapVSS_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"VSS", EItemType::VSS_手持);
		EntityNameIDMap[("Weapvz61Skorpion_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"蝎式冲锋枪", EItemType::蝎式冲锋枪_手持);
		EntityNameIDMap[("WeapWin94_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"Win94", EItemType::Win94_手持);
		EntityNameIDMap[("WeapWinchester_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"S1897", EItemType::S1897_手持);
		EntityNameIDMap[("WeapFlareGun_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"信号枪", EItemType::信号枪_手持);
		EntityNameIDMap[("WeapC4_C")] = EntityNameIDTypeMap(EntityType::投掷, 天蓝, u8"C4", EItemType::C4_手持);
		EntityNameIDMap[("WeapMolotov_C")] = EntityNameIDTypeMap(EntityType::投掷, 天蓝, u8"燃烧弹", EItemType::燃烧弹_手持);
		EntityNameIDMap[("WeapGrenade_C")] = EntityNameIDTypeMap(EntityType::投掷, 天蓝, u8"手榴弹", EItemType::手榴弹_手持);
		EntityNameIDMap[("WeapApple_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"苹果", EItemType::苹果_手持);

		//EntityNameIDMap[("WeapJerryCan_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"燃料", EItemType::燃料);
	}

	/*枪械*/
	{
		EntityNameIDMap[("Item_Weapon_K2_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|K2", EItemType::K2);
		EntityNameIDMap[("Item_Weapon_HK416")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|M416", EItemType::M416);
		EntityNameIDMap[("Item_Weapon_AWM_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|AWM", EItemType::AWM);
		EntityNameIDMap[("Item_Weapon_M24_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|M24", EItemType::M24);
		EntityNameIDMap[("Item_Weapon_SKS_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|SKS", EItemType::SKS);
		EntityNameIDMap[("Item_Weapon_G36C_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|G36C", EItemType::G36C);
		EntityNameIDMap[("Item_Weapon_M249_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|M249", EItemType::M249);
		EntityNameIDMap[("Item_Weapon_DP28_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|DP28", EItemType::DP28);
		EntityNameIDMap[("Item_Weapon_Mk12_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|MK12", EItemType::MK12);
		EntityNameIDMap[("Item_Weapon_Mk14_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|MK14", EItemType::MK14);
		EntityNameIDMap[("Item_Weapon_AK47_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|AKM", EItemType::AKM);
		EntityNameIDMap[("Item_Weapon_HK416_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|M416", EItemType::M416);
		EntityNameIDMap[("Item_Weapon_QBU88_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|QBU8", EItemType::QBU8);
		EntityNameIDMap[("Item_Weapon_M16A4_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|M16A4", EItemType::M16A4);
		EntityNameIDMap[("Item_Weapon_QBZ95_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|QB95", EItemType::QB95);
		EntityNameIDMap[("Item_Weapon_Groza_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|Groza", EItemType::Groza);
		EntityNameIDMap[("Item_Weapon_FNFal_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|SLR", EItemType::SLR);
		EntityNameIDMap[("Item_Weapon_Mosin_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|莫辛纳甘", EItemType::莫辛纳甘);
		EntityNameIDMap[("Item_Weapon_Mortar_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|迫击炮", EItemType::迫击炮);
		EntityNameIDMap[("Item_Weapon_SCAR-L_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|SCAR-L", EItemType::SCARL);
		EntityNameIDMap[("Item_Weapon_Kar98k_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|Kar98k", EItemType::Kar98k);
		EntityNameIDMap[("Item_Weapon_Mini14_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|Mini14", EItemType::Mini14);
		EntityNameIDMap[("Item_Weapon_FlareGun_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|信号枪", EItemType::信号枪);
		EntityNameIDMap[("Item_Weapon_BerylM762_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|M762", EItemType::M762);
		EntityNameIDMap[("Item_Weapon_Mk47Mutant_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|MK47", EItemType::MK47);
		EntityNameIDMap[("Item_Weapon_ACE32_C")] = EntityNameIDTypeMap(EntityType::枪械, 天蓝, u8"|ACE32", EItemType::ACE32);
		EntityNameIDMap[("Item_Weapon_P90_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|P90", EItemType::P90);
		EntityNameIDMap[("Item_Weapon_FAMASG2_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|法玛斯", EItemType::法玛斯);
		EntityNameIDMap[("Item_Weapon_Vector_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|Vector", EItemType::Vector);
		EntityNameIDMap[("Item_Weapon_BizonPP19_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|野牛冲锋枪", EItemType::野牛冲锋枪);
		EntityNameIDMap[("Item_Weapon_UZI_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|UZI", EItemType::UZI);
		EntityNameIDMap[("Item_Weapon_VSS_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|VSS", EItemType::VSS);
		EntityNameIDMap[("Item_Weapon_Win1894_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|Win94", EItemType::Win94);
		EntityNameIDMap[("Item_Weapon_Thompson_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|汤姆逊", EItemType::汤姆逊);
		EntityNameIDMap[("Item_Weapon_UMP_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|UMP9", EItemType::UMP9);
		EntityNameIDMap[("Item_Weapon_Saiga12_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|S12K", EItemType::S12K);
		EntityNameIDMap[("Item_Weapon_Sawnoff_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|霰弹手喷", EItemType::霰弹手喷);
		EntityNameIDMap[("Item_Weapon_MP5K_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|MP5K", EItemType::MP5K);
		EntityNameIDMap[("Item_Weapon_L6_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|AMR", EItemType::AMR);
		EntityNameIDMap[("Item_Weapon_M1911_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|P1911", EItemType::P1911);
		EntityNameIDMap[("Item_Weapon_M79_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|M79", EItemType::M79);
		EntityNameIDMap[("Item_Weapon_M9_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|P92", EItemType::P92);
		EntityNameIDMap[("Item_Weapon_MG3_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|MG3", EItemType::MG3);
		EntityNameIDMap[("Item_Weapon_JS9_C")] = EntityNameIDTypeMap(EntityType::枪械, 红色, u8"|JS9", EItemType::JS9);





	}
	/*配件*/
	{
		EntityNameIDMap[("Item_Attach_Weapon_Upper_Aimpoint_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|二倍镜", EItemType::二倍镜);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_Scope3x_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|三倍镜", EItemType::三倍镜);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_CQBSS_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|八倍镜", EItemType::八倍镜);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_ACOG_01_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|四倍镜", EItemType::四倍镜);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_Scope6x_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|六倍镜", EItemType::六倍镜);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_PM2_01_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|十五倍镜", EItemType::十五倍镜);
		EntityNameIDMap[("Item_Attach_Weapon_Lower_Foregrip_C")] = EntityNameIDTypeMap(EntityType::配件, 黄色, u8"|垂直", EItemType::垂直);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_Holosight_C")] = EntityNameIDTypeMap(EntityType::配件, 黄色, u8"|全息", EItemType::全息);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_DotSight_01_C")] = EntityNameIDTypeMap(EntityType::配件, 黄色, u8"|红点", EItemType::红点);
		EntityNameIDMap[("Item_Attach_Weapon_Stock_AR_Composite_C")] = EntityNameIDTypeMap(EntityType::配件, 黄色, u8"|枪托", EItemType::枪托);
		EntityNameIDMap[("Item_Attach_Weapon_Muzzle_Suppressor_Large_C")] = EntityNameIDTypeMap(EntityType::配件, 黄色, u8"|枪消", EItemType::枪消);
		EntityNameIDMap[("Item_Attach_Weapon_Magazine_Extended_Large_C")] = EntityNameIDTypeMap(EntityType::配件, 黄色, u8"|普扩", EItemType::普扩);
		EntityNameIDMap[("Item_Attach_Weapon_Muzzle_Compensator_Large_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|枪补", EItemType::枪补);
		EntityNameIDMap[("Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C")] = EntityNameIDTypeMap(EntityType::配件, 黄色, u8"|托腮", EItemType::托腮);
		EntityNameIDMap[("Item_Attach_Weapon_Magazine_Extended_SniperRifle_C")] = EntityNameIDTypeMap(EntityType::配件, 黄色, u8"|狙扩", EItemType::狙扩);
		EntityNameIDMap[("Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|狙消", EItemType::狙消);
		EntityNameIDMap[("Item_Attach_Weapon_Muzzle_Compensator_SniperLarge_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|狙补", EItemType::狙补);
		EntityNameIDMap[("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|快扩", EItemType::快扩);
		EntityNameIDMap[("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|狙扩", EItemType::狙扩);
		//EntityNameIDMap[("Tiger_Key_C")] = EntityNameIDTypeMap(EntityType::配件, 红色, u8"|神秘钥匙", EItemType::神秘钥匙);
		
	}

	/*防具*/
	{
		EntityNameIDMap[("Item_Ghillie_01_C")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|吉利服", EItemType::吉利服);
		EntityNameIDMap[("Item_Ghillie_02_C")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|吉利服", EItemType::吉利服);
		EntityNameIDMap[("Item_Ghillie_03_C")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|吉利服", EItemType::吉利服);
		EntityNameIDMap[("Item_Ghillie_04_C")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|吉利服", EItemType::吉利服);
		EntityNameIDMap[("Item_Head_F_02_Lv2_C")] = EntityNameIDTypeMap(EntityType::防具, 深青, u8"|二头盔", EItemType::二头盔);
		EntityNameIDMap[("Item_Head_F_01_Lv2_C")] = EntityNameIDTypeMap(EntityType::防具, 深青, u8"|二头盔", EItemType::二头盔);
		EntityNameIDMap[("Item_Head_G_01_Lv3_C")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|三头盔", EItemType::三头盔);
		EntityNameIDMap[("Item_Back_E_01_Lv1_C")] = EntityNameIDTypeMap(EntityType::防具, 深青, u8"|一背包", EItemType::一背包);
		EntityNameIDMap[("Item_Back_E_02_Lv1_C")] = EntityNameIDTypeMap(EntityType::防具, 深青, u8"|一背包", EItemType::一背包);
		EntityNameIDMap[("Item_Back_F_01_Lv2_C")] = EntityNameIDTypeMap(EntityType::防具, 深青, u8"|二背包", EItemType::二背包);
		EntityNameIDMap[("Item_Back_F_02_Lv2_C")] = EntityNameIDTypeMap(EntityType::防具, 深青, u8"|二背包", EItemType::二背包);
		EntityNameIDMap[("Item_Back_C_01_Lv3_C")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|三背包", EItemType::三背包);
		EntityNameIDMap[("Item_Back_C_02_Lv3_C")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|三背包", EItemType::三背包);
		EntityNameIDMap[("Item_Back_BlueBlocker")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|二背包", EItemType::二背包);
		EntityNameIDMap[("Item_Armor_D_01_Lv1_C")] = EntityNameIDTypeMap(EntityType::防具, 深青, u8"|一级甲", EItemType::一级甲);
		EntityNameIDMap[("Item_Armor_D_01_Lv2_C")] = EntityNameIDTypeMap(EntityType::防具, 深青, u8"|二级甲", EItemType::二级甲);
		EntityNameIDMap[("Item_Armor_C_01_Lv3_C")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|三级甲", EItemType::三级甲);
		EntityNameIDMap[("Item_EmergencyPickup_C")] = EntityNameIDTypeMap(EntityType::防具, 红色, u8"|呼救器", EItemType::呼救器);



	}
	/*药品*/
	{

		EntityNameIDMap[("Item_Heal_MedKit_C")] = EntityNameIDTypeMap(EntityType::药品, 绿色, u8"|医疗箱", EItemType::医疗箱);
		EntityNameIDMap[("Item_Heal_FirstAid_C")] = EntityNameIDTypeMap(EntityType::药品, 绿色, u8"|急救包", EItemType::急救包);
		EntityNameIDMap[("Item_Boost_PainKiller_C")] = EntityNameIDTypeMap(EntityType::药品, 绿色, u8"|止疼", EItemType::止疼);
		EntityNameIDMap[("Item_Boost_EnergyDrink_C")] = EntityNameIDTypeMap(EntityType::药品, 绿色, u8"|饮料", EItemType::饮料);
		EntityNameIDMap[("Item_Weapon_VendingMachine_C")] = EntityNameIDTypeMap(EntityType::药品, 绿色, u8"|售货级", EItemType::售货级);
		EntityNameIDMap[("Item_Boost_AdrenalineSyringe_C")] = EntityNameIDTypeMap(EntityType::药品, 绿色, u8"|肾上腺素", EItemType::肾上腺素);
		EntityNameIDMap[("Item_Heal_Bandage_C")] = EntityNameIDTypeMap(EntityType::药品, 绿色, u8"|绷带", EItemType::绷带);

	}
	/*投掷*/
	{


		EntityNameIDMap[("Item_Weapon_Grenade_C")] = EntityNameIDTypeMap(EntityType::投掷, 白色, u8"|手雷", EItemType::手雷);
		EntityNameIDMap[("Weapon_StickyGrenade_C")] = EntityNameIDTypeMap(EntityType::投掷, 白色, u8"|C4炸弹", EItemType::C4炸弹);
		EntityNameIDMap[("Item_Weapon_C4_C")] = EntityNameIDTypeMap(EntityType::投掷, 白色, u8"|C4炸弹", EItemType::C4炸弹);
		EntityNameIDMap[("Item_Weapon_SmokeBomb_C")] = EntityNameIDTypeMap(EntityType::投掷, 白色, u8"|烟雾弹", EItemType::烟雾弹);
		EntityNameIDMap[("Item_Weapon_Molotov_C")] = EntityNameIDTypeMap(EntityType::投掷, 白色, u8"|烟雾弹", EItemType::烟雾弹);
		EntityNameIDMap[("Item_Weapon_BluezoneGrenade_C")] = EntityNameIDTypeMap(EntityType::投掷, 白色, u8"|篮圈手雷", EItemType::篮圈手雷);
		EntityNameIDMap[("Item_Weapon_StickyGrenade_C")] = EntityNameIDTypeMap(EntityType::投掷, 白色, u8"黏土炸弹", EItemType::黏土炸弹);
		//下方是投掷出来的类名
		EntityNameIDMap[("ProjGrenade_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, 红色, u8"|小心手雷", EItemType::UnKnown);
		EntityNameIDMap[("ProjC4_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, 红色, u8"小心C4", EItemType::UnKnown);
		EntityNameIDMap[("ProjStickyGrenade_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, 红色, u8"|小心C4", EItemType::UnKnown);
		EntityNameIDMap[("ProjFlashBang_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, 红色, u8"|小心闪光弹", EItemType::UnKnown);
		EntityNameIDMap[("ProjMolotov_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, 红色, u8"|小心燃烧弹", EItemType::UnKnown);
		EntityNameIDMap[("ProjBluezoneGrenade_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, 红色, u8"|小心篮圈手雷", EItemType::UnKnown);

	}
	/*空投盒子*/
	{
		EntityNameIDMap[("DeathDropItemPackage_C")] = EntityNameIDTypeMap(EntityType::盒子, 橙黄, u8"死亡盒子", EItemType::死亡盒子);
		EntityNameIDMap[("Carapackage_RedBox_C")] = EntityNameIDTypeMap(EntityType::盒子, 红色, u8"空投箱子", EItemType::空投箱子);
		EntityNameIDMap[("Carapackage_FlareGun_C")] = EntityNameIDTypeMap(EntityType::盒子, 红色, u8"超级空投", EItemType::超级空投);
		EntityNameIDMap[("Carapackage_SmallPackage_C")] = EntityNameIDTypeMap(EntityType::盒子, 红色, u8"小空投箱", EItemType::小空投箱);
		EntityNameIDMap[("Carapackage_RedBox_COL_C")] = EntityNameIDTypeMap(EntityType::盒子, 红色, u8"空投箱子", EItemType::空投箱子);
	}

	std::unordered_map<std::string, EntityNameIDTypeMap>::iterator EntityTypeIt = std::unordered_map<std::string, EntityNameIDTypeMap>::iterator();

	for (ULONG i = 0; i < 0x100000; i++)
	{
		string Name = SDK::GetNames(i);

		EntityTypeIt = EntityNameIDMap.find(Name);

		if (EntityTypeIt != EntityNameIDMap.end())
		{
			EntityIDTypeMap[i] = EntityTypeIt->second;
			continue;
		}
	}

}
