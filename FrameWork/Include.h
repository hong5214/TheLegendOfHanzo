#pragma once
#include <list>

// d3d, sound 사용하기위한 라이브러리
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dsound.lib")

// 데이터 베이스 관련 헤더 및 라이브러리
#include <winsock2.h>
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")

// 시스템 구현 관련 헤더파일
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// d3d, sound 관련 헤더파일
#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>
#include "FmodSound.h"

// 기본값, 폰트, 스프라이트(이미지), 챕터 지정 관련 헤더파일
#include "Define.h"
#include "DeviceFont.h"
#include "Sprite.h"
#include "Chap.h"
#include "ImageInfo.h"

// 챕터 관련 헤더 파일
#include "Game.h"
#include "Logo.h"
#include "Menu.h"
#include "Over.h"
#include "CMng.h"

// 몬스터 관련 헤더파일
#include "Character.h"
#include "Monster.h"
#include "Player.h"

// 맵, 키, 사운드, 게임 매니저(컨테이너) 관련 헤더파일
#include "Map.h"
#include "Iteminfo.h"
#include "Stat.h"
#include "Help.h"
#include "Key.h"
#include "Sound.h"
#include "Container.h"
#include "MonsterMGR.h"
#include "GameManager.h"
#include "MenuManager.h"


// 직접 만든 데이터 베이스 관련 헤더파일
#include "Mysql.h"

// 키 입력을 위한 추가 함수
inline int KeyDown	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 1:0 ); 
}

inline int KeyUp	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 0:1 ); 
}