#pragma once
#include <SFML/Graphics.hpp>
#include <spdlog/spdlog.h>

namespace Utils {
class WindowManager {
public:
  static void initialize(const sf::Vector2u &size, const std::string &title,
                         unsigned int style = sf::Style::Default,
                         const int framerateLimit = 60);
  static void shutdown() {
    spdlog::info("Shutting down window...");
    window.close();
  }
  static sf::RenderWindow &getWindow() { return window; };
  static void clear(const sf::Color color = sf::Color::White) {
    window.clear(color);
  }
  static void display() { window.display(); }
  static sf::Vector2f mapPixelToCoords(const sf::Vector2i &pixelPos) {
    return window.mapPixelToCoords(pixelPos);
  }

private:
  static bool initialized;
  static sf::RenderWindow window;
};
} // namespace Utils
