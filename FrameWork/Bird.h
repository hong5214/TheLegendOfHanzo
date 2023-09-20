#pragma once
#include "Include.h"

class Bird
{
	Sprite Bdimg[2];


public :
	Bird();
	~Bird();

	DWORD m_BirdAniTime;
	int m_BirdCount;

	void Init();
	void Update();
	void Draw();

};

extern Bird bird;