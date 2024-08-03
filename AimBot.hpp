#pragma once
#include "Features/Global.h"
#include "kmbox/KMSeria.h"
#include "Engine.h"
namespace AimControl
{
	static int HotKey = 6;	// 瞄准热键
	static float AimRange = 300;	// 瞄准范围




	inline void AimBot()
	{
		while (true)
		{
			int FPS限制 = F::Global.Menu.自瞄帧数;
			DWORD64	once_time = 1000 / F::Global.Menu.自瞄帧数;
			DWORD64 start, end;

			start = timeGetTime();
			{
				if (F::Global.Menu.自瞄器连接状态)
				{
					if (F::Global.Aim.自瞄地址 != 0)
					{
						//printf("自瞄对象%p\n", F::Global.Aim.自瞄地址);
						FVector pm{};
						FVector Target{};
						float Distance;
						if (SDK::WorldToScreen_Aim(F::Global.Aim.自瞄坐标, &pm, &Distance))
						{
							
							//this->绘制线条({ pm.X , pm.Y }, { (float)+F::Global.GameData.Width,(float)+F::Global.GameData.Height }, ImColor(255, 255, 255));
							////——————————
							//if (IsKeyDown(1))//F::Global.KeyBind.isAim)
							//{
							//	printf(" pm.X [%f] pm.Y [%f]\n", pm.x, pm.y);
							//}
							
							if (IsKeyDown(F::Global.Menu.自瞄按键))//F::Global.KeyBind.isAim)
							{
								F::Global.Aim.锁定 = true;
								//开锁
								if (true)
								{

									float X轴速度 = F::Global.Menu.自瞄X速;
									float Y轴速度 = F::Global.Menu.自瞄Y速;

									Target.x = (pm.x - F::Global.GameData.Width) / 1.0f / X轴速度;
									Target.y = (pm.y - F::Global.GameData.Height) / 1.0f / Y轴速度;

									Target.Normalize();
									if (F::Global.Menu.自瞄类型 == 0)
										G::kmbox.move((int)Target.x, (int)Target.y);
									if (F::Global.Menu.自瞄类型 == 1)
										mouse_event(MOUSEEVENTF_MOVE, (int)Target.x, (int)Target.y, 0, 0);
									
								}
								else
								{
									F::Global.Aim.锁定 = false;
									F::Global.Aim.自瞄地址 = 0;
									F::Global.Aim.自瞄坐标 = {};
									F::Global.Aim.屏幕当前 = F::Global.Menu.自瞄FOV;
								}
							}
							else
							{
								F::Global.Aim.锁定 = false;
								F::Global.Aim.自瞄地址 = 0;
								F::Global.Aim.自瞄坐标 = {};
								F::Global.Aim.屏幕当前 = F::Global.Menu.自瞄FOV;
							}

						}
					}
					else
					{
						F::Global.Aim.锁定 = false;
						F::Global.Aim.自瞄地址 = 0;
						F::Global.Aim.自瞄坐标 = {};
						F::Global.Aim.屏幕当前 = F::Global.Menu.自瞄FOV;
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