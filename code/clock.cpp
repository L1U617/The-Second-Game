#include "stdafx.h"
#include "clock.h"

CLOCK::CLOCK()
{
	iNum = 0;
	iIsActive = 0;
	iElapse = 100;
}
CLOCK::~CLOCK()
{
	Destroy();
}

void CLOCK::Begin(HWND hwnd, int elapse)
{
	if (iIsActive)
		return;

	hWnd = hwnd;
	iElapse = elapse;

	SetTimer(hWnd, 1, iElapse, NULL);
	iNum = 1000 / iElapse;
	iIsActive = 1;
}

void CLOCK::Destroy()
{
	if (iIsActive)
	{
		iIsActive = 0;
		KillTimer(hWnd, 1);
	}
}
