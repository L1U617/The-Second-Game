// ±÷”
#ifndef _CLOCK
#define _CLOCK

#include "stdio.h"

class CLOCK
{
public:
	CLOCK();
	~CLOCK();
	void Begin(HWND hwnd, int elapse);
	void Destroy();	

public:
	HWND hWnd;
	HDC hDc;

	int iNum;
	int iElapse;
	int iIsActive;
};

#endif