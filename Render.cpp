#include "Render.h"
#include <cstdarg>

#include "Engine.h"
#include "Memory.h"
#include "util.hpp"
#include "CThread.h"

using namespace CThread;

void Render::Init()//�����Ѵ�����ɵ����� UE
{
	if (Local.��ս���� > 0)
	{
		�����ı�(60, 80, TXT_CENTERX, ImColor(255, 0, 0), u8"��ǰ��ս����:%d", Local.��ս����);
	}
	//��������({ (float)F::Global.GameData.�´���X + 10,(float)F::Global.GameData.�´���Y + 10 }, { (float)F::Global.GameData.�´���X + 10,(float)F::Global.GameData.�´���Y + 1070 }, ImColor(255, 255, 155), 2.0f);	
	float ���˵�׼�Ǿ��� = 0;
	F::Global.Aim.����Ѫ�� = 0;
	Base_Radar Radar;
	RadarSetting(Radar);
	
	if (F::Global.Menu.Debug) return;

	for (auto Temp : this->����õ��������)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;	

		

		if (F::Global.Menu.�״�)
			Radar.AddPoint(Local.CameraPos, Local.ControlRotation.y, Temp.Location, ImColor(237, 85, 106, 200), F::Global.Menu.RadarType, Temp.���˳��� - 90);

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

			if (F::Global.Menu.�����Ϣ) {
				draw::�����ı�(Screen2.X, Screen2.Y, TXT_CENTERX, Temp.�Ƿ񵹵� ? ImVec4(255, 255, 255, 255) : Temp.TeamColor, u8"%ws  [%.0f]\n T:%d | A:%d | K:%d",
					Temp.Name.c_str(), Distance, Temp.Teamid, Temp.Audience, Temp.Kill);
			}
			if (F::Global.Menu.���Ѫ��) {
				draw::����Ѫ��((int)bbox.x, (int)bbox.y, (int)bbox.w,(int)bbox.h, Temp.Health, 100);
			}
			
			if (true/*Local.LoaclWeaponData.WeaponMap*/) {
				//BOOL PlayerDie = Temp.Health <= 0.f || Temp.Health > 100.f;
				if (/*!PlayerDie*/ true)//��������
				{
					FVector ����Ԥ������ = Local.LoaclWeaponData.WeaponMap ? SDK::PredictedPosition(Temp.PlayerVelocity, Temp.PlayerVelocityUp, Distance) : FVector{};
					����Ԥ������ += Temp.��������;
					float AimDistance;
					FVector2 ScreenPos{};
					if (SDK::WorldScreen(����Ԥ������, &ScreenPos, &AimDistance))
					{
						if (F::Global.Aim.���� == false)
						{
							���˵�׼�Ǿ��� = ScreenPos.DistanceTo({ (float)F::Global.GameData.Width, (float)F::Global.GameData.Height });
							if (���˵�׼�Ǿ��� <= F::Global.Aim.��Ļ��ǰ)
							{
								F::Global.Aim.�����ַ = Temp.pActor;
								F::Global.Aim.��Ļ��ǰ = ���˵�׼�Ǿ���;
								F::Global.Aim.�������� = ����Ԥ������;
								F::Global.Aim.����Ѫ�� = Temp.Health;
							}
						}
						else//�����������
						{
							if (Temp.pActor == F::Global.Aim.�����ַ)
							{
								F::Global.Aim.��Ļ��ǰ = ���˵�׼�Ǿ���;
								F::Global.Aim.�������� = ����Ԥ������;
								F::Global.Aim.����Ѫ�� = Temp.Health;
								//printf("%.0f %.0f %.0f\n", F::Global.Aim.��������.x, F::Global.Aim.��������.y, F::Global.Aim.��������.z);
							}
						}


					}
				}
			}


			if (F::Global.KeyBind.ս��ģʽ)
			{
				continue;
			}
			if (F::Global.Menu.��ҷ���) {
				draw::DrawRect((int)bbox.x, (int)bbox.y, (int)bbox.w, (int)bbox.h, Temp.�Ƿ񵹵� ? ImColor(255,255,255) : ImColor(255, 255, 0), 1);
			}
			if (F::Global.Menu.�������) {
				draw::��������({ F::Global.GameData.Width + 0.f,F::Global.GameData.Height * 4.f }, { Screen2.X, Screen2.Y }, Temp.�Ƿ񵹵� ? ImColor(255, 255, 255) : ImColor(255, 255, 0), 1.0f);
			}



		}
		if (F::Global.Menu.��ͼ�״� && !F::Global.KeyBind.ս��ģʽ)
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
				FVector GunDir = FRotator(0.0f, Temp.���˳���, 0.0f).GetUnitVector();

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

					draw::��������({ p1.x, p1.y }, { p2.x, p2.y }, 2, ImColor(255, 0, 0));
					draw::��������({ p2.x, p2.y }, { p3.x, p3.y }, 2, ImColor(255, 0, 0));
					draw::��������({ p3.x, p3.y }, { p1.x, p1.y }, 2, ImColor(255, 0, 0));
				}
				CircleFilled(map.X, map.Y, Size, Temp.�Ƿ񵹵� ? ImColor(255, 255, 255) : ImColor(255, 0, 0), 1);

				draw::�����ı�(map.X, map.Y, TXT_CENTERX, Temp.�Ƿ񵹵� ? ImColor(255, 255, 255) : ImColor(255, 255, 0), "[T:%d]",Temp.Teamid);
			}
		}

		

	}

	for (auto Temp : this->bonedata)
	{
		FVector2 ͷ�� = {}, ���� = {}, ���� = {}, ��� = {}, ���� = {}, ���� = {}, �Ҽ� = {}, ���� = {}, ���� = {}, ���� = {}, ��ϥ = {}, ��� = {}, ���� = {}, ��ϥ = {}, �ҽ� = {};
		float Distance;
		if (SDK::WorldScreen(Temp.ͷ��, &ͷ�� ,&Distance)
			&& SDK::WorldScreen(Temp.����, &����, &Distance)
			&& SDK::WorldScreen(Temp.����, &����, &Distance)
			&& SDK::WorldScreen(Temp.���, &���, &Distance)
			&& SDK::WorldScreen(Temp.����, &����, &Distance)
			&& SDK::WorldScreen(Temp.����, &����, &Distance)
			&& SDK::WorldScreen(Temp.�Ҽ�, &�Ҽ�, &Distance)
			&& SDK::WorldScreen(Temp.����, &����, &Distance)
			&& SDK::WorldScreen(Temp.����, &����, &Distance)
			&& SDK::WorldScreen(Temp.����, &����, &Distance)
			&& SDK::WorldScreen(Temp.��ϥ, &��ϥ, &Distance)
			&& SDK::WorldScreen(Temp.���, &���, &Distance)
			&& SDK::WorldScreen(Temp.����, &����, &Distance)
			&& SDK::WorldScreen(Temp.��ϥ, &��ϥ, &Distance)
			&& SDK::WorldScreen(Temp.�ҽ�, &�ҽ�, &Distance))
		{
			ImColor color = Temp.�Ƿ񵹵� ? ImColor(255, 255, 255) : F::Global.Menu.������ɫ;
			int ������ϸ = F::Global.Menu.������ϸ;
			//if (!ͷ��.IsZero() && !����.IsZero() && !����.IsZero())
			{
				draw::��������(ͷ��, ����, color, ������ϸ);
				draw::��������(����, ����, color, ������ϸ);
				draw::��������(���, ����, color, ������ϸ);
				draw::��������(����, ���, color, ������ϸ);
				draw::��������(����, ����, color, ������ϸ);
				draw::��������(�Ҽ�, ����, color, ������ϸ);
				draw::��������(����, �Ҽ�, color, ������ϸ);
				draw::��������(����, ����, color, ������ϸ);
				draw::��������(����, ����, color, ������ϸ);
				draw::��������(��ϥ, ����, color, ������ϸ);
				draw::��������(���, ��ϥ, color, ������ϸ);
				draw::��������(����, ����, color, ������ϸ);
				draw::��������(��ϥ, ����, color, ������ϸ);
				draw::��������(�ҽ�, ��ϥ, color, ������ϸ);
			}
			
		}
	}
	if (F::Global.Menu.�״�)Radar.Render();

}

