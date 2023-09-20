#include "Include.h"

GameManager Gmanager;

GameManager::GameManager(void)
{
	LoadingState = true; // ���α׷� ���۽� �ѹ��� �ʱ�ȭ(�α���ȭ��)
	NewId = false; // ���ο� ���̵��̸� true
	m_PlayStart = false; // ���α׷� ���۽� ���� �������̹Ƿ� false
	GameReset(); // �������� �ʱ�ȭ
}

GameManager::~GameManager(void)
{
}

void GameManager::Init()
{
	// ���� ����
	map.m_Stage = 1; // �������� 1�� �ʱ�ȭ
	GameReset(); // �������� �ʱ�ȭ
}

void GameManager::Update()
{
	if (m_PlayStart && !m_Pause) // ������ �������̰�, �Ͻ������� �ƴҶ��� ����
	{
		key.Update(); // ���ӿ��� ����� Ű 
		map.Update(50); // �� ���� ������Ʈ
		player.Update(); // �÷��̾� ���� ������Ʈ
		statInfo.Update();
		for (int i = 0; i < M_MGR.GetMonsterCount(); i++){
			if (M_MGR.GetMonster(i)->Life) // ����ִ� ���
				M_MGR.Update_Monster(i); // ��ȯ�� ���� ������Ʈ
		}

		if (monsterCount < monsterMaxCount) // ��ȯ�ð��� ���� ���� ��ȯ
			CreateMonster();
		NextStage(); // Ŭ���� ���� �޼��� ����
		if (player.PlayExp >= player.PlayMaxExp) // ������ �ÿ��� �Ͻ�����
		{
			m_Pause = true; // �Ͻ�����
			BoxCount = 0; // �ڽ� ������ �ʱ�ȭ
		}
		RandomSelect(rand() % 3); // ������ ���� ���û��� �������� ����
		if (GetTickCount64() - CheckSecTime > 100 && !player.SklUse1)
		{
			if (player.PlaySklDelay > 0.0)
				player.PlaySklDelay -= 0.1; // 0.1�ʾ� ����
			if (player.PlaySklDelay <= 0.0) // ����ó��
				player.PlaySklDelay = 0.0; // 0���� �ʱ�ȭ
			CheckSecTime = GetTickCount64();
		}
		if ((player.SklUse1 && GetTickCount64() - CheckSecTime > 1000)) // ��ų ���ð�(1��) ������ ��Ÿ�� �ʱ�ȭ
		{
			player.PlaySklDelay = player.SklDelay - statInfo.plusSklDelay;
			player.SklUse1 = !player.SklUse1;
		}
	}
	else
	{	
		if (GetTickCount64() - key.KeyTime > 100)
		{
			if (KeyDown(VK_RETURN)) {
				player.PlayLevelUp(); // ������ �����ϸ� ������	
				CheckSecTime += GetTickCount64() - CheckSecTime; // ��ų ���� ��ų ���� �ð� ����
				Sleep(200); // ���ý� �ణ �������ֱ�
				m_Pause = false; // �Ͻ����� ����
			}

			if (KeyDown(VK_RIGHT)) {
				if (BoxCount < 2)
					BoxCount++;
				else
					BoxCount = 0;
			}
			if (KeyDown(VK_LEFT)) {
				if (BoxCount > 0)
					BoxCount--;
				else
					BoxCount = 2;
			}
			key.KeyTime = GetTickCount64();
		}
	}
}

