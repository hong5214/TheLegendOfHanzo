#include "Include.h"

Monster::~Monster(void)
{
}

void Monster::Init()
{
	playerAtkEffectIndex = 0; // �÷��̾� ���� �̹��� �ε���
	Hp = 40; // �����
	Atk = 5; // ���ݷ�	
	Def = 0; // ����
	AtkSpeed = 1000; // ���ݼӵ�
	MoveSpeed = 3; // �̵��ӵ�
	Reset();
}

void Monster::Update()
{
	if (X > player.X + 80) // �÷��̾� ��ġ�� ���� �¿� �̹��� ����
	{
		X -= MoveSpeed;
		Pos = false; // ���Ͱ� �����ʿ� ���� ��		
	}
	else if (X <= player.X - 80) {
		X += MoveSpeed;
		Pos = true;		
	}

	if (KeyDown(VK_CONTROL) && GetTickCount64() - player.AttackTime >= player.PlayAtkSpeed) // �÷��̾� ���ݽ�(�Ѹ� ����)
	{
		int test_atk = (player.X + (int)imageInfo.AttackImgR.imagesinfo.Width * 3 * (player.Pos ? 1 : -1)) * (player.Pos ? 1 : -1);
		if (player.X * (player.Pos ? 1 : -1) <= this->X * (player.Pos ? 1 : -1) && this->X * (player.Pos ? 1 : -1) <= test_atk ) // ���� �浹 ��
		{
			IsDamage = true;
			Gmanager.Damage(&player, this); // �÷��̾� ���ݹ��� ���̸� ������ ����
			player.AttackTime = GetTickCount64();
		}
	}
	if (this->X <= player.X + 80 && player.X - 80 <= this->X
		&& player.Y - 10 <= Y && Y <= player.Y + 10) {
		if (GetTickCount64() - AttackTime > PlayAtkSpeed) // ���� ���ݽ�
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

		// ��ų ������ ���� ��
		if (player.SklUse1)
		{
			if (playerAtkEffectIndex < 9)
				imageInfo.AtkEffectimg1[playerAtkEffectIndex].Render(X, Y, 0, 0.4, 0.4);
			else if (playerAtkEffectIndex > 18)
				imageInfo.AtkEffectimg1[playerAtkEffectIndex].Render(X + imageInfo.GenjiAtkImgR.imagesinfo.Width * 0.7 / 4, Y + imageInfo.GenjiAtkImgR.imagesinfo.Height * 0.7 / 4, 0, 0.4, 0.4);
			else
				imageInfo.AtkEffectimg1[playerAtkEffectIndex].Render(X + imageInfo.GenjiAtkImgR.imagesinfo.Width * 0.7 / 2, Y + imageInfo.GenjiAtkImgR.imagesinfo.Height * 0.7 / 2, 0, 0.4, 0.4);
		}		
		// �⺻ ���� ������ ���� ��
		else {
			Pos ?
				imageInfo.AttackImgL.Render(X + 60, Y + imageInfo.GenjiImgR.imagesinfo.Height / 4, 0, 0.7, 0.7) : imageInfo.AttackImgR.Render(X - 20, Y + imageInfo.GenjiImgR.imagesinfo.Height / 4, 0, 0.7, 0.7);
		}
	}

	SetRect(&HpBox, X, Y-20, X + 200, Y + 200);
	dv_font.Fonts->DrawTextA(NULL, PlayState, -1, &HpBox, DT_LEFT, D3DCOLOR_ARGB(255, 255, 255, 50));

	if (X <= player.X + 80 && player.X - 80 <= X
		&& player.Y - 10 <= Y && Y <= player.Y + 10) { // ���ݹ����� ��
		Pos ?
			imageInfo.GenjiAtkImgR.Render(X + 75, Y, 0, 0.2, 0.2)
			: imageInfo.GenjiAtkImgL.Render(X - 50, Y, 0, 0.2, 0.2);
	}
}

void Monster::Reset()
{
	// ȭ�� ũ�⿡ ���� �ϴ� ��ġ
	srand(time(NULL));
	X = rand() % 11 * 100; // ��ġ���� ����
	Y = 600;

	Level = 0; // ���� : 0~3(�ʱ�/���/���� ����)

	// ���������� ���� ����
	MaxHp = Hp + 10 * map.m_Stage; // �����
	Exp = 2 * map.m_Stage; // ���� : ���� ų�� ����ġ
	Gold = 100 + 10 * map.m_Stage; // ���� : ���� ų�� ���
	PlayHp = MaxHp; // ������ �����
	PlayAtk = Atk + 5 * map.m_Stage; // ������ ���ݷ�
	PlayDef = Def + 3 * map.m_Stage; // ������ ����
	PlayMoveSpeed = MoveSpeed + map.m_Stage; // ������ �̵��ӵ�
	PlayAtkSpeed = AtkSpeed - 30 * map.m_Stage; // ������ ���ݼӵ�

	RESET(); // ĳ���� �⺻���� �ʱ�ȭ	
}