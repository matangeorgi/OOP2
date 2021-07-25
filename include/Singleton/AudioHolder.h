#pragma once
#include <SFML/Audio.hpp>
#include "Macros.h"

// Singleton Class for audio.
class AudioHolder
{
public:

	static AudioHolder& instance();

	void playSound(int element);
	void stopBGSound();
	~AudioHolder();

private:

	AudioHolder();
	AudioHolder(const AudioHolder&) = default;
	AudioHolder& operator=(const AudioHolder&) = default;

	sf::SoundBuffer m_tracks[AUDIOS];
	sf::Sound m_sound[AUDIOS];
	sf::Music m_background;
};