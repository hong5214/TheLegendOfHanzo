#pragma once

// FMOD �����Ͻ� ����
#include<string>

int AddSoundFile(std::string _FullPath, bool IsLoop = false);
void EffectPlay(int _SoundNum);
void SkillPlay(int _SoundNum);

void BGPlay(int _SoundNum);
void VolumUp();
void VolumDown();
void BGStop();
bool BGPlayCheck();
