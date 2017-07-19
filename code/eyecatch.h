#pragma once
#ifndef _EYECATCH
#define _EYECATCH
#include "display.h"
#include "text.h"

class ANIMATE
{
public:
	ANIMATE();
	~ANIMATE();

	void Init(int iResource);
	void PlayAni(HDC hdc);
	void SetTimer(int i,int reset);
	void SetFrame(int chapter);
	void SetFont(HDC hdc, COLORREF cbk, COLORREF ctext,int x,int y);//ÉèÖÃ×ÖÄ»²ÎÊý
public:
	FONT caption;
	BK frame;

	int chap;
	int id_caption, id_frame;
	int timer;
};

#endif