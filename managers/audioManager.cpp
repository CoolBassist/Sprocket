#include "audioManager.hpp"

using namespace sprocket::managers;

std::unordered_map<game::Sound, sf::SoundBuffer *> AudioManager::soundBuffers;
std::unordered_map<game::Sound, sf::Sound *> AudioManager::sounds;
std::unordered_map<game::Music, sf::Music> AudioManager::musicBuffers;

void AudioManager::addSound(game::Sound soundEnum,
                            const std::string &filePath) {
  auto buffer = new sf::SoundBuffer();
  if (buffer->loadFromFile(filePath)) {
    soundBuffers[soundEnum] = buffer;
    sounds[soundEnum] = new sf::Sound(*buffer);
  } else {
    spdlog::error("Failed to load sound: {}", filePath);
  }
}
