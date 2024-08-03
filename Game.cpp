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
	//��ɾ���ж�����

	std::thread(CThread::Cache�߳�).detach();
	std::thread(CThread::��ȡ����).detach();
	std::thread(CThread::GetPlayerWeaponData).detach();
	std::thread(CThread::GetPlayerData).detach();
	std::thread(CThread::RadarData).detach();
	//std::thread(CThread::ȡ������Ϣ).detach();
	AimControl::Attach();
	return true;

}

bool EngineThread::GameData() {
	auto start = std::chrono::high_resolution_clock::now();

	std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator IDTypeMapIt = std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator();
	auto ��ʱ��� = Player();
	auto ��ʱ��Ʒ = Item();
	auto ������Ʒ = Item();
	auto ������Ʒ = PackgeItem();
	auto ��ʱ�ؾ� = vehicle();
	auto ��ʱ�������� = Actor();
	//printf("��Ϸ״̬%d ��Ϸ���� %d\n", Data.��Ϸ״̬, Data.��Ϸ����);
	
	auto Count = G::Mem.Read<int>(Data.Actors + 8);
	this->ActorCount = Count;
	//printf("%d\n", Count);
	if (Count > 1 && Count < 9000) {
		auto Actors = G::Mem.Read<uint64_t>(Data.Actors);

		for (auto i = 0; i < Count; i++) {
			auto pActor = G::Mem.Read<uint64_t>(Actors + i * 8); 
			if (pActor <= 65536) continue;
			auto ObjectID = SDK::DecryptID(pActor); if (ObjectID <= 0) continue;
			if (pActor == Local.AcknowledgedPawn) continue;//�ж��Ƿ���



			if (F::Global.Menu.Debug)
			{
					

				if (SDK::GetNames(ObjectID) == E("DroppedItem"))//DroppedItem
				{
					//auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::RootComponent));
					//if (RootComponent <= 65536) continue;
					ULONG_PTR PackageItemPtr = SDK::DecryptCall(G::Mem.Read<ULONG_PTR>(pActor + offsets::DroppedItem));
					if (PackageItemPtr <= 65536) continue;
					ULONG PackageItemObjID = G::Mem.Read<ULONG>(G::Mem.Read<ULONG_PTR>(PackageItemPtr + offsets::��Ʒһ) + offsets::��Ʒ��);
					//��ʱ��������.RootComponent = RootComponent;
					��ʱ��������.pActor = pActor;
					��ʱ��������.Name = SDK::GetNames(PackageItemObjID);
					�������黺��.push_back(��ʱ��������);
				}
				else
				{
					auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
					if (RootComponent <= 65536) continue;
					��ʱ��������.RootComponent = RootComponent;
					��ʱ��������.pActor = pActor;
					��ʱ��������.Name = SDK::GetNames(ObjectID);
					�������黺��.push_back(��ʱ��������);
				}

			}
			if (F::Global.Menu.Debug) continue;

			IDTypeMapIt = Game::EntityIDTypeMap.find(ObjectID);
			if (IDTypeMapIt == Game::EntityIDTypeMap.end()) continue;


			if (IDTypeMapIt->second.Type == Game::EntityType::EntityTypePlayer)//���
			{
				auto Mesh = G::Mem.Read<uint64_t>(pActor + offsets::Mesh); if (Mesh <= 65536) continue;

				auto Teamid = G::Mem.Read<int>(pActor + offsets::TeamNumber);
				if (Teamid >= 100000) { Teamid -= 100000; }
				if (Teamid == Local.Teamid && !F::Global.Menu.������ʾ)continue;
				auto PlayerState = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::PlayerState));
					
				auto pName = G::Mem.Read<uint64_t>(pActor + offsets::Playname);
				/*ULONG_PTR PlayerVehicleComponent = G::Mem.Read<ULONG_PTR>(pActor + offsets::VehicleRiderComponent);*/
				//printf("PlayerVehicleComponent %p\n", PlayerVehicleComponent);

				//auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::RootComponent));
				//��ʱ���.RootComponent = RootComponent;

				��ʱ���.pActor = pActor;
				��ʱ���.ActorRootComp = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
				��ʱ���.Mesh = Mesh;
				��ʱ���.Teamid = Teamid;
				��ʱ���.PlayerState = PlayerState;
				std::string str = SDK::GetNames(ObjectID);
				std::wstring wstr(str.length(), L'\0\0');
				std::copy(str.begin(), str.end(), wstr.begin());

				//��ʱ���.PlayerVehicleComponent = PlayerVehicleComponent;
				��ʱ���.Name = SDK::GetPlayName(pName);
				��ʱ���.TeamColor = Game::GetTeamColor(IDTypeMapIt->second.Name == "Bot" ? 0 : Teamid);

				this->��_������黺��.push_back(Player(��ʱ���));
			}
			else if (IDTypeMapIt->second.Type == Game::EntityType::EntityTypeItem)//ȫ��Ʒ
			{
				//printf("Item %s\n",SDK::GetNames(ObjectID).c_str());
				//if (F::Global.Menu.��͸����) continue;
				ULONG_PTR PackageItemPtr = SDK::DecryptCall(G::Mem.Read<ULONG_PTR>(pActor + offsets::DroppedItem));
				if (!PackageItemPtr) continue;
				ULONG PackageItemObjID = G::Mem.Read<ULONG>(G::Mem.Read<ULONG_PTR>(PackageItemPtr + offsets::��Ʒһ) + offsets::��Ʒ��);

				IDTypeMapIt = Game::EntityIDTypeMap.find(PackageItemObjID);

				if (IDTypeMapIt == Game::EntityIDTypeMap.end()) continue;

				auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
				if (!RootComponent) continue;
				// printf("pActor %p RootComponent %p\n", pActor, RootComponent);
				��ʱ��Ʒ.pActor = pActor;
				��ʱ��Ʒ.RootComponent = RootComponent;
				��ʱ��Ʒ.Name = IDTypeMapIt->second.Name;
				��ʱ��Ʒ.Type = IDTypeMapIt->second.Type;
				��ʱ��Ʒ.Ҫ���ֵ���Ʒ���� = Game::EItemType::UnKnown;
				��ʱ��Ʒ.Ҫ���ֵ���Ʒ���� = IDTypeMapIt->second.ItemType;
				//��ʱ��Ʒ.Color = IDTypeMapIt->second.Color;
				{
					if (IDTypeMapIt->second.Type == Game::EntityType::�ؾ�)
					{
						��ʱ��Ʒ.Color = F::Global.Color.�ؾ�;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::ǹе)
					{
						��ʱ��Ʒ.Color = F::Global.Color.ǹе;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::���)
					{
						��ʱ��Ʒ.Color = F::Global.Color.���;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::����)
					{
						��ʱ��Ʒ.Color = F::Global.Color.����;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::ҩƷ)
					{
						��ʱ��Ʒ.Color = F::Global.Color.ҩƷ;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::Ͷ��)
					{
						��ʱ��Ʒ.Color = F::Global.Color.Ͷ��;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::��Ͷ)
					{
						��ʱ��Ʒ.Color = F::Global.Color.��Ͷ����;
					}
					else if (IDTypeMapIt->second.Type == Game::EntityType::��Ͷ)
					{
						��ʱ��Ʒ.Color = F::Global.Color.��Ͷ����;
					}
				}
				this->��_��Ʒ���黺��.push_back(Item(��ʱ��Ʒ));
			}
			else if (IDTypeMapIt->second.Type == Game::EntityType::EntityTypeItemGroup)
			{
				//if (F::Global.Menu.��͸����) continue;

				ULONG_PTR DroppedItemArray = G::Mem.Read<ULONG_PTR>(pActor + offsets::DroppedItemGroup);

				ULONG DroppedItemCount = G::Mem.Read<ULONG>(pActor + offsets::DroppedItemGroup_Count); if (DroppedItemCount < 0 || DroppedItemCount > 100) continue;

				for (ULONG_PTR i = 0; i < DroppedItemCount; i++)
				{
					ULONG_PTR DroppedItemPtr = G::Mem.Read<ULONG_PTR>(DroppedItemArray + i * 0x10);
					if (!DroppedItemPtr) continue;
					ULONG_PTR DroppedItemObj = G::Mem.Read<ULONG_PTR>(DroppedItemPtr + offsets::DroppedItemGroup_UItem);
					if (!DroppedItemObj) continue;
					ULONG DroppedItemObjID = G::Mem.Read<ULONG>(G::Mem.Read<ULONG_PTR>(DroppedItemObj + offsets::��Ʒһ) + offsets::��Ʒ��); if (!DroppedItemObjID || DroppedItemObjID > 1000000) { continue; }
					IDTypeMapIt = Game::EntityIDTypeMap.find(DroppedItemObjID);

					if (IDTypeMapIt == Game::EntityIDTypeMap.end()) continue;

					������Ʒ.pActor = DroppedItemPtr;
					������Ʒ.RootComponent = DroppedItemPtr;
					������Ʒ.Name = IDTypeMapIt->second.Name;
					������Ʒ.Type = IDTypeMapIt->second.Type;
					������Ʒ.Ҫ���ֵ���Ʒ���� = Game::EItemType::UnKnown;
					������Ʒ.Ҫ���ֵ���Ʒ���� = IDTypeMapIt->second.ItemType;
					//������Ʒ.Color = IDTypeMapIt->second.Color;
					{
						if (IDTypeMapIt->second.Type == Game::EntityType::�ؾ�)
						{
							������Ʒ.Color = F::Global.Color.�ؾ�;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::ǹе)
						{
							������Ʒ.Color = F::Global.Color.ǹе;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::���)
						{
							������Ʒ.Color = F::Global.Color.���;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::����)
						{
							������Ʒ.Color = F::Global.Color.����;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::ҩƷ)
						{
							������Ʒ.Color = F::Global.Color.ҩƷ;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::Ͷ��)
						{
							������Ʒ.Color = F::Global.Color.Ͷ��;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::��Ͷ)
						{
							������Ʒ.Color = F::Global.Color.��Ͷ����;
						}
						else if (IDTypeMapIt->second.Type == Game::EntityType::��Ͷ)
						{
							������Ʒ.Color = F::Global.Color.��Ͷ����;
						}
					}

					this->��_������Ʒ���黺��.push_back(Item(������Ʒ));
				}
			}
			else if (IDTypeMapIt->second.Type == Game::EntityType::�ؾ�)
			{
				auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
				if (!RootComponent) continue;
				��ʱ�ؾ�.pActor = pActor;
				��ʱ�ؾ�.RootComponent = RootComponent;
				��ʱ�ؾ�.Name = IDTypeMapIt->second.Name;
				��ʱ�ؾ�.Type = IDTypeMapIt->second.Type;

				��ʱ�ؾ�.Ҫ���ֵ���Ʒ���� = IDTypeMapIt->second.ItemType;
				//printf("���ؾ� %s\n", IDTypeMapIt->second.Name);
				this->��_�ؾ����黺��.push_back(vehicle(��ʱ�ؾ�));

			}
			//else if (IDTypeMapIt->second.Type == Game::EntityType::����)
			//{
			//	continue;
			//	uintptr_t ��_��Ʒ���� = G::Mem.Read<uintptr_t>(pActor + offsets::Packge - 8);
			//	int ��_��Ʒ���� = G::Mem.Read<int>(pActor + offsets::Packge);

			//	if (��_��Ʒ���� <= 0 || ��_��Ʒ���� > 30 || ��_��Ʒ���� < 0)
			//		continue;
			//	if (F::Global.Menu.��͸����) continue;

			//	auto RootComponent = SDK::DecryptCall(G::Mem.Read<uint64_t>(pActor + offsets::m_rootComponent));
			//	������Ʒ.Actor = pActor;
			//	������Ʒ.DroppedItemGroup = ��_��Ʒ����;// G::Mem.Read<uintptr_t>(pActor + offsets::DroppedItemGroup);
			//	������Ʒ.RootComponent = RootComponent;
			//	for (size_t n = 0; n < ��_��Ʒ����; n++)
			//	{


			//		uintptr_t ptr1 = G::Mem.Read<uintptr_t>(��_��Ʒ���� + n * 8);
			//		if (!ptr1) continue;
			//		uint32_t PackItemObjID = G::Mem.Read<ULONG>(G::Mem.Read<ULONG_PTR>(ptr1 + offsets::��Ʒһ) + offsets::��Ʒ��);
			//		IDTypeMapIt = Game::EntityIDTypeMap.find(PackItemObjID);

			//		if (IDTypeMapIt == Game::EntityIDTypeMap.end()) continue;

			//		������Ʒ.Name = IDTypeMapIt->second.Name;

			//		this->��_�������龏��.push_back(PackgeItem(������Ʒ));
			//	}

			//}
		}
		this->�������� = this->�������黺��;
		this->��_������� = this->��_������黺��;
		this->��_��Ʒ���� = this->��_��Ʒ���黺��;
		this->��_������Ʒ���� = this->��_������Ʒ���黺��;
		this->��_�ؾ����� = this->��_�ؾ����黺��;
		//this->��_�������� = this->��_�������龏��;
		this->�������黺��.clear();
		this->��_������黺��.clear();
		this->��_��Ʒ���黺��.clear();
		this->��_������Ʒ���黺��.clear();
		this->��_�ؾ����黺��.clear();
		//this->��_�������龏��.clear();
			
	}
	
	
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	//auto stop = std::chrono::high_resolution_clock::now();
	//auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
	
	//std::cout << "ʹ�� " << duration.count() << " ����  " << "������:" << Count << std::endl;

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
		return ImGui::HexToImVec4("0xA0F8A658", 255); // Ĭ����ɫ
	}
}

