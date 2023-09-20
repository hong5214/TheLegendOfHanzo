#include "Include.h"

Monster::~Monster(void)
{
}

void Monster::Init()
{
	playerAtkEffectIndex = 0; // 플레이어 공격 이미지 인덱스
	Hp = 40; // 생명력
	Atk = 5; // 공격력	
	Def = 0; // 방어력
	AtkSpeed = 1000; // 공격속도
	MoveSpeed = 3; // 이동속도
	Reset();
}

void Monster::Update()
{
	if (X > player.X + 80) // 플레이어 위치에 따라 좌우 이미지 변경
	{
		X -= MoveSpeed;
		Pos = false; // 몬스터가 오른쪽에 있을 때		
	}
	else if (X <= player.X - 80) {
		X += MoveSpeed;
		Pos = true;		
	}

	if (KeyDown(VK_CONTROL) && GetTickCount64() - player.AttackTime >= player.PlayAtkSpeed) // 플레이어 공격시(한명 공격)
	{
		int test_atk = (player.X + (int)imageInfo.AttackImgR.imagesinfo.Width * 3 * (player.Pos ? 1 : -1)) * (player.Pos ? 1 : -1);
		if (player.X * (player.Pos ? 1 : -1) <= this->X * (player.Pos ? 1 : -1) && this->X * (player.Pos ? 1 : -1) <= test_atk ) // 몬스터 충돌 시
		{
			IsDamage = true;
			Gmanager.Damage(&player, this); // 플레이어 공격범위 내이면 데미지 입음
			player.AttackTime = GetTickCount64();
		}
	}
	if (this->X <= player.X + 80 && player.X - 80 <= this->X
		&& player.Y - 10 <= Y && Y <= player.Y + 10) {
		if (GetTickCount64() - AttackTime > PlayAtkSpeed) // 몬스터 공격시
		{
			Gmanager.Damage(this, &player);
			AttackTime = GetTickCount64();
		}
	}
	if (GetTickCount64() - DamageTime > 30 && IsDamage)
	{
		playerAtkEffectIndex++;
		if (playerAtkEffectIndex >= 26) { playerAtkEffectIndex = 0; IsDamage = false; }
		DamageTime = GetTickCount64();
	}
}

void Monster::Draw()
{
	if (Gmanager.m_PlayStart && Life) {
		Pos ?
			imageInfo.GenjiImgR.Render(X, Y, 0, 0.7, 0.7) :
			imageInfo.GenjiImgL.Render(X, Y, 0, 0.7, 0.7);
		imageInfo.HpZeroImg.Render(X, Y, 0, 0.6, 0.5);
		imageInfo.HpFullImg.Render(X, Y, 0, 0.6 * (PlayHp / MaxHp), 0.5);
	}

	if (IsDamage)
	{	
		SetRect(&DamageBox, X, Y-40, X + 60, Y + 100);
		dv_font.Fonts->DrawTextA(NULL, AtkDamage, -1, &DamageBox, DT_CENTER, D3DCOLOR_ARGB(255, 255, 0, 0));

		// 스킬 데미지 입을 때
		if (player.SklUse1)
		{
			if (playerAtkEffectIndex < 9)
				imageInfo.AtkEffectimg1[playerAtkEffectIndex].Render(X, Y, 0, 0.4, 0.4);
			else if (playerAtkEffectIndex > 18)
				imageInfo.AtkEffectimg1[playerAtkEffectIndex].Render(X + imageInfo.GenjiAtkImgR.imagesinfo.Width * 0.7 / 4, Y + imageInfo.GenjiAtkImgR.imagesinfo.Height * 0.7 / 4, 0, 0.4, 0.4);
			else
				imageInfo.AtkEffectimg1[playerAtkEffectIndex].Render(X + imageInfo.GenjiAtkImgR.imagesinfo.Width * 0.7 / 2, Y + imageInfo.GenjiAtkImgR.imagesinfo.Height * 0.7 / 2, 0, 0.4, 0.4);
		}		
		// 기본 공격 데미지 입을 때
		else {
			Pos ?
				imageInfo.AttackImgL.Render(X + 60, Y + imageInfo.GenjiImgR.imagesinfo.Height / 4, 0, 0.7, 0.7) : imageInfo.AttackImgR.Render(X - 20, Y + imageInfo.GenjiImgR.imagesinfo.Height / 4, 0, 0.7, 0.7);
		}
	}

	SetRect(&HpBox, X, Y-20, X + 200, Y + 200);
	dv_font.Fonts->DrawTextA(NULL, PlayState, -1, &HpBox, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 50));

	if (X <= player.X + 80 && player.X - 80 <= X
		&& player.Y - 10 <= Y && Y <= player.Y + 10) { // 공격범위일 때
		Pos ?
			imageInfo.GenjiAtkImgR.Render(X + 75, Y, 0, 0.2, 0.2)
			: imageInfo.GenjiAtkImgL.Render(X - 50, Y, 0, 0.2, 0.2);
	}
}

void Monster::Reset()
{
	// 화면 크기에 따라 하단 배치
	srand(time(NULL));
	X = rand() % 11 * 100; // 위치랜덤 생성
	Y = 600;

	Level = 0; // 몬스터 : 0~3(초급/고급/보스 몬스터)

	// 스테이지별 몬스터 정보
	MaxHp = Hp + 10 * map.m_Stage; // 생명력
	Exp = 2 * map.m_Stage; // 몬스터 : 몬스터 킬당 경험치
	Gold = 100 + 10 * map.m_Stage; // 몬스터 : 몬스터 킬당 골드
	PlayHp = MaxHp; // 게임중 생명력
	PlayAtk = Atk + 5 * map.m_Stage; // 게임중 공격력
	PlayDef = Def + 3 * map.m_Stage; // 게임중 방어력
	PlayMoveSpeed = MoveSpeed + map.m_Stage; // 게임중 이동속도
	PlayAtkSpeed = AtkSpeed - 30 * map.m_Stage; // 게임중 공격속도

	RESET(); // 캐릭터 기본정보 초기화	
}