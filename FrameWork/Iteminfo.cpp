#include "Include.h"

ItemInfo itemInfo;

void ItemInfo::Init() {
	itemBox.Create("./resource/Img/menu/effect/itemBox.png", false, D3DCOLOR_XRGB(0, 0, 0));
	equBox.Create("./resource/Img/menu/effect/equBox.png", false, D3DCOLOR_XRGB(0, 0, 0));
	itemEmpty.Create("./resource/Img/menu/effect/itemEmpty.png", false, D3DCOLOR_XRGB(0, 0, 0));
	for (int i = 0; i < 4; i++)
	{
		char FileName[256];
		sprintf_s(FileName, "./resource/Img/menu/effect/itemLevel%02d.png", i);
		itemBG[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
	for (int i = 0; i < 16; i++)
	{
		char FileName[256];
		sprintf_s(FileName, "./resource/Img/Item/Bow%02d.png", i);
		itemBowImg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
		sprintf_s(FileName, "./resource/Img/Item/Cap%02d.png", i);
		itemCapImg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
		sprintf_s(FileName, "./resource/Img/Item/Armor%02d.png", i);
		itemArmorImg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
		sprintf_s(FileName, "./resource/Img/Item/Shoes%02d.png", i);
		itemShoesImg[i].Create(FileName, false, D3DCOLOR_XRGB(0, 0, 0));
	}
}
void ItemInfo::RandomPerSet(int idx) {
	RandomPer[idx] = rand() % 1000; // 10회 뽑기할 랜덤 변수 저장
}

void ItemInfo::BuyItem(int idx, int type) {
	srand(time(NULL)); // 살때마다 시간 초기화
	type == 0 ? RandomItem(idx) : RandomSelectItem(idx, type);
	sprintf_s(itemBoxNum[idx], "%02d", itemNum); // 아이템 박스 번호 변경
	itemBoxType[idx] = itemType;
	itemBoxUse = true;
	itemBoxTime = GetTickCount64(); // 뽑는 시간 초기화
}

void ItemInfo::RandomItem(int idx) {
	int per = RandomPer[idx];
	if (per < 860) // 일반 장비
		itemLevel = 0;
	else if (860 <= per && per < 980) // 레어 장비
		itemLevel = 1;
	else if (980 <= per && per < 995) // 에픽 장비
		itemLevel = 2;
	else if (995 <= per) // 전설 장비
		itemLevel = 3;
	
	itemType = (per % 64) / 16; // 아이템 종류(무기,헬멧,갑옷,신발)
	itemNum = (per % 4 * 4) + itemLevel; // 아이템 번호(추가할 아이템 번호)
	sql.setItemCount();
}

void ItemInfo::RandomSelectItem(int idx, int type) {
	int per = RandomPer[idx];
	if (per < 870) // 일반 장비
		itemLevel = 0;
	else if (870 <= per && per < 985) // 레어 장비
		itemLevel = 1;
	else if (985 <= per && per < 997)// 에픽 장비
		itemLevel = 2;
	else if (997 <= per) // 전설 장비
		itemLevel = 3;
	itemType = type - 1; // 아이템 종류(무기,헬멧,갑옷,신발)
	itemNum = (per % 4 * 4) + itemLevel; // 아이템 번호(추가할 아이템 번호)
	sql.setItemCount();
}

void ItemInfo::UpdateItem(int idx, int type) {
	switch (type)
	{
	case 0:
		switch (idx % 4)
		{
		case 0:
			sprintf_s(itemEquName, "일반 활%d", idx / 4 + 1);
			break;
		case 1:
			sprintf_s(itemEquName, "레어 활%d", idx / 4 + 1);
			break;
		case 2:
			sprintf_s(itemEquName, "에픽 활%d", idx / 4 + 1);
			break;
		case 3:
			sprintf_s(itemEquName, "전설 활%d", idx / 4 + 1);
			break;
		}
		sprintf_s(itemEquOption1, "(1) 공격력 + %d", (idx % 4 + 1)*3);
		sprintf_s(itemEquOption2, "(2) 공속 - %d", (idx % 4 + 1) * 20);
		break;
	case 1:
		switch (idx % 4)
		{
		case 0:
			sprintf_s(itemEquName, "일반 헬멧%d", idx / 4 + 1);
			break;
		case 1:
			sprintf_s(itemEquName, "레어 헬멧%d", idx / 4 + 1);
			break;
		case 2:
			sprintf_s(itemEquName, "에픽 헬멧%d", idx / 4 + 1);
			break;
		case 3:
			sprintf_s(itemEquName, "전설 헬멧%d", idx / 4 + 1);
			break;
		}
		sprintf_s(itemEquOption1, "(1) 쿨감 - %d", (idx % 4 + 1) * 2);
		sprintf_s(itemEquOption2, "(2) 명중률 + %d", (idx % 4 + 1) * 4);
		break;
	case 2:
		switch (idx % 4)
		{
		case 0:
			sprintf_s(itemEquName, "일반 갑옷%d", idx / 4 + 1);
			break;
		case 1:
			sprintf_s(itemEquName, "레어 갑옷%d", idx / 4 + 1);
			break;
		case 2:
			sprintf_s(itemEquName, "에픽 갑옷%d", idx / 4 + 1);
			break;
		case 3:
			sprintf_s(itemEquName, "전설 갑옷%d", idx / 4 + 1);
			break;
		}
		sprintf_s(itemEquOption1, "(1) 방어력 + %d", (idx % 4 + 1) * 2);
		sprintf_s(itemEquOption2, "(2) 체력 + %d", (idx % 4 + 1) * 10);
		break;
	case 3:
		switch (idx % 4)
		{
		case 0:
			sprintf_s(itemEquName, "일반 신발%d", idx / 4 + 1);
			break;
		case 1:
			sprintf_s(itemEquName, "레어 신발%d", idx / 4 + 1);
			break;
		case 2:
			sprintf_s(itemEquName, "에픽 신발%d", idx / 4 + 1);
			break;
		case 3:
			sprintf_s(itemEquName, "전설 신발%d", idx / 4 + 1);
			break;
		}
		sprintf_s(itemEquOption1, "(1) 이속 + %d", idx % 4 + 1);
		sprintf_s(itemEquOption2, "(2) 방어률 + %d", (idx % 4 + 1) * 10);
		break;
	}
}

void ItemInfo::SelectItem() {
	switch (Mmanager.equTypeIndex)
	{
	case 0:
		switch (Mmanager.itemIndex % 4)
		{
		case 0:
			sprintf_s(itemSelectName, "일반 활%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 1:
			sprintf_s(itemSelectName, "레어 활%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 2:
			sprintf_s(itemSelectName, "에픽 활%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 3:
			sprintf_s(itemSelectName, "전설 활%d", Mmanager.itemIndex / 4 + 1);
			break;
		}
		sprintf_s(itemOption1, "(1) 공격력 + %d", (Mmanager.itemIndex % 4 + 1) * 3);
		sprintf_s(itemOption2, "(2) 공속 - %d", (Mmanager.itemIndex % 4 + 1) * 20);
		break;
	case 1:
		switch (Mmanager.itemIndex % 4)
		{
		case 0:
			sprintf_s(itemSelectName, "일반 헬멧%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 1:
			sprintf_s(itemSelectName, "레어 헬멧%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 2:
			sprintf_s(itemSelectName, "에픽 헬멧%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 3:
			sprintf_s(itemSelectName, "전설 헬멧%d", Mmanager.itemIndex / 4 + 1);
			break;
		}
		sprintf_s(itemOption1, "(1) 쿨감 - %d", (Mmanager.itemIndex % 4 + 1) * 2);
		sprintf_s(itemOption2, "(2) 명중률 + %d", (Mmanager.itemIndex % 4 + 1) * 4);
		break;
	case 2:
		switch (Mmanager.itemIndex % 4)
		{
		case 0:
			sprintf_s(itemSelectName, "일반 갑옷%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 1:
			sprintf_s(itemSelectName, "레어 갑옷%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 2:
			sprintf_s(itemSelectName, "에픽 갑옷%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 3:
			sprintf_s(itemSelectName, "전설 갑옷%d", Mmanager.itemIndex / 4 + 1);
			break;
		}
		sprintf_s(itemOption1, "(1) 방어력 + %d", (Mmanager.itemIndex % 4 + 1) * 2);
		sprintf_s(itemOption2, "(2) 체력 + %d", (Mmanager.itemIndex % 4 + 1) * 10);
		break;
	case 3:
		switch (Mmanager.itemIndex % 4)
		{
		case 0:
			sprintf_s(itemSelectName, "일반 신발%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 1:
			sprintf_s(itemSelectName, "레어 신발%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 2:
			sprintf_s(itemSelectName, "에픽 신발%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 3:
			sprintf_s(itemSelectName, "전설 신발%d", Mmanager.itemIndex / 4 + 1);
			break;
		}
		sprintf_s(itemOption1, "(1) 이속 + %d", Mmanager.itemIndex % 4 + 1);
		sprintf_s(itemOption2, "(2) 방어률 + %d", (Mmanager.itemIndex % 4 + 1) * 10);
		break;
	}
}
void ItemInfo::PlusOption() {	
	if (itemUse[0] != 16) // 무기 보유
	{
		// 공격력, 공격속도 증가
		statInfo.plusAtk = (3 * (itemUse[0] % 4 + 1));
		statInfo.plusAtkSpeed = (20 * (itemUse[0] % 4 + 1));
	}
	else {
		statInfo.plusAtk = 0;
		statInfo.plusAtkSpeed = 0;
	}

	if (itemUse[1] != 16) // 헬멧 보유
	{
		// 스킬 쿨타임 감소, 명중률 증가
		statInfo.plusSklDelay = (2.0 * (itemUse[1] % 4 + 1));
		statInfo.plusHitPer = (4 * (itemUse[1] % 4 + 1));
	}
	else {
		statInfo.plusSklDelay = 0;
		statInfo.plusHitPer = 0;
	}
	if (itemUse[2] != 16) // 갑옷 보유
	{
		// 방어력, 체력 증가
		statInfo.plusDef = (2 * (itemUse[2] % 4 + 1));
		statInfo.plusHp = (10 * (itemUse[2] % 4 + 1));
	}
	else {
		statInfo.plusHp = 0;
		statInfo.plusHp = 0;
	}
	if (itemUse[3] != 16) // 신발 보유
	{
		// 이동속도, 회피율 증가
		statInfo.plusMoveSpeed = (1 * (itemUse[3] % 4 + 1));
		statInfo.plusMissPer = (10 * (itemUse[3] % 4 + 1));
	}
	else {
		statInfo.plusMoveSpeed = 0;
		statInfo.plusMissPer = 0;
	}
}

// 아이템 뽑기 시 그려주는 함수
void ItemInfo::DrawItem(int idx) {
	switch (itemBoxType[idx])
	{
	case 0:
		itemBG[atoi(itemBoxNum[idx]) % 4].Render(SCREEN_WITH / 4 + 60 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 20 + (idx / 5) * 100, 0, 1, 1); // 아이템 박스 출력
		itemBowImg[atoi(itemBoxNum[idx])].Render(SCREEN_WITH / 4 + 70 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 30 + (idx / 5) * 100, 0, 1, 1); // 아이템 박스 출력
		dv_font.DrawString(itemBoxNum[idx], SCREEN_WITH / 4 + 95 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 100 + (idx / 5) * 100);
		break;
	case 1:
		itemBG[atoi(itemBoxNum[idx]) % 4].Render(SCREEN_WITH / 4 + 60 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 20 + (idx / 5) * 100, 0, 1, 1); // 아이템 박스 출력
		itemCapImg[atoi(itemBoxNum[idx])].Render(SCREEN_WITH / 4 + 70 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 30 + (idx / 5) * 100, 0, 1, 1); // 아이템 박스 출력
		dv_font.DrawString(itemBoxNum[idx], SCREEN_WITH / 4 + 95 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 100 + (idx / 5) * 100);
		break;
	case 2:
		itemBG[atoi(itemBoxNum[idx]) % 4].Render(SCREEN_WITH / 4 + 60 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 20 + (idx / 5) * 100, 0, 1, 1); // 아이템 박스 출력
		itemArmorImg[atoi(itemBoxNum[idx])].Render(SCREEN_WITH / 4 + 70 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 30 + (idx / 5) * 100, 0, 1, 1); // 아이템 박스 출력
		dv_font.DrawString(itemBoxNum[idx], SCREEN_WITH / 4 + 95 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 100 + (idx / 5) * 100);
		break;
	case 3:
		itemBG[atoi(itemBoxNum[idx]) % 4].Render(SCREEN_WITH / 4 + 60 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 20 + (idx / 5) * 100, 0, 1, 1); // 아이템 박스 출력
		itemShoesImg[atoi(itemBoxNum[idx])].Render(SCREEN_WITH / 4 + 70 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 30 + (idx / 5) * 100, 0, 1, 1); // 아이템 박스 출력
		dv_font.DrawString(itemBoxNum[idx], SCREEN_WITH / 4 + 95 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 100 + (idx / 5) * 100);
		break;
	}
}

void ItemInfo::DrawItemInfo(int idx, int type) {
	dv_font.DrawStringItem("<장착전>", 755, 230);
	dv_font.DrawStringItem("[이름]", 720, 250);
	dv_font.DrawStringItem(itemEquName, 770, 250);
	dv_font.DrawStringItem("[능력]", 720, 270);
	dv_font.DrawStringItem(itemEquOption1, 720, 290);
	dv_font.DrawStringItem(itemEquOption2, 720, 310);


	dv_font.DrawStringItem("<장착후>", 755, 340);
	dv_font.DrawStringItem("[이름]", 720, 360);
	dv_font.DrawStringItem(itemSelectName, 770, 360);
	dv_font.DrawStringItem("[능력]", 720, 380);
	dv_font.DrawStringItem(itemOption1, 720, 400);
	dv_font.DrawStringItem(itemOption2, 720, 420);
}