void GameManager::Draw()
{	
	map.Draw(); // �� �̹��� ���		
	statInfo.Draw();
	player.Draw(); // �÷��̾� �̹��� �׸���
	if (player.SklUse1) {
		imageInfo.SkillEffectImg.Render(SCREEN_WITH / 2 - imageInfo.SkillEffectImg.imagesinfo.Width / 2, 140, 0, 1.1, 1.1);
	}
	for (int i = 0; i < M_MGR.GetMonsterCount(); i++) {
		if (M_MGR.GetMonster(i)->Life) // ����ִ� ���
			M_MGR.Draw_Monster(i); // ��ȯ�� ���� �׸���
	}
	if (player.PlayExp >= player.PlayMaxExp) // ������ �ÿ��� ������ ȭ�� ���
	{
		int selectX = SCREEN_WITH / 2 - imageInfo.LevelUpImg.imagesinfo.Width / 2;
		int spaceX = (imageInfo.LevelUpImg.imagesinfo.Width - imageInfo.RandomImg[0].imagesinfo.Width * 0.6 * 3) / 4;
		int random0 = selectX + spaceX;
		int random1 = SCREEN_WITH / 2 - imageInfo.RandomImg[1].imagesinfo.Width * 0.6 / 2;
		int random2 = SCREEN_WITH / 2 + imageInfo.RandomImg[2].imagesinfo.Width * 0.6 / 2 + spaceX;
		imageInfo.LevelUpImg.Render(selectX, SCREEN_HEIGHT / 2 - imageInfo.LevelUpImg.imagesinfo.Height / 2, 0, 1, 1);
		imageInfo.RandomImg[0].Render(random0, SCREEN_HEIGHT / 2, 0, 0.6, 0.6);
		imageInfo.RandomImg[1].Render(random1, SCREEN_HEIGHT / 2, 0, 0.6, 0.6);
		imageInfo.RandomImg[2].Render(random2, SCREEN_HEIGHT / 2, 0, 0.6, 0.6);

		spaceX = (imageInfo.SelectBox.imagesinfo.Width - imageInfo.RandomImg[0].imagesinfo.Width) * 0.6 / 2;
		if (BoxCount == 0)
			imageInfo.SelectBox.Render(random0 - spaceX, SCREEN_HEIGHT / 2 - spaceX, 0, 0.6, 0.6);
		else if (BoxCount == 1)
			imageInfo.SelectBox.Render(random1 - spaceX, SCREEN_HEIGHT / 2 - spaceX, 0, 0.6, 0.6);
		else if (BoxCount == 2)
			imageInfo.SelectBox.Render(random2 - spaceX, SCREEN_HEIGHT / 2 - spaceX, 0, 0.6, 0.6);
	}
}

void GameManager::GameReset(void)  // ���ӿ� ���� ���� �ʱ�ȭ
{
	AlphaTime = GetTickCount64();
	GameTime = GetTickCount64();
	CheckSecTime = GetTickCount64();
	m_GameSpeed = 1;
	m_Pause = false; // �Ͻ����� ����
	m_PlayStart = true; // ���� ���۽� true

	monsterCount = 0;
	monsterKillCount = 0;
	monsterMaxCount = 1 + map.m_Stage * 2; // ���������� ���� ���� ���ͼ� ����
	M_MGR.Reset_Monster(); // ���� ���� �ʱ�ȭ
}


void GameManager::Damage(Player* atk, Monster* atked)
{
	Attacked(atk, atked);
}

void GameManager::Damage(Monster* atk, Player* atked)
{	
	if(atk->X * (atk->Pos ? 1 : -1) <= atked->X * (atk->Pos ? 1 : -1) && atked->X * (atk->Pos ? 1 : -1) <= (atk->X + imageInfo.GenjiAtkImgR.imagesinfo.Width * 0.5 * (atk->Pos ? 1 : -1)) * (atk->Pos ? 1 : -1)
		&& atk->Y - imageInfo.GenjiAtkImgR.imagesinfo.Height / 2 * 0.5 <= atked->Y && atked->Y <= atk->Y + imageInfo.GenjiAtkImgR.imagesinfo.Height / 2 * 0.5) // ���� �浹 ��
		Attacked(atk, atked);
	//if (atk->Pos) {
	//	if (atk->X <= atked->X && atked->X <= atk->X + atk->AttackImg.imagesinfo.Width * 0.5
	//		&& atk->Y - atk->AttackImg.imagesinfo.Height / 2 * 0.5 <= atked->Y && atked->Y <= atk->Y + atk->AttackImg.imagesinfo.Height / 2 * 0.5) // ���� �浹 ��
	//		Attacked(atk, atked);
	//}
	//else {
	//	if (atk->X >= atked->X && atked->X >= atk->X - atk->AttackImg.imagesinfo.Width * 0.5) // ���� �浹 ��
	//		Attacked(atk, atked);
	//}
}

