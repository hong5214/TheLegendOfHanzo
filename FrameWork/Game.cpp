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
	//	Gmanager.M_MGR.Insert_Monster(); // 1���� �߰�
	//	Gmanager.M_MGR.Insert_Monster(); // 2���� �߰�
	//}
	sound.Init();
	Gmanager.Init(); // ���� ����
	// ����Ÿ ���̽� �ʱ�ȭ
	PauseTime = GetTickCount64();
}

void Game::Draw()
{
	if (Gmanager.m_PlayStart) // ������ �������϶��� ����(�Ͻ����������� �׷��ش�.)
	{
		Gmanager.Draw(); // ���� ���� ���� �׸���		
		sql.Draw(); // ����Ÿ ���̽� üũ
		statInfo.ShowStat();		
	}	
	if (true)
		imageInfo.HelpGame.Render(SCREEN_WITH - imageInfo.HelpLogo.imagesinfo.Width, 130, 0, 1, 1);
}

// Chap, ������ �Լ� ȣ��
void Game::Update(double frame)
{
	/*if (GetTickCount64() - key.KeyTime > 150)
	{
		if (KeyDown('P'))
			Gmanager.m_Pause = !Gmanager.m_Pause;

		key.KeyTime = GetTickCount64();
	}*/

	if (GetTickCount64() - PauseTime > 50) // �Ͻ�����
	{
		if (KeyDown(VK_ESCAPE))
			Gmanager.m_Pause = !Gmanager.m_Pause;
		PauseTime = GetTickCount64();
	}
	Gmanager.Update(); // ���� ���� ���� ������Ʈ
}


void Game::OnMessage( MSG* msg )
{

}