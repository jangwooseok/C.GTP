#include "pch.h"
#include "Sound.h"


//http://codingplus.tistory.com/61



CSound::CSound()
{
	CSound::Init();
	CSound::set_sound();
}


CSound::~CSound()
{	
	CSound::Release();
}

void CSound::Init()
{
	//�ý����� ũ������Ʈ
	FMOD::System_Create(&m_pSystem);
	
	//�ý����� init
	m_pSystem->init(SOUND_NUM, FMOD_INIT_NORMAL, nullptr);

	//�ý����� nul ���·� �ʱ�ȭ
	for (int i = 0; i < SOUND_NUM; i++)
		m_pSounds[i] = nullptr;


}

void CSound::Release()
{
	//���带 ������
	for (int i = 0; i < SOUND_NUM; i++)
		m_pSounds[i]->release();
	//�ý����� ������
	m_pSystem->release();
	//�ý��� �ݱ�
	m_pSystem->close();
}

void CSound::set_sound()
{
	m_pSystem->createStream(
		"Sound/Bgm1.mp3",
		FMOD_2D | FMOD_LOOP_NORMAL,
		nullptr,
		&m_pSounds[0]
	);

	m_pSystem->createStream(
		"Sound/Skill1.wav",
		FMOD_DEFAULT | FMOD_LOOP_OFF,
		nullptr,
		&m_pSounds[1]
	);

	m_pSystem->createStream(
		"Sound/Skill2.wav",
		FMOD_DEFAULT | FMOD_LOOP_OFF,
		nullptr,
		&m_pSounds[2]
	);
}

void CSound::Play(size_t soundid)
{
	m_pSystem->update();

	m_pSystem->playSound(FMOD_CHANNEL_REUSE,m_pSounds[soundid],false, &m_pChannel[soundid]);

}
