#include "Include.h"
class ItemInfo
{
public:
	ItemInfo() {		
		// 뽑을 아이템 정보
		itemLevel = 0;
		itemType = 0;
		itemNum = 0;
		itemMode = 3;
		itemBoxUse = false;
		itemBoxTime = GetTickCount64();
		for (int i = 0; i < 10; i++) {
			RandomPerSet(i); // 랜덤 확률 초기화
			sprintf_s(itemBoxNum[i], "%02d", itemNum); // 박스 번호 초기화
			itemBoxType[i] = 0;
		}
	}
	~ItemInfo() {}

	void Init();
	Sprite itemBox;
	Sprite equBox;
	Sprite itemEmpty;
	Sprite itemBG[4];
	Sprite itemBowImg[16];
	Sprite itemCapImg[16];
	Sprite itemArmorImg[16];
	Sprite itemShoesImg[16];
	char itemBoxNum[10][256]; // 박스 번호
	int itemBoxType[10]; // 박스 아이템 종류

	bool itemBoxUse; // 아이템 뽑을 시
	int RandomPer[10]; // 10회뽑기에 사용할 랜덤 변수
	DWORD itemBoxTime;

	int itemBow[16]; // 무기 아이템 수
	int itemCap[16]; // 헬멧 아이템 수
	int itemArmor[16]; // 갑옷 아이템 수
	int itemShoes[16]; // 신발 아이템 수
	int itemUse[4]; // 장착유무
	char itemEquName[256]; // 아이템 장착 정보
	char itemEquOption1[100]; // 아이템 장착옵션1
	char itemEquOption2[100]; // 아이템 장착옵션2
	char itemSelectName[256]; // 아이템 정보
	char itemOption1[100]; // 아이템 옵션1
	char itemOption2[100]; // 아이템 옵션2
	int itemMode; // 0 : 착용/해제, 1 : 강화, 2 : 합성, 3 : 미선택

	// 뽑을 아이템 정보
	int itemNum; // 아이템 번호(0, 1, 2, 3)
	int itemType; // 아이템 종류(무기, 헬멧, 갑옷, 신발)
	int itemLevel; // 아이템 등급(일반, 레어, 에픽, 전설)	
	
	void RandomPerSet(int idx);
	void BuyItem(int idx, int type); // 아이템 구매
	void RandomItem(int idx); // 랜덤 뽑기
	void RandomSelectItem(int idx, int type); // 선택 뽑기
	void UpdateItem(int idx, int type); // 장착한 장비 정보
	void SelectItem(); // 선택한 장비 정보
	void PlusOption();
	void DrawItem(int idx); // 아이템 뽑기 시 그려주는 함수
	void DrawItemInfo(int idx, int type); // 아이템 선택 시 정보를 그려주는 함수
};

extern ItemInfo itemInfo;