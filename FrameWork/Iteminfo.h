#include "Include.h"
class ItemInfo
{
public:
	ItemInfo() {		
		// ���� ������ ����
		itemLevel = 0;
		itemType = 0;
		itemNum = 0;
		itemMode = 3;
		itemBoxUse = false;
		itemBoxTime = GetTickCount64();
		for (int i = 0; i < 10; i++) {
			RandomPerSet(i); // ���� Ȯ�� �ʱ�ȭ
			sprintf_s(itemBoxNum[i], "%02d", itemNum); // �ڽ� ��ȣ �ʱ�ȭ
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
	char itemBoxNum[10][256]; // �ڽ� ��ȣ
	int itemBoxType[10]; // �ڽ� ������ ����

	bool itemBoxUse; // ������ ���� ��
	int RandomPer[10]; // 10ȸ�̱⿡ ����� ���� ����
	DWORD itemBoxTime;

	int itemBow[16]; // ���� ������ ��
	int itemCap[16]; // ��� ������ ��
	int itemArmor[16]; // ���� ������ ��
	int itemShoes[16]; // �Ź� ������ ��
	int itemUse[4]; // ��������
	char itemEquName[256]; // ������ ���� ����
	char itemEquOption1[100]; // ������ �����ɼ�1
	char itemEquOption2[100]; // ������ �����ɼ�2
	char itemSelectName[256]; // ������ ����
	char itemOption1[100]; // ������ �ɼ�1
	char itemOption2[100]; // ������ �ɼ�2
	int itemMode; // 0 : ����/����, 1 : ��ȭ, 2 : �ռ�, 3 : �̼���

	// ���� ������ ����
	int itemNum; // ������ ��ȣ(0, 1, 2, 3)
	int itemType; // ������ ����(����, ���, ����, �Ź�)
	int itemLevel; // ������ ���(�Ϲ�, ����, ����, ����)	
	
	void RandomPerSet(int idx);
	void BuyItem(int idx, int type); // ������ ����
	void RandomItem(int idx); // ���� �̱�
	void RandomSelectItem(int idx, int type); // ���� �̱�
	void UpdateItem(int idx, int type); // ������ ��� ����
	void SelectItem(); // ������ ��� ����
	void PlusOption();
	void DrawItem(int idx); // ������ �̱� �� �׷��ִ� �Լ�
	void DrawItemInfo(int idx, int type); // ������ ���� �� ������ �׷��ִ� �Լ�
};

extern ItemInfo itemInfo;