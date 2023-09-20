#pragma once
#include "Include.h"

class Player : public Character {
public:
	// 게임 진행중 정보
	int PlayLevel; // 게임중 레벨
	int PlayMaxLevel; // 게임중 최대레벨
	int PlayExp; // 게임중 경험치
	int PlayMaxExp; // 게임중 최대경험치
	int PlayGold; // 게임중 수확골드

	bool PlayJump; // 게임중 점프
	bool PlayJump2; // 게임중 2단점프
	bool JumpUpDown; // 게임중 점프방향

	double PlayHit; // 게임중 명중률
	double PlayMissPer; // 게임중 회피률
	double PlaySklSpeed; // 게임중 스킬공격속도
	double PlaySklDelay; // 게임중 스킬 쿨타임

	// 플레이어만 가지는 특성
	double HitPer; // 명중률
	double MissPer; // 회피률
	double SklSpeed; // 스킬공격속도
	double SklDelay; // 스킬 쿨타임

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