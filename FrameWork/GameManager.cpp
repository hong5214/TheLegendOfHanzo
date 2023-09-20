#include "Include.h"

GameManager Gmanager;

GameManager::GameManager(void)
{
	LoadingState = true; // 프로그램 시작시 한번만 초기화(로그인화면)
	NewId = false; // 새로운 아이디이면 true
	m_PlayStart = false; // 프로그램 시작시 게임 미진행이므로 false
	GameReset(); // 게임정보 초기화
}

GameManager::~GameManager(void)
{
}

void GameManager::Init()
{
	// 게임 시작
	map.m_Stage = 1; // 스테이지 1로 초기화
	GameReset(); // 게임정보 초기화
}

void GameManager::Update()
{
	if (m_PlayStart && !m_Pause) // 게임이 시작중이고, 일시정지가 아닐때만 실행
	{
		key.Update(); // 게임에서 사용할 키 
		map.Update(50); // 맵 정보 업데이트
		player.Update(); // 플레이어 정보 업데이트
		statInfo.Update();
		for (int i = 0; i < M_MGR.GetMonsterCount(); i++){
			if (M_MGR.GetMonster(i)->Life) // 살아있는 경우
				M_MGR.Update_Monster(i); // 소환된 몬스터 업데이트
		}

		if (monsterCount < monsterMaxCount) // 소환시간에 따라 몬스터 소환
			CreateMonster();
		NextStage(); // 클리어 조건 달성시 실행
		if (player.PlayExp >= player.PlayMaxExp) // 레벨업 시에는 일시정지
		{
			m_Pause = true; // 일시정지
			BoxCount = 0; // 박스 아이템 초기화
		}
		RandomSelect(rand() % 3); // 렙업시 나올 선택상자 랜덤으로 변경
		if (GetTickCount64() - CheckSecTime > 100 && !player.SklUse1)
		{
			if (player.PlaySklDelay > 0.0)
				player.PlaySklDelay -= 0.1; // 0.1초씩 감소
			if (player.PlaySklDelay <= 0.0) // 예외처리
				player.PlaySklDelay = 0.0; // 0으로 초기화
			CheckSecTime = GetTickCount64();
		}
		if ((player.SklUse1 && GetTickCount64() - CheckSecTime > 1000)) // 스킬 사용시간(1초) 끝나면 쿨타임 초기화
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
				player.PlayLevelUp(); // 레벨업 가능하면 레벨업	
				CheckSecTime += GetTickCount64() - CheckSecTime; // 스킬 사용시 스킬 선택 시간 제외
				Sleep(200); // 선택시 약간 딜레이주기
				m_Pause = false; // 일시정지 해제
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
	map.Draw(); // 맵 이미지 출력		
	statInfo.Draw();
	player.Draw(); // 플레이어 이미지 그리기
	if (player.SklUse1) {
		imageInfo.SkillEffectImg.Render(SCREEN_WITH / 2 - imageInfo.SkillEffectImg.imagesinfo.Width / 2, 140, 0, 1.1, 1.1);
	}
	for (int i = 0; i < M_MGR.GetMonsterCount(); i++) {
		if (M_MGR.GetMonster(i)->Life) // 살아있는 경우
			M_MGR.Draw_Monster(i); // 소환된 몬스터 그리기
	}
	if (player.PlayExp >= player.PlayMaxExp) // 레벨업 시에만 레벨업 화면 출력
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

void GameManager::GameReset(void)  // 게임에 대한 정보 초기화
{
	AlphaTime = GetTickCount64();
	GameTime = GetTickCount64();
	CheckSecTime = GetTickCount64();
	m_GameSpeed = 1;
	m_Pause = false; // 일시정지 해제
	m_PlayStart = true; // 게임 시작시 true

	monsterCount = 0;
	monsterKillCount = 0;
	monsterMaxCount = 1 + map.m_Stage * 2; // 스테이지에 따라 남은 몬스터수 변경
	M_MGR.Reset_Monster(); // 몬스터 정보 초기화
}


void GameManager::Damage(Player* atk, Monster* atked)
{
	Attacked(atk, atked);
}

void GameManager::Damage(Monster* atk, Player* atked)
{	
	if(atk->X * (atk->Pos ? 1 : -1) <= atked->X * (atk->Pos ? 1 : -1) && atked->X * (atk->Pos ? 1 : -1) <= (atk->X + imageInfo.GenjiAtkImgR.imagesinfo.Width * 0.5 * (atk->Pos ? 1 : -1)) * (atk->Pos ? 1 : -1)
		&& atk->Y - imageInfo.GenjiAtkImgR.imagesinfo.Height / 2 * 0.5 <= atked->Y && atked->Y <= atk->Y + imageInfo.GenjiAtkImgR.imagesinfo.Height / 2 * 0.5) // 몬스터 충돌 시
		Attacked(atk, atked);
	//if (atk->Pos) {
	//	if (atk->X <= atked->X && atked->X <= atk->X + atk->AttackImg.imagesinfo.Width * 0.5
	//		&& atk->Y - atk->AttackImg.imagesinfo.Height / 2 * 0.5 <= atked->Y && atked->Y <= atk->Y + atk->AttackImg.imagesinfo.Height / 2 * 0.5) // 몬스터 충돌 시
	//		Attacked(atk, atked);
	//}
	//else {
	//	if (atk->X >= atked->X && atked->X >= atk->X - atk->AttackImg.imagesinfo.Width * 0.5) // 몬스터 충돌 시
	//		Attacked(atk, atked);
	//}
}

void GameManager::Attacked(Player* atk, Monster* atked) {
	srand(time(NULL));
	int damage = (int)(atk->PlayAtk + rand() % (int)atk->PlayHit) * (atk->SklUse1 ? 0.8 : 1) - rand() % (int)atked->PlayDef;
	if (damage > 0)
	{
		atked->PlayHp -= damage; // 스킬은 데미지 20프로 감소
		sprintf(atked->PlayState, "%.lf", atked->PlayHp);
		sprintf_s(atked->AtkDamage, "%d", damage);
	}
	else {
		sprintf_s(atked->AtkDamage, "Miss");
	}
	
	EffectPlay(sound.ATK);
	//sound.m_Shot->Play();
	if (atked->PlayHp <= 0) // 몬스터가 죽은 상태면
	{
		monsterKillCount++; // 킬 카운트 증가
		atked->Life = !atked->Life; // 사망 처리
		M_MGR.Remove_Monster(atked->index); // 객체 감소
		for (int i = atked->index; i < M_MGR.GetMonsterCount(); i++) // 후반부의 몬스터 인덱스 초기화
			M_MGR.GetMonster(i)->index--; // 1마리 죽일때마다		
		player.PlayGold += atked->Gold; // 해당 몬스터의 보유 골드만큼 증가
		if (player.PlayLevel >= player.PlayMaxLevel) { // 최대 레벨이면
			player.PlayExp = 0;
		}
		else
			player.PlayExp += atked->Exp; // 해당 몬스터의 보유 경험치만큼 증가
	}
}

void GameManager::Attacked(Monster* atk, Player* atked) {
	if (rand() % 100 >= atked->PlayMissPer) // 0~DefPer 에서는 데미지 안입음
	{
		int damage = (int)(atk->PlayAtk - rand() % (int)atked->PlayDef);
		if (damage > 0) // 공격력이 더 크면
		{
			atked->PlayHp -= damage;
			sprintf(atked->PlayState, "%.lf", atked->PlayHp);			
			sprintf_s(atked->AtkDamage, "%d", damage);
			player.IsDamage = true;
			player.DamageTime = GetTickCount64();
		}
		else {
			sprintf_s(atked->AtkDamage, "Block"); // 방어력이 높아서 막음
			player.IsDamage = true;
			player.DamageTime = GetTickCount64();
		}
	}
	else {
		sprintf_s(atked->AtkDamage, "Miss"); // 회피율이 높아서 막음
		player.IsDamage = true;
		player.DamageTime = GetTickCount64();
	}
	EffectPlay(sound.GENJIATK);
	//sound.m_Shot->Play();

	if (atked->PlayHp <= 0) //플레이어가 죽었다면
	{		
		atked->Life = false; // 사망
		Sleep(50); // 약간 딜레이 줌
		g_Mng.n_Chap = OVER;
	}
}

void GameManager::NextStage()
{
	if (0 >= M_MGR.GetMonsterCount()) // 남은 몬스터가 없다면
	{
		// 스테이지 클리어시 다음 단계로
		if (monsterCount == monsterMaxCount) {
			if (map.m_Stage < map.MaxStage) // 3스테이지까지 있음
			{
				map.m_Stage++; // 스테이지 수 증가
				GameReset(); // 다음 스테이지로 재시작
			}
			else { // 모두 클리어하면 끝				
				g_Mng.n_Chap = OVER;
			}
		}		
	}
}

void GameManager::CreateMonster()
{
	if (GetTickCount64() - AlphaTime >= 2000 && M_MGR.GetMonsterCount() < 5) // 몬스터 최대 3마리 소환
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
		if (RandomIdx[i] == count) // 기존의 3개중 중복되는 번호라면
		{
			count = (count + 1) % SELECT_MAX; // 1증가한 새로운 번호로 초기화
			i = 0;
		}
	}
	RandomIdx[idx] = count;
	imageInfo.RandomImg[idx] = imageInfo.SelectImg[RandomIdx[idx]];
}