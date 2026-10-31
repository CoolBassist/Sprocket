#include "windowManager.hpp"

using namespace sprocket::managers;

sf::RenderWindow WindowManager::window;
bool WindowManager::initialized = false;

void sprocket::managers::WindowManager::initialize(const sf::Vector2u &size,
                                                   const std::string &title,
                                                   sf::Image favicon,
                                                   unsigned int style,
                                                   const int framerateLimit) {
  initialize(size, title, style, framerateLimit);
  window.setIcon(favicon.getSize(), favicon.getPixelsPtr());
}

void WindowManager::initialize(const sf::Vector2u &size,
                               const std::string &title, unsigned int style,
                               const int framerateLimit) {
  spdlog::info("Initializing window...");
  spdlog::info("Size: {}x{}", size.x, size.y);
  spdlog::info("Title: {}", title);
  window = sf::RenderWindow(sf::VideoMode(size), title, style);
  window.setFramerateLimit(framerateLimit);
  initialized = true;
}
