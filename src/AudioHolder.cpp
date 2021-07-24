#include "AudioHolder.h"

AudioHolder::AudioHolder()
{
	// Uploading the audio from resources.
	m_tracks[AUDIO_KILL].loadFromFile("enemykill.wav");
	m_tracks[AUDIO_JUMP].loadFromFile("jump.wav");
	m_tracks[AUDIO_FIRE].loadFromFile("fireball.wav");
	m_tracks[AUDIO_COIN].loadFromFile("coin.wav");
	m_tracks[AUDIO_FINISH_STAGE].loadFromFile("poledown.wav");
	m_tracks[AUDIO_LOST].loadFromFile("youlost.wav");
	m_tracks[AUDIO_BUMP].loadFromFile("bump.wav");
	m_tracks[AUDIO_PAUSE].loadFromFile("pause.wav");
	m_tracks[AUDIO_DEATH].loadFromFile("death.wav");
	m_tracks[AUDIO_BACKGROUND].loadFromFile("background.ogg");
	m_tracks[AUDIO_SUPER].loadFromFile("supermushroom.wav");
	m_tracks[AUDIO_WON].loadFromFile("won.wav");

	m_sound[AUDIO_KILL].setBuffer(m_tracks[AUDIO_KILL]);
	m_sound[AUDIO_JUMP].setBuffer(m_tracks[AUDIO_JUMP]);
	m_sound[AUDIO_FIRE].setBuffer(m_tracks[AUDIO_FIRE]);
	m_sound[AUDIO_COIN].setBuffer(m_tracks[AUDIO_COIN]);
	m_sound[AUDIO_FINISH_STAGE].setBuffer(m_tracks[AUDIO_FINISH_STAGE]);
	m_sound[AUDIO_LOST].setBuffer(m_tracks[AUDIO_LOST]);
	m_sound[AUDIO_BUMP].setBuffer(m_tracks[AUDIO_BUMP]);
	m_sound[AUDIO_PAUSE].setBuffer(m_tracks[AUDIO_PAUSE]);
	m_sound[AUDIO_DEATH].setBuffer(m_tracks[AUDIO_DEATH]);
	m_sound[AUDIO_BACKGROUND].setBuffer(m_tracks[AUDIO_BACKGROUND]);
	m_sound[AUDIO_SUPER].setBuffer(m_tracks[AUDIO_SUPER]);
	m_sound[AUDIO_WON].setBuffer(m_tracks[AUDIO_WON]);

	m_sound[AUDIO_BACKGROUND].setLoop(true);
}

//-----------------------------------------------------------------------------
void AudioHolder::playSound(int element)
{
	m_sound[element].play();
}

//-----------------------------------------------------------------------------
void AudioHolder::stopBGSound()
{
	m_sound[AUDIO_BACKGROUND].pause();
}

//-----------------------------------------------------------------------------
AudioHolder& AudioHolder::instance()
{
	static AudioHolder instance;
	return instance;
}

//-----------------------------------------------------------------------------
AudioHolder :: ~AudioHolder() {}