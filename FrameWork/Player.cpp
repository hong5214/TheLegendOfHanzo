#include "Include.h"

Player player;

Player::Player(void) {
	// 캐릭터 고유 정보는 한번만 초기화
	Hp = 100; // 생명력
	Atk = 10; // 공격력
	Def = 10; // 방어력
	HitPer = 10; // 명중률
	MissPer = 5; // 회피률
	MoveSpeed = 3; // 이동속도
	AtkSpeed = 500; // 공격속도
	SklSpeed = AtkSpeed/2; // 공격속도	
	SklDelay = 10.0; // 스킬 쿨타임
}

Player::~Player() {
}

void Player::Init()
{
	Level = sql.level[sql.index]; // 플레이어 정보 업데이트
	MaxExp = Level * 30;
	Exp = sql.exp[sql.index]; // 플레이어 정보 업데이트
	Gold = sql.gold[sql.index]; // 플레이어 정보 업데이트
	statInfo.Init(); // 스탯 정보 초기화
	Reset(); // 초기화
}

void Player::Update()
{
	if (!Gmanager.m_Pause && Gmanager.m_PlayStart)
	{
		if (KeyDown(VK_MENU)) // 점프키 누르면
		{
			if (!PlayJump) { // 1단 점프중이 아닐 때
				PlayJump = !PlayJump; // 점프 시작
				Y -= 8;
				key.KeyTime = GetTickCount64();
			}
			else // 1단 점프일 때
			{
				if (GetTickCount64() - key.KeyTime > 150) // 1단 점프 후 딜레이주기
				{
					if (!PlayJump2) // 2단점프가 아닐 때
					{
						PlayJump2 = !PlayJump2; // 2단 점프 시작
						Y -= 15;
					}
					key.KeyTime = GetTickCount64();
				}
			}
		}

		if (PlayJump) // 점프 상태이면
		{
			if (!JumpUpDown) Y -= 8;
			else Y += 8;

			if (PlayJump2) // 2단점프 상태이면
			{
				if (Y <= 350)
					JumpUpDown = !JumpUpDown;
			}
			else { // 1단점프 상태이면
				if (Y <= 500)
					JumpUpDown = !JumpUpDown;
			}
			if (Y >= 600) { // 땅 착지하면			
				Y = 600;
				JumpUpDown = !JumpUpDown;
				PlayJump = !PlayJump; // 점프 끝
				PlayJump2 = false; // 2단 점프 끝
			}
		}
		if (KeyDown(VK_LEFT))
		{
			X = (X <= 0) ? X : X - PlayMoveSpeed;
			Pos = false;
		}

		if (KeyDown(VK_RIGHT))
		{
			X = (X >= SCREEN_WITH - 100) ? X : X + PlayMoveSpeed;
			Pos = true;
		}	

		if (KeyDown(VK_SHIFT) && !SklUse1 && PlaySklDelay == 0.0) {
			SkillPlay(sound.SKILL0); // 효과음 한번만 실행
			SklUse1 = !SklUse1;
			player.AttackTime = GetTickCount64();
		}
		if (SklUse1 && GetTickCount64() - AttackTime >= PlaySklSpeed)
		{
			for (int i = 0; i < Gmanager.M_MGR.GetMonsterCount(); i++) {
				Gmanager.M_MGR.GetMonster(i)->IsDamage = true;
				Gmanager.Damage(&player, Gmanager.M_MGR.GetMonster(i)); // 전체 공격
			}
			player.AttackTime = GetTickCount64();
		}

		if (GetTickCount64() - DamageTime > 1000 && IsDamage) // 1초동안 표시
		{
			IsDamage = !IsDamage;
			DamageTime = GetTickCount64();
		}
	}	
}