void Render::��Ʒ����()
{
	Game::DrawOverlay::ItemList.clear(); // ��������
	if (F::Global.KeyBind.ս��ģʽ) return;

	for (auto Temp : this->��������)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		//draw::�����ı�(Screen.X, Screen.Y, TXT_CENTERX, ImColor(255, 255, 0), "%s", Temp.Name.c_str());
		if (Distance > 100.f) continue;
		DrawItem(Temp.Name, Screen, Temp.Color, Distance);

	}
	if (F::Global.Menu.Debug) return;

	for (auto Temp : this->����õ���Ʒ����)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		if (Distance > 800.f) continue;
		DrawItem(Temp.Name, Screen,Temp.Color, Distance);
		//draw::�����ı�(Screen.X, Screen.Y, TXT_CENTERX, Temp.Color, u8"[%d %s %.0fm]",Temp.Ҫ���ֵ���Ʒ����, Temp.Name.c_str(), Distance);

	}
	for (auto Temp : this->����õĵ�����Ʒ����)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		if (Distance > 800.f) continue;
		DrawItem(Temp.Name, Screen, Temp.Color, Distance);
		//�����ı�(Screen.X, Screen.Y, TXT_CENTERX, Temp.Color, u8"[%s %.0fm]", Temp.Name.c_str(), Distance);
	}
	//printf("�ؾ�����%d��\n", this->����õ��ؾ�����.size());
	for (auto Temp : this->����õ��ؾ�����)
	{
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		if (Distance > 800.f) continue;
		draw::�����ı�(Screen.X, Screen.Y, TXT_CENTERX, F::Global.Color.�ؾ�, u8"%s %.0fm", Temp.Name.c_str(), Distance);

	}
	int Index = 0;
	for (auto Temp : this->����õĺ�������)
	{
		Index+=1;
		FVector2 Screen = {};
		FVector2 Screen2 = {};
		float Distance;
		if (!SDK::WorldScreen(Temp.Location, &Screen, &Distance)) continue;
		if (Distance > 800.f) continue;
		DrawItem(Temp.Name, { Screen.X,Screen.Y - 14 * Index }, Temp.Color,Distance);
		//�����ı�(Screen.X, Screen.Y - 14 * Index, TXT_CENTERX, F::Global.Color.�ؾ�, u8"[����]%s [%s] %.0fm", Temp.info[Index].����.c_str(), Temp.Name.c_str(), Distance);

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
	if (G::Mem.��ɢ��д<uint8_t>(��ɢ.�ṹ��ɢ, ptr + offsets::AActorRole) == 3 || !G::Mem.��ɢ��д<uint32_t>(��ɢ.�ṹ��ɢ, ptr + offsets::CharacterId))
		v2 = G::Mem.��ɢ��д<float>(��ɢ.�ṹ��ɢ, ptr + offsets::Health5);
	else
	{
		v1 = G::Mem.��ɢ��д<uint8_t>(��ɢ.�ṹ��ɢ, ptr + offsets::Health1) == 0;
		v3 = G::Mem.��ɢ��д<uint8_t>(��ɢ.�ṹ��ɢ, ptr + offsets::Health2);
		if (v3 >= 0)
		{
			v2 = G::Mem.Read<float>(ptr + offsets::Health3 + v3);
			v4 = v2;
			if (!v1)
			{
				DecryptHealth((uint8_t*)&v4, 4u, G::Mem.��ɢ��д<uint32_t>(��ɢ.�ṹ��ɢ, ptr + offsets::Health4));
				v2 = v4;
			}
		}
	}
	return v2;
}

