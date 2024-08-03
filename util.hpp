#pragma once
#include <Windows.h>

inline void ProcessEvents()
{
	MSG msg;
	while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
inline void 超级优化_(int 延时间隔, int 延时单位)
{
	if (延时间隔 < 1)
		return;

	HANDLE hTimer;
	LARGE_INTEGER int64;
	int 计次;

	if (延时单位 == 1)
	{
		int64.QuadPart = -10 * 延时间隔;
		hTimer = CreateWaitableTimerA(0, FALSE, 0);
		SetWaitableTimer(hTimer, &int64, 0, 0, 0, FALSE);

		while (MsgWaitForMultipleObjects(1, &hTimer, FALSE, INFINITE, QS_ALLINPUT) != 0)
		{
			ProcessEvents();
			// 处理事件
		}

		CloseHandle(hTimer);
		return;
	}

	if (延时单位 == 0)
		延时单位 = 1;
	else if (延时单位 == 2)
		延时单位 = 1000;
	else if (延时单位 == 3)
		延时单位 = 1000 * 60;
	else if (延时单位 == 4)
		延时单位 = 1000 * 60 * 60;
	else if (延时单位 == 5)
		延时单位 = 1000 * 60 * 60 * 24;

	int64.QuadPart = -10 * 延时间隔 * 1000 * 延时单位;
	hTimer = CreateWaitableTimerA(0, FALSE, 0);
	SetWaitableTimer(hTimer, &int64, 0, 0, 0, FALSE);

	while (MsgWaitForMultipleObjects(1, &hTimer, FALSE, INFINITE, QS_ALLINPUT) != 0)
	{
		ProcessEvents();
		// 处理事件
	}

	CloseHandle(hTimer);
}