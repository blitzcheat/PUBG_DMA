#include "Render.h"
#include <cstdarg>

#include "Engine.h"
#include "Memory.h"
#include "util.hpp"
#include "CThread.h"

using namespace CThread;

void Render::Init()//绘制已处理完成的数据 UE
{
	if (Local.观战人数 > 0)
	{
		绘制文本(60, 80, TXT_CENTERX, ImColor(255, 0, 0), u8"当前观战人数:%d", Local.观战人数);
	}
	//绘制线条({ (float)F::Global.GameData.新窗口X + 10,(float)F::Global.GameData.新窗口Y + 10 }, { (float)F::Global.GameData.新窗口X + 10,(float)F::Global.GameData.新窗口Y + 1070 }, ImColor(255, 255, 155), 2.0f);	
	float 敌人到准星距离 = 0;
	F::Global.Aim.自瞄血量 = 0;
	Base_Radar Radar;
	RadarSetting(Radar);
	
	if (F::Global.Menu.Debug) return;

	for (auto Temp : this->处理好的玩家数组)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;	

		

		if (F::Global.Menu.雷达)
			Radar.AddPoint(Local.CameraPos, Local.ControlRotation.y, Temp.Location, ImColor(237, 85, 106, 200), F::Global.Menu.RadarType, Temp.敌人朝向 - 90);

		if (
			SDK::WorldScreen(Temp.HeadLoc, &Screen, &Distance)
			&& SDK::WorldScreen(Temp.RootLoc, &Screen2, &Distance)
			)
		{
			Box bbox{};
			bbox.x = Screen.X - (Screen2.Y - Screen.Y) / 2;
			bbox.y = Screen.Y - (Screen2.Y - Screen.Y) / 4;

			bbox.w = Screen2.Y - Screen.Y;
			bbox.h = bbox.w * 2 - bbox.w / 1.26;

			if (F::Global.Menu.玩家信息) {
				draw::绘制文本(Screen2.X, Screen2.Y, TXT_CENTERX, Temp.是否倒地 ? ImVec4(255, 255, 255, 255) : Temp.TeamColor, u8"%ws  [%.0f]\n T:%d | A:%d | K:%d",
					Temp.Name.c_str(), Distance, Temp.Teamid, Temp.Audience, Temp.Kill);
			}
			if (F::Global.Menu.玩家血条) {
				draw::横向血条((int)bbox.x, (int)bbox.y, (int)bbox.w,(int)bbox.h, Temp.Health, 100);
			}
			
			if (true/*Local.LoaclWeaponData.WeaponMap*/) {
				//BOOL PlayerDie = Temp.Health <= 0.f || Temp.Health > 100.f;
				if (/*!PlayerDie*/ true)//攻击倒地
				{
					FVector 自瞄预判坐标 = Local.LoaclWeaponData.WeaponMap ? SDK::PredictedPosition(Temp.PlayerVelocity, Temp.PlayerVelocityUp, Distance) : FVector{};
					自瞄预判坐标 += Temp.自瞄坐标;
					float AimDistance;
					FVector2 ScreenPos{};
					if (SDK::WorldScreen(自瞄预判坐标, &ScreenPos, &AimDistance))
					{
						if (F::Global.Aim.锁定 == false)
						{
							敌人到准星距离 = ScreenPos.DistanceTo({ (float)F::Global.GameData.Width, (float)F::Global.GameData.Height });
							if (敌人到准星距离 <= F::Global.Aim.屏幕当前)
							{
								F::Global.Aim.自瞄地址 = Temp.pActor;
								F::Global.Aim.屏幕当前 = 敌人到准星距离;
								F::Global.Aim.自瞄坐标 = 自瞄预判坐标;
								F::Global.Aim.自瞄血量 = Temp.Health;
							}
						}
						else//按下自瞄键后
						{
							if (Temp.pActor == F::Global.Aim.自瞄地址)
							{
								F::Global.Aim.屏幕当前 = 敌人到准星距离;
								F::Global.Aim.自瞄坐标 = 自瞄预判坐标;
								F::Global.Aim.自瞄血量 = Temp.Health;
								//printf("%.0f %.0f %.0f\n", F::Global.Aim.自瞄坐标.x, F::Global.Aim.自瞄坐标.y, F::Global.Aim.自瞄坐标.z);
							}
						}


					}
				}
			}


			if (F::Global.KeyBind.战斗模式)
			{
				continue;
			}
			if (F::Global.Menu.玩家方框) {
				draw::DrawRect((int)bbox.x, (int)bbox.y, (int)bbox.w, (int)bbox.h, Temp.是否倒地 ? ImColor(255,255,255) : ImColor(255, 255, 0), 1);
			}
			if (F::Global.Menu.玩家射线) {
				draw::绘制线条({ F::Global.GameData.Width + 0.f,F::Global.GameData.Height * 4.f }, { Screen2.X, Screen2.Y }, Temp.是否倒地 ? ImColor(255, 255, 255) : ImColor(255, 255, 0), 1.0f);
			}



		}
		if (F::Global.Menu.地图雷达 && !F::Global.KeyBind.战斗模式)
		{
			float MapSize = 0.0f;
			if (Game::Mapname == "Tiger_Main" || Game::Mapname == "Desert_Main" || Game::Mapname == "Kiki_Main")
				MapSize = 408000.f;
			else if (Game::Mapname == "Range_Main")
				MapSize = 101175.f;
			else if (Game::Mapname == "Baltic_Main")
				MapSize = 406387.5;
			else if (Game::Mapname == "Heaven_Main")
				MapSize = 51420.f;
			else if (Game::Mapname == "Savage_Main")
				MapSize = 202387.5f;
			else if (Game::Mapname == "DihorOtok_Main")
				MapSize = 306050.f;
			else if (Game::Mapname == "Chimera_Main")
				MapSize = 152950.f;
			constexpr float Size = 8.0f;
			if (Local.bWorldMap)
			{
				auto map = SDK::Map::DrawMap(Temp.Location, MapSize);
				FVector GunDir = FRotator(0.0f, Temp.敌人朝向, 0.0f).GetUnitVector();

				float Degree90 = ConvertToRadians(90.0f);
				FVector Dir1 = {
								GunDir.x * cosf(Degree90) - GunDir.y * sinf(Degree90),
								GunDir.x * sinf(Degree90) + GunDir.y * cosf(Degree90),
								0.0f };

				FVector Dir2 = {
								GunDir.x * cosf(-Degree90) - GunDir.y * sinf(-Degree90),
								GunDir.x * sinf(-Degree90) + GunDir.y * cosf(-Degree90),
								0.0f };
				auto RadarScreenPos = FVector(map.X, map.Y, 0);

				for (size_t i = 0; i < 3; i++)
				{
					FVector p1 = RadarScreenPos + GunDir * (Size - i) * 2.0f;
					FVector p2 = RadarScreenPos + Dir1 * (Size - i);
					FVector p3 = RadarScreenPos + Dir2 * (Size - i);

					draw::绘制线条({ p1.x, p1.y }, { p2.x, p2.y }, 2, ImColor(255, 0, 0));
					draw::绘制线条({ p2.x, p2.y }, { p3.x, p3.y }, 2, ImColor(255, 0, 0));
					draw::绘制线条({ p3.x, p3.y }, { p1.x, p1.y }, 2, ImColor(255, 0, 0));
				}
				CircleFilled(map.X, map.Y, Size, Temp.是否倒地 ? ImColor(255, 255, 255) : ImColor(255, 0, 0), 1);

				draw::绘制文本(map.X, map.Y, TXT_CENTERX, Temp.是否倒地 ? ImColor(255, 255, 255) : ImColor(255, 255, 0), "[T:%d]",Temp.Teamid);
			}
		}

		

	}

	for (auto Temp : this->bonedata)
	{
		FVector2 头部 = {}, 颈部 = {}, 骨盆 = {}, 左肩 = {}, 左肘 = {}, 左手 = {}, 右肩 = {}, 右肘 = {}, 右手 = {}, 左臀 = {}, 左膝 = {}, 左脚 = {}, 右臀 = {}, 右膝 = {}, 右脚 = {};
		float Distance;
		if (SDK::WorldScreen(Temp.头部, &头部 ,&Distance)
			&& SDK::WorldScreen(Temp.颈部, &颈部, &Distance)
			&& SDK::WorldScreen(Temp.骨盆, &骨盆, &Distance)
			&& SDK::WorldScreen(Temp.左肩, &左肩, &Distance)
			&& SDK::WorldScreen(Temp.左肘, &左肘, &Distance)
			&& SDK::WorldScreen(Temp.左手, &左手, &Distance)
			&& SDK::WorldScreen(Temp.右肩, &右肩, &Distance)
			&& SDK::WorldScreen(Temp.右肘, &右肘, &Distance)
			&& SDK::WorldScreen(Temp.右手, &右手, &Distance)
			&& SDK::WorldScreen(Temp.左臀, &左臀, &Distance)
			&& SDK::WorldScreen(Temp.左膝, &左膝, &Distance)
			&& SDK::WorldScreen(Temp.左脚, &左脚, &Distance)
			&& SDK::WorldScreen(Temp.右臀, &右臀, &Distance)
			&& SDK::WorldScreen(Temp.右膝, &右膝, &Distance)
			&& SDK::WorldScreen(Temp.右脚, &右脚, &Distance))
		{
			ImColor color = Temp.是否倒地 ? ImColor(255, 255, 255) : F::Global.Menu.骨骼颜色;
			int 骨骼粗细 = F::Global.Menu.骨骼粗细;
			//if (!头部.IsZero() && !左手.IsZero() && !右手.IsZero())
			{
				draw::绘制线条(头部, 颈部, color, 骨骼粗细);
				draw::绘制线条(颈部, 骨盆, color, 骨骼粗细);
				draw::绘制线条(左肩, 颈部, color, 骨骼粗细);
				draw::绘制线条(左肘, 左肩, color, 骨骼粗细);
				draw::绘制线条(左手, 左肘, color, 骨骼粗细);
				draw::绘制线条(右肩, 颈部, color, 骨骼粗细);
				draw::绘制线条(右肘, 右肩, color, 骨骼粗细);
				draw::绘制线条(右手, 右肘, color, 骨骼粗细);
				draw::绘制线条(左臀, 骨盆, color, 骨骼粗细);
				draw::绘制线条(左膝, 左臀, color, 骨骼粗细);
				draw::绘制线条(左脚, 左膝, color, 骨骼粗细);
				draw::绘制线条(右臀, 骨盆, color, 骨骼粗细);
				draw::绘制线条(右膝, 右臀, color, 骨骼粗细);
				draw::绘制线条(右脚, 右膝, color, 骨骼粗细);
			}
			
		}
	}
	if (F::Global.Menu.雷达)Radar.Render();

}

