#include "Include.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Init()
{
	Mmanager.Init(); // 메뉴 정보 초기화
	imageInfo.Init(); // 사용할 이미지들 초기화
}

// Chap, 재정의 함수 호출
void Menu::Update(double frame)
{
	if (GetTickCount64() - Mmanager.ItemTime > rand() % Mmanager.itemPerDelay) // 아이템 뽑기 확률 랜덤 조정
	{
		Mmanager.itemPerDelay = rand() % 1000 + 1; // 딜레이 시간을 랜덤으로 변경
		itemInfo.RandomPerSet((Mmanager.itemPerDelay - 1) % 10); // 10회 뽑기할 랜덤 변수 저장
		Mmanager.ItemTime = GetTickCount64();
	}
	if (!itemInfo.itemBoxUse && !Gmanager.LoadingState) {
		key.Update(); // 키 입력 받기
		statInfo.Update(); // 스탯 정보 초기화
		if (Mmanager.itemIndex != 16) // 아이템 정보창 갱신
		{
			// 장착하고있는 장비정보 갱신
			if (itemInfo.itemUse[Mmanager.equTypeIndex] != 16) // 장착중이면
				itemInfo.UpdateItem(itemInfo.itemUse[Mmanager.equTypeIndex] % 16, Mmanager.equTypeIndex);
			else
			{
				sprintf_s(itemInfo.itemEquName, "없음");
				sprintf_s(itemInfo.itemEquOption1, "(1) 없음");
				sprintf_s(itemInfo.itemEquOption2, "(2) 없음");
			}			
			
			// 선택한 아이템 장비정보 갱신
			itemInfo.SelectItem();
		}
	}	
}

