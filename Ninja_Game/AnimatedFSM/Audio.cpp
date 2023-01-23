#include "Audio.h"

void Audio::playBgMusic()
{
	if (!m_bgMusic.openFromFile("assets/audio/bgMusic.wav"))
	{
		// Error
	}

	m_bgMusic.setLoop(true);
	m_bgMusic.setPosition(.0f, .0f, .0f);
	m_bgMusic.setVolume(50.0f);
	m_bgMusic.play();
}

void Audio::playHurtSound()
{
	if (!hurtBuffer.loadFromFile("assets/audio/hurt.wav"))
	{
		// Error
	}

	hurtSound.setBuffer(hurtBuffer);
	hurtSound.setPosition(.0f, .0f, 20.0f);
	hurtSound.setVolume(750.0f);
	hurtSound.play();
}

void Audio::playSwooshSound()
{
	if (!swooshBuffer.loadFromFile("assets/audio/swoosh.wav"))
	{
		// Error
	}

	swooshSound.setBuffer(swooshBuffer);
	swooshSound.setPosition(.0f, .0f, 10.0f);
	swooshSound.setVolume(750.0f);
	swooshSound.play();
}
