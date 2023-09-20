#pragma once
#include "Include.h"

class Character
{
public:
	Character() {};
	~Character() {};

	// 캐릭터 기본 필수 정보
	bool Life; // true : 생존, false : 죽음
	bool Pos; // 이동 방향 (true : 오른쪽, false : 왼쪽)
	bool IsDamage; // 데미지 입음 유무
	bool SklUse1; // 스킬 사용 유무

	// 캐릭터/몬스터별 정보
	int Level; // 플레이어 : 레벨, 몬스터 : 0~3(초급/고급/보스 몬스터)
	int Exp; // 플레이어 : 보유 경험치, 몬스터 : 몬스터 킬당 경험치
	int MaxExp; // 플레이어 : 최대 경험치, 몬스터 : 미적용
	int Gold; // 플레이어 : 보유 골드, 몬스터 : 몬스터 킬당 골드
	int Item; // 플레이어 : 아이템 드랍 확률, 몬스터 : 고급 아이템 드랍 확률
	double X, Y; // 현재 위치
	
	// 스탯 정보
	double Hp; // 생명력
	double MaxHp; // 최대 생명력
	double Atk; // 공격력
	double Def; // 방어력
	double AtkSpeed; // 기본공격속도
	double MoveSpeed; // 이동속도

	double PlayHp; // 게임중 생명력
	double PlayAtk; // 게임중 공격력
	double PlayDef; // 게임중 방어력
	double PlayAtkSpeed; // 게임중 공격속도
	double PlayMoveSpeed; // 게임중 이동속도

	char PlayState[100]; // 플레이어 상태
	char AtkDamage[100]; // 데미지

	RECT HpBox; // 현재 체력 표시영역
	RECT DamageBox; // 데미지 표시영역

	DWORD DamageTime; // 데미지 유효 시간
	DWORD AttackTime; // 공격 시간

	void RESET() {
		Life = true; // true : 생존, false : 죽음
		Pos = true; // 이동 방향 (true : right, false : left)
		IsDamage = false;
		SklUse1 = false;
		DamageTime = GetTickCount64(); // 데미지 받지 않은 시간 체크
		AttackTime = GetTickCount64(); // 공격 시간 체크
		sprintf(PlayState, "%.lf", PlayHp); // 현재 체력 초기화
	}
};