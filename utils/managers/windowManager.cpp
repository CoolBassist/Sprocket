#include "windowManager.hpp"

using namespace sprocket::utils;

sf::RenderWindow WindowManager::window;
bool WindowManager::initialized = false;

void Utils::WindowManager::initialize(const sf::Vector2u &size,
                                      const std::string &title,
                                      unsigned int style,
                                      const int framerateLimit) {

  spdlog::info("Initializing window...");
  spdlog::info("Size: {}x{}", size.x, size.y);
  spdlog::info("Title: {}", title);
  window = sf::RenderWindow(sf::VideoMode(size), title, style);
  window.setFramerateLimit(framerateLimit);
  initialized = true;
}