void Menu::Draw()
{	
	statInfo.Draw(); // 유저 정보 표시(레벨, 경험치, 골드)
	if (true) // 스탯 보이기 유무에 따라 출력
	{
		statInfo.ShowStat();
	}

	switch (Mmanager.btnIndex) // 버튼에 따라 메뉴 배경 이미지 및 효과 변경
	{
	case SHOP:
		imageInfo.menuImg[0].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //이미지출력
		dv_font.DrawString("상점", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280, 645, 0, 0.2, 0.2);
		break;
	case EQU:
		if (Mmanager.equTypeIndex != 4)
			imageInfo.itemTypeImg[Mmanager.equTypeIndex].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //이미지출력		
		else
			imageInfo.menuImg[1].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //이미지출력
		dv_font.DrawString("장비", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280 + (115* Mmanager.btnIndex), 645, 0, 0.2, 0.2);
		break;
	case HOME:
		imageInfo.menuImg[2].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //이미지출력
		dv_font.DrawString("로비", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280 + (115* Mmanager.btnIndex), 645, 0, 0.2, 0.2);
		break;
	case QUEST:
		imageInfo.menuImg[3].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //이미지출력
		dv_font.DrawString("퀘스트", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280 + (115* Mmanager.btnIndex), 645, 0, 0.2, 0.2);
		break;
	case SETTING:
		imageInfo.menuImg[4].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //이미지출력
		dv_font.DrawString("설정", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280 + (115* Mmanager.btnIndex), 645, 0, 0.2, 0.2);
		break;
	case LOGOUT:
		imageInfo.menuImg[2].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //이미지출력
		dv_font.DrawString("로그아웃", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280, 680, 0, 0.2, 0.2);
		break;
	case START:
		imageInfo.menuImg[2].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //이미지출력
		dv_font.DrawString("시작", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 50, 680, 0, 0.2, 0.2);
		break;
	case EXIT:
		imageInfo.menuImg[2].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //이미지출력
		dv_font.DrawString("종료", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith + 180, 680, 0, 0.2, 0.2);
		break;
	}
	
	// 버튼 표시
	for (int i = 0; i < 5; i++)
		imageInfo.bt_menu[i].Render(imageInfo.centerWith - 280 + (115 * i), 650, 0, 0.4, 0.4);
	imageInfo.bt_logout.Render(imageInfo.centerWith - 280, 685, 0, 0.4, 0.4);
	imageInfo.bt_start.Render(imageInfo.centerWith - 50, 685, 0, 0.4, 0.4);
	imageInfo.bt_exit.Render(imageInfo.centerWith + 180, 685, 0, 0.4, 0.4);

	if (Mmanager.shopIndex == 5 && Mmanager.equTypeIndex == 4)
	{
		if (true)
			imageInfo.HelpMenu.Render(SCREEN_WITH - imageInfo.HelpLogo.imagesinfo.Width, 200, 0, 1, 1);
	}
	else if (Mmanager.shopIndex != 5) // 상점 이용시
	{
		if (true)
			imageInfo.HelpShop.Render(SCREEN_WITH - imageInfo.HelpLogo.imagesinfo.Width, 200, 0, 1, 1);
		imageInfo.bt_shopBorder.Render(imageInfo.centerWith + 72 + Mmanager.shopSellCount * 72, 67 + Mmanager.shopIndex * 90, 0, 1, 1);
		imageInfo.bt_shopSelect.Render(imageInfo.centerWith + 210, 70 + Mmanager.shopIndex * 90, 0, 1, 1);
		// 아이템 뽑기 출력
		if (GetTickCount64() - itemInfo.itemBoxTime <= 1000 && itemInfo.itemBoxUse)
		{
			itemInfo.itemBox.Render(SCREEN_WITH / 4, SCREEN_HEIGHT / 2 - itemInfo.itemBox.imagesinfo.Height / 2, 0, 1, 1); // 아이템 박스 출력
			if (Mmanager.shopSellCount == 0) // 1개 뽑기시 1번째 아이템 아이템만 그려주기
				itemInfo.DrawItem(0);
			else
				for (int i = 0; i < 10; i++) // 10개 뽑기시 10개 아이템 그려주기
					itemInfo.DrawItem(i);
		}
		else
			itemInfo.itemBoxUse = false;
	}
	else if (Mmanager.equTypeIndex != 4) { // 장비 이용시		
		if (true)
			imageInfo.HelpItem.Render(SCREEN_WITH - imageInfo.HelpLogo.imagesinfo.Width, 200, 0, 1, 1);
		imageInfo.bt_itemTypeSelect.Render(imageInfo.centerWith - 235 + 124 * Mmanager.equTypeIndex, 70, 0, 1, 1); // 장비 타입 선택
		itemInfo.equBox.Render(SCREEN_WITH / 4, SCREEN_HEIGHT / 2 + 180, 0, 1, 1);
		for (int i = 0; i < 4; i++) {
			if (itemInfo.itemUse[i] != 16) // 부위별로 착용했으면 그려주기
			{
				itemInfo.itemBG[itemInfo.itemUse[i] % 4].Render(imageInfo.centerWith - 226 + 124 * i, SCREEN_HEIGHT / 2 + 190, 0, 1, 1); // 장비 타입				
				switch (i)
				{
					case 0:
						itemInfo.itemBowImg[itemInfo.itemUse[i] % 16].Render(imageInfo.centerWith - 216 + 124 * i, SCREEN_HEIGHT / 2 + 200, 0, 1, 1); // 장비 이미지				
						break;
					case 1:
						itemInfo.itemCapImg[itemInfo.itemUse[i] % 16].Render(imageInfo.centerWith - 216 + 124 * i, SCREEN_HEIGHT / 2 + 200, 0, 1, 1); // 장비 이미지
						break;
					case 2:
						itemInfo.itemArmorImg[itemInfo.itemUse[i] % 16].Render(imageInfo.centerWith - 216 + 124 * i, SCREEN_HEIGHT / 2 + 200, 0, 1, 1); // 장비 이미지
						break;
					case 3:
						itemInfo.itemShoesImg[itemInfo.itemUse[i] % 16].Render(imageInfo.centerWith - 216 + 124 * i, SCREEN_HEIGHT / 2 + 200, 0, 1, 1); // 장비 이미지
						break;
				}
			}
			else
			{
				itemInfo.itemBG[0].Render(imageInfo.centerWith - 226 + 124 * i, SCREEN_HEIGHT / 2 + 190, 0, 1, 1); // 장비 타입없어서 일반
				itemInfo.itemEmpty.Render(imageInfo.centerWith - 226 + 124 * i, SCREEN_HEIGHT / 2 + 190, 0, 1, 1); // 빈 이미지				
			}
		}

		for (int i = 0; i < 16; i++)
		{
			switch (Mmanager.equTypeIndex)
			{
			case 0:
				sprintf_s(Mmanager.itemCount, "%d", itemInfo.itemBow[i]);
				break;
			case 1:
				sprintf_s(Mmanager.itemCount, "%d", itemInfo.itemCap[i]);
				break;
			case 2:
				sprintf_s(Mmanager.itemCount, "%d", itemInfo.itemArmor[i]);
				break;
			case 3:
				sprintf_s(Mmanager.itemCount, "%d", itemInfo.itemShoes[i]);
				break;
			}
			dv_font.DrawStringItem(Mmanager.itemCount, imageInfo.centerWith - 190 + 83 * (i / 4), 235 + 84 * (i % 4));
		}
		if (Mmanager.itemIndex != 16) // 아이템 선택시
		{
			imageInfo.bt_itemSelect.Render(imageInfo.centerWith - 245 + 82 * (Mmanager.itemIndex / 4), 188 + 84 * (Mmanager.itemIndex % 4), 0, 1.4, 1);
			itemInfo.DrawItemInfo(Mmanager.itemIndex, Mmanager.equTypeIndex);
		}
	}	
}