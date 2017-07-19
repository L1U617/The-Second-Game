#include "stdafx.h"
#include "Resource.h"
#include "display.h"
#include "logic.h"
#include "define.h"

int GAMESTATE::state;

GAMESTATE::GAMESTATE()
{
	state = 0;
}
GAMESTATE::~GAMESTATE()
{
}
 

void GAMESTATE::setState(int i)
{
	state = i;
}

//******12.27update*******
void GAMESTATE::Back()
{
	viewx = 900;
	viewy = 200;
	setState(GAMESTATE_MENU);
}
void GAMESTATE::setPosition(int x, int y)
{
	viewx = x;
	viewy = y;
}
bool GAMESTATE::moveCtrl(WPARAM wParam, ROLE &role, MONSTER &monster)
{
	if (wParam == VK_DOWN)
	{
		if (role.state == 2)
		{
			role.Init(IDB_ROLE_FRONT2);
			role.InitMask(IDB_ROLE_FRONT2_MASK);
			role.SetState(3);
		}
		else if (role.state == 3)
		{
			role.Init(IDB_ROLE_FRONT3);
			role.InitMask(IDB_ROLE_FRONT3_MASK);
			role.SetState(2);
		}
		role.SetDirection(ROLE_FRONT);
		ROLE::move(MOVE_DOWN);

		if (ROLE::checkwall())		//ø…“‘“∆∂Ø
		{
			viewy += MOVE_SPEED;
			if (role.shadow == 0 && monster.checkkill(role) == false) setState(GAMESTATE_OVER);

			if (role.checkfloor() == MAPTYPE_FLOOR_WIN) setState(GAMESTATE_END);
		}
		else ROLE::move(MOVE_UP);
		return true;
	}
	if (wParam == VK_UP)
	{
		if (role.state == 2)
		{
			role.Init(IDB_ROLE_BACK2);
			role.InitMask(IDB_ROLE_BACK2_MASK);
			role.SetState(3);
		}
		else if (role.state == 3)
		{
			role.Init(IDB_ROLE_BACK3);
			role.InitMask(IDB_ROLE_BACK3_MASK);
			role.SetState(2);
		}
		role.SetDirection(ROLE_BACK);
		ROLE::move(MOVE_UP);
		if (ROLE::checkwall())
		{
			viewy -= MOVE_SPEED;
			if (role.shadow==0 && monster.checkkill(role) == false) setState(GAMESTATE_OVER);

			if (role.checkfloor() == MAPTYPE_FLOOR_WIN ) setState(GAMESTATE_END);
		}
		else ROLE::move(MOVE_DOWN);
		return true;
	}
	if (wParam == VK_RIGHT)
	{
		if (role.state == 2)
		{
			role.Init(IDB_ROLE_RIGHT_PROF2);
			role.InitMask(IDB_ROLE_RIGHT_PROF2_MASK);
			role.SetState(3);
		}
		else if (role.state == 3)
		{
			role.Init(IDB_ROLE_RIGHT_PROF3);
			role.InitMask(IDB_ROLE_RIGHT_PROF3_MASK);
			role.SetState(2);
		}
		role.SetDirection(ROLE_RIGHT);
		ROLE::move(MOVE_RIGHT);
		if (ROLE::checkwall())
		{
			viewx += MOVE_SPEED;
			if (role.shadow == 0 && monster.checkkill(role) == false) setState(GAMESTATE_OVER);

			if (role.checkfloor() == MAPTYPE_FLOOR_WIN) setState(GAMESTATE_END);
		}
		else ROLE::move(MOVE_LEFT);
		return true;
	}
	if (wParam == VK_LEFT)
	{
		if (role.state == 2)
		{
			role.Init(IDB_ROLE_PROF2);
			role.InitMask(IDB_ROLE_PROF2_MASK);
			role.SetState(3);
		}
		else if (role.state == 3)
		{
			role.Init(IDB_ROLE_PROF3);
			role.InitMask(IDB_ROLE_PROF3_MASK);
			role.SetState(2);
		}
		role.SetDirection(ROLE_LEFT);
		ROLE::move(MOVE_LEFT);
		if (ROLE::checkwall())
		{
			viewx -= MOVE_SPEED;
			if (role.shadow == 0 && monster.checkkill(role) == false) setState(GAMESTATE_OVER);

			if (role.checkfloor() == MAPTYPE_FLOOR_WIN) setState(GAMESTATE_END);
		}
		else ROLE::move(MOVE_RIGHT);
		return true;
	}
	if (wParam == VK_SPACE)
	{
		role.switchShadow();

		return true;
	}
}

void GAMESTATE::setMusic()
{
	music = !music;
}

MENU::MENU()
{
	menuNum = MENUSTATE_START_TUTORIAL;
	music = 1;
}

MENU::~MENU()
{

}
