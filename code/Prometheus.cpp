// Prometheus.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Prometheus.h"
#include "display.h"
#include "logic.h"
#include "clock.h"
#include "eyecatch.h"
#include "define.h"
#include "mmsystem.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;                                // 当前实例
WCHAR szTitle[MAX_LOADSTRING];                  // 标题栏文本
WCHAR szWindowClass[MAX_LOADSTRING];            // 主窗口类名

/*==========自定义变量================*/
HDC hscreen,hdcbuf;
HDC hwindow;
HDC hwinBuffer;
HBITMAP hmapNull,hbmbuf,hbmoldbuf;

POINT point;
DISPLAY arrow;
BK bk;
BK testmap;
MAP test;
BK mask;
MONSTER monster;

ROLE role=ROLE();
GAMESTATE game;
MENU menu=MENU();
CLOCK clk;
ANIMATE ani;

int viewx;
int viewy;
/*====================================*/

// 此代码模块中包含的函数的前向声明: 
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 在此放置代码。

    // 初始化全局字符串
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_PROMETHEUS, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 执行应用程序初始化: 
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_PROMETHEUS));

    MSG msg;

    // 主消息循环: 
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROMETHEUS));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 将实例句柄存储在全局变量中
   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0,WINDOW_WIDTH, WINDOW_HEIGHT, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }
   /*=====自定义初始化======*/
   /*加载图片*/

   hwindow = GetDC(hWnd);
   hwinBuffer= CreateCompatibleDC(hwindow);
   hscreen = CreateCompatibleDC(hwindow);
   hmapNull = CreateCompatibleBitmap(hwindow,7800,5600);
   hbmbuf= CreateCompatibleBitmap(hwindow, WINDOW_WIDTH, WINDOW_HEIGHT);

   game.setPosition(role.x*100, role.y*100);

	bk.Init(IDB_MENU);
	bk.SetPosition(0, 0);

	ani.Init(IDB_PRELUDE);

	testmap.Init(IDB_TESTMAP);
	testmap.SetPosition(0, 0);

	test.InitMapObj(IDB_BLOCK,IDB_LIGHT,IDB_DARK,IDB_WALL,IDB_DESTINATION);
	test.ReadMap();

	mask.Init(IDB_MASK);
	mask.InitMask(IDB_MASK_2);

	monster.Init(IDB_MONSTER);
	monster.InitMask(IDB_MONSTER_MASK);
	monster.readMonster();

	role.InitRole(IDB_ROLE,IDB_ROLE_MASK,IDB_VALUE,IDB_VALUE_MASK);
	role.SetPosition(400, 300);

  arrow.Init(IDB_ARROW);
  clk.Begin(hWnd, 500);
  /*=======================*/
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND  - 处理应用程序菜单
//  WM_PAINT    - 绘制主窗口
//  WM_TIMER    - 接收定时器消息
//  WM_KEYDOWN  - 接收键盘消息
//  WM_DESTROY  - 发送退出消息并返回
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{	
	switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 分析菜单选择: 
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
			PAINTSTRUCT ps;
            hwindow = BeginPaint(hWnd, &ps);
			SelectObject(hscreen, hmapNull);
			SelectObject(hwinBuffer,hbmbuf);
			switch (game.state)
			{
			case GAMESTATE_MENU://显示开始（菜单栏）界面				
				bk.DrawBasic(hscreen);
				if (menu.music)
				{
					PlaySound(TEXT("bgm//main_bgm.wav"),NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
					menu.setMusic();
				}
				
				switch (menu.menuNum)//通过menu.state设定箭头的位置，达到指向对应菜单栏的效果
				{
				case MENUSTATE_START_TUTORIAL:
					arrow.SetPosition(670, 250);
					arrow.DrawBasic(hscreen);
					break;
				case MENUSTATE_START:
					arrow.SetPosition(800, 300);
					arrow.DrawBasic(hscreen);
					break;
				case MENUSTATE_HELP:
					arrow.SetPosition(690, 370);
					arrow.DrawBasic(hscreen);
					break;
				case MENUSTATE_EXIT:
					arrow.SetPosition(810, 420);
					arrow.DrawBasic(hscreen);
					break;
				}
				BitBlt(hwindow, 0, 0, bk.width, bk.height, hscreen, 0, 0, SRCCOPY);
				break;
			case GAMESTATE_HELP:
				bk.DrawBasic(hscreen);
				BitBlt(hwindow, 0, 0, bk.width, bk.height, hscreen, 0, 0, SRCCOPY);
				break;
			case GAMESTATE_ANIMATE_0://序幕过场
				ani.SetFrame(0);
				ani.SetFont(hscreen, RGB(0, 0, 0), RGB(255, 255, 255), 400, 500);	
				ani.PlayAni(hscreen);			
				if (ani.timer == 34)
				{
					game.setState(GAMESTATE_ING_1);
					ani.SetTimer(0,1);
				}
				
				BitBlt(hwindow, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hscreen, 0, 0, SRCCOPY);
				break;
			case GAMESTATE_ING_1://游戏中的界面		
				testmap.DrawBasic(hscreen);
				test.ShowMapObj(hscreen);
				if(!role.shadow)
					monster.ShowMonster(hscreen);				
				BitBlt(hwinBuffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,hscreen,game.viewx,game.viewy, SRCCOPY);
				if(!role.shadow)
					mask.Normal(hwinBuffer,role);

				role.DrawRole(hwinBuffer);
				role.ShowLight(hwinBuffer);			

				BitBlt(hwindow, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, hwinBuffer, 0, 0, SRCCOPY);
				
				break;
			case GAMESTATE_END:
				bk.Init(IDB_PASS);
				bk.DrawBasic(hwindow);
				break;
			case GAMESTATE_OVER:
				bk.Init(IDB_GAMEOVER);
				bk.DrawBasic(hwindow);
				break;
			}
            EndPaint(hWnd, &ps);
        }
        break;
	case WM_TIMER:
		
		/*if (game.state == GAMESTATE_ING_1)//接收定时器消息以后，如果游戏状态为游戏中，那么，改变坐标，再次绘制窗口的时候就可以产生动画效果
		{
			if (monster.xpos >= 860) 
			{
				monster.xpos = 0;
				monster.ypos = 0;
		    }
			else 
			monster.xpos++; 
        InvalidateRect(hWnd, NULL, FALSE);//重新绘制窗口的函数
		
		}*/
		switch (game.state)
		{			
			case GAMESTATE_ING_1://接收定时器消息以后，如果游戏状态为游戏中，那么，改变坐标，再次绘制窗口的时候就可以产生动画效果
			{
				role.SetTimer(1);
				if (role.timer == 3)
				{
					switch (role.direction) {
					case ROLE_FRONT:role.Init(IDB_ROLE); role.InitMask(IDB_ROLE_MASK); break;
					case ROLE_BACK:role.Init(IDB_ROLE_BACK1); role.InitMask(IDB_ROLE_BACK1_MASK); break;
					case ROLE_LEFT:role.Init(IDB_ROLE_PROF1); role.InitMask(IDB_ROLE_PROF1_MASK); break;
					case ROLE_RIGHT:role.Init(IDB_ROLE_RIGHT_PROF1); role.InitMask(IDB_ROLE_RIGHT_PROF1_MASK); break;
					}
					role.SetTimer(-3);
				}
				if (role.shadow == 1)
				{
 				role.setLight(-5);		//阴影化状态light值流失
				}

			monster.refresh();
			if (role.checkfloor() == MAPTYPE_FLOOR_LIGHT) role.setLight(3);
			if (role.checkfloor() == MAPTYPE_FLOOR_DARK) role.setLight(-5);
			if (role.shadow == 0 && monster.checkkill(role) == false) game.setState(GAMESTATE_OVER);

			InvalidateRect(hWnd, NULL, FALSE);//重新绘制窗口的函数
			break;
			}
			case GAMESTATE_ANIMATE_0:
			{
				ani.SetTimer(1,0);
				InvalidateRect(hWnd, NULL, FALSE);
				break;
			}
			case GAMESTATE_OVER:
			{
				break;
			}
			
			case GAMESTATE_END:
			{
				break;
			}
		}

		break;
	//case WM_ERASEBKGND:return TRUE; break;
	case WM_KEYDOWN:
		if(game.state==GAMESTATE_MENU)
		{ 			
			if (wParam == VK_DOWN) //按下方向键下键时，改变menu.state(指示指向哪一条菜单栏)
			{
				menu.menuNum=(menu.menuNum +1)%4;//通过模除达到循环的效果
				InvalidateRect(hWnd, NULL, FALSE);
			}
			if (wParam == VK_UP) //按下上键
			{
				menu.menuNum = menu.menuNum - 1;
				if (menu.menuNum < 0)//不能用模除了，这样也可以实现循环指向
					menu.menuNum = 3;
				InvalidateRect(hWnd, NULL, FALSE);
			}
			if (wParam == VK_RETURN&&menu.menuNum == MENUSTATE_START_TUTORIAL)//按下回车，且此时指向tutorial时，进入下一界面
			{
				PlaySound(TEXT("bgm//menu_button.wav"), NULL, SND_FILENAME | SND_ASYNC );
				game.setState(GAMESTATE_ANIMATE_0);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (wParam == VK_RETURN&&menu.menuNum == MENUSTATE_HELP)//按下回车，且此时指向tutorial时，进入下一界面
			{
				PlaySound(TEXT("bgm//menu_button.wav"), NULL, SND_FILENAME | SND_ASYNC);
				game.setState(GAMESTATE_HELP);
				bk.Init(IDB_HELP);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			if (wParam == VK_RETURN&&menu.menuNum == MENUSTATE_EXIT)//按下回车，且此时指向tutorial时，进入下一界面
			{
				PlaySound(TEXT("bgm//menu_button.wav"), NULL, SND_FILENAME | SND_ASYNC);
				PostQuitMessage(0);
			}

		}
		else if (game.state == GAMESTATE_ING_1)
		{
			game.moveCtrl(wParam,role,monster);
			InvalidateRect(hWnd, NULL, FALSE);
		}
		else if (game.state == GAMESTATE_HELP)
		{
			if (wParam = VK_ESCAPE)
			{
				game.setState(GAMESTATE_MENU);
				bk.Init(IDB_MENU);
				InvalidateRect(hWnd, NULL, TRUE);
			}
		}
		else if (game.state == GAMESTATE_END)
		{
			if (wParam == VK_RETURN)
			{
				role.Back();
				game.Back();
				bk.Init(IDB_MENU);
				InvalidateRect(hWnd, NULL, TRUE);
			}
			
		}
		else if (game.state == GAMESTATE_OVER)
		{
			if (wParam == VK_RETURN)
			{
				role.Back();

				game.Back();
				bk.Init(IDB_MENU);
				InvalidateRect(hWnd, NULL, TRUE);
			}

		}
		break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// “关于”框的消息处理程序。
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
