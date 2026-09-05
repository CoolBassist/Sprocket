#pragma once
#include <SFML/Audio.hpp>
#include <spdlog/spdlog.h>
#include <string>
#include <unordered_map>

namespace sprocket::utils {

enum class Sound { ButtonClick };
enum class Music { Background };

class AudioManager {
public:
  static void addSound(Sound soundEnum, const std::string &filePath);
  static void addMusic(Music musicEnum, const std::string &filePath) {
    sf::Music music;
    if (music.openFromFile(filePath)) {
      musicBuffers[musicEnum] = std::move(music);
    } else {
      spdlog::error("Failed to load music: {}", filePath);
    }
  }

  static void playSound(const Sound &sound) { sounds[sound]->play(); }

  static void playMusic(const Music &music) {
    musicBuffers[music].play();
    musicBuffers[music].setLooping(true); // Loop the music
  }

  static bool isMusicPlaying(const Music &music) {
    return musicBuffers[music].getStatus() == sf::SoundSource::Status::Playing;
  }

  static void stopMusic(const Music &music) { musicBuffers[music].stop(); }

private:
  static std::unordered_map<Sound, sf::SoundBuffer *> soundBuffers;
  static std::unordered_map<Sound, sf::Sound *> sounds;
  static std::unordered_map<Music, sf::Music> musicBuffers;
};
} // namespace sprocket::utils