void Render::物品绘制()
{
	Game::DrawOverlay::ItemList.clear(); // 叠加数组
	if (F::Global.KeyBind.战斗模式) return;

	for (auto Temp : this->调试数组)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		//draw::绘制文本(Screen.X, Screen.Y, TXT_CENTERX, ImColor(255, 255, 0), "%s", Temp.Name.c_str());
		if (Distance > 100.f) continue;
		DrawItem(Temp.Name, Screen, Temp.Color, Distance);

	}
	if (F::Global.Menu.Debug) return;

	for (auto Temp : this->处理好的物品数组)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		if (Distance > 800.f) continue;
		DrawItem(Temp.Name, Screen,Temp.Color, Distance);
		//draw::绘制文本(Screen.X, Screen.Y, TXT_CENTERX, Temp.Color, u8"[%d %s %.0fm]",Temp.要区分的物品类型, Temp.Name.c_str(), Distance);

	}
	for (auto Temp : this->处理好的地面物品数组)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		if (Distance > 800.f) continue;
		DrawItem(Temp.Name, Screen, Temp.Color, Distance);
		//绘制文本(Screen.X, Screen.Y, TXT_CENTERX, Temp.Color, u8"[%s %.0fm]", Temp.Name.c_str(), Distance);
	}
	//printf("载具数组%d个\n", this->处理好的载具数组.size());
	for (auto Temp : this->处理好的载具数组)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		if (Distance > 800.f) continue;
		draw::绘制文本(Screen.X, Screen.Y, TXT_CENTERX, F::Global.Color.载具, u8"%s %.0fm", Temp.Name.c_str(), Distance);

	}
	int Index = 0;
	for (auto Temp : this->处理好的盒子数组)
	{
		Index+=1;
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		if (Distance > 800.f) continue;
		DrawItem(Temp.Name, { Screen.X,Screen.Y - 14 * Index }, Temp.Color,Distance);
		//绘制文本(Screen.X, Screen.Y - 14 * Index, TXT_CENTERX, F::Global.Color.载具, u8"[盒子]%s [%s] %.0fm", Temp.info[Index].名称.c_str(), Temp.Name.c_str(), Distance);

	}
	
	
}

