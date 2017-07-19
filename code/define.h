#pragma once

#define WINDOW_WIDTH 960
#define WINDOW_HEIGHT 640

#define GAMESTATE_MENU   0
#define GAMESTATE_HELP   1
#define GAMESTATE_ING_1  10
#define GAMESTATE_ING_2  20
#define GAMESTATE_OVER 30
#define GAMESTATE_END 40 

#define GAMESTATE_ANIMATE_0 100

#define MENUSTATE_START_TUTORIAL 0 //从教学关开始
#define MENUSTATE_START          1 //从正式关开始
#define MENUSTATE_HELP           2
#define MENUSTATE_EXIT           3  

#define ROLE_SHADOW  1
#define MAP_SHADOW   1
#define XMAX		100
#define YMAX		100

#define MOVE_UP  1
#define MOVE_RIGHT  2
#define MOVE_DOWN  3
#define MOVE_LEFT  4
#define MOVE_SPEED 100

#define MAPTYPE_FLOOR		1
#define MAPTYPE_FLOOR_LIGHT		2    
#define MAPTYPE_FLOOR_DARK		3
#define MAPTYPE_FLOOR_WALL		4     //
#define MAPTYPE_FLOOR_WIN		5         //胜利

//12.27update
#define BLOCK_SIZE  100 //地砖大小

#define ROLE_FRONT 1
#define ROLE_BACK  2
#define ROLE_LEFT  3
#define ROLE_RIGHT 4