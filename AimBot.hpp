#pragma once
#include "Features/Global.h"
#include "kmbox/KMSeria.h"
#include "Engine.h"
namespace AimControl
{
	static int HotKey = 6;	// ��׼�ȼ�
	static float AimRange = 300;	// ��׼��Χ




	inline void AimBot()
	{
		while (true)
		{
			int FPS���� = F::Global.Menu.����֡��;
			DWORD64	once_time = 1000 / F::Global.Menu.����֡��;
			DWORD64 start, end;

			start = timeGetTime();
			{
				if (F::Global.Menu.����������״̬)
				{
					if (F::Global.Aim.�����ַ != 0)
					{
						//printf("�������%p\n", F::Global.Aim.�����ַ);
						FVector pm{};
						FVector Target{};
						float Distance;
						if (SDK::WorldToScreen_Aim(F::Global.Aim.��������, &pm, &Distance))
						{
							
							//this->��������({ pm.X , pm.Y }, { (float)+F::Global.GameData.Width,(float)+F::Global.GameData.Height }, ImColor(255, 255, 255));
							////��������������������
							//if (IsKeyDown(1))//F::Global.KeyBind.isAim)
							//{
							//	printf(" pm.X [%f] pm.Y [%f]\n", pm.x, pm.y);
							//}
							
							if (IsKeyDown(F::Global.Menu.���鰴��))//F::Global.KeyBind.isAim)
							{
								F::Global.Aim.���� = true;
								//����
								if (true)
								{

									float X���ٶ� = F::Global.Menu.����X��;
									float Y���ٶ� = F::Global.Menu.����Y��;

									Target.x = (pm.x - F::Global.GameData.Width) / 1.0f / X���ٶ�;
									Target.y = (pm.y - F::Global.GameData.Height) / 1.0f / Y���ٶ�;

									Target.Normalize();
									if (F::Global.Menu.�������� == 0)
										G::kmbox.move((int)Target.x, (int)Target.y);
									if (F::Global.Menu.�������� == 1)
										mouse_event(MOUSEEVENTF_MOVE, (int)Target.x, (int)Target.y, 0, 0);
									
								}
								else
								{
									F::Global.Aim.���� = false;
									F::Global.Aim.�����ַ = 0;
									F::Global.Aim.�������� = {};
									F::Global.Aim.��Ļ��ǰ = F::Global.Menu.����FOV;
								}
							}
							else
							{
								F::Global.Aim.���� = false;
								F::Global.Aim.�����ַ = 0;
								F::Global.Aim.�������� = {};
								F::Global.Aim.��Ļ��ǰ = F::Global.Menu.����FOV;
							}

						}
					}
					else
					{
						F::Global.Aim.���� = false;
						F::Global.Aim.�����ַ = 0;
						F::Global.Aim.�������� = {};
						F::Global.Aim.��Ļ��ǰ = F::Global.Menu.����FOV;
					}
				}


			}
			end = timeGetTime();
			int remain_time = once_time - (end - start);
			if (remain_time >= 0)
			{
				Sleep(remain_time);
			}

		}
	}

	inline void Attach()
	{
		std::thread(AimBot).detach();

	}
}