void RenderThread()
{
	FVector ͷ��3D{}, ����3D, ����3D, ���3D, ����3D, ����3D, �Ҽ�3D, ����3D, ����3D,
		����3D, ��ϥ3D, ���3D, ����3D, ��ϥ3D, �ҽ�3D;
	
	Index index{};
	SDK::GetIndex(index);
	while (true)
	{
		std::vector<player_data> ������黺��;
		std::vector<player_bone> �������黺��;
		auto ��ʱ���� = player_data();
		auto ��ʱ��� = std::vector<Player>();

		auto ��ʱ�������� = Player();
		auto ��ʱ�������� = std::vector<Player>();

		
		{
			��ʱ��� = G::engine->��_�������;
			if (��ʱ���.size() < 0) return;
			G::Mem.ScatterClear(��ɢ.�ṹ��ʱ��ɢ, 1);
			for (size_t i = 0; i < ��ʱ���.size(); i++)
			{
				if (��ʱ���[i].Mesh)
					G::Mem.ScatterPrepare(��ɢ.�ṹ��ʱ��ɢ, ��ʱ���[i].Mesh + offsets::Bone, sizeof(DWORD_PTR));
				if (��ʱ���[i].pActor)
					G::Mem.ScatterPrepare(��ɢ.�ṹ��ʱ��ɢ, ��ʱ���[i].pActor + offsets::VehicleRiderComponent, sizeof(DWORD_PTR));

			}
			
			G::Mem.ExecuteRead(��ɢ.�ṹ��ʱ��ɢ);


			for (size_t i = 0; i < ��ʱ���.size(); i++)
			{
				if (!��ʱ���[i].Mesh) continue;
				DWORD_PTR BoneArray = G::Mem.��ɢ��д<uintptr_t>(��ɢ.�ṹ��ʱ��ɢ, ��ʱ���[i].Mesh + offsets::Bone);//��������
				
				ULONG_PTR PlayerVehicleComponent = G::Mem.��ɢ��д<ULONG_PTR>(��ɢ.�ṹ��ʱ��ɢ, ��ʱ���[i].pActor + offsets::VehicleRiderComponent);
				//int PlayerVehicleSeat = G::Mem.ValidPtr(��ʱ���[i].Mesh, sizeof(ULONG_PTR)) ? -1 : G::Mem.��ɢ��д<INT>(��ɢ.�ṹ��ɢ, ��ʱ���[i].PlayerVehicleComponent + offsets::SeatIndex);


				auto LastVehiclePawn = G::Mem.��ɢ��д<ULONG_PTR>(��ɢ.�ṹ��ɢ, ��ʱ���[i].PlayerVehicleComponent + offsets::LastVehiclePawn);

				��ʱ��������.BoneArray = BoneArray;

				��ʱ��������.pActor = ��ʱ���[i].pActor;
				��ʱ��������.Mesh = ��ʱ���[i].Mesh;
				��ʱ��������.ActorRootComp = ��ʱ���[i].ActorRootComp;
				��ʱ��������.PlayerState = ��ʱ���[i].PlayerState;
				��ʱ��������.PlayerVehicleComponent = PlayerVehicleComponent;
				��ʱ��������.TeamColor = ��ʱ���[i].TeamColor;
				��ʱ��������.Teamid = ��ʱ���[i].Teamid;
				��ʱ��������.Name = ��ʱ���[i].Name;
				
				��ʱ��������.push_back(��ʱ��������);
			}
			

			G::Mem.ScatterClear(��ɢ.�ṹ��ɢ,1);
			for (auto Temp : ��ʱ��������)
			{
				//FLOAT ���˳��� = Memory::Read<FLOAT>(Temp.pActor + offsets::���ﳯ��);

				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::���ﳯ��, sizeof(float));

				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Health, sizeof(float));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Health_Die, sizeof(float));


				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::AActorRole, 4);
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::CharacterId, 4);
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Health1, 4);
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Health2, 4);
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Health3, 4);
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Health5, 4);

				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Audience, sizeof(int));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.Mesh + offsets::BoneArry, sizeof(FTransform));
				//G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.RootComponent + offsets::Position, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.ActorRootComp + offsets::ComponentVelocity, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.ActorRootComp + offsets::ComponentVelocity - 0x28, sizeof(FVector));
				
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.PlayerState + offsets::PlayerSatisitc, sizeof(int));
				
				//G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.PlayerVehicleComponent + offsets::SeatIndex, sizeof(INT));



				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.PlayerVehicleComponent + offsets::LastVehiclePawn, sizeof(ULONG_PTR));
			

				//G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + 0x30, 0x3000);
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.ͷ�� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.���� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.���� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.ͷ�� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.��� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.���� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.���� * 0x30, sizeof(FVector));

				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.�Ҽ� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.���� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.���� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.���� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.��ϥ * 0x30, sizeof(FVector));

				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.��� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.���� * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.��ϥ * 0x30, sizeof(FVector));
				G::Mem.ScatterPrepare(��ɢ.�ṹ��ɢ, Temp.BoneArray + index.�ҽ� * 0x30, sizeof(FVector));

			}
			G::Mem.ExecuteRead(��ɢ.�ṹ��ɢ);



			for (auto Temp : ��ʱ��������)
			{
				FLOAT ���˳��� = G::Mem.��ɢ��д<FLOAT>(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::���ﳯ��);

				bool �Ƿ񵹵� = false;

				float ����Ѫ��;
				float ���Ѫ��;
				bool ��������;
				float վ��Ѫ�� = GetHealth(Temp.pActor);// G::Mem.��ɢ��д<float>(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Health);

				if (վ��Ѫ�� < 0)
				{
					�Ƿ񵹵� = false;
					���Ѫ�� = 100;//G::Mem.��ɢ��д<float>(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::HealthMax);
					//printf("վ��Ѫ�� %f  ���Ѫ�� %f\n", վ��Ѫ��, ���Ѫ��);
					����Ѫ�� = վ��Ѫ��;
					�������� = true;
				}
				else
				{
					�Ƿ񵹵� = true;
					//������
					float ����Ѫ�� = G::Mem.��ɢ��д<float>(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Health_Die);
					float ���Ѫ�� = 100;// G::Mem.��ɢ��д<float>(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::GroggyHealthMax);

					if (վ��Ѫ�� < 0.1 && ����Ѫ�� < 0.1)
						continue;
					����Ѫ�� = ����Ѫ��;
					�������� = false;
				}
				//if (!��������) continue;
				FVector Location = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, 0);
				if (Temp.BoneArray > 65535 && Temp.Mesh > 65536)
				{
					
					float deltaZ = Location.z - Local.CameraPos.z; // �����ڵص��¾������z��xx��

					/*if (deltaZ <= 200.f)
						continue;*/
					ͷ��3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.ͷ��);
					����3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.����);
					����3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.����);
					���3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.���);
					����3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.����);
					����3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.����);
					�Ҽ�3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.�Ҽ�);
					����3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.����);
					����3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.����);
					����3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.����);
					��ϥ3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.��ϥ);
					���3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.���);
					����3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.����);
					��ϥ3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.��ϥ);
					�ҽ�3D = SDK::GetBoneMatrix(Temp.Mesh, Temp.BoneArray, index.�ҽ�);
					�������黺��.push_back(player_bone(
						�Ƿ񵹵�,
						ͷ��3D, ����3D, ����3D, ���3D,
						����3D, ����3D, �Ҽ�3D, ����3D,
						����3D, ����3D, ��ϥ3D, ���3D,
						����3D, ��ϥ3D, �ҽ�3D));
				}
				//printf("%f %f %f\n", ͷ��3D.x, ͷ��3D.y, ͷ��3D.z);


				FVector ��������;
				if (F::Global.Menu.���鲿λ�б����� == 0)
				{
					�������� = ͷ��3D;
					//F::Global.Menu.����λ�� = 46;
				}
				if (F::Global.Menu.���鲿λ�б����� == 1)
				{
					�������� = ����3D;
					//F::Global.Menu.����λ�� = 45;
				}
				if (F::Global.Menu.���鲿λ�б����� == 2)
				{
					�������� = ����3D;
					//F::Global.Menu.����λ�� = 1;
				}
				if (F::Global.Menu.���鲿λ�б����� == 3)
				{
					�������� = ����3D;
					//F::Global.Menu.����λ�� = 6;
				}
				
				int Kill = G::Mem.��ɢ��д<int>(��ɢ.�ṹ��ɢ, Temp.PlayerState + offsets::PlayerSatisitc);
				int Audience = G::Mem.��ɢ��д<int>(��ɢ.�ṹ��ɢ, Temp.pActor + offsets::Audience);


				//INT PlayerVehicleSeat = G::Mem.ValidPtr(Temp.Mesh, sizeof(ULONG_PTR)) ? -1 : G::Mem.��ɢ��д<INT>(��ɢ.�ṹ��ɢ, Temp.PlayerVehicleComponent + offsets::SeatIndex);


				auto LastVehiclePawn = G::Mem.��ɢ��д<ULONG_PTR>(��ɢ.�ṹ��ɢ, Temp.PlayerVehicleComponent + offsets::LastVehiclePawn);

				G::Mem.ScatterClear(��ɢ.LastVehiclePawn, 1);
				G::Mem.ScatterPrepare(��ɢ.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovement, sizeof(FVector));
				//G::Mem.ScatterPrepare(��ɢ.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovementUp, sizeof(FVector));

				G::Mem.ExecuteRead(��ɢ.LastVehiclePawn);
				/*if (Temp.pActor  == Local.AcknowledgedPawn)
				printf("Temp.ActorRootComp %p\n", Temp.ActorRootComp);*/
				auto PlayerVelocity = (LastVehiclePawn < 65536 ? G::Mem.��ɢ��д<FVector>(��ɢ.�ṹ��ɢ, Temp.ActorRootComp + offsets::ComponentVelocity)
					: G::Mem.��ɢ��д<FVector>(��ɢ.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovement));
				auto PlayerVelocityUp = (LastVehiclePawn <65536 ? G::Mem.��ɢ��д<FVector>(��ɢ.�ṹ��ɢ, Temp.ActorRootComp + offsets::ComponentVelocity - 0x28)
					: PlayerVelocity * 2/*G::Mem.��ɢ��д<FVector>(��ɢ.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovementUp)*/);

				//FVector speed = G::Mem.��ɢ��д<FVector>(��ɢ.LastVehiclePawn, LastVehiclePawn + offsets::ReplicatedMovementUp);

				��ʱ����.�Ƿ񵹵� = �Ƿ񵹵�;
				��ʱ����.pActor = Temp.pActor;
				��ʱ����.PlayerState = Temp.PlayerState;
				��ʱ����.Health = ����Ѫ��;
				��ʱ����.MaxHealth = ���Ѫ��;
				��ʱ����.Audience = Audience;
				��ʱ����.���˳��� = ���˳���;
				��ʱ����.Kill = Kill;
				��ʱ����.Location = Location;
				��ʱ����.Teamid = Temp.Teamid;
				��ʱ����.Name = Temp.Name;
				��ʱ����.�������� = ��������;
				��ʱ����.TeamColor = Temp.TeamColor;
				��ʱ����.PlayerVelocity = PlayerVelocity;
				��ʱ����.PlayerVelocityUp = PlayerVelocityUp;

				��ʱ����.RootLoc = Location;
				��ʱ����.HeadLoc = ͷ��3D;

				������黺��.push_back(player_data(��ʱ����));
				
				
			}
			G::render.bonedata = �������黺��;
			G::render.����õ�������� = ������黺��;
			��ʱ���.clear();
			��ʱ��������.clear();
			�������黺��.clear();
			������黺��.clear();

		}
	}
}

