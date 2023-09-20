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
	RandomPer[idx] = rand() % 1000; // 10ȸ �̱��� ���� ���� ����
}

void ItemInfo::BuyItem(int idx, int type) {
	srand(time(NULL)); // �춧���� �ð� �ʱ�ȭ
	type == 0 ? RandomItem(idx) : RandomSelectItem(idx, type);
	sprintf_s(itemBoxNum[idx], "%02d", itemNum); // ������ �ڽ� ��ȣ ����
	itemBoxType[idx] = itemType;
	itemBoxUse = true;
	itemBoxTime = GetTickCount64(); // �̴� �ð� �ʱ�ȭ
}

void ItemInfo::RandomItem(int idx) {
	int per = RandomPer[idx];
	if (per < 860) // �Ϲ� ���
		itemLevel = 0;
	else if (860 <= per && per < 980) // ���� ���
		itemLevel = 1;
	else if (980 <= per && per < 995) // ���� ���
		itemLevel = 2;
	else if (995 <= per) // ���� ���
		itemLevel = 3;
	
	itemType = (per % 64) / 16; // ������ ����(����,���,����,�Ź�)
	itemNum = (per % 4 * 4) + itemLevel; // ������ ��ȣ(�߰��� ������ ��ȣ)
	sql.setItemCount();
}

void ItemInfo::RandomSelectItem(int idx, int type) {
	int per = RandomPer[idx];
	if (per < 870) // �Ϲ� ���
		itemLevel = 0;
	else if (870 <= per && per < 985) // ���� ���
		itemLevel = 1;
	else if (985 <= per && per < 997)// ���� ���
		itemLevel = 2;
	else if (997 <= per) // ���� ���
		itemLevel = 3;
	itemType = type - 1; // ������ ����(����,���,����,�Ź�)
	itemNum = (per % 4 * 4) + itemLevel; // ������ ��ȣ(�߰��� ������ ��ȣ)
	sql.setItemCount();
}

