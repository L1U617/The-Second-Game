#include "stdafx.h"
#include "display.h"
#include "define.h"  
#include "Resource.h"
#include "stdio.h"
#include "logic.h"


DISPLAY::DISPLAY()
{

}
DISPLAY::~DISPLAY()
{

}
void DISPLAY::Init(int iResource)
{
	BITMAP bm;
	hbm = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(iResource));
	GetObject(hbm, sizeof(bm), &bm);
	width = bm.bmWidth;
	height = bm.bmHeight;
}

void DISPLAY::SetPosition(int x, int y)
{
	xpos = x;
	ypos = y;
}

void DISPLAY::DrawBasic(HDC hdc)
{
	hdcBuffer = CreateCompatibleDC(hdc);
	hbmBuffer = CreateCompatibleBitmap(hdc, width, height);
	hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

	hdcMem = CreateCompatibleDC(hdc);
	hbmOld = (HBITMAP)SelectObject(hdcMem, hbm);

	BitBlt(hdcBuffer, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

	BitBlt(hdc, xpos, ypos, width, height, hdcBuffer, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	SelectObject(hdcBuffer, hbmOldBuffer);
	DeleteDC(hdcBuffer);
	DeleteObject(hbmBuffer);
}

BK::BK()
{

}
BK::~BK()
{

}
void BK::Normal(HDC hdc, ROLE role)
{
	hdcBuffer = CreateCompatibleDC(hdc);
	hbmBuffer = CreateCompatibleBitmap(hdc, width, height);
	hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

	hdcMem = CreateCompatibleDC(hdc);
	hbmOld = (HBITMAP)SelectObject(hdcMem, hbm);

	maskhdc = CreateCompatibleDC(hdc);
	SelectObject(maskhdc, maskbm);

	if (role.light < 30) {
		BitBlt(hdcBuffer, 0, 0, width, height, maskhdc, 0, 0, SRCCOPY);
		BitBlt(hdc, xpos, ypos, width, height, hdcBuffer, 0, 0, SRCAND);
	}
	else if (role.light > 30 && role.light <= 60)
	{
		BitBlt(hdcBuffer, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
		BitBlt(hdc, xpos, ypos, width, height, hdcBuffer, 0, 0, SRCAND);
	}	
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);
	DeleteDC(maskhdc);
	SelectObject(hdcBuffer, hbmOldBuffer);
	DeleteDC(hdcBuffer);
	DeleteObject(hbmBuffer);
}


void BK::PosInit(int x, int y)
{
	xpos = x;
	ypos = y;
}

void BK::Play(HDC hdc,int chap,int id)
{
	hdcBuffer = CreateCompatibleDC(hdc);
	hbmBuffer = CreateCompatibleBitmap(hdc, width, height);
	hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

	hdcMem = CreateCompatibleDC(hdc);
	hbmOld = (HBITMAP)SelectObject(hdcMem, hbm);

	BitBlt(hdcBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hdcMem, 0, id*640, SRCCOPY);

	BitBlt(hdc, xpos, ypos, WINDOW_WIDTH, WINDOW_HEIGHT, hdcBuffer, 0, 0, SRCCOPY);
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	SelectObject(hdcBuffer, hbmOldBuffer);
	DeleteDC(hdcBuffer);
	DeleteObject(hbmBuffer);
}


/*--------ROLE类 角色函数---------------*/
int ROLE::x;
int ROLE::y;

/*=============12.31update=============*/
void DISPLAY::InitMask(int maskResource)
{
	BITMAP bm;
	maskbm = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(maskResource));
	GetObject(maskbm, sizeof(bm), &bm);
}

void ROLE::DrawRole(HDC hdc)
{
	hdcBuffer = CreateCompatibleDC(hdc);
	hbmBuffer = CreateCompatibleBitmap(hdc, width, height);
	hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

	hdcMem = CreateCompatibleDC(hdc);
	hbmOld = (HBITMAP)SelectObject(hdcMem, hbm);

	maskhdc = CreateCompatibleDC(hdc);
	SelectObject(maskhdc, maskbm);
	if(!shadow)
		BitBlt(hdc, xpos, ypos, width, height, maskhdc, 0, 0, SRCAND);	

	BitBlt(hdcBuffer, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);
	BitBlt(hdc, xpos, ypos, width, height, hdcBuffer, 0, 0, SRCPAINT);

	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);

	DeleteDC(maskhdc);

	SelectObject(hdcBuffer, hbmOldBuffer);
	DeleteDC(hdcBuffer);
	DeleteObject(hbmBuffer);
}

void ROLE::InitRole(int role, int mask, int light,int lightmask)
{
	BITMAP bm1,bm2,bm3,bm4;
	hbm = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(role));
	GetObject(hbm, sizeof(bm1), &bm1);

	maskbm = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(mask));
	GetObject(maskbm, sizeof(bm2), &bm2);

	hbmLight = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(light));
	GetObject(hbmLight, sizeof(bm3), &bm3);

	hbmLightmask = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(light));
	GetObject(hbmLightmask, sizeof(bm4), &bm4);
}

