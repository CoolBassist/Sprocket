#pragma once
#include "../../utils/gameState.hpp"
#include <SFML/Audio.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>

namespace sprocket::managers {

class AudioManager {
public:
  static void addSound(game::Sound soundEnum, const std::string &filePath);
  static void addMusic(game::Music musicEnum, const std::string &filePath);

  static void setMusicVolume(float volume);
  static float getMusicVolume() { return musicVolume; }
  static void setSoundEffectsVolume(float volume);
  static float getSoundEffectsVolume() { return soundEffectsVolume; }
  static void setMusicMuted(bool muted);
  static bool isMusicMuted() { return musicMuted; }
  static void setSoundEffectsMuted(bool muted);
  static bool isSoundEffectsMuted() { return soundEffectsMuted; }

  static void playSound(const game::Sound &sound) { sounds[sound]->play(); }

  static void playMusic(const game::Music &music) {
    musicBuffers[music].play();
    musicBuffers[music].setLooping(true);
  }

  static bool isMusicPlaying(const game::Music &music) {
    return musicBuffers[music].getStatus() == sf::SoundSource::Status::Playing;
  }

  static void stopMusic(const game::Music &music) {
    musicBuffers[music].stop();
  }

private:
  static void applyMusicVolume();
  static void applySoundEffectsVolume();

  static std::unordered_map<game::Sound, sf::SoundBuffer *> soundBuffers;
  static std::unordered_map<game::Sound, sf::Sound *> sounds;
  static std::unordered_map<game::Music, sf::Music> musicBuffers;
  static float musicVolume;
  static float soundEffectsVolume;
  static bool musicMuted;
  static bool soundEffectsMuted;
};
} // namespace sprocket::managers
