#pragma once

class Sound
{
	
public:
	Sound(void);
	~Sound(void);
int BG; // �����
int ATK; // ������
int GENJIATK; // ����������
int BUTTONCLICK; // ��ư Ŭ����
int SKILL0; // �÷��̾� ��ų ����

int m_Select;
void Init();	
void BGChange(std::string filename);
};

extern Sound sound;