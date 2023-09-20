#include "FMODENGIN/inc/fmod.hpp"
#pragma    comment (lib, "FMODENGIN/lib/fmodex64_vc.lib") // 1. 경로의 명시적 효과, 속성 창에 라이브러리 추가
using namespace FMOD;

#include "FmodSound.h"

// STL 컨테이너
#include <map>

// FMOD 비지니스 로직 클래스
class FmodSound
{
	System* m_pSystem; // 시스템의 포인터를 만들고
	int m_Index;
	Channel* m_pBGChannel;
	Channel* pChannel1 = nullptr;
	Channel* pChannel2 = nullptr;
	float	m_volume;
public:
	std::map<std::string, int> m_CheckList;
	std::map<int, Sound*> m_SoundList;	// 인덱스와 사운드 그자체

	FmodSound()
	{
		System_Create(&m_pSystem); // m_pSystem의 주소를 넘기면 알아서 초기화 해 주겠다.
		// init(채널 최대 설정값, 초기화 시점, 추가로 넣을 보조 드라이버)
		m_pSystem->init(10, FMOD_INIT_NORMAL, 0); // 초기화 끝

		m_Index = 0;
		m_volume = 0.1f;
		m_pBGChannel = nullptr; // 이건 뭘까?
		pChannel1 = nullptr;
		pChannel2 = nullptr;
	}
	~FmodSound()
	{
		m_CheckList.clear();

		for (auto& Iter : m_SoundList)
		{
			Iter.second->release();
		}
		m_SoundList.clear();
		m_pSystem->release();
		m_pSystem->close();
	}

	// 사운드 추가 
	int	AddSoundFile(std::string _FullPath, bool _IsLoop)
	{
		auto Find = m_CheckList.find(_FullPath);

		if (Find != m_CheckList.end())
		{
			return Find->second;
		}

		Sound* pSound = nullptr;
		int		Mode = FMOD_HARDWARE | (_IsLoop ? FMOD_LOOP_NORMAL | FMOD_DEFAULT : FMOD_LOOP_OFF);

		// 사운드를 지정된 경로에서 두 번째 인자인 LOOP/ONCE 로 선택 해서 로딩 , 참고( c_str : string = > char* 변경)
		m_pSystem->createSound(_FullPath.c_str(), Mode, 0, &pSound);

		if (pSound == nullptr)
		{
			return -1;
		}

		m_CheckList.insert(std::make_pair(_FullPath, m_Index));
		m_SoundList.insert(std::make_pair(m_Index, pSound));

		return m_Index++;
	}

	// 이펙트 플레이
	void EffectPlay(int _SoundNum)
	{
		auto Find = m_SoundList.find(_SoundNum);

		// FMOD_CHANNEL_FREE : 하나만 실행, FMOD_CHANNEL_REUSE : 중복실행 가능
		pChannel1->setVolume(1.0); // 볼륨음 조절은 0.0부터 1.0까지 가능
		m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &pChannel1);
	}

	// 스킬 효과음
	void SkillPlay(int _SoundNum)
	{
		auto Find = m_SoundList.find(_SoundNum);

		pChannel2->setVolume(1.0);
		m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &pChannel2);
	}

	// 배경음 플레이
	void BGPlay(int _SoundNum)
	{
		auto Find = m_SoundList.find(_SoundNum);
		pChannel1->setVolume(0.1); // 볼륨음 조절은 0.0부터 1.0까지 가능

		m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &m_pBGChannel);
	}

	// 배경음 멈춤
	void BGStop()
	{
		if (m_pBGChannel != nullptr)
		{
			m_pBGChannel->stop();
		}
	}
	bool BGPlayCheck() {
		return m_pBGChannel != nullptr;
	}

	// 볼륨 다운
	void VolumDown()
	{
		m_volume -= 0.1f;
		if (m_volume <= 0) m_volume = 0;
		m_pBGChannel->setVolume(m_volume);
	}

	// 볼륨 업
	void VolumUp()
	{
		m_volume += 0.1f;
		if (m_volume >= 1.0) m_volume = 1.0;
		m_pBGChannel->setVolume(m_volume);
	}
};
static FmodSound g_SoundMgr;

// 전역 사운드 추가 함수
int	AddSoundFile(std::string _FullPath, bool _IsLoop)
{
	return g_SoundMgr.AddSoundFile(_FullPath, _IsLoop);
}

// 전역 이펙트 플레이 함수
void EffectPlay(int _SoundNum)
{
	g_SoundMgr.EffectPlay(_SoundNum);
}

void SkillPlay(int _SoundNum)
{
	g_SoundMgr.SkillPlay(_SoundNum);
}

// 전역 배경음 출력 함수
void BGPlay(int _SoundNum)
{
	g_SoundMgr.BGPlay(_SoundNum);
}

// 전역 볼륨 업
void VolumUp()
{
	g_SoundMgr.VolumUp();
}

// 전역 볼륨 다운
void VolumDown()
{
	g_SoundMgr.VolumDown();
}

// 전역 배경음 중지 함수
void BGStop()
{
	g_SoundMgr.BGStop();
}

// 실행중인지 체크
bool BGPlayCheck() {
	return g_SoundMgr.BGPlayCheck();
}