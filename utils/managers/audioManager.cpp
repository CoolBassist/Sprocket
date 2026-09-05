#include "audioManager.hpp"

using namespace sprocket::utils;

std::unordered_map<Sound, sf::SoundBuffer *> AudioManager::soundBuffers;
std::unordered_map<Sound, sf::Sound *> AudioManager::sounds;
std::unordered_map<Music, sf::Music> AudioManager::musicBuffers;

void AudioManager::addSound(Sound soundEnum, const std::string &filePath) {
  auto buffer = new sf::SoundBuffer();
  if (buffer->loadFromFile(filePath)) {
    soundBuffers[soundEnum] = buffer;
    sounds[soundEnum] = new sf::Sound(*buffer);
  } else {
    spdlog::error("Failed to load sound: {}", filePath);
  }
}