void DecryptHealth(uint8_t* a1, unsigned int a2, unsigned int a3)
{
	unsigned int v4;
	char v5;
	int v7[16] = {};
	v7[0] = offsets::HealthKeyValue1;
	v4 = 0;
	v7[1] = offsets::HealthKeyValue2;
	v7[2] = offsets::HealthKeyValue3;
	v7[3] = offsets::HealthKeyValue4;
	v7[4] = offsets::HealthKeyValue5;
	v7[5] = offsets::HealthKeyValue6;
	v7[6] = offsets::HealthKeyValue7;
	v7[7] = offsets::HealthKeyValue8;
	v7[8] = offsets::HealthKeyValue9;
	v7[9] = offsets::HealthKeyValue10;
	v7[10] = offsets::HealthKeyValue11;
	v7[11] = offsets::HealthKeyValue12;
	v7[12] = offsets::HealthKeyValue13;
	v7[13] = offsets::HealthKeyValue14;
	v7[14] = offsets::HealthKeyValue15;

	//printf("a1 [%d]  \n",*a1);

	for (v7[15] = offsets::HealthKeyValue16; v4 < a2; ++a1)
	{
		v5 = v4++ + a3;
		int b = 10;
		b ^= *((uint8_t*)v7 + (12 & 0x3F));
		//printf("v7 + (v5 & 0x3F) [%d] [%d] b [%d]\n", *((uint8_t*)v7 + (12 & 0x3F)), *(uint8_t*)v7, b);
		*a1 ^= *((uint8_t*)v7 + (v5 & 0x3F));
		//printf("a [%d] v4 [%d] v7 [%d]  v5 [%d]  a3  [%d]   [%d]\n", *a1, v4, *(uint8_t*)v7, v5, a3, (v5 & 0x3F));

	}

	//printf("OK  \n");
}
float GetHealth(uint64_t ptr)
{
	bool v1 = false;
	float v2 = 0.0f;
	uint8_t v3 = 0;
	float v4 = 0.0f;
	if (G::Mem.分散读写<uint8_t>(分散.结构分散, ptr + offsets::AActorRole) == 3 || !G::Mem.分散读写<uint32_t>(分散.结构分散, ptr + offsets::CharacterId))
		v2 = G::Mem.分散读写<float>(分散.结构分散, ptr + offsets::Health5);
	else
	{
		v1 = G::Mem.分散读写<uint8_t>(分散.结构分散, ptr + offsets::Health1) == 0;
		v3 = G::Mem.分散读写<uint8_t>(分散.结构分散, ptr + offsets::Health2);
		if (v3 >= 0)
		{
			v2 = G::Mem.Read<float>(ptr + offsets::Health3 + v3);
			v4 = v2;
			if (!v1)
			{
				DecryptHealth((uint8_t*)&v4, 4u, G::Mem.分散读写<uint32_t>(分散.结构分散, ptr + offsets::Health4));
				v2 = v4;
			}
		}
	}
	return v2;
}

