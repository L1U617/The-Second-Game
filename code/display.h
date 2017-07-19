//图像显示，包括背景（地砖），人物，怪
#ifndef _DISPLAY
#define _DISPLAY

#include "wtypes.h"

class DISPLAY
{
public:
	DISPLAY();
	~DISPLAY();
	void Init(int iResource);
	void InitMask(int maskResource);
	void DrawBasic(HDC hdc);
	void SetPosition(int x, int y);

public:
	HBITMAP hbm;

	HBITMAP hbmBuffer;
	HBITMAP hbmOld;
	HBITMAP hbmOldBuffer;
	HDC hdcBuffer;//缓冲
	HDC hdcMem;

	HBITMAP maskbm;
	HDC maskhdc;

	int width;//图片长
	int height;//宽
	int xpos;//坐标
	int ypos;

};

//背景显示子类

struct pos
{
	int x;
	int y;
};



//地图 12.25
class MAP :public DISPLAY
{
public:
	static int mapArray[100][100];
	static int seex, seey;

	HBITMAP hbm_light, hbm_dark, hbm_wall, hbm_floor,hbm_win;
	
public:
	MAP();	//记得初始化mapArray
	~MAP();
	 
	void InitMapObj(int floor, int light, int dark, int wall,int win);
	void ReadMap();//从数组文件读入地图
	void SetMap(int x, int y, int type);//设置地图元素
	void ShowMapObj(HDC hdcSrc);
};



//角色
class ROLE :public DISPLAY
{
public:
	ROLE();
	~ROLE();

	
	void DrawRole(HDC hdc);
	void setShadow(int i);
	void setLight(int i);
	void setVision(int i);
	void switchShadow();
    static void move(int ins);
	static void setPos(int xx, int yy);
	void ShowLight(HDC hdc);
	void InitRole(int role, int mask, int light,int lightmask);
	void Back();

	static bool checkwall();
	int checkfloor();	//返回地砖类型
	
	bool checkLight();
	
	void SetState(int i);
	void SetDirection(int i);
	void SetTimer(int i);
public:		

	static int x, y;	//人物的位置

	int shadow;//0 正常状态，1 阴影化状态
	int light;	//光值
	int vision;	//视野
	float speed; //速度
	int direction;
	int state;
	int timer;

	HBITMAP hbmLight,hbmLightmask;
	HDC hdcLight,hdcLightmask;
};

class BK :public DISPLAY
{
public:
	BK();
	~BK();
	void PosInit(int x, int y);
	void Normal(HDC hdc, ROLE role);//非阴影化状态下的界面显示	
	void Play(HDC hdc,int chap,int id);//过场动画播放

};


struct mstArr
{
	int x, y; //出生地点
	int pathlength; //巡视路径长度
	int l;//当前在路径的哪里
	pos pathpoint[20]; //记录路径的点
};

//怪
class MONSTER :public DISPLAY
{
public:
	MONSTER();
	~MONSTER();
	void setVisible(int i);
	void readMonster();
	bool checkkill(ROLE &role);
	void refresh();
	void ShowMonster(HDC hdc);

public:
	int visible;//0 不可见，1可见
	int speed;
	
	int nmst;	//怪物数量
	static mstArr monsterArray[100];


};



#endif