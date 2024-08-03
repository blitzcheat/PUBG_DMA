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
			//CreatConfigItem(parameters["Menu"]["1"], handle, &cfg.�˵�, false);

			//��������������������������������������������������������������������������������������������������������
			//������
			CreatConfigItem(parameters["AimBot"]["AimKey"], handle, &F::Global.Menu.���鰴��, 5);
			CreatConfigItem(parameters["AimBot"]["AimKey2"], handle, &F::Global.Menu.�����Ӱ���, VK_LSHIFT);
			CreatConfigItem(parameters["AimBot"]["AimKeymerge"], handle, &F::Global.Menu.�ȼ��ϲ�, false);
			CreatConfigItem(parameters["AimBot"]["AimType"], handle, &F::Global.Menu.��������, 0);
			CreatConfigItem(parameters["AimBot"]["AimParts"], handle, &F::Global.Menu.����λ��, 6);
			CreatConfigItem(parameters["AimBot"]["AimPartsWindow_menu_button_position"], handle, &F::Global.Menu.window_menu_button_position, 0);
			CreatConfigItem(parameters["AimBot"]["AimPartsWindow"], handle, &F::Global.Menu.���鲿λ�б�����, 0);


			
			CreatConfigItem(parameters["AimBot"]["AimSpeed"], handle, &F::Global.Menu.�����ٶ�, 2.00f);
			CreatConfigItem(parameters["AimBot"]["AimFOV"], handle, &F::Global.Menu.����FOV, 80.0f);
			CreatConfigItem(parameters["AimBot"]["AimFps"], handle, &F::Global.Menu.����֡��, 60.0f);
			CreatConfigItem(parameters["AimBot"]["AimVisible"], handle, &F::Global.Menu.�����ж�, true);
			CreatConfigItem(parameters["AimBot"]["AimXspeed"], handle, &F::Global.Menu.����X��, 10.0f);
			CreatConfigItem(parameters["AimBot"]["AimYspeed"], handle, &F::Global.Menu.����Y��, 12.0f);
			CreatConfigItem(parameters["AimBot"]["AimBotKey"], handle, &F::Global.Menu.�������, 6);
			CreatConfigItem(parameters["AimBot"]["AimBotspeed"], handle, &F::Global.Menu.����ӳ�, 10.0f);

			//CreatConfigItem(parameters["AimBot"]["AimKMBOX_COM"], handle, &F::Global.Menu.KMBOX�˿ں�, 6);
			CreatConfigItem(parameters["AimBot"]["AimKMBOX_SUOY"], handle, &F::Global.Menu.�˿�����ֵ, 0);


			float ������ = std::stof(F::Global.Menu.������������);
			CreatConfigItem(parameters["AimBot"]["AimKMBOX_COMbr"], handle, &������, 115200.f);
			char ������_str[128];
			std::sprintf(������_str, "%.f", ������);
			strcpy(F::Global.Menu.������������, ������_str);


			//��������������������������������������������������������������������������������������������������������
			//͸����
			CreatConfigItem(parameters["Esp"]["COMPEsp"], handle, &F::Global.GameData.����ģʽ, true);

			CreatConfigItem(parameters["Esp"]["AllEsp"], handle, &F::Global.Menu.͸�ӿ���, true);
			CreatConfigItem(parameters["Esp"]["EspFOV"], handle, &F::Global.Menu.FOV��ʾ, true);

			
			CreatConfigItem(parameters["Esp"]["pESP1"], handle, &F::Global.Menu.��ҷ���, true);
			CreatConfigItem(parameters["Esp"]["pESP2"], handle, &F::Global.Menu.��ҹ���, true);
			CreatConfigItem(parameters["Esp"]["pESP3"], handle, &F::Global.Menu.�������, true);
			CreatConfigItem(parameters["Esp"]["pESP4"], handle, &F::Global.Menu.���Ѫ��, true);
			CreatConfigItem(parameters["Esp"]["pESP5"], handle, &F::Global.Menu.�����Ϣ, true);
			CreatConfigItem(parameters["Esp"]["pESP6"], handle, &F::Global.Menu.������ʾ, true);
			CreatConfigItem(parameters["Esp"]["pESP7"], handle, &F::Global.Menu.������ϸ, 1.0f);

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
			CreatConfigItem(parameters["Esp"]["Radar"], handle, &F::Global.Menu.�״�, true);
			CreatConfigItem(parameters["Esp"]["RadarRange"], handle, &F::Global.Menu.RadarRange, 150.f);

			CreatConfigItem(parameters["Esp"]["RadarPointSizeProportion"], handle, &F::Global.Menu.RadarPointSizeProportion, 1.f);


			CreatConfigItem(parameters["Esp"]["RadarType"], handle, &F::Global.Menu.RadarType, 1);

			CreatConfigItem(parameters["Esp"]["Proportion"], handle, &F::Global.Menu.Proportion, 220.f);

			CreatConfigItem(parameters["Esp"]["RadarX"], handle, &F::Global.Menu.RadarX, 0.f);

			CreatConfigItem(parameters["Esp"]["RadarY"], handle, &F::Global.Menu.RadarY, 0.f);


			float WindowX = std::stof(F::Global.Menu.�´���X_);
			float WindowY = std::stof(F::Global.Menu.�´���Y_);
			float WindowW = std::stof(F::Global.Menu.�´���W_);
			float WindowH = std::stof(F::Global.Menu.�´���H_);
			CreatConfigItem(parameters["Other"]["EspWindowX"], handle, &WindowX, 2560.f);
			CreatConfigItem(parameters["Other"]["EspWindowY"], handle, &WindowY, 0.f);
			CreatConfigItem(parameters["Other"]["EspWindowW"], handle, &WindowW, 2560.f);
			CreatConfigItem(parameters["Other"]["EspWindowH"], handle, &WindowH, 1440.f);

			char �´���X_str[128];
			char �´���Y_str[128];
			char �´���W_str[128];
			char �´���H_str[128];

			std::sprintf(�´���X_str, "%.f", WindowX);
			std::sprintf(�´���Y_str, "%.f", WindowY);
			std::sprintf(�´���W_str, "%.f", WindowW);
			std::sprintf(�´���H_str, "%.f", WindowH);

			strcpy(F::Global.Menu.�´���X_, �´���X_str);
			strcpy(F::Global.Menu.�´���Y_, �´���Y_str);
			strcpy(F::Global.Menu.�´���W_, �´���W_str);
			strcpy(F::Global.Menu.�´���H_, �´���H_str);

			//printf(u8"%s\n", �´���X_str);
			//printf(u8"%s\n", �´���Y_str);
			//printf(u8"%s\n", �´���W_str);
			//printf(u8"%s\n", �´���H_str);

			F::Global.GameData.�´���X = (int)WindowX;
			F::Global.GameData.�´���Y = (int)WindowY;
			F::Global.GameData.�´���W = (int)WindowW;
			F::Global.GameData.�´���H = (int)WindowH;

			//���þ���W H
			F::Global.GameData.Width = (int)WindowW / 2;
			F::Global.GameData.Height = (int)WindowH / 2;

			
			glfwSetWindowPos(window1, F::Global.GameData.�´���X, F::Global.GameData.�´���Y);//�ƶ�����
			glfwSetWindowSize(window1, F::Global.GameData.�´���W, F::Global.GameData.�´���H);//�ı䴰�ڴ�С


			//��Ʒ �� ��Ʒ��
			


			for (size_t i = 0; i < F::Global.Menu.itemgrounp.size(); i++)
			{
				CreatConfigItem(parameters["ItemGrounp"]["GrounpIndex"][i], handle, &F::Global.Menu.itemgrounp[i].��Ʒ��, 0);
			}
			
		
		}
		catch (...)
		{
			//�ߵ���ʹ�����Щ����֮ǰû���棬������ִ��һ��Save�ٽ���load
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

