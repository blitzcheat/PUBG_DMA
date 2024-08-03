#pragma once
#include "Includes.h"
#include "Memory.h"
#include "offset.h"
#include "struct.h"
#include "Features/Global.h"
#include<codecvt>
#define _WORD  uint16_t
#define WORD1(x)   (*((_WORD*)&(x)+1))


typedef uint64_t(__fastcall* Decrypt_)(int sed, uint64_t ShieldDet);
inline Decrypt_ Decrypt_Call = { 0 };
inline vector<BYTE> ReadBYTE(uint64_t ptr, SIZE_T size)
{
	vector<BYTE> BYTES;
	for (auto i = 0; i < size; i++) {
		BYTES.push_back(G::Mem.Read<BYTE>(ptr++));
	}
	return BYTES;
}
namespace SDK
{
	
	inline bool DecryptInit(uint64_t Encrypt)
	{
		BYTE ShieIDcode[100] = { NULL };

		int DecryptID = 0;
		do {
			DecryptID++;
		} while (ReadBYTE(Encrypt + DecryptID, 3) != vector<BYTE>{ 72, 139, 193 });

		SIZE_T Legth = DecryptID - 3;
		uint64_t DecryptRax = Encrypt + G::Mem.Read<int>(Encrypt + 3) + 7;
		uint64_t DecryptAdd = (uint64_t)VirtualAlloc(0, Legth * 2, 4096, 64);
		if (!DecryptAdd)
			return false;
		*(BYTE*)DecryptAdd = 72;
		*(BYTE*)(DecryptAdd + 1) = 184;
		*(uint64_t*)(DecryptAdd + 2) = DecryptRax;

		G::Mem.ReadMemory(Encrypt + 7, ShieIDcode, Legth);
		CopyMemory((PVOID)(DecryptAdd + 10), ShieIDcode, Legth);

		Decrypt_Call = (Decrypt_)DecryptAdd;
		return Decrypt_Call != 0;
	}
	inline DWORD DecryptIndex(DWORD value)
	{
		UINT32 v10, result;
		if (offsets::PZ == 1)
			v10 = _rotr(value ^ offsets::DecryptOne, offsets::TableOne);
		else
			v10 = _rotl(value ^ offsets::DecryptOne, offsets::TableOne);
		result = v10 ^ (v10 << offsets::TableTwo) ^ offsets::DecryptTwo;

		return result;
	}

	inline ULONG DecryptID(uint64_t a1)
	{
		if (a1 <= 65536) return 0;
		return DecryptIndex(G::Mem.Read<int>(a1 + offsets::OBJid));
	}
	inline uint64_t DecryptCall(uint64_t a1)
	{
		return a1 != 0 ? Decrypt_Call(0, a1) : NULL;
	}
	inline uintptr_t GetUWorld()
	{
		return DecryptCall(G::Mem.Read<uint64_t>(G::Mem.GameBase + offsets::Uworld));
	}
	inline uintptr_t GetPersistent(uintptr_t Decrypt_UWorld)
	{
		return DecryptCall(G::Mem.Read<uint64_t>(Decrypt_UWorld + offsets::Leve));
	}
	inline uintptr_t GetActors(uintptr_t Decrypt_Persistent)
	{
		return DecryptCall(G::Mem.Read<uint64_t>(Decrypt_Persistent + offsets::Actor));
	}

