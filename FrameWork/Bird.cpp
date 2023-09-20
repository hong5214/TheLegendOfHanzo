#include "Include.h"


Bird bird;


Bird::Bird()
{
	m_BirdAniTime = 0;
	m_BirdCount = 0;
}

Bird::~Bird()
{
}

void Bird::Init()
{
	char FileName[256];
	
	for(int i = 0; i<2; i++ )
	{
		sprintf_s(FileName, "./resource/Img/AAA/bird_fly%02d.png", i+1 );
		Bdimg[i].Create(FileName,false,D3DCOLOR_XRGB(0,0,0));
	}

}

void Bird::Update()
{


	if(GetTickCount() - m_BirdAniTime > 1000)
	{
		m_BirdCount++;
		if(m_BirdCount >1) m_BirdCount = 0;
		m_BirdAniTime = GetTickCount();
	}



}

void Bird::Draw()
{
	if (Gmanager.m_GameStart == true)
	{
		Bdimg[m_BirdCount].SetColor(0, 255, 0, 255);
		Bdimg[m_BirdCount].Draw(500, 500, 20, 20, 40, 40, 0, 0);
	}

}
