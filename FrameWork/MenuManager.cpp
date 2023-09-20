#include "Include.h"
MenuManager Mmanager;

MenuManager::MenuManager(void)
{
	
}

MenuManager::~MenuManager(void)
{
}

void MenuManager::Init() {
	btnIndex = 7; // 버튼 인덱스(Start)
	shopIndex = 5; // 상점창 인덱스(5 : 미사용중)
	shopSellCount = 0; // 상점창 구매 개수(1, 10개)
	equTypeIndex = 4; // 장비창 타입 인덱스(4 : 미사용중)
	itemIndex = 16; // 아이템 인덱스
	itemPerDelay = 100; // 랜덤 아이템 생성 딜레이
	sprintf_s(itemCount, ""); // 장비창에 표시할 아이템 카운트

	ItemTime = GetTickCount64();
}