void RenderThread()
{
	FVector 头部3D{}, 颈部3D, 骨盆3D, 左肩3D, 左肘3D, 左手3D, 右肩3D, 右肘3D, 右手3D,
		左臀3D, 左膝3D, 左脚3D, 右臀3D, 右膝3D, 右脚3D;
	
	Index index{};
	SDK::GetIndex(index);
	while (true)
	{
		std::vector<player_data> 玩家数组缓存;
		std::vector<player_bone> 骨骼数组缓存;
		auto 临时数据 = player_data();
		auto 临时玩家 = std::vector<Player>();

		auto 临时二次数据 = Player();
		auto 临时二次数组 = std::vector<Player>();

		
		{
			临时玩家 = G::engine->集_玩家数组;
			if (临时玩家.size() < 0) return;
			G::Mem.ScatterClear(分散.结构临时分散, 1);
			for (size_t i = 0; i < 临时玩家.size(); i++)
			{
				if (临时玩家[i].Mesh)
					G::Mem.ScatterPrepare(分散.结构临时分散, 临时玩家[i].Mesh + offsets::Bone, sizeof(DWORD_PTR));
				if (临时玩家[i].pActor)
					G::Mem.ScatterPrepare(分散.结构临时分散, 临时玩家[i].pActor + offsets::VehicleRiderComponent, sizeof(DWORD_PTR));

			}
			
			G::Mem.ExecuteRead(分散.结构临时分散);


			for (size_t i = 0; i < 临时玩家.size(); i++)
			{
				if (!临时玩家[i].Mesh) continue;
				DWORD_PTR BoneArray = G::Mem.分散读写<uintptr_t>(分散.结构临时分散, 临时玩家[i].Mesh + offsets::Bone);//骨骼数组
				
				ULONG_PTR PlayerVehicleComponent = G::Mem.分散读写<ULONG_PTR>(分散.结构临时分散, 临时玩家[i].pActor + offsets::VehicleRiderComponent);
				//int PlayerVehicleSeat = G::Mem.ValidPtr(临时玩家[i].Mesh, sizeof(ULONG_PTR)) ? -1 : G::Mem.分散读写<INT>(分散.结构分散, 临时玩家[i].PlayerVehicleComponent + offsets::SeatIndex);


				auto LastVehiclePawn = G::Mem.分散读写<ULONG_PTR>(分散.结构分散, 临时玩家[i].PlayerVehicleComponent + offsets::LastVehiclePawn);

				临时二次数据.BoneArray = BoneArray;

				临时二次数据.pActor = 临时玩家[i].pActor;
				临时二次数据.Mesh = 临时玩家[i].Mesh;
				临时二次数据.ActorRootComp = 临时玩家[i].ActorRootComp;
				临时二次数据.PlayerState = 临时玩家[i].PlayerState;
				临时二次数据.PlayerVehicleComponent = PlayerVehicleComponent;
				临时二次数据.TeamColor = 临时玩家[i].TeamColor;
				临时二次数据.Teamid = 临时玩家[i].Teamid;
				临时二次数据.Name = 临时玩家[i].Name;
				
				临时二次数组.push_back(临时二次数据);
			}
			

			G::Mem.ScatterClear(分散.结构分散,1);
			for (auto Temp : 临时二次数组)
			{
				//FLOAT 敌人朝向 = Memory::Read<FLOAT>(Temp.pActor + offsets::人物朝向);

				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::人物朝向, sizeof(float));

				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::Health, sizeof(float));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::Health_Die, sizeof(float));


				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::AActorRole, 4);
				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::CharacterId, 4);
				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::Health1, 4);
				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::Health2, 4);
				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::Health3, 4);
				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::Health5, 4);

				G::Mem.ScatterPrepare(分散.结构分散, Temp.pActor + offsets::Audience, sizeof(int));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.Mesh + offsets::BoneArry, sizeof(FTransform));
				//G::Mem.ScatterPrepare(分散.结构分散, Temp.RootComponent + offsets::Position, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.ActorRootComp + offsets::ComponentVelocity, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.ActorRootComp + offsets::ComponentVelocity - 0x28, sizeof(FVector));
				
				G::Mem.ScatterPrepare(分散.结构分散, Temp.PlayerState + offsets::PlayerSatisitc, sizeof(int));
				
				//G::Mem.ScatterPrepare(分散.结构分散, Temp.PlayerVehicleComponent + offsets::SeatIndex, sizeof(INT));



				G::Mem.ScatterPrepare(分散.结构分散, Temp.PlayerVehicleComponent + offsets::LastVehiclePawn, sizeof(ULONG_PTR));
			

				//G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + 0x30, 0x3000);
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.头部 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.颈部 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.骨盆 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.头部 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.左肩 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.左肘 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.左手 * 0x30, sizeof(FVector));

				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.右肩 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.右肘 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.右手 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.左臀 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.左膝 * 0x30, sizeof(FVector));

				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.左脚 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.右臀 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.右膝 * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(分散.结构分散, Temp.BoneArray + index.右脚 * 0x30, sizeof(FVector));

			}
			G::Mem.ExecuteRead(分散.结构分散);



			for (auto Temp : 临时二次数组)
			{
				FLOAT 敌人朝向 = G::Mem.分散读写<FLOAT>(分散.结构分散, Temp.pActor + offsets::人物朝向);

				bool 是否倒地 = false;

				float 對象血量;
				float 最大血量;
				bool 對象死亡;
				float 站立血量 = GetHealth(Temp.pActor);// G::Mem.分散读写<float>(分散.结构分散, Temp.pActor + offsets::Health);

				if (站立血量 < 0)
				{
					是否倒地 = false;
					最大血量 = 100;//G::Mem.分散读写<float>(分散.结构分散, Temp.pActor + offsets::HealthMax);
					//printf("站立血量 %f  最大血量 %f\n", 站立血量, 最大血量);
					對象血量 = 站立血量;
					對象死亡 = true;
				}
				else
				{
					是否倒地 = true;
					//倒地了
					float 倒地血量 = G::Mem.分散读写<float>(分散.结构分散, Temp.pActor + offsets::Health_Die);
					float 最大血量 = 100;// G::Mem.分散读写<float>(分散.结构分散, Temp.pActor + offsets::GroggyHealthMax);

					if (站立血量 < 0.1 && 倒地血量 < 0.1)
						continue;
					對象血量 = 倒地血量;
					對象死亡 = false;
				}
				//if (!對象死亡) continue;
				FVector Location = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, 0);
				if (Temp.BoneArray > 65535 && Temp.Mesh > 65536)
				{
					
					float deltaZ = Location.z - Local.CameraPos.z; // 假人在地底下距离你的z轴xx米

					/*if (deltaZ <= 200.f)
						continue;*/
					头部3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.头部);
					颈部3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.颈部);
					骨盆3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.骨盆);
					左肩3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.左肩);
					左肘3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.左肘);
					左手3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.左手);
					右肩3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.右肩);
					右肘3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.右肘);
					右手3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.右手);
					左臀3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.左臀);
					左膝3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.左膝);
					左脚3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.左脚);
					右臀3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.右臀);
					右膝3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.右膝);
					右脚3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.右脚);
					骨骼数组缓存.push_back(player_bone(
						是否倒地,
						头部3D, 颈部3D, 骨盆3D, 左肩3D,
						左肘3D, 左手3D, 右肩3D, 右肘3D,
						右手3D, 左臀3D, 左膝3D, 左脚3D,
						右臀3D, 右膝3D, 右脚3D));
				}
				//printf("%f %f %f\n", 头部3D.x, 头部3D.y, 头部3D.z);


				FVector 自瞄坐标;
				if (F::Global.Menu.自瞄部位列表索引 == 0)
				{
					自瞄坐标 = 头部3D;
					//F::Global.Menu.自瞄位置 = 46;
				}
				if (F::Global.Menu.自瞄部位列表索引 == 1)
				{
					自瞄坐标 = 颈部3D;
					//F::Global.Menu.自瞄位置 = 45;
				}
				if (F::Global.Menu.自瞄部位列表索引 == 2)
				{
					自瞄坐标 = 颈部3D;
					//F::Global.Menu.自瞄位置 = 1;
				}
				if (F::Global.Menu.自瞄部位列表索引 == 3)
				{
					自瞄坐标 = 骨盆3D;
					//F::Global.Menu.自瞄位置 = 6;
				}
				
				int Kill = G::Mem.分散读写<int>(分散.结构分散, Temp.PlayerState + offsets::PlayerSatisitc);
				int Audience = G::Mem.分散读写<int>(分散.结构分散, Temp.pActor + offsets::Audience);


				//INT PlayerVehicleSeat = G::Mem.ValidPtr(Temp.Mesh, sizeof(ULONG_PTR)) ? -1 : G::Mem.分散读写<INT>(分散.结构分散, Temp.PlayerVehicleComponent + offsets::SeatIndex);


				auto LastVehiclePawn = G::Mem.分散读写<ULONG_PTR>(分散.结构分散, Temp.PlayerVehicleComponent + offsets::LastVehiclePawn);

				G::Mem.ScatterClear(分散.LastVehiclePawn, 1);
				G::Mem.ScatterPrepare(分散.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovement, sizeof(FVector));
				//G::Mem.ScatterPrepare(分散.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovementUp, sizeof(FVector));

				G::Mem.ExecuteRead(分散.LastVehiclePawn);
				/*if (Temp.pActor  == Local.AcknowledgedPawn)
				printf("Temp.ActorRootComp %p\n", Temp.ActorRootComp);*/
				auto PlayerVelocity = (LastVehiclePawn < 65536 ? G::Mem.分散读写<FVector>(分散.结构分散, Temp.ActorRootComp + offsets::ComponentVelocity)
					: G::Mem.分散读写<FVector>(分散.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovement));
				auto PlayerVelocityUp = (LastVehiclePawn <65536 ? G::Mem.分散读写<FVector>(分散.结构分散, Temp.ActorRootComp + offsets::ComponentVelocity - 0x28)
					: PlayerVelocity * 2/*G::Mem.分散读写<FVector>(分散.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovementUp)*/);

				//FVector speed = G::Mem.分散读写<FVector>(分散.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovementUp);

				临时数据.是否倒地 = 是否倒地;
				临时数据.pActor = Temp.pActor;
				临时数据.PlayerState = Temp.PlayerState;
				临时数据.Health = 對象血量;
				临时数据.MaxHealth = 最大血量;
				临时数据.Audience = Audience;
				临时数据.敌人朝向 = 敌人朝向;
				临时数据.Kill = Kill;
				临时数据.Location = Location;
				临时数据.Teamid = Temp.Teamid;
				临时数据.Name = Temp.Name;
				临时数据.自瞄坐标 = 自瞄坐标;
				临时数据.TeamColor = Temp.TeamColor;
				临时数据.PlayerVelocity = PlayerVelocity;
				临时数据.PlayerVelocityUp = PlayerVelocityUp;

				临时数据.RootLoc = Location;
				临时数据.HeadLoc = 头部3D;

				玩家数组缓存.push_back(player_data(临时数据));
				
				
			}
			G::render.bonedata = 骨骼数组缓存;
			G::render.处理好的玩家数组 = 玩家数组缓存;
			临时玩家.clear();
			临时二次数组.clear();
			骨骼数组缓存.clear();
			玩家数组缓存.clear();

		}
	}
}

