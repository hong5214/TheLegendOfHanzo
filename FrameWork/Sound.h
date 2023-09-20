#pragma once

class Sound
{
	
public:
	Sound(void);
	~Sound(void);
int BG; // 배경음
int ATK; // 공격음
int GENJIATK; // 겐지공격음
int BUTTONCLICK; // 버튼 클릭음
int SKILL0; // 플레이어 스킬 사운드

int m_Select;
void Init();	
void BGChange(std::string filename);
};

extern Sound sound;