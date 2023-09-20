#pragma once
#include "Include.h"

class GameManager
{
public:
	GameManager(void); // 생성자
	~GameManager(void); // 소멸자

	bool LoadingState; // 로그인 대기중 일때 true
	bool NewId; // 새로운 아이디일때
	bool m_Pause; // 일시정지 일때 true
	bool m_PlayStart; // 게임 화면 일때 true
	int m_GameSpeed; // 게임 속도
	
	// 몬스터 정보
	int monsterCount; // 현재 소환된 몬스터 수
	int monsterKillCount; // 현재 사냥한 몬스터 수
	int monsterMaxCount; // 이번 스테이지 몬스터 최대 수
	int BoxCount; // 선택할 아이템 박스
	int RandomIdx[3]; // 랜덤 이미지에 저장된 능력

	MonsterMGR M_MGR; // 몬스터 매니저 생성
	
	DWORD AlphaTime; // 캐릭터 생성시간
	DWORD GameTime; // 게임 플레이 시간
	DWORD CheckSecTime; // 1초 체크하기

	// 기초 함수
	void Init(); // 초기화
	void Update(); // 업데이트
	void Draw(); // 그리기

	// 추가 함수
	void GameReset(void);
	void Damage(Player* atk, Monster* atked); // 몬스터 공격 판정
	void Damage(Monster* atk, Player* atked); // 플레이어 공격 판정
	void Attacked(Player* atk, Monster* atked); // 몬스터 공격시
	void Attacked(Monster* atk, Player* atked); // 몬스터에게 타격시
	void NextStage();
	void CreateMonster();
	void RandomSelect(int idx);
};

extern GameManager Gmanager;