//物品数组
void RenderThread::ItemThread()
{
	std::vector<Item> 物品数组缓存;
	auto 临时数据 = Item();
	auto _pushback = [&](Item Temp,int 物品组, ImColor color)
	{
		if (Temp.RootComponent)
		{
			FVector Location = G::Mem.分散读写<FVector>(分散.物品分散, Temp.RootComponent + offsets::Position);
			临时数据.pActor = Temp.pActor;
			临时数据.Location = Location;
			临时数据.Name = Temp.Name;
			临时数据.Color = color;
			临时数据.物品所在组 = 物品组;
			临时数据.要区分的物品类型 = Temp.要区分的物品类型;

			物品数组缓存.push_back(Item(临时数据));
		}
	};
	
	{

		G::Mem.ScatterClear(分散.物品分散, 1);
		for (auto Temp : G::engine->集_物品数组)
		{
			if (Temp.RootComponent)
			{
				G::Mem.ScatterPrepare(分散.物品分散, Temp.RootComponent + offsets::Position, sizeof(FVector));
			}
		}
		G::Mem.ExecuteRead(分散.物品分散);


		for (auto Temp : G::engine->集_物品数组)
		{
			int ItemIndex = F::Global.Menu.itemgrounp[Temp.要区分的物品类型 - 1].物品组;

			if (ItemIndex == (int)F::Global.Menu.当前物品组 - 65)
			{
				_pushback(Temp, F::Global.Menu.itemgrounp[Temp.要区分的物品类型 - 1].物品组, Temp.Color);
			}
			
		}
	}
	G::render.处理好的物品数组 = 物品数组缓存;
	物品数组缓存.clear();
}