//��Ʒ����
void RenderThread::ItemThread()
{
	std::vector<Item> ��Ʒ���黺��;
	auto ��ʱ���� = Item();
	auto _pushback = [&](Item Temp,int ��Ʒ��, ImColor color)
	{
		if (Temp.RootComponent)
		{
			FVector Location = G::Mem.��ɢ��д<FVector>(��ɢ.��Ʒ��ɢ, Temp.RootComponent + offsets::Position);
			��ʱ����.pActor = Temp.pActor;
			��ʱ����.Location = Location;
			��ʱ����.Name = Temp.Name;
			��ʱ����.Color = color;
			��ʱ����.��Ʒ������ = ��Ʒ��;
			��ʱ����.Ҫ���ֵ���Ʒ���� = Temp.Ҫ���ֵ���Ʒ����;

			��Ʒ���黺��.push_back(Item(��ʱ����));
		}
	};
	
	{

		G::Mem.ScatterClear(��ɢ.��Ʒ��ɢ, 1);
		for (auto Temp : G::engine->��_��Ʒ����)
		{
			if (Temp.RootComponent)
			{
				G::Mem.ScatterPrepare(��ɢ.��Ʒ��ɢ, Temp.RootComponent + offsets::Position, sizeof(FVector));
			}
		}
		G::Mem.ExecuteRead(��ɢ.��Ʒ��ɢ);


		for (auto Temp : G::engine->��_��Ʒ����)
		{
			int ItemIndex = F::Global.Menu.itemgrounp[Temp.Ҫ���ֵ���Ʒ���� - 1].��Ʒ��;

			if (ItemIndex == (int)F::Global.Menu.��ǰ��Ʒ�� - 65)
			{
				_pushback(Temp, F::Global.Menu.itemgrounp[Temp.Ҫ���ֵ���Ʒ���� - 1].��Ʒ��, Temp.Color);
			}
			
		}
	}
	G::render.����õ���Ʒ���� = ��Ʒ���黺��;
	��Ʒ���黺��.clear();
}

