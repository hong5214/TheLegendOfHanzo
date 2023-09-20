#include "Include.h"

Logo::Logo()
{
	// ����Ÿ ���̽� ����
	sql.mysql_Success = false;
	// ����Ÿ ���̽� �׽�Ʈ ����
	count = 0;
}

Logo::~Logo()
{
}

void Logo::Init()
{
	speed = 2000;
	alpha = 0;

	loadimg.Create("./resource/Img/Load/hero.png", false, D3DCOLOR_XRGB(0, 0, 0));
	sql.Init(); // �����ͺ��̽� �ʱ�ȭ
}

// Chap, ������ �Լ� ȣ��
void Logo::Update(double frame)
{	
	alpha += speed * frame / 1000;
	if( alpha >= 255 )
	{
		alpha = 255;
		speed = -speed;
	}
	if(alpha <= 0) {
		alpha = 0;
		speed = -speed;
		g_Mng.n_Chap = MENU;
	}
	//Sound1.Play(0, DSBPLAY_LOOPING);
}

void Logo::Draw()
{
	if (true)
	{
		imageInfo.HelpLogo.Render(SCREEN_WITH - imageInfo.HelpLogo.imagesinfo.Width, 200, 0, 1, 1);
	}
	loadimg.SetColor(255,255,255, alpha);  // ���� ����
	loadimg.Draw(SCREEN_WITH / 4, 0 ) ;  //�̹������
	dv_font.DrawString("�ε�", 0, 0);   //�������
	dv_font.DrawString("�ü��� ����", SCREEN_WITH / 2 - 50, 230);   //�������


	// ����Ÿ ���̽� ��� �� ó�� ���� ǥ��/////////////////////////////////////
	if (sql.mysql_Success)
	{
		dv_font.DrawString("DB_OK", SCREEN_WITH / 2 - 30, 0);
	}
	else
	{
		dv_font.DrawString("DB_NO", SCREEN_WITH / 2 - 30, 0);
		// dv_font.DrawString(sql.state, SCREEN_WITH / 2 - 30, 100); // �����ͺ��̽� ���� ǥ��
	}
}

void Logo::OnMessage( MSG* msg )
{
}