#include "Include.h"
MenuManager Mmanager;

MenuManager::MenuManager(void)
{
	
}

MenuManager::~MenuManager(void)
{
}

void MenuManager::Init() {
	btnIndex = 7; // ��ư �ε���(Start)
	shopIndex = 5; // ����â �ε���(5 : �̻����)
	shopSellCount = 0; // ����â ���� ����(1, 10��)
	equTypeIndex = 4; // ���â Ÿ�� �ε���(4 : �̻����)
	itemIndex = 16; // ������ �ε���
	itemPerDelay = 100; // ���� ������ ���� ������
	sprintf_s(itemCount, ""); // ���â�� ǥ���� ������ ī��Ʈ

	ItemTime = GetTickCount64();
}