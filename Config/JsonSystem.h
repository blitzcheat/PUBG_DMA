#pragma once
#include "Json/json.h"
#include "../Includes.h"

enum ConfigHandle : int {
	Save = 0,
	Load = 1,
	Reset = 2
};

namespace JsonSystem
{
	inline json To_JsonColor(const ImColor clr)
	{
		json Json;

		Json["r"] = clr.Value.x;
		Json["g"] = clr.Value.y;
		Json["b"] = clr.Value.z;
		Json["a"] = clr.Value.w;

		return Json;
	}


	inline ImColor From_JsonColor(const json json)
	{
		ImColor clr;

		clr.Value.x = json["r"];
		clr.Value.y = json["g"];
		clr.Value.z = json["b"];
		clr.Value.w = json["a"];

		return clr;
	}


	template <class T>
	inline constexpr T CreatConfigItem(json& j, ConfigHandle handle, T* setting, T defaultValue)
	{
		switch (handle)
		{
		case ConfigHandle::Save:
			j = *(T*)setting;
			break;
		case ConfigHandle::Load:
			*(T*)setting = j;
			break;
		case ConfigHandle::Reset:
			*setting = defaultValue;
			break;

		}
		return *setting;
	}

	inline void CreatConfigColor(json& j, ConfigHandle handle, ImColor& setting, ImColor defaultValue)
	{
		switch (handle)
		{
		case ConfigHandle::Save:
			j = To_JsonColor(setting);
			break;
		case ConfigHandle::Load:
			setting = From_JsonColor(j);
			break;
		case ConfigHandle::Reset:
			setting = defaultValue;
			break;
		}
	}

