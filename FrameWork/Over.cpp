#include "Include.h"


Over::Over()
{	
}

Over::~Over()
{
}

void Over::Init()
{
	Gmanager.m_PlayStart = false; // 게임 종료	
	alpha = 0;
	speed = 2000;	
	overWinImg.Create("./resource/Img/Over/overWin.png", false, D3DCOLOR_XRGB(0, 0, 0));
	overLossImg.Create("./resource/Img/Over/overDie.png", false, D3DCOLOR_XRGB(0, 0, 0));
}

// Chap, 재정의 함수 호출
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
		Init(); // over 정보 초기화(다음 판을 위함)
		
		// 일시정지 상태도 해제
		Gmanager.m_Pause = false;
		player.Gold += player.PlayGold; // 골드 추가
		player.Exp += (int)(20 * (player.PlayLevel-1) + 100 * ((player.PlayHp > 0) ? player.PlayHp : 1)); // 경험치 추가
		player.LevelUp();
		sql.autoSave();
		player.Init(); // 초기화 해주고
		g_Mng.n_Chap = MENU;
		sound.BGChange("./resource/Sound/BGM_Menu.mp3");
		//sound.m_Bk1->Stop(); // 음악 정지
	}
}

void Over::Draw()
{
	if (player.Life)
	{
		overWinImg.SetColor(255, 255, 255, alpha);  // 색상 변경
		overWinImg.Draw(SCREEN_WITH / 2 - overWinImg.imagesinfo.Width / 2, SCREEN_HEIGHT / 2 - overWinImg.imagesinfo.Height / 2);  //이미지출력
	}
	else
	{
		overLossImg.SetColor(255, 255, 255, alpha);  // 색상 변경
		overLossImg.Draw(SCREEN_WITH / 2 - overLossImg.imagesinfo.Width / 2, SCREEN_HEIGHT / 2 - overLossImg.imagesinfo.Height / 2);  //이미지출력
	}
	
	dv_font.DrawString("종료", 0, 0);   //글자출력
	if(player.Life)
		dv_font.DrawString("승리", SCREEN_WITH / 2 - 10, 0);   //글자출력
	else
		dv_font.DrawString("패배", SCREEN_WITH / 2 - 10, 0);   //글자출력
}

void Over::OnMessage( MSG* msg )
{

}