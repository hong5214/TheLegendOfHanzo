#include "Include.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	map.Init();
	//if (!Gmanager.LoadingState) {
	//	Gmanager.M_MGR.Insert_Monster(); // 1마리 추가
	//	Gmanager.M_MGR.Insert_Monster(); // 2마리 추가
	//}
	sound.Init();
	Gmanager.Init(); // 몬스터 생성
	// 데이타 베이스 초기화
	PauseTime = GetTickCount64();
}

void Game::Draw()
{
	if (Gmanager.m_PlayStart) // 게임이 시작중일때만 실행(일시정지에서도 그려준다.)
	{
		Gmanager.Draw(); // 게임 관련 정보 그리기		
		sql.Draw(); // 데이타 베이스 체크
		statInfo.ShowStat();		
	}	
	if (true)
		imageInfo.HelpGame.Render(SCREEN_WITH - imageInfo.HelpLogo.imagesinfo.Width, 130, 0, 1, 1);
}

// Chap, 재정의 함수 호출
void Game::Update(double frame)
{
	/*if (GetTickCount64() - key.KeyTime > 150)
	{
		if (KeyDown('P'))
			Gmanager.m_Pause = !Gmanager.m_Pause;

		key.KeyTime = GetTickCount64();
	}*/

	if (GetTickCount64() - PauseTime > 50) // 일시정지
	{
		if (KeyDown(VK_ESCAPE))
			Gmanager.m_Pause = !Gmanager.m_Pause;
		PauseTime = GetTickCount64();
	}
	Gmanager.Update(); // 게임 관련 정보 업데이트
}


void Game::OnMessage( MSG* msg )
{

}