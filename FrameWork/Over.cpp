#include "Include.h"


Over::Over()
{	
}

Over::~Over()
{
}

void Over::Init()
{
	Gmanager.m_PlayStart = false; // ���� ����	
	alpha = 0;
	speed = 2000;	
	overWinImg.Create("./resource/Img/Over/overWin.png", false, D3DCOLOR_XRGB(0, 0, 0));
	overLossImg.Create("./resource/Img/Over/overDie.png", false, D3DCOLOR_XRGB(0, 0, 0));
}

// Chap, ������ �Լ� ȣ��
void Over::Update(double frame)
{
	alpha += speed * frame / 1000;
	if (alpha >= 255)
	{
		alpha = 255;
		speed = -speed;
		//Draw();
	}
	if (alpha <= 0) {
		Init(); // over ���� �ʱ�ȭ(���� ���� ����)
		
		// �Ͻ����� ���µ� ����
		Gmanager.m_Pause = false;
		player.Gold += player.PlayGold; // ��� �߰�
		player.Exp += (int)(20 * (player.PlayLevel-1) + 100 * ((player.PlayHp > 0) ? player.PlayHp : 1)); // ����ġ �߰�
		player.LevelUp();
		sql.autoSave();
		player.Init(); // �ʱ�ȭ ���ְ�
		g_Mng.n_Chap = MENU;
		sound.BGChange("./resource/Sound/BGM_Menu.mp3");
		//sound.m_Bk1->Stop(); // ���� ����
	}
}

void Over::Draw()
{
	if (player.Life)
	{
		overWinImg.SetColor(255, 255, 255, alpha);  // ���� ����
		overWinImg.Draw(SCREEN_WITH / 2 - overWinImg.imagesinfo.Width / 2, SCREEN_HEIGHT / 2 - overWinImg.imagesinfo.Height / 2);  //�̹������
	}
	else
	{
		overLossImg.SetColor(255, 255, 255, alpha);  // ���� ����
		overLossImg.Draw(SCREEN_WITH / 2 - overLossImg.imagesinfo.Width / 2, SCREEN_HEIGHT / 2 - overLossImg.imagesinfo.Height / 2);  //�̹������
	}
	
	dv_font.DrawString("����", 0, 0);   //�������
	if(player.Life)
		dv_font.DrawString("�¸�", SCREEN_WITH / 2 - 10, 0);   //�������
	else
		dv_font.DrawString("�й�", SCREEN_WITH / 2 - 10, 0);   //�������
}

void Over::OnMessage( MSG* msg )
{

}