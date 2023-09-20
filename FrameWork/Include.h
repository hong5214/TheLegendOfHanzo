#pragma once
#include <list>

// d3d, sound ����ϱ����� ���̺귯��
#pragma comment(lib,"d3d9.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib,"dsound.lib")

// ������ ���̽� ���� ��� �� ���̺귯��
#include <winsock2.h>
#include <mysql.h>
#pragma comment(lib, "libmySQL.lib")

// �ý��� ���� ���� �������
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

// d3d, sound ���� �������
#include <d3d9.h>
#include <d3dx9.h>
#include <dsound.h>
#include "FmodSound.h"

// �⺻��, ��Ʈ, ��������Ʈ(�̹���), é�� ���� ���� �������
#include "Define.h"
#include "DeviceFont.h"
#include "Sprite.h"
#include "Chap.h"
#include "ImageInfo.h"

// é�� ���� ��� ����
#include "Game.h"
#include "Logo.h"
#include "Menu.h"
#include "Over.h"
#include "CMng.h"

// ���� ���� �������
#include "Character.h"
#include "Monster.h"
#include "Player.h"

// ��, Ű, ����, ���� �Ŵ���(�����̳�) ���� �������
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


// ���� ���� ������ ���̽� ���� �������
#include "Mysql.h"

// Ű �Է��� ���� �߰� �Լ�
inline int KeyDown	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 1:0 ); 
}

inline int KeyUp	( int vk ) 
{ 
	return ( (GetAsyncKeyState(vk) & 0x8000) ? 0:1 ); 
}