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
	/* �α��� Ű�Է� */
	if (g_Mng.n_Chap == LOGO)
	{
	}
	/* �޴� Ű�Է� */
	if (g_Mng.n_Chap == MENU && !Gmanager.LoadingState)
	{
		if (GetTickCount64() - KeyTime > 100)
		{
			// ����, ��� �̿����� �ƴ� ��
			if (Mmanager.shopIndex == 5 && Mmanager.equTypeIndex == 4)
			{
				if (KeyDown(VK_UP)) { // �޴� ��� �̵�
					if (Mmanager.btnIndex > TOTALMENU)
						// �ٷ� �� ��ư���� �̵�
						Mmanager.btnIndex = Mmanager.btnIndex*2 - 12;
				}
				else if (KeyDown(VK_DOWN)) { // �޴� �ϴ� �̵�
					if (Mmanager.btnIndex < TOTALMENU)
					{
						Mmanager.btnIndex = Mmanager.btnIndex/2 + 6;
					}
				}
				else if (KeyDown(VK_LEFT)) { // �޴� ���� �̵�
					if (Mmanager.btnIndex < TOTALMENU) // ��� ��ư�̸�
						Mmanager.btnIndex = (Mmanager.btnIndex + (TOTALMENU - 1)) % TOTALMENU; // �������� �̵�
					else if(Mmanager.btnIndex != LOGOUT) // �α׾ƿ� ��ư�� �ƴϸ�
						Mmanager.btnIndex--; // �������� �̵�
					else
						Mmanager.btnIndex = EXIT; // �α׾ƿ���ư�̸� ���� ��ư���� �̵�
				}
				else if (KeyDown(VK_RIGHT)) // �޴� ���� �̵�
				{
					if (Mmanager.btnIndex < TOTALMENU) // ���� �̿����� �ƴϸ� ����
						Mmanager.btnIndex = (Mmanager.btnIndex + 1) % TOTALMENU;
					else if (Mmanager.btnIndex != EXIT) // ���� ��ư�� �ƴϸ�
						Mmanager.btnIndex++; // �������� �̵�
					else
						Mmanager.btnIndex = LOGOUT; // �����ư�̸� �α׾ƿ� ��ư���� �̵�
				}
				else if (KeyDown(VK_SPACE) || KeyDown(VK_RETURN)) // �޴� ����
				{
					EffectPlay(sound.BUTTONCLICK);
					switch (Mmanager.btnIndex) // �޴� ���ÿ� ���� ������ ����
					{
					case SHOP:
						Mmanager.shopIndex = 0; // ����â Ȱ��ȭ
						break;
					case EQU:
						Mmanager.equTypeIndex = 0; // ���â Ȱ��ȭ
						break;
					case SETTING: // ȸ�� Ż��
						sql.DeleteID();
						g_Mng.n_Chap = LOGO; // �α��� é�ͷ� �̵�
						Mmanager.btnIndex = 7; // �ٽ� �α��� ȭ�� ���� ���۹�ư����
						sound.BGChange("./resource/Sound/BGM_Lobby.mp3");
						Gmanager.LoadingState = true;
						break;
					case HOME: case QUEST: // �غ���
						break;
					case LOGOUT:
						g_Mng.n_Chap = LOGO; // �α��� é�ͷ� �̵�
						Mmanager.btnIndex = 7; // �ٽ� �α��� ȭ�� ���� ���۹�ư����
						sound.BGChange("./resource/Sound/BGM_Lobby.mp3");
						Gmanager.LoadingState = true;
						break;
					case START: // ���� ȭ������ �̵�
						Gmanager.m_PlayStart = true; // ���� ����
						player.Init(); // �÷��̾� ���� �ʱ�ȭ
						g_Mng.chap[GAME]->Init(); // ���� ���� �ʱ�ȭ
						map.m_Stage = 1; // �� �ʱ�ȭ
						g_Mng.n_Chap = GAME; // ���� é�ͷ� �̵�
						sound.BGChange("./resource/Sound/BGM_Game.mp3");
						break;
					case EXIT:
						PostQuitMessage(0); // ����
						break;
					}
				}
				else if (KeyDown(VK_ESCAPE)) // ���� ���� ��ư���� �̵�
				{
					Mmanager.btnIndex = 7;
				}
			}
			// ���� �̿����϶�
			else if (Mmanager.shopIndex != 5)
			{
				if (KeyDown(VK_UP)) // ���� ��� �̵�
					Mmanager.shopIndex = (Mmanager.shopIndex + 4) % 5;
				else if (KeyDown(VK_DOWN)) // ���� �ϴ� �̵�
					Mmanager.shopIndex = (Mmanager.shopIndex + 1) % 5;
				else if (KeyDown(VK_ESCAPE)) // �޴� ����
					Mmanager.shopIndex = 5;
				else if (KeyDown(VK_LEFT)) // ���� ���� �̵�
					Mmanager.shopSellCount = 0;
				else if (KeyDown(VK_RIGHT)) // ���� ������ �̵�
					Mmanager.shopSellCount = 1;
				else if (KeyDown(VK_SPACE) || KeyDown(VK_RETURN)) // ���� ����
				{
					EffectPlay(sound.BUTTONCLICK);
					if (Mmanager.shopSellCount == 0 && player.Gold >= 1000) // 1�� �̱�
					{
						itemInfo.BuyItem(0, Mmanager.shopIndex); // 1�� ����
						player.Gold -= 1000; // ��庯��
						sql.autoSave(); // DB����
					}
					else if (Mmanager.shopSellCount == 1 && player.Gold >= 10000) // 10�� �̱�
					{
						for (int i = 0; i < 10; i++) // 10�� �ݺ�
							itemInfo.BuyItem(i, Mmanager.shopIndex); // 1�� ����
						player.Gold -= 10000; // ��庯��
						sql.autoSave(); // DB����
					}
				}
			}
			// ��� �̿����϶�
			else if (Mmanager.equTypeIndex != 4)
			{
				if (Mmanager.itemIndex != 16) { // ������ ���ý�					
					if (KeyDown(VK_UP)) // ������ ��� �̵�
						Mmanager.itemIndex = (Mmanager.itemIndex + 15) % 4 + Mmanager.itemIndex / 4 * 4;
					else if (KeyDown(VK_DOWN)) // ������ �ϴ� �̵�
						Mmanager.itemIndex = (Mmanager.itemIndex + 1) % 4 + Mmanager.itemIndex / 4 * 4;
					else if (KeyDown(VK_LEFT)) // ������ ���� �̵�					
						Mmanager.itemIndex = (Mmanager.itemIndex + 12) % 16;
					else if (KeyDown(VK_RIGHT)) // ������ ������ �̵�
						Mmanager.itemIndex = (Mmanager.itemIndex + 4) % 16;
					else if (KeyDown(VK_SPACE) || KeyDown(VK_ESCAPE))
						Mmanager.itemIndex = 16; // ������ ����â ����
					else if (KeyDown('1')) { // ��� ����
						switch (Mmanager.equTypeIndex)
						{
						case 0:
							if (itemInfo.itemBow[Mmanager.itemIndex] > 0) // �ش� ������ �����ϰ� ������
								sql.setItemUse(Mmanager.itemIndex, Mmanager.equTypeIndex); // �����ͺ��̽� ����
							break;
						case 1:
							if (itemInfo.itemCap[Mmanager.itemIndex] > 0) // �ش� ������ �����ϰ� ������
								sql.setItemUse(Mmanager.itemIndex, Mmanager.equTypeIndex); // �����ͺ��̽� ����
							break;
						case 2:
							if (itemInfo.itemArmor[Mmanager.itemIndex] > 0) // �ش� ������ �����ϰ� ������
								sql.setItemUse(Mmanager.itemIndex, Mmanager.equTypeIndex); // �����ͺ��̽� ����
							break;
						case 3:
							if (itemInfo.itemShoes[Mmanager.itemIndex] > 0) // �ش� ������ �����ϰ� ������
								sql.setItemUse(Mmanager.itemIndex, Mmanager.equTypeIndex); // �����ͺ��̽� ����
							break;
						}
					}
					else if (KeyDown('2')) { // ��ȭ

					}
					else if (KeyDown('3')) { // �ռ�
						if (Mmanager.itemIndex % 4 != 3) { // ���� ������ ����
							switch (Mmanager.equTypeIndex)
							{
							case 0:
								if (itemInfo.itemBow[Mmanager.itemIndex] > 9) // �����ϰ� ������
								{
									itemInfo.itemBow[Mmanager.itemIndex] -= 10;
									itemInfo.itemBow[Mmanager.itemIndex + 1] += 1;
									sql.FusionItem(Mmanager.itemIndex, Mmanager.equTypeIndex); // ���� ����
									if (itemInfo.itemBow[Mmanager.itemIndex] == 0 && itemInfo.itemUse[Mmanager.equTypeIndex] == Mmanager.itemIndex)
										sql.setItemUse(Mmanager.itemIndex + 1, Mmanager.equTypeIndex); // ��������� ����
								}
								break;
							case 1:
								if (itemInfo.itemCap[Mmanager.itemIndex] > 9) // �����ϰ� ������
								{
									itemInfo.itemCap[Mmanager.itemIndex] -= 10;
									itemInfo.itemCap[Mmanager.itemIndex + 1] += 1;
									sql.FusionItem(Mmanager.itemIndex, Mmanager.equTypeIndex); // ���� ����
									if (itemInfo.itemCap[Mmanager.itemIndex] == 0 && itemInfo.itemUse[Mmanager.equTypeIndex] == Mmanager.itemIndex)
										sql.setItemUse(Mmanager.itemIndex + 1, Mmanager.equTypeIndex); // ��������� ����
								}
								break;
							case 2:
								if (itemInfo.itemArmor[Mmanager.itemIndex] > 9) // �����ϰ� ������
								{
									itemInfo.itemArmor[Mmanager.itemIndex] -= 10;
									itemInfo.itemArmor[Mmanager.itemIndex + 1] += 1;
									sql.FusionItem(Mmanager.itemIndex, Mmanager.equTypeIndex); // ���� ����
									if (itemInfo.itemArmor[Mmanager.itemIndex] == 0 && itemInfo.itemUse[Mmanager.equTypeIndex] == Mmanager.itemIndex)
										sql.setItemUse(Mmanager.itemIndex + 1, Mmanager.equTypeIndex); // ��������� ����
								}
								break;
							case 3:
								if (itemInfo.itemShoes[Mmanager.itemIndex] > 9) // �����ϰ� ������
								{
									itemInfo.itemShoes[Mmanager.itemIndex] -= 10;
									itemInfo.itemShoes[Mmanager.itemIndex + 1] += 1;
									sql.FusionItem(Mmanager.itemIndex, Mmanager.equTypeIndex); // ���� ����
									if (itemInfo.itemShoes[Mmanager.itemIndex] == 0 && itemInfo.itemUse[Mmanager.equTypeIndex] == Mmanager.itemIndex)
										sql.setItemUse(Mmanager.itemIndex + 1, Mmanager.equTypeIndex); // ��������� ����
								}
								break;
							}
						}
					}
				}
				else {
					if (KeyDown(VK_SPACE) || KeyDown(VK_RETURN)) { // Ÿ�� ����
						EffectPlay(sound.BUTTONCLICK);
						Mmanager.itemIndex = 0; // ������ â���� �̵�
					}
					else if (KeyDown(VK_LEFT)) // ������ Ÿ�� ���� �̵�					
						Mmanager.equTypeIndex = (Mmanager.equTypeIndex + 3) % 4;
					else if (KeyDown(VK_RIGHT)) // ������ Ÿ�� ���� �̵�
						Mmanager.equTypeIndex = (Mmanager.equTypeIndex + 1) % 4;
					else if (KeyDown(VK_ESCAPE))
						Mmanager.equTypeIndex = 4; // ������ Ÿ�Լ���â ����, �޴�â���� �̵�					
				}
			}			
			KeyTime = GetTickCount64();
		}
	}
	/* ���� Ű�Է� */
	if (g_Mng.n_Chap == GAME)
	{

	}
}