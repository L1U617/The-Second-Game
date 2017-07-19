//ͼ����ʾ��������������ש���������
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
	HDC hdcBuffer;//����
	HDC hdcMem;

	HBITMAP maskbm;
	HDC maskhdc;

	int width;//ͼƬ��
	int height;//��
	int xpos;//����
	int ypos;

};

//������ʾ����

struct pos
{
	int x;
	int y;
};



//��ͼ 12.25
class MAP :public DISPLAY
{
public:
	static int mapArray[100][100];
	static int seex, seey;

	HBITMAP hbm_light, hbm_dark, hbm_wall, hbm_floor,hbm_win;
	
public:
	MAP();	//�ǵó�ʼ��mapArray
	~MAP();
	 
	void InitMapObj(int floor, int light, int dark, int wall,int win);
	void ReadMap();//�������ļ������ͼ
	void SetMap(int x, int y, int type);//���õ�ͼԪ��
	void ShowMapObj(HDC hdcSrc);
};



//��ɫ
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
	int checkfloor();	//���ص�ש����
	
	bool checkLight();
	
	void SetState(int i);
	void SetDirection(int i);
	void SetTimer(int i);
public:		

	static int x, y;	//�����λ��

	int shadow;//0 ����״̬��1 ��Ӱ��״̬
	int light;	//��ֵ
	int vision;	//��Ұ
	float speed; //�ٶ�
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
	void Normal(HDC hdc, ROLE role);//����Ӱ��״̬�µĽ�����ʾ	
	void Play(HDC hdc,int chap,int id);//������������

};


struct mstArr
{
	int x, y; //�����ص�
	int pathlength; //Ѳ��·������
	int l;//��ǰ��·��������
	pos pathpoint[20]; //��¼·���ĵ�
};

//��
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
	int visible;//0 ���ɼ���1�ɼ�
	int speed;
	
	int nmst;	//��������
	static mstArr monsterArray[100];


};



#endif