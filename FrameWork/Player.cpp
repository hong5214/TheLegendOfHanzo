#include "Include.h"

Player player;

Player::Player(void) {
	// ĳ���� ���� ������ �ѹ��� �ʱ�ȭ
	Hp = 100; // �����
	Atk = 10; // ���ݷ�
	Def = 10; // ����
	HitPer = 10; // ���߷�
	MissPer = 5; // ȸ�Ƿ�
	MoveSpeed = 3; // �̵��ӵ�
	AtkSpeed = 500; // ���ݼӵ�
	SklSpeed = AtkSpeed/2; // ���ݼӵ�	
	SklDelay = 10.0; // ��ų ��Ÿ��
}

Player::~Player() {
}

void Player::Init()
{
	Level = sql.level[sql.index]; // �÷��̾� ���� ������Ʈ
	MaxExp = Level * 30;
	Exp = sql.exp[sql.index]; // �÷��̾� ���� ������Ʈ
	Gold = sql.gold[sql.index]; // �÷��̾� ���� ������Ʈ
	statInfo.Init(); // ���� ���� �ʱ�ȭ
	Reset(); // �ʱ�ȭ
}

void Player::Update()
{
	if (!Gmanager.m_Pause && Gmanager.m_PlayStart)
	{
		if (KeyDown(VK_MENU)) // ����Ű ������
		{
			if (!PlayJump) { // 1�� �������� �ƴ� ��
				PlayJump = !PlayJump; // ���� ����
				Y -= 8;
				key.KeyTime = GetTickCount64();
			}
			else // 1�� ������ ��
			{
				if (GetTickCount64() - key.KeyTime > 150) // 1�� ���� �� �������ֱ�
				{
					if (!PlayJump2) // 2�������� �ƴ� ��
					{
						PlayJump2 = !PlayJump2; // 2�� ���� ����
						Y -= 15;
					}
					key.KeyTime = GetTickCount64();
				}
			}
		}

		if (PlayJump) // ���� �����̸�
		{
			if (!JumpUpDown) Y -= 8;
			else Y += 8;

			if (PlayJump2) // 2������ �����̸�
			{
				if (Y <= 350)
					JumpUpDown = !JumpUpDown;
			}
			else { // 1������ �����̸�
				if (Y <= 500)
					JumpUpDown = !JumpUpDown;
			}
			if (Y >= 600) { // �� �����ϸ�			
				Y = 600;
				JumpUpDown = !JumpUpDown;
				PlayJump = !PlayJump; // ���� ��
				PlayJump2 = false; // 2�� ���� ��
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
			SkillPlay(sound.SKILL0); // ȿ���� �ѹ��� ����
			SklUse1 = !SklUse1;
			player.AttackTime = GetTickCount64();
		}
		if (SklUse1 && GetTickCount64() - AttackTime >= PlaySklSpeed)
		{
			for (int i = 0; i < Gmanager.M_MGR.GetMonsterCount(); i++) {
				Gmanager.M_MGR.GetMonster(i)->IsDamage = true;
				Gmanager.Damage(&player, Gmanager.M_MGR.GetMonster(i)); // ��ü ����
			}
			player.AttackTime = GetTickCount64();
		}

		if (GetTickCount64() - DamageTime > 1000 && IsDamage) // 1�ʵ��� ǥ��
		{
			IsDamage = !IsDamage;
			DamageTime = GetTickCount64();
		}
	}	
}

void Player::Draw()
{
	if (Gmanager.m_PlayStart) {
		Pos ? // ��ġ�� ���� �¿� �̹��� ���
			imageInfo.PlayerImgR.Render(X, Y, 0, 0.7, 0.7) :
			imageInfo.PlayerImgL.Render(X, Y, 0, 0.7, 0.7);
		imageInfo.HpZeroImg.Render(X, Y, 0, 0.6, 0.5);
		imageInfo.HpFullImg.Render(X, Y, 0, 0.6 *(PlayHp / MaxHp), 0.5);
	}

	SetRect(&HpBox, X, Y - 20, X + 200, Y + 200);
	dv_font.Fonts->DrawTextA(NULL, PlayState, -1, &HpBox, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 50));

	if (IsDamage) // ������ ������
	{
		SetRect(&DamageBox, X, Y - 40, X + 60, Y + 100);
		dv_font.Fonts->DrawTextA(NULL, AtkDamage, -1, &DamageBox, DT_CENTER, D3DCOLOR_ARGB(255, 255, 0, 0));
	}
	
	if (SklUse1) // ��ų
	{
		Pos ?
			imageInfo.SkillImgR.Render(X + 75, Y - 85, 0, 0.5, 0.5) :
			imageInfo.SkillImgL.Render(X - 250, Y - 85, 0, 0.5, 0.5);
	}
	if (!Gmanager.m_Pause) // �Ͻ����� �ƴҶ��� Ű �۵�
	{
		if (KeyDown(VK_CONTROL)) // ����
		{
			Pos ?
				imageInfo.AttackImgR.Render(X + 50, Y+25, 0, 1, 1) :
				imageInfo.AttackImgL.Render(X - 50, Y+25, 0, 1, 1);
		}		
	}
}

