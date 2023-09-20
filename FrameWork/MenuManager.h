#include "Include.h"

class MenuManager
{

public:
	MenuManager();
	~MenuManager();

	int btnIndex; // 버튼 인덱스
	int shopIndex; // 상점창 인덱스(뽑기선택)
	int shopSellCount; // 상점창 구매 개수(1, 10개)
	int equTypeIndex; // 장비창 타입 인덱스
	int itemIndex; // 아이템 인덱스
	int itemPerDelay; // 랜덤 아이템 생성 딜레이
	char itemCount[100]; // 장비창에 표시할 아이템 카운트

	DWORD ItemTime; // 랜덤 아이템 생성 시간

	void Init();
};

extern MenuManager Mmanager;