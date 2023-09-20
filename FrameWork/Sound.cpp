#include "Include.h"

Sound sound;



Sound::Sound(void)
{
	//g_pSoundManager = NULL; 사용 안했다
}

Sound::~Sound(void)
{
}

void Sound::Init()
{
	BG = AddSoundFile("./resource/Sound/BGM_Lobby.mp3", true);
	ATK = AddSoundFile("./resource/Sound/PlayerAtk.mp3", false);
	GENJIATK = AddSoundFile("./resource/Sound/AtkSound_Genji.mp3", false);
	BUTTONCLICK = AddSoundFile("./resource/Sound/ButtonClick.mp3", false);
	SKILL0 = AddSoundFile("./resource/Sound/SkillSound0.mp3", false);	
}


void Sound::BGChange(std::string filename) {
	BGStop();
	BG = AddSoundFile(filename, true);
	BGPlay(BG);
}