void ROLE::ShowLight(HDC hdc)
{
	hdcBuffer = CreateCompatibleDC(hdc);
	hbmBuffer = CreateCompatibleBitmap(hdc, width, height);
	hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

	hdcMem = CreateCompatibleDC(hdc);
	hbmOld = (HBITMAP)SelectObject(hdcMem, hbmLight);

	hdcLightmask = CreateCompatibleDC(hdc);
	SelectObject(hdcLightmask, hbmLightmask);

	BitBlt(hdcBuffer, 0, 0, width, height, hdcMem, 0, 0, SRCCOPY);

	for (int i=0; i < light/10; i++)
	{
		BitBlt(hdc, 100 + i * 20,500, width, height, hdcLightmask, 0, 0, SRCAND);
		BitBlt(hdc, 100+i*20 , 500, width, height, hdcBuffer, 0, 0, SRCPAINT);
	}	
	SelectObject(hdcMem, hbmOld);
	DeleteDC(hdcMem);	

	SelectObject(hdcBuffer, hbmOldBuffer);
	DeleteDC(hdcBuffer);
	DeleteObject(hbmBuffer);
}

void ROLE::setShadow(int i)
{
	shadow = i;

}
void ROLE::setLight(int i)
{
	light= light+i;
	if (light >= 100) light = 100;
	if (!checkLight()) GAMESTATE::setState(GAMESTATE_OVER);
	
}
void ROLE::setVision(int i)
{
	vision = i;
}

int ROLE::checkfloor()
{
	return MAP::mapArray[ROLE::x][ROLE::y];
}

void ROLE::switchShadow()
{
	if (shadow == 0)
	{
		setShadow(1);
	}
	else
	{
		setShadow(0);

	}

}

bool ROLE::checkLight()
{
	if (light < 1) return false;
	else return true;


}

bool ROLE::checkwall()
{
	if (x >= 40
		|| x < 0
		|| y >= 28
		|| y < 0
		|| MAP::mapArray[x][y] == MAPTYPE_FLOOR_WALL
		)
		return false;
	else return true;
}

void ROLE::setPos(int xx,int yy)
{
	ROLE::x = ROLE::x + xx;
	ROLE::y = ROLE::y + yy;
}

void ROLE::SetState(int i)
{
	state = i;
}

void ROLE::SetDirection(int i)
{
	direction = i;
}

void ROLE::SetTimer(int i)
{
	timer = timer+i;
}

void ROLE::move(int ins)
{
	switch (ins)
	{
	case MOVE_UP:
		{
		setPos(0, -1);
		break;
		}
	case MOVE_RIGHT:
	{
		setPos(1, 0);
		break;
	}
	case MOVE_DOWN:
	{
		setPos(0, 1);
		break;
	}
	case MOVE_LEFT:
	{
		setPos(-1, 0);
		break;
	}
	}
}

void ROLE::Back()
{
	InitRole(IDB_ROLE, IDB_ROLE_MASK, IDB_VALUE, IDB_VALUE_MASK);
	SetPosition(400, 300);
	x = 9;
	y = 2;
	shadow = 0;
	light=100;
	setVision(5);

	state = 2;
	direction = ROLE_FRONT;
	timer = 0;
}

ROLE::ROLE()
{
	x = 9;
	y = 2;
	shadow = 0;
	setLight(100);
	setVision(5);

	state = 2;
	direction = ROLE_FRONT;
	timer = 0;
}

ROLE::~ROLE()
{

}


/*--------ROLE类 角色函数 结束---------------*/



/*--------MONSTER类 怪物函数---------------*/
mstArr MONSTER::monsterArray[100];

MONSTER::MONSTER()
{
	memset(monsterArray, 0, sizeof(monsterArray));
}

MONSTER::~MONSTER()
{

}

bool MONSTER::checkkill(ROLE &role)
{
	int i;
	int x, y;
	x = role.x;
	y = role.y;
	int tx, ty;
	for (i = 0; i < nmst; i++)
	{
		tx = monsterArray[i].x - x;
		ty = monsterArray[i].y - y;
		//if ((tx>=-1 && tx<=1) &&(ty>=-1&&ty<=1))
		if (tx==0 && ty==0)
		return false;
	}
	return true;
}

void MONSTER::readMonster()
{
	FILE *mstin;
	errno_t err;
	int x, y, i, j, length, xx, yy;
	err = fopen_s(&mstin, "monster.in.txt", "r");
	err = fscanf_s(mstin, "%d", &i);
	nmst = i;
	/*monster.in.txt格式
	第一行		怪物数量
	第二行开始	第i个怪物的出生位置x y
	第i个怪物的路径长度j（pathlength）
	j个路径点x y

	*/
	i = 0;
	while (!feof(mstin))
	{
		err = fscanf_s(mstin, "%d %d", &x, &y);
		monsterArray[i].x = x;
		monsterArray[i].y = y;
		err = fscanf_s(mstin, "%d", &length);
		monsterArray[i].pathlength = length;
		for (j = 0; j < length; j++)
		{
			err = fscanf_s(mstin, "%d %d", &xx, &yy);
			monsterArray[i].pathpoint[j].x = xx;
			monsterArray[i].pathpoint[j].y = yy;
		}

		i++;
	}

	fclose(mstin);

}

