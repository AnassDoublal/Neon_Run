#pragma once
#include <SFML/Audio.hpp>

class Audio {
	public:
		void playBgMusic();
		void playHurtSound();
		void playSwooshSound();
	private:
		sf::Music m_bgMusic;

		sf::SoundBuffer hurtBuffer;
		sf::Sound hurtSound;

		sf::SoundBuffer swooshBuffer;
		sf::Sound swooshSound;
};