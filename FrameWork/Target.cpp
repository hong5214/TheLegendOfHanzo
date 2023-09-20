#include "Include.h"


Target target;


Target::Target()
{
	// 화면 크기에 따라 하단 배치
	m_W = SCREEN_WITH / 2 - 20;
	m_H = 600;
	m_Target.dx = SCREEN_WITH / 2 + 15;
	m_Target.dy = 630;
}

Target::~Target()
{
}

void Target::Init()
{
	char FileName[256];
	
	for(int i = 0; i<2; i++ )
	{
		sprintf_s(FileName, "./resource/Img/Player/userR.png");
		Tgimg[i].Create(FileName,false,D3DCOLOR_XRGB(0,0,0));
	}
	for(int i = 0; i<4; i++ )
	{
		sprintf_s(FileName, "./resource/Img/Player/AttackR.png");
		Tgimg2[i].Create(FileName,false,D3DCOLOR_XRGB(0,0,0));
	}

}

void Target::Update()
{
	if(GetTickCount() - AniTime1 > 1000)
	{
		m_TgCount1++;
		if(m_TgCount1>1) m_TgCount1 = 0;
		AniTime1 = GetTickCount();
	}

	if(GetTickCount() - AniTime2 > 100)
	{
		target.m_TgCount2++;
		if(target.m_TgCount2>3) { target.m_TgCount2 = 0; target.m_Life = false;}

			
		AniTime2 = GetTickCount();
	}

}

void Target::Draw()
{
	if(Gmanager.m_GameStart==true) 
		Tgimg[m_TgCount1].Render(m_W, m_H, 0, 0.7, 0.7);

	if(m_Life==true && Gmanager.m_GameStart==true  )
	{
		Tgimg2[m_TgCount2].Render(m_W+70, m_H-85, 0, 0.5, 0.5);
	}

	if(Gmanager.m_Collision == true)
	{
		/*SetRect(&m_rc, m_Target.dx,m_Target.dy, m_Target.dx+150, m_Target.dy+150);
		dv_font.Fonts->DrawTextA(NULL,"충",-1,&m_rc,DT_LEFT,D3DCOLOR_ARGB(255,255,0,0));*/
	}
	/*SetRect(&m_rc, m_Target.dx,m_Target.dy, m_Target.dx+150, m_Target.dy+150);
	char a[256];
	sprintf(a, "%lf\n%lf\n%lf\n%lf\n", m_W, m_H, m_Target.dx, m_Target.dy);
	dv_font.Fonts->DrawTextA(NULL, a, -1, &m_rc, DT_LEFT, D3DCOLOR_ARGB(255, 255, 0, 0));
	dv_font.DrawString(a, 100, 100);*/
}

void Target::Reset()
{
	m_W = SCREEN_WITH/2;
	m_H = SCREEN_HEIGHT/2;
	m_Target.dx = SCREEN_WITH/2+35;
	m_Target.dy = SCREEN_HEIGHT/2+30;
}