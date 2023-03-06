#pragma once
#include "SFML/Audio.hpp"

class Audio {
	public:
		void playMenuMusic();
		void playBgMusic();
		void playHurtSound();
		void playSwooshSound();

		sf::Music m_bgMusic;
		sf::Music m_menuMusic;

		sf::SoundBuffer hurtBuffer;
		sf::Sound hurtSound;

		sf::SoundBuffer swooshBuffer;
		sf::Sound swooshSound;
};