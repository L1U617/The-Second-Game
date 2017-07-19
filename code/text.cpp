#include "stdafx.h"
#include "text.h"

FONT::FONT()
{
	timer = 0;
}
FONT::~FONT()
{

}

void FONT::setFont(HDC hDC)
{
	hdc = hDC;
	lfHeight = -MulDiv(14, GetDeviceCaps(hdc, LOGPIXELSY), 72);
	
	hf = CreateFont(lfHeight, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,L"微软雅黑");
	SelectObject(hdc, hf);
}

void FONT::setPosition(int x, int y)
{
	xpos = x;
	ypos = y;
}

void FONT::ShowText(int chapter, int num)
{
	LPCWSTR n_1 = L"你说你要找回光？";
	LPCWSTR n_2 = L"可笑，你根本就不明白光是什么——";
	LPCWSTR n_3 = L"  ";
	LPCWSTR n_4 = L"无归之路";
	LPCWSTR n_5 = L"光,消失了";
	LPCWSTR n_6 = L"是暗影盗走了光";
	LPCWSTR n_7 = L"帮我们找回光好么，混血的孩子";
	LPCWSTR n_8 = L"踏上这条路吧，避过怪物和机关";
	LPCWSTR n_9 = L"死在路上，或是抵达终点";
	LPCWSTR n_10 = L"没有尽头的长夜，或是没有归途的终点";
	switch (chapter)
	{
	case 0:
		switch (num)
		{
		case 0:TextOut(hdc, xpos, ypos, n_1, wcslen(n_1)); break;
		case 1:TextOut(hdc, xpos-70, ypos, n_2, wcslen(n_2)); break;
		case 2: {
			TextOut(hdc, 400, 200, n_3, wcslen(n_3));
			break;
				}			
			
		case 3:
		case 4:
		{
			TextOut(hdc, 400, 420, n_5, wcslen(n_5)); 
			TextOut(hdc, 380, 450, n_6, wcslen(n_6)); break;			
		}

		case 5:TextOut(hdc, 500, 250, n_7, wcslen(n_7)); break;
		case 6:TextOut(hdc, 500, 250, n_8, wcslen(n_8)); break;

		case 7:
		case 8: {
			TextOut(hdc, 350, 250, n_9, wcslen(n_9));
			TextOut(hdc, 300, 300, n_10, wcslen(n_10)); break;
			} 
		}
		break;
	}
}
	

void FONT::setColor(COLORREF c1, COLORREF c2)
{
	cbk = c1;
	ctext = c2;
	SetBkColor(hdc, cbk);
	SetTextColor(hdc, ctext);

}

void FONT::setTimer(int i)
{
	timer = timer+i;
}