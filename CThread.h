#pragma once
#include "Engine.h"
#include "Game.h"
#include "util.hpp"

namespace CThread
{
	void Cache�߳�();


	void ��ȡ����();

	void GetPlayerWeaponData();

	void GetPlayerData();

	void RadarData();


	namespace RenderThread
	{

		void DebugThread();

		void VehicleThread();

		void ItemThread();

		void GrounpBoxThread();

		void ItemGroupThread();


	}

	
}
