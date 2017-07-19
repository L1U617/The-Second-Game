//文字信息显示
#include "wtypes.h"

class FONT
{
public:
	FONT();
	~FONT();

	void setFont(HDC hDC);
	void ShowText(int chapter,int num);
	void setPosition(int x, int y);
	void setColor(COLORREF cbk, COLORREF ctext);
	void setTimer(int i);
public:
	HDC hdc;
	HFONT hf;
	HFONT hfold;
	long lfHeight;

	COLORREF cbk;
	COLORREF ctext;

	int timer;
	int xpos;
	int ypos;
};