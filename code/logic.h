//Âß¼­ÅÐ¶Ï
#ifndef _LOGIC
#define _LOGIC

class GAMESTATE
{
public:
	GAMESTATE();
	~GAMESTATE();
	static void setState(int i);
	void setPosition(int x, int y);
	bool moveCtrl( WPARAM wParam,ROLE &role,MONSTER &monster);
	void Back();
	void setMusic();

	int viewx;
	int viewy;
	static int state;
	int music;
};

class MENU :public GAMESTATE
{
public:
	MENU();
	~MENU();

public:
	int menuNum;
};



#endif