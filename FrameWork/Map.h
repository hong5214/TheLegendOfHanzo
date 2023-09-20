#pragma once
#include "Include.h"

class Map
{

public :
	Map();
	~Map();

	// 게임 화면에 표시할 문자열
	char stageNum[100]; // 현재 스테이지
	char monsterCount[256]; // 몬스터 남은 수
	char skillDelay[256]; // 스킬 에너지

	
	// 스테이지별 맵, 효과 이미지
	Sprite m_MapStage1;
	Sprite m_MapStage1Effect;

	// 현재 스테이지
	int m_Stage;
	int MaxStage;

	void Init();
	void Update(double frame);
	void Draw();
};

extern Map map;