void MONSTER::refresh()
{
	int i, j;
	for (i = 0; i < nmst; i++)
	{
		j = (monsterArray[i].l + 1) % monsterArray[i].pathlength;
		monsterArray[i].x = monsterArray[i].pathpoint[j].x;
		monsterArray[i].y = monsterArray[i].pathpoint[j].y;
		monsterArray[i].l = j;

	}

}


void MONSTER::setVisible(int i)
{
	visible = i;
}



/*--------MONSTER类 怪物函数 结束---------------*/

/*--------MAP类 地图函数---------------*/
int MAP::mapArray[100][100];
int MAP::seex;
int MAP::seey;


MAP::MAP()
{
	memset(mapArray, 0, sizeof(mapArray));	//清零地图
	seex = 0;
	seey = 0;
}

MAP::~MAP()
{


}


void MAP::ReadMap()
{
	FILE *mapin;
	errno_t err;
	int x, y, type;
	err= fopen_s(&mapin,"map.in.txt", "r");
	while ( !feof(mapin))
	{
		err= fscanf_s(mapin, "%d %d %d",&x,&y,&type);
		mapArray[x][y] = type;
	}
	
	fclose(mapin);

}

void MAP::SetMap(int x, int y, int type)
{
	mapArray[x][y] = type;
}


//*******12.27update
void MAP::InitMapObj(int floor, int light, int dark, int wall,int win)
{
	BITMAP bm1, bm2, bm3, bm4,bm5;
	hbm_floor = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(floor));
	GetObject(hbm_floor, sizeof(bm1), &bm1);

	hbm_light = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(light));
	GetObject(hbm_light, sizeof(bm2), &bm2);

	hbm_dark = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(dark));
	GetObject(hbm_dark, sizeof(bm3), &bm3);

	hbm_wall = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(wall));
	GetObject(hbm_wall, sizeof(bm4), &bm4);
	hbm_win = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(win));
	GetObject(hbm_wall, sizeof(bm5), &bm5);
}

void MAP::ShowMapObj(HDC hdc)
{
	int i, j;
	for (i = 0; i < 100;i++ )
		for (j = 0;j < 100; j++)
			if(mapArray[i][j]==MAPTYPE_FLOOR)
			{
				hdcMem = CreateCompatibleDC(hdc);
				SelectObject(hdcMem, hbm_floor);
				BitBlt(hdc, 400+i*BLOCK_SIZE,300+j*BLOCK_SIZE , BLOCK_SIZE, BLOCK_SIZE, hdcMem, 0, 0, SRCCOPY);
				DeleteDC(hdcMem);
			}
			else if (mapArray[i][j] == MAPTYPE_FLOOR_LIGHT)
			{
				hdcMem = CreateCompatibleDC(hdc);
				SelectObject(hdcMem, hbm_light);
				BitBlt(hdc, 400 + i*BLOCK_SIZE, 300 + j*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, hdcMem, 0, 0, SRCCOPY);
				DeleteDC(hdcMem);
			}
			else if (mapArray[i][j] == MAPTYPE_FLOOR_DARK)
			{
				hdcMem = CreateCompatibleDC(hdc);
				SelectObject(hdcMem, hbm_dark);
				BitBlt(hdc, 400 + i*BLOCK_SIZE, 300 + j*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, hdcMem, 0, 0, SRCCOPY);
				DeleteDC(hdcMem);
			}
			else if (mapArray[i][j] == MAPTYPE_FLOOR_WALL)
			{
				hdcMem = CreateCompatibleDC(hdc);
				SelectObject(hdcMem, hbm_wall);
				BitBlt(hdc, 400 + i*BLOCK_SIZE, 300 + j*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, hdcMem, 0, 0, SRCCOPY);
				DeleteDC(hdcMem);
			}
			else if (mapArray[i][j] == MAPTYPE_FLOOR_WIN)
			{
				hdcMem = CreateCompatibleDC(hdc);
				SelectObject(hdcMem, hbm_win);
				BitBlt(hdc, 400 + i*BLOCK_SIZE, 300 + j*BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE, hdcMem, 0, 0, SRCCOPY);
				DeleteDC(hdcMem);
			}

}


/*--------MAP类 地图函数 结束---------------*/

void MONSTER::ShowMonster(HDC hdc)
{
	int n;
	for (n = 0; n < nmst; n++)
			{
				hdcMem = CreateCompatibleDC(hdc);
				maskhdc = CreateCompatibleDC(hdc);
				SelectObject(hdcMem, hbm);
				SelectObject(maskhdc, maskbm);
				BitBlt(hdc, 400+monsterArray[n].x*BLOCK_SIZE, 300+monsterArray[n].y*BLOCK_SIZE, width, height, maskhdc, 0, 0, SRCAND);
				BitBlt(hdc, 400+monsterArray[n].x*BLOCK_SIZE, 300+monsterArray[n].y*BLOCK_SIZE, width, height, hdcMem, 0, 0, SRCPAINT);
				DeleteDC(hdcMem);
				DeleteDC(maskhdc);
			}
}