void Player::Draw()
{
	if (Gmanager.m_PlayStart) {
		Pos ? // 위치에 따라 좌우 이미지 출력
			imageInfo.PlayerImgR.Render(X, Y, 0, 0.7, 0.7) :
			imageInfo.PlayerImgL.Render(X, Y, 0, 0.7, 0.7);
		imageInfo.HpZeroImg.Render(X, Y, 0, 0.6, 0.5);
		imageInfo.HpFullImg.Render(X, Y, 0, 0.6 *(PlayHp / MaxHp), 0.5);
	}

	SetRect(&HpBox, X, Y - 20, X + 200, Y + 200);
	dv_font.Fonts->DrawTextA(NULL, PlayState, -1, &HpBox, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 50));

	if (IsDamage) // 데미지 입으면
	{
		SetRect(&DamageBox, X, Y - 40, X + 60, Y + 100);
		dv_font.Fonts->DrawTextA(NULL, AtkDamage, -1, &DamageBox, DT_CENTER, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	
	if (SklUse1) // 스킬
	{
		Pos ?
			imageInfo.SkillImgR.Render(X + 75, Y - 85, 0, 0.5, 0.5) :
			imageInfo.SkillImgL.Render(X - 250, Y - 85, 0, 0.5, 0.5);
	}
	if (!Gmanager.m_Pause) // 일시정지 아닐때만 키 작동
	{
		if (KeyDown(VK_CONTROL)) // 공격
		{
			Pos ?
				imageInfo.AttackImgR.Render(X + 50, Y+25, 0, 1, 1) :
				imageInfo.AttackImgL.Render(X - 50, Y+25, 0, 1, 1);
		}		
	}
}

void Player::LevelUp()
{
	while (Exp >= MaxExp) // 경험치가 초과되면
	{
		Level++;
		Exp -= MaxExp; // 경험치 감소
		MaxExp = Level * 30;
	} 
		
}

void Player::PlayLevelUp()
{
	while (PlayExp >= PlayMaxExp) // 경험치가 초과되면
	{
		switch (Gmanager.RandomIdx[Gmanager.BoxCount])
		{
		case 0:
			PlayAtk += 5;
			break;
		case 1:
			PlayDef += 5;
			break;
		case 2:
			PlayHp += 30; // 회복하면서
			MaxHp += 10; // 최대 체력 증가
			break;
		case 3:
			PlayHit += 3;
			break;
		case 4:
			PlayAtkSpeed -= 20;
			break;
		case 5:
			PlayMoveSpeed += 1;
			break;
		default:
			break;
		}
		PlayLevel++;
		PlayExp -= PlayMaxExp; // 경험치 감소
		PlayMaxExp = PlayLevel * 10; // 게임중 최대경험치 레벨에 따라 변경
		PlayHp += (MaxHp * 0.1); // 레벨업시 10%체력 회복
		if (MaxHp <= PlayHp) // 회복한 체력이 최대체력보다 많으면
			MaxHp = PlayHp; // 체력 조정	
		sprintf(PlayState, "%.lf", PlayHp); // 체력수치 갱신
	}	
}

void Player::Reset()
{
	// 화면 크기에 따라 하단 배치
	X = SCREEN_WITH / 2 - 20;
	Y = 600;

	// 캐릭터 플레이 정보는 새 게임 시작마다 초기화
	PlayLevel = 1; // 게임중 레벨
	PlayMaxLevel = 10; // 게임중 최대레벨
	PlayExp = 0; // 게임중 경험치
	PlayGold = 0; // 게임중 수확골드
	PlayMaxExp = PlayLevel * 15; // 게임중 최대경험치

	MaxHp = Hp + statInfo.plusHp;; // 게임중 최대 생명력(장비 수치 적용)
	PlayAtk = Atk + statInfo.plusAtk; // 게임중 공격력
	PlayDef = Def + statInfo.plusDef; // 게임중 방어력
	PlayHp = MaxHp; // 게임중 생명력
	PlayHit = HitPer + statInfo.plusHitPer; // 게임중 명중률
	PlayMoveSpeed = MoveSpeed + statInfo.plusMoveSpeed; // 게임중 이동속도
	PlayAtkSpeed = AtkSpeed - statInfo.plusAtkSpeed; // 게임중 공격속도
	PlaySklSpeed = PlayAtkSpeed / 2; // 게임중 스킬공격속도
	PlaySklDelay = SklDelay - statInfo.plusSklDelay; // 게임중 스킬 쿨타임
	PlayMissPer = MissPer + statInfo.plusMissPer; // 게임중 회피률

	PlayJump = false;
	PlayJump2 = false;
	JumpUpDown = false;
	RESET();
}