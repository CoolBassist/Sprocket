#include "audioManager.hpp"
#include <algorithm>
#include <utility>

using namespace sprocket::managers;

std::unordered_map<game::Sound, sf::SoundBuffer *> AudioManager::soundBuffers;
std::unordered_map<game::Sound, sf::Sound *> AudioManager::sounds;
std::unordered_map<game::Music, sf::Music> AudioManager::musicBuffers;
float AudioManager::musicVolume = 100.0f;
float AudioManager::soundEffectsVolume = 100.0f;
bool AudioManager::musicMuted = false;
bool AudioManager::soundEffectsMuted = false;

void AudioManager::addSound(game::Sound soundEnum,
                            const std::string &filePath) {
  auto buffer = new sf::SoundBuffer();
  if (buffer->loadFromFile(filePath)) {
    soundBuffers[soundEnum] = buffer;
    sounds[soundEnum] = new sf::Sound(*buffer);
    sounds[soundEnum]->setVolume(soundEffectsMuted ? 0.0f : soundEffectsVolume);
  } else {
    spdlog::error("Failed to load sound: {}", filePath);
  }
}

void AudioManager::addMusic(game::Music musicEnum,
                            const std::string &filePath) {
  sf::Music music;
  if (music.openFromFile(filePath)) {
    music.setVolume(musicMuted ? 0.0f : musicVolume);
    musicBuffers[musicEnum] = std::move(music);
  } else {
    spdlog::error("Failed to load music: {}", filePath);
  }
}

void AudioManager::setMusicVolume(float volume) {
  musicVolume = std::clamp(volume, 0.0f, 100.0f);
  applyMusicVolume();
}

void AudioManager::setSoundEffectsVolume(float volume) {
  soundEffectsVolume = std::clamp(volume, 0.0f, 100.0f);
  applySoundEffectsVolume();
}

void AudioManager::setMusicMuted(bool muted) {
  musicMuted = muted;
  applyMusicVolume();
}

void AudioManager::setSoundEffectsMuted(bool muted) {
  soundEffectsMuted = muted;
  applySoundEffectsVolume();
}

void AudioManager::applyMusicVolume() {
  for (auto &entry : musicBuffers) {
    entry.second.setVolume(musicMuted ? 0.0f : musicVolume);
  }
}

void AudioManager::applySoundEffectsVolume() {
  for (auto &entry : sounds) {
    entry.second->setVolume(soundEffectsMuted ? 0.0f : soundEffectsVolume);
  }
}
