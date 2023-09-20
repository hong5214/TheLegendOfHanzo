#pragma once
#include "Include.h"

class GameManager
{
public:
	GameManager(void); // ������
	~GameManager(void); // �Ҹ���

	bool LoadingState; // �α��� ����� �϶� true
	bool NewId; // ���ο� ���̵��϶�
	bool m_Pause; // �Ͻ����� �϶� true
	bool m_PlayStart; // ���� ȭ�� �϶� true
	int m_GameSpeed; // ���� �ӵ�
	
	// ���� ����
	int monsterCount; // ���� ��ȯ�� ���� ��
	int monsterKillCount; // ���� ����� ���� ��
	int monsterMaxCount; // �̹� �������� ���� �ִ� ��
	int BoxCount; // ������ ������ �ڽ�
	int RandomIdx[3]; // ���� �̹����� ����� �ɷ�

	MonsterMGR M_MGR; // ���� �Ŵ��� ����
	
	DWORD AlphaTime; // ĳ���� �����ð�
	DWORD GameTime; // ���� �÷��� �ð�
	DWORD CheckSecTime; // 1�� üũ�ϱ�

	// ���� �Լ�
	void Init(); // �ʱ�ȭ
	void Update(); // ������Ʈ
	void Draw(); // �׸���

	// �߰� �Լ�
	void GameReset(void);
	void Damage(Player* atk, Monster* atked); // ���� ���� ����
	void Damage(Monster* atk, Player* atked); // �÷��̾� ���� ����
	void Attacked(Player* atk, Monster* atked); // ���� ���ݽ�
	void Attacked(Monster* atk, Player* atked); // ���Ϳ��� Ÿ�ݽ�
	void NextStage();
	void CreateMonster();
	void RandomSelect(int idx);
};

extern GameManager Gmanager;