#include "Include.h"

class MenuManager
{

public:
	MenuManager();
	~MenuManager();

	int btnIndex; // ��ư �ε���
	int shopIndex; // ����â �ε���(�̱⼱��)
	int shopSellCount; // ����â ���� ����(1, 10��)
	int equTypeIndex; // ���â Ÿ�� �ε���
	int itemIndex; // ������ �ε���
	int itemPerDelay; // ���� ������ ���� ������
	char itemCount[100]; // ���â�� ǥ���� ������ ī��Ʈ

	DWORD ItemTime; // ���� ������ ���� �ð�

	void Init();
};

extern MenuManager Mmanager;