//������Ʒ����
void RenderThread::ItemGroupThread()
{
	std::vector<Item> ��Ʒ���黺��;
	auto ��ʱ���� = Item();
	auto _pushback = [&](Item Temp, int ��Ʒ��, ImColor color)
	{
		FVector Location = G::Mem.��ɢ��д<FVector>(��ɢ.������Ʒ��ɢ, Temp.pActor + offsets::Position);
		��ʱ����.pActor = Temp.pActor;
		��ʱ����.Location = Location;
		��ʱ����.Name = Temp.Name;
		��ʱ����.Color = color;
		��ʱ����.��Ʒ������ = ��Ʒ��;
		��Ʒ���黺��.push_back(Item(��ʱ����));

	};
	
	{
		G::Mem.ScatterClear(��ɢ.������Ʒ��ɢ, 1);
		for (auto Temp : G::engine->��_������Ʒ����)
		{
			G::Mem.ScatterPrepare(��ɢ.������Ʒ��ɢ, Temp.pActor + offsets::Position, sizeof(FVector));
		}
		G::Mem.ExecuteRead(��ɢ.������Ʒ��ɢ);

		for (auto Temp : G::engine->��_������Ʒ����)
		{
			int ItemIndex = F::Global.Menu.itemgrounp[Temp.Ҫ���ֵ���Ʒ���� - 1].��Ʒ��;
			//printf("ItemIndex %d\n", ItemIndex);
			if (ItemIndex == (int)F::Global.Menu.��ǰ��Ʒ�� - 65)
			{
				_pushback(Temp, F::Global.Menu.itemgrounp[Temp.Ҫ���ֵ���Ʒ���� - 1].��Ʒ��, Temp.Color);
			}
			
			//_pushback(Temp,Temp.Color);
			
			
		}
	}
	G::render.����õĵ�����Ʒ���� = ��Ʒ���黺��;
	��Ʒ���黺��.clear();
}

