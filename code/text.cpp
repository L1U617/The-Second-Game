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
	
	hf = CreateFont(lfHeight, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,L"΢���ź�");
	SelectObject(hdc, hf);
}

void FONT::setPosition(int x, int y)
{
	xpos = x;
	ypos = y;
}

void FONT::ShowText(int chapter, int num)
{
	LPCWSTR n_1 = L"��˵��Ҫ�һع⣿";
	LPCWSTR n_2 = L"��Ц��������Ͳ����׹���ʲô����";
	LPCWSTR n_3 = L"  ";
	LPCWSTR n_4 = L"�޹�֮·";
	LPCWSTR n_5 = L"��,��ʧ��";
	LPCWSTR n_6 = L"�ǰ�Ӱ�����˹�";
	LPCWSTR n_7 = L"�������һع��ô����Ѫ�ĺ���";
	LPCWSTR n_8 = L"̤������·�ɣ��ܹ�����ͻ���";
	LPCWSTR n_9 = L"����·�ϣ����ǵִ��յ�";
	LPCWSTR n_10 = L"û�о�ͷ�ĳ�ҹ������û�й�;���յ�";
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