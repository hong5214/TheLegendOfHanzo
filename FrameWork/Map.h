#pragma once
#include "Include.h"

class Map
{

public :
	Map();
	~Map();

	// ���� ȭ�鿡 ǥ���� ���ڿ�
	char stageNum[100]; // ���� ��������
	char monsterCount[256]; // ���� ���� ��
	char skillDelay[256]; // ��ų ������

	
	// ���������� ��, ȿ�� �̹���
	Sprite m_MapStage1;
	Sprite m_MapStage1Effect;

	// ���� ��������
	int m_Stage;
	int MaxStage;

	void Init();
	void Update(double frame);
	void Draw();
};

extern Map map;