//��Ʒ����/�ǻҺ�����
void RenderThread::GrounpBoxThread()
{
	std::vector<PackgeItem> ���Ӕ��M����;
	auto ��ʱ���� = PackgeItem();

	
	{
		G::Mem.ScatterClear(��ɢ.���ӷ�ɢ, 1);
		for (auto Temp : G::engine->��_��������)
		{
			if (Temp.RootComponent > 65536)
				G::Mem.ScatterPrepare(��ɢ.���ӷ�ɢ, Temp.RootComponent + offsets::Position, sizeof(FVector));
		}
		
		G::Mem.ExecuteRead(��ɢ.���ӷ�ɢ);

		int index = 0;
		for (auto Temp : G::engine->��_��������)
		{
			index = index + 1;
			if (Temp.RootComponent <= 65536) continue;
			FVector Location = G::Mem.��ɢ��д<FVector>(��ɢ.���ӷ�ɢ, Temp.RootComponent + offsets::Position);
			//printf("Location %f %f %f\n", Location.x, Location.y, Location.z);
			��ʱ����.pActor = Temp.pActor;
			��ʱ����.Location = Location;
			��ʱ����.Name = Temp.Name;
			//printf("%s\n", ��ʱ����.Name.c_str());
			��ʱ����.Color = Temp.info[index].��ɫ;
			���Ӕ��M����.push_back(PackgeItem(��ʱ����));

		}
	}
	G::render.����õĺ������� = ���Ӕ��M����;
	���Ӕ��M����.clear();
}

