#include "CThread.h"
namespace CThread
{
	void Cache线程()
	{
		while (true)
		{
			if (!G::engine->GameData())
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
		return;
	}


	void 获取数据()
	{
		bool Decrypt = false;
		std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator IDTypeMapIt = std::unordered_map<ULONG, Game::EntityNameIDTypeMap>::iterator();
		分散.LastVehiclePawn = G::Mem.ScatterInitialize(3);
		分散.结构分散 = G::Mem.ScatterInitialize(3);
		分散.结构临时分散 = G::Mem.ScatterInitialize(3);
		分散.本人分散 = G::Mem.ScatterInitialize(3);
		分散.载具分散 = G::Mem.ScatterInitialize(3);
		分散.物品分散 = G::Mem.ScatterInitialize(3);
		分散.盒子分散 = G::Mem.ScatterInitialize(3);
		分散.地面物品分散 = G::Mem.ScatterInitialize(3);
		分散.雷达分散 = G::Mem.ScatterInitialize(3);
		分散.ScatterDebug = G::Mem.ScatterInitialize(3);



		/*  初始化太快了 */



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
				printf(E("缓存完成!\n"));
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
				//if (IDTypeMapIt->second.Type == Game::EntityType::游戏內)
				//{

				//	//printf("游戏内\n");
				//}

				//if (IDTypeMapIt->second.Type == Game::EntityType::大厅)
				//{
				//	//printf("大厅内\n");
				//	Data.游戏状态 = false;
				//	Data.游戏数据 = false;
				//}
				Data.游戏状态 = true;
				Data.游戏数据 = true;
				if (Data.游戏状态 && Data.游戏数据)
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

				G::Mem.ScatterClear(分散.雷达分散, 1);
				if (Data.UWorld > 65536)
				{
					G::Mem.ScatterPrepare(分散.雷达分散, Data.UWorld + offsets::世界转小地图, sizeof(ULONG));
					G::Mem.ScatterPrepare(分散.雷达分散, Data.UWorld + offsets::世界转小地图 + 0x4, sizeof(ULONG));
				}
				if (Local.TslBaseHUD > 65536)
					G::Mem.ScatterPrepare(分散.雷达分散, Local.TslBaseHUD + offsets::WidgetStateMap, sizeof(TMap<FString, FTslWidgetState>));


				G::Mem.ExecuteRead(分散.雷达分散);
				if (Data.UWorld > 65536)
				{
					Local.地图X = G::Mem.分散读写<ULONG>(分散.雷达分散, Data.UWorld + offsets::世界转小地图);
					Local.地图Y = G::Mem.分散读写<ULONG>(分散.雷达分散, Data.UWorld + offsets::世界转小地图 + 0x4);
				}

				if (Local.TslBaseHUD > 65536)
				{
					auto WidgetStateMap = G::Mem.分散读写<TMap<FString, FTslWidgetState>>(分散.雷达分散, Local.TslBaseHUD + offsets::WidgetStateMap);
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
								//printf("真\n");
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
								//printf("真\n");
								Local.WorldMapZoomFactor = SDK::Map::GetZoomFactor(MapGrid);
								Local.WorldMapPosition = SDK::Map::GetPosition(MapGrid);

							}
							if (WidgetPtrName == E("MinimapOriginalType_C")) {
								Local.bRadarExtended = G::Mem.Read<int>(Value.Widget + offsets::SelectMinimapSizeIndex) > 0;
								//printf("真\n");
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
			if (Data.游戏状态 && Data.游戏数据 && Local.AcknowledgedPawn > 65536)
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
				//printf("当前武器MING %s\n", SDK::GetNames(WeaponObjID).c_str());

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
					//printf("当前武器 %s\n", Local.LoaclWeaponData.WeaponName);
					//Local.LoaclWeaponData.TrajectoryGravityZ = G::Mem.ReadEx<FLOAT>(LocalWeaponPtr + offsets::TrajectoryGravityZ);
					Local.LoaclWeaponData.TrajectoryConfig = G::Mem.ReadEx<FWeaponTrajectoryConfig>(WeaponTrajectoryData + offsets::TrajectoryConfig);
					Local.LoaclWeaponData.WeaponInitialSpeed = SDK::GetAimSpeed();
					//Local.LoaclWeaponData.WeaponBullet = G::Mem.ReadEx<ULONG>(LocalWeaponPtr + offsets::子弹数量);
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

			if (Data.游戏状态 && Data.游戏数据)
			{
				if (Local.PlayerCameraManager)
				{
					G::Mem.ScatterClear(分散.本人分散, 1);

					if (Local.PlayerController > 65536)
					{
						G::Mem.ScatterPrepare(分散.本人分散, Local.PlayerController + offsets::地图判断, sizeof(ULONG));
					}
					if (Local.AnimScript > 65536)
					{
						G::Mem.ScatterPrepare(分散.本人分散, Local.AnimScript + offsets::ControlRotation_CP, sizeof(FVector));
						G::Mem.ScatterPrepare(分散.本人分散, Local.AnimScript + offsets::RecoilADSRotation_CP, sizeof(FVector));
						//G::Mem.ScatterPrepare(分散.本人分散, Local.AnimScript + offsets::LeanLeftAlpha_CP, sizeof(float));
						//G::Mem.ScatterPrepare(分散.本人分散, Local.AnimScript + offsets::LeanRightAlpha_CP, sizeof(float));
					}

					if (Local.PlayerCameraManager > 65536)
					{
						G::Mem.ScatterPrepare(分散.本人分散, Local.PlayerCameraManager + offsets::CameraFov, sizeof(float));
						G::Mem.ScatterPrepare(分散.本人分散, Local.PlayerCameraManager + offsets::CameraPos, sizeof(FVector));
						G::Mem.ScatterPrepare(分散.本人分散, Local.PlayerCameraManager + offsets::CameraRot, sizeof(FVector));
					}
					if (Local.AcknowledgedPawn > 65536)
					{
						G::Mem.ScatterPrepare(分散.本人分散, Local.AcknowledgedPawn + offsets::TeamNumber, sizeof(int));
						G::Mem.ScatterPrepare(分散.本人分散, Local.AcknowledgedPawn + offsets::Audience, sizeof(int));
					}
					G::Mem.ExecuteRead(分散.本人分散);

					if (Local.AnimScript > 65536)
					{
						Local.ControlRotation = G::Mem.分散读写<FVector>(分散.本人分散, Local.AnimScript + offsets::ControlRotation_CP);
						Local.RecoilADSRotation = G::Mem.分散读写<FVector>(分散.本人分散, Local.AnimScript + offsets::RecoilADSRotation_CP);
						//Local.LeanLeft = G::Mem.分散读写<float>(分散.本人分散, Local.AnimScript + offsets::LeanLeftAlpha_CP);
						//Local.LeanRight = G::Mem.分散读写<float>(分散.本人分散, Local.AnimScript + offsets::LeanRightAlpha_CP);
					}
					if (Local.PlayerController > 65536)
					{
						Local.地图判断 = G::Mem.分散读写<ULONG>(分散.本人分散, Local.PlayerController + offsets::地图判断);

					}
					if (Local.PlayerCameraManager > 65536)
					{
						Local.CameraFov = G::Mem.分散读写<float>(分散.本人分散, Local.PlayerCameraManager + offsets::CameraFov);
						Local.Tangent = tan(Local.CameraFov * (float)M_PI / 360.0f);
						Local.CameraPos = G::Mem.分散读写<FVector>(分散.本人分散, Local.PlayerCameraManager + offsets::CameraPos);
						//printf("%f %f %f\n", Local.CameraPos.x, Local.CameraPos.y, Local.CameraPos.z);
						Local.CameraRotPos = G::Mem.分散读写<FVector>(分散.本人分散, Local.PlayerCameraManager + offsets::CameraRot);
					}
					if (Local.AcknowledgedPawn > 65536)
					{
						Local.Teamid = G::Mem.分散读写<int>(分散.本人分散, Local.AcknowledgedPawn + offsets::TeamNumber);
						if (Local.Teamid >= 100000) { Local.Teamid -= 100000; }

						Local.观战人数 = G::Mem.分散读写<int>(分散.本人分散, Local.AcknowledgedPawn + offsets::Audience);
					}


					GetAxes(Local.CameraRotPos, &Local.AxisX, &Local.AxisY, &Local.AxisZ);
				}
			}
		}
	}
}