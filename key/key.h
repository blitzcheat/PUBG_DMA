#pragma once

#include "../Includes.h"

typedef __int64 (__fastcall* PInitRemoteKeyDetectionFunc)(VMM_HANDLE hVMM);

typedef __int64(__fastcall* Pis_key_down)(int key);

class Key
{
public:


public:
	HMODULE Module;
	VMM_HANDLE hVMM;
};

namespace F { inline Key vmm; };
