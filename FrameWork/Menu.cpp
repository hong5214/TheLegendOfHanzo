#include "Include.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::Init()
{
	Mmanager.Init(); // �޴� ���� �ʱ�ȭ
	imageInfo.Init(); // ����� �̹����� �ʱ�ȭ
}

// Chap, ������ �Լ� ȣ��
void Menu::Update(double frame)
{
	if (GetTickCount64() - Mmanager.ItemTime > rand() % Mmanager.itemPerDelay) // ������ �̱� Ȯ�� ���� ����
	{
		Mmanager.itemPerDelay = rand() % 1000 + 1; // ������ �ð��� �������� ����
		itemInfo.RandomPerSet((Mmanager.itemPerDelay - 1) % 10); // 10ȸ �̱��� ���� ���� ����
		Mmanager.ItemTime = GetTickCount64();
	}
	if (!itemInfo.itemBoxUse && !Gmanager.LoadingState) {
		key.Update(); // Ű �Է� �ޱ�
		statInfo.Update(); // ���� ���� �ʱ�ȭ
		if (Mmanager.itemIndex != 16) // ������ ����â ����
		{
			// �����ϰ��ִ� ������� ����
			if (itemInfo.itemUse[Mmanager.equTypeIndex] != 16) // �������̸�
				itemInfo.UpdateItem(itemInfo.itemUse[Mmanager.equTypeIndex] % 16, Mmanager.equTypeIndex);
			else
			{
				sprintf_s(itemInfo.itemEquName, "����");
				sprintf_s(itemInfo.itemEquOption1, "(1) ����");
				sprintf_s(itemInfo.itemEquOption2, "(2) ����");
			}			
			
			// ������ ������ ������� ����
			itemInfo.SelectItem();
		}
	}	
}