void Player::LevelUp()
{
	while (Exp >= MaxExp) // ����ġ�� �ʰ��Ǹ�
	{
		Level++;
		Exp -= MaxExp; // ����ġ ����
		MaxExp = Level * 30;
	} 
		
}

void Player::PlayLevelUp()
{
	while (PlayExp >= PlayMaxExp) // ����ġ�� �ʰ��Ǹ�
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
			PlayHp += 30; // ȸ���ϸ鼭
			MaxHp += 10; // �ִ� ü�� ����
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
		PlayExp -= PlayMaxExp; // ����ġ ����
		PlayMaxExp = PlayLevel * 10; // ������ �ִ����ġ ������ ���� ����
		PlayHp += (MaxHp * 0.1); // �������� 10%ü�� ȸ��
		if (MaxHp <= PlayHp) // ȸ���� ü���� �ִ�ü�º��� ������
			MaxHp = PlayHp; // ü�� ����	
		sprintf(PlayState, "%.lf", PlayHp); // ü�¼�ġ ����
	}	
}

void Player::Reset()
{
	// ȭ�� ũ�⿡ ���� �ϴ� ��ġ
	X = SCREEN_WITH / 2 - 20;
	Y = 600;

	// ĳ���� �÷��� ������ �� ���� ���۸��� �ʱ�ȭ
	PlayLevel = 1; // ������ ����
	PlayMaxLevel = 10; // ������ �ִ뷹��
	PlayExp = 0; // ������ ����ġ
	PlayGold = 0; // ������ ��Ȯ���
	PlayMaxExp = PlayLevel * 15; // ������ �ִ����ġ

	MaxHp = Hp + statInfo.plusHp;; // ������ �ִ� �����(��� ��ġ ����)
	PlayAtk = Atk + statInfo.plusAtk; // ������ ���ݷ�
	PlayDef = Def + statInfo.plusDef; // ������ ����
	PlayHp = MaxHp; // ������ �����
	PlayHit = HitPer + statInfo.plusHitPer; // ������ ���߷�
	PlayMoveSpeed = MoveSpeed + statInfo.plusMoveSpeed; // ������ �̵��ӵ�
	PlayAtkSpeed = AtkSpeed - statInfo.plusAtkSpeed; // ������ ���ݼӵ�
	PlaySklSpeed = PlayAtkSpeed / 2; // ������ ��ų���ݼӵ�
	PlaySklDelay = SklDelay - statInfo.plusSklDelay; // ������ ��ų ��Ÿ��
	PlayMissPer = MissPer + statInfo.plusMissPer; // ������ ȸ�Ƿ�

	PlayJump = false;
	PlayJump2 = false;
	JumpUpDown = false;
	RESET();
}