//地面物品数组
void RenderThread::ItemGroupThread()
{
	std::vector<Item> 物品数组缓存;
	auto 临时数据 = Item();
	auto _pushback = [&](Item Temp, int 物品组, ImColor color)
	{
		FVector Location = G::Mem.分散读写<FVector>(分散.地面物品分散, Temp.pActor + offsets::Position);
		临时数据.pActor = Temp.pActor;
		临时数据.Location = Location;
		临时数据.Name = Temp.Name;
		临时数据.Color = color;
		临时数据.物品所在组 = 物品组;
		物品数组缓存.push_back(Item(临时数据));

	};
	
	{
		G::Mem.ScatterClear(分散.地面物品分散, 1);
		for (auto Temp : G::engine->集_地面物品数组)
		{
			G::Mem.ScatterPrepare(分散.地面物品分散, Temp.pActor + offsets::Position, sizeof(FVector));
		}
		G::Mem.ExecuteRead(分散.地面物品分散);

		for (auto Temp : G::engine->集_地面物品数组)
		{
			int ItemIndex = F::Global.Menu.itemgrounp[Temp.要区分的物品类型 - 1].物品组;
			//printf("ItemIndex %d\n", ItemIndex);
			if (ItemIndex == (int)F::Global.Menu.当前物品组 - 65)
			{
				_pushback(Temp, F::Global.Menu.itemgrounp[Temp.要区分的物品类型 - 1].物品组, Temp.Color);
			}
			
			//_pushback(Temp,Temp.Color);
			
			
		}
	}
	G::render.处理好的地面物品数组 = 物品数组缓存;
	物品数组缓存.clear();
}