void ItemInfo::UpdateItem(int idx, int type) {
	switch (type)
	{
	case 0:
		switch (idx % 4)
		{
		case 0:
			sprintf_s(itemEquName, "�Ϲ� Ȱ%d", idx / 4 + 1);
			break;
		case 1:
			sprintf_s(itemEquName, "���� Ȱ%d", idx / 4 + 1);
			break;
		case 2:
			sprintf_s(itemEquName, "���� Ȱ%d", idx / 4 + 1);
			break;
		case 3:
			sprintf_s(itemEquName, "���� Ȱ%d", idx / 4 + 1);
			break;
		}
		sprintf_s(itemEquOption1, "(1) ���ݷ� + %d", (idx % 4 + 1)*3);
		sprintf_s(itemEquOption2, "(2) ���� - %d", (idx % 4 + 1) * 20);
		break;
	case 1:
		switch (idx % 4)
		{
		case 0:
			sprintf_s(itemEquName, "�Ϲ� ���%d", idx / 4 + 1);
			break;
		case 1:
			sprintf_s(itemEquName, "���� ���%d", idx / 4 + 1);
			break;
		case 2:
			sprintf_s(itemEquName, "���� ���%d", idx / 4 + 1);
			break;
		case 3:
			sprintf_s(itemEquName, "���� ���%d", idx / 4 + 1);
			break;
		}
		sprintf_s(itemEquOption1, "(1) �� - %d", (idx % 4 + 1) * 2);
		sprintf_s(itemEquOption2, "(2) ���߷� + %d", (idx % 4 + 1) * 4);
		break;
	case 2:
		switch (idx % 4)
		{
		case 0:
			sprintf_s(itemEquName, "�Ϲ� ����%d", idx / 4 + 1);
			break;
		case 1:
			sprintf_s(itemEquName, "���� ����%d", idx / 4 + 1);
			break;
		case 2:
			sprintf_s(itemEquName, "���� ����%d", idx / 4 + 1);
			break;
		case 3:
			sprintf_s(itemEquName, "���� ����%d", idx / 4 + 1);
			break;
		}
		sprintf_s(itemEquOption1, "(1) ���� + %d", (idx % 4 + 1) * 2);
		sprintf_s(itemEquOption2, "(2) ü�� + %d", (idx % 4 + 1) * 10);
		break;
	case 3:
		switch (idx % 4)
		{
		case 0:
			sprintf_s(itemEquName, "�Ϲ� �Ź�%d", idx / 4 + 1);
			break;
		case 1:
			sprintf_s(itemEquName, "���� �Ź�%d", idx / 4 + 1);
			break;
		case 2:
			sprintf_s(itemEquName, "���� �Ź�%d", idx / 4 + 1);
			break;
		case 3:
			sprintf_s(itemEquName, "���� �Ź�%d", idx / 4 + 1);
			break;
		}
		sprintf_s(itemEquOption1, "(1) �̼� + %d", idx % 4 + 1);
		sprintf_s(itemEquOption2, "(2) ���� + %d", (idx % 4 + 1) * 10);
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
			sprintf_s(itemSelectName, "�Ϲ� Ȱ%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 1:
			sprintf_s(itemSelectName, "���� Ȱ%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 2:
			sprintf_s(itemSelectName, "���� Ȱ%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 3:
			sprintf_s(itemSelectName, "���� Ȱ%d", Mmanager.itemIndex / 4 + 1);
			break;
		}
		sprintf_s(itemOption1, "(1) ���ݷ� + %d", (Mmanager.itemIndex % 4 + 1) * 3);
		sprintf_s(itemOption2, "(2) ���� - %d", (Mmanager.itemIndex % 4 + 1) * 20);
		break;
	case 1:
		switch (Mmanager.itemIndex % 4)
		{
		case 0:
			sprintf_s(itemSelectName, "�Ϲ� ���%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 1:
			sprintf_s(itemSelectName, "���� ���%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 2:
			sprintf_s(itemSelectName, "���� ���%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 3:
			sprintf_s(itemSelectName, "���� ���%d", Mmanager.itemIndex / 4 + 1);
			break;
		}
		sprintf_s(itemOption1, "(1) �� - %d", (Mmanager.itemIndex % 4 + 1) * 2);
		sprintf_s(itemOption2, "(2) ���߷� + %d", (Mmanager.itemIndex % 4 + 1) * 4);
		break;
	case 2:
		switch (Mmanager.itemIndex % 4)
		{
		case 0:
			sprintf_s(itemSelectName, "�Ϲ� ����%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 1:
			sprintf_s(itemSelectName, "���� ����%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 2:
			sprintf_s(itemSelectName, "���� ����%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 3:
			sprintf_s(itemSelectName, "���� ����%d", Mmanager.itemIndex / 4 + 1);
			break;
		}
		sprintf_s(itemOption1, "(1) ���� + %d", (Mmanager.itemIndex % 4 + 1) * 2);
		sprintf_s(itemOption2, "(2) ü�� + %d", (Mmanager.itemIndex % 4 + 1) * 10);
		break;
	case 3:
		switch (Mmanager.itemIndex % 4)
		{
		case 0:
			sprintf_s(itemSelectName, "�Ϲ� �Ź�%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 1:
			sprintf_s(itemSelectName, "���� �Ź�%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 2:
			sprintf_s(itemSelectName, "���� �Ź�%d", Mmanager.itemIndex / 4 + 1);
			break;
		case 3:
			sprintf_s(itemSelectName, "���� �Ź�%d", Mmanager.itemIndex / 4 + 1);
			break;
		}
		sprintf_s(itemOption1, "(1) �̼� + %d", Mmanager.itemIndex % 4 + 1);
		sprintf_s(itemOption2, "(2) ���� + %d", (Mmanager.itemIndex % 4 + 1) * 10);
		break;
	}
}
void ItemInfo::PlusOption() {	
	if (itemUse[0] != 16) // ���� ����
	{
		// ���ݷ�, ���ݼӵ� ����
		statInfo.plusAtk = (3 * (itemUse[0] % 4 + 1));
		statInfo.plusAtkSpeed = (20 * (itemUse[0] % 4 + 1));
	}
	else {
		statInfo.plusAtk = 0;
		statInfo.plusAtkSpeed = 0;
	}

	if (itemUse[1] != 16) // ��� ����
	{
		// ��ų ��Ÿ�� ����, ���߷� ����
		statInfo.plusSklDelay = (2.0 * (itemUse[1] % 4 + 1));
		statInfo.plusHitPer = (4 * (itemUse[1] % 4 + 1));
	}
	else {
		statInfo.plusSklDelay = 0;
		statInfo.plusHitPer = 0;
	}
	if (itemUse[2] != 16) // ���� ����
	{
		// ����, ü�� ����
		statInfo.plusDef = (2 * (itemUse[2] % 4 + 1));
		statInfo.plusHp = (10 * (itemUse[2] % 4 + 1));
	}
	else {
		statInfo.plusHp = 0;
		statInfo.plusHp = 0;
	}
	if (itemUse[3] != 16) // �Ź� ����
	{
		// �̵��ӵ�, ȸ���� ����
		statInfo.plusMoveSpeed = (1 * (itemUse[3] % 4 + 1));
		statInfo.plusMissPer = (10 * (itemUse[3] % 4 + 1));
	}
	else {
		statInfo.plusMoveSpeed = 0;
		statInfo.plusMissPer = 0;
	}
}

// ������ �̱� �� �׷��ִ� �Լ�
void ItemInfo::DrawItem(int idx) {
	switch (itemBoxType[idx])
	{
	case 0:
		itemBG[atoi(itemBoxNum[idx]) % 4].Render(SCREEN_WITH / 4 + 60 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 20 + (idx / 5) * 100, 0, 1, 1); // ������ �ڽ� ���
		itemBowImg[atoi(itemBoxNum[idx])].Render(SCREEN_WITH / 4 + 70 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 30 + (idx / 5) * 100, 0, 1, 1); // ������ �ڽ� ���
		dv_font.DrawString(itemBoxNum[idx], SCREEN_WITH / 4 + 95 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 100 + (idx / 5) * 100);
		break;
	case 1:
		itemBG[atoi(itemBoxNum[idx]) % 4].Render(SCREEN_WITH / 4 + 60 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 20 + (idx / 5) * 100, 0, 1, 1); // ������ �ڽ� ���
		itemCapImg[atoi(itemBoxNum[idx])].Render(SCREEN_WITH / 4 + 70 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 30 + (idx / 5) * 100, 0, 1, 1); // ������ �ڽ� ���
		dv_font.DrawString(itemBoxNum[idx], SCREEN_WITH / 4 + 95 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 100 + (idx / 5) * 100);
		break;
	case 2:
		itemBG[atoi(itemBoxNum[idx]) % 4].Render(SCREEN_WITH / 4 + 60 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 20 + (idx / 5) * 100, 0, 1, 1); // ������ �ڽ� ���
		itemArmorImg[atoi(itemBoxNum[idx])].Render(SCREEN_WITH / 4 + 70 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 30 + (idx / 5) * 100, 0, 1, 1); // ������ �ڽ� ���
		dv_font.DrawString(itemBoxNum[idx], SCREEN_WITH / 4 + 95 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 100 + (idx / 5) * 100);
		break;
	case 3:
		itemBG[atoi(itemBoxNum[idx]) % 4].Render(SCREEN_WITH / 4 + 60 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 20 + (idx / 5) * 100, 0, 1, 1); // ������ �ڽ� ���
		itemShoesImg[atoi(itemBoxNum[idx])].Render(SCREEN_WITH / 4 + 70 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 30 + (idx / 5) * 100, 0, 1, 1); // ������ �ڽ� ���
		dv_font.DrawString(itemBoxNum[idx], SCREEN_WITH / 4 + 95 + (idx % 5) * 100, SCREEN_HEIGHT / 2 - itemBox.imagesinfo.Height / 2 + 100 + (idx / 5) * 100);
		break;
	}
}

void ItemInfo::DrawItemInfo(int idx, int type) {
	dv_font.DrawStringItem("<������>", 755, 230);
	dv_font.DrawStringItem("[�̸�]", 720, 250);
	dv_font.DrawStringItem(itemEquName, 770, 250);
	dv_font.DrawStringItem("[�ɷ�]", 720, 270);
	dv_font.DrawStringItem(itemEquOption1, 720, 290);
	dv_font.DrawStringItem(itemEquOption2, 720, 310);


	dv_font.DrawStringItem("<������>", 755, 340);
	dv_font.DrawStringItem("[�̸�]", 720, 360);
	dv_font.DrawStringItem(itemSelectName, 770, 360);
	dv_font.DrawStringItem("[�ɷ�]", 720, 380);
	dv_font.DrawStringItem(itemOption1, 720, 400);
	dv_font.DrawStringItem(itemOption2, 720, 420);
}