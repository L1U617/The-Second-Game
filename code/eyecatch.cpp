#include "stdafx.h"
#include "eyecatch.h"

ANIMATE::ANIMATE()
{
}

ANIMATE::~ANIMATE()
{
}

void ANIMATE::Init(int iResource)
{
	frame.Init(iResource);
}

void ANIMATE::SetFont(HDC hdc, COLORREF cbk, COLORREF ctext, int x, int y)
{
	caption.setFont(hdc);
	caption.setColor(cbk, ctext);
	caption.setPosition(x, y);
}

void ANIMATE::PlayAni(HDC hdc)
{		
	switch (chap)
	{
	case 0:
		if (timer >= 0 && timer <=3) { id_caption=0; }
		else if (timer >= 4 && timer < 9) { id_caption = 1; }

		else if (timer >= 9 && timer < 12) { id_caption = 2; }

		else if (timer >= 12 && timer < 14) { id_caption = 3; }
		else if (timer >= 13 && timer < 17) { id_caption = 4; }

		else if (timer >= 17 && timer < 18) { id_caption = 2; }

		else if (timer >= 18 && timer < 21) { id_caption = 5; }
		else if (timer >= 21&& timer < 25) { id_caption = 6; }
		else if (timer >= 25 && timer < 30) { id_caption = 7; }

		else if (timer >= 30 && timer < 34) { id_caption = 8; }

		if (timer >= 0 && timer <8) {
			//id_frame = 1;
			switch (timer)
			{
			case 0:id_frame = 1; break;
			case 1:id_frame = 0; break;
			case 2:id_frame = 1; break;
			case 3:id_frame = 2; break;
			case 4:id_frame = 1; break;
			case 5:id_frame = 0; break;
			case 6:id_frame = 1; break;
			case 7:id_frame = 2; break;
			}
		}

		else if (timer >= 8 && timer < 9) { id_frame = 9; }

		else if (timer >= 9 && timer < 11) { id_frame = 7; }
		else if (timer >= 11 && timer < 12) { id_frame = 9; }

		else if (timer >= 12 && timer < 13) { id_frame = 3; }
		else if (timer >= 13 && timer < 14) { id_frame = 4; }
		else if (timer >= 14 && timer < 15) { id_frame = 5; }
		else if (timer >= 15 && timer < 16) { id_frame = 6; }

		else if (timer >= 17 && timer < 18) { id_frame = 9; }

		else if (timer >= 18 && timer < 25) { id_frame = 8; }
		else if (timer >= 25 && timer < 34) { id_frame = 9; }

		break;
	case 1:break;
	}
	frame.Play(hdc,chap,id_frame);
	caption.ShowText(chap, id_caption);
}

void ANIMATE::SetFrame(int chapter)
{
	chap = chapter;
}

void ANIMATE::SetTimer(int i,int reset)
{
	if (reset) timer = 0;
	else timer = timer + i;
}