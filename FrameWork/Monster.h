#pragma once
#include "Include.h"
// 기본값, 폰트, 스프라이트(이미지), 챕터 지정 관련 헤더파일

class Monster : public Character
{
public:
	// 몬스터만 가지는 특성
	int index; // 몬스터 인덱스
	int playerAtkEffectIndex; // 플레이어 공격 이미지 인덱스

	Monster() {	}
	Monster(int idx) { index = idx; }
	~Monster(void);

	void Init();
	void Draw();
	void Update();
	void Reset();
	void Damage() {} // 미구현
};