//�ؾ�����
void RenderThread::VehicleThread()
{
	std::vector<vehicle> �ؾ����黺��;
	auto ��ʱ���� = vehicle();
	auto _pushback = [&](vehicle Temp, ImColor color)
	{
		if (Temp.RootComponent > 65536)
		{
			FVector Location = G::Mem.��ɢ��д<FVector>(��ɢ.�ؾ߷�ɢ, Temp.RootComponent + offsets::Position);
			��ʱ����.pActor = Temp.pActor;
			��ʱ����.Location = Location;
			//printf("%f %f %f\n", ��ʱ����.Location.x, ��ʱ����.Location.y, ��ʱ����.Location.z);
			��ʱ����.Name = Temp.Name;
			��ʱ����.Color = color;
			�ؾ����黺��.push_back(vehicle(��ʱ����));
		}
		

	};
	
	{
		G::Mem.ScatterClear(��ɢ.�ؾ߷�ɢ, 1);
		for (auto Temp : G::engine->��_�ؾ�����)
		{
			if (Temp.RootComponent > 65536)
				G::Mem.ScatterPrepare(��ɢ.�ؾ߷�ɢ, Temp.RootComponent + offsets::Position, sizeof(FVector));
		}
		G::Mem.ExecuteRead(��ɢ.�ؾ߷�ɢ);

		for (auto Temp : G::engine->��_�ؾ�����)
		{
			_pushback(Temp, Temp.Color);
		}
	}
	G::render.����õ��ؾ����� = �ؾ����黺��;
	�ؾ����黺��.clear();
}

