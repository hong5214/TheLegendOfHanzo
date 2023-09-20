#include "Include.h"

Key key;

Key::Key(void)
{
	KeyTime = GetTickCount64();
}

Key::~Key(void)
{
}

void Key::Update()
{	
	/* 로그인 키입력 */
	if (g_Mng.n_Chap == LOGO)
	{
	}
	/* 메뉴 키입력 */
	if (g_Mng.n_Chap == MENU && !Gmanager.LoadingState)
	{
		if (GetTickCount64() - KeyTime > 100)
		{
			// 상점, 장비 이용중이 아닐 때
			if (Mmanager.shopIndex == 5 && Mmanager.equTypeIndex == 4)
			{
				if (KeyDown(VK_UP)) { // 메뉴 상단 이동
					if (Mmanager.btnIndex > TOTALMENU)
						// 바로 위 버튼으로 이동
						Mmanager.btnIndex = Mmanager.btnIndex*2 - 12;
				}
				else if (KeyDown(VK_DOWN)) { // 메뉴 하단 이동
					if (Mmanager.btnIndex < TOTALMENU)
					{
						Mmanager.btnIndex = Mmanager.btnIndex/2 + 6;
					}
				}
				else if (KeyDown(VK_LEFT)) { // 메뉴 좌측 이동
					if (Mmanager.btnIndex < TOTALMENU) // 상단 버튼이면
						Mmanager.btnIndex = (Mmanager.btnIndex + (TOTALMENU - 1)) % TOTALMENU; // 왼쪽으로 이동
					else if(Mmanager.btnIndex != LOGOUT) // 로그아웃 버튼이 아니면
						Mmanager.btnIndex--; // 좌측으로 이동
					else
						Mmanager.btnIndex = EXIT; // 로그아웃버튼이면 종료 버튼으로 이동
				}
				else if (KeyDown(VK_RIGHT)) // 메뉴 우측 이동
				{
					if (Mmanager.btnIndex < TOTALMENU) // 상점 이용중이 아니면 가능
						Mmanager.btnIndex = (Mmanager.btnIndex + 1) % TOTALMENU;
					else if (Mmanager.btnIndex != EXIT) // 종료 버튼이 아니면
						Mmanager.btnIndex++; // 우측으로 이동
					else
						Mmanager.btnIndex = LOGOUT; // 종료버튼이면 로그아웃 버튼으로 이동
				}
				else if (KeyDown(VK_SPACE) || KeyDown(VK_RETURN)) // 메뉴 선택
				{
					EffectPlay(sound.BUTTONCLICK);
					switch (Mmanager.btnIndex) // 메뉴 선택에 따른 변수값 변경
					{
					case SHOP:
						Mmanager.shopIndex = 0; // 상점창 활성화
						break;
					case EQU:
						Mmanager.equTypeIndex = 0; // 장비창 활성화
						break;
					case SETTING: // 회원 탈퇴
						sql.DeleteID();
						g_Mng.n_Chap = LOGO; // 로그인 챕터로 이동
						Mmanager.btnIndex = 7; // 다시 로그인 화면 오면 시작버튼으로
						sound.BGChange("./resource/Sound/BGM_Lobby.mp3");
						Gmanager.LoadingState = true;
						break;
					case HOME: case QUEST: // 준비중
						break;
					case LOGOUT:
						g_Mng.n_Chap = LOGO; // 로그인 챕터로 이동
						Mmanager.btnIndex = 7; // 다시 로그인 화면 오면 시작버튼으로
						sound.BGChange("./resource/Sound/BGM_Lobby.mp3");
						Gmanager.LoadingState = true;
						break;
					case START: // 게임 화면으로 이동
						Gmanager.m_PlayStart = true; // 게임 시작
						player.Init(); // 플레이어 정보 초기화
						g_Mng.chap[GAME]->Init(); // 게임 정보 초기화
						map.m_Stage = 1; // 맵 초기화
						g_Mng.n_Chap = GAME; // 게임 챕터로 이동
						sound.BGChange("./resource/Sound/BGM_Game.mp3");
						break;
					case EXIT:
						PostQuitMessage(0); // 종료
						break;
					}
				}
				else if (KeyDown(VK_ESCAPE)) // 게임 시작 버튼으로 이동
				{
					Mmanager.btnIndex = 7;
				}
			}
			// 상점 이용중일때
			else if (Mmanager.shopIndex != 5)
			{
				if (KeyDown(VK_UP)) // 상점 상단 이동
					Mmanager.shopIndex = (Mmanager.shopIndex + 4) % 5;
				else if (KeyDown(VK_DOWN)) // 상점 하단 이동
					Mmanager.shopIndex = (Mmanager.shopIndex + 1) % 5;
				else if (KeyDown(VK_ESCAPE)) // 메뉴 복귀
					Mmanager.shopIndex = 5;
				else if (KeyDown(VK_LEFT)) // 상점 왼쪽 이동
					Mmanager.shopSellCount = 0;
				else if (KeyDown(VK_RIGHT)) // 상점 오른쪽 이동
					Mmanager.shopSellCount = 1;
				else if (KeyDown(VK_SPACE) || KeyDown(VK_RETURN)) // 상점 선택
				{
					EffectPlay(sound.BUTTONCLICK);
					if (Mmanager.shopSellCount == 0 && player.Gold >= 1000) // 1번 뽑기
					{
						itemInfo.BuyItem(0, Mmanager.shopIndex); // 1개 구매
						player.Gold -= 1000; // 골드변동
						sql.autoSave(); // DB저장
					}
					else if (Mmanager.shopSellCount == 1 && player.Gold >= 10000) // 10번 뽑기
					{
						for (int i = 0; i < 10; i++) // 10번 반복
							itemInfo.BuyItem(i, Mmanager.shopIndex); // 1개 구매
						player.Gold -= 10000; // 골드변동
						sql.autoSave(); // DB저장
					}
				}
			}
			// 장비 이용중일때
			else if (Mmanager.equTypeIndex != 4)
			{
				if (Mmanager.itemIndex != 16) { // 아이템 선택시					
					if (KeyDown(VK_UP)) // 아이템 상단 이동
						Mmanager.itemIndex = (Mmanager.itemIndex + 15) % 4 + Mmanager.itemIndex / 4 * 4;
					else if (KeyDown(VK_DOWN)) // 아이템 하단 이동
						Mmanager.itemIndex = (Mmanager.itemIndex + 1) % 4 + Mmanager.itemIndex / 4 * 4;
					else if (KeyDown(VK_LEFT)) // 아이템 왼쪽 이동					
						Mmanager.itemIndex = (Mmanager.itemIndex + 12) % 16;
					else if (KeyDown(VK_RIGHT)) // 아이템 오른쪽 이동
						Mmanager.itemIndex = (Mmanager.itemIndex + 4) % 16;
					else if (KeyDown(VK_SPACE) || KeyDown(VK_ESCAPE))
						Mmanager.itemIndex = 16; // 아이템 선택창 종료
					else if (KeyDown('1')) { // 장비 장착
						switch (Mmanager.equTypeIndex)
						{
						case 0:
							if (itemInfo.itemBow[Mmanager.itemIndex] > 0) // 해당 아이템 보유하고 있으면
								sql.setItemUse(Mmanager.itemIndex, Mmanager.equTypeIndex); // 데이터베이스 변경
							break;
						case 1:
							if (itemInfo.itemCap[Mmanager.itemIndex] > 0) // 해당 아이템 보유하고 있으면
								sql.setItemUse(Mmanager.itemIndex, Mmanager.equTypeIndex); // 데이터베이스 변경
							break;
						case 2:
							if (itemInfo.itemArmor[Mmanager.itemIndex] > 0) // 해당 아이템 보유하고 있으면
								sql.setItemUse(Mmanager.itemIndex, Mmanager.equTypeIndex); // 데이터베이스 변경
							break;
						case 3:
							if (itemInfo.itemShoes[Mmanager.itemIndex] > 0) // 해당 아이템 보유하고 있으면
								sql.setItemUse(Mmanager.itemIndex, Mmanager.equTypeIndex); // 데이터베이스 변경
							break;
						}
					}
					else if (KeyDown('2')) { // 강화

					}
					else if (KeyDown('3')) { // 합성
						if (Mmanager.itemIndex % 4 != 3) { // 전설 아이템 제외
							switch (Mmanager.equTypeIndex)
							{
							case 0:
								if (itemInfo.itemBow[Mmanager.itemIndex] > 9) // 보유하고 있으면
								{
									itemInfo.itemBow[Mmanager.itemIndex] -= 10;
									itemInfo.itemBow[Mmanager.itemIndex + 1] += 1;
									sql.FusionItem(Mmanager.itemIndex, Mmanager.equTypeIndex); // 개수 변경
									if (itemInfo.itemBow[Mmanager.itemIndex] == 0 && itemInfo.itemUse[Mmanager.equTypeIndex] == Mmanager.itemIndex)
										sql.setItemUse(Mmanager.itemIndex + 1, Mmanager.equTypeIndex); // 착용아이템 변경
								}
								break;
							case 1:
								if (itemInfo.itemCap[Mmanager.itemIndex] > 9) // 보유하고 있으면
								{
									itemInfo.itemCap[Mmanager.itemIndex] -= 10;
									itemInfo.itemCap[Mmanager.itemIndex + 1] += 1;
									sql.FusionItem(Mmanager.itemIndex, Mmanager.equTypeIndex); // 개수 변경
									if (itemInfo.itemCap[Mmanager.itemIndex] == 0 && itemInfo.itemUse[Mmanager.equTypeIndex] == Mmanager.itemIndex)
										sql.setItemUse(Mmanager.itemIndex + 1, Mmanager.equTypeIndex); // 착용아이템 변경
								}
								break;
							case 2:
								if (itemInfo.itemArmor[Mmanager.itemIndex] > 9) // 보유하고 있으면
								{
									itemInfo.itemArmor[Mmanager.itemIndex] -= 10;
									itemInfo.itemArmor[Mmanager.itemIndex + 1] += 1;
									sql.FusionItem(Mmanager.itemIndex, Mmanager.equTypeIndex); // 개수 변경
									if (itemInfo.itemArmor[Mmanager.itemIndex] == 0 && itemInfo.itemUse[Mmanager.equTypeIndex] == Mmanager.itemIndex)
										sql.setItemUse(Mmanager.itemIndex + 1, Mmanager.equTypeIndex); // 착용아이템 변경
								}
								break;
							case 3:
								if (itemInfo.itemShoes[Mmanager.itemIndex] > 9) // 보유하고 있으면
								{
									itemInfo.itemShoes[Mmanager.itemIndex] -= 10;
									itemInfo.itemShoes[Mmanager.itemIndex + 1] += 1;
									sql.FusionItem(Mmanager.itemIndex, Mmanager.equTypeIndex); // 개수 변경
									if (itemInfo.itemShoes[Mmanager.itemIndex] == 0 && itemInfo.itemUse[Mmanager.equTypeIndex] == Mmanager.itemIndex)
										sql.setItemUse(Mmanager.itemIndex + 1, Mmanager.equTypeIndex); // 착용아이템 변경
								}
								break;
							}
						}
					}
				}
				else {
					if (KeyDown(VK_SPACE) || KeyDown(VK_RETURN)) { // 타입 선택
						EffectPlay(sound.BUTTONCLICK);
						Mmanager.itemIndex = 0; // 아이템 창으로 이동
					}
					else if (KeyDown(VK_LEFT)) // 아이템 타입 좌측 이동					
						Mmanager.equTypeIndex = (Mmanager.equTypeIndex + 3) % 4;
					else if (KeyDown(VK_RIGHT)) // 아이템 타입 우측 이동
						Mmanager.equTypeIndex = (Mmanager.equTypeIndex + 1) % 4;
					else if (KeyDown(VK_ESCAPE))
						Mmanager.equTypeIndex = 4; // 아이템 타입선택창 종료, 메뉴창으로 이동					
				}
			}			
			KeyTime = GetTickCount64();
		}
	}
	/* 게임 키입력 */
	if (g_Mng.n_Chap == GAME)
	{

	}
}