//物品盒子/骨灰盒数组
void RenderThread::GrounpBoxThread()
{
	std::vector<PackgeItem> 盒子數組緩存;
	auto 临时数据 = PackgeItem();

	
	{
		G::Mem.ScatterClear(分散.盒子分散, 1);
		for (auto Temp : G::engine->集_盒子数组)
		{
			if (Temp.RootComponent > 65536)
				G::Mem.ScatterPrepare(分散.盒子分散, Temp.RootComponent + offsets::Position, sizeof(FVector));
		}
		
		G::Mem.ExecuteRead(分散.盒子分散);

		int index = 0;
		for (auto Temp : G::engine->集_盒子数组)
		{
			index = index + 1;
			if (Temp.RootComponent <= 65536) continue;
			FVector Location = G::Mem.分散读写<FVector>(分散.盒子分散, Temp.RootComponent + offsets::Position);
			//printf("Location %f %f %f\n", Location.x, Location.y, Location.z);
			临时数据.pActor = Temp.pActor;
			临时数据.Location = Location;
			临时数据.Name = Temp.Name;
			//printf("%s\n", 临时数据.Name.c_str());
			临时数据.Color = Temp.info[index].颜色;
			盒子數組緩存.push_back(PackgeItem(临时数据));

		}
	}
	G::render.处理好的盒子数组 = 盒子數組緩存;
	盒子數組緩存.clear();
}

//载具数组
void RenderThread::VehicleThread()
{
	std::vector<vehicle> 载具数组缓存;
	auto 临时数据 = vehicle();
	auto _pushback = [&](vehicle Temp, ImColor color)
	{
		if (Temp.RootComponent > 65536)
		{
			FVector Location = G::Mem.分散读写<FVector>(分散.载具分散, Temp.RootComponent + offsets::Position);
			临时数据.pActor = Temp.pActor;
			临时数据.Location = Location;
			//printf("%f %f %f\n", 临时数据.Location.x, 临时数据.Location.y, 临时数据.Location.z);
			临时数据.Name = Temp.Name;
			临时数据.Color = color;
			载具数组缓存.push_back(vehicle(临时数据));
		}
		

	};
	
	{
		G::Mem.ScatterClear(分散.载具分散, 1);
		for (auto Temp : G::engine->集_载具数组)
		{
			if (Temp.RootComponent > 65536)
				G::Mem.ScatterPrepare(分散.载具分散, Temp.RootComponent + offsets::Position, sizeof(FVector));
		}
		G::Mem.ExecuteRead(分散.载具分散);

		for (auto Temp : G::engine->集_载具数组)
		{
			_pushback(Temp, Temp.Color);
		}
	}
	G::render.处理好的载具数组 = 载具数组缓存;
	载具数组缓存.clear();
}