void Menu::Draw()
{	
	statInfo.Draw(); // ���� ���� ǥ��(����, ����ġ, ���)
	if (true) // ���� ���̱� ������ ���� ���
	{
		statInfo.ShowStat();
	}

	switch (Mmanager.btnIndex) // ��ư�� ���� �޴� ��� �̹��� �� ȿ�� ����
	{
	case SHOP:
		imageInfo.menuImg[0].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //�̹������
		dv_font.DrawString("����", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280, 645, 0, 0.2, 0.2);
		break;
	case EQU:
		if (Mmanager.equTypeIndex != 4)
			imageInfo.itemTypeImg[Mmanager.equTypeIndex].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //�̹������		
		else
			imageInfo.menuImg[1].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //�̹������
		dv_font.DrawString("���", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280 + (115* Mmanager.btnIndex), 645, 0, 0.2, 0.2);
		break;
	case HOME:
		imageInfo.menuImg[2].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //�̹������
		dv_font.DrawString("�κ�", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280 + (115* Mmanager.btnIndex), 645, 0, 0.2, 0.2);
		break;
	case QUEST:
		imageInfo.menuImg[3].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //�̹������
		dv_font.DrawString("����Ʈ", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280 + (115* Mmanager.btnIndex), 645, 0, 0.2, 0.2);
		break;
	case SETTING:
		imageInfo.menuImg[4].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //�̹������
		dv_font.DrawString("����", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280 + (115* Mmanager.btnIndex), 645, 0, 0.2, 0.2);
		break;
	case LOGOUT:
		imageInfo.menuImg[2].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //�̹������
		dv_font.DrawString("�α׾ƿ�", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 280, 680, 0, 0.2, 0.2);
		break;
	case START:
		imageInfo.menuImg[2].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //�̹������
		dv_font.DrawString("����", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith - 50, 680, 0, 0.2, 0.2);
		break;
	case EXIT:
		imageInfo.menuImg[2].Render(SCREEN_WITH / 4, 0, 0, 1, 1); //�̹������
		dv_font.DrawString("����", 0, 0);
		imageInfo.bt_menuBorder.Render(imageInfo.centerWith + 180, 680, 0, 0.2, 0.2);
		break;
	}
	
	// ��ư ǥ��
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
	else if (Mmanager.shopIndex != 5) // ���� �̿��
	{
		if (true)
			imageInfo.HelpShop.Render(SCREEN_WITH - imageInfo.HelpLogo.imagesinfo.Width, 200, 0, 1, 1);
		imageInfo.bt_shopBorder.Render(imageInfo.centerWith + 72 + Mmanager.shopSellCount * 72, 67 + Mmanager.shopIndex * 90, 0, 1, 1);
		imageInfo.bt_shopSelect.Render(imageInfo.centerWith + 210, 70 + Mmanager.shopIndex * 90, 0, 1, 1);
		// ������ �̱� ���
		if (GetTickCount64() - itemInfo.itemBoxTime <= 1000 && itemInfo.itemBoxUse)
		{
			itemInfo.itemBox.Render(SCREEN_WITH / 4, SCREEN_HEIGHT / 2 - itemInfo.itemBox.imagesinfo.Height / 2, 0, 1, 1); // ������ �ڽ� ���
			if (Mmanager.shopSellCount == 0) // 1�� �̱�� 1��° ������ �����۸� �׷��ֱ�
				itemInfo.DrawItem(0);
			else
				for (int i = 0; i < 10; i++) // 10�� �̱�� 10�� ������ �׷��ֱ�
					itemInfo.DrawItem(i);
		}
		else
			itemInfo.itemBoxUse = false;
	}
	else if (Mmanager.equTypeIndex != 4) { // ��� �̿��		
		if (true)
			imageInfo.HelpItem.Render(SCREEN_WITH - imageInfo.HelpLogo.imagesinfo.Width, 200, 0, 1, 1);
		imageInfo.bt_itemTypeSelect.Render(imageInfo.centerWith - 235 + 124 * Mmanager.equTypeIndex, 70, 0, 1, 1); // ��� Ÿ�� ����
		itemInfo.equBox.Render(SCREEN_WITH / 4, SCREEN_HEIGHT / 2 + 180, 0, 1, 1);
		for (int i = 0; i < 4; i++) {
			if (itemInfo.itemUse[i] != 16) // �������� ���������� �׷��ֱ�
			{
				itemInfo.itemBG[itemInfo.itemUse[i] % 4].Render(imageInfo.centerWith - 226 + 124 * i, SCREEN_HEIGHT / 2 + 190, 0, 1, 1); // ��� Ÿ��				
				switch (i)
				{
					case 0:
						itemInfo.itemBowImg[itemInfo.itemUse[i] % 16].Render(imageInfo.centerWith - 216 + 124 * i, SCREEN_HEIGHT / 2 + 200, 0, 1, 1); // ��� �̹���				
						break;
					case 1:
						itemInfo.itemCapImg[itemInfo.itemUse[i] % 16].Render(imageInfo.centerWith - 216 + 124 * i, SCREEN_HEIGHT / 2 + 200, 0, 1, 1); // ��� �̹���
						break;
					case 2:
						itemInfo.itemArmorImg[itemInfo.itemUse[i] % 16].Render(imageInfo.centerWith - 216 + 124 * i, SCREEN_HEIGHT / 2 + 200, 0, 1, 1); // ��� �̹���
						break;
					case 3:
						itemInfo.itemShoesImg[itemInfo.itemUse[i] % 16].Render(imageInfo.centerWith - 216 + 124 * i, SCREEN_HEIGHT / 2 + 200, 0, 1, 1); // ��� �̹���
						break;
				}
			}
			else
			{
				itemInfo.itemBG[0].Render(imageInfo.centerWith - 226 + 124 * i, SCREEN_HEIGHT / 2 + 190, 0, 1, 1); // ��� Ÿ�Ծ�� �Ϲ�
				itemInfo.itemEmpty.Render(imageInfo.centerWith - 226 + 124 * i, SCREEN_HEIGHT / 2 + 190, 0, 1, 1); // �� �̹���				
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
		if (Mmanager.itemIndex != 16) // ������ ���ý�
		{
			imageInfo.bt_itemSelect.Render(imageInfo.centerWith - 245 + 82 * (Mmanager.itemIndex / 4), 188 + 84 * (Mmanager.itemIndex % 4), 0, 1.4, 1);
			itemInfo.DrawItemInfo(Mmanager.itemIndex, Mmanager.equTypeIndex);
		}
	}	
}