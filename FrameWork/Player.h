#pragma once
#include "Include.h"

class Player : public Character {
public:
	// ���� ������ ����
	int PlayLevel; // ������ ����
	int PlayMaxLevel; // ������ �ִ뷹��
	int PlayExp; // ������ ����ġ
	int PlayMaxExp; // ������ �ִ����ġ
	int PlayGold; // ������ ��Ȯ���

	bool PlayJump; // ������ ����
	bool PlayJump2; // ������ 2������
	bool JumpUpDown; // ������ ��������

	double PlayHit; // ������ ���߷�
	double PlayMissPer; // ������ ȸ�Ƿ�
	double PlaySklSpeed; // ������ ��ų���ݼӵ�
	double PlaySklDelay; // ������ ��ų ��Ÿ��

	// �÷��̾ ������ Ư��
	double HitPer; // ���߷�
	double MissPer; // ȸ�Ƿ�
	double SklSpeed; // ��ų���ݼӵ�
	double SklDelay; // ��ų ��Ÿ��

	Player();
	~Player();

	void Init();
	void Update();
	void Draw();
	void LevelUp();
	void PlayLevelUp();
	void Reset();
};

extern Player player;