//调试数组
void RenderThread::DebugThread()
{
	std::vector<Actor> tmp_pActor;
	auto tmppActor = Actor();
	
	G::Mem.ScatterClear(分散.ScatterDebug, 1);
	for (auto Temp : G::engine->调试数组)
	{
		if (Temp.RootComponent > 65536)
			G::Mem.ScatterPrepare(分散.ScatterDebug, Temp.RootComponent + offsets::Position, sizeof(FVector));
	}
	G::Mem.ExecuteRead(分散.ScatterDebug);

	for (auto Temp : G::engine->调试数组)
	{
			
		if (Temp.RootComponent > 65536)
		{
			FVector Location = G::Mem.分散读写<FVector>(分散.ScatterDebug, Temp.RootComponent + offsets::Position);
			tmppActor.pActor = Temp.pActor;
			tmppActor.Location = Location;

			tmppActor.Name = Temp.Name;
			tmppActor.Color = ImColor(255,255,0);
			tmp_pActor.push_back(tmppActor);
		}

	}
	
	G::render.调试数组 = tmp_pActor;
	tmp_pActor.clear();
}

void ItemThread() {
	while (true) {
		RenderThread::DebugThread();
		RenderThread::VehicleThread();
		RenderThread::GrounpBoxThread();
		RenderThread::ItemGroupThread();
		RenderThread::ItemThread();
	}
}

void Render::Attath()
{
	std::thread(::RenderThread).detach();
	std::thread(::ItemThread).detach();
	//CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)处理_玩家数组, 0, 0, 0));
	//CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)处理_物品数组, 0, 0, 0));
}

FVector Render::叠加物品(FVector ItemScreenLocation) {
	for (ULONG i = 0; i < Game::DrawOverlay::ItemList.size(); i++)
	{
		
		if (ItemScreenLocation.x > Game::DrawOverlay::ItemList[i].x - 80.f && ItemScreenLocation.x < Game::DrawOverlay::ItemList[i].x + 80.f
			&& ItemScreenLocation.y > Game::DrawOverlay::ItemList[i].y - 16.f && ItemScreenLocation.y < Game::DrawOverlay::ItemList[i].y + 16.f)
		{
			ItemScreenLocation = Game::DrawOverlay::ItemList[i];
			ItemScreenLocation.y = ItemScreenLocation.y - 18.f * 0.8 ;

			//叠加坐标.Y ＝ 叠加坐标.Y － 16 × 0.8
			
		}
	}
	return ItemScreenLocation;
}
BOOL Render::DrawItem(string PackageItemName, OUT FVector* ItemScreenLocation,ImColor Color , FLOAT EntityDistance) {
	/*EntityNameIDTypeMap PackageEntityObjName = FindEntityObjName(PackageItemObjID); if (PackageEntityObjName.Type == EntityType::Unknowns) { return false; }
	ImVec4 透视颜色;
	if (PackageEntityObjName.Follow) { if (Menu::物资透视::透视开关::特殊) 透视颜色 = Menu::物资透视::透视颜色::特殊; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Weapon) { if (Menu::物资透视::透视开关::武器) 透视颜色 = Menu::物资透视::透视颜色::武器; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Accessories) { if (Menu::物资透视::透视开关::配件) 透视颜色 = Menu::物资透视::透视颜色::配件; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Drug) { if (Menu::物资透视::透视开关::医疗) 透视颜色 = Menu::物资透视::透视颜色::医疗; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Armor) { if (Menu::物资透视::透视开关::防具) 透视颜色 = Menu::物资透视::透视颜色::防具; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Grenade) { if (Menu::物资透视::透视开关::投掷) 透视颜色 = Menu::物资透视::透视颜色::投掷; else return false; }
	else return false;*/
	
	if (EntityDistance > 1.0f) ItemScreenLocation->z = 绘制文本2(ItemScreenLocation->x, ItemScreenLocation->y, 0,Color, u8"%s[%.0f]", PackageItemName.c_str(), EntityDistance);
	else {
		FLOAT ItemScreenLocationX = ItemScreenLocation->z > 0.0f ? ItemScreenLocation->z : ItemScreenLocation->x;
		//ItemScreenLocationX -= F::Global.GameData.新窗口W;
		draw::绘制文本(ItemScreenLocationX, ItemScreenLocation->y,0,Color, u8"|%s", PackageItemName.c_str());
	}
	

	return true;
}
BOOL Render::DrawItem(string PackageItemObjName, FVector2 ItemScreenLocation, ImColor Color, FLOAT EntityDistance) {
	FLOAT ItemScreenLocationX = ItemScreenLocation.X;
	FLOAT ItemScreenLocationY = ItemScreenLocation.Y;
	FVector ItemScreenLocation3 = FVector(ItemScreenLocationX, ItemScreenLocationY, 0.0f);
	ItemScreenLocation3 = 叠加物品(ItemScreenLocation3);
	EntityDistance = ItemScreenLocationX != ItemScreenLocation3.x || ItemScreenLocationY != ItemScreenLocation3.y ? 0 : EntityDistance;
	if (DrawItem(PackageItemObjName, &ItemScreenLocation3, Color, EntityDistance)) {
		
		Game::DrawOverlay::ItemList.push_back(ItemScreenLocation3);
		return true;
	}
	return false;

}