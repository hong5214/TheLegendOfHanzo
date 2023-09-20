#pragma once
#include "Include.h"
// �⺻��, ��Ʈ, ��������Ʈ(�̹���), é�� ���� ���� �������

class Monster : public Character
{
public:
	// ���͸� ������ Ư��
	int index; // ���� �ε���
	int playerAtkEffectIndex; // �÷��̾� ���� �̹��� �ε���

	Monster() {	}
	Monster(int idx) { index = idx; }
	~Monster(void);

	void Init();
	void Draw();
	void Update();
	void Reset();
	void Damage() {} // �̱���
};