//��������
void RenderThread::DebugThread()
{
	std::vector<Actor> tmp_pActor;
	auto tmppActor = Actor();
	
	G::Mem.ScatterClear(��ɢ.ScatterDebug, 1);
	for (auto Temp : G::engine->��������)
	{
		if (Temp.RootComponent > 65536)
			G::Mem.ScatterPrepare(��ɢ.ScatterDebug, Temp.RootComponent + offsets::Position, sizeof(FVector));
	}
	G::Mem.ExecuteRead(��ɢ.ScatterDebug);

	for (auto Temp : G::engine->��������)
	{
			
		if (Temp.RootComponent > 65536)
		{
			FVector Location = G::Mem.��ɢ��д<FVector>(��ɢ.ScatterDebug, Temp.RootComponent + offsets::Position);
			tmppActor.pActor = Temp.pActor;
			tmppActor.Location = Location;

			tmppActor.Name = Temp.Name;
			tmppActor.Color = ImColor(255,255,0);
			tmp_pActor.push_back(tmppActor);
		}

	}
	
	G::render.�������� = tmp_pActor;
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
	//CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)����_�������, 0, 0, 0));
	//CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)����_��Ʒ����, 0, 0, 0));
}

FVector Render::������Ʒ(FVector ItemScreenLocation) {
	for (ULONG i = 0; i < Game::DrawOverlay::ItemList.size(); i++)
	{
		
		if (ItemScreenLocation.x > Game::DrawOverlay::ItemList[i].x - 80.f && ItemScreenLocation.x < Game::DrawOverlay::ItemList[i].x + 80.f
			&& ItemScreenLocation.y > Game::DrawOverlay::ItemList[i].y - 16.f && ItemScreenLocation.y < Game::DrawOverlay::ItemList[i].y + 16.f)
		{
			ItemScreenLocation = Game::DrawOverlay::ItemList[i];
			ItemScreenLocation.y = ItemScreenLocation.y - 18.f * 0.8 ;

			//��������.Y �� ��������.Y �� 16 �� 0.8
			
		}
	}
	return ItemScreenLocation;
}
BOOL Render::DrawItem(string PackageItemName, OUT FVector* ItemScreenLocation,ImColor Color , FLOAT EntityDistance) {
	/*EntityNameIDTypeMap PackageEntityObjName = FindEntityObjName(PackageItemObjID); if (PackageEntityObjName.Type == EntityType::Unknowns) { return false; }
	ImVec4 ͸����ɫ;
	if (PackageEntityObjName.Follow) { if (Menu::����͸��::͸�ӿ���::����) ͸����ɫ = Menu::����͸��::͸����ɫ::����; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Weapon) { if (Menu::����͸��::͸�ӿ���::����) ͸����ɫ = Menu::����͸��::͸����ɫ::����; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Accessories) { if (Menu::����͸��::͸�ӿ���::���) ͸����ɫ = Menu::����͸��::͸����ɫ::���; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Drug) { if (Menu::����͸��::͸�ӿ���::ҽ��) ͸����ɫ = Menu::����͸��::͸����ɫ::ҽ��; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Armor) { if (Menu::����͸��::͸�ӿ���::����) ͸����ɫ = Menu::����͸��::͸����ɫ::����; else return false; }
	else if (PackageEntityObjName.Type == EntityType::Grenade) { if (Menu::����͸��::͸�ӿ���::Ͷ��) ͸����ɫ = Menu::����͸��::͸����ɫ::Ͷ��; else return false; }
	else return false;*/
	
	if (EntityDistance > 1.0f) ItemScreenLocation->z = �����ı�2(ItemScreenLocation->x, ItemScreenLocation->y, 0,Color, u8"%s[%.0f]", PackageItemName.c_str(), EntityDistance);
	else {
		FLOAT ItemScreenLocationX = ItemScreenLocation->z > 0.0f ? ItemScreenLocation->z : ItemScreenLocation->x;
		//ItemScreenLocationX -= F::Global.GameData.�´���W;
		draw::�����ı�(ItemScreenLocationX, ItemScreenLocation->y,0,Color, u8"|%s", PackageItemName.c_str());
	}
	

	return true;
}
BOOL Render::DrawItem(string PackageItemObjName, FVector2 ItemScreenLocation, ImColor Color, FLOAT EntityDistance) {
	FLOAT ItemScreenLocationX = ItemScreenLocation.X;
	FLOAT ItemScreenLocationY = ItemScreenLocation.Y;
	FVector ItemScreenLocation3 = FVector(ItemScreenLocationX, ItemScreenLocationY, 0.0f);
	ItemScreenLocation3 = ������Ʒ(ItemScreenLocation3);
	EntityDistance = ItemScreenLocationX != ItemScreenLocation3.x || ItemScreenLocationY != ItemScreenLocation3.y ? 0 : EntityDistance;
	if (DrawItem(PackageItemObjName, &ItemScreenLocation3, Color, EntityDistance)) {
		
		Game::DrawOverlay::ItemList.push_back(ItemScreenLocation3);
		return true;
	}
	return false;

}