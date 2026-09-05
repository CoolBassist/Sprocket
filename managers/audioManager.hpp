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
  static void addMusic(game::Music musicEnum, const std::string &filePath) {
    sf::Music music;
    if (music.openFromFile(filePath)) {
      musicBuffers[musicEnum] = std::move(music);
    } else {
      spdlog::error("Failed to load music: {}", filePath);
    }
  }

  static void playSound(const game::Sound &sound) { sounds[sound]->play(); }

  static void playMusic(const game::Music &music) {
    musicBuffers[music].play();
    musicBuffers[music].setLooping(true); // Loop the music
  }

  static bool isMusicPlaying(const game::Music &music) {
    return musicBuffers[music].getStatus() == sf::SoundSource::Status::Playing;
  }

  static void stopMusic(const game::Music &music) {
    musicBuffers[music].stop();
  }

private:
  static std::unordered_map<game::Sound, sf::SoundBuffer *> soundBuffers;
  static std::unordered_map<game::Sound, sf::Sound *> sounds;
  static std::unordered_map<game::Music, sf::Music> musicBuffers;
};
} // namespace sprocket::managers
