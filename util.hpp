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
inline void �����Ż�_(int ��ʱ���, int ��ʱ��λ)
{
	if (��ʱ��� < 1)
		return;

	HANDLE hTimer;
	LARGE_INTEGER int64;
	int �ƴ�;

	if (��ʱ��λ == 1)
	{
		int64.QuadPart = -10 * ��ʱ���;
		hTimer = CreateWaitableTimerA(0, FALSE, 0);
		SetWaitableTimer(hTimer, &int64, 0, 0, 0, FALSE);

		while (MsgWaitForMultipleObjects(1, &hTimer, FALSE, INFINITE, QS_ALLINPUT) != 0)
		{
			ProcessEvents();
			// �����¼�
		}

		CloseHandle(hTimer);
		return;
	}

	if (��ʱ��λ == 0)
		��ʱ��λ = 1;
	else if (��ʱ��λ == 2)
		��ʱ��λ = 1000;
	else if (��ʱ��λ == 3)
		��ʱ��λ = 1000 * 60;
	else if (��ʱ��λ == 4)
		��ʱ��λ = 1000 * 60 * 60;
	else if (��ʱ��λ == 5)
		��ʱ��λ = 1000 * 60 * 60 * 24;

	int64.QuadPart = -10 * ��ʱ��� * 1000 * ��ʱ��λ;
	hTimer = CreateWaitableTimerA(0, FALSE, 0);
	SetWaitableTimer(hTimer, &int64, 0, 0, 0, FALSE);

	while (MsgWaitForMultipleObjects(1, &hTimer, FALSE, INFINITE, QS_ALLINPUT) != 0)
	{
		ProcessEvents();
		// �����¼�
	}

	CloseHandle(hTimer);
}