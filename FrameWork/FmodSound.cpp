#include "FMODENGIN/inc/fmod.hpp"
#pragma    comment (lib, "FMODENGIN/lib/fmodex64_vc.lib") // 1. ����� ����� ȿ��, �Ӽ� â�� ���̺귯�� �߰�
using namespace FMOD;

#include "FmodSound.h"

// STL �����̳�
#include <map>

// FMOD �����Ͻ� ���� Ŭ����
class FmodSound
{
	System* m_pSystem; // �ý����� �����͸� �����
	int m_Index;
	Channel* m_pBGChannel;
	Channel* pChannel1 = nullptr;
	Channel* pChannel2 = nullptr;
	float	m_volume;
public:
	std::map<std::string, int> m_CheckList;
	std::map<int, Sound*> m_SoundList;	// �ε����� ���� ����ü

	FmodSound()
	{
		System_Create(&m_pSystem); // m_pSystem�� �ּҸ� �ѱ�� �˾Ƽ� �ʱ�ȭ �� �ְڴ�.
		// init(ä�� �ִ� ������, �ʱ�ȭ ����, �߰��� ���� ���� ����̹�)
		m_pSystem->init(10, FMOD_INIT_NORMAL, 0); // �ʱ�ȭ ��

		m_Index = 0;
		m_volume = 0.1f;
		m_pBGChannel = nullptr; // �̰� ����?
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

	// ���� �߰� 
	int	AddSoundFile(std::string _FullPath, bool _IsLoop)
	{
		auto Find = m_CheckList.find(_FullPath);

		if (Find != m_CheckList.end())
		{
			return Find->second;
		}

		Sound* pSound = nullptr;
		int		Mode = FMOD_HARDWARE | (_IsLoop ? FMOD_LOOP_NORMAL | FMOD_DEFAULT : FMOD_LOOP_OFF);

		// ���带 ������ ��ο��� �� ��° ������ LOOP/ONCE �� ���� �ؼ� �ε� , ����( c_str : string = > char* ����)
		m_pSystem->createSound(_FullPath.c_str(), Mode, 0, &pSound);

		if (pSound == nullptr)
		{
			return -1;
		}

		m_CheckList.insert(std::make_pair(_FullPath, m_Index));
		m_SoundList.insert(std::make_pair(m_Index, pSound));

		return m_Index++;
	}

	// ����Ʈ �÷���
	void EffectPlay(int _SoundNum)
	{
		auto Find = m_SoundList.find(_SoundNum);

		// FMOD_CHANNEL_FREE : �ϳ��� ����, FMOD_CHANNEL_REUSE : �ߺ����� ����
		pChannel1->setVolume(1.0); // ������ ������ 0.0���� 1.0���� ����
		m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &pChannel1);
	}

	// ��ų ȿ����
	void SkillPlay(int _SoundNum)
	{
		auto Find = m_SoundList.find(_SoundNum);

		pChannel2->setVolume(1.0);
		m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &pChannel2);
	}

	// ����� �÷���
	void BGPlay(int _SoundNum)
	{
		auto Find = m_SoundList.find(_SoundNum);
		pChannel1->setVolume(0.1); // ������ ������ 0.0���� 1.0���� ����

		m_pSystem->playSound(FMOD_CHANNEL_REUSE, Find->second, 0, &m_pBGChannel);
	}

	// ����� ����
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

	// ���� �ٿ�
	void VolumDown()
	{
		m_volume -= 0.1f;
		if (m_volume <= 0) m_volume = 0;
		m_pBGChannel->setVolume(m_volume);
	}

	// ���� ��
	void VolumUp()
	{
		m_volume += 0.1f;
		if (m_volume >= 1.0) m_volume = 1.0;
		m_pBGChannel->setVolume(m_volume);
	}
};
static FmodSound g_SoundMgr;

// ���� ���� �߰� �Լ�
int	AddSoundFile(std::string _FullPath, bool _IsLoop)
{
	return g_SoundMgr.AddSoundFile(_FullPath, _IsLoop);
}

// ���� ����Ʈ �÷��� �Լ�
void EffectPlay(int _SoundNum)
{
	g_SoundMgr.EffectPlay(_SoundNum);
}

void SkillPlay(int _SoundNum)
{
	g_SoundMgr.SkillPlay(_SoundNum);
}

// ���� ����� ��� �Լ�
void BGPlay(int _SoundNum)
{
	g_SoundMgr.BGPlay(_SoundNum);
}

// ���� ���� ��
void VolumUp()
{
	g_SoundMgr.VolumUp();
}

// ���� ���� �ٿ�
void VolumDown()
{
	g_SoundMgr.VolumDown();
}

// ���� ����� ���� �Լ�
void BGStop()
{
	g_SoundMgr.BGStop();
}

// ���������� üũ
bool BGPlayCheck() {
	return g_SoundMgr.BGPlayCheck();
}