void GameManager::Attacked(Player* atk, Monster* atked) {
	srand(time(NULL));
	int damage = (int)(atk->PlayAtk + rand() % (int)atk->PlayHit) * (atk->SklUse1 ? 0.8 : 1) - rand() % (int)atked->PlayDef;
	if (damage > 0)
	{
		atked->PlayHp -= damage; // ��ų�� ������ 20���� ����
		sprintf(atked->PlayState, "%.lf", atked->PlayHp);
		sprintf_s(atked->AtkDamage, "%d", damage);
	}
	else {
		sprintf_s(atked->AtkDamage, "Miss");
	}
	
	EffectPlay(sound.ATK);
	//sound.m_Shot->Play();
	if (atked->PlayHp <= 0) // ���Ͱ� ���� ���¸�
	{
		monsterKillCount++; // ų ī��Ʈ ����
		atked->Life = !atked->Life; // ��� ó��
		M_MGR.Remove_Monster(atked->index); // ��ü ����
		for (int i = atked->index; i < M_MGR.GetMonsterCount(); i++) // �Ĺݺ��� ���� �ε��� �ʱ�ȭ
			M_MGR.GetMonster(i)->index--; // 1���� ���϶�����		
		player.PlayGold += atked->Gold; // �ش� ������ ���� ��常ŭ ����
		if (player.PlayLevel >= player.PlayMaxLevel) { // �ִ� �����̸�
			player.PlayExp = 0;
		}
		else
			player.PlayExp += atked->Exp; // �ش� ������ ���� ����ġ��ŭ ����
	}
}

void GameManager::Attacked(Monster* atk, Player* atked) {
	if (rand() % 100 >= atked->PlayMissPer) // 0~DefPer ������ ������ ������
	{
		int damage = (int)(atk->PlayAtk - rand() % (int)atked->PlayDef);
		if (damage > 0) // ���ݷ��� �� ũ��
		{
			atked->PlayHp -= damage;
			sprintf(atked->PlayState, "%.lf", atked->PlayHp);			
			sprintf_s(atked->AtkDamage, "%d", damage);
			player.IsDamage = true;
			player.DamageTime = GetTickCount64();
		}
		else {
			sprintf_s(atked->AtkDamage, "Block"); // ������ ���Ƽ� ����
			player.IsDamage = true;
			player.DamageTime = GetTickCount64();
		}
	}
	else {
		sprintf_s(atked->AtkDamage, "Miss"); // ȸ������ ���Ƽ� ����
		player.IsDamage = true;
		player.DamageTime = GetTickCount64();
	}
	EffectPlay(sound.GENJIATK);
	//sound.m_Shot->Play();

	if (atked->PlayHp <= 0) //�÷��̾ �׾��ٸ�
	{		
		atked->Life = false; // ���
		Sleep(50); // �ణ ������ ��
		g_Mng.n_Chap = OVER;
	}
}

void GameManager::NextStage()
{
	if (0 >= M_MGR.GetMonsterCount()) // ���� ���Ͱ� ���ٸ�
	{
		// �������� Ŭ����� ���� �ܰ��
		if (monsterCount == monsterMaxCount) {
			if (map.m_Stage < map.MaxStage) // 3������������ ����
			{
				map.m_Stage++; // �������� �� ����
				GameReset(); // ���� ���������� �����
			}
			else { // ��� Ŭ�����ϸ� ��				
				g_Mng.n_Chap = OVER;
			}
		}		
	}
}

void GameManager::CreateMonster()
{
	if (GetTickCount64() - AlphaTime >= 2000 && M_MGR.GetMonsterCount() < 5) // ���� �ִ� 3���� ��ȯ
	{
		monsterCount++;
		M_MGR.Insert_Monster();
		AlphaTime = GetTickCount64();
	}
}

void GameManager::RandomSelect(int idx) {
	srand(time(NULL));
	int count = rand() % SELECT_MAX;
	for (int i = 0; i < 3; i++)
	{
		if (RandomIdx[i] == count) // ������ 3���� �ߺ��Ǵ� ��ȣ���
		{
			count = (count + 1) % SELECT_MAX; // 1������ ���ο� ��ȣ�� �ʱ�ȭ
			i = 0;
		}
	}
	RandomIdx[idx] = count;
	imageInfo.RandomImg[idx] = imageInfo.SelectImg[RandomIdx[idx]];
}