	inline uintptr_t GetGameInstance(uintptr_t Decrypt_UWorld)
	{
		return DecryptCall(G::Mem.Read<uint64_t>(Decrypt_UWorld + offsets::GameInstence));
	}
	inline uintptr_t GetPlayerController(uintptr_t Decrypt_GameInstance)
	{
		uintptr_t LocalPlayer = DecryptCall(G::Mem.Read<uint64_t>(G::Mem.Read<uint64_t>(Decrypt_GameInstance + offsets::LocalPlayer)));
		//printf("LocalPlayer %p\n", LocalPlayer);
		return DecryptCall(G::Mem.Read<uint64_t>(LocalPlayer + offsets::PlayerController));
	}
	inline uintptr_t GetAcknowledgedPawn(uintptr_t Decrypt_PlayerController)
	{
		return DecryptCall(G::Mem.Read<uint64_t>(Decrypt_PlayerController + offsets::AcknowledgedPawn));
	}
	inline uintptr_t GetRootComponent(uintptr_t Decrypt_AcknowledgedPawn)
	{
		return DecryptCall(G::Mem.Read<uint64_t>(Decrypt_AcknowledgedPawn + offsets::m_rootComponent));
	}
	inline uintptr_t GetGNames()
	{
		uintptr_t GNames = DecryptCall(G::Mem.Read<uint64_t>(G::Mem.GameBase + offsets::GNames));
		return DecryptCall(G::Mem.Read<uint64_t>(GNames));
	}
	inline uintptr_t GetCameraManager(uintptr_t Decrypt_PlayerController)
	{
		return G::Mem.Read<uint64_t>(Decrypt_PlayerController + offsets::PlayerCameraManager);
	}
	inline std::string GetNames(DWORD ID)
	{
		std::string emp = "Unknown";
		if (ID <= 0) return emp;
		uint32_t IdDiv = ID / offsets::IDD;
		uint32_t Idtemp = ID % offsets::IDD;
		uint64_t Serial = G::Mem.Read<uint64_t>(Data.GNames + IdDiv * 0x8);
		if (!Serial || Serial < 0x100000)
			return emp;
		uint64_t pName = G::Mem.Read<uint64_t>(Serial + 0x8 * Idtemp);
		if (!pName || pName < 0x100000)
			return emp;
		StringA names = G::Mem.Read<StringA>(pName + 0x10);
		char te[256];
		memset(&te, 0, 256);
		if (memcmp(names.buffer, te, 256) == 0)
			return emp;
		std::string str(names.buffer);
		return str;
	}


	
	inline bool WorldScreen(FVector Location, FVector2* Screen, float* Distance)
	{
		if (Location.isZero()) return false;
		FVector Temp = FVector(0, 0, 0);
		float X, Y, Z;
		SubVector(Location, Local.CameraPos, &Temp);
		Z = DotProduct(Temp, Local.AxisX);
		if (Z < 100099) {
			if (Z > 1) {
				X = DotProduct(Temp, Local.AxisY);
				Y = DotProduct(Temp, Local.AxisZ);
				X = F::Global.GameData.Width + X * F::Global.GameData.Width / Local.Tangent / Z;
				Y = F::Global.GameData.Height - Y * F::Global.GameData.Width / Local.Tangent / Z;
				if (X <= 0 || Y <= 0) { return false; }
				Screen->X = X;
				Screen->Y = Y;
				*Distance = Z / 100;
				return true;
			}
			return false;
		}
		return false;
	}
	inline FVector GetBoneMatrix(DWORD64 Mesh, DWORD64 BoneArray, int id)
	{

		FTransform bone = G::Mem.∑÷…¢∂¡–¥<FTransform>(∑÷…¢.Ω·ππ∑÷…¢, BoneArray + (id * 0x30));
		FTransform ComponentToWorld = G::Mem.∑÷…¢∂¡–¥<FTransform>(∑÷…¢.Ω·ππ∑÷…¢, Mesh + offsets::BoneArry);
		FMatrix Matrix;
		Matrix = bone.ToMatrixWithScale().MatrixMultiplication(ComponentToWorld.ToMatrixWithScale());
		return FVector(Matrix._41, Matrix._42, Matrix._43);
	}
	inline void GetIndex(Index& index)
	{
		index.Õ∑≤ø = 35;//66ÃÏ¡È∏«
		index.æ±≤ø = 5;
		index.π«≈Ë = 1;
		index.◊ÛºÁ = 88;
		index.◊Û÷‚ = 89;
		index.◊Û ÷ = 90;
		index.”“ºÁ = 115;
		index.”“÷‚ = 116;
		index.”“ ÷ = 117;
		index.◊ÛÕŒ = 177;
		index.◊Ûœ• = 173;
		index.◊ÛΩ≈ = 174;
		index.”“ÕŒ = 183;
		index.”“œ• = 179;
		index.”“Ω≈ = 180;

	}
	inline std::wstring GetPlayName(uint64_t Ptr)
	{
		struct PNmae
		{
			wchar_t temp[64];
		};

		auto a = G::Mem.Read<PNmae>(Ptr);
		//if (!pname) return string("ÀØæı÷–");

		//auto playername = G::Mem.ReadEx<FString>(pname);
		std::wstring pName = a.temp;

		//std::wstring playerName = std::wstring(playername.PlayerName); //  π”√L«∞◊∫¿¥¥¥Ω®øÌ◊÷∑˚◊÷∑˚¥Æ◊÷√Ê¡ø
		//printf("%ws\n", pname.);
		return pName.c_str();
	}
	inline FLOAT GetAimDragForce(FLOAT Distance) {
		FLOAT Gravity = 1.33f;	
		PCSTR WeaponName = Local.LoaclWeaponData.WeaponName;
		if (Distance <= 250)
		{
			if (strcmp(WeaponName, u8"AKM") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"AUG") == 0) { Gravity = 1.25; }
			else if (strcmp(WeaponName, u8"QBZ") == 0) { Gravity = 0.5f; }
			else if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 0.7f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 0.6f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 0.55f; }
			else if (strcmp(WeaponName, u8"SCAR-L") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"M416") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"M16A4") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 0.45f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 0.55f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 0.45f; }
			else if (strcmp(WeaponName, u8"Groza") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"UMP9") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 0.5f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 0.55f; }
			else if (strcmp(WeaponName, u8"BerylM762") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"Mk47Mutant") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"G36C") == 0) { Gravity = 1.0f; }
			else { Gravity = 1.1f; }
		}
		else if (Distance <= 300)
		{
			if (strcmp(WeaponName, u8"AKM") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"AUG") == 0) { Gravity = 1.25f; }
			else if (strcmp(WeaponName, u8"QBZ") == 0) { Gravity = 0.5f; }
			else if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 0.8f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 0.9f; }
			else if (strcmp(WeaponName, u8"SCAR-L") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"M416") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"M16A4") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 0.45f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 0.6f; }
			else if (strcmp(WeaponName, u8"Groza") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"UMP9") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 0.75f; }
			else if (strcmp(WeaponName, u8"BerylM762") == 0) { Gravity = 0.9f; }
			else if (strcmp(WeaponName, u8"Mk47Mutant") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"G36C") == 0) { Gravity = 1.0f; }
			else { Gravity = 1.1f; }
		}
		else if (Distance <= 350)
		{
			if (strcmp(WeaponName, u8"AKM") == 0) { Gravity = 1.5f; }
			else if (strcmp(WeaponName, u8"AUG") == 0) { Gravity = 1.4f; }
			else if (strcmp(WeaponName, u8"QBZ") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"SCAR-L") == 0) { Gravity = 1.3f; }
			else if (strcmp(WeaponName, u8"M416") == 0) { Gravity = 1.4f; }
			else if (strcmp(WeaponName, u8"M16A4") == 0) { Gravity = 1.3f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 0.9f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 1.1f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"Groza") == 0) { Gravity = 1.4f; }
			else if (strcmp(WeaponName, u8"UMP9") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 0.95f; }
			else if (strcmp(WeaponName, u8"BerylM762") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"Mk47Mutant") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"G36C") == 0) { Gravity = 1.2f; }
			else { Gravity = 1.2f; }
		}
		else if (Distance <= 400)
		{
			if (strcmp(WeaponName, u8"AKM") == 0) { Gravity = 1.82f; }
			else if (strcmp(WeaponName, u8"AUG") == 0) { Gravity = 1.65f; }
			else if (strcmp(WeaponName, u8"QBZ") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 1.4f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 1.35f; }
			else if (strcmp(WeaponName, u8"SCAR-L") == 0) { Gravity = 1.6f; }
			else if (strcmp(WeaponName, u8"M416") == 0) { Gravity = 1.6f; }
			else if (strcmp(WeaponName, u8"M16A4") == 0) { Gravity = 1.5f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 1.0f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 1.4f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 1.4f; }
			else if (strcmp(WeaponName, u8"Groza") == 0) { Gravity = 1.6f; }
			else if (strcmp(WeaponName, u8"UMP9") == 0) { Gravity = 1.5f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 1.15f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"BerylM762") == 0) { Gravity = 1.3f; }
			else if (strcmp(WeaponName, u8"Mk47Mutant") == 0) { Gravity = 1.5f; }
			else if (strcmp(WeaponName, u8"G36C") == 0) { Gravity = 1.4f; }
			else { Gravity = 1.5f; }
		}
		else if (Distance <= 450)
		{
			if (strcmp(WeaponName, u8"AKM") == 0) { Gravity = 2.15f; }
			else if (strcmp(WeaponName, u8"AUG") == 0) { Gravity = 2.0f; }
			else if (strcmp(WeaponName, u8"QBZ") == 0) { Gravity = 1.4f; }
			else if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 1.5f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 1.3f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 1.45f; }
			else if (strcmp(WeaponName, u8"SCAR-L") == 0) { Gravity = 1.9f; }
			else if (strcmp(WeaponName, u8"M416") == 0) { Gravity = 1.85f; }
			else if (strcmp(WeaponName, u8"M16A4") == 0) { Gravity = 1.75f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 1.2f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 1.7f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 1.45f; }
			else if (strcmp(WeaponName, u8"Groza") == 0) { Gravity = 2.1f; }
			else if (strcmp(WeaponName, u8"UMP9") == 0) { Gravity = 1.7f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 1.35f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 1.35f; }
			else if (strcmp(WeaponName, u8"BerylM762") == 0) { Gravity = 1.5f; }
			else if (strcmp(WeaponName, u8"Mk47Mutant") == 0) { Gravity = 1.7f; }
			else if (strcmp(WeaponName, u8"G36C") == 0) { Gravity = 1.61f; }
			else { Gravity = 1.7f; }
		}
		else if (Distance <= 500)
		{
			if (strcmp(WeaponName, u8"AKM") == 0) { Gravity = 2.45f; }
			else if (strcmp(WeaponName, u8"AUG") == 0) { Gravity = 2.1f; }
			else if (strcmp(WeaponName, u8"QBZ") == 0) { Gravity = 1.6f; }
			else if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 1.7f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 1.55f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 1.8f; }
			else if (strcmp(WeaponName, u8"SCAR-L") == 0) { Gravity = 2.15f; }
			else if (strcmp(WeaponName, u8"M416") == 0) { Gravity = 2.1f; }
			else if (strcmp(WeaponName, u8"M16A4") == 0) { Gravity = 1.9f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 1.3f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 2.0f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 1.9f; }
			else if (strcmp(WeaponName, u8"Groza") == 0) { Gravity = 2.3f; }
			else if (strcmp(WeaponName, u8"UMP9") == 0) { Gravity = 1.9f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 1.5f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 1.5f; }
			else if (strcmp(WeaponName, u8"BerylM762") == 0) { Gravity = 1.7f; }
			else if (strcmp(WeaponName, u8"Mk47Mutant") == 0) { Gravity = 1.9f; }
			else if (strcmp(WeaponName, u8"G36C") == 0) { Gravity = 1.85f; }
			else { Gravity = 1.9f; }
		}
		else if (Distance <= 550)
		{
			if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 1.8f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 1.75f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 2.2f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 1.5f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 2.5f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 2.0f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 1.7f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 1.6f; }
			else { Gravity = 2.2f; }
		}
		else if (Distance <= 600)
		{
			if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 1.95f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 1.85f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 2.35f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 1.67f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 2.5f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 2.4f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 1.8f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 1.8f; }
			else { Gravity = 2.5f; }
		}
		else if (Distance <= 650)
		{
			if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 2.175f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 1.95f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 2.5f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 1.75f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 2.95f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 2.5f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 2.0f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 1.95f; }
			else { Gravity = 3.0f; }
		}
		else if (Distance <= 700)
		{
			if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 2.25f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 2.1f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 2.95f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 2.1f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 3.25f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 2.8f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 2.05f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 2.1f; }
			else { Gravity = 3.5f; }
		}
		else if (Distance <= 800)
		{
			if (strcmp(WeaponName, u8"Kar98k") == 0) { Gravity = 2.35f; }
			else if (strcmp(WeaponName, u8"M24") == 0) { Gravity = 2.3f; }
			else if (strcmp(WeaponName, u8"SKS") == 0) { Gravity = 3.4f; }
			else if (strcmp(WeaponName, u8"AWM") == 0) { Gravity = 1.95f; }
			else if (strcmp(WeaponName, u8"Mini14") == 0) { Gravity = 3.6f; }
			else if (strcmp(WeaponName, u8"QBU") == 0) { Gravity = 3.3f; }
			else if (strcmp(WeaponName, u8"Mk14") == 0) { Gravity = 2.25f; }
			else if (strcmp(WeaponName, u8"SLR") == 0) { Gravity = 2.4f; }
			else { Gravity = 4.0f; }
		}
		else { Gravity = 5.0f; }
		return Gravity;
	}
	inline FLOAT GetAimSpeed()
	{
		FLOAT AimSpeed;	PCSTR WeaponName = Local.LoaclWeaponData.WeaponName;
		if (Local.LoaclWeaponData.TrajectoryConfig.InitialSpeed > 100.f) {
			AimSpeed = Local.LoaclWeaponData.TrajectoryConfig.InitialSpeed;
		}
		else {
			if (strcmp(WeaponName, u8"AKM") == 0) { AimSpeed = 715.f; }
			if (strcmp(WeaponName, u8"M416") == 0) { AimSpeed = 880.f; }
			if (strcmp(WeaponName, u8"M16A4") == 0) { AimSpeed = 900.f; }
			if (strcmp(WeaponName, u8"QBZ") == 0) { AimSpeed = 870.f; }
			if (strcmp(WeaponName, u8"SCAR-L") == 0) { AimSpeed = 870.f; }
			if (strcmp(WeaponName, u8"Mini14") == 0) { AimSpeed = 990.f; }
			if (strcmp(WeaponName, u8"SKS") == 0) { AimSpeed = 800.f; }
			if (strcmp(WeaponName, u8"Kar98k") == 0) { AimSpeed = 760.f; }
			if (strcmp(WeaponName, u8"M24") == 0) { AimSpeed = 790.f; }
			if (strcmp(WeaponName, u8"AWM") == 0) { AimSpeed = 910.f; }
			if (strcmp(WeaponName, u8"SLR") == 0) { AimSpeed = 840.f; }
			if (strcmp(WeaponName, u8"QBU") == 0) { AimSpeed = 945.f; }
			if (strcmp(WeaponName, u8"Groza") == 0) { AimSpeed = 715.f; }
			if (strcmp(WeaponName, u8"Mk14") == 0) { AimSpeed = 853.f; }
			if (strcmp(WeaponName, u8"M249") == 0) { AimSpeed = 880.f; }
			if (strcmp(WeaponName, u8"VSS") == 0) { AimSpeed = 300.f; }
			if (strcmp(WeaponName, u8"DP-28") == 0) { AimSpeed = 450.f; }
			if (strcmp(WeaponName, u8"UMP9") == 0) { AimSpeed = 400.f; }
			if (strcmp(WeaponName, u8"AUG") == 0) { AimSpeed = 940.f; }
			if (strcmp(WeaponName, u8"Vector") == 0) { AimSpeed = 300.f; }
			if (strcmp(WeaponName, u8" Æ◊÷ÂÛ") == 0) { AimSpeed = 160.f; }
			if (strcmp(WeaponName, u8"Ã¿ƒ∑—∑") == 0) { AimSpeed = 280.f; }
			if (strcmp(WeaponName, u8"Micro Uzi") == 0) { AimSpeed = 350.f; }
			if (strcmp(WeaponName, u8"S12K") == 0) { AimSpeed = 350.f; }
			if (strcmp(WeaponName, u8"S686") == 0) { AimSpeed = 370.f; }
			if (strcmp(WeaponName, u8"S1897") == 0) { AimSpeed = 360.f; }
			if (strcmp(WeaponName, u8"Mk47Mutant") == 0) { AimSpeed = 780.f; }
			if (strcmp(WeaponName, u8"BerylM762") == 0) { AimSpeed = 715.f; }
			if (strcmp(WeaponName, u8"Win94") == 0) { AimSpeed = 760.f; }
			else { AimSpeed = 880.f; }
		}
		return AimSpeed;
	}
	inline FVector PredictedPosition(FVector Velocity, FVector VelocityUp, FLOAT Distance)
	{
		FVector Results = { 0.f, 0.f, 0.f };
		FLOAT À•ºı = GetAimDragForce(Distance);
		FLOAT Gravity = 9.72f;// 9.800000191f;
		FLOAT TimeToReach = Distance / Local.LoaclWeaponData.WeaponInitialSpeed;
		FLOAT Drop = Distance <= 100 ? 0 : (0.5f * Gravity * TimeToReach * TimeToReach * 50.0f) * À•ºı;
		Results.z += Drop;

		Results.x = VelocityUp.x / 2 * powf(TimeToReach, 2) + Results.x;
		Results.y = VelocityUp.y / 2 * powf(TimeToReach, 2) + Results.y;
		Results.z = VelocityUp.z / 2 * powf(TimeToReach, 2) + Results.z;

		Results.x = Velocity.x * TimeToReach * 1.33f + Results.x;
		Results.y = Velocity.y * TimeToReach * 1.33f + Results.y;
		Results.z = Velocity.z * TimeToReach * 1.33f + Results.z;
		return Results;
	}
	inline bool ◊¯±Í◊™∆¡ƒª_◊‘√È—π«π(FVector WorldLocation, FVector2& Out, int& DeltaInMeters)
	{
		FVector vAxisX, vAxisY, vAxisZ;
		FVector Transformed;
		FVector Delta;
		FVector Axes;
		float FovAngle;
		FVector ControlRotation = Local.ControlRotation;
		FVector RecoilADSRotation = Local.RecoilADSRotation;
		float LeanLeft, LeanRight;

		
		LeanLeft = Local.LeanLeft;
		LeanRight = Local.LeanRight;
		RecoilADSRotation.y += (LeanRight - LeanLeft) * RecoilADSRotation.x / 50;//—π«¿∑˘∂»

		AddVector(ControlRotation, RecoilADSRotation,&Axes);
		Delta = Local.CameraPos;
		GetAxes(Axes,&vAxisX, &vAxisY, &vAxisZ);
		SubVector(WorldLocation, Delta, &Delta);
		Transformed.x = DotProduct(Delta, vAxisY);
		Transformed.y = DotProduct(Delta, vAxisZ);
		Transformed.z = DotProduct(Delta, vAxisX);

		if (DeltaInMeters != NULL) {
			DeltaInMeters = Transformed.z / 100;
		}
		FovAngle = Local.CameraFov;
		Out.X = F::Global.GameData.Width + Transformed.x * F::Global.GameData.Width / tan(FovAngle * (float)M_PI / 360.0) / Transformed.z;
		Out.Y = F::Global.GameData.Height - Transformed.y * F::Global.GameData.Height / tan(FovAngle * (float)M_PI / 360.0) / Transformed.z;

		if (Out.X > 0 && Out.Y > 0) {
			if (Out.X <= F::Global.GameData.Width * 2 && Out.Y <= F::Global.GameData.Height * 2.0f) {//?????
				return true;
			}
		}
		return false;
	}
	inline BOOL WorldToScreen_Aim(FVector WorldLocation, FVector* pOut, float* DeltaInMeters)
	{

		FVector Rotation = Local.ControlRotation + Local.RecoilADSRotation;//—π«πµÿ÷∑2

		FVector vAxisX, vAxisY, vAxisZ;
		GetAxes(Rotation, &vAxisX, &vAxisY, &vAxisZ);
		FVector Location = Local.CameraPos;
		FVector vDelta = WorldLocation - Location;// CameraInfo.Location;
		FVector vTransformed = FVector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;
		if (DeltaInMeters != NULL)
		{
			*DeltaInMeters = vTransformed.z / 100;
		}
		float FovAngle = Local.CameraFov;

		pOut->x = F::Global.GameData.Width + vTransformed.x * F::Global.GameData.Width / tanf(FovAngle * (float)M_PI / 360.f) / vTransformed.z;
		pOut->y = F::Global.GameData.Height - vTransformed.y * F::Global.GameData.Width / tanf(FovAngle * (float)M_PI / 360.f) / vTransformed.z;
		pOut->z = 0;

		if (pOut->x < 0) {
			pOut->x = 0;
		}
		if (pOut->y < 0) {
			pOut->y = 0;
		}
		if (pOut->x > 0 && pOut->y > 0) {
			if (pOut->x <= F::Global.GameData.Width * 2.0f && pOut->y <= F::Global.GameData.Height * 2.0f) {
				return TRUE;
			}
		}

		return FALSE;
	}
	namespace Map
	{
		inline FVector2 DefaultSize = { 1080.0f, 1080.0f };
		inline float GetZoomFactor(ULONG64 MapGrid) {
			ULONG64 Slot = G::Mem.Read<ULONG64>(MapGrid + offsets::Slot);
			if (Slot <= 65536)
				return 0.0f;
			//printf("Slot %p\n");
			auto Offsets = G::Mem.ReadEx<FMargin>(Slot + offsets::LayoutData + offsets::Offsets);
			const FVector2 CurrentSize = { Offsets.Right, Offsets.Bottom };
			return CurrentSize.X / DefaultSize.X;
		}
		inline FVector2 GetPosition(ULONG64 MapGrid) {
			ULONG64 Slot = G::Mem.Read<ULONG64>(MapGrid + offsets::Slot);
			if (Slot <= 65536)
				return FVector2();
			auto Offsets = G::Mem.ReadEx<FMargin>(Slot + offsets::LayoutData + offsets::Offsets);
			auto Alignment = G::Mem.ReadEx<FVector2>(Slot + offsets::LayoutData + offsets::Offsets + offsets::Alignment);
			const FVector2 CurrentPos = {
				Offsets.Right * (Alignment.X - 0.5f) - Offsets.Left,
				Offsets.Bottom * (Alignment.Y - 0.5f) - Offsets.Top
			};
			const float ZoomFactor = GetZoomFactor(MapGrid);
			return { CurrentPos.X / DefaultSize.X / ZoomFactor * 2.0f, CurrentPos.Y / DefaultSize.Y / ZoomFactor * 2.0f };
		}
		
		inline bool IsVisible(ULONG64 MapWidget, ULONG64 MapGrid) {
			if (IsNearlyZero(GetZoomFactor(MapGrid)))
				return false;
			return G::Mem.ReadEx<ESlateVisibility>(MapWidget + offsets::Visibility) == ESlateVisibility::SelfHitTestInvisible;
		}
		inline FVector2 DrawMap(FVector ActorLocation, float MapSize) {
			int X = Local.µÿÕºX;
			int Y = Local.µÿÕºY;
			FVector OriginLocation = FVector(X, Y, 0);

			const float MapSizeFactored = MapSize / Local.WorldMapZoomFactor;
			const FVector WorldLocation = ActorLocation + OriginLocation;
			const FVector WorldCenterLocation = { MapSize * (1.0f + Local.WorldMapPosition.X), MapSize * (1.0f + Local.WorldMapPosition.Y), 0.0f };
			const FVector RadarPos = WorldLocation - WorldCenterLocation;
			const FVector2 RadarScreenCenterPos = {(float)F::Global.GameData.Width,(float)F::Global.GameData.Height};
			const FVector2 RadarScreenPos = RadarScreenCenterPos + FVector2{
				RadarPos.x / MapSizeFactored * F::Global.GameData.Height,
				RadarPos.y / MapSizeFactored * F::Global.GameData.Height
			};
			return RadarScreenPos;
		}

	}

}