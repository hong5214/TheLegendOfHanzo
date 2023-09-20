#include "Include.h"

Logo::Logo()
{
	// 데이타 베이스 관련
	sql.mysql_Success = false;
	// 데이타 베이스 테스트 관련
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
	sql.Init(); // 데이터베이스 초기화
}

// Chap, 재정의 함수 호출
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
	loadimg.SetColor(255,255,255, alpha);  // 색상 변경
	loadimg.Draw(SCREEN_WITH / 4, 0 ) ;  //이미지출력
	dv_font.DrawString("로딩", 0, 0);   //글자출력
	dv_font.DrawString("궁수의 전설", SCREEN_WITH / 2 - 50, 230);   //글자출력


	// 데이타 베이스 결과 및 처리 상태 표시/////////////////////////////////////
	if (sql.mysql_Success)
	{
		dv_font.DrawString("DB_OK", SCREEN_WITH / 2 - 30, 0);
	}
	else
	{
		dv_font.DrawString("DB_NO", SCREEN_WITH / 2 - 30, 0);
		// dv_font.DrawString(sql.state, SCREEN_WITH / 2 - 30, 100); // 데이터베이스 상태 표시
	}
}

void Logo::OnMessage( MSG* msg )
{
}