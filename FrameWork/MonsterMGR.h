#include "Include.h"

class MonsterMGR // ���� ������ �迭�� ���� ��ü ������ ���� �Ŵ���
{	
	Container<Monster*> monsterboss;  // ���� �ε��� ���� ��ü
public:
	enum { INSERT = 0, // ���� ����
		REMOVE, // ���� ����
		};	
	void Insert_Monster();
	void Remove_Monster(int idx);
	void Reset_Monster();
	void Draw_Monster(int idx);
	void Update_Monster(int idx);
	int GetMonsterCount(); // ��ȯ�� ���� �� ����
	Monster* GetMonster(int idx); // �ش� �ε����� ���� ��ü�� ��ȯ
};