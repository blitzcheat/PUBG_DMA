#include "CThread.h"
namespace CThread
{
	void Cache�߳�()
	{
		while (true)
		{
			if (!G::engine->GameData())
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		return;
	}


	void ��ȡ����()
	{
		bool Decrypt = false;
		std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator IDTypeMapIt = std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator();
		��ɢ.LastVehiclePawn = G::Mem.ScatterInitialize(3);
		��ɢ.�ṹ��ɢ = G::Mem.ScatterInitialize(3);
		��ɢ.�ṹ��ʱ��ɢ = G::Mem.ScatterInitialize(3);
		��ɢ.���˷�ɢ = G::Mem.ScatterInitialize(3);
		��ɢ.�ؾ߷�ɢ = G::Mem.ScatterInitialize(3);
		��ɢ.��Ʒ��ɢ = G::Mem.ScatterInitialize(3);
		��ɢ.���ӷ�ɢ = G::Mem.ScatterInitialize(3);
		��ɢ.������Ʒ��ɢ = G::Mem.ScatterInitialize(3);
		��ɢ.�״��ɢ = G::Mem.ScatterInitialize(3);
		��ɢ.ScatterDebug = G::Mem.ScatterInitialize(3);



		/*  ��ʼ��̫���� */



		while (Data.ShieldPtr == 0)
		{
			Data.ShieldPtr = G::Mem.Read<uintptr_t>(G::Mem.GameBase + offsets::Shield);
			SDK::DecryptInit(Data.ShieldPtr);
		}
		//printf("%p\n", Data.ShieldPtr);


		while (!Decrypt)
		{
			Data.GNames = SDK::GetGNames();
			Game::InitNameTypeMap();
			if (Game::EntityIDTypeMap.empty() == false)
			{
				printf(E("�������!\n"));
				Decrypt = true;
			}
			else
			{
				Decrypt = false;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}



		while (true)
		{
			if (Decrypt)
			{
				Data.UWorld = SDK::GetUWorld();

				auto UWorldID = SDK::DecryptID(Data.UWorld);

				Game::Mapname = SDK::GetNames(UWorldID);
				//IDTypeMapIt = Game::EntityIDTypeMap.find(UWorldID);
				//if (IDTypeMapIt == Game::EntityIDTypeMap.end()) { continue; }
				//if (IDTypeMapIt->second.Type == Game::EntityType::��Ϸ��)
				//{

				//	//printf("��Ϸ��\n");
				//}

				//if (IDTypeMapIt->second.Type == Game::EntityType::����)
				//{
				//	//printf("������\n");
				//	Data.��Ϸ״̬ = false;
				//	Data.��Ϸ���� = false;
				//}
				Data.��Ϸ״̬ = true;
				Data.��Ϸ���� = true;
				if (Data.��Ϸ״̬ && Data.��Ϸ����)
				{
					Data.ULevel = SDK::GetPersistent(Data.UWorld);

					Data.Actors = SDK::GetActors(Data.ULevel);

					Data.GameInstance = SDK::GetGameInstance(Data.UWorld);

					Local.PlayerController = SDK::GetPlayerController(Data.GameInstance);
					if (Local.PlayerController > 65536)
					{
						Local.AcknowledgedPawn = SDK::GetAcknowledgedPawn(Local.PlayerController);
						Local.PlayerCameraManager = SDK::GetCameraManager(Local.PlayerController);
						Local.TslBaseHUD = G::Mem.Read<uintptr_t>(Local.PlayerController + offsets::MyHUD);
						if (Local.AcknowledgedPawn > 65536)
						{
							//printf("AcknowledgedPawn %p\n", Local.AcknowledgedPawn);
							Local.Mesh = G::Mem.Read<uintptr_t>(Local.AcknowledgedPawn + offsets::Mesh);
							Local.AnimScript = G::Mem.Read<uintptr_t>(Local.Mesh + offsets::AnimScriptInstance);
						}
					}


				}
				std::this_thread::sleep_for(std::chrono::milliseconds(50));
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(100));


	}
	void RadarData()
	{
		while (true)
		{
			if (Local.TslBaseHUD)
			{

				G::Mem.ScatterClear(��ɢ.�״��ɢ, 1);
				if (Data.UWorld > 65536)
				{
					G::Mem.ScatterPrepare(��ɢ.�״��ɢ, Data.UWorld + offsets::����תС��ͼ, sizeof(ULONG));
					G::Mem.ScatterPrepare(��ɢ.�״��ɢ, Data.UWorld + offsets::����תС��ͼ + 0x4, sizeof(ULONG));
				}
				if (Local.TslBaseHUD > 65536)
					G::Mem.ScatterPrepare(��ɢ.�״��ɢ, Local.TslBaseHUD + offsets::WidgetStateMap, sizeof(TMap<FString, FTslWidgetState>));


				G::Mem.ExecuteRead(��ɢ.�״��ɢ);
				if (Data.UWorld > 65536)
				{
					Local.��ͼX = G::Mem.��ɢ��д<ULONG>(��ɢ.�״��ɢ, Data.UWorld + offsets::����תС��ͼ);
					Local.��ͼY = G::Mem.��ɢ��д<ULONG>(��ɢ.�״��ɢ, Data.UWorld + offsets::����תС��ͼ + 0x4);
				}

				if (Local.TslBaseHUD > 65536)
				{
					auto WidgetStateMap = G::Mem.��ɢ��д<TMap<FString, FTslWidgetState>>(��ɢ.�״��ɢ, Local.TslBaseHUD + offsets::WidgetStateMap);
					for (auto& Elem : WidgetStateMap.GetVector()) {
						auto& Key = Elem.Value.Key;
						auto& Value = Elem.Value.Value;
						if (Value.Widget <= 65536)continue;
						auto WidgetPtrName = SDK::GetNames(SDK::DecryptID(Value.Widget));

						if (!WidgetPtrName.empty() && WidgetPtrName != E("Unknown"))
						{
							//printf("WidgetPtrName %s\n", WidgetPtrName.c_str());
							if (WidgetPtrName == E("NewWorldMapWidget_BP_C"))
							{
								auto MapGrid = G::Mem.Read<ULONG64>(Value.Widget + offsets::TrainingMapGrid + 0x30);
								if (!MapGrid || 0xFFFFFFFF == MapGrid)continue;

								Local.bWorldMap = SDK::Map::IsVisible(Value.Widget, MapGrid);
								if (!Local.bWorldMap)
									continue;
								//printf("��\n");
								Local.WorldMapZoomFactor = SDK::Map::GetZoomFactor(MapGrid);
								Local.WorldMapPosition = SDK::Map::GetPosition(MapGrid);

							}
							if (WidgetPtrName == E("UI_TrainingWorldMapWidget_C"))
							{
								//printf("Value.Widget %p\n", Value.Widget);
								auto MapGrid = G::Mem.Read<ULONG64>(Value.Widget + offsets::TrainingMapGrid);
								if (!MapGrid || 0xFFFFFFFF == MapGrid)continue;
								Local.bWorldMap = SDK::Map::IsVisible(Value.Widget, MapGrid);
								if (!Local.bWorldMap)
									continue;
								//printf("��\n");
								Local.WorldMapZoomFactor = SDK::Map::GetZoomFactor(MapGrid);
								Local.WorldMapPosition = SDK::Map::GetPosition(MapGrid);

							}
							if (WidgetPtrName == E("MinimapOriginalType_C")) {
								Local.bRadarExtended = G::Mem.Read<int>(Value.Widget + offsets::SelectMinimapSizeIndex) > 0;
								//printf("��\n");
							}
							//printf("%f %f\n", Local.WorldMapPosition.X, Local.WorldMapPosition.Y);

						}

					}
				}

			}

			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
	}
	void GetPlayerWeaponData()
	{
		while (true)
		{
			if (Data.��Ϸ״̬ && Data.��Ϸ���� && Local.AcknowledgedPawn > 65536)
			{
				std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator IDTypeMapIt = std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator();
				ULONG_PTR WeaponProcessor = G::Mem.Read<ULONG_PTR>(Local.AcknowledgedPawn + offsets::WeaponProcessor);
				if (WeaponProcessor <= 65536) return;

				ULONG_PTR EquippedWeapons = G::Mem.Read<ULONG_PTR>(WeaponProcessor + offsets::EquippedWeapons);
				if (EquippedWeapons <= 65536) return;
				BYTE WeaponIndex = G::Mem.Read<BYTE>(WeaponProcessor + offsets::CurrentWeaponIndex);
				ULONG_PTR LocalWeaponPtr = G::Mem.Read<ULONG_PTR>(EquippedWeapons + (WeaponIndex * 8));
				if (LocalWeaponPtr <= 65536) return;
				ULONG_PTR WeaponTrajectoryData = G::Mem.Read<ULONG_PTR>(LocalWeaponPtr + offsets::WeaponTrajectoryData);
				if (WeaponTrajectoryData <= 65536) return;
				ULONG WeaponObjID = SDK::DecryptIndex(G::Mem.Read<ULONG>(LocalWeaponPtr + offsets::OBJid)); if (WeaponObjID <= 0 && WeaponObjID >= 1000000);
				//printf("��ǰ����MING %s\n", SDK::GetNames(WeaponObjID).c_str());

				IDTypeMapIt = Game::EntityIDTypeMap.find(WeaponObjID);
				if (IDTypeMapIt == Game::EntityIDTypeMap.end())
				{
					Local.LoaclWeaponData.WeaponMap = false;
				}
				else
				{
					Local.LoaclWeaponData.WeaponMap = true;
				}
				if (Local.LoaclWeaponData.WeaponMap)
				{
					Local.LoaclWeaponData.WeaponName = IDTypeMapIt->second.Name;
					//printf("��ǰ���� %s\n", Local.LoaclWeaponData.WeaponName);
					//Local.LoaclWeaponData.TrajectoryGravityZ = G::Mem.ReadEx<FLOAT>(LocalWeaponPtr + offsets::TrajectoryGravityZ);
					Local.LoaclWeaponData.TrajectoryConfig = G::Mem.ReadEx<FWeaponTrajectoryConfig>(WeaponTrajectoryData + offsets::TrajectoryConfig);
					Local.LoaclWeaponData.WeaponInitialSpeed = SDK::GetAimSpeed();
					//Local.LoaclWeaponData.WeaponBullet = G::Mem.ReadEx<ULONG>(LocalWeaponPtr + offsets::�ӵ�����);
					Local.LoaclWeaponData.WeaponHold = TRUE;
				}
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}



	}

	void GetPlayerData()
	{
		while (true)
		{

			if (Data.��Ϸ״̬ && Data.��Ϸ����)
			{
				if (Local.PlayerCameraManager)
				{
					G::Mem.ScatterClear(��ɢ.���˷�ɢ, 1);

					if (Local.PlayerController > 65536)
					{
						G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.PlayerController + offsets::��ͼ�ж�, sizeof(ULONG));
					}
					if (Local.AnimScript > 65536)
					{
						G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.AnimScript + offsets::ControlRotation_CP, sizeof(FVector));
						G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.AnimScript + offsets::RecoilADSRotation_CP, sizeof(FVector));
						//G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.AnimScript + offsets::LeanLeftAlpha_CP, sizeof(float));
						//G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.AnimScript + offsets::LeanRightAlpha_CP, sizeof(float));
					}

					if (Local.PlayerCameraManager > 65536)
					{
						G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.PlayerCameraManager + offsets::CameraFov, sizeof(float));
						G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.PlayerCameraManager + offsets::CameraPos, sizeof(FVector));
						G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.PlayerCameraManager + offsets::CameraRot, sizeof(FVector));
					}
					if (Local.AcknowledgedPawn > 65536)
					{
						G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.AcknowledgedPawn + offsets::TeamNumber, sizeof(int));
						G::Mem.ScatterPrepare(��ɢ.���˷�ɢ, Local.AcknowledgedPawn + offsets::Audience, sizeof(int));
					}
					G::Mem.ExecuteRead(��ɢ.���˷�ɢ);

					if (Local.AnimScript > 65536)
					{
						Local.ControlRotation = G::Mem.��ɢ��д<FVector>(��ɢ.���˷�ɢ, Local.AnimScript + offsets::ControlRotation_CP);
						Local.RecoilADSRotation = G::Mem.��ɢ��д<FVector>(��ɢ.���˷�ɢ, Local.AnimScript + offsets::RecoilADSRotation_CP);
						//Local.LeanLeft = G::Mem.��ɢ��д<float>(��ɢ.���˷�ɢ, Local.AnimScript + offsets::LeanLeftAlpha_CP);
						//Local.LeanRight = G::Mem.��ɢ��д<float>(��ɢ.���˷�ɢ, Local.AnimScript + offsets::LeanRightAlpha_CP);
					}
					if (Local.PlayerController > 65536)
					{
						Local.��ͼ�ж� = G::Mem.��ɢ��д<ULONG>(��ɢ.���˷�ɢ, Local.PlayerController + offsets::��ͼ�ж�);

					}
					if (Local.PlayerCameraManager > 65536)
					{
						Local.CameraFov = G::Mem.��ɢ��д<float>(��ɢ.���˷�ɢ, Local.PlayerCameraManager + offsets::CameraFov);
						Local.Tangent = tan(Local.CameraFov * (float)M_PI / 360.0f);
						Local.CameraPos = G::Mem.��ɢ��д<FVector>(��ɢ.���˷�ɢ, Local.PlayerCameraManager + offsets::CameraPos);
						//printf("%f %f %f\n", Local.CameraPos.x, Local.CameraPos.y, Local.CameraPos.z);
						Local.CameraRotPos = G::Mem.��ɢ��д<FVector>(��ɢ.���˷�ɢ, Local.PlayerCameraManager + offsets::CameraRot);
					}
					if (Local.AcknowledgedPawn > 65536)
					{
						Local.Teamid = G::Mem.��ɢ��д<int>(��ɢ.���˷�ɢ, Local.AcknowledgedPawn + offsets::TeamNumber);
						if (Local.Teamid >= 100000) { Local.Teamid -= 100000; }

						Local.��ս���� = G::Mem.��ɢ��д<int>(��ɢ.���˷�ɢ, Local.AcknowledgedPawn + offsets::Audience);
					}


					GetAxes(Local.CameraRotPos, &Local.AxisX, &Local.AxisY, &Local.AxisZ);
				}
			}
		}
	}
}