void Game::InitNameTypeMap()
{
	std::unordered_map<std::string, EntityNameIDTypeMap> EntityNameIDMap = std::unordered_map<std::string, EntityNameIDTypeMap>();

	/*�ж���*/
	{
		EntityNameIDMap[("Chimera_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 1, "Chimera_Main");
		EntityNameIDMap[("Desert_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 2, "Desert_Main");
		EntityNameIDMap[("DihorOtok_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 3, "DihorOtok_Main");
		EntityNameIDMap[("Erangel_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 4, "Erangel_Main");
		EntityNameIDMap[("Range_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 5, "Range_Main");
		EntityNameIDMap[("Savage_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 6, "Savage_Main");
		EntityNameIDMap[("Summerland_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 7, "Summerland_Main");
		EntityNameIDMap[("Heaven_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 8, "Heaven_Main");
		EntityNameIDMap[("Kiki_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 9, "Kiki_Main");
		EntityNameIDMap[("Tiger_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 10, "Tiger_Main");

		EntityNameIDMap[("Baltic_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 4, "Baltic_Main");
		EntityNameIDMap[("Tutorial_Main")] = EntityNameIDTypeMap(EntityType::��Ϸ��, 0, "Tutorial_Main");
		EntityNameIDMap[("TslLobby_Persistent_Main")] = EntityNameIDTypeMap(EntityType::����, 0, "TslLobby_Persistent_Main");
	}

	/*����*/
	{
		EntityNameIDMap[("RegistedPlayer")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("AIPawn_Base_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("AIPawn_Base_Female_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("AIPawn_Base_Male_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("AIPawn_Base_Male_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Pillar_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Female_Pillar_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Male_Pillar_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Female_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("UltAIPawn_Base_Male_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Bot");
		EntityNameIDMap[("PlayerMale_A")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Player");
		EntityNameIDMap[("PlayerMale_A_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Player");
		EntityNameIDMap[("PlayerFemale_A")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Player");
		EntityNameIDMap[("PlayerFemale_A_C")] = EntityNameIDTypeMap(EntityType::EntityTypePlayer, ��ɫ, "Player");
		EntityNameIDMap[("DroppedItem")] = EntityNameIDTypeMap(EntityType::EntityTypeItem, ��ɫ, nullptr);
		EntityNameIDMap[("DroppedItemGroup")] = EntityNameIDTypeMap(EntityType::EntityTypeItemGroup, ��ɫ, nullptr);
	}


	/*�ؾ�*/
	{
		EntityNameIDMap[("Weapon_Drone_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"���˻����", EItemType::���˻����);
		EntityNameIDMap[("Uaz_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_ATV_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"������", EItemType::������);
		EntityNameIDMap[("Uaz_A_01")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("Uaz_B_01")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("Uaz_C_01")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("Uaz_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("Uaz_B_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("Uaz_C_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("Dacia_A_01")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Dacia_A_02")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Dacia_A_03")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Dacia_A_01")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Dacia_A_04")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Buggy_A_01")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_02")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_03")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_04")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_05")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_06")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("AquaRail_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħͧ", EItemType::Ħͧ);
		EntityNameIDMap[("BP_Drone_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"���˻�", EItemType::���˻�);
		EntityNameIDMap[("BP_Van_A_01")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_Van_A_02")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_Van_A_03")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_Porter_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_CoupeRB_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("Buggy_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_04_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_05_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Buggy_A_06_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ı�", EItemType::�ı�);
		EntityNameIDMap[("Dacia_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Dacia_A_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Dacia_A_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Dacia_A_04_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Boat_PG117_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"��ͧ", EItemType::��ͧ);
		EntityNameIDMap[("PG117_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"��ͧ", EItemType::��ͧ);
		EntityNameIDMap[("BP_Niva_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_04_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_05_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Niva_06_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"NIVA", EItemType::NIVA);
		EntityNameIDMap[("BP_Dirtbike_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"ԽҰĦ��", EItemType::ԽҰĦ��);
		EntityNameIDMap[("BP_Van_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_Van_A_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_Van_A_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("Dacia_A_04_v2")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("AquaRail_A_01")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħͧ", EItemType::Ħͧ);
		EntityNameIDMap[("BP_KillTruck_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"KILLTRUCK", EItemType::KILLTRUCK);
		EntityNameIDMap[("BP_TukTukTuk_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"TUK", EItemType::TUK);
		EntityNameIDMap[("Dacia_A_03_v2_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("Dacia_A_04_v2_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�γ�", EItemType::�γ�);
		EntityNameIDMap[("BP_Motorbike_04")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("AquaRail_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħͧ", EItemType::Ħͧ);
		EntityNameIDMap[("BP_Helicopter_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Helicopter", EItemType::Helicopter);
		EntityNameIDMap[("BP_M_Rony_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ܳ�", EItemType::�ܳ�);
		EntityNameIDMap[("BP_M_Rony_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_M_Rony_A_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_M_Rony_A_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("ABP_Motorbike_03")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("ABP_Motorbike_04")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("BP_Mirado_A_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ܳ�", EItemType::�ܳ�);
		EntityNameIDMap[("BP_Motorbike_04_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("BP_Motorbike_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("BP_Scooter_01_A_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"SCOOTER", EItemType::SCOOTER);
		EntityNameIDMap[("BP_Scooter_02_A_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"SCOOTER", EItemType::SCOOTER);
		EntityNameIDMap[("BP_Scooter_03_A_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"SCOOTER", EItemType::SCOOTER);
		EntityNameIDMap[("BP_Scooter_04_A_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"SCOOTER", EItemType::SCOOTER);
		EntityNameIDMap[("BP_Snowmobile_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"SMOBILE", EItemType::SMOBILE);
		EntityNameIDMap[("BP_Snowmobile_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"SMOBILE", EItemType::SMOBILE);
		EntityNameIDMap[("BP_Snowmobile_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"SMOBILE", EItemType::SMOBILE);
		EntityNameIDMap[("ABP_Motorbike_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("ABP_Motorbike_04_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("BP_Mirado_Open_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ܳ�", EItemType::�ܳ�);
		EntityNameIDMap[("BP_Mirado_Open_04_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"�ܳ�", EItemType::�ܳ�);
		EntityNameIDMap[("BP_TukTukTuk_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_TukTukTuk_A_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_TukTukTuk_A_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"����", EItemType::����);
		EntityNameIDMap[("BP_PickupTruck_A_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ƥ��", EItemType::Ƥ��);
		EntityNameIDMap[("BP_PickupTruck_A_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ƥ��", EItemType::Ƥ��);
		EntityNameIDMap[("BP_PickupTruck_A_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ƥ��", EItemType::Ƥ��);
		EntityNameIDMap[("BP_PickupTruck_A_04_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ƥ��", EItemType::Ƥ��);
		EntityNameIDMap[("BP_PickupTruck_A_05_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ƥ��", EItemType::Ƥ��);
		EntityNameIDMap[("BP_PickupTruck_B_01_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ƥ��", EItemType::Ƥ��);
		EntityNameIDMap[("BP_PickupTruck_B_02_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ƥ��", EItemType::Ƥ��);
		EntityNameIDMap[("BP_PickupTruck_B_03_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ƥ��", EItemType::Ƥ��);
		EntityNameIDMap[("BP_PickupTruck_B_04_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ƥ��", EItemType::Ƥ��);
		EntityNameIDMap[("BP_Motorbike_04_Desert")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("ABP_Motorbike_04_Sidecar")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("BP_Motorbike_04_Desert_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"Ħ��", EItemType::Ħ��);
		EntityNameIDMap[("BP_DummyTransportAircraft_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"AIRCRAFT", EItemType::AIRCRAFT);
		EntityNameIDMap[("BP_BRDM_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"װ�׳�", EItemType::װ�׳�);
		EntityNameIDMap[("Item_Mountainbike_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ, u8"���г�", EItemType::���г�);


		//EntityNameIDMap[("Dacia_A_01_v2")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ,u8"�γ�");
		//EntityNameIDMap[("BP_PonyCoupe_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ,u8"AE86");
		//EntityNameIDMap[("BP_LootTruck_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ,u8"���ʳ�");
		//EntityNameIDMap[("BP_Motorglider_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ,u8"�����");
		//EntityNameIDMap[("BP_DummyTransportAircraft_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ,u8"AIRCRAFT");
		//EntityNameIDMap[("BP_Motorbike_04_SideCar_Desert")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ,u8"Ħ��");
		//EntityNameIDMap[("BP_Motorbike_04_SideCar_Desert_C")] = EntityNameIDTypeMap(EntityType::�ؾ�, ��ɫ,u8"Ħ��");
	}

	/* �ֳ����� */
	{
		EntityNameIDMap[("WeapLunchmeatsAK47_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"AKM", EItemType::AKM_�ֳ�);
		EntityNameIDMap[("WeapAK47_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"AKM", EItemType::AKM_�ֳ�);
		EntityNameIDMap[("WeapAUG_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"AUG", EItemType::AUG_�ֳ�);
		EntityNameIDMap[("WeapAWM_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"AWM", EItemType::AWM_�ֳ�);
		EntityNameIDMap[("WeapBerreta686_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"S686", EItemType::S686_�ֳ�);
		EntityNameIDMap[("WeapBerylM762_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"BerylM762", EItemType::BerylM762_�ֳ�);
		EntityNameIDMap[("WeapBizonPP19_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Ұţ���ǹ", EItemType::Ұţ���ǹ_�ֳ�);
		EntityNameIDMap[("WeapCowbar_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"�˹�", EItemType::�˹�_�ֳ�);
		EntityNameIDMap[("WeapCowbarProjectile_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"�˹�", EItemType::�˹�_�ֳ�);
		EntityNameIDMap[("WeapCrossbow_1_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"ʮ����", EItemType::ʮ����_�ֳ�);
		EntityNameIDMap[("WeapDesertEagle_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"ɳĮ֮ӥ", EItemType::ɳĮ֮ӥ_�ֳ�);
		EntityNameIDMap[("WeapDP12_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"DBS", EItemType::DBS_�ֳ�);
		EntityNameIDMap[("WeapDP28_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"DP-28", EItemType::DP28_�ֳ�);
		EntityNameIDMap[("WeapDuncansHK416_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"M416", EItemType::M416_�ֳ�);
		EntityNameIDMap[("WeapHK416_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"M416", EItemType::M416_�ֳ�);
		EntityNameIDMap[("WeapFNFal_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"SLR", EItemType::SLR_�ֳ�);
		EntityNameIDMap[("WeapG18_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"P18C", EItemType::P18C_�ֳ�);
		EntityNameIDMap[("WeapG36C_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"G36C", EItemType::G36C_�ֳ�);
		EntityNameIDMap[("WeapGroza_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Groza", EItemType::Groza_�ֳ�);
		EntityNameIDMap[("WeapJuliesKar98k_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Kar98k", EItemType::Kar98k_�ֳ�);
		EntityNameIDMap[("WeapKar98k_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Kar98k", EItemType::Kar98k_�ֳ�);
		EntityNameIDMap[("WeapMk12_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Mk12", EItemType::Mk12_�ֳ�);
		EntityNameIDMap[("WeapK2_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"K2", EItemType::K2_�ֳ�);
		EntityNameIDMap[("WeapL6_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"AMR", EItemType::AMR_�ֳ�);
		EntityNameIDMap[("WeapM16A4_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"M16A4", EItemType::M16A4_�ֳ�);
		EntityNameIDMap[("WeapM1911_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"P1911", EItemType::P1911_�ֳ�);
		EntityNameIDMap[("WeapM249_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"M249", EItemType::M249_�ֳ�);
		EntityNameIDMap[("WeapM24_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"M24", EItemType::M24_�ֳ�);
		EntityNameIDMap[("WeapM9_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"P92", EItemType::P92_�ֳ�);
		EntityNameIDMap[("WeapMachete_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"����", EItemType::����_�ֳ�);
		EntityNameIDMap[("WeapMacheteProjectile_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"����", EItemType::����_�ֳ�);
		EntityNameIDMap[("WeapMadsQBU88_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"QBU", EItemType::QBU_�ֳ�);
		EntityNameIDMap[("WeapMG3_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"MG3", EItemType::MG3_�ֳ�);
		EntityNameIDMap[("WeapMini14_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Mini14", EItemType::Mini14_�ֳ�);
		EntityNameIDMap[("WeapMk14_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Mk14", EItemType::Mk14_�ֳ�);
		EntityNameIDMap[("WeapMk47Mutant_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Mk47Mutant", EItemType::Mk47Mutant_�ֳ�);
		EntityNameIDMap[("WeapMP5K_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"MP5K", EItemType::MP5K_�ֳ�);
		EntityNameIDMap[("WeapNagantM1895_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"R1895", EItemType::R1895_�ֳ�);
		EntityNameIDMap[("WeapMosinNagant_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Ī���ɸ�", EItemType::Ī���ɸ�_�ֳ�);
		EntityNameIDMap[("WeapP90_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"P90", EItemType::P90_�ֳ�);
		EntityNameIDMap[("WeapPan_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"ƽ�׹�", EItemType::ƽ�׹�_�ֳ�);
		EntityNameIDMap[("WeapPanProjectile_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"ƽ�׹�", EItemType::ƽ�׹�_�ֳ�);
		EntityNameIDMap[("WeapPanzerFaust100M1_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"��ȭ���Ͳ", EItemType::��ȭ���Ͳ_�ֳ�);
		EntityNameIDMap[("WeapQBU88_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"QBU", EItemType::QBU_�ֳ�);
		EntityNameIDMap[("WeapQBZ95_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"QBZ", EItemType::QBZ_�ֳ�);
		EntityNameIDMap[("WeapRhino_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"R45", EItemType::R45_�ֳ�);
		EntityNameIDMap[("WeapSaiga12_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"S12K", EItemType::S12K_�ֳ�);
		EntityNameIDMap[("WeapSawnoff_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"��������", EItemType::��������_�ֳ�);
		EntityNameIDMap[("WeapSCAR-L_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"SCAR-L", EItemType::SCARL_�ֳ�);
		EntityNameIDMap[("WeapSickle_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"����", EItemType::����_�ֳ�);
		EntityNameIDMap[("WeapSickleProjectile_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"����", EItemType::����_�ֳ�);
		EntityNameIDMap[("WeapSKS_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"SKS", EItemType::SKS_�ֳ�);
		EntityNameIDMap[("WeapThompson_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"��ķѷ", EItemType::��ķѷ_�ֳ�);
		EntityNameIDMap[("WeapUMP_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"UMP9", EItemType::UMP9_�ֳ�);
		EntityNameIDMap[("WeapUZI_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Micro Uzi", EItemType::MicroUzi_�ֳ�);
		EntityNameIDMap[("WeapVector_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Vector", EItemType::Vector_�ֳ�);
		EntityNameIDMap[("WeapVSS_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"VSS", EItemType::VSS_�ֳ�);
		EntityNameIDMap[("Weapvz61Skorpion_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Ыʽ���ǹ", EItemType::Ыʽ���ǹ_�ֳ�);
		EntityNameIDMap[("WeapWin94_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"Win94", EItemType::Win94_�ֳ�);
		EntityNameIDMap[("WeapWinchester_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"S1897", EItemType::S1897_�ֳ�);
		EntityNameIDMap[("WeapFlareGun_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"�ź�ǹ", EItemType::�ź�ǹ_�ֳ�);
		EntityNameIDMap[("WeapC4_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ����, u8"C4", EItemType::C4_�ֳ�);
		EntityNameIDMap[("WeapMolotov_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ����, u8"ȼ�յ�", EItemType::ȼ�յ�_�ֳ�);
		EntityNameIDMap[("WeapGrenade_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ����, u8"����", EItemType::����_�ֳ�);
		EntityNameIDMap[("WeapApple_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"ƻ��", EItemType::ƻ��_�ֳ�);

		//EntityNameIDMap[("WeapJerryCan_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"ȼ��", EItemType::ȼ��);
	}

	/*ǹе*/
	{
		EntityNameIDMap[("Item_Weapon_K2_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|K2", EItemType::K2);
		EntityNameIDMap[("Item_Weapon_HK416")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|M416", EItemType::M416);
		EntityNameIDMap[("Item_Weapon_AWM_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|AWM", EItemType::AWM);
		EntityNameIDMap[("Item_Weapon_M24_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|M24", EItemType::M24);
		EntityNameIDMap[("Item_Weapon_SKS_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|SKS", EItemType::SKS);
		EntityNameIDMap[("Item_Weapon_G36C_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|G36C", EItemType::G36C);
		EntityNameIDMap[("Item_Weapon_M249_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|M249", EItemType::M249);
		EntityNameIDMap[("Item_Weapon_DP28_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|DP28", EItemType::DP28);
		EntityNameIDMap[("Item_Weapon_Mk12_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|MK12", EItemType::MK12);
		EntityNameIDMap[("Item_Weapon_Mk14_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|MK14", EItemType::MK14);
		EntityNameIDMap[("Item_Weapon_AK47_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|AKM", EItemType::AKM);
		EntityNameIDMap[("Item_Weapon_HK416_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|M416", EItemType::M416);
		EntityNameIDMap[("Item_Weapon_QBU88_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|QBU8", EItemType::QBU8);
		EntityNameIDMap[("Item_Weapon_M16A4_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|M16A4", EItemType::M16A4);
		EntityNameIDMap[("Item_Weapon_QBZ95_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|QB95", EItemType::QB95);
		EntityNameIDMap[("Item_Weapon_Groza_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|Groza", EItemType::Groza);
		EntityNameIDMap[("Item_Weapon_FNFal_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|SLR", EItemType::SLR);
		EntityNameIDMap[("Item_Weapon_Mosin_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|Ī���ɸ�", EItemType::Ī���ɸ�);
		EntityNameIDMap[("Item_Weapon_Mortar_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|�Ȼ���", EItemType::�Ȼ���);
		EntityNameIDMap[("Item_Weapon_SCAR-L_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|SCAR-L", EItemType::SCARL);
		EntityNameIDMap[("Item_Weapon_Kar98k_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|Kar98k", EItemType::Kar98k);
		EntityNameIDMap[("Item_Weapon_Mini14_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|Mini14", EItemType::Mini14);
		EntityNameIDMap[("Item_Weapon_FlareGun_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|�ź�ǹ", EItemType::�ź�ǹ);
		EntityNameIDMap[("Item_Weapon_BerylM762_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|M762", EItemType::M762);
		EntityNameIDMap[("Item_Weapon_Mk47Mutant_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|MK47", EItemType::MK47);
		EntityNameIDMap[("Item_Weapon_ACE32_C")] = EntityNameIDTypeMap(EntityType::ǹе, ����, u8"|ACE32", EItemType::ACE32);
		EntityNameIDMap[("Item_Weapon_P90_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|P90", EItemType::P90);
		EntityNameIDMap[("Item_Weapon_FAMASG2_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|����˹", EItemType::����˹);
		EntityNameIDMap[("Item_Weapon_Vector_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|Vector", EItemType::Vector);
		EntityNameIDMap[("Item_Weapon_BizonPP19_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|Ұţ���ǹ", EItemType::Ұţ���ǹ);
		EntityNameIDMap[("Item_Weapon_UZI_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|UZI", EItemType::UZI);
		EntityNameIDMap[("Item_Weapon_VSS_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|VSS", EItemType::VSS);
		EntityNameIDMap[("Item_Weapon_Win1894_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|Win94", EItemType::Win94);
		EntityNameIDMap[("Item_Weapon_Thompson_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|��ķѷ", EItemType::��ķѷ);
		EntityNameIDMap[("Item_Weapon_UMP_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|UMP9", EItemType::UMP9);
		EntityNameIDMap[("Item_Weapon_Saiga12_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|S12K", EItemType::S12K);
		EntityNameIDMap[("Item_Weapon_Sawnoff_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|��������", EItemType::��������);
		EntityNameIDMap[("Item_Weapon_MP5K_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|MP5K", EItemType::MP5K);
		EntityNameIDMap[("Item_Weapon_L6_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|AMR", EItemType::AMR);
		EntityNameIDMap[("Item_Weapon_M1911_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|P1911", EItemType::P1911);
		EntityNameIDMap[("Item_Weapon_M79_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|M79", EItemType::M79);
		EntityNameIDMap[("Item_Weapon_M9_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|P92", EItemType::P92);
		EntityNameIDMap[("Item_Weapon_MG3_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|MG3", EItemType::MG3);
		EntityNameIDMap[("Item_Weapon_JS9_C")] = EntityNameIDTypeMap(EntityType::ǹе, ��ɫ, u8"|JS9", EItemType::JS9);





	}
	/*���*/
	{
		EntityNameIDMap[("Item_Attach_Weapon_Upper_Aimpoint_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_Scope3x_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_CQBSS_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|�˱���", EItemType::�˱���);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_ACOG_01_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|�ı���", EItemType::�ı���);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_Scope6x_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_PM2_01_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|ʮ�屶��", EItemType::ʮ�屶��);
		EntityNameIDMap[("Item_Attach_Weapon_Lower_Foregrip_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|��ֱ", EItemType::��ֱ);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_Holosight_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|ȫϢ", EItemType::ȫϢ);
		EntityNameIDMap[("Item_Attach_Weapon_Upper_DotSight_01_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|���", EItemType::���);
		EntityNameIDMap[("Item_Attach_Weapon_Stock_AR_Composite_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|ǹ��", EItemType::ǹ��);
		EntityNameIDMap[("Item_Attach_Weapon_Muzzle_Suppressor_Large_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|ǹ��", EItemType::ǹ��);
		EntityNameIDMap[("Item_Attach_Weapon_Magazine_Extended_Large_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|����", EItemType::����);
		EntityNameIDMap[("Item_Attach_Weapon_Muzzle_Compensator_Large_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|ǹ��", EItemType::ǹ��);
		EntityNameIDMap[("Item_Attach_Weapon_Stock_SniperRifle_CheekPad_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|����", EItemType::����);
		EntityNameIDMap[("Item_Attach_Weapon_Magazine_Extended_SniperRifle_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|����", EItemType::����);
		EntityNameIDMap[("Item_Attach_Weapon_Muzzle_Suppressor_SniperRifle_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|����", EItemType::����);
		EntityNameIDMap[("Item_Attach_Weapon_Muzzle_Compensator_SniperLarge_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|�Ѳ�", EItemType::�Ѳ�);
		EntityNameIDMap[("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_Large_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|����", EItemType::����);
		EntityNameIDMap[("Item_Attach_Weapon_Magazine_ExtendedQuickDraw_SniperRifle_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|����", EItemType::����);
		//EntityNameIDMap[("Tiger_Key_C")] = EntityNameIDTypeMap(EntityType::���, ��ɫ, u8"|����Կ��", EItemType::����Կ��);
		
	}

	/*����*/
	{
		EntityNameIDMap[("Item_Ghillie_01_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Ghillie_02_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Ghillie_03_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Ghillie_04_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Head_F_02_Lv2_C")] = EntityNameIDTypeMap(EntityType::����, ����, u8"|��ͷ��", EItemType::��ͷ��);
		EntityNameIDMap[("Item_Head_F_01_Lv2_C")] = EntityNameIDTypeMap(EntityType::����, ����, u8"|��ͷ��", EItemType::��ͷ��);
		EntityNameIDMap[("Item_Head_G_01_Lv3_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|��ͷ��", EItemType::��ͷ��);
		EntityNameIDMap[("Item_Back_E_01_Lv1_C")] = EntityNameIDTypeMap(EntityType::����, ����, u8"|һ����", EItemType::һ����);
		EntityNameIDMap[("Item_Back_E_02_Lv1_C")] = EntityNameIDTypeMap(EntityType::����, ����, u8"|һ����", EItemType::һ����);
		EntityNameIDMap[("Item_Back_F_01_Lv2_C")] = EntityNameIDTypeMap(EntityType::����, ����, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Back_F_02_Lv2_C")] = EntityNameIDTypeMap(EntityType::����, ����, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Back_C_01_Lv3_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Back_C_02_Lv3_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Back_BlueBlocker")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Armor_D_01_Lv1_C")] = EntityNameIDTypeMap(EntityType::����, ����, u8"|һ����", EItemType::һ����);
		EntityNameIDMap[("Item_Armor_D_01_Lv2_C")] = EntityNameIDTypeMap(EntityType::����, ����, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_Armor_C_01_Lv3_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|������", EItemType::������);
		EntityNameIDMap[("Item_EmergencyPickup_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"|������", EItemType::������);



	}
	/*ҩƷ*/
	{

		EntityNameIDMap[("Item_Heal_MedKit_C")] = EntityNameIDTypeMap(EntityType::ҩƷ, ��ɫ, u8"|ҽ����", EItemType::ҽ����);
		EntityNameIDMap[("Item_Heal_FirstAid_C")] = EntityNameIDTypeMap(EntityType::ҩƷ, ��ɫ, u8"|���Ȱ�", EItemType::���Ȱ�);
		EntityNameIDMap[("Item_Boost_PainKiller_C")] = EntityNameIDTypeMap(EntityType::ҩƷ, ��ɫ, u8"|ֹ��", EItemType::ֹ��);
		EntityNameIDMap[("Item_Boost_EnergyDrink_C")] = EntityNameIDTypeMap(EntityType::ҩƷ, ��ɫ, u8"|����", EItemType::����);
		EntityNameIDMap[("Item_Weapon_VendingMachine_C")] = EntityNameIDTypeMap(EntityType::ҩƷ, ��ɫ, u8"|�ۻ���", EItemType::�ۻ���);
		EntityNameIDMap[("Item_Boost_AdrenalineSyringe_C")] = EntityNameIDTypeMap(EntityType::ҩƷ, ��ɫ, u8"|��������", EItemType::��������);
		EntityNameIDMap[("Item_Heal_Bandage_C")] = EntityNameIDTypeMap(EntityType::ҩƷ, ��ɫ, u8"|����", EItemType::����);

	}
	/*Ͷ��*/
	{


		EntityNameIDMap[("Item_Weapon_Grenade_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ��ɫ, u8"|����", EItemType::����);
		EntityNameIDMap[("Weapon_StickyGrenade_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ��ɫ, u8"|C4ը��", EItemType::C4ը��);
		EntityNameIDMap[("Item_Weapon_C4_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ��ɫ, u8"|C4ը��", EItemType::C4ը��);
		EntityNameIDMap[("Item_Weapon_SmokeBomb_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ��ɫ, u8"|����", EItemType::����);
		EntityNameIDMap[("Item_Weapon_Molotov_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ��ɫ, u8"|����", EItemType::����);
		EntityNameIDMap[("Item_Weapon_BluezoneGrenade_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ��ɫ, u8"|��Ȧ����", EItemType::��Ȧ����);
		EntityNameIDMap[("Item_Weapon_StickyGrenade_C")] = EntityNameIDTypeMap(EntityType::Ͷ��, ��ɫ, u8"���ը��", EItemType::���ը��);
		//�·���Ͷ������������
		EntityNameIDMap[("ProjGrenade_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, ��ɫ, u8"|С������", EItemType::UnKnown);
		EntityNameIDMap[("ProjC4_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, ��ɫ, u8"С��C4", EItemType::UnKnown);
		EntityNameIDMap[("ProjStickyGrenade_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, ��ɫ, u8"|С��C4", EItemType::UnKnown);
		EntityNameIDMap[("ProjFlashBang_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, ��ɫ, u8"|С�����ⵯ", EItemType::UnKnown);
		EntityNameIDMap[("ProjMolotov_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, ��ɫ, u8"|С��ȼ�յ�", EItemType::UnKnown);
		EntityNameIDMap[("ProjBluezoneGrenade_C")] = EntityNameIDTypeMap(EntityType::ProGrenade, ��ɫ, u8"|С����Ȧ����", EItemType::UnKnown);

	}
	/*��Ͷ����*/
	{
		EntityNameIDMap[("DeathDropItemPackage_C")] = EntityNameIDTypeMap(EntityType::����, �Ȼ�, u8"��������", EItemType::��������);
		EntityNameIDMap[("Carapackage_RedBox_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"��Ͷ����", EItemType::��Ͷ����);
		EntityNameIDMap[("Carapackage_FlareGun_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"������Ͷ", EItemType::������Ͷ);
		EntityNameIDMap[("Carapackage_SmallPackage_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"С��Ͷ��", EItemType::С��Ͷ��);
		EntityNameIDMap[("Carapackage_RedBox_COL_C")] = EntityNameIDTypeMap(EntityType::����, ��ɫ, u8"��Ͷ����", EItemType::��Ͷ����);
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