	inline void CreatConfig(ConfigHandle handle, const char* fileName)
	{
		std::string Body = "Config/";
		std::string FileNmae = fileName;
		std::string FilePath = Body + FileNmae;

		json parameters;

		if (handle == ConfigHandle::Load)
		{
			std::ifstream i(FilePath.c_str());
			if (!i.good()) {
				CreatConfig(ConfigHandle::Save, fileName);
				return CreatConfig(ConfigHandle::Load, fileName);
			}
			i >> parameters;
		}

		try
		{
			//CreatConfigItem(parameters["Menu"]["1"], handle, &cfg.菜单, false);

			//————————————————————————————————————————————————————
			//自瞄区
			CreatConfigItem(parameters["AimBot"]["AimKey"], handle, &F::Global.Menu.自瞄按键, 5);
			CreatConfigItem(parameters["AimBot"]["AimKey2"], handle, &F::Global.Menu.自瞄子按键, VK_LSHIFT);
			CreatConfigItem(parameters["AimBot"]["AimKeymerge"], handle, &F::Global.Menu.热键合并, false);
			CreatConfigItem(parameters["AimBot"]["AimType"], handle, &F::Global.Menu.自瞄类型, 0);
			CreatConfigItem(parameters["AimBot"]["AimParts"], handle, &F::Global.Menu.自瞄位置, 6);
			CreatConfigItem(parameters["AimBot"]["AimPartsWindow_menu_button_position"], handle, &F::Global.Menu.window_menu_button_position, 0);
			CreatConfigItem(parameters["AimBot"]["AimPartsWindow"], handle, &F::Global.Menu.自瞄部位列表索引, 0);


			
			CreatConfigItem(parameters["AimBot"]["AimSpeed"], handle, &F::Global.Menu.自瞄速度, 2.00f);
			CreatConfigItem(parameters["AimBot"]["AimFOV"], handle, &F::Global.Menu.自瞄FOV, 80.0f);
			CreatConfigItem(parameters["AimBot"]["AimFps"], handle, &F::Global.Menu.自瞄帧数, 60.0f);
			CreatConfigItem(parameters["AimBot"]["AimVisible"], handle, &F::Global.Menu.可视判断, true);
			CreatConfigItem(parameters["AimBot"]["AimXspeed"], handle, &F::Global.Menu.自瞄X速, 10.0f);
			CreatConfigItem(parameters["AimBot"]["AimYspeed"], handle, &F::Global.Menu.自瞄Y速, 12.0f);
			CreatConfigItem(parameters["AimBot"]["AimBotKey"], handle, &F::Global.Menu.扳机按键, 6);
			CreatConfigItem(parameters["AimBot"]["AimBotspeed"], handle, &F::Global.Menu.扳机延迟, 10.0f);

			//CreatConfigItem(parameters["AimBot"]["AimKMBOX_COM"], handle, &F::Global.Menu.KMBOX端口号, 6);
			CreatConfigItem(parameters["AimBot"]["AimKMBOX_SUOY"], handle, &F::Global.Menu.端口索引值, 0);


			float 波特率 = std::stof(F::Global.Menu.控制器波特率);
			CreatConfigItem(parameters["AimBot"]["AimKMBOX_COMbr"], handle, &波特率, 115200.f);
			char 波特率_str[128];
			std::sprintf(波特率_str, "%.f", 波特率);
			strcpy(F::Global.Menu.控制器波特率, 波特率_str);


			//————————————————————————————————————————————————————
			//透视区
			CreatConfigItem(parameters["Esp"]["COMPEsp"], handle, &F::Global.GameData.串流模式, true);

			CreatConfigItem(parameters["Esp"]["AllEsp"], handle, &F::Global.Menu.透视开关, true);
			CreatConfigItem(parameters["Esp"]["EspFOV"], handle, &F::Global.Menu.FOV显示, true);

			
			CreatConfigItem(parameters["Esp"]["pESP1"], handle, &F::Global.Menu.玩家方框, true);
			CreatConfigItem(parameters["Esp"]["pESP2"], handle, &F::Global.Menu.玩家骨骼, true);
			CreatConfigItem(parameters["Esp"]["pESP3"], handle, &F::Global.Menu.玩家射线, true);
			CreatConfigItem(parameters["Esp"]["pESP4"], handle, &F::Global.Menu.玩家血条, true);
			CreatConfigItem(parameters["Esp"]["pESP5"], handle, &F::Global.Menu.玩家信息, true);
			CreatConfigItem(parameters["Esp"]["pESP6"], handle, &F::Global.Menu.队友显示, true);
			CreatConfigItem(parameters["Esp"]["pESP7"], handle, &F::Global.Menu.骨骼粗细, 1.0f);

			CreatConfigItem(parameters["Esp"]["item1"], handle, &F::Global.MenuE.Item1, true);
			CreatConfigItem(parameters["Esp"]["item2"], handle, &F::Global.MenuE.Item2, true);
			CreatConfigItem(parameters["Esp"]["item3"], handle, &F::Global.MenuE.Item3, true);
			CreatConfigItem(parameters["Esp"]["item4"], handle, &F::Global.MenuE.Item4, true);
			CreatConfigItem(parameters["Esp"]["item5"], handle, &F::Global.MenuE.Item5, true);
			CreatConfigItem(parameters["Esp"]["item6"], handle, &F::Global.MenuE.Item6, true);
			CreatConfigItem(parameters["Esp"]["item7"], handle, &F::Global.MenuE.Item7, true);
			CreatConfigItem(parameters["Esp"]["item8"], handle, &F::Global.MenuE.Item8, true);
			CreatConfigItem(parameters["Esp"]["item9"], handle, &F::Global.MenuE.Item9, true);
			CreatConfigItem(parameters["Esp"]["item10"], handle, &F::Global.MenuE.Item10, true);
			CreatConfigItem(parameters["Esp"]["item11"], handle, &F::Global.MenuE.Item11, true);
			CreatConfigItem(parameters["Esp"]["item12"], handle, &F::Global.MenuE.Item12, true);
			CreatConfigItem(parameters["Esp"]["item13"], handle, &F::Global.MenuE.Item13, true);
			CreatConfigItem(parameters["Esp"]["Radar"], handle, &F::Global.Menu.雷达, true);
			CreatConfigItem(parameters["Esp"]["RadarRange"], handle, &F::Global.Menu.RadarRange, 150.f);

			CreatConfigItem(parameters["Esp"]["RadarPointSizeProportion"], handle, &F::Global.Menu.RadarPointSizeProportion, 1.f);


			CreatConfigItem(parameters["Esp"]["RadarType"], handle, &F::Global.Menu.RadarType, 1);

			CreatConfigItem(parameters["Esp"]["Proportion"], handle, &F::Global.Menu.Proportion, 220.f);

			CreatConfigItem(parameters["Esp"]["RadarX"], handle, &F::Global.Menu.RadarX, 0.f);

			CreatConfigItem(parameters["Esp"]["RadarY"], handle, &F::Global.Menu.RadarY, 0.f);


			float WindowX = std::stof(F::Global.Menu.新窗口X_);
			float WindowY = std::stof(F::Global.Menu.新窗口Y_);
			float WindowW = std::stof(F::Global.Menu.新窗口W_);
			float WindowH = std::stof(F::Global.Menu.新窗口H_);
			CreatConfigItem(parameters["Other"]["EspWindowX"], handle, &WindowX, 2560.f);
			CreatConfigItem(parameters["Other"]["EspWindowY"], handle, &WindowY, 0.f);
			CreatConfigItem(parameters["Other"]["EspWindowW"], handle, &WindowW, 2560.f);
			CreatConfigItem(parameters["Other"]["EspWindowH"], handle, &WindowH, 1440.f);

			char 新窗口X_str[128];
			char 新窗口Y_str[128];
			char 新窗口W_str[128];
			char 新窗口H_str[128];

			std::sprintf(新窗口X_str, "%.f", WindowX);
			std::sprintf(新窗口Y_str, "%.f", WindowY);
			std::sprintf(新窗口W_str, "%.f", WindowW);
			std::sprintf(新窗口H_str, "%.f", WindowH);

			strcpy(F::Global.Menu.新窗口X_, 新窗口X_str);
			strcpy(F::Global.Menu.新窗口Y_, 新窗口Y_str);
			strcpy(F::Global.Menu.新窗口W_, 新窗口W_str);
			strcpy(F::Global.Menu.新窗口H_, 新窗口H_str);

			//printf(u8"%s\n", 新窗口X_str);
			//printf(u8"%s\n", 新窗口Y_str);
			//printf(u8"%s\n", 新窗口W_str);
			//printf(u8"%s\n", 新窗口H_str);

			F::Global.GameData.新窗口X = (int)WindowX;
			F::Global.GameData.新窗口Y = (int)WindowY;
			F::Global.GameData.新窗口W = (int)WindowW;
			F::Global.GameData.新窗口H = (int)WindowH;

			//设置矩阵W H
			F::Global.GameData.Width = (int)WindowW / 2;
			F::Global.GameData.Height = (int)WindowH / 2;

			
			glfwSetWindowPos(window1, F::Global.GameData.新窗口X, F::Global.GameData.新窗口Y);//移动窗口
			glfwSetWindowSize(window1, F::Global.GameData.新窗口W, F::Global.GameData.新窗口H);//改变窗口大小


			//物品 与 物品组
			


			for (size_t i = 0; i < F::Global.Menu.itemgrounp.size(); i++)
			{
				CreatConfigItem(parameters["ItemGrounp"]["GrounpIndex"][i], handle, &F::Global.Menu.itemgrounp[i].物品组, 0);
			}
			
		
		}
		catch (...)
		{
			//走到这就代表有些参数之前没保存，现在先执行一次Save再进行load
			CreatConfig(ConfigHandle::Save, fileName);
			return CreatConfig(ConfigHandle::Load, fileName);
		}

		if (handle == ConfigHandle::Save)
		{
			std::ofstream file(FilePath.c_str());
			if (file.is_open())
			{
				file << parameters;
				file.close();
			}
		}

		if (handle == ConfigHandle::Reset)
		{
			CreatConfig(ConfigHandle::Save, fileName);
			return CreatConfig(ConfigHandle::Load, fileName);
		}
	}

	inline void HandleConfig(const char* configName, ConfigHandle handle)
	{
		try {
			CreatConfig(handle, configName);
		}
		catch (...)
		{
			CreatConfig(ConfigHandle::Save, configName);
			CreatConfig(ConfigHandle::Load, configName);
		}
	}
}

