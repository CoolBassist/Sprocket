#pragma once

#include "../utils/saveData.hpp"
#include <filesystem>
#include <optional>
#include <stdexcept>
#include <type_traits>

namespace sprocket::managers {

namespace detail {
void writeSaveFile(const std::filesystem::path &path,
                   const sprocket::utils::SaveData &data);
void readSaveFile(const std::filesystem::path &path,
                  sprocket::utils::SaveData &data);
} // namespace detail

template <typename Data> class SaveManager {
public:
  static void initialise(const std::filesystem::path &path) {
    if (data) {
      throw std::logic_error("SaveManager is already initialized");
    }
    if (path.empty()) {
      throw std::invalid_argument("Save file path must not be empty");
    }
    filePath = std::filesystem::absolute(path);
    data.emplace();
    load();
  }

  static Data &get() {
    if (!data) {
      throw std::logic_error("Initialize SaveManager before use");
    }
    return *data;
  }

  static void save() { detail::writeSaveFile(filePath, get()); }
  static void load() { detail::readSaveFile(filePath, get()); }

private:
  inline static std::optional<Data> data;
  inline static std::filesystem::path filePath